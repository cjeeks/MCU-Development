#ifndef _BMP085_H_
#define _BMP085_H_
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include "lcd.h"

#define	BMP085_SlaveAddress	0xEE	//IIC写入时的地址字节数据，+1为读取

//************************************
/*模拟IIC端口输出输入定义*/
#define SCL_H         GPIO_SetBits(GPIOB,GPIO_Pin_6) 
#define SCL_L         GPIO_ResetBits(GPIOB,GPIO_Pin_6) 
   
#define SDA_H         GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SDA_L         GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

typedef enum { FALSE = 0, TRUE } BOOL;
#define bool BOOL

void I2C_GPIO_Config(void);
void InitBMP085(void);
void bmp085Convert();

int GetData(unsigned char REG_Address);
void DATA_Diplay();

void I2C_Gpio_Init(void);


void I2C_Start();
void I2C_Stop();
void I2C_SendACK(char ack);
char I2C_RecvACK();
void I2C_SendByte(u8 dat);
u8 I2C_RecvByte(void);
void Single_WriteI2C(u8 SlaveAddress, u8 REG_Address,u8 REG_data);
u8 Single_ReadI2C(u8 SlaveAddress, u8 REG_Address);
short Multiple_read(u8 SlaveAddress, u8 ST_Address);
void Acc_Gas_Test(void);


#endif