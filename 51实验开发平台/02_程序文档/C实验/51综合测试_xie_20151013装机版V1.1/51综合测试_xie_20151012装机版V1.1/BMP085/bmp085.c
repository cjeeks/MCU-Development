#include "bmp085.h"

#define uchar u8
#define OSS 0	// Oversampling Setting (note: code is not set up to use other OSS values)

short ac1;
short ac2; 
short ac3; 
unsigned short ac4;
unsigned short ac5;
unsigned short ac6;
short b1; 
short b2;
short mb;
short mc;
short md;
long  temperature;
long  pressure;
float tempdat=0;
unsigned char outdata[6]={0};
//*********************************************************
//??BMP085????,????
//*********************************************************
short Multiple_read(uchar ST_Address)
{   
	uchar msb, lsb;
	short _data;
    I2C_Start();                          //????
    I2C_WriteAbyte(BMP085_SlaveAddress);    //??????+???
    I2C_WriteAbyte(ST_Address);             //????????
    I2C_Start();                          //????
    I2C_WriteAbyte(BMP085_SlaveAddress+1);         //??????+???

    msb = I2C_ReadAbyte();                 //BUF[0]??
    //I2C_SendACK(0);                       //??ACK
	S_ACK();
    lsb = I2C_ReadAbyte();     
	//I2C_SendACK(1);                       //?????????NOACK
	S_NoACK(); 
    I2C_Stop();                           //????
    //Delay5ms();
    _data = msb << 8;
	_data |= lsb;	
	return _data;
}


//******************************************************************************************************
//3?¨º??¡¥MPU6050
//******************************************************************************************************
void InitBMP085(void)
{	
	u8 tmp[16]={"temperture:00.0 "};
	u8 pres[19] = {"pressure:000000 Pa"};

	ac1 = Multiple_read(0xAA);
	ac2 = Multiple_read(0xAC);
	ac3 = Multiple_read(0xAE);
	ac4 = Multiple_read(0xB0);
	ac5 = Multiple_read(0xB2);
	ac6 = Multiple_read(0xB4);
	b1 =  Multiple_read(0xB6);
	b2 =  Multiple_read(0xB8);
	mb =  Multiple_read(0xBA);
	mc =  Multiple_read(0xBC);
	md =  Multiple_read(0xBE);

	LCD_ShowString(150, 150, "temperture:");
	LCD_ShowString(150, 120, "pressure:");
}
//********************************************************************
long bmp085ReadTemp(void)
{

    I2C_Start();                  //????
    //I2C_SendByte(BMP085_SlaveAddress);   //??????+???
	I2C_WriteAbyte(BMP085_SlaveAddress);
    I2C_WriteAbyte(0xF4);	          // write register address
    I2C_WriteAbyte(0x2E);       	// write register data for temp
    I2C_Stop();                   //??????
		I2C_delay();	// max time is 4.5ms
	
	return (long) Multiple_read(0xF6);
}
//*************************************************************
long bmp085ReadPressure(void)
{
	long pressure = 0;

    I2C_Start();                   //????
    I2C_WriteAbyte(BMP085_SlaveAddress);   //??????+???
    I2C_WriteAbyte(0xF4);	          // write register address
    I2C_WriteAbyte(0x34);       	  // write register data for pressure
    I2C_Stop();                    //??????
	I2C_delay();    	                  // max time is 4.5ms
	
	pressure = Multiple_read(0xF6);
	pressure &= 0x0000FFFF;
	
	return pressure;	
	//return (long) bmp085ReadShort(0xF6);
}

//***********************************************************************
void bmp085Convert(void)
{
	unsigned int ut = 0;
	unsigned long up = 0;
	long x1, x2, b5, b6, x3, b3, p;
	unsigned long b4, b7;

	ut = bmp085ReadTemp();	   // change by enviornment
	up = bmp085ReadPressure();  // change by enviornment
	
	x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
	x2 = ((long) mc << 11) / (x1 + md);
	b5 = x1 + x2;
	temperature = ((b5 + 8) >> 4);
	
  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<< OSS) + 2)>>2;
  
  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
  
  b7 = ((unsigned long)(up - b3) * (50000 >> OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;
    
  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  pressure = p+((x1 + x2 + 3791)>>4);
}

void bmp085_conversion(long temp_data, u8 *p)
{
	  *p++ = temp_data/100000+0x30;
    temp_data=temp_data%100000;   
		*p++=temp_data/10000+0x30;
    temp_data=temp_data%10000;   
		*p++=temp_data/1000+0x30;
    temp_data=temp_data%1000;    
    *p++=temp_data/100+0x30;
    temp_data=temp_data%100;     
    *p++=temp_data/10+0x30;
    temp_data=temp_data%10;     
    *p++=temp_data+0x30; 
}


void DATA_Diplay()
{ 
	u8 tmp[33]={"00.0                             "};
	u8 pres[19] = {"pressure:000000 Pa"};

	long temp_value;
//	LCD_ShowString(200, 18, bmp_tmp);
	temp_value=temperature;

	bmp085_conversion(temp_value, outdata);	

	tmp[0]=outdata[3];
	tmp[1]=outdata[4];
	tmp[3]=outdata[5];
	LCD_ShowString(238, 150, tmp);
//	printf("temperature=%c%c.%c\n",outdata[3],outdata[4],outdata[5]);
	
	temp_value = pressure;
	bmp085_conversion(temp_value, outdata);
	
	pres[9]  = outdata[0];
	pres[10] = outdata[1];
	pres[11] = outdata[2];
	pres[12] = outdata[3];
	pres[13] = outdata[4];
	pres[14] = outdata[5];	
	
	LCD_ShowString(150, 120, pres);
	//printf("pressure=%c%c%c%c%c%c Pa\n",outdata[0],outdata[1],outdata[2],outdata[3],outdata[4],outdata[5]);
}

void BMP085_Test(void)
{

		
	InitBMP085();

	bmp085Convert();
	DATA_Diplay();			
}

