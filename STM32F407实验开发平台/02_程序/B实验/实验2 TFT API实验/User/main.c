/****************************************Copyright (c)***************************************
/**-------------------------------------------------------------------------------------------
** Created by:          qinyx
** Last modified Date:  2014-02-28
** Last Version:        V1.00
** Descriptions:        STM32F407嵌入式实验箱
**-------------------------------------------------------------------------------------------*/
//********************************************************************************************/
#include "stm32f4xx.h"
#include "SysTick.h"
#include "lcd.h"
#include "Gpio.h"

extern u8 gImage_fg[];

int main(void)
{
    SysTick_Init();
    lcd_init();   											/*系统初始化*/
												/* LCD初始化 */
		LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(60, 18, "****屏_API测试****", Red, Black);  	/* 显示字符串 */
	LCD_Fill(10, 40, 100, 100, Red);						   	/* 红色填充   */
	LCD_Fill(30, 60, 120, 120, Blue);

    LCD_DrawLine(0, 0, 180, 120, Red);							/*  画线     */
    Draw_Circle(180, 120, 30, Blue);							/*  画园     */
    LCD_DrawRectangle(180, 120, 238, 180, Green);				/*  画矩形   */
/////////////////////////////////////////

	////////////////////////////////////

	LCD_DrawPicture(100,160,260,320, gImage_fg);	  				//240和320为图片的高度和宽度
	while(1);
}

