

//#include "stm32f10x.h"
#include "tm1638.h"
#include "msp430f5438a.h"
//#include "delay.h"
//#include "gpio.h"
#include "macro.h"
#include "LCD.h"

unsigned char const tab[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};//êy??1ü0μ?Fμ???ê?
unsigned char key_tmp=0xff;
//CLK
#define DDCLK_DIROUT do{P1DIR|=BIT4;}while(0)
#define DDCLK_OFF do{P1OUT&=~BIT4;}while(0)
#define DDCLK_ON do{P1OUT|=BIT4;}while(0)

//STB
#define DDSTB_DIROUT do{P1DIR|=BIT6;}while(0)
#define DDSTB_OFF do{P1OUT&=~BIT6;}while(0)
#define DDSTB_ON do{P1OUT|=BIT6;}while(0)

//DIO FOR OUTPUT
#define DDDIO_DIROUT do{P1DIR|=BIT7;}while(0)
#define DDDIO_OFF do{P1OUT&=~BIT7;}while(0)
#define DDDIO_ON do{P1OUT|=BIT7;}while(0)

//DIO FOR INPUT
#define DDDIO_PULLUP do{P1REN|=BIT7;}while(0)
#define DDDIO_OUT_H do{P1OUT|=BIT7;}while(0)
#define DDDIO_IN (P1IN&BIT7)

//P1.4--> CLK
//P1.6-->STB
//P1.7-->DIO

//TM1638 STB接PB9  CLK接PB4    DIO接PB8
void Delay(unsigned char tim)
{
	int i;
	for(;tim>0;tim--)
       // for(i=0;i<500;i++)
          for(i=0;i<100;i++)
	{;}
}
void delay_tim(unsigned char tim)
{
	unsigned char i;
	for(;tim>0;tim--)
	 for(i=0;i<20;i++)
	{;}
}
/*
//读数据延时函数
static Delay_1us(int counter)
{
	int i,j;
	for(i=0;i<counter;i++)
	  for(j=0;j<33;j++);
}
*/

void DIO_OUT() //配置TM1638DIO引脚为推挽输出
{
  DDDIO_DIROUT;//上拉使能输出
}
void DIO_IN()  //配置TM1638DIO引脚为上拉输入
{
  DDDIO_PULLUP;
  DDDIO_OUT_H;
}
//
void TM1638_Write(unsigned char	DATA)			//写数据函数
{
   unsigned char i;
   DIO_OUT();
				
   for(i=0;i<8;i++)
   {
   	//GPIO_ResetBits(GPIOB,GPIO_Pin_4);
    //delay_us(3);//delay_tim(1);
        DDCLK_OFF;
        delay_us(3);//delay_tim(1);
	  if(DATA&0X01)
            DDDIO_ON;
	  else 
            DDDIO_OFF;    
	  DATA>>=1;
          delay_us(3);//delay_tim(1);
          DDCLK_ON;  
	 //delay_tim(1);
   }
	 
}
unsigned char TM1638_Read(void)					//读数据函数
{
	unsigned char i;
	unsigned char temp=0;
	DIO_IN();
	for(i=0;i<8;i++)
	{
	  temp>>=1;
        //delay_us(10);// delay_tim(1);
           DDCLK_OFF; 
	  //delay_ms(10);// Delay(1);
	   if(DDDIO_IN == BIT7) 
	    temp|=0x80;
           //delay_us(10);//delay_tim(1);
		DDCLK_ON;  
		//delay_tim(1);
	}
	return temp;
}
void Write_COM(unsigned char cmd)		//发送命令字
{
      //delay_tim(1);
      //delay_us(3);
        DDSTB_OFF; 
       // delay_tim(1);
       // delay_us(3);
	TM1638_Write(cmd);
        //delay_us(3);//delay_tim(1);
        DDSTB_ON;
}


