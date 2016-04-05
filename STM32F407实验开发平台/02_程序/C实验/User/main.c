/****************************************Copyright (c)***************************************
/**-------------------------------------------------------------------------------------------
** Created by:          qinyx
** Last modified Date:  2014-02-28
** Last Version:        V1.00
** Descriptions:        STM32F407嵌入式实验箱
**-------------------------------------------------------------------------------------------*/
//********************************************************************************************/
#include "stm32f4xx.h"
#include "stdio.h"
#include "uart.h"
#include "SysTick.h"
#include "lcd.h"
#include "Gpio.h"
//#include "stm32f10x.h"
#include "tm1638.h"
#include "MMA7455.h"
#include "BMP085.h"

#define ADC3_DR_ADDRESS    ((uint32_t)0x4001224C)

__IO uint16_t ADC3ConvertedValue = 0;
__IO uint32_t ADC3ConvertedVoltage = 0;
 u8 ADC_volt[17]={"Now,AD is [0000]."};

//	u8 F_Rotation[4]={0x03,0x09,0x0c,0x06};//正转表格
u8 F_Rotation[8]={0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09};		//
unsigned char const tab[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};//数码管0到F的显示
													//  01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f
//unsigned char const keytab[]={01,02,16,15,17,18,00,00,03,04,14,13,19,20,00,00,05,06,12,11,21,22,00,00,07,08,10,09,23,24,00};
	unsigned char const keytab[]={0x01,0x02,0x10,0x0f,0x11,0x12,0x00,0x00,0x03,0x04,0x0e,0x0d,0x13,0x14,0x00,0x00,0x05,0x06,0x0c,0x0b,0x15,0x16,0x00,0x00,0x07,0x08,0x0a,0x09,0x17,0x18,00};														
