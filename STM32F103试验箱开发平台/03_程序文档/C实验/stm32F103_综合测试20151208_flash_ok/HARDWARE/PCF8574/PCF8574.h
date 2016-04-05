#ifndef _PCF8574_IIC_H_
#define _PCF8574_IIC_H_
#include "stm32f10x.h"

#define   uchar unsigned char
#define   uint unsigned int	

//A0 A1 A2
//L  L  L
#define PCF8574T_A 0x20										
#define PCF8574T_A_W (PCF8574T_A << 1)
#define PCF8574T_A_R ((PCF8574T_A << 1) | 0x01)
//A0 A1 A2
//L  L  H
#define PCF8574T_B 0x21										
#define PCF8574T_B_W (PCF8574T_B << 1)
#define PCF8574T_B_R ((PCF8574T_B << 1) | 0x01)
//H  H  L
#define PCF8574T_C 0x23										
#define PCF8574T_C_W (PCF8574T_C << 1)
#define PCF8574T_C_R ((PCF8574T_C << 1) | 0x01)
//H  H  H
#define PCF8574T_D 0x27										
#define PCF8574T_D_W (PCF8574T_D << 1)
#define PCF8574T_D_R ((PCF8574T_D << 1) | 0x01)

//PCF8574_SlaveAddress OLD: 0X22   NEW: 0X23

#define	PCF8574_SlaveAddress	0x23	//IIC写入时的地址 
#define IIC_READ  0x22      				//定义读指令
#define IIC_WRITE 0x22      				//定义写指令
//************************************
/*模拟IIC端口输出输入定义*/
#define SCL_H         GPIO_SetBits(GPIOB,GPIO_Pin_6) 
#define SCL_L         GPIO_ResetBits(GPIOB,GPIO_Pin_6) 
   
#define SDA_H         GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SDA_L         GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7

void PCF8574_I2C_GPIO_Config(void);
void PCF8574_i2c_SDA_input(void);
void PCF8574_i2c_SDA_output(void);
void PCF8574_I2C_delay(void);
void PCF8574_delay5ms(void);
void PCF8574_delay50us(void);
void PCF8574_I2C_Start(void);
void PCF8574_I2C_Stop(void);
void PCF8574_I2C_SendACK(char ack);
char PCF8574_I2C_RecvACK(void);
void PCF8574_I2C_SendByte(uchar dat);
uchar PCF8574_I2C_RecvByte(void);
void PCF8574_Single_WriteI2C(uchar REG_Address,uchar REG_data);
uchar PCF8574_Single_ReadI2C(uchar REG_Address);


#endif

