#include "keypad.h"
#include "lcd.h"

//本程序包含键盘模块的所有代码，包括按键和LED灯



unsigned char const tab[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};//数码管0到F的显示
													//  01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f
//unsigned char const keytab[]={01,02,16,15,17,18,00,00,03,04,14,13,19,20,00,00,05,06,12,11,21,22,00,00,07,08,10,09,23,24,00};
	unsigned char const keytab[]={0x01,0x02,0x10,0x0f,0x11,0x12,0x00,0x00,0x03,0x04,0x0e,0x0d,0x13,0x14,0x00,0x00,0x05,0x06,0x0c,0x0b,0x15,0x16,0x00,0x00,0x07,0x08,0x0a,0x09,0x17,0x18,00};														

u8 key_tmp=0xff;


void delay_tim(u32 tim)
{
	unsigned char i;
	for(;tim>0;tim--)
	 for(i=0;i<250;i++);
}
/*
//读数据延时函数
static Delay_1us_tim(int counter)
{
	int i,j;
	for(i=0;i<counter;i++)
	  for(j=0;j<33;j++);
}
*/
//STB -> PF15 -> PC6
//CLK -> PF13 -> PC7
//DIO -> PB2  -> PC8
//配置成推挽输出
void TM1638_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;        //定义GPIO初始化结构体
//f13//f15
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 
		GPIO_InitStructure.GPIO_Pin = TIM_STB | TIM_CLK;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_WriteBit(GPIOC,TIM_STB | TIM_CLK,Bit_SET);
}

void DIO_OUT() //配置TM1638 DIO引脚为推挽输出
{
   GPIO_InitTypeDef GPIO_InitStructure;

	  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 
		GPIO_InitStructure.GPIO_Pin = TIM_DIO;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_WriteBit(GPIOC,TIM_DIO,Bit_SET);
}
void DIO_IN()  //配置TM1638 DIO引脚为上拉输入
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = TIM_DIO ;
	 //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	 //GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
   //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	
   GPIO_Init(GPIOC, &GPIO_InitStructure);
}


void TM1638_Write(unsigned char	DATA)			//写数据函数
{
   unsigned char i;
   DIO_OUT();
				
   for(i=0;i<8;i++)
   {
   	GPIO_ResetBits(GPIOC,TIM_CLK);
	  if(DATA&0X01)
		{
	    GPIO_SetBits(GPIOC, TIM_DIO);
		}
	  else 
		{
	    GPIO_ResetBits(GPIOC,TIM_DIO);
		}
	  DATA>>=1;
	  GPIO_SetBits(GPIOC,TIM_CLK);
	  delay_tim(1);
   }
	 
}
unsigned char TM1638_Read(void)					//读数据函数
{
	unsigned char i;
	unsigned char temp=0;
	DIO_IN();
	delay_tim(1);
	for(i=0;i<8;i++)
	{
	  temp>>=1;
	  GPIO_ResetBits(GPIOC,TIM_CLK);
		delay_tim(10);
		if(GPIO_ReadInputDataBit(GPIOC,TIM_DIO) == Bit_SET)
	    temp|=0x80;
	  GPIO_SetBits(GPIOC,TIM_CLK);
		
		delay_tim(1);
	}
	return temp;
}
void Write_COM(unsigned char cmd)		//发送命令字
{
  GPIO_ResetBits(GPIOC,TIM_STB);
	TM1638_Write(cmd);
	GPIO_SetBits(GPIOC,TIM_STB);
}


