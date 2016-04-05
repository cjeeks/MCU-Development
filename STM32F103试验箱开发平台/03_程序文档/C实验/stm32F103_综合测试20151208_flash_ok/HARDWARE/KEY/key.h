#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#include "PCF8574.h"
#include "lcd.h"
#include "string.h"		//include : strstr()
#include "usart.h"

extern uint8_t gsm_ch[GSM_length];

// 
//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define KEY3 PAin(0)	//PA0  WK_UP
 
#define KEY4  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//读取按键1
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键2 
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 


#define KEY_UP 		4
#define KEY_LEFT	3
#define KEY_DOWN	2
#define KEY_RIGHT	1

 void Delay5ms(void);
void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数		
void KEY_Test(void);
#endif
