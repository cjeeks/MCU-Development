#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "timer2.h"
#include "delay2.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  P5SEL     |= 0x0C                                       ; // 端口功能选择振荡器
  UCSCTL6   &= ~XT2OFF                                    ; // 振荡器使能
  UCSCTL3   |= SELREF_2                                   ; // FLLref = REFO
  UCSCTL4   |= SELA_2;//为何该句必不可少？？？？？？？？？？？？？？？？？？？
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 错误标志                                                          
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // 检测振荡器错误标志
  UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 驱动模式 24~32MHz                                            
  UCSCTL4   |= SELS_5 + SELM_5 + SELA_5                   ; // ACLK = SMCLK = MCLK = XT2
  UCSCTL5   |= DIVS2;                                     ; //SMCLK source divider,fACLK/16=1MHz
}

unsigned char count=0;

/************该工程实现TIMER的compare Output ：Toggle output mode 功能**********/

void main()
{
  Init_CLK();//初始化系统时钟
  Init_Timer0_A5();//初始化Timer0_A5
  Timer0_A5_Start();//启动定时器比较功能
  
  while(1)
  {
    __no_operation();
  }
}