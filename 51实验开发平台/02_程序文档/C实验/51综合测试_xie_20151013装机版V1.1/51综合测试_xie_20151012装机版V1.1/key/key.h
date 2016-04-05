#ifndef __KEY_H
#define __KEY_H	 
#include <reg51.h>
#include <intrins.h>
#include "PCF8574T\PCF8574T.h"
#include "LCD/lcd.h"
#include "string.h"		//include : strstr()
#include <UART\UART.h>

#define KEY_UP 		4
#define KEY_LEFT	3
#define KEY_DOWN	2
#define KEY_RIGHT	1
	
sbit KEY4 = P3^2;		

extern char gsm_ch[GSM_length];
extern unsigned char BufferCount;
	
void KEY_Test(void);

#endif
