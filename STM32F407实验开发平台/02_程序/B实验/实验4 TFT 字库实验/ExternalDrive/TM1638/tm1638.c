

//#include "stm32f10x.h"
#include "tm1638.h"
#include "delay.h"
//TM1638 STB?PB13  CLK?PB14    DIO?PB15  old
//TM1638 STB接PB9  CLK接PB4    DIO接PB8
void DIO_OUT() //配置TM1638DIO引脚为推挽输出
{
   GPIO_InitTypeDef GPIO_InitStructure;
   //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
   GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void DIO_IN()  //配置TM1638DIO引脚为上拉输入
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void TM1638_Write(unsigned char	DATA)			//写数据函数
{
   unsigned char i;
   DIO_OUT();
   for(i=0;i<8;i++)
   {
   	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	  if(DATA&0X01)
	  GPIO_SetBits(GPIOB,GPIO_Pin_8);
	  else 
	  GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	  DATA>>=1;
	  GPIO_SetBits(GPIOB,GPIO_Pin_4);
	  delay_us(1);
   }
}
unsigned char TM1638_Read(void)					//读数据函数
{
	unsigned char i;
	unsigned char temp=0;
	DIO_IN();
	delay_us(1);
	for(i=0;i<8;i++)
	{
	  temp>>=1;
	  GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	  delay_ms(1);
	  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1)
	  temp|=0x80;
	  GPIO_SetBits(GPIOB,GPIO_Pin_4);
	  delay_us(1);
	}
	return temp;
}
void Write_COM(unsigned char cmd)		//发送命令字
{
	DIO_OUT();//qinyx
    GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	TM1638_Write(cmd);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}
unsigned char Read_key(void)
{
   unsigned char c[4],i,key_value=0;
   GPIO_ResetBits(GPIOB,GPIO_Pin_9);
   TM1638_Write(0x42);//开始读取健值
   delay_us(1);
   for(i=0;i<4;i++)
   {c[i]=TM1638_Read();delay_us(1);}
   GPIO_SetBits(GPIOB,GPIO_Pin_9);
   for(i=0;i<4;i++)
   key_value|=c[i]<<i;
   for(i=0;i<8;i++)
   if((0x01<<i)==key_value)break;
   return i;
}
void Write_DATA(unsigned char add,unsigned char DATA)
{
    Write_COM(0x44);
    GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	TM1638_Write(0xc0|add);
	TM1638_Write(DATA);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}
void Write_oneLED(unsigned char num,unsigned char flag)	//单独控制一个LED函数，num为需要控制的led序号，flag为0时熄灭，不为0时点亮
{
	Write_DATA(num,flag);
}
void init_TM1638(void)
{
	unsigned char i;
	Write_COM(0x8a);//脉冲宽度为全亮度的4/16
	Write_COM(0x40);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	TM1638_Write(0xc0);
	for(i=0;i<16;i++)
	TM1638_Write(0x00);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);

}

