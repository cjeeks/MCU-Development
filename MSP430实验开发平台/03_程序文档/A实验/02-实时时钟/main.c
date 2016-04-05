#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RTC.h"
#include "delay.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  P5SEL     |= 0x0C                                       ; // 端口功能选择振荡器
  UCSCTL6   &= ~XT2OFF                                    ; // 振荡器使能
  UCSCTL3   |= SELREF_2                                   ; // FLLref = REFO
  UCSCTL4   |= SELA_2                                     ; // ACLK=REFO,SMCLK=DCO,MCLK=DCO
  //REFOCLK: Internal, trimmed, low frequency oscillator with 32768 Hz typical frequency, with the ability 
  //to be used as a clock reference into the FLL.
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 错误标志                                                          
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // 检测振荡器错误标志
  UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 驱动模式 24~32MHz                                            
  UCSCTL4   |= SELS_5 + SELM_5                            ; // SMCLK = MCLK = XT2
}

/**************该例程实现RTC的Calendar功能，采用轮训的方式读写RTC寄存器***************/

CALENDAR_n CalendarSET={0x2014,0x07,0x08,0x02,0x18,0x30,0x00};
CALENDAR_n CalendarGET[2];

void main()
{
  //__disable_interrupt();
  Init_CLK();//初始化系统时钟
  Init_RTC_Calendar();
  //__enable_interrupt();
  
  CalendarGET[0] = GetTime();
  delay_s(10);
  SET_Time(CalendarSET);
  delay_s(10);
  CalendarGET[1] = GetTime();
  delay_s(1);
}

