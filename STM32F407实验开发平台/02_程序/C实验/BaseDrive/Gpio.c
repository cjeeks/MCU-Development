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

Gpio_Info RELAY_info[RELAY_NUMBER]={
    {RELAY1_RCC,RELAY1_GPIO,RELAY1_GPIO_PIN},
    {RELAY2_RCC,RELAY2_GPIO,RELAY2_GPIO_PIN},
    {RELAY3_RCC,RELAY3_GPIO,RELAY3_GPIO_PIN}    
};

Gpio_Info Key_info[KEY_NUMBER] = {
    {KEY_S1_RCC,KEY_S1_GPIO,KEY_S1_GPIO_PIN},
    {KEY_S2_RCC,KEY_S2_GPIO,KEY_S2_GPIO_PIN},
    {KEY_S3_RCC,KEY_S3_GPIO,KEY_S3_GPIO_PIN},
    {KEY_S4_RCC,KEY_S4_GPIO,KEY_S4_GPIO_PIN},
    {KEY_S5_RCC,KEY_S5_GPIO,KEY_S5_GPIO_PIN}
};
Gpio_Info DP_info[DP_NUMBER]={
    {D_RCC,D_GPIO,D_GPIO_PIN},
    {C_RCC,C_GPIO,C_GPIO_PIN},
    {B_RCC,B_GPIO,B_GPIO_PIN},
    {A_RCC,A_GPIO,A_GPIO_PIN},
		{G_RCC,G_GPIO,G_GPIO_PIN},
    {DI_RCC,DI_GPIO,DI_GPIO_PIN},
    {DCLK_RCC,DCLK_GPIO,DCLK_GPIO_PIN},
    {LAT_RCC,LAT_GPIO,LAT_GPIO_PIN}
};
Gpio_Info TM1638_info[TM1638_NUMBER] = {
    {CLK_RCC,CLK_GPIO,CLK_GPIO_PIN},
    {STB_RCC,STB_GPIO,STB_GPIO_PIN}
};
Gpio_Info STEP_info[STEP_NUMBER]={
    {IN1_RCC,IN1_GPIO,IN1_GPIO_PIN},
    {IN2_RCC,IN2_GPIO,IN2_GPIO_PIN},
    {IN3_RCC,IN3_GPIO,IN3_GPIO_PIN},
    {IN4_RCC,IN4_GPIO,IN4_GPIO_PIN},
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
*函数名称：void RELAYGpio_Init(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：RELAY初始化
*******************************************************************************************/
void RELAYGpio_Init(void)
{
    uint8_t i;
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    for(i=0;i<RELAY_NUMBER;i++)
    {
        RCC_AHB1PeriphClockCmd( RELAY_info[i].rcc , ENABLE); 
        GPIO_InitStructure.GPIO_Pin = RELAY_info[i].pin;
        GPIO_Init(RELAY_info[i].gpio, &GPIO_InitStructure);
        GPIO_WriteBit(RELAY_info[i].gpio,RELAY_info[i].pin,Bit_SET);
    }
}
/******************************************************************************************
*函数名称：void DPGpio_Init(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：点阵初始化
*******************************************************************************************/
void DPGpio_Init(void)
{
    uint8_t i;
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    for(i=0;i<DP_NUMBER;i++)
    {
        RCC_AHB1PeriphClockCmd( DP_info[i].rcc , ENABLE); 
        GPIO_InitStructure.GPIO_Pin = DP_info[i].pin;
        GPIO_Init(DP_info[i].gpio, &GPIO_InitStructure);
        GPIO_WriteBit(DP_info[i].gpio,DP_info[i].pin,Bit_SET);
    }
}
/******************************************************************************************
*函数名称：void TM1638Gpio_Init(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：tm1638初始化
*******************************************************************************************/
void TM1638Gpio_Init(void)
{
    uint8_t i;
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    for(i=0;i<TM1638_NUMBER;i++)
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
/******************************************************************************************
*函数名称：void ABCD_port(u8 dat)
*
*入口参数：dat
*
*出口参数：无
*
*功能说明：修改ABCD的值
*******************************************************************************************/
void ABCD_port(u8 dat)
{
	if((dat&0x01)==0x00)
		A_ONOFF(Bit_RESET);
	else A_ONOFF(Bit_SET);
	
	if((dat&0x02)==0x00)
		B_ONOFF(Bit_RESET);
	else B_ONOFF(Bit_SET);
	
	if((dat&0x04)==0x00)
		C_ONOFF(Bit_RESET);
	else C_ONOFF(Bit_SET);
	
	if((dat&0x08)==0x00)
		D_ONOFF(Bit_RESET);
	else D_ONOFF(Bit_SET);
}
/******************************************************************************************
*函数名称：void DUJIN_port(u8 dat)
*
*入口参数：dat
*
*出口参数：无
*
*功能说明：修改步进电机的控制脚电平
*******************************************************************************************/
/*
void DUJIN_port(u8 dat)
{
	//unsigned char dat=0x09;
	
	if((dat&0x01)==0x00)
		IN4_ONOFF(Bit_RESET);
	else IN4_ONOFF(Bit_SET);
	
	if((dat&0x02)==0x00)
		IN3_ONOFF(Bit_RESET);
	else IN3_ONOFF(Bit_SET);
	
	if((dat&0x04)==0x00)
		IN2_ONOFF(Bit_RESET);
	else IN2_ONOFF(Bit_SET);
	
	if((dat&0x08)==0x00)
		IN1_ONOFF(Bit_RESET);
	else IN1_ONOFF(Bit_SET);	
}
*/

void DUJIN_port(u8 dat)
{
	//unsigned char dat=0x09;
		if((dat&0x08)==0x00)
		IN2_ONOFF(Bit_RESET);
	else IN2_ONOFF(Bit_SET);
		
		if((dat&0x04)==0x00)
		IN4_ONOFF(Bit_RESET);
	else IN4_ONOFF(Bit_SET);		
		
			if((dat&0x02)==0x00)
		IN3_ONOFF(Bit_RESET);
	else IN3_ONOFF(Bit_SET);
		
		if((dat&0x01)==0x00)
		IN1_ONOFF(Bit_RESET);
	else IN1_ONOFF(Bit_SET);
}


/******************************************************************************************
*函数名称：void DuojiGpio_Init(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：步进电机管脚初始化
*******************************************************************************************/
void DuojiGpio_Init(void)
{
    uint8_t i;
    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
    for(i=0;i<STEP_NUMBER;i++)
    {
        RCC_AHB1PeriphClockCmd( STEP_info[i].rcc , ENABLE); 
        GPIO_InitStructure.GPIO_Pin = STEP_info[i].pin;
        GPIO_Init(STEP_info[i].gpio, &GPIO_InitStructure);
        GPIO_WriteBit(STEP_info[i].gpio,STEP_info[i].pin,Bit_SET);
    }
}
