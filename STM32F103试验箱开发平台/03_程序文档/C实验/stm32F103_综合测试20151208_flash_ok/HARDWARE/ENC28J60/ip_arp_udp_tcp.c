
//#include <includes.h>
#include "net.h"
#include "ip_arp_udp_tcp.h"
#include "enc28j60.h"
#include "stdio.h"
#define  pgm_read_byte(ptr)  ((char)*(ptr))

//#define unsigned char  unsigned char
//#define unsigned  int unisgned int

static unsigned char wwwport=80;
static unsigned char macaddr[6];
static unsigned char ipaddr[4];
static unsigned int info_hdr_len=0;
static unsigned int info_data_len=0;
static unsigned char seqnum=0xa; // my initial tcp sequence number

// The Ip checksum is calculated over the ip header only starting
// with the header length field and a total length of 20 bytes
// unitl ip.dst
// You must set the IP checksum field to zero before you start
// the calculation.
// len for ip is 20.
//
// For UDP/TCP we do not make up the required pseudo header. Instead we 
// use the ip.src and ip.dst fields of the real packet:
// The udp checksum calculation starts with the ip.src field
// Ip.src=4bytes,Ip.dst=4 bytes,Udp header=8bytes + data length=16+len
// In other words the len here is 8 + length over which you actually
// want to calculate the checksum.
// You must set the checksum field to zero before you start
// the calculation.
// len for udp is: 8 + 8 + data length
// len for tcp is: 4+4 + 20 + option len + data length
//
// For more information on how this algorithm works see:
// http://www.netfor2.com/checksum.html
// http://www.msc.uky.edu/ken/cs471/notes/chap3.htm
// The RFC has also a C code example: http://www.faqs.org/rfcs/rfc1071.html
unsigned  int checksum(unsigned char *buf, unsigned  int len,unsigned char type)
	{
	// type 0=ip 
	//      1=udp
	//      2=tcp
	unsigned long sum = 0;
	
	//if(type==0){
	//        // do not add anything
	//}
	if(type==1)
		{
		sum+=IP_PROTO_UDP_V; // protocol udp
		// the length here is the length of udp (data+header len)
		// =length given to this function - (IP.scr+IP.dst length)
		sum+=len-8; // = real tcp len
		}
	if(type==2)
		{
		sum+=IP_PROTO_TCP_V; 
		// the length here is the length of tcp (data+header len)
		// =length given to this function - (IP.scr+IP.dst length)
		sum+=len-8; // = real tcp len
		}
	// build the sum of 16bit words
	while(len >1)
		{
		sum += 0xFFFF & (*buf<<8|*(buf+1));
		buf+=2;
		len-=2;
		}
	// if there is a byte left then add it (padded with zero)
	if (len)
		{
		sum += (0xFF & *buf)<<8;
		}
	// now calculate the sum over the bytes in the sum
	// until the result is only 16bit long
	while (sum>>16)
		{
		sum = (sum & 0xFFFF)+(sum >> 16);
		}
	// build 1's complement:
	return( (unsigned  int) sum ^ 0xFFFF);
	}

// you must call this function once before you use any of the other functions:
void init_ip_arp_udp_tcp(unsigned char *mymac,unsigned char *myip,unsigned char wwwp)
{
	unsigned char i=0;
	wwwport=wwwp;
	while(i<4)
	{
        ipaddr[i]=myip[i];
        i++;
	}
	i=0;
	while(i<6)
	{
        macaddr[i]=mymac[i];
        i++;
	}
}
/*----------------------------------------------------------------------------------
当收到目的IP为本机IP的ARP包时，返回值为1，否则返回0
-----------------------------------------------------------------------------------*/
unsigned char eth_type_is_arp_and_my_ip(unsigned char *buf,unsigned  int len)
{
	unsigned char i=0;
    //包长度不够，直接返回
	if (len<41)
	{
	    return(0);
	}

    //如果类型不是ARP包，直接返回
	if(buf[ETH_TYPE_H_P] != ETHTYPE_ARP_H_V || buf[ETH_TYPE_L_P] != ETHTYPE_ARP_L_V)
	{
	    return(0);
	}

    //如果ARP包的IP地址与本机IP不一致，直接返回
	while(i<4)
	{
	    if(buf[ETH_ARP_DST_IP_P+i] != ipaddr[i])
		{
	        return(0);
	    }
	    i++;
	}
    printf("\n\r收到主机[%d.%d.%d.%d]发送的ARP包",buf[ETH_ARP_SRC_IP_P],buf[ETH_ARP_SRC_IP_P+1],buf[ETH_ARP_SRC_IP_P+2],buf[ETH_ARP_SRC_IP_P+3]);
    
	return(1);
}

