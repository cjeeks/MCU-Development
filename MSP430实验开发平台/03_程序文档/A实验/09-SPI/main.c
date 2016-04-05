#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SPI.h"
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
unsigned char SD_sendbuffer[512];
unsigned char SD_Receivebuffer[512];

void main()
{
  unsigned int i=0;
  Init_CLK();//初始化系统时钟
  
  for(;i<512;i++)
  {
    if(i<256)SD_sendbuffer[i]=i;
    else SD_sendbuffer[i]=511-i;
  }
  
  SPI_Init();
  while(SD_Init()==false);
  
  SD_Block_W(SD_sendbuffer,0);
  SD_Block_R(SD_Receivebuffer,0);
  
  while(1)
  {
     __no_operation();
  }
}

