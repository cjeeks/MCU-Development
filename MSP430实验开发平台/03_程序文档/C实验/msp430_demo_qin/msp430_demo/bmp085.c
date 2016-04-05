#include "msp430f5438a.h"
#include "macro.h"
#include "bmp085.h"

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
unsigned char outdata[4]={0x00,0x00,0x00,0x00};

/*******************************************************************************
* Function Name  : I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_delay(void)
{
  delay_us(5);
}

//*************************************************************************************************
//I2C?e那?D?o?
//*************************************************************************************************
void I2C_Start()
{
    SDA_H;                    //角-??那y?Y??
    SCL_H;                    //角-??那㊣?車??
    I2C_delay();                 //?車那㊣
    SDA_L;                    //2迆谷迆???米??
    I2C_delay();                 //?車那㊣
    SCL_L;                    //角-米赤那㊣?車??
    I2C_delay();                 //?車那	
}
//*************************************************************************************************
//I2C赤㏒?1D?o?
//*************************************************************************************************
void I2C_Stop()
{
    SCL_L;                    //角-??那㊣?車??
    SDA_L;                    //角-米赤那y?Y??
    I2C_delay();                 //?車那㊣	
    SCL_H;                    //角-??那㊣?車??
    I2C_delay();                 //?車那㊣
    SDA_H;                    //2迆谷迆谷?谷y??
    I2C_delay();                 //?車那㊣
}
//**************************************************************************************************
//I2C﹞⊿?赤車|∩eD?o?
//豕??迆2?那y:ack (0:ACK 1:NAK)
//**************************************************************************************************
void I2C_SendACK(char ack)
{
	if(ack == 1)
	  SDA_H;
	else
          SDA_L;                  //D∩車|∩eD?o?
	SCL_H;                    //角-??那㊣?車??
	I2C_delay();                 //?車那㊣
	SCL_L;                    //角-米赤那㊣?車??
	I2C_delay();                 //?車那㊣
}
//****************************************************************************************************
//I2C?車那?車|∩eD?o?
//****************************************************************************************************
char I2C_RecvACK()
{
	char CY;
	SDA_INPUT;
	I2C_delay();                 //?車那㊣	
	SCL_H;                    //角-??那㊣?車??
        SDA_INPUT;//CLAY
	I2C_delay();                 //?車那㊣
	if(READ_SDA)
            CY = 1;                   //?芍車|∩eD?o?
	else
	    CY = 0;
	SCL_L;                    //角-米赤那㊣?車??
	SDA_OUTPUT;
	I2C_delay();                 //?車那㊣
	return CY;
}
//*****************************************************************************************************
//?辰I2C℅邦??﹞⊿?赤辰???℅??迆那y?Y
//*****************************************************************************************************
void I2C_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8????那y?¯
    {
	if(dat&0x80)
          SDA_H;               //?赤那y?Y?迆
	else
	  SDA_L;
				
        dat <<= 1;              //辰?3?那y?Y米?℅?????			
        SCL_H;                //角-??那㊣?車??
        I2C_delay();             //?車那㊣
        SCL_L;                //角-米赤那㊣?車??
        I2C_delay();             //?車那㊣
    }
    I2C_RecvACK();
}
//*****************************************************************************************************
//∩車I2C℅邦???車那?辰???℅??迆那y?Y
//******************************************************************************************************
uchar I2C_RecvByte()
{
    uchar i;
    uchar dat = 0;
  SDA_INPUT;
    for (i=0; i<8; i++)         //8????那y?¯
    {
        SCL_L;                //角-米赤那㊣?車??
        I2C_delay();             //?車那㊣ 
        SCL_H;                //角-??那㊣?車??
        SDA_INPUT;
        I2C_delay();             //?車那㊣
  	dat <<= 1;			
	if(READ_SDA)
	  dat |= 1;             //?芍那y?Y               

    }
	  SDA_OUTPUT;		
    return dat;
}
//*****************************************************************************************************
//?辰I2C谷豕㊣?D∩豕?辰???℅??迆那y?Y
//*****************************************************************************************************
void Single_WriteI2C(uchar REG_Address,uchar REG_data)
{
    I2C_Start();                  //?e那?D?o?
    I2C_SendByte(SlaveAddress);   //﹞⊿?赤谷豕㊣?米??﹞+D∩D?o?
    I2C_SendByte(REG_Address);    //?迆2???∩??¯米??﹞㏒?
    I2C_SendByte(REG_data);       //?迆2???∩??¯那y?Y㏒?
    I2C_Stop();                   //﹞⊿?赤赤㏒?1D?o?
}
//*******************************************************************************************************
//∩車I2C谷豕㊣??芍豕?辰???℅??迆那y?Y
//*******************************************************************************************************
uchar Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	I2C_Start();                   //?e那?D?o?
	I2C_SendByte(SlaveAddress);    //﹞⊿?赤谷豕㊣?米??﹞+D∩D?o?
	I2C_SendByte(REG_Address);     //﹞⊿?赤∩?∩⊿米ㄓ?a米??﹞㏒?∩車0?a那?	
	I2C_Start();                   //?e那?D?o?
	I2C_SendByte(SlaveAddress+1);  //﹞⊿?赤谷豕㊣?米??﹞+?芍D?o?
	REG_data=I2C_RecvByte();       //?芍3???∩??¯那y?Y
	I2C_SendACK(1);                //?車那?車|∩eD?o?
	I2C_Stop();                    //赤㏒?1D?o?
	return REG_data;
}			

//*********************************************************
//??BMP085????,????
//*********************************************************
short Multiple_read(uchar ST_Address)
{   
	uchar msb, lsb;
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


//************那?芍迄????℅a??3谷℅?﹞?****************************
void string_shift(unsigned int dat) 
{ 
  outdata[3] =dat/1000+'0';      // 豕??∫?? 
  outdata[2] =(dat%1000)/100+'0'; //豕?～迄?? 
  outdata[1] =(dat%100)/10+'0';  // 豕?那??? 
  outdata[0] =dat%10+'0';        // 豕????? 
} 

  /*******************************/