unsigned char eth_type_is_ip_and_my_ip(unsigned char *buf,unsigned  int len)
{
	unsigned char i=0;
    //包长度不够，直接返回
	if (len<42)
	{
	    return(0);
	}
    
    //如果包类型不是IP包，直接返回
	if(buf[ETH_TYPE_H_P]!=ETHTYPE_IP_H_V || buf[ETH_TYPE_L_P]!=ETHTYPE_IP_L_V)
	{

        return(0);
	}
    //如果长度参数不正确，直接返回
	if (buf[IP_HEADER_LEN_VER_P]!=0x45)
	{
	    // must be IP V4 and 20 byte header
	    return(0);
	}
    
    //如果IP包的IP地址与本机IP不一致，直接返回    
	while(i<4)
	{
	    if(buf[IP_DST_P+i]!=ipaddr[i])
		{
	        return(0);
	    }
	    i++;
	}
	return(1);
}

// make a return eth header from a received eth packet
void make_eth(unsigned char *buf)
{
	unsigned char i=0;

	//填写包的目的MAC地址，以及源MAC地址
	while(i<6)
	{
        buf[ETH_DST_MAC +i]=buf[ETH_SRC_MAC +i];
        buf[ETH_SRC_MAC +i]=macaddr[i];
        i++;
	}
}
void fill_ip_hdr_checksum(unsigned char *buf)
	{
	unsigned  int ck;
	// clear the 2 byte checksum
	buf[IP_CHECKSUM_P]=0;
	buf[IP_CHECKSUM_P+1]=0;
	buf[IP_FLAGS_P]=0x40; // don't fragment
	buf[IP_FLAGS_P+1]=0;  // fragement offset
	buf[IP_TTL_P]=64; // ttl
	// calculate the checksum:
	ck=checksum(&buf[IP_P], IP_HEADER_LEN,0);
	buf[IP_CHECKSUM_P]=ck>>8;
	buf[IP_CHECKSUM_P+1]=ck& 0xff;
	}

// make a return ip header from a received ip packet
void make_ip(unsigned char *buf)
{
	unsigned char i=0;
	while(i<4)
	{
        buf[IP_DST_P+i]=buf[IP_SRC_P+i];
        buf[IP_SRC_P+i]=ipaddr[i];
        i++;
	}
	fill_ip_hdr_checksum(buf);
}

