//===========================================================================//
//                                                                           //
// 文件：  MAIN.C                                                            //
// 说明：  BW-DK5438开发板以太网UDP通讯示例程序                              //
//         通过ENC28J60扩展以太网接口，以UDP协议接收/发送数据                //
//         PC机通过以太网工具软件，以UDP协议向开发板发送数据                 //
//         当开发板接收到字符'w'时，应答"This is BW-DK5438"                  //
//         程序支持ping应答，用户可在PC上COMMAND方式下发送                   //
//         “ping 192.163.1.103”,检验此功能                                 //
// 注意：  PC端软件要将主机端/客户端网络端口都设置为8001                     //
//         开发板IP被设置为192.163.1.103，如有冲突，可修改                   //
// 编译：  IAR Embedded Workbench IDE for MSP430 v4.21                       //
// 版本：  v1.1                                                              //
// 编写：  JASON.ZHANG                                                       //
// 版权：  北京拓普博维电子技术有限公司                                      //
// 日期：  2010.09.25                                                        //
//                                                                           //
//===========================================================================//

#include "msp430x54x.h"
#include <stdlib.h>
#include <stdio.h>
#include "PIN_DEF.H"
#include "enc28j60.h"
#include "ip_arp_udp.h"
#include "timeout.h"
#include "net.h"

#define FLL_FACTOR   649
#define BUFFER_SIZE 250

static uint8_t mymac[6] = {0x54,0x55,0x58,0x10,0x00,0x24};
static uint8_t myip[4]  = {192,168,1,113}                ; // 开发板IP
static uint16_t myport  = 8001                           ; 
static uint8_t buf[BUFFER_SIZE+1]                        ;


//***************************************************************************//
//                                                                           //
//                 初始化主时钟: MCLK = XT1×(FLL_FACTOR+1)                  //
//                                                                           //
//***************************************************************************//
#if 0
void Init_CLK(void)
{
  P7SEL     |= 0x03                                  ; // 端口选择外部低频晶振XT1
  UCSCTL6   &=~XT1OFF                                ; // 使能外部晶振 
  UCSCTL6   |= XCAP_3                                ; // 设置内部负载电容
  UCSCTL3   |= SELREF_2                              ; // DCOref = REFO
  UCSCTL4   |= SELA_0                                ; // ACLK   = XT1  
  __bis_SR_register(SCG0)                            ; // 关闭FLL控制回路
  UCSCTL0    = 0x0000                                ; // 设置DCOx, MODx
  UCSCTL1    = DCORSEL_7                             ; // 设置DCO振荡范围
  UCSCTL2    = FLLD__1 + FLL_FACTOR                  ; // Fdco = ( FLL_FACTOR + 1)×FLLRef = (649 + 1) * 32768 = 21.2992MHz
  __bic_SR_register(SCG0)                            ; // 打开FLL控制回路                                                            
  __delay_cycles(1024000)                            ; 
  do
  {
    UCSCTL7 &=~(XT2OFFG+XT1LFOFFG+XT1HFOFFG+DCOFFG)  ; // 清除 XT2,XT1,DCO 错误标志                                                            
    SFRIFG1 &=~OFIFG                                 ; 
  }while(SFRIFG1&OFIFG)                              ; // 检测振荡器错误标志 
}
#endif

void Init_PSPI(void)
{  
  P3OUT    |=  TP_CS                                 ; // 关闭触摸屏
  P3DIR    |=  TP_CS                                 ;
  P5OUT    |=  J60_CS                                ;
  P5DIR    |=  J60_CS                                ;
  P10DIR   &= ~PMISO                                 ;
  P10REN   |=  PMISO                                 ;
  P10DIR   |=  PMOSI+PSCK                            ;
  P10OUT   &=~(PMOSI+PSCK)                           ;
}

extern int net_main(void);
int net_main(void)
{
  uint16_t plen                                      ;
//  uint8_t payloadlen=0                               ;
//  WDTCTL   = WDTPW + WDTHOLD                         ;
//  Init_CLK()                                         ;
  Init_PSPI()                                        ; 
  P9DIR   |= IrDA_OUT                                ;
  P9OUT   &=~IrDA_OUT                                ;  
  MAIN_POWER_ON                                      ;
  __delay_cycles(5000000)                            ;                
  enc28j60Init(mymac)                                ;
  delay_ms(20)                                       ;
        
        /* Magjack leds configuration, see enc28j60 datasheet, page 11 */
        // LEDB=yellow LEDA=green
        //
        // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
        // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
  enc28j60PhyWrite(PHLCON,0x476);
  delay_ms(20);
  init_ip_arp_udp(mymac,myip);//init the ethernet/ip layer:
        while(1){
                // get the next new packet:
                plen = enc28j60PacketReceive(BUFFER_SIZE, buf);

                /*plen will ne unequal to zero if there is a valid 
                 * packet (without crc error) */
                if(plen==0){
                        continue;
                }
                // arp is broadcast if unknown but a host may also
                // verify the mac address by sending it to 
                // a unicast address.
                if(eth_type_is_arp_and_my_ip(buf,plen)){
                        make_arp_answer_from_request(buf,plen);
                        continue;
                }
                // check if ip packets (icmp or udp) are for us:
                if(eth_type_is_ip_and_my_ip(buf,plen)==0){
                        continue;
                }                
                        
                if(buf[IP_PROTO_P]==IP_PROTO_ICMP_V && buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V){
                        // a ping packet, let's send pong
                        make_echo_reply_from_request(buf,plen);
                        continue;
                }
         //       if (buf[IP_PROTO_P]==IP_PROTO_UDP_V){
                if (buf[23]==IP_PROTO_UDP_V)
                {
//                  payloadlen=buf[UDP_LEN_L_P]-UDP_HEADER_LEN;
                  if (buf[UDP_DATA_P]=='w')
                        {
                          make_udp_reply_from_request(buf,"This is BW-DK5438",17,myport);
                        }
                }
        }
}
