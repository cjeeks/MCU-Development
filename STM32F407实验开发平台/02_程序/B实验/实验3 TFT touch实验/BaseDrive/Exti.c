/******************************************************************
**	  红龙407开发板（V1.0）
**	  外部中断 配置文件
**
**	  论    坛：bbs.openmcu.com
**	  旺    宝：www.openmcu.com
**	  邮    箱：support@openmcu.com
**
**    版    本：V1.0
**	  作    者：FXL
**	  完成日期:	2012.12.28
********************************************************************/
#include "stm32f4xx.h"
#include "Gpio.h"
#include "Exti.h"

/******************************************************************************************
*函数名称：void ExtiLine0_IRQ(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：外部中断0处理函数
*******************************************************************************************/
void ExtiLine0_IRQ(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        if(GPIO_ReadOutputDataBit(LED1_GPIO,LED1_GPIO_PIN) == Bit_SET)     //判断灯的当前状态，然后对灯取反
            LED1_ONOFF(Bit_RESET);
        else
            LED1_ONOFF(Bit_SET);

        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

/******************************************************************************************
*函数名称：void ExtiLine6_IRQ(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：外部中断6处理函数
*******************************************************************************************/
void ExtiLine6_IRQ(void)
{
    if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        if(GPIO_ReadOutputDataBit(LED2_GPIO,LED2_GPIO_PIN) == Bit_SET)        //判断灯的当前状态，然后对灯取反
            LED2_ONOFF(Bit_RESET);
        else
            LED2_ONOFF(Bit_SET);

        EXTI_ClearITPendingBit(EXTI_Line6);
    }
}

/******************************************************************************************
*函数名称：void EXTILine0_Config(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：外部中断0初始化
*******************************************************************************************/
void EXTILine0_Config(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //使能IO时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;          //模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;          //设置上接
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;             //IO口为0
  GPIO_Init(GPIOA, &GPIO_InitStructure);                //如上配置gpio

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//实始化中断线0

  EXTI_InitStructure.EXTI_Line = EXTI_Line0;                   //配置中断线为中断线0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;          //配置中断模式
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;      //配置为下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                    //配置中断线使能
  EXTI_Init(&EXTI_InitStructure);                              

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;             
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************************
*函数名称：void EXTILine6_Config(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：外部中断6初始化
*******************************************************************************************/
void EXTILine6_Config(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource6);

  EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
}