// make a return tcp header from a received tcp packet
// rel_ack_num is how much we must step the seq number received from the
// other side. We do not send more than 255 bytes of text (=data) in the tcp packet.
// If mss=1 then mss is included in the options list
//
// After calling this function you can fill in the first data byte at TCP_OPTIONS_P+4
// If cp_seq=0 then an initial sequence number is used (should be use in synack)
// otherwise it is copied from the packet we received
void make_tcphead(unsigned char *buf,unsigned  int rel_ack_num,unsigned char mss,unsigned char cp_seq)
	{
	unsigned char i=0;
	unsigned char tseq;
	while(i<2)
		{
	    buf[TCP_DST_PORT_H_P+i]=buf[TCP_SRC_PORT_H_P+i];
	    buf[TCP_SRC_PORT_H_P+i]=0; // clear source port
	    i++;
		}
	// set source port  (http):
	buf[TCP_SRC_PORT_L_P]=wwwport;
	i=4;
	// sequence numbers:
	// add the rel ack num to SEQACK
	while(i>0)
		{
	    rel_ack_num=buf[TCP_SEQ_H_P+i-1]+rel_ack_num;
	    tseq=buf[TCP_SEQACK_H_P+i-1];
	    buf[TCP_SEQACK_H_P+i-1]=0xff&rel_ack_num;
	    if (cp_seq)
				{
		        // copy the acknum sent to us into the sequence number
		        buf[TCP_SEQ_H_P+i-1]=tseq;
		    	}
			else
				{
	            buf[TCP_SEQ_H_P+i-1]= 0; // some preset vallue
	    		}
	    rel_ack_num=rel_ack_num>>8;
	    i--;
		}
	if (cp_seq==0)
		{
	    // put inital seq number
	    buf[TCP_SEQ_H_P+0]= 0;
	    buf[TCP_SEQ_H_P+1]= 0;
	    // we step only the second byte, this allows us to send packts 
	    // with 255 bytes or 512 (if we step the initial seqnum by 2)
	    buf[TCP_SEQ_H_P+2]= seqnum; 
	    buf[TCP_SEQ_H_P+3]= 0;
	    // step the inititial seq num by something we will not use
	    // during this tcp session:
	    seqnum+=2;
		}
	// zero the checksum
	buf[TCP_CHECKSUM_H_P]=0;
	buf[TCP_CHECKSUM_L_P]=0;
	
	// The tcp header length is only a 4 bit field (the upper 4 bits).
	// It is calculated in units of 4 bytes. 
	// E.g 24 bytes: 24/4=6 => 0x60=header len field
	//buf[TCP_HEADER_LEN_P]=(((TCP_HEADER_LEN_PLAIN+4)/4)) <<4; // 0x60
	if (mss)
			{
		    // the only option we set is MSS to 1408:
		    // 1408 in hex is 0x580
		    buf[TCP_OPTIONS_P]=2;
		    buf[TCP_OPTIONS_P+1]=4;
		    buf[TCP_OPTIONS_P+2]=0x05; 
		    buf[TCP_OPTIONS_P+3]=0x80;
		    // 24 bytes:
		    buf[TCP_HEADER_LEN_P]=0x60;
			}
		else
			{
		    // no options:
		    // 20 bytes:
		    buf[TCP_HEADER_LEN_P]=0x50;
			}
	}

void make_arp_answer_from_request(unsigned char *buf)
{
	unsigned char i=0;
    
	//填写包的目的MAC地址以及源MAC地址	
	make_eth(buf); 
    
    //填写ARP响应包的类型
	buf[ETH_ARP_OPCODE_H_P]=ETH_ARP_OPCODE_REPLY_H_V;   //arp 响应
	buf[ETH_ARP_OPCODE_L_P]=ETH_ARP_OPCODE_REPLY_L_V;

    //填写ARP包的目的MAC地址以及源MAC地址
	while(i<6)
	{
        buf[ETH_ARP_DST_MAC_P+i]=buf[ETH_ARP_SRC_MAC_P+i];
        buf[ETH_ARP_SRC_MAC_P+i]=macaddr[i];
        i++;
	}

    //填写ARP包的目的IP地址以及源IP地址    
	i=0;
	while(i<4)
	{
        buf[ETH_ARP_DST_IP_P+i]=buf[ETH_ARP_SRC_IP_P+i];
        buf[ETH_ARP_SRC_IP_P+i]=ipaddr[i];
        i++;
	}

    printf("\n\r神舟III号[%d.%d.%d.%d]发送ARP相应",ipaddr[0],ipaddr[1],ipaddr[2],ipaddr[3]);

    //发送ARP相应包
	enc28j60PacketSend(42,buf); 
}

void make_echo_reply_from_request(unsigned char *buf,unsigned  int len)
{
	//填写包的目的MAC地址以及源MAC地址	
	make_eth(buf);
	//填写包的目的IP地址以及源IP地址	
	make_ip(buf);

    //填写ICMP相应包类型
	buf[ICMP_TYPE_P]=ICMP_TYPE_ECHOREPLY_V;	  //////回送应答////////////////////////////////////////////////////////////////////////////

    // we changed only the icmp.type field from request(=8) to reply(=0).
	// we can therefore easily correct the checksum:
	if (buf[ICMP_CHECKSUM_P] > (0xff-0x08))
	{
	    buf[ICMP_CHECKSUM_P+1]++;
	}
	buf[ICMP_CHECKSUM_P]+=0x08;

    printf("\n\r神舟III号[%d.%d.%d.%d]发送ICMP包响应",ipaddr[0],ipaddr[1],ipaddr[2],ipaddr[3]);

    //发送ICMP响应包
	enc28j60PacketSend(len,buf);
}

