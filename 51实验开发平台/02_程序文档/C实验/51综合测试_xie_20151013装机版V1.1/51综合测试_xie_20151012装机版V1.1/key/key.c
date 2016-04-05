#include "key.h"
#include <UART\UART.h>
						
u8 play[4]  = {0x7E, 0x02, 0x0D, 0xEF};
u8 prev[4]  = {0x7E, 0x02, 0x02, 0xEF};
u8 next[4]  = {0x7E, 0x02, 0x01, 0xEF};
u8 pause[4] = {0x7E, 0x02, 0x0E, 0xEF};

u8 mode_U[5] = 			{0x7E, 0x03, 0x09, 0, 0xEF};
u8 mode_FLASH[5] =  {0x7E, 0x03, 0x09, 4, 0xEF}; 
u8 mode_TF[5] = 		{0x7E, 0x03, 0x09, 1, 0xEF};	



void KEY_Test(void)
{
	u8 i = 0;
	
	unsigned char key_flag = 0;
	unsigned char read_val = 0;
	LCD_Clear(BLACK);
	LCD_DrawRectangle(0,5, 479, 271);
	LCD_DrawRectangle(5,18, 474, 266);
	LCD_ShowString(150, 6, "--STC51 Platform--");  // 实验开发平台
	LCD_ShowString(150,60, "Step 1:Key and Led Testing");
	LCD_ShowString(150, 100,"Press K1,K2,K3,K4,Seee the LED"); 		 
	
	while(key_flag != 0x0F)
	{					
		
		LCD_ShowNum(150, 80,uart_flag, 0);
		
		if(strstr((const char*)gsm_ch, "OK"))
			LCD_ShowString(200, 150, "GSM_OK!"); 
		
		if(KEY4 == 0)				// K1   1110 0111
		{
			delayms(20);
			if(KEY4 == 0)
			{
				//Uart1_SendData('1');
				while(!KEY4);
				key_flag |= 0x01;
				PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress, 0xE7);	
				
				Uart2_SendString("AT\r\n");					//GSM test
				
				//Uart1_SendString(mode_FLASH);	  		//MP3 test
				//Delay5ms();
				Uart1_SendString(play);	  		//MP3 test
			}
		}
	read_val = PCF8574_Single_ReadI2C(UD_PCF8574_SlaveAddress);	
/////////////////////////////////////////			
		if((read_val & 0x80) == 0)	//OUTC1				   K2  1110 0101
		{
			key_flag |= 0x08;	
			Uart1_SendData('2');			
			PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress, 0xE5);	///led2 buzzer  1111 0011
		}
/////////////////////////////////////////
	
/////////////////////////////////////////
		if((read_val & 0x40) == 0)	//OUTC2				   K3  1110 0001 
		{
			Uart1_SendData('3');
			key_flag |= 0x04;		
			PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress, 0xE1);	///led1  buzzer   1110 0111
		}
/////////////////////////////////////////		
		if((read_val & 0x20) == 0)	//OUTC5         K4  LED2 1111 0111
		{
			Uart1_SendData('4');	
			key_flag |= 0x02;			
			PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress, 0xF7);	//led off!  1111 0101
			
		}
		
		if(strstr((const char*)gsm_ch, "OK"))
			LCD_ShowString(200, 150, "GSM_OK!"); 

	}           
		for(i; i < GSM_length; i++)
		gsm_ch[i] = 0;
		
	for(i=0;i<BufferCount;i++)
			BufferA[i]=0x00;
	
		BufferCount=0;
		uart_flag = 0;

}

