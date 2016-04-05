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


int main(void)
{
    SysTick_Init();
    lcd_init();

	while(1)
	{
		lcd_clear(Red);
		Delay(1000);
		lcd_clear(Green);
		Delay(1000);
		lcd_clear(Blue);
		Delay(1000);
		lcd_clear(White);
		Delay(1000);
		lcd_clear(Black);
		Delay(1000);
		lcd_clear(Yellow);
        Delay(1000);
	}
}