// you can send a max of 220 bytes of data
void make_udp_reply_from_request(unsigned char *buf,char *data,unsigned int datalen,unsigned  int port)
	{
	unsigned int i=0;
	unsigned  int ck;
	make_eth(buf);
	
	// total length field in the IP header must be set:
	i= IP_HEADER_LEN+UDP_HEADER_LEN+datalen;
	buf[IP_TOTLEN_H_P]=i>>8;
	buf[IP_TOTLEN_L_P]=i;
	make_ip(buf);
	buf[UDP_DST_PORT_H_P]=port>>8;
	buf[UDP_DST_PORT_L_P]=port & 0xff;
	// source port does not matter and is what the sender used.
	// calculte the udp length:
	buf[UDP_LEN_H_P]=datalen>>8;
	buf[UDP_LEN_L_P]=UDP_HEADER_LEN+datalen;
	// zero the checksum
	buf[UDP_CHECKSUM_H_P]=0;
	buf[UDP_CHECKSUM_L_P]=0;
	// copy the data:
	while(i<datalen)
		{
        buf[UDP_DATA_P+i]=data[i];
        i++;
		}
	ck=checksum(&buf[IP_SRC_P], 16 + datalen,1);
	buf[UDP_CHECKSUM_H_P]=ck>>8;
	buf[UDP_CHECKSUM_L_P]=ck& 0xff;

	enc28j60PacketSend(UDP_HEADER_LEN+IP_HEADER_LEN+ETH_HEADER_LEN+datalen,buf);
	}

void make_tcp_synack_from_syn(unsigned char *buf)
{
	unsigned  int ck;
    
	//填写包的目的MAC地址以及源MAC地址	
	make_eth(buf);
	//计算包的长度
	// total length field in the IP header must be set: 20 bytes IP + 24 bytes (20tcp+4tcp options)
	buf[IP_TOTLEN_H_P]=0;
	buf[IP_TOTLEN_L_P]=IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN+4;
	//填写包的目的IP地址以及源IP地址	
	make_ip(buf);
	buf[TCP_FLAGS_P]=TCP_FLAGS_SYNACK_V;
	make_tcphead(buf,1,1,0);
	// calculate the checksum, len=8 (start from ip.src) + TCP_HEADER_LEN_PLAIN + 4 (one option: mss)
	ck=checksum(&buf[IP_SRC_P], 8+TCP_HEADER_LEN_PLAIN+4,2);
	buf[TCP_CHECKSUM_H_P]=ck>>8;
	buf[TCP_CHECKSUM_L_P]=ck& 0xff;
	// add 4 for option mss:
    printf("\n\r神舟III号[%d.%d.%d.%d]发送SYN包响应",ipaddr[0],ipaddr[1],ipaddr[2],ipaddr[3]);
	
	enc28j60PacketSend(IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN+4+ETH_HEADER_LEN,buf);
}

// get a pointer to the start of tcp data in buf
// Returns 0 if there is no data
// You must call init_len_info once before calling this function
unsigned  int get_tcp_data_pointer(void)
{
	if (info_data_len)
	{
	    return((unsigned  int)TCP_SRC_PORT_H_P+info_hdr_len);
	}
	else
	{
	    return(0);
	}
}

// do some basic length calculations and store the result in static varibales
void init_len_info(unsigned char *buf)
{
    info_data_len=(buf[IP_TOTLEN_H_P]<<8)|(buf[IP_TOTLEN_L_P]&0xff);
    info_data_len-=IP_HEADER_LEN;
    info_hdr_len=(buf[TCP_HEADER_LEN_P]>>4)*4; // generate len in bytes;
    info_data_len-=info_hdr_len;
    if (info_data_len<=0)
	{
        info_data_len=0;
    }
}