u8 key_tmp=0xff;
const unsigned char ziku_table[]={
	
0xFF,0xF7,0x80,0xF5,0xEB,0xF5,0xEB,0xC1,0x80,0xF5,0xAA,0xF6,0xAA,0xF7,0xAA,0x80,
0x8A,0xFF,0xBC,0xFF,0xBE,0xC1,0x80,0xDD,0xBE,0xDD,0xBE,0xDD,0x80,0xC1,0xBE,0xDD,/*"?",0*/



0xFF,0xFF,0xFB,0x7F,0x1B,0x7E,0xDB,0x7E,0xDB,0xBE,0xDB,0xBE,0x00,0xD0,0xDB,0xEE,
0xDB,0xD6,0xDB,0xBA,0x1B,0x7E,0xFB,0x7F,0xF8,0xFF,0x07,0x00,0x9F,0xFF,0x7F,0xFF,/*"?",2*/

0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x80,0xDD,0x7D,0xDD,0xBD,0xDD,0xFD,0xDD,0xFD,
0x01,0x80,0xDD,0xFD,0xDD,0xFD,0xDD,0xFD,0xDD,0xFD,0x01,0xE0,0xFF,0x9F,0xFF,0x7F,/*"?",3*/

0xFF,0xFF,0xC7,0xE3,0xF7,0xDD,0xF7,0xDE,0xF7,0xDE,0x77,0xDF,0x8F,0xC7,0xFF,0xFF,/*"S",4*/

0xFF,0xFF,0xE7,0xFF,0xF7,0xFF,0xF7,0xDF,0x07,0xC0,0xF7,0xDF,0xF7,0xFF,0xE7,0xFF,/*"T",5*/

0xFF,0xFF,0xF7,0xDF,0x07,0xC0,0x07,0xFF,0xFF,0xC0,0x07,0xFF,0x07,0xC0,0xF7,0xDF,/*"M",6*/

0xFF,0xFF,0xCF,0xF1,0xB7,0xEE,0x77,0xDF,0x77,0xDF,0xF7,0xDF,0xCF,0xE7,0xFF,0xFF,/*"3",7*/

0xFF,0xFF,0x8F,0xCF,0x77,0xDE,0xF7,0xDD,0xF7,0xDB,0xF7,0xD7,0x8F,0xCF,0xFF,0xFF,/*"2",8*/

0xFF,0xFF,0xEF,0xFF,0xF7,0xFF,0x17,0xFC,0x77,0xFF,0x77,0xDF,0x07,0xC0,0xF7,0xDF,/*"F",9*/

0xFF,0xFF,0xFF,0xDB,0x07,0xC0,0xEF,0xDB,0xDF,0xDB,0x3F,0xFB,0xFF,0xF8,0xFF,0xFF,/*"4",10*/

0xFF,0xFF,0x1F,0xF0,0xEF,0xEF,0xF7,0xDF,0xF7,0xDF,0xEF,0xEF,0x1F,0xF0,0xFF,0xFF,/*"0",11*/

0xFF,0xFF,0xF7,0xFF,0xC7,0xFF,0x37,0xFF,0xF7,0xC0,0xF7,0xFF,0xC7,0xFF,0xFF,0xFF,/*"7",12*/

0xFF,0xFF,0x3F,0x7F,0xBF,0xBE,0xB1,0xCF,0xB7,0xF0,0x87,0xCF,0x77,0xBF,0xF7,0x7E,
0x70,0xFF,0x17,0x80,0x77,0xDB,0x77,0xDB,0x77,0xDB,0x11,0x80,0x7F,0xFF,0x7F,0xFF,/*"?",13*/

0xFF,0xFF,0xFF,0x7F,0xFF,0x7F,0xFF,0xBF,0xFF,0xCF,0xFF,0xF3,0xFF,0xFC,0x1F,0xFF,
0xE3,0xFF,0x1D,0xFF,0xFE,0xFC,0xFF,0xF3,0xFF,0xEF,0xFF,0xDF,0xFF,0xBF,0xFF,0x7F,/*"?",14*/

0xFF,0xFF,0xEF,0x07,0xE9,0xBF,0xEE,0xDF,0xEF,0xEF,0xEF,0xF3,0x00,0xFC,0xEF,0xFF,
0xEF,0xEF,0x6F,0xEF,0x6F,0xEF,0x6F,0xC0,0x6F,0xDF,0x6F,0x9F,0xEF,0xDF,0xEF,0xFF,/*"?",15*/

0xFF,0xFF,0x7F,0xFF,0x7D,0xFF,0x7D,0xFF,0x7D,0xFF,0x01,0x00,0x7D,0xFF,0x7D,0xFF,
0x7D,0xFF,0x7D,0xFF,0x7D,0xFF,0x01,0xF0,0x7D,0xCF,0x7D,0xBF,0x7D,0x7F,0x7F,0xFF,/*"?",16*/

0xFF,0xFF,0xFF,0x7F,0xEF,0x7F,0x6B,0xBC,0x6D,0xBB,0x6F,0xD7,0x6F,0xEF,0x6F,0xD7,
0x68,0xB9,0x47,0xBE,0x2F,0x7F,0xEF,0x7C,0xE9,0x73,0xE7,0xEF,0xFF,0xDF,0xFF,0xFF,/*"?",17*/

0xFF,0xFF,0xFF,0xFE,0xFD,0xFE,0xFD,0xFE,0xCD,0xFE,0xBD,0xFE,0xFD,0xFE,0xFD,0xFE,
0x01,0x00,0xFD,0xFE,0xFD,0xFE,0x9D,0xFE,0xED,0xFE,0xFD,0xFE,0xFD,0xFE,0xFF,0xFE,/*"?",18*/

0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0x9F,0xFF,0xAF,0x01,0xB7,0xBD,0xBF,0xBD,0xBF,0xBD,
0xBF,0xBD,0xBC,0xBD,0xBB,0xBD,0xB7,0xBD,0xAF,0x01,0x1F,0xFF,0xBF,0xFF,0xFF,0xFF,/*"?",19*/


};


//char Date_Buf[11];
/****************************************************************************
* 名    称：void Menu_RFIDTest(void)
* 功    能：显示主菜单
* 入口参数：无
* 出口参数：无
* 说    明：在LCD上显示DHT11的测试菜单
* 调用方法：Menu_RFIDTest();
****************************************************************************/
void Menu_RFIDTest(void)
{  u8 j,i,t;
	unsigned long temp;
	//LCD_ShowString(150, 60, "备注：按任意按键进入例程测试界面", Red, Black);	
	//while(Read_key()!=0x07)
		Send_Com();

	
///结束后的处理
	
}