void DATA_printf(uchar *s,short temp_data)
{
	if(temp_data<0){
	temp_data=-temp_data;
    *s='-';
	}
	else *s=' ';
    *++s =temp_data/100+0x30;
    temp_data=temp_data%100;     //豕?車角????
    *++s =temp_data/10+0x30;
    temp_data=temp_data%10;      //豕?車角????
    *++s =temp_data+0x30; 	
}

/*******************************************************************************
* Function Name  : I2C_GPIO_Config
* Description    : Configration Simulation IIC GPIO
* Input          : None 
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_GPIO_Config(void)
{
	I2C_Stop();
}

void i2c_SDA_input(void)
{
  SDA_INPUT;
}

void i2c_SDA_output(void)
{
  SDA_OUTPUT;
}
//******************************************************************************************************
//3?那??‘MPU6050
//******************************************************************************************************
void InitBMP085(void)
{
	I2C_GPIO_Config();
	
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
	
}
//********************************************************************
long bmp085ReadTemp(void)
{

    I2C_Start();                  //????
    I2C_SendByte(SlaveAddress);   //??????+???
    I2C_SendByte(0xF4);	          // write register address
    I2C_SendByte(0x2E);       	// write register data for temp
    I2C_Stop();                   //??????
	I2C_delay();	// max time is 4.5ms
	delay_ms(5);//clay
	return (long) Multiple_read(0xF6);
}
//*************************************************************
long bmp085ReadPressure(void)
{
	long pressure = 0;

    I2C_Start();                   //????
    I2C_SendByte(SlaveAddress);   //??????+???
    I2C_SendByte(0xF4);	          // write register address
    I2C_SendByte(0x34);       	  // write register data for pressure
    I2C_Stop();                    //??????
	I2C_delay();    	                  // max time is 4.5ms
		delay_ms(5);//clay
	pressure = Multiple_read(0xF6);
	pressure &= 0x0000FFFF;
	
	return pressure;	
	//return (long) bmp085ReadShort(0xF6);
}
	long  temperature;
	long  pressure;
//***********************************************************************
void bmp085Convert()
{
	long ut;
	long up;
	long x1, x2, b5, b6, x3, b3, p;
	unsigned long b4, b7;

	
	ut = bmp085ReadTemp();
	ut = bmp085ReadTemp();	   // ????
	up = bmp085ReadPressure();
	up = bmp085ReadPressure();  // ????
	
	x1 = ((long)ut - ac6) * ac5 >> 15;
	x2 = ((long) mc << 11) / (x1 + md);
	b5 = x1 + x2;
	 temperature = (b5 + 8) >> 4;

     //*************
	
	b6 = b5 - 4000;
	x1 = (b2 * (b6 * b6 >> 12)) >> 11;
	x2 = ac2 * b6 >> 11;
	x3 = x1 + x2;
	b3 = (((long)ac1 * 4 + x3) + 2)/4;
	x1 = ac3 * b6 >> 13;
	x2 = (b1 * (b6 * b6 >> 12)) >> 16;
	x3 = ((x1 + x2) + 2) >> 2;
	b4 = (ac4 * (unsigned long) (x3 + 32768)) >> 15;
	b7 = ((unsigned long) up - b3) * (50000 >> OSS);
	if( b7 < 0x80000000)
	     p = (b7 * 2) / b4 ;
           else  
		    p = (b7 / b4) * 2;
	x1 = (p >> 8) * (p >> 8);
	x1 = (x1 * 3038) >> 16;
	x2 = (-7357 * p) >> 16;
	 pressure = p + ((x1 + x2 + 3791) >> 4);


}

uchar str_value[5];
extern uchar* get_temperature()
{
  unsigned int temp_value;//char
  temp_value=temperature;
  string_shift(temp_value);
  str_value[0]=outdata[2];
  str_value[1]=outdata[1];
  str_value[2]='.';
  str_value[3]=outdata[0];
  str_value[4]='\0';
  return &str_value[0];
}
extern uchar* get_pressure()
{
   unsigned int temp_value;//char
  temp_value=pressure/1000;
  string_shift(temp_value*20);  
  
  str_value[0]=outdata[3];
  str_value[1]=outdata[2];
  str_value[2]=outdata[1];
  str_value[3]=outdata[0];
  str_value[4]='\0';  
  return &str_value[0];
}

void MMA7455_WriteI2C(uchar REG_Address,uchar REG_data)
{   uchar t;
    t=(0x1D<<1);
    I2C_Start();                  //?e那?D?o?
    I2C_SendByte(t);   //﹞⊿?赤谷豕㊣?米??﹞+D∩D?o?
    I2C_SendByte(REG_Address);    //?迆2???∩??¯米??﹞㏒?
    I2C_SendByte(REG_data);       //?迆2???∩??¯那y?Y㏒?
    I2C_Stop();                   //﹞⊿?赤赤㏒?1D?o?
}

uchar MMA7455_ReadI2C(uchar REG_Address)
{
    uchar REG_data;
     uchar t;
     t=(0x1D<<1);
    I2C_Start();                   //?e那?D?o?
    //I2C_SendByte(SlaveAddress);    //﹞⊿?赤谷豕㊣?米??﹞+D∩D?o?
    I2C_SendByte(t);    //﹞⊿?赤谷豕㊣?米??﹞+D∩D?
    I2C_SendByte(REG_Address);     //﹞⊿?赤∩?∩⊿米ㄓ?a米??﹞㏒?∩車0?a那?
    t=((0x1D<<1)|0x01);	
    I2C_Start();                   //?e那?D?o?
    //I2C_SendByte(SlaveAddress+1);  //﹞⊿?赤谷豕㊣?米??﹞+?芍D?o?
    I2C_SendByte(t);  //﹞⊿?赤谷豕㊣?米??﹞+?芍D?o?
    REG_data=I2C_RecvByte();       //?芍3???∩??¯那y?Y
    I2C_SendACK(1);                //?車那?車|∩eD?o?
    I2C_Stop();                    //赤㏒?1D?o?
    return REG_data;
}		

uchar self_test7455()					 //
{										 // 
	//uchar j;							 //		
	uchar t;

	I2C_delay();  
	MMA7455_WriteI2C(0x16,0x05);
	I2C_delay();  
        	delay_ms(5);//clay
	t=MMA7455_ReadI2C(0x16);
	//t=iic_read(0x16);
        return t;
/*
	if(t!=0x05)
	{
		//printf("No acceleration!"); //plug no good
	}
	else
	{
		//printf("X= 0.00,Y= 0.00, Z= 0.00,t=%c",t);
	}
*/
}