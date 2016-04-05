

#include <string.h>
#include "enc28j60.h"
#include "ip_arp_udp_tcp.h"
#include "net.h"
#include "simple_server.h"
#include "stdio.h"
#define PSTR(s) s
extern  void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);


// please modify the following two lines. mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:
static unsigned char myip[4] = {192,168,1,15};
extern unsigned char mymac[6];

// base url (you can put a DNS name instead of an IP addr. if you have
// a DNS server (baseurl must end in "/"):
static char baseurl[]="http://192.168.1.15/";
static unsigned int mywwwport = 80; // listen port for tcp/www (max range 1-254)
// or on a different port:
//static char baseurl[]="http://10.0.0.24:88/";
//static unsigned int mywwwport =88; // listen port for tcp/www (max range 1-254)
//
static unsigned int myudpport =1200; // listen port for udp
// how did I get the mac addr? Translate the first 3 numbers into ascii is: TUX

#define BUFFER_SIZE 1500//400
static unsigned char buf[BUFFER_SIZE+1];

// the password string (only the first 5 char checked), (only a-z,0-9,_ characters):
static char password[]="SZIII"; // must not be longer than 9 char

#define LED1_ON()   GPIO_ResetBits(GPIOF, GPIO_Pin_6);
#define LED1_OFF()  GPIO_SetBits(GPIOF, GPIO_Pin_6);  
// 
unsigned char verify_password(char *str)
{
	// the first characters of the received string are
	// a simple password/cookie:
	if (strncmp(password,str,5)==0)
	{
	    return(1);
	}
	return(0);
}

// takes a string of the form password/commandNumber and analyse it
// return values: -1 invalid password, otherwise command number
//                -2 no command given but password valid
signed char analyse_get_url(char *str)
{
	unsigned char i=0;
	if (verify_password(str)==0)
	{
		return(-1);
	}
	// find first "/"
	// passw not longer than 9 char:
	while(*str && i<10 && *str >',' && *str<'{')
	{
        if (*str=='/')
		{
            str++;
            break;
        }
        i++;
        str++;
	}
	if (*str < 0x3a && *str > 0x2f)
	{
        // is a ASCII number, return it
        return(*str-0x30);
	}
	return(-2);
}

// prepare the webpage by writing the data to the tcp send buffer
unsigned int print_webpage(unsigned char *buf,unsigned char on_off)
	{
    unsigned int plen;
    plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
    plen=fill_tcp_data_p(buf,plen,PSTR("<center><p>DS1 LED灯输出: "));
    if (on_off)
	{
        plen=fill_tcp_data_p(buf,plen,PSTR("<font color=\"#00FF00\"> 亮</font>"));
    }
	else
	{
        plen=fill_tcp_data_p(buf,plen,PSTR("灭"));
    }

    plen=fill_tcp_data_p(buf,plen,PSTR(" <small><a href=\""));
    plen=fill_tcp_data(buf,plen,baseurl);
    plen=fill_tcp_data(buf,plen,password);
    plen=fill_tcp_data_p(buf,plen,PSTR("\">[刷新]</a></small></p>\n<p><a href=\""));

    plen=fill_tcp_data(buf,plen,baseurl);
    plen=fill_tcp_data(buf,plen,password);
    if (on_off)
	{
        plen=fill_tcp_data_p(buf,plen,PSTR("/0\">关闭DS1 LED</a><p>"));
    }
	else
	{
        plen=fill_tcp_data_p(buf,plen,PSTR("/1\">开启DS1 LED</a><p>"));
	}

    plen=fill_tcp_data_p(buf,plen,PSTR("<center><hr><br>神舟III号STM32开发板 WEB 网页试验\n</center>"));
    
    return(plen);
}

