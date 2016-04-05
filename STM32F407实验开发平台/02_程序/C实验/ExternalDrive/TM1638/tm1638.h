#ifndef __TM1638_H
#define __TM1638_H 			   
//#include "stm32f10x.h"
void TM1638_Write(unsigned char	DATA);
unsigned char TM1638_Read(void); 
void Write_COM(unsigned char cmd);
unsigned char Read_key(void);
void Write_DATA(unsigned char add,unsigned char DATA);
void Write_oneLED(unsigned char num,unsigned char flag);
void init_TM1638(void);	
void TM1638_GPIO_Configuration(void);

#endif									   





