void STEP_delay_1ms(uint8_t x)
{
    u8 j,t;
    while(x--){
        for(j=0;j<190;j++)
			    for(t=0;t<180;t++)
            {;}
        }   
}
void delay_1ms(uint32_t x)
{
    u8 j;
    while(x--){
        for(j=0;j<125;j++)
            {;}
        }   
}


void HUMEN_IN()  //PD13
{   GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD , ENABLE); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void GAS_IN()  //PG2
{   GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOG , ENABLE); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

}


/****************************************************************************
* 名    称：void RELAYTest(void)
* 功    能：显示主菜单
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：RELAYTest();
****************************************************************************/
void RELAYTest(void)
{  	u8 j,i,t;
		RELAYGpio_Init();                  //GPIO管脚初始化
		RELAY1_ONOFF(SET);
		RELAY2_ONOFF(SET);
		RELAY3_ONOFF(SET);

    Delay(1000);		
		RELAY1_ONOFF(RESET);
		Delay(1000);
		RELAY2_ONOFF(RESET);
		Delay(1000);
		RELAY3_ONOFF(RESET);
		Delay(1000);
		RELAY1_ONOFF(SET);
		RELAY2_ONOFF(SET);
		RELAY3_ONOFF(SET);
		Delay(1000);
}
/****************************************************************************
* 名    称：void LEDTest(void)
* 功    能：显示主菜单
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：LEDTest();
****************************************************************************/
void LEDTest(void)
{  	u8 j,i,t;
		LEDGpio_Init();                  //GPIO管脚初始化
		LED1_ONOFF(SET);
		LED2_ONOFF(SET);
		LED3_ONOFF(SET);
		LED4_ONOFF(SET);
    Delay(1000);		
		LED1_ONOFF(RESET);
		Delay(1000);
		LED2_ONOFF(RESET);
		Delay(1000);
		LED3_ONOFF(RESET);
		Delay(1000);
		LED4_ONOFF(RESET);
		Delay(1000);
		LED1_ONOFF(SET);
		LED2_ONOFF(SET);
		LED3_ONOFF(SET);
		LED4_ONOFF(SET);
}
//////////////////////////////////////
/****************************************************************************
* 名    称：void TM1638Test(void)
* 功    能：显示主菜单
* 入口参数：无
* 出口参数：无
* 说    明：在LCD上显示8LED测试菜单
* 调用方法：TM1638Test();
****************************************************************************/