unsigned char c[4];
unsigned char Read_key(void)
{
	unsigned char i,key_value=0;
	unsigned char tmp_num[4]={0,0,0,0};
//	int* key;
   GPIO_ResetBits(GPIOC,TIM_STB);
	TM1638_Write(0x42);
	delay_tim(1);								//xie  
	/*for(i=0;i<200;i++)
	delay_tim(200);*/
	for(i=0;i<4;i++)
	{
		c[i]=TM1638_Read();
		//delay_tim(10);
	}
	GPIO_SetBits(GPIOC,TIM_STB);				//4个字节数据合成一个字节
	for(i=0;i<4;i++)
		{
			if(c[i]!=0)
				switch(c[i])
			{
				case 0x01:tmp_num[i]=i*8+1; break;
				case 0x10:tmp_num[i]=i*8+2; break;
				case 0x02:tmp_num[i]=i*8+3; break;
				case 0x20:tmp_num[i]=i*8+4; break;
				case 0x04:tmp_num[i]=i*8+5; break;
				case 0x40:tmp_num[i]=i*8+6; break;
				case 0x08:tmp_num[i]=i*8+7; break;
				case 0x80:tmp_num[i]=i*8+8; break;
				default : tmp_num[i]=0;break;
			}
		}
		key_value=tmp_num[0]+tmp_num[1]+tmp_num[2]+tmp_num[3];
///////		
		/*key = (int *)&c[0];
	switch(*key)
	{
	  case 0x00000002:
		  key_value = 1;
	    break;
	  case 0x00000020:
		  key_value = 2;
	    break;
	  case 0x00000200:
		  key_value = 3;
	    break;
	  case 0x00002000:
		  key_value = 4;
	    break;
	  case 0x00020000:
		  key_value = 5;
	    break;
	  case 0x00200000:
		  key_value = 6;
	    break;
	  case 0x02000000:
		  key_value = 7;
	    break;
	  case 0x20000000:
		  key_value = 8;
	    break;
		case 0x00000001:
		  key_value = 9;
	    break;
	  case 0x00000010:
		  key_value = 10;
	    break;
	  case 0x00000100:
		  key_value = 11;
	    break;
	  case 0x00001000:
		  key_value = 12;
	    break;
	  case 0x00010000:
		  key_value = 13;
	    break;
	  case 0x00100000:
		  key_value = 14;
	    break;
	  case 0x01000000:
		  key_value = 15;
	    break;
	  case 0x10000000:
		  key_value = 16;
	    break;
		default :
			key_value = 0xff;
			break;
  }*/
   
  return (key_value);
}


void Write_DATA(unsigned char add,unsigned char DATA)
{
    Write_COM(0x44);
    GPIO_ResetBits(GPIOC,TIM_STB);
	TM1638_Write(0xc0|add);
	TM1638_Write(DATA);
	GPIO_SetBits(GPIOC,TIM_STB);
}
void Write_oneLED(unsigned char num,unsigned char flag)	//单独控制一个LED函数，num为需要控制的led序号，flag为0时熄灭，不为0时点亮
{
	Write_DATA(num,flag);
}
void init_TM1638(void)
{	
	unsigned char i;
	
	TM1638_GPIO_Configuration();   //IO口初始化

	Write_COM(0x8a);//脉冲宽度为全亮度的4/16
	Write_COM(0x40);
	GPIO_ResetBits(GPIOC,TIM_STB);
	TM1638_Write(0xc0);
	for(i=0;i<16;i++)
	TM1638_Write(0x00);
	GPIO_SetBits(GPIOC,TIM_STB);

	DIO_OUT();
}


/****************************************************************************
* 名    称：void TM1638Test(void)
* 功    能：显示主菜单
* 入口参数：无
* 出口参数：无
* 说    明：在LCD上显示8LED测试菜单
* 调用方法：TM1638Test();
****************************************************************************/

