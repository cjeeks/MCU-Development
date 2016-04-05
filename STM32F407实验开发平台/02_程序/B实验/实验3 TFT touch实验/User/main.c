/**-------------------------------------------------------------------------------------------
** Created by:          qinyx
** Last modified Date:  2014-02-28
** Last Version:        V1.00
** Descriptions:        STM32F407嵌入式实验箱
**	  Gpio配置文件
**
**-------------------------------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "math.h"
#include "stdio.h"
#include "SysTick.h"
#include "lcd.h"
#include "Touch.h"
#include "Uart.h"
//#include "font.h"
extern u8 gImage_fg[];

extern Pen_Holder Pen_Point;	/* 定义笔实体 */


void nvic_config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* NVIC configuration */
	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

int main(void)
{  int i;
    FlagStatus state;
    nvic_config();	    
    
    SysTick_Init();
    lcd_init();
    lcd_clear(Black);

	uart_init();
	printf("hello!welcome to F4...\r\n ");
	//480x272	
	//LCD_DrawPicture(0,0,160,320, gImage_fg);	  				//240和320为图片的高度和宽度

	lcd_clear(Black);
		LCD_DrawPicture(0,0,160,160, gImage_fg);	  				//240和320为图片的高度和宽度
 Delay(1000);
	Delay(500);
	lcd_clear(Green);
	LCD_DrawPicture(0,160,160,272, gImage_fg);	  				//240和320为图片的高度和宽度
	  Delay(1000);
	Delay(500);
		lcd_clear(Black);
		LCD_DrawPicture(200,0,360,160, gImage_fg);	  				//240和320为图片的高度和宽度
	  Delay(1000);
	Delay(500);
		lcd_clear(Red);
		LCD_DrawPicture(200,160,360,272, gImage_fg);	  				//240和320为图片的高度和宽度
	  Delay(1000);
	Delay(500);
	 lcd_clear(Black);
	Touch_Init();
	Refreshes_Screen();
    while(1)
	{
		if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
		{
			Pen_Int_Set(0);				//关闭中断
			do
			{
				Convert_Pos();
		LCD_DrawPicture(0,160,160,320, gImage_fg);	  				//240和320为图片的高度和宽度
				Pen_Point.Key_Sta=Key_Up;

				if(Pen_Point.X0>460&&Pen_Point.Y0<48)
				{
				     Refreshes_Screen();
				}
				else 
				{
					Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0); // 画图	                           
				}
			    state =  TP_IO_STATE;
			}while(state == RESET);                //如果PEN一直有效,则一直执行
			Pen_Int_Set(1);                //开启中断
		}
	}
}


 