int simple_server(void)
{  
    unsigned int plen,dat_p,i1=0,payloadlen=0;
    unsigned char i=0;
	char *buf1 = 0;
    signed char cmd;
    
	init_ip_arp_udp_tcp(mymac,myip,mywwwport);
    printf("\n\r神舟III号MAC地址:0x%x,0x%x,0x%x,0x%x,0x%x,0x%x",mymac[0],mymac[1],mymac[2],mymac[3],mymac[4],mymac[5]);
    printf("\n\r         IP地址:%d.%d.%d.%d",myip[0],myip[1],myip[2],myip[3]);
    printf("\n\r         端口号:%d\n\r\n\r",mywwwport);

	//init the ethernet/ip layer:
    while(1)
    {
        //判断是否有接收到有效的包
        plen = enc28j60PacketReceive(BUFFER_SIZE, buf);
        //如果收到有效的包，plen将为非0值。
        if(plen==0)
        {
            continue; //没有收到有效的包就退出重新检测
        }
		//当收到目的地址为本机IP的ARP包时，发出ARP相应包
        if(eth_type_is_arp_and_my_ip(buf,plen))
        {
			make_arp_answer_from_request(buf);
            continue;
        }
        
        //判断是否接收到目的地址为本机IP的合法的IP包
        if(eth_type_is_ip_and_my_ip(buf,plen)==0) 
        {
            continue;
        }
        //如果收到ICMP包
        if(buf[IP_PROTO_P]==IP_PROTO_ICMP_V && buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V)
        {

            printf("\n\r收到主机[%d.%d.%d.%d]发送的ICMP包",buf[ETH_ARP_SRC_IP_P],buf[ETH_ARP_SRC_IP_P+1],
                                                           buf[ETH_ARP_SRC_IP_P+2],buf[ETH_ARP_SRC_IP_P+3]);
			make_echo_reply_from_request(buf, plen);
			continue;
        }
        
        //如果收到TCP包，且端口为80
		if (buf[IP_PROTO_P]==IP_PROTO_TCP_V&&buf[TCP_DST_PORT_H_P]==0&&buf[TCP_DST_PORT_L_P]==mywwwport)
		{
		    printf("\n\r神舟III号接收到TCP包，端口为80。");
            if (buf[TCP_FLAGS_P] & TCP_FLAGS_SYN_V)
			{
			    printf("包类型为SYN");
                make_tcp_synack_from_syn(buf);
                continue;
            }
	        if (buf[TCP_FLAGS_P] & TCP_FLAGS_ACK_V)
			{
			    printf("包类型为ACK");
	            init_len_info(buf); // init some data structures
	            dat_p=get_tcp_data_pointer();
	            if (dat_p==0)
				{
	                if (buf[TCP_FLAGS_P] & TCP_FLAGS_FIN_V)
					{
	                    make_tcp_ack_from_any(buf);/*发送响应*/
	                }
	                // 发送一个没有数据的ACK响应，等待下一个包
	                continue;
	            }
				if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0)
				{
			        // 如果是Telnet方式登录，返回如下提示信息
			        plen=fill_tcp_data_p(buf,0,PSTR("神舟III号\r\n\n\rHTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>200 OK</h1>"));
			        goto SENDTCP;
				}
				if (strncmp("/ ",(char *)&(buf[dat_p+4]),2)==0)
				{
				    //如果是通过网页方式登录，输出如下提示信息
			        plen=fill_tcp_data_p(buf,plen,PSTR("<p>Usage: "));
			        plen=fill_tcp_data(buf,plen,baseurl);
			        plen=fill_tcp_data_p(buf,plen,PSTR("password</p>"));
			        goto SENDTCP;
				}
                //分析网页控制的命令类型
				cmd=analyse_get_url((char *)&(buf[dat_p+5]));
				if (cmd==-1)
				{
			        plen=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));
			        goto SENDTCP;
				}
                //网页控制点亮LED灯DS1
				if (cmd==1)
				{
                    LED1_ON();
					i=1;
				}
                //网页控制熄灭LED灯DS1
				if (cmd==0)
				{
                    LED1_OFF();
					i=0;
				}
				//更新网页信息
				plen=print_webpage(buf,(i));
				
			SENDTCP:
				make_tcp_ack_from_any(buf); // send ack for http get
				make_tcp_ack_with_data(buf,plen); // send data
				continue;
			}
		}

	    //UDP包，监听1200端口的UDP包
		if (buf[IP_PROTO_P]==IP_PROTO_UDP_V&&buf[UDP_DST_PORT_H_P]==4&&buf[UDP_DST_PORT_L_P]==0xb0)
		{
			payloadlen=	  buf[UDP_LEN_H_P];
			payloadlen=payloadlen<<8;
			payloadlen=(payloadlen+buf[UDP_LEN_L_P])-UDP_HEADER_LEN;
	
            //ANSWER
            for(i1=0; i1<payloadlen; i1++)
            {         
                buf1[i1]=buf[UDP_DATA_P+i1];
            }
			
			//make_udp_reply_from_request(buf,str,strlen(str),myudpport);
			make_udp_reply_from_request(buf,buf1,payloadlen,myudpport);
		}
	}
}