void TM1638Test(void)
{
	u8 i,j;
	u8 keyDat;
	u8 tempcount=0;
	u8 temp_key1=0x00;
	u8 temp_key2=0x00;
	u8 temp_key3=0x00;
	init_TM1638();
	for(i=0;i<16;i++)
	{
	  for(j=0;j<8;j++)
	  Write_DATA(j<<1,tab[i]); 
	  Delay(100);
	}

	for(j=0;j<8;j++)
	  Write_DATA(j<<1,tab[0]); 
	
	for(i=0;i<16;i++)
	{ i++;
	  for(j=0;j<3;j++)
		{
		Write_oneLED(i,j);
	  Delay(100);
		}
	}
	
	//while(tempcount<24)
	//while(1)
	temp_key1=0x00;
	temp_key2=0x00;
	temp_key3=0x00;
	while((temp_key1!=0xff)||(temp_key2!=0xff)||(temp_key3!=0xff))
	{
		keyDat=Read_key();
		keyDat=keytab[keyDat-1];
		if(keyDat<0x1f)
		{   	printf("%c\n",keyDat);
					//for(j=0;j<8;j++)
	  //Write_DATA(8,tab[keyDat&0x0f]);
		//	Write_DATA(6,tab[(keyDat&0xf0)>>4]);
			Write_DATA(7<<1,tab[keyDat&0x0f]);
			Write_DATA(6<<1,tab[(keyDat&0xf0)>>4]);
			if(keyDat!=key_tmp)
			{
			//tempcount++;
				key_tmp=keyDat;
			}
			switch (keyDat){
				case 0x01:
				LCD_ShowString(120, 120, "KEY_ID:KEY01", White, Black);
				temp_key1=temp_key1|0x01;
				break;
				case 0x02:
				LCD_ShowString(120, 120, "KEY_ID:KEY02", White, Black);
				temp_key1=temp_key1|0x02;
				break;
				case 0x03:
				LCD_ShowString(120, 120, "KEY_ID:KEY03", White, Black);
				temp_key1=temp_key1|0x04;
				break;
				case 0x04:
				LCD_ShowString(120, 120, "KEY_ID:KEY04", White, Black);
				temp_key1=temp_key1|0x08;
				break;
				case 0x05:
				LCD_ShowString(120, 120, "KEY_ID:KEY05", White, Black);
				temp_key1=temp_key1|0x10;
				break;
				case 0x06:
				LCD_ShowString(120, 120, "KEY_ID:KEY06", White, Black);
				temp_key1=temp_key1|0x20;
				break;
				case 0x07:
				LCD_ShowString(120, 120, "KEY_ID:KEY07", White, Black);
				temp_key1=temp_key1|0x40;
				break;
				case 0x08:
				LCD_ShowString(120, 120, "KEY_ID:KEY08", White, Black);
				temp_key1=temp_key1|0x80;
				break;
				//
				case 0x09:
				LCD_ShowString(120, 120, "KEY_ID:KEY09", White, Black);
				temp_key2=temp_key2|0x01;
				break;
				case 0x0a:
				LCD_ShowString(120, 120, "KEY_ID:KEY0A", White, Black);
				temp_key2=temp_key2|0x02;
				break;
				case 0x0b:
				LCD_ShowString(120, 120, "KEY_ID:KEY0B", White, Black);
				temp_key2=temp_key2|0x04;
				break;
				case 0x0c:
				LCD_ShowString(120, 120, "KEY_ID:KEY0C", White, Black);
				temp_key2=temp_key2|0x08;
				break;
				case 0x0d:
				LCD_ShowString(120, 120, "KEY_ID:KEY0D", White, Black);
				temp_key2=temp_key2|0x10;
				break;
				case 0x0e:
				LCD_ShowString(120, 120, "KEY_ID:KEY0E", White, Black);
				temp_key2=temp_key2|0x20;
				break;
				case 0x0f:
				LCD_ShowString(120, 120, "KEY_ID:KEY0F", White, Black);
				temp_key2=temp_key2|0x40;
				break;
				case 16:
				LCD_ShowString(120, 120, "KEY_ID:KEY10", White, Black);
				temp_key2=temp_key2|0x80;
				break;
			//
				case 0x11:
				LCD_ShowString(120, 120, "KEY_ID:KEY11", White, Black);
				temp_key3=temp_key3|0x01;
				break;
				case 0x12:
				LCD_ShowString(120, 120, "KEY_ID:KEY12", White, Black);
				temp_key3=temp_key3|0x02;
				break;
				case 0x13:
				LCD_ShowString(120, 120, "KEY_ID:KEY13", White, Black);
				temp_key3=temp_key3|0x04;
				break;
				case 0x14:
				LCD_ShowString(120, 120, "KEY_ID:KEY14", White, Black);
				temp_key3=temp_key3|0x08;
				break;
				case 0x15:
				LCD_ShowString(120, 120, "KEY_ID:KEY15", White, Black);
				temp_key3=temp_key3|0x10;
				break;
				case 0x16:
				LCD_ShowString(120, 120, "KEY_ID:KEY16", White, Black);
				temp_key3=temp_key3|0x20;
				break;
				case 0x17:
				LCD_ShowString(120, 120, "KEY_ID:KEY17", White, Black);
				temp_key3=temp_key3|0x40;
				break;
				case 0x18:
				LCD_ShowString(120, 120, "KEY_ID:KEY18", White, Black);
				temp_key3=temp_key3|0x80;
				break;
				
								
				default:
				break;
			}
}
}
}


/**
  * @brief  ADC3 channel06 with DMA configuration
  * @param  None
  * @retval None
  */
