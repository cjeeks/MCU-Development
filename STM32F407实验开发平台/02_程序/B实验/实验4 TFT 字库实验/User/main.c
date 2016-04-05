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
//#include "sddriver.h"
//#include "ff.h"
//#include "w25q16.h"
//#include "tm1638.h"
#include "delay.h"



void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;        //定义GPIO初始化结构体
  RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  //允许GPIOB时钟
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);  //使能GPIOa外设模块时钟使能 ,PA6引脚复用为PWM模块
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9;; //配置PB13 PB14分别为TM1638 STB CLK引脚，配置成推挽输出
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}



int main(void)
{
  		u8 i,j;  
	SysTick_Init();
    lcd_init();
	/*--------显示汉字 从字库----------*/
  lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
  LCD_ShowString(150,30, "**  STM32F407实验开发平台 **", Red, Black);
	LCD_ShowString(60,60, " 实验1：串口测试实验 ", White, Black);		
	LCD_ShowString(60, 90, "本实验是串口测试实验", White, Black);	
  LCD_ShowString(60, 120, "1）操作步骤", White, Black);	
	LCD_ShowString(60, 150, "2）操作步骤", White, Black);	
	LCD_ShowString(30, 180, "实验结果：能在串口调试软件中看到串口信息\"hh\"", White, Black);	
	///////////////////////////////////////////////
	while(1);
}

