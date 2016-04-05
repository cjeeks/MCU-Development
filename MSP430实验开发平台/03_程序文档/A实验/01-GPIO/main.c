#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GPIO.h"
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


void main()
{
  Init_CLK();//初始化系统时钟
  Init_GPIO();//初始化按键，LED
  while(1)
  {
    //test qin 
   /* while(1)
   {
      LED1_ON;
       LED2_ON;
        LED3_ON;
        LED4_ON;
      delay_s(1);
      LED1_OFF;
      LED2_OFF;
      LED3_OFF;
      LED4_OFF;
      delay_s(1);
    
    }
    */
    
    //test over
    
    
    
    
    
    if(KEY2_IN==0)//当KEY2按下并被扫描到时，点亮LED1，延时1秒熄灭LED1
    {
      BUZZER_ON;
      LED1_ON;
      delay_s(1);
      BUZZER_OFF;
      LED1_OFF;
    }
    if(KEY3_IN==0)//当KEY3按下并被扫描到时，点亮LED2，延时1秒熄灭LED2
    {
      BUZZER_ON;
      LED2_ON;
      delay_s(1);
      BUZZER_OFF;
      LED2_OFF;
    }
    if(KEY4_IN==0)//当KEY4按下并被扫描到时，点亮LED3，延时1秒熄灭LED3
    {
      BUZZER_ON;
      LED3_ON;
      delay_s(1);
      BUZZER_OFF;
      LED3_OFF;
    }
    if(KEY5_IN==0)//当KEY5按下并被扫描到时，点亮LED4，延时1秒熄灭LED4
    {
      BUZZER_ON;
      LED4_ON;
      delay_s(1);
      BUZZER_OFF;
      LED4_OFF;
    }
    if(KEY1_IN==0)//当KEY1按下并被扫描到时，点亮LED1~LED4，延时1秒熄灭LED1~LED4
    {BUZZER_ON;LED1_ON;LED2_ON;LED3_ON;LED4_ON;delay_s(1);BUZZER_OFF;LED1_OFF;LED2_OFF;LED3_OFF;LED4_OFF;}
  }
}