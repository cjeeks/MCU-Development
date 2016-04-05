#ifndef __DHT11_H
#define __DHT11_H 			   
#include "stm32f10x.h"
extern unsigned char sbuf;
extern  unsigned char tdata[4];

unsigned char start_DHT11(void);
void DTH11_OUT(void); //配置TM1638DIO引脚为推挽输出
unsigned long DHT11_Get_Data(void);//获取数据
void DTH11_RH(void);
void Send_DTH11(void);
void  DTH11_COM(void);
void DHT11_Test(void);
#endif									   





























