#ifndef _BMP085_H_
#define _BMP085_H_
#include <reg51.h>
#include <intrins.h>
#include <PCF8574T\PCF8574T.h>
#include <lcd\lcd.h>
 
#define	BMP085_SlaveAddress	0xEE	//IICD¡ä¨¨?¨º¡À¦Ì?¦Ì??¡¤¡Á??¨²¨ºy?Y¡ê?+1?a?¨¢¨¨?

//************************************
//¡ê?aIIC???¨²¨º?3?¨º?¨¨??¡§¨°?
#define SCL_H         SCL = 1; //GPIO_SetBits(GPIOF,GPIO_Pin_1) //GPIOB->BSRR = GPIO_Pin_3
#define SCL_L         SCL = 0; //GPIO_ResetBits(GPIOF,GPIO_Pin_1) //GPIOB->BRR  = GPIO_Pin_3 
   
#define SDA_H         SDA = 1; //GPIO_SetBits(GPIOF,GPIO_Pin_0)//GPIOA->BSRR = GPIO_Pin_15
#define SDA_L         SDA = 0; //GPIO_ResetBits(GPIOF,GPIO_Pin_0)//GPIOA->BRR  = GPIO_Pin_15

//#define SCL_read      GPIOF->IDR  & GPIO_Pin_1
//#define SDA_read      GPIOF->IDR  & GPIO_Pin_0


typedef enum { FALSE = 0, TRUE } BOOL;
#define bool BOOL

short Multiple_read(u8 ST_Address);

void InitBMP085(void);
long bmp085ReadTemp(void);
long bmp085ReadPressure(void);
void bmp085Convert(void);
void bmp085_conversion(long temp_data, u8 *p);
int GetData(u8 REG_Address);
void DATA_Diplay();

#endif