/*
void ADC3_CH5_DMA_Config(void)
{
    ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    DMA_InitTypeDef       DMA_InitStructure;
    GPIO_InitTypeDef      GPIO_InitStructure;
    
    // Enable ADC3, DMA2 and GPIO clocks 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    
    /// DMA2 Stream0 channel2 configuration 
    DMA_InitStructure.DMA_Channel = DMA_Channel_2;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream0, ENABLE);
    
    /// Configure ADC3 Channel6 pin as analog input 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    
    /// ADC Common Init 
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);
    
    /// ADC3 Init 
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC3, &ADC_InitStructure);
    
    /// ADC3 regular channel6 configuration 
    ADC_RegularChannelConfig(ADC3, ADC_Channel_5, 1, ADC_SampleTime_3Cycles);
    
    /// Enable DMA request after last transfer (Single-ADC mode) ///
    ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);
    
    /// Enable ADC3 DMA ///
    ADC_DMACmd(ADC3, ENABLE);
    
    /// Enable ADC3 ///
    ADC_Cmd(ADC3, ENABLE);
}*/
/****************************************************************************
* 名    称：void Menu_DCMOTORTest(void)
* 功    能：显示主菜单
* 入口参数：无
* 出口参数：无
* 说    明：在LCD上显示8LED测试菜单
* 调用方法：Menu_DCMOTORTest();
****************************************************************************/
void Menu_DCMOTORTest(void)
{  u8 j,i,t;
	 u8 keytemp;
	 u8 motor_number;
	 u8 motor_n[3];
	//dc motor 
   GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
   GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
   GPIO_Init(GPIOE, &GPIO_InitStructure);

	
	printf("Now,DC MOTOR test!\r\n");  
 

		GPIO_WriteBit(GPIOC,GPIO_Pin_13,SET);	

		Delay(1000);	
		Delay(1000);
		Delay(1000);

		GPIO_WriteBit(GPIOC,GPIO_Pin_13,RESET);


	


	
}
void nvic_config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	/* NVIC configuration */
	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
				
	//Enable the USART1 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
			//Enable the USART6 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}


int main(void)
{ 
	u8 keyDat,tempf;
	u8  i,j;
	//u8 i;
	u8 data_buff;
	u8 hanzi;
//	u8 han;
	u8 shift=1;

	SysTick_Init();
	nvic_config();
	
	uart1_init();    	//GSM	
	uart3_init();			//DEBUG
	uart6_init();			//RFID

  DPGpio_Init();
	DuojiGpio_Init();  
  
	DUJIN_port(0X00);//关步进电机
	LAT_ONOFF(Bit_RESET);
	CLK_ONOFF(Bit_RESET);

	G_ONOFF(Bit_SET);//EN_port = 1;    //关屏显示，原理为使HC138输出全为1，从而三极管截止，点阵不显示
	printf("Start test!");
	//第一步测试
	lcd_init();


	lcd_clear(Black);

	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	

	LCD_ShowString(150,60, " 第一步:核心板按键和GSM测试", White, Black);	
	LCD_ShowString(150, 180, "现象：按K2发送AT指令", Red, Black); 
	LCD_ShowString(150, 200, "现象：依次按核心板中的按键除复位键外", Red, Black); 

	init_TM1638();
	KEYGpio_Init();//按键IO口初始化
	LEDGpio_Init(); //初始化LED
#if 1	
	keyDat=0;
	while(keyDat!=0x1f)
	{
		if(KEY_S1_UPDOWM()==Bit_RESET)
		{
			LED1_ONOFF(RESET);
			while(KEY_S1_UPDOWM()==Bit_RESET);
			keyDat =keyDat|0x01;
		}
		if(KEY_S2_UPDOWM()==Bit_RESET)
		{
			LED2_ONOFF(RESET);
							USART1_Send("AT\r\n",4);
			while(KEY_S2_UPDOWM()==Bit_RESET);
			keyDat =keyDat|0x02;
		}
		if(KEY_S3_UPDOWM()==Bit_RESET)
		{
			LED3_ONOFF(RESET);
			while(KEY_S3_UPDOWM()==Bit_RESET);
			keyDat =keyDat|0x04;
		}
		if(KEY_S4_UPDOWM()==Bit_RESET)
		{
			LED4_ONOFF(RESET);
			while(KEY_S4_UPDOWM()==Bit_RESET);
			keyDat =keyDat|0x08;
		}
		if(KEY_S5_UPDOWM()==Bit_RESET)
		{
			LED4_ONOFF(SET);
			while(KEY_S5_UPDOWM()==Bit_RESET);
			keyDat =keyDat|0x10;
		}
	
	}
	LED1_ONOFF(SET);
	LED2_ONOFF(SET);
	LED3_ONOFF(SET);
	LED4_ONOFF(SET);
	keyDat=0;
	//核心板按键和LED测试完成
	//第二步测试
	DPGpio_Init();
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(150,60, " 第二步:继电器测试", White, Black);	
	LCD_ShowString(150, 200, "现象：看继电器的现象", Red, Black); 
	RELAYTest();
  //继电器测试完成
	//第三步测试	
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(150,60, " 第三步:温湿度传感器测试", White, Black);	
	LCD_ShowString(150, 200, "现象：看屏幕显示的温度湿度的信息", Red, Black); 	
	LCD_ShowString(150, 220, "提示：按K1退出", Red, Black); 
		while((KEY_S1_UPDOWM()!=Bit_RESET))
	{
		DTH11_RH();
		Send_DTH11();
	}
	Delay(1000);
	//温湿度测试完成
/*	 DATA_Diplay();
	 if(tempf!=0x05)
	{
		LCD_ShowString(150, 120, "No acceleration!", White, Black); 
	}
	else
	{
		LCD_ShowString(150, 120, "MMA7455A test OK!", White, Black); 
	}
	*/
	//while(Read_key()!=0x01)
	
	/////////////////////////////////
	//第四步测试
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);		
	LCD_ShowString(150,60, " 第四步:RFID测试", White, Black);	
	LCD_ShowString(150, 220, "现象：刷卡看屏幕显示的信息", Red, Black); 	
	LCD_ShowString(150, 220, "提示：按K1退出", Red, Black); 
	Menu_RFIDTest();
	Delay(1000);
  //RFID测试完成
  //第五步测试
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(150,150, " 第五步:直流测试", White, Black);	
	LCD_ShowString(150, 220, "现象：直流电机转动", Red, Black); 
	Menu_DCMOTORTest();//OK

 //直流电机测试完成
 //第六步测试
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(150,60, " 第六步:步进电机测试", White, Black);	
	LCD_ShowString(150, 220, "现象：步进电机转动", Red, Black); 


	DuojiGpio_Init();  
	
	while(0)
	{	
		GPIO_WriteBit(GPIOF,GPIO_Pin_4,Bit_SET);
			STEP_delay_1ms(10);		
		GPIO_WriteBit(GPIOF,GPIO_Pin_4,Bit_RESET);
			STEP_delay_1ms(10);		
	};
	
   for(j=0;j<90;j++)
		for(i = 0; i < 8; i ++)
		{
			DUJIN_port(F_Rotation[i]);
			STEP_delay_1ms(5);
		}
		DUJIN_port(0x00); //        8214
