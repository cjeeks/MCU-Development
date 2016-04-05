#include "dht11.h"
#include "delay.h"
#include "lcd.h"
#include "PCF8574.h"

//PB9  -> DHT11

typedef unsigned char  U8;       //defined for unsigned 8-bits integer variable 	  无符号8位整型变量  
typedef unsigned int   U16;      // defined for unsigned 16-bits integer variable 	  无符号16位整型变量 
unsigned char  U8FLAG,k;
unsigned char  U8count,U8temp;
unsigned char  U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
unsigned char  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
unsigned char  U8comdata;

unsigned char  indata[5];
unsigned char  count, count_r=0;
unsigned char  str[5]={"RS232"};
unsigned char  U16temp1,U16temp2;
u8 tdata[4]={0x00,0x00,0x00,0x00};
u8 sbuf;

void DTH11_OUT() 
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
   GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}

void DTH11_IN()  
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DTH11_Delay(U16 j)
    {     
			U8 i;
	    for(;j>0;j--)
	  { 	
		//for(i=0;i<27;i++);
			for(i=0;i<60;i++);

	  }
    } 
		
void  DTH11_Delay_10us(void)
{
	unsigned char i;
	i--;
	i--;
	i--;
	i--;
	i--;
	i--;
 }

void  DTH11_COM(void)
{

	unsigned char count,i;

	U8comdata=0;
	for(i=0;i<8;i++)	   
	{
		DTH11_IN();	

		while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9));
		DTH11_Delay(4);
		U8temp=0;
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))U8temp=1;

		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9));
		// while((P2_0)&&U8FLAG++);
		//超时则跳出for循环		  
		//	 if(U8FLAG==1)break;
		//判断数据位是0还是1	 
			 
		// 如果高电平高过预定0高电平值则数据位为 1 
		 
		 U8comdata<<=1;
			 U8comdata|=U8temp;        //0
	}
//U8comdata=9;
}

void DTH11_RH(void)
	{
	  //主机拉低18ms 
		DTH11_OUT();
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
       //P2_0=0;
		DTH11_Delay(2600);
		//DTH11_Delay(200);
		//DTH11_Delay(200);
	//	DTH11_Delay(200);
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
	  // P2_0=1;
	 //总线由上拉电阻拉高 主机延时20us
		DTH11_Delay(3);
	 //主机设为输入 判断从机响应信号 
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
	   //P2_0=1;
	 //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	
			DTH11_IN();
		if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))
	   //if(!P2_0)		 //T !	  
	   {
	   U8FLAG=2;
	 //判断从机是否发出 80us 的低电平响应信号是否结束	 
			 //while((!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))&&U8FLAG++);
			 while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9));  //xie
	   U8FLAG=2;
	 //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态

			//while((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))&&U8FLAG++);	
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9));		//xie			 
			//while((P2_0)&&U8FLAG++);
	 //数据接收状态		 
	   DTH11_COM();
	   U8RH_data_H_temp=U8comdata;
	   DTH11_COM();
	   U8RH_data_L_temp=U8comdata;
	   DTH11_COM();
	   U8T_data_H_temp=U8comdata;
	   DTH11_COM();
	   U8T_data_L_temp=U8comdata;
	   DTH11_COM();
	   U8checkdata_temp=U8comdata;
			 DTH11_OUT();
			 GPIO_SetBits(GPIOB,GPIO_Pin_9);
	  // P2_0=1;
	 //数据校验 
	 
	   U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
	  if(U8temp==U8checkdata_temp)
	   {
	   	  U8RH_data_H=U8RH_data_H_temp;
	   	  U8RH_data_L=U8RH_data_L_temp;
		  U8T_data_H=U8T_data_H_temp;
	   	  U8T_data_L=U8T_data_L_temp;
	   	  U8checkdata=U8checkdata_temp;
	   }//fi
	   }//fi

	}
	
void Send_DTH11(void)
{
	u8 DHT11_temp[17]={"temp_value:00.0 C"};
	u8 DHT11_humi[17]={"humi_value:00.0RH"};
	str[0]=U8RH_data_H;
	str[1]=U8RH_data_L;
	str[2]=U8T_data_H;
	str[3]=U8T_data_L;
	str[4]=U8checkdata;

	DHT11_temp[11]=(str[2]%100)/10+'0';  // 取十位 
	DHT11_temp[12]=str[2]%10+'0';        // 取个位
	LCD_ShowString(150, 140,DHT11_temp);
	
			
	DHT11_humi[11]=(str[0]%100)/10+'0';  // 取十位 
	DHT11_humi[12]=str[0]%10+'0';        // 取个位
	LCD_ShowString(150, 160,DHT11_humi);		
}

void DHT11_Test(void)
{
		DTH11_RH();
		Send_DTH11();
}

//OUTA4
void GAS_Test(void)
{
	uint8_t gas_read = 0;
	
	gas_read = PCF8574_Single_ReadI2C(PCF8574T_A);
	
	if(!(gas_read & 0x10))
		LCD_ShowString(150, 200, "********GAS IN********");	
  else LCD_ShowString(150, 200, "********GAS NO********");
}

//OUTA5
void HUMAN_Test(void)
{
	uint8_t human_read = 0;
	
	human_read = PCF8574_Single_ReadI2C(PCF8574T_A);
	
	if(!(human_read & 0x20))
		LCD_ShowString(150, 180, "*******HUMAN NO*******");
  else LCD_ShowString(150, 180, "*******HUMAN IN*******"); 
		
	
}