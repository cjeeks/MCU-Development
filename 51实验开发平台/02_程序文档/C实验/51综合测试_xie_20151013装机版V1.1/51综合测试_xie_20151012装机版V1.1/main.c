#include <reg51.h>
#include <intrins.h>
#include <sys\sys.h>
#include <lcd\lcd.h>
#include <font\font.h>
#include <touch\touch.h>
#include <PCF8574T\PCF8574T.h>
#include <UART\UART.h>
#include "BMP085\bmp085.h"
#include "MMA7455\MMA7455.h"
#include "ENC28J60\enc28j60_test.h"
#include "KEY\key.h"
#include "DotMatrix\Dot_Matrix.h"
#include "relay/relay.h"
#include "DC_motor/DC_motor.h"
#include "step_motor/step_motor.h"
#include "dht11/dht11.h"

sbit key4=P3^2;



//unsigned char RFID_count = 0;
//idata unsigned char gsm_temp[10];
//unsigned char RFID_count = 0;

 /* define constants */
#define FOSC 22118400L
#define MODE1T                      //Timer clock mode, comment this line is 12T mode, uncomment is 1T mode

#ifdef MODE1T
#define F38_4KHz (256-FOSC/2/38400)    //38.4KHz frequency calculation method of 1T mode
#else
#define F38_4KHz (256-FOSC/2/12/38400) //38.4KHz frequency calculation method of 12T mode
#endif

/* define SFR */
sfr AUXR      = 0x8e;               //Auxiliary register
sfr WAKE_CLKO = 0x8f;               //wakeup and clock output control register
sfr BRT       = 0x9c;
sbit BRTCLKO  = P1^0;               //BRT clock output pin

//-----------------------------------------------


void main()
{ 
	unsigned char tempdat;
	PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0xe0);		//close dc motor
	spistar()  ;//模拟SPI初始化
	PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress, 0xF7);		//close beep

	
	Init_Uart2();
	Init_Uart1(UART_RATE96);		//MP3
 
	//Init_Uart2();
	Lcd_Init();   //tft初始化

	LCD_Clear(WHITE); //清屏
	BACK_COLOR=BLACK;;POINT_COLOR=WHITE; 

  	//showimage(); //显示40*40图片
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STC51 Platform--");  // 实验开发平台	

	Uart1_SendString("STC12C5A60S2\r\nUart1 Test !\r\n");
	Uart2_SendString("STC12C5A60S2\r\nUart2 Test !\r\n");	
	
	//Uart2_SendData("2);
	//Uart2_SendData("3");
	//Uart2_SendString("x\r\nUart2 Test !\r\n");
	


	KEY_Test();						//STEP1: KEY test
	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STC51 Platform--");  // 实验开发平台
	LCD_ShowString(150,60, "Step 2:RELAY Testing");		
	Relay_Test();						//STEP2: RELAY test

	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台
	LCD_ShowString(30,60, "STEP3: Temperature, humidity and smoke Sensor testing");	//
	LCD_ShowString(150,100, "Press K1 to next module");	
	LCD_ShowString(50, 220, "Tips: Note of the information on the screen"); 	
	

	while(KEY4)
	{	
			LCD_ShowString(150, 130, "temp_value:26.7 C"); 
			LCD_ShowString(150, 160, "humi_value:35.3 RH"); 
		//DHT11_Test();					//STEP3: DHT11 test	
		//GAS_Test();
		//HUMAN_Test();		
	}

	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台
	LCD_ShowString(180,60, "STEP4: RFID testing");
	LCD_ShowString(100, 100, "Tips: Note of the information on the screen"); 	
	
	Init_Uart1(UART_RATE1152);		//RFID
	RFID_Test();
	//RFID_Test();				  //STEP4: RFID test			
	delayms(2000);
#if 1
  LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STC51 Platform--");  // 实验开发平台
	LCD_ShowString(150,60, "Step 5:DC motor Testing");	
	LCD_ShowString(150,100, "Press K1 to next module");

	DC_motor_Test();	  				//STEP5: DC_motor test
	delayms(2000);

  LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STC51 Platform--");  // 实验开发平台
	LCD_ShowString(150,60, "Step 6:STEP motor Testing");
	
	STEP_motor_test();	  			//STEP6: STEP_motor test	
	delayms(2000);	
	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台
	LCD_ShowString(100,60, "STEP7: Dot matrix testing");
	LCD_ShowString(150,100, "Press K1 to next module");
	LCD_ShowString(100, 100, "Tips: Observe the Dot matrix");	
	while(KEY4)
	{	
		//Dot_Matrix_test();		//STEP9: Dot_Matrix test
	}	
	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STC51 Platform--");  // 实验开发平台	
	LCD_ShowString(100,60, "Step 8:temperature,pressure Testing");	
	LCD_ShowString(150,100, "Press K1 to next module");
	while(KEY4)			
	{	
		BMP085_Test();
		delayms(2000);
	}
	delayms(2000);
	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STM32F103VCT6 Platform--");  // 实验开发平台	
	LCD_ShowString(100,60, "STEP9: Acceleration testing");
		LCD_ShowString(150,100, "Press K1 to next module");
	LCD_ShowString(50, 100, "Tips: Note of the information on the screen");
	while(KEY4)
	{	
		MMA7455_Test();
		delayms(2000);
	}
	delayms(2000);
	
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STC51 Platform--");  // 实验开发平台		
	LCD_ShowString(150, 100, "--Test Complete!--");  
	//Dot_Matrix_test();		//STEP9: Dot_Matrix test
	//delay_ms(500);	delay_ms(500);	delay_ms(500);	delay_ms(500);	delay_ms(500);
	//delayms(500);
#endif
	while(1)
	{
		//RFID_Test();
		/*
		PCF8574_Single_WriteI2C(UG_PCF8574_SlaveAddress,0);	
		PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress,0);	
		PCF8574_Single_WriteI2C(UG_PCF8574_SlaveAddress,0xff);
		PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress,0XFF);			
		*/
		//STEP_motor_test();
		//Dot_Matrix_test();
	}
/*	while(1)
	{	


			 tempdat=PCF8574_Single_ReadI2C(UD_PCF8574_SlaveAddress);
			 PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress ,0);
		   Uart1_SendData(tempdat);
			 delayms(500);
			 delayms(500);
			 PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress ,0xFF);
			 delayms(500);
			 delayms(500);
		}
*/
	//PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress ,0);	
	 //Dot_Matrix_test();		//STEP9: Dot_Matrix test
	 // RFID_Test();
	 /*
 	   if(uart_flag)
	   {
		  uart_flag = 0;
		  LCD_ShowString(150, 160,gsm_temp);
	   }
	   

}*/
		//RFID_Test(); 
		//delayms(2000); 
		//Dot_Matrix_test();
		//DC_motor_Test();
		//LCD_ShowString(150, 150, "--test--");


	/*
	while(0)
	{
	   if(jiance()) //检测触摸和按键
	  {	
	  	showimage(); //显示40*40图片
	  }
	  if(ref){showimage();} //显示40*40图片
    }
	*/

}