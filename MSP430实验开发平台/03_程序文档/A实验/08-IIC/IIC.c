#include "msp430f5438a.h"
#include "IIC.h"

#define ATxx_CLR_SCK
#define ATxx_SET_SCK
#define ATxx_CLR_SI
#define ATxx_SET_SI
#define ATxx_IN_SO
#define 
#define 
#define 
#define 
#define 

void Init_AT24C02(void) 
{
  
}
static void Start_FM31256(void)
{
   FM_SCL_out;
   FM_SDA_out;
   FM_SET_SCL;
   FM_SET_SDA;
   delay_us(3);
   FM_CLR_SDA;
   delay_us(6);
   FM_CLR_SCL;
   delay_us(4);
}

static void Stop_FM31256(void)
{
   FM_SDA_out;
   FM_CLR_SCL;
   FM_CLR_SDA;
   delay_us(3);
   FM_SET_SCL;
   delay_us(5);
   FM_SET_SDA;
   delay_us(3);
}

static void SendByte_FM31256(unsigned char dat)
{
   unsigned char i,FMin;
   FM_SDA_out;
   do
   {
     for(i=0;i<8;i++)
     {
       FMin=dat&0x80;
       if(FMin)
       {
         FM_SET_SDA;  //set SDA	
       }
       else
       {
         FM_CLR_SDA;  //clr SDA
       }
       dat=dat<<1;
       FM_SET_SCL;  //set SCL
       delay_us(5);
       FM_CLR_SCL; 
       delay_us(3);
     }
     FM_SDA_in;  //SDA设定为输入？？？？   //**************ATX256A3**************
     delay_us(2);
     FM_SET_SCL;
     delay_us(3);
   }while(SDA_IN);  //等待应答，无应答重新发送    //**************ATX256A3**************
   delay_us(3);
   FM_CLR_SCL;
   FM_SDA_out;
   FM_CLR_SDA;
}

static unsigned char ReceiveByte_FM31256(void)
{
   unsigned char i,FMout,dat=0;
   delay_us(3);
   FM_SDA_in;  //SDA设定为输入？？？？   //**************ATX256A3**************
   for(i=0;i<8;i++)
   {
     FM_SET_SCL;  //set SCL
     delay_us(2);
     FMout=SDA_IN;    //**************ATX256A3**************
     delay_us(3);
     if(FMout)
     {
       dat|=0x01;
     }
     if(i!=7)
     {
       dat<<=1;
     }
     FM_CLR_SCL;  //clr SCL
     delay_us(3);
   }
   delay_us(3);
   return(dat);
}

static void Ans_FM31256(void)
{
   FM_SDA_out;
   FM_CLR_SDA;
   FM_SET_SCL;
   delay_us(5);
   FM_CLR_SCL;
   delay_us(3);
}

static void NoAns_FM31256(void)
{
   FM_SDA_out;
   FM_CLR_SCL;
   FM_SET_SDA;
   FM_SET_SCL;
   delay_us(5);
   FM_CLR_SCL;
   delay_us(3);
}
