#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "watchdog1.h"
#include "delay1.h"

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

/**************该例程实现Watchdog Timer的Interval Timer Mode功能***************/

void main()
{
  Init_CLK();//初始化系统时钟
  P1DIR|=0xC0;//LED4、LED3
  P1OUT|=0xC0;
  WatchDog_init1();
  unsigned char i=0;
  while(1)
  {   
      P1OUT&=~BIT6;//点亮LED3
      for(i=0;i<5;i++)
      {
          delay_ms(500);
          WDT_CLEAR;//喂狗
          P1OUT&=~BIT7;//点亮LED4
          delay_ms(500);
          WDT_CLEAR;//喂狗
          P1OUT|=BIT7;//熄灭LED4
      }
      delay_ms(520);
      P1OUT&=~BIT7;//点亮LED4
  }
}

