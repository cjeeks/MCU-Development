#include "DC_motor.h"

//DC_Motor1A : PE0
//DC_Motor1B : PB14

void DC_Motor_delay(u32 tim)
{
	unsigned char i;
	for(;tim>0;tim--)
	 for(i=0;i<250;i++);
}

void DC_Motor_GPIO_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		
	 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	 GPIO_SetBits(GPIOE,GPIO_Pin_0); 						 //PE.5 输出高 
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		
	 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
	 GPIO_SetBits(GPIOB,GPIO_Pin_14); 						 //PE.5 输出高 
}

void DC_Motor_test(void)
{
	GPIO_WriteBit(GPIOE,GPIO_Pin_0,SET);	
	DC_Motor_delay(1000);	
	DC_Motor_delay(1000);
	DC_Motor_delay(1000);
	GPIO_WriteBit(GPIOE,GPIO_Pin_0,RESET);
}