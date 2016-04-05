#include "bmp085.h"

#define OSS 0	// Oversampling Setting (note: code is not set up to use other OSS values)

//***BMP085??
unsigned char ge,shi,bai,qian,wan,shiwan;           //????
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

void delay5ms(void);
void I2C_Stop();


//************Ê®Áù½øÖÆ×ª»»³É×Ö·û****************************
void string_shift(unsigned int dat) 
{ 
  outdata[3] =dat/1000+'0';      // È¡Ç§Î» 
  outdata[2] =(dat%1000)/100+'0'; //È¡°ÙÎ» 
  outdata[1] =(dat%100)/10+'0';  // È¡Ê®Î» 
  outdata[0] =dat%10+'0';        // È¡¸öÎ» 
} 

  /*******************************/
void DATA_printf(u8 *s,short temp_data)
{
	if(temp_data<0){
	temp_data=-temp_data;
    *s='-';
	}
	else *s=' ';
    *++s =temp_data/100+0x30;
    temp_data=temp_data%100;     //È¡ÓàÔËËã
    *++s =temp_data/10+0x30;
    temp_data=temp_data%10;      //È¡ÓàÔËËã
    *++s =temp_data+0x30; 	
}
/*
void I2C_Gpio_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ÍÆÍìÊä³ö
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO¿ÚËÙ¶ÈÎª50MHz
		
	 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				
	 I2C_Stop();	
}
*/
void I2C_Gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	I2C_Stop();
}