#if 0
//步进电机测试完成
//第七步测试
	 init_TM1638();
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(150,60, " 第七步:键盘*8LED**LED**测试", White, Black);
	LCD_ShowString(150, 200, "现象:显示数码管和 LED亮然后按按键", Red, Black); 
	LCD_ShowString(150, 220, "提示：按K1退出", Red, Black);
	
		init_TM1638();	
		TM1638Test();
	Delay(1000);
//键盘\8LED\LED 测试完成
#endif
		
//第八步测试
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(150,60, " 第八步:气体--人体测试", White, Black);
	GAS_IN();
	HUMEN_IN();
	KEYGpio_Init();//按键IO口初始化
	while((KEY_S1_UPDOWM()!=Bit_RESET))
		{
	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2)  == Bit_RESET) LCD_ShowString(150, 200, "********GAS IN********", Red, Black);	
  else LCD_ShowString(150, 200, "********GAS NO********", White, Black);
/*		
	if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13) == Bit_RESET)	LCD_ShowString(150, 180, "*******HUMEN NO*******", White, Black);
  else LCD_ShowString(150, 180, "*******HUMEN IN*******", Red, Black); 
*/			
		LCD_ShowString(150, 220, "现象：有输入会红色报警**按K1退出", Red, Black); 	
		}
		Delay(1000);
