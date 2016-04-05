#ifndef __BMP085_H
#define __BMP085_H 		

typedef enum { FALSE = 0, TRUE } BOOL;
#define bool BOOL

#define	SlaveAddress	0xEE	//IICD¡ä¨¨?¨º¡À¦Ì?¦Ì??¡¤¡Á??¨²¨ºy?Y¡ê?+1?a?¨¢¨¨?

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
#endif		