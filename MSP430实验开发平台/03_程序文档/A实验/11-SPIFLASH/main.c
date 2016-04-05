#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "spi.h"

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
  UCSCTL4   |= SELS__XT2CLK + SELM__XT2CLK                ; // SMCLK = MCLK = XT2
}


uchar data0[10]={0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa},data1[10];
uchar X=0,Y=0;
void main()
{
    Init_CLK();
    SPI_Init();
    //__enable_interrupt();
    SPIFLASH_WR_Enable;
    X=SPIFLASH_RD_Status1();
    Y=SPIFLASH_RD_Status2();
    SPIFLASH_RD_ID();
    SPIFLASH_WR_Enable;
    SPIFLASH_PPro(0x0010,data0,10);
    delay_us(34);//经过测试最少要33us的时间延时，否则读取的都是0xFF
    SPIFLASH_RD_DATA(0x0010,data1,10);
    while(1)
    {
        SPIFLASH_WR_Enable;
        X=SPIFLASH_RD_Status1();
    }
}