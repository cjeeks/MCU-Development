/**-------------------------------------------------------------------------------------------
** Created by:          qinyx
** Last modified Date:  2014-02-28
** Last Version:        V1.00
** Descriptions:        STM32F407嵌入式实验箱
**	  Gpio配置文件
**
**-------------------------------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "Gpio.h"

Gpio_Info Gpio_info[LED_NUMBER]={
    {LED1_RCC,LED1_GPIO,LED1_GPIO_PIN},
    {LED2_RCC,LED2_GPIO,LED2_GPIO_PIN},
    {LED3_RCC,LED3_GPIO,LED3_GPIO_PIN},
    {LED4_RCC,LED4_GPIO,LED4_GPIO_PIN}
};

Gpio_Info Key_info[KEY_NUMBER] = {
    {KEY_S1_RCC,KEY_S1_GPIO,KEY_S1_GPIO_PIN},
    {KEY_S2_RCC,KEY_S2_GPIO,KEY_S2_GPIO_PIN},
    {KEY_S3_RCC,KEY_S3_GPIO,KEY_S3_GPIO_PIN},
    {KEY_S4_RCC,KEY_S4_GPIO,KEY_S4_GPIO_PIN},
    {KEY_S5_RCC,KEY_S5_GPIO,KEY_S5_GPIO_PIN}
};

/******************************************************************************************
*函数名称：void LEDGpio_Init(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：LED初始化
*******************************************************************************************/
void LEDGpio_Init(void)
{
    uint8_t i;
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    for(i=0;i<LED_NUMBER;i++)
    {
        RCC_AHB1PeriphClockCmd( Gpio_info[i].rcc , ENABLE); 
        GPIO_InitStructure.GPIO_Pin = Gpio_info[i].pin;
        GPIO_Init(Gpio_info[i].gpio, &GPIO_InitStructure);
        GPIO_WriteBit(Gpio_info[i].gpio,Gpio_info[i].pin,Bit_SET);
    }
}

/******************************************************************************************
*函数名称：void KEYGpio_Init(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：KEY初始化
*******************************************************************************************/
void KEYGpio_Init(void)
{
    uint8_t i;
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    for(i=0;i<KEY_NUMBER;i++)
    {
        RCC_AHB1PeriphClockCmd( Key_info[i].rcc , ENABLE); 
        GPIO_InitStructure.GPIO_Pin = Key_info[i].pin;
        GPIO_Init(Key_info[i].gpio, &GPIO_InitStructure);
    }
}



