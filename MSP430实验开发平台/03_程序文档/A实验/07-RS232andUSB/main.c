#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RS232.h"
#include "delay.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  P5SEL     |= 0x0C                                       ; // 端口功能选择振荡器
  UCSCTL6   &= ~XT2OFF                                    ; // 振荡器使能
  UCSCTL3   |= SELREF_2                                   ; // FLLref = REFO
  UCSCTL4   |= SELA__REFOCLK                                     ; // ACLK=REFO,SMCLK=DCO,MCLK=DCO
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 错误标志                                                          
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // 检测振荡器错误标志
  UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 驱动模式 24~32MHz     
  UCSCTL4  = UCSCTL4-SELA__REFOCLK                     ;
  UCSCTL4   |= SELS_5 + SELM_5  + SELA__XT2CLK         ; // ACLK = SMCLK = MCLK = XT2
}

/**************该例程实现Watchdog Timer的Interval Timer Mode功能***************/

unsigned char RS1_RX;
unsigned char RS2_RX;
unsigned char USB_RX;

void main()
{
  __disable_interrupt();
  Init_CLK();//初始化系统时钟
  P1DIR|=0xe0;//LED1~LED3
  P1OUT|=0xe0;//LED1~LED3熄灭
  Init_USB();
  Init_RS232_1();
  Init_RS232_2();
  
  RS232_1_TX("this is RS232_1");
  RS2_RX=0;RS232_2_TX("this is RS232_2");
  USB_TX("this is USB");
  
  __enable_interrupt();
  while(1)
  {
    if(RS1_RX=='1'){RS1_RX=0;RS232_1_TX("this is RS232_1");}
    if(RS2_RX=='2'){RS2_RX=0;RS232_2_TX("this is RS232_2");}
    if(USB_RX=='u'){USB_RX=0;USB_TX("this is USB");}
  }
}

#pragma vector=USCI_A1_VECTOR    //RS232_2
__interrupt void USCI_A1_ISR(void)
{
  switch(UCA1IV)
  {
    case 0:break;               // Vector 0 - no interrupt
    case 2:                     // Vector 2 - RXIFG
      {
         RS2_RX=UCA1RXBUF;
         if(RS2_RX=='2')
           P1OUT&=~BIT7;
         else
           P1OUT|=BIT7;
         break;
      }
    case 4:break;               // Vector 4 - TXIFG
    default: break;  
  }
}

#pragma vector=USCI_A2_VECTOR    //USB
__interrupt void USCI_A2_ISR(void)
{
  switch(UCA2IV)
  {
    case 0:break;               // Vector 0 - no interrupt
    case 2:                     // Vector 2 - RXIFG
      {
         USB_RX=UCA2RXBUF;
         if(USB_RX=='u')
           P1OUT&=~BIT6;
         else
           P1OUT|=BIT6;
         break;
      }
    case 4:break;               // Vector 4 - TXIFG
    default: break;  
  }
}

#pragma vector=USCI_A3_VECTOR    //RS232_1
__interrupt void USCI_A3_ISR(void)
{
  switch(UCA3IV)
  {
    case 0:break;               // Vector 0 - no interrupt
    case 2:                     // Vector 2 - RXIFG
      {
         RS1_RX=UCA3RXBUF;
         if(RS1_RX=='1')
           P1OUT&=~BIT5;
         else
           P1OUT|=BIT5;
         break;
      }
    case 4:break;               // Vector 4 - TXIFG
    default: break;  
  }
}