//气体和人体的测试完成		

		//下面是点阵测试		
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(150,60," 第九步:点阵测试", White, Black);		
	LCD_ShowString(150, 200, "现象：点阵上显示**酷**字", Red, Black); 	
	LCD_ShowString(150, 220, "提示：按K1退出", Red, Black); 
	init_TM1638();
	KEYGpio_Init();//按键IO口初始化
	DPGpio_Init();
				hanzi=0;
			//while(KEY_S2_UPDOWM() == Bit_SET)
			while((KEY_S1_UPDOWM()!=Bit_RESET))
		//while(Read_key()!=0x01)
			{
			 for(shift=0;shift<16;shift++){	//一个字移位16位
  //HC595锁定输出,避免数据传输过程中，屏数据变化从而显示闪烁
	LAT_ONOFF(Bit_RESET);
	DCLK_ONOFF(Bit_RESET);
	//74HC595输出数据Hzk16
	data_buff = ziku_table[hanzi*32+shift*2+1];
	for(i=0;i<8;i++){
		if((data_buff&0x80)!=0) DI_ONOFF(Bit_SET);//DA_in_port = 1;
		else DI_ONOFF(Bit_RESET);//DA_in_port = 0;
		DCLK_ONOFF(Bit_SET);//CLK_port = 1;
		DCLK_ONOFF(Bit_RESET);//CLK_port = 0;
		data_buff <<= 1;
		}
		data_buff = ziku_table[hanzi*32+shift*2];
		for(i=0;i<8;i++)
		{
		if((data_buff&0x01)!=0) DI_ONOFF(Bit_SET);//DA_in_port = 1;
		else DI_ONOFF(Bit_RESET);//DA_in_port = 0;
		DCLK_ONOFF(Bit_SET);//CLK_port = 1;
		DCLK_ONOFF(Bit_RESET);//CLK_port = 0;
		data_buff >>= 1;
		}
	//74HC138输出控制	 
	G_ONOFF(Bit_SET);//EN_port = 1;    //关屏显示，原理为使HC138输出全为1，从而三极管截止，点阵不显示
	ABCD_port(shift);//ABCD_port = (ABCD_port & 0x0f)|(han<<4);  //HC138译码输出
	//ABCD_port(han);//ABCD_port = (ABCD_port & 0x0f)|(han<<4);  //HC138译码输出
	LAT_ONOFF(Bit_SET);//Latch_port = 1; //允许HC595数据输出到Q1-Q8端口
	G_ONOFF(Bit_RESET);//EN_port = 0;    //HC138输出有效，打开显示
	LAT_ONOFF(Bit_RESET);//Latch_port = 0;	//锁定HC595数据输出
	}
	
}

LAT_ONOFF(Bit_RESET);
	DCLK_ONOFF(Bit_RESET);
	G_ONOFF(Bit_SET);//EN_port = 1;    //关屏显示，原理为使HC138输出全为1，从而三极管截止，点阵不显示 

#endif
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(150,60, " 第十步:人体_传感器测试", White, Black);	
	LCD_ShowString(150, 200, "现象：看屏上的数据", Red, Black); 
	LCD_ShowString(150, 220, "提示：按K1退出", Red, Black);

	I2C_GPIO_Config();		
	InitBMP085();		
	MMA7455_self_test7455();	

	while((KEY_S1_UPDOWM()!=Bit_RESET))
	{
		 bmp085Convert();
		 DATA_Diplay();			
		if(MMA7455_self_test7455())	
		{					
			MMA7455_sendxyz();
			delay_1ms(100000);		
		}
		
		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13) == Bit_RESET)	LCD_ShowString(150, 180, "*******HUMEN NO*******", White, Black);
		else LCD_ShowString(150, 180, "*******HUMEN IN*******", Red, Black); 			
	}
	
/*	
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(150,60, " 第十一步：GSM测试 ", White, Black);	
	LCD_ShowString(150, 200, "现象：按K2发送AT指令", Red, Black); 
	LCD_ShowString(150, 220, "提示：按K1退出", Red, Black);
	
	while(1)
	{
		if(KEY_S2_UPDOWM()==Bit_RESET)
		{
				USART1_Send("AT\r\n",4);
			//while(KEY_S2_UPDOWM()==Bit_RESET);
		}		
	}
*/
	lcd_clear(Black);
	LCD_DrawRectangle(0,0, 479, 271, Green);
	LCD_DrawRectangle(5,5, 474, 266, Green);
	LCD_ShowString(150, 0, "--STM32F407 实验开发平台--", Red, Black);	
	LCD_ShowString(200,60, " 测试完成", White, Black);

	while(1)
	{
			//USART1_Send("AT\r\n",4);	
		//USART6_Send("AT\n",3);
	}
	
	
}

