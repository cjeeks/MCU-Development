#include "DC_motor.h"

//OUTE1 E4
void DC_motor_Test(void)
{  
	PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0xff);		//0xe2
 	delayms(500);  	
	delayms(500);
	delayms(500);
	PCF8574_Single_WriteI2C(UE_PCF8574_SlaveAddress,0xe0);

}