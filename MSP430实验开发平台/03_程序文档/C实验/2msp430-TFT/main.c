#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "delay.h"
#include "TFT.h"

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
  unsigned char i;
  Init_CLK();
  LCD_Init();   //TFT初始化
  LCD_Clear(BLACK); //清屏
 /* LCD_Clear(RED);
  delay_s(1);
  LCD_Clear(GREEN);
  delay_s(2);
  LCD_Clear(BLUE);
  delay_s(2);
 
  
  //showimage(); */
  POINT_COLOR=GREEN;
  LCD_DrawRectangle(0,0, 479, 271);
  POINT_COLOR=BLUE;
  LCD_DrawRectangle(5,5, 474, 266);
   POINT_COLOR=RED;
  Draw_Circle(100,100,100);
  LCD_DrawPicture(0,0,160,160, gImage_fg);
  while(1)
  {
    POINT_COLOR=RED;
     for(i=100;i>0;i--)
  {
    Draw_Circle(100,100,i);
    Draw_Circle(100,200,i);
    Draw_Circle(200,200,i);
    Draw_Circle(300,100,i);
    Draw_Circle(300,200,i);
    delay_ms(50);
  }
  POINT_COLOR=BLACK;
       for(i=0;i<101;i++)
  {
    Draw_Circle(100,100,i);
    Draw_Circle(100,200,i);
    Draw_Circle(200,200,i);
    Draw_Circle(300,100,i);
    Draw_Circle(300,200,i);
    delay_ms(50);
  }
  }
}