#ifndef __BMP085_H
#define __BMP085_H 		

typedef enum { FALSE = 0, TRUE } BOOL;
#define bool BOOL

#define	SlaveAddress	0xEE	//IICD′è?ê±μ?μ??·×??úêy?Y￡?+1?a?áè?

#define	PCF8574_SlaveAddress	0x23	//IIC写入时的地址 
#define IIC_READ  PCF8574_SlaveAddress      				//定义读指令
#define IIC_WRITE PCF8574_SlaveAddress      				//定义写指令

#define OSS 0	// Oversampling Setting (note: code is not set up to use other OSS values)

//IIC FOR BMP085 PRESSURE
//FOR MMA7455 acceleration
// eeprom
//sda p9.7 scl p9.6 

#define SDA_INPUT do{P9DIR&=~BIT7;}while(0)
#define SDA_OUTPUT do{P9DIR|=BIT7;}while(0)
#define SDA_H do{P9DIR|=BIT7;P9OUT|=BIT7;}while(0)
#define SDA_L do{P9DIR|=BIT7;P9OUT&=~BIT7;}while(0)
#define READ_SDA (P9IN&BIT7)
#define SCL_H do{P9DIR|=BIT6;P9OUT|=BIT6;}while(0)
#define SCL_L do{P9DIR|=BIT6;P9OUT&=~BIT6;}while(0)

extern unsigned char self_test7455();	
extern void InitBMP085(void);
extern unsigned char* get_temperature();
extern unsigned char* get_pressure();
extern void bmp085Convert();
extern void PCF8574_Single_WriteI2C(uchar REG_Address,uchar REG_data);
extern unsigned char  PCF8574_Single_ReadI2C(uchar REG_Address);
extern void KEY_Test(void);
#endif		