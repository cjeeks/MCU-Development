#include "relay.h"



void Relay_Test(void)
{
	PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0xA0);
 	delayms(1000);
	 	
	PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0xC0);
	delayms(1000); 
	
	PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0x60);	
 	delayms(1000);	
	
	PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0xf0);	
 	delayms(1000);	
}