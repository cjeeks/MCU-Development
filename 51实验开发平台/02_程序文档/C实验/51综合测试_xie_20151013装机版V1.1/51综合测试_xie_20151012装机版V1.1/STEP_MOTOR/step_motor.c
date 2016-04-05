#include "step_motor.h"

u8 F_Rotation[8]={0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09};		//

void delayus(int count)  // /* X1us */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1;j++);
}

//操作步进电机时需要把继电器的相关IO清零，还有直流电机的IO也要清零
void DUJIN_port(u8 dat)
{
		u8 read_value = 0;

	//unsigned char dat=0x09;
		if((dat&0x08)==0x00)	  //OUTE2
		//IN2_ONOFF(Bit_RESET);
		{
		   PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0x01); //& read_value
		}
		else 
		//IN2_ONOFF(Bit_SET);
		 {  
		   PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0x04 );	//| read_value	
		 }
		if((dat&0x04)==0x00)	  //OUTE0
		//IN4_ONOFF(Bit_RESET);
		 { 
		   PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0x04 );//& read_value
		 }
		else 
		//IN4_ONOFF(Bit_SET);	
		{	
		   PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,1 );//| read_value
		}   		
		if((dat&0x02)==0x00)	  //OUTC0
		//IN3_ONOFF(Bit_RESET);
		 {  
		   PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress,0xF6);//& read_value
		 }
		else 
		//IN3_ONOFF(Bit_SET);
		{
		   PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress,1 );		//| read_value
		}
		
		if((dat&0x01)==0x00)	  //OUTG7
		//IN1_ONOFF(Bit_RESET);
		{
		   PCF8574_Single_WriteI2C(UG_PCF8574_SlaveAddress,0x77);	// & read_value	
		}
		else 
		//IN1_ONOFF(Bit_SET);
		{
		   PCF8574_Single_WriteI2C(UG_PCF8574_SlaveAddress,0x80);	//| read_value	
		}
}

void STEP_motor_test(void)
{
	u8 i = 0,j = 0;

    for(j=0; j<90; j++)
		for(i = 0; i < 8; i ++)
		{
			DUJIN_port(F_Rotation[i]);
			delayus(200);
		}
		
	DUJIN_port(0x00); //        8214

}