void i2c_SDA_input(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void i2c_SDA_output(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	 GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*******************************************************************************
* Function Name  : I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_delay(void)
{
   u16 i=5000; //ÕâÀï¿ÉÒÔÓÅ»¯ËÙ¶È	£¬¾­²âÊÔ×îµÍµ½5»¹ÄÜÐ´Èë
   while(i) 
   { 
     i--; 
   }  
}

void delay5ms(void)
{
   int i=50000;  
   while(i) 
   { 
     i--; 
   }  
}
//*************************************************************************************************
//I2CÆðÊ¼ÐÅºÅ
//*************************************************************************************************
void I2C_Start()
{
    SDA_H;                    //À­¸ßÊý¾ÝÏß
    SCL_H;                    //À­¸ßÊ±ÖÓÏß
    I2C_delay();                 //ÑÓÊ±
    SDA_L;                    //²úÉúÏÂ½µÑØ
    I2C_delay();                 //ÑÓÊ±
    SCL_L;                    //À­µÍÊ±ÖÓÏß
    I2C_delay();                 //ÑÓÊ	
}
//*************************************************************************************************
//I2CÍ£Ö¹ÐÅºÅ
//*************************************************************************************************
void I2C_Stop()
{
	  SCL_L;                    //À­¸ßÊ±ÖÓÏß
    SDA_L;                    //À­µÍÊý¾ÝÏß
    I2C_delay();                 //ÑÓÊ±	
    SCL_H;                    //À­¸ßÊ±ÖÓÏß
    I2C_delay();                 //ÑÓÊ±
    SDA_H;                    //²úÉúÉÏÉýÑØ
    I2C_delay();                 //ÑÓÊ±
}
//**************************************************************************************************
//I2C·¢ËÍÓ¦´ðÐÅºÅ
//Èë¿Ú²ÎÊý:ack (0:ACK 1:NAK)
//**************************************************************************************************
void I2C_SendACK(char ack)
{
	if(ack == 1)
	  SDA_H;
	else
    SDA_L;                  //Ð´Ó¦´ðÐÅºÅ
	SCL_H;                    //À­¸ßÊ±ÖÓÏß
	I2C_delay();                 //ÑÓÊ±
	SCL_L;                    //À­µÍÊ±ÖÓÏß
	I2C_delay();                 //ÑÓÊ±
}
//****************************************************************************************************
//I2C½ÓÊÕÓ¦´ðÐÅºÅ
//****************************************************************************************************
char I2C_RecvACK()
{
	char CY;
	i2c_SDA_input();
	I2C_delay();                 //ÑÓÊ±	
	SCL_H;                    //À­¸ßÊ±ÖÓÏß
	I2C_delay();                 //ÑÓÊ±
	if(SDA_read)
    CY = 1;                   //¶ÁÓ¦´ðÐÅºÅ
	else
		CY = 0;
	SCL_L;                    //À­µÍÊ±ÖÓÏß
	i2c_SDA_output();
	I2C_delay();                 //ÑÓÊ±
	return CY;
}
//*****************************************************************************************************
//ÏòI2C×ÜÏß·¢ËÍÒ»¸ö×Ö½ÚÊý¾Ý
//*****************************************************************************************************
void I2C_SendByte(u8 dat)
{
    u8 i;
    for (i=0; i<8; i++)         //8Î»¼ÆÊýÆ÷
    {
			  if(dat&0x80)
          SDA_H;               //ËÍÊý¾Ý¿Ú
			  else
					SDA_L;
				
        dat <<= 1;              //ÒÆ³öÊý¾ÝµÄ×î¸ßÎ»			
        SCL_H;                //À­¸ßÊ±ÖÓÏß
        I2C_delay();             //ÑÓÊ±
        SCL_L;                //À­µÍÊ±ÖÓÏß
        I2C_delay();             //ÑÓÊ±
    }
    I2C_RecvACK();
}
//*****************************************************************************************************
//´ÓI2C×ÜÏß½ÓÊÕÒ»¸ö×Ö½ÚÊý¾Ý
//******************************************************************************************************
u8 I2C_RecvByte(void)
{
    u8 i;
    u8 dat = 0;
		i2c_SDA_input();
    for (i=0; i<8; i++)         //8Î»¼ÆÊýÆ÷
    {
        SCL_L;                //À­µÍÊ±ÖÓÏß
        I2C_delay();             //ÑÓÊ± 
        SCL_H;                //À­¸ßÊ±ÖÓÏß
        I2C_delay();             //ÑÓÊ±
  			dat <<= 1;			
			  if(SDA_read)
					dat |= 1;             //¶ÁÊý¾Ý               

    }
	  i2c_SDA_output();		
    return dat;
}



//*****************************************************************************************************
//ÏòI2CÉè±¸Ð´ÈëÒ»¸ö×Ö½ÚÊý¾Ý
//*****************************************************************************************************
void Single_WriteI2C(u8 SlaveAddress, u8 REG_Address,u8 REG_data)
{
    I2C_Start();                  //ÆðÊ¼ÐÅºÅ
    I2C_SendByte(SlaveAddress);   //·¢ËÍÉè±¸µØÖ·+Ð´ÐÅºÅ
    I2C_SendByte(REG_Address);    //ÄÚ²¿¼Ä´æÆ÷µØÖ·£¬
    I2C_SendByte(REG_data);       //ÄÚ²¿¼Ä´æÆ÷Êý¾Ý£¬
    I2C_Stop();                   //·¢ËÍÍ£Ö¹ÐÅºÅ
}

//*******************************************************************************************************
//´ÓI2CÉè±¸¶ÁÈ¡Ò»¸ö×Ö½ÚÊý¾Ý
//*******************************************************************************************************
u8 Single_ReadI2C(u8 SlaveAddress, u8 REG_Address)
{
	u8 REG_data;
	I2C_Start();                   //ÆðÊ¼ÐÅºÅ
	I2C_SendByte(SlaveAddress - 1);    //·¢ËÍÉè±¸µØÖ·+Ð´ÐÅºÅ
	I2C_SendByte(REG_Address);     //·¢ËÍ´æ´¢µ¥ÔªµØÖ·£¬´Ó0¿ªÊ¼	
	I2C_Start();                   //ÆðÊ¼ÐÅºÅ
	I2C_SendByte(SlaveAddress);  //·¢ËÍÉè±¸µØÖ·+¶ÁÐÅºÅ
	REG_data=I2C_RecvByte();       //¶Á³ö¼Ä´æÆ÷Êý¾Ý
	I2C_SendACK(1);                //½ÓÊÕÓ¦´ðÐÅºÅ
	I2C_Stop();                    //Í£Ö¹ÐÅºÅ
	return REG_data;
}				   

//*********************************************************
//??BMP085????,????
//*********************************************************
short Multiple_read(u8 SlaveAddress, u8 ST_Address)
{   
	u8 msb, lsb;
	short _data;
    I2C_Start();                          //????
    I2C_SendByte(SlaveAddress);    //??????+???
    I2C_SendByte(ST_Address);             //????????
    I2C_Start();                          //????
    I2C_SendByte(SlaveAddress+1);         //??????+???

    msb = I2C_RecvByte();                 //BUF[0]??
    I2C_SendACK(0);                       //??ACK
    lsb = I2C_RecvByte();     
	I2C_SendACK(1);                       //?????????NOACK

    I2C_Stop();                           //????
    //Delay5ms();
    _data = msb << 8;
	_data |= lsb;	
	return _data;
}
//******************************************************************************************************
//³õÊ¼»¯MPU6050
//******************************************************************************************************
void InitBMP085(void)
{
	ac1 = Multiple_read(BMP085_SlaveAddress, 0xAA);
	ac2 = Multiple_read(BMP085_SlaveAddress, 0xAC);
	ac3 = Multiple_read(BMP085_SlaveAddress, 0xAE);
	ac4 = Multiple_read(BMP085_SlaveAddress, 0xB0);
	ac5 = Multiple_read(BMP085_SlaveAddress, 0xB2);
	ac6 = Multiple_read(BMP085_SlaveAddress, 0xB4);
	b1 =  Multiple_read(BMP085_SlaveAddress, 0xB6);
	b2 =  Multiple_read(BMP085_SlaveAddress, 0xB8);
	mb =  Multiple_read(BMP085_SlaveAddress, 0xBA);
	mc =  Multiple_read(BMP085_SlaveAddress, 0xBC);
	md =  Multiple_read(BMP085_SlaveAddress, 0xBE);
}
//********************************************************************
long bmp085ReadTemp(void)
{

    I2C_Start();                  //????
    I2C_SendByte(BMP085_SlaveAddress);   //??????+???
    I2C_SendByte(0xF4);	          // write register address
    I2C_SendByte(0x2E);       	// write register data for temp
    I2C_Stop();                   //??????
		I2C_delay();	// max time is 4.5ms
	
	return (long) Multiple_read(BMP085_SlaveAddress, 0xF6);
}
//*************************************************************
long bmp085ReadPressure(void)
{
	long pressure = 0;

    I2C_Start();                   //????
    I2C_SendByte(BMP085_SlaveAddress);   //??????+???
    I2C_SendByte(0xF4);	          // write register address
    I2C_SendByte(0x34);       	  // write register data for pressure
    I2C_Stop();                    //??????
	I2C_delay();    	                  // max time is 4.5ms
	
	pressure = Multiple_read(BMP085_SlaveAddress, 0xF6);
	pressure &= 0x0000FFFF;
	
	return pressure;	
	//return (long) bmp085ReadShort(0xF6);
}

//***********************************************************************
void bmp085Convert()
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

void bmp085_conversion(long temp_data, uint8_t *p)
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
	u8 tmp[15]={"temperture:00.0"}, pres[19] = {"pressure:000000 Pa"};
	long temp_value;
//	LCD_ShowString(200, 18, bmp_tmp, White, Black);
	temp_value=temperature;

	bmp085_conversion(temp_value, outdata);	

	tmp[11]=outdata[3];
	tmp[12]=outdata[4];
	tmp[14]=outdata[5];

	LCD_ShowString(150, 150, tmp);
	//printf("temperature=%c%c.%c\n",outdata[3],outdata[4],outdata[5]);
	
	temp_value = pressure;
	bmp085_conversion(temp_value, outdata);
	
	pres[9]  = outdata[0];
	pres[10] = outdata[1];
	pres[11] = outdata[2];
	pres[12] = outdata[3];
	pres[13] = outdata[4];
	pres[14] = outdata[5];	
	
	LCD_ShowString(150, 180, pres);
	//printf("pressure=%c%c%c%c%c%c Pa\n",outdata[0],outdata[1],outdata[2],outdata[3],outdata[4],outdata[5]);
}

void BMP085_Test(void)
{

	
	I2C_Gpio_Init();
	InitBMP085();
  bmp085Convert();
  DATA_Diplay();		
}