unsigned char Read_key(void)
{
  unsigned char c[4],i,key_value=0;
  
  DDSTB_OFF;
  TM1638_Write(0x42);
  for(i=0;i<4;i++)
          c[i]=TM1638_Read();	
  DDSTB_ON;
  /*
  for(i=0;i<4;i++)
          key_value|=c[i]<<i;
  for(i=0;i<8;i++)
          if((0x01<<i)==key_value)
                  break;
  */
  if(c[0] == 0x01)
    key_value = 9;
  else if(c[0] == 0x10)
    key_value = 10;
   else if(c[0] == 0x02)
    key_value = 1;
   else if(c[0] == 0x20)
    key_value = 2;
   else  if(c[1] == 0x01)
    key_value = 11;
  else if(c[1] == 0x10)
    key_value = 12;
   else if(c[1] == 0x02)
    key_value = 3;
   else if(c[1] == 0x20)
    key_value = 4;
   else if(c[2] == 0x01)
    key_value = 13;
  else if(c[2] == 0x10)
    key_value = 14;
   else if(c[2] == 0x02)
    key_value = 5;
   else if(c[2] == 0x20)
    key_value = 6;
   else if(c[3] == 0x01)
    key_value = 15;
  else if(c[3] == 0x10)
    key_value = 16;
   else if(c[3] == 0x02)
    key_value = 7;
   else if(c[3] == 0x20)
    key_value = 8;
   else
    key_value = 0xff;
  
  return key_value;
  
}
void Write_DATA(unsigned char add,unsigned char DATA)
{
  //delay_us(3);//delay_tim(1);
    Write_COM(0x44);
    //delay_us(3);//delay_tim(1);
     DDSTB_OFF;
    //delay_us(3);// delay_tim(1);
	TM1638_Write(0xc0|add);
      // delay_us(3);// delay_tim(1);
	TM1638_Write(DATA);
       //delay_us(3);// delay_tim(1);
         DDSTB_ON;
       //delay_us(3);//  delay_tim(1);
}
void Write_oneLED(unsigned char num,unsigned char flag)	//单独控制一个LED函数，num为需要控制的led序号，flag为0时熄灭，不为0时点亮
{
	Write_DATA(num,flag);
}
void init_TM1638(void)
{	
	unsigned char i;
	//TM1638_GPIO_Configuration();   //IO口初始化
          DDCLK_DIROUT;
          DDSTB_DIROUT;
          DDCLK_OFF;
          DDSTB_ON; 
          DDDIO_DIROUT;
          DDDIO_OFF;
          
         // delay_us(10);
        //  delay_tim(1);
	Write_COM(0x8a);//脉冲宽度为全亮度的4/16
        //delay_ms(1);
       // delay_tim(1);
	Write_COM(0x40);
        //delay_ms(1);
       // delay_tim(1);
        DDSTB_OFF;
        //delay_tim(1);
	TM1638_Write(0xc0);
	for(i=0;i<16;i++)
	TM1638_Write(0x00);
       // delay_tim(1);
        //delay_ms(1);
        DDSTB_ON;
}

extern void USB_TX(char *);

void TM1638Test(void)
{
	unsigned char i,j;
	unsigned char keyDat;
	unsigned char tempcount=0;
         USB_TX("init_TM1638 \n\r ");
	init_TM1638();

        USB_TX("init_TM1638 test \n\r ");
       // while(1)
	for(i=0;i<16;i++)
	{
	  for(j=0;j<8;j++)
	    Write_DATA(j<<1,tab[i]); //show 1~9 a~f
          delay_ms(300);//delay_s(1);delay_s(1);
	}

	for(j=0;j<8;j++){
	  Write_DATA(j<<1,tab[0]); //set to 0
          delay_ms(300);//delay_s(1);
        }
	
	for(i=0;i<16;i++)
	{ 
          i++;
	  for(j=0;j<3;j++)
		{
		Write_oneLED(i,j); //led on key
	        delay_ms(300);
		}
	}
        
	 USB_TX("init_TM1638 test 3233333 \n\r ");
      
	while(tempcount<16)
	{
		keyDat=Read_key();
                
                //LCD_ShowString(160,160,"get key dat  = ");
                //LCD_ShowNum(250,160,keyDat,4);
                delay_ms(50);//delay_s(1); delay_s(1);
                
		if(keyDat<17)
		{   	
		    for(j=0;j<8;j++)
	                Write_DATA(j<<1,tab[keyDat]);
                    
		    if(keyDat!=key_tmp)
			{
			    tempcount++;
			    key_tmp=keyDat;
			}                  
			switch (keyDat){
				case 0x01:
				default:
				break;
			}
                 }
          }
        
}