#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "timer.h"
#include "delay.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  P5SEL     |= 0x0C                                       ; // 端口功能选择振荡器
  UCSCTL6   &= ~XT2OFF                                    ; // 振荡器使能
  UCSCTL3   |= SELREF_2                                   ; // FLLref = REFO
  UCSCTL4   |= SELA_2                                     ; // ACLK=REFO,SMCLK=DCO,MCLK=DCO
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 错误标志                                                          
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // 检测振荡器错误标志
  UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 驱动模式 24~32MHz                                            
  UCSCTL4   |= SELS_5 + SELM_5                            ; // SMCLK = MCLK = XT2
}

unsigned char count=0;

/************该工程实现TIMER的定时器up mode的功能**********/

void main()
{
  __disable_interrupt();//禁能全局中断
  Init_CLK();//初始化系统时钟
  P1DIR|=BIT4+BIT5+BIT6+BIT7;//LED1~LED4初始化配置为输出
  Init_Timer0_A5();//初始化Timer0_A5
  Timer0_A5_Start();//启动定时器工作
  __enable_interrupt();//使能全局中断
  while(1)
  {
     if(sign)//当1S定时到达，timer的中断程序置位sign
     {
       sign=0;//清零等待下一次1S延时中断函数执行时再置位sign
       count++;
       switch(count)
       {
         case 1:{P1OUT&=~BIT4;break;}//点亮LED1
         case 2:{P1OUT&=~BIT5;break;}//点亮LED2
         case 3:{P1OUT&=~BIT6;break;}//点亮LED3
         case 4:{P1OUT&=~BIT7;break;}//点亮LED4
         case 5:{P1OUT|=BIT4;break;}//熄灭LED1
         case 6:{P1OUT|=BIT5;break;}//熄灭LED2
         case 7:{P1OUT|=BIT6;break;}//熄灭LED3
         case 8:{P1OUT|=BIT7;count=0;break;}//熄灭LED4，同时清零count，这样就可以循环点亮熄灭LED灯了
         default:break;
       }
     }
  }
}