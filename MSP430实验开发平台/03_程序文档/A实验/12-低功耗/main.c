#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lowpower.h"
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

/**************该例程实现Watchdog Timer的Interval Timer Mode功能***************/

/******在msp430f5438a.h头文件中已经给出了进入低功耗和退出低功耗的宏定义*********
#include "in430.h"

#define LPM0      _BIS_SR(LPM0_bits)      //Enter Low Power Mode 0 
#define LPM0_EXIT _BIC_SR_IRQ(LPM0_bits)  //Exit Low Power Mode 0 
#define LPM1      _BIS_SR(LPM1_bits)      // Enter Low Power Mode 1 
#define LPM1_EXIT _BIC_SR_IRQ(LPM1_bits)  // Exit Low Power Mode 1 
#define LPM2      _BIS_SR(LPM2_bits)      // Enter Low Power Mode 2 
#define LPM2_EXIT _BIC_SR_IRQ(LPM2_bits)  // Exit Low Power Mode 2 
#define LPM3      _BIS_SR(LPM3_bits)      // Enter Low Power Mode 3 
#define LPM3_EXIT _BIC_SR_IRQ(LPM3_bits)  // Exit Low Power Mode 3 
#define LPM4      _BIS_SR(LPM4_bits)      // Enter Low Power Mode 4 
#define LPM4_EXIT _BIC_SR_IRQ(LPM4_bits)  // Exit Low Power Mode 4 
#endif // End #defines for C 

********************************************************************************/

void main()
{
  __disable_interrupt();
  Init_CLK();//初始化系统时钟
  P1DIR|=0xf0;//LED1~LED4
  P1OUT|=0xf0;//LED1~LED4熄灭
  Init_RTC();
  __enable_interrupt();
  
  while(1)
  {
    P1OUT&=~BIT4;
    __low_power_mode_0();
    //MCLK=disable,ACLK=SMCLK=FLL(from DCO)=DCO(from ACLK/SMCLK/MCLK)=enable(SMCLKOFF = 0)
    //CPUOFF=1，OSCOFF=0，GIE=1，SCG0=0，SCG1=0
    P1OUT&=~BIT5;
    __low_power_mode_1();
    //MCLK=FLL=disable,ACLK=SMCLK=DCO(from ACLK/SMCLK)=enable(SMCLKOFF = 0)
    //CPUOFF=1，OSCOFF=0，GIE=1，SCG0=1，SCG1=0
    P1OUT&=~BIT6;
    __low_power_mode_2();
    //MCLK=SMCLK=FLL=disable,ACLK=DCO(from ACLK)=enable(SMCLKOFF = 0)
    //CPUOFF=1，OSCOFF=0，GIE=1，SCG0=0，SCG1=1
    P1OUT&=~BIT7;
    __low_power_mode_3();
    //MCLK=SMCLK=FLL=disable,ACLK=DCO(from ACLK)=enable(SMCLKOFF = 0)
    //CPUOFF=1，OSCOFF=0，GIE=1，SCG0=1，SCG1=1
    P1OUT|=0xf0;
    __low_power_mode_4();
    //MCLK=ACLK=SMCLK=FLL=DCO=disable
    //CPUOFF=1，OSCOFF=1，GIE=1，SCG0=1，SCG1=1
  }
}

#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)//2S的延时
{
  RTCCTL01&=~RTCTEVIFG;//清中断标志位
  __low_power_mode_off_on_exit();//清除SR寄存器的：CPUOFF=0，OSCOFF=0，GIE=0，SCG0=0，SCG1=0,退出低功耗的同时清零全局中断使能位
  __enable_interrupt();//打开全局中断 GIE=1
}