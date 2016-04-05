#include "relay.h"
#include "lcd.h"

//PE3 PE2 PB5 -> 3 RELAY

void Relay_delay_tim(u32 tim)
{
	unsigned char i;
	for(;tim>0;tim--)
	 for(i=0;i<250;i++);
}

void Relay_Gpio_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_3 | GPIO_Pin_2); 						 //PE.5 输出高 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	
 GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOB,GPIO_Pin_5); 						 //PE.5 输出高 	
};

void Relay_test(void)
{
	Relay_Gpio_Init();
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_3); 					
	Relay_delay_tim(20000);	
	GPIO_SetBits(GPIOE,GPIO_Pin_3); 					
	Relay_delay_tim(20000);

	GPIO_ResetBits(GPIOE,GPIO_Pin_2); 					
	Relay_delay_tim(20000);	
	GPIO_SetBits(GPIOE,GPIO_Pin_2); 					
	Relay_delay_tim(20000);

	GPIO_ResetBits(GPIOB,GPIO_Pin_5); 					
	Relay_delay_tim(20000);		
	GPIO_SetBits(GPIOB,GPIO_Pin_5); 					
	Relay_delay_tim(20000);

}
