#ifndef _MMA7455_H_
#define _MMA7455_H_

#include <reg51.h>
#include <intrins.h>
#include <PCF8574T\PCF8574T.h>
#include <lcd\lcd.h>
 
#define   uchar unsigned char
#define   uint unsigned int	

#define	MMA7455_SlaveAddress	0x1D	//IICD′è?ê±μ?μ??· 
#define MMA7455_IIC_READ  		((0x1D << 1) | 0x01)  //?¨ò??á??á?
#define MMA7455_IIC_WRITE 		(0x1D << 1)  //?¨ò?D′??á?

#define IIC_READ  0x1D      //定义读指令
#define IIC_WRITE 0x1D      //定义写指令

//************************************
/*?￡?aIIC???úê?3?ê?è??¨ò?*/
#define SCL_H         SCL = 1; //GPIO_SetBits(GPIOF,GPIO_Pin_1) //GPIOB->BSRR = GPIO_Pin_3
#define SCL_L         SCL = 0; //GPIO_ResetBits(GPIOF,GPIO_Pin_1) //GPIOB->BRR  = GPIO_Pin_3 
   
#define SDA_H         SDA = 1; //GPIO_SetBits(GPIOF,GPIO_Pin_0)//GPIOA->BSRR = GPIO_Pin_15
#define SDA_L         SDA = 0; //GPIO_ResetBits(GPIOF,GPIO_Pin_0)//GPIOA->BRR  = GPIO_Pin_15

sbit sda=P1^0;              //I2C 数据传送位
sbit scl=P1^1;              //I2C 时钟传送位

//#define SCL_read      GPIOB->IDR  & GPIO_Pin_6
//#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

void MMA7455_delay50us(void);
void MMA7455_data_init(void);
u8 MMA7455_self_test(void);
void MMA7455_sendxyz(void);
void MMA7455_Test(void);



 #endif