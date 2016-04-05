#ifndef _BMP085_H_
#define _BMP085_H_
#define   uchar unsigned char
#define   uint unsigned int	

#define	BMP085_SlaveAddress	0xEE	//IIC写入时的地址字节数据，+1为读取

//************************************
/*模拟IIC端口输出输入定义*/
#define SCL_H         GPIO_SetBits(GPIOF,GPIO_Pin_1) //GPIOB->BSRR = GPIO_Pin_3
#define SCL_L         GPIO_ResetBits(GPIOF,GPIO_Pin_1) //GPIOB->BRR  = GPIO_Pin_3 
   
#define SDA_H         GPIO_SetBits(GPIOF,GPIO_Pin_0)//GPIOA->BSRR = GPIO_Pin_15
#define SDA_L         GPIO_ResetBits(GPIOF,GPIO_Pin_0)//GPIOA->BRR  = GPIO_Pin_15

#define SCL_read      GPIOF->IDR  & GPIO_Pin_1
#define SDA_read      GPIOF->IDR  & GPIO_Pin_0

typedef enum { FALSE = 0, TRUE } BOOL;
#define bool BOOL

void I2C_GPIO_Config(void);
void i2c_SDA_input(void);
void i2c_SDA_output(void);
void I2C_delay(void);
void I2C_Start();
void I2C_Stop();
void I2C_SendACK(char ack);
char I2C_RecvACK();
void I2C_SendByte(uchar dat);
void Single_WriteI2C(uchar SlaveAddress, uchar REG_Address,uchar REG_data);
uchar Single_ReadI2C(uchar SlaveAddress, uchar REG_Address);
short Multiple_read(uchar SlaveAddress, uchar ST_Address);

void InitBMP085(void);

void bmp085Convert();

int GetData(unsigned char REG_Address);
void DATA_Diplay();

#endif