// fill in tcp data at position pos. pos=0 means start of
// tcp data. Returns the position at which the string after
// this string could be filled.
unsigned  int fill_tcp_data_p(unsigned char *buf,unsigned  int pos, const unsigned char *progmem_s)
	{
	char c;
	// fill in tcp data at position pos	  jesse

	while ((c = pgm_read_byte(progmem_s++)) != 0) 
		{
	    	buf[TCP_CHECKSUM_L_P+3+pos]=c;
	    	pos++;
		}
	return(pos);
	}

// fill in tcp data at position pos. pos=0 means start of
// tcp data. Returns the position at which the string after
// this string could be filled.
unsigned  int fill_tcp_data(unsigned char *buf,unsigned  int pos, const char *s)
	{
	// fill in tcp data at position pos
	//
	// with no options the data starts after the checksum + 2 more bytes (urgent ptr)
	while (*s) 
		{
	    buf[TCP_CHECKSUM_L_P+3+pos]=*s;
	    pos++;
	    s++;
		}
	return(pos);
	}

// Make just an ack packet with no tcp data inside
// This will modify the eth/ip/tcp header 
void make_tcp_ack_from_any(unsigned char *buf)
{
	unsigned  int j;
	make_eth(buf);
	// fill the header:
	buf[TCP_FLAGS_P]=TCP_FLAGS_ACK_V;
	if (info_data_len==0)
	{
	     // if there is no data then we must still acknoledge one packet
	    make_tcphead(buf,1,0,1); // no options
	}
	else
	{
	    make_tcphead(buf,info_data_len,0,1); // no options
	}
	
	// total length field in the IP header must be set:
	// 20 bytes IP + 20 bytes tcp (when no options) 
	j=IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN;
	buf[IP_TOTLEN_H_P]=j>>8;
	buf[IP_TOTLEN_L_P]=j& 0xff;
	make_ip(buf);
	// calculate the checksum, len=8 (start from ip.src) + TCP_HEADER_LEN_PLAIN + data len
	j=checksum(&buf[IP_SRC_P], 8+TCP_HEADER_LEN_PLAIN,2);
	buf[TCP_CHECKSUM_H_P]=j>>8;
	buf[TCP_CHECKSUM_L_P]=j& 0xff;

    printf("\n\r神舟III号[%d.%d.%d.%d]发送ACK包响应",ipaddr[0],ipaddr[1],ipaddr[2],ipaddr[3]);
    
	enc28j60PacketSend(IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN+ETH_HEADER_LEN,buf);
}

// you must have called init_len_info at some time before calling this function
// dlen is the amount of tcp data (http data) we send in this packet
// You can use this function only immediately after make_tcp_ack_from_any
// This is because this function will NOT modify the eth/ip/tcp header except for
// length and checksum
void make_tcp_ack_with_data(unsigned char *buf,unsigned  int dlen)
	{
	unsigned  int j;
	// fill the header:
	// This code requires that we send only one data packet
	// because we keep no state information. We must therefore set
	// the fin here:
	buf[TCP_FLAGS_P]=TCP_FLAGS_ACK_V|TCP_FLAGS_PUSH_V|TCP_FLAGS_FIN_V;
	
	// total length field in the IP header must be set:
	// 20 bytes IP + 20 bytes tcp (when no options) + len of data
	j=IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN+dlen;
	buf[IP_TOTLEN_H_P]=j>>8;
	buf[IP_TOTLEN_L_P]=j& 0xff;
	fill_ip_hdr_checksum(buf);
	// zero the checksum
	buf[TCP_CHECKSUM_H_P]=0;
	buf[TCP_CHECKSUM_L_P]=0;
	// calculate the checksum, len=8 (start from ip.src) + TCP_HEADER_LEN_PLAIN + data len
	j=checksum(&buf[IP_SRC_P], 8+TCP_HEADER_LEN_PLAIN+dlen,2);
	buf[TCP_CHECKSUM_H_P]=j>>8;
	buf[TCP_CHECKSUM_L_P]=j& 0xff;
	enc28j60PacketSend(IP_HEADER_LEN+TCP_HEADER_LEN_PLAIN+dlen+ETH_HEADER_LEN,buf);
	}

/* end of ip_arp_udp.c */
