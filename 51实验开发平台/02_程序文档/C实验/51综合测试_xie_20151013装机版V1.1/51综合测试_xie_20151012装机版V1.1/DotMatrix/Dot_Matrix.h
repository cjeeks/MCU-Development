#ifndef _DOT_MATRIX_H_
#define _DOT_MATRIX_H_
#include <reg51.h>
#include <intrins.h>
#include <sys\sys.h>
#include "lcd/lcd.h"
#include <PCF8574T\PCF8574T.h>



#define Bit_RESET 		0
#define Bit_SET   		1

#define read(y) 		PCF8574_Single_ReadI2C(y)
 /*
#define D_ONOFF(x)      	  //OUTF4
#define C_ONOFF(x)      	  //OUTG0	
#define B_ONOFF(x)      	  //OUTF7
#define A_ONOFF(x)       	  //OUTF5
#define G_ONOFF(x)       	  //OUTF0
#define DI_ONOFF(x)      	  //OUTF2
#define DCLK_ONOFF(x)    	  //OUTG1
#define LAT_ONOFF(x)     	  //OUTG3
   */
#define A_ONOFF(Bit_RESET) 		PCF8574_Single_WriteI2C(UF_PCF8574_SlaveAddress,(~(1 << 5)) & read_value)
#define A_ONOFF(Bit_SET)

void Dot_Matric_Gpio_init(void);
void Dot_Matrix_test(void);


#endif