#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "24cxx.h"
#include "touch.h"	
#include "keypad.h"
#include "relay.h"
#include "dht11.h"
#include "DC_motor.h"
#include "step_motor.h"
#include "bmp085.h"
#include "MMA7455.h"
#include "flash.h"
#include "lcd.h"
#include "PCF8574.h"
#include "enc28j60.h"
#include "Dot_Matrix.h"

  
u8 state=0;	   
void beepms(u16 va);  
void refshow(void);//刷新显示	
 


void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(lcddev.width-24,0,"RST");//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色 
}

void xianshi()//显示信息
{    
	u8 idstr[5];
	BACK_COLOR=WHITE;
	POINT_COLOR=RED;	
	LCD_ShowString(0,2,"ID:");	    
	inttohex(lcddev.id,idstr);	  
	LCD_ShowString(100,2,idstr);
}

void refshow(void)	 //刷新显示
{
	switch(state)
	{
		case 0:
		LCD_Clear(WHITE);
	    xianshi();
    	//showqq();
		break;
		case 1:
		LCD_Clear(BLACK); 
		break;
		case 2:
		LCD_Clear(RED);
		break;
		case 3:
		LCD_Clear(GREEN);
		break;
		case 4:
		LCD_Clear(BLUE);
		break;
	}	
}
void jiance(u8 key) //检测按键
{
	if(key==1)	//KEY_RIGHT按下,则执行校准程序
	{
		LCD_Clear(WHITE);//清屏
	    TP_Adjust();  //屏幕校准 
		TP_Save_Adjdata();	 
		Load_Drow_Dialog();
	}
	if(key==2)
	{
		state++;
		 if(state==5)
		 {
		 	state=0;
			abx=1;
			LCD_Init();	

		 }
		refshow();//刷新显示
	}

}	 

void beepms(u16 va)
{
	beep=1;
	delay_ms(va);
	beep=0;
}				

uint32_t address = 0;

int main(void)
{	 
	delay_init();	    	 		//延时函数初始化	 
	PCF8574_I2C_GPIO_Config();	 
			
	lcddev.bus16=1;//总线接口，0-8位总线，1-16位总线，修改8位总线之前先确定你手里的屏是否是8位接口，目前只有2.4和2.8寸才有支持8位的版本，3.2寸以上均不支持8位总线 
	lcddev.id=0x1943;//指定ID,0x1234为自动读ID,切记注意不是所有的屏都能读到ID,只有少部分驱动IC能读ID,比如4.3寸以及4.3寸以上的都不能读ID.

	delay_init();	    	 		//延时函数初始化	  
	NVIC_Configuration(); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	Uart1_init(9600);	 			//串口初始化为9600
	Uart3_init(115200);			//RFID
	Uart4_init(9600);				//MP3  
	Uart5_init(9600);				//GSM

	LCD_Init();	
	
  SPI_Flash_Init();			  //初始化Flash;	
	GPIO_SetBits(GPIOC, GPIO_Pin_0);	
	GPIO_SetBits(GPIOD, GPIO_Pin_7);	
	
		while(1)
	{
		ziku_test();
	}
	
	
	//tp_dev.init();					//触摸初始化
	
	//enc28j60_Test();			//網口測試

#if 1	                                       
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台	
	LCD_ShowString(150,60, "STEP1: KEY and GSM testing");
	LCD_ShowString(10, 200, "Press K1,K2,K3,K4, observe LED1,LED2,LED3 and information"); 		
	KEY_Test();						//STEP1: KEY test
	
		
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台	
	LCD_ShowString(150,60, "STEP2: RELAY testing");
	LCD_ShowString(150, 200, "Tips: observe the RELAY"); 		
	Relay_test();					//STEP2: RELAY test
		
#endif
		//Delay5ms();
		LCD_Clear(BLACK);
		LCD_DrawRectangle(0,5, 479, 271);
		LCD_DrawRectangle(5,18, 474, 266);
		LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台
		LCD_ShowString(30,60, "STEP3: Temperature, humidity and smoke Sensor testing");	//
		//LCD_ShowString(150, 200, ""); 
		LCD_ShowString(50, 220, "Tips: Note of the information on the screen"); 		
	while(KEY1 == 1)
	{	
		DHT11_Test();					//STEP3: DHT11 test	
		GAS_Test();
		HUMAN_Test();		
	}
		//delay_ms(500);
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台
	LCD_ShowString(180,60, "STEP4: RFID testing");
	LCD_ShowString(100, 100, "Tips: Note of the information on the screen"); 	
	RFID_Test();				  //STEP4: RFID test			
	delay_ms(500);
	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台
	LCD_ShowString(100,60, "STEP5: DC motor testing");
	LCD_ShowString(100, 100, "Tips: Observe the DC motor"); 
	while(KEY1 == 1)
	{	
		DC_Motor_test();			//STEP5: DC motor test	
	}		
		delay_ms(500);
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台
	LCD_ShowString(100,60, "STEP6: STEP motor testing");
	LCD_ShowString(100, 100, "Tips: Observe the STEP motor"); 	
	while(KEY1 == 1)
	{	
		STEP_Motor_test();		//STEP6: step_motor test	
	}
		delay_ms(500);
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台
	LCD_ShowString(100,60, "STEP7: Dot matrix testing");
	LCD_ShowString(100, 100, "Tips: Observe the Dot matrix");	
	while(KEY1 == 1)
	{	
		Dot_Matrix_test();		//STEP9: Dot_Matrix test
	}
	G_ONOFF(Bit_SET);
	delay_ms(500);
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台	
	LCD_ShowString(100,60, "STEP8: Presure and temperature testing");
	LCD_ShowString(50, 100, "Tips: Note of the information on the screen");
	while(KEY1 == 1)
	{	
		BMP085_Test();
	}
		delay_ms(500);	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台	
	LCD_ShowString(100,60, "STEP9: Acceleration testing");
	LCD_ShowString(50, 100, "Tips: Note of the information on the screen");
	while(KEY1 == 1)
	{	
		MMA7455_Test();
	}
	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台	
	LCD_ShowString(150,60, "Test complete!");
		//init_TM1638();			//keypad
		//TM1638Test();	

	while(1)
	{	

			//PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0xFF);
			//Delay5ms();
			//PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0);
			//Delay5ms();Delay5ms();Delay5ms();Delay5ms();Delay5ms();
			//Delay5ms();Delay5ms();Delay5ms();Delay5ms();		
			//Delay5ms();	
	}
}
		/*
	while(1)
	{ 
	   key=KEY_Scan(0);//扫描按键		   
	   tp_dev.scan(0); //扫描触摸		   	
			
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{
			if(state!=1)
			{
				LCD_Clear(WHITE);
			}
			while(key==0)
			{	
			
				key=KEY_Scan(0);//扫描按键
		    	tp_dev.scan(0);	
				if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
				{			
				 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
					{	
						if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)Load_Drow_Dialog();//清除
						else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,RED);		//画图	  			   
					}
				}
							
			} 			
		}	   	    
	   jiance(key);//检测按键	 
		i++;
		if(i==65000)
		{
			i=0;
			LED0=!LED0;
		}
	}
	*/