void TM1638Test(void)
{
	u8 i,j;
	u8 keyDat;
//	u8 tempcount=0;
	u8 temp_key1=0x00;
	u8 temp_key2=0x00;
	u8 temp_key3=0x00;
	init_TM1638();	
	for(i=0;i<16;i++)
	{
	  for(j=0;j<8;j++)
	  Write_DATA(j<<1,tab[i]); 
	  delay_tim(5000);
	}

	for(j=0;j<8;j++)
	  Write_DATA(j<<1,tab[0]); 
	
	for(i=0;i<16;i++)
	{ i++;
	  for(j=0;j<3;j++)
		{
		Write_oneLED(i,j);
	  delay_tim(5000);
		}
	}
	
	//while(tempcount<24)
	//while(1)
	temp_key1=0x00;
	temp_key2=0x00;
	temp_key3=0x00;
	while((temp_key1!=0xff)||(temp_key2!=0xff)||(temp_key3!=0xff))
	{
		keyDat=Read_key();
		keyDat=keytab[keyDat-1];
		if(keyDat<0x1f)
		{   	printf("%c\n",keyDat);
					//for(j=0;j<8;j++)
	  Write_DATA(2,tab[keyDat&0x0f]);
			Write_DATA(0,tab[(keyDat&0xf0)>>4]);
			if(keyDat!=key_tmp)
			{
			//tempcount++;
				key_tmp=keyDat;
			}
			switch (keyDat){
				case 0x01:
				LCD_ShowString(120, 120, "KEY_ID:KEY01");
				temp_key1=temp_key1|0x01;
				break;
				case 0x02:
				LCD_ShowString(120, 120, "KEY_ID:KEY02");
				temp_key1=temp_key1|0x02;
				break;
				case 0x03:
				LCD_ShowString(120, 120, "KEY_ID:KEY03");
				temp_key1=temp_key1|0x04;
				break;
				case 0x04:
				LCD_ShowString(120, 120, "KEY_ID:KEY04");
				temp_key1=temp_key1|0x08;
				break;
				case 0x05:
				LCD_ShowString(120, 120, "KEY_ID:KEY05");
				temp_key1=temp_key1|0x10;
				break;
				case 0x06:
				LCD_ShowString(120, 120, "KEY_ID:KEY06");
				temp_key1=temp_key1|0x20;
				break;
				case 0x07:
				LCD_ShowString(120, 120, "KEY_ID:KEY07");
				temp_key1=temp_key1|0x40;
				break;
				case 0x08:
				LCD_ShowString(120, 120, "KEY_ID:KEY08");
				temp_key1=temp_key1|0x80;
				break;
				//
				case 0x09:
				LCD_ShowString(120, 120, "KEY_ID:KEY09");
				temp_key2=temp_key2|0x01;
				break;
				case 0x0a:
				LCD_ShowString(120, 120, "KEY_ID:KEY0A");
				temp_key2=temp_key2|0x02;
				break;
				case 0x0b:
				LCD_ShowString(120, 120, "KEY_ID:KEY0B");
				temp_key2=temp_key2|0x04;
				break;
				case 0x0c:
				LCD_ShowString(120, 120, "KEY_ID:KEY0C");
				temp_key2=temp_key2|0x08;
				break;
				case 0x0d:
				LCD_ShowString(120, 120, "KEY_ID:KEY0D");
				temp_key2=temp_key2|0x10;
				break;
				case 0x0e:
				LCD_ShowString(120, 120, "KEY_ID:KEY0E");
				temp_key2=temp_key2|0x20;
				break;
				case 0x0f:
				LCD_ShowString(120, 120, "KEY_ID:KEY0F");
				temp_key2=temp_key2|0x40;
				break;
				case 16:
				LCD_ShowString(120, 120, "KEY_ID:KEY10");
				temp_key2=temp_key2|0x80;
				break;
			//
				case 0x11:
				LCD_ShowString(120, 120, "KEY_ID:KEY11");
				temp_key3=temp_key3|0x01;
				break;
				case 0x12:
				LCD_ShowString(120, 120, "KEY_ID:KEY12");
				temp_key3=temp_key3|0x02;
				break;
				case 0x13:
				LCD_ShowString(120, 120, "KEY_ID:KEY13");
				temp_key3=temp_key3|0x04;
				break;
				case 0x14:
				LCD_ShowString(120, 120, "KEY_ID:KEY14");
				temp_key3=temp_key3|0x08;
				break;
				case 0x15:
				LCD_ShowString(120, 120, "KEY_ID:KEY15");
				temp_key3=temp_key3|0x10;
				break;
				case 0x16:
				LCD_ShowString(120, 120, "KEY_ID:KEY16");
				temp_key3=temp_key3|0x20;
				break;
				case 0x17:
				LCD_ShowString(120, 120, "KEY_ID:KEY17");
				temp_key3=temp_key3|0x40;
				break;
				case 0x18:
				LCD_ShowString(120, 120, "KEY_ID:KEY18");
				temp_key3=temp_key3|0x80;
				break;
				
								
				default:
				break;
			}
}
}
}


