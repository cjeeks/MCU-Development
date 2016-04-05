#ifndef __DHT11_H
#define __DHT11_H 		
/*
#define DTH11_PULLUP do{P8REN|=BIT6;}while(0)
#define DTH11_PULL_DOWN do{P8REN&=~BIT6;}while(0)
#define DTH11_DIRIN  do{P8DIR&=~BIT6;}while(0)
#define DTH11_STATE    (P8IN&BIT6)
#define IS_DTH11_LOW    ((P8IN&BIT6)==0)
#define IS_DTH11_HIGH    ((P8IN&BIT6)== BIT6)
#define DTH11_DIROUT   do{P8DIR|=BIT6;}while(0)
#define DTH11_LOW      do{P8OUT&=~BIT6;}while(0)
#define DTH11_HIGH     do{P8OUT|=BIT6;}while(0)
*/
#define DTH11_PULLUP do{P11REN|=BIT1;}while(0)
#define DTH11_PULL_DOWN do{P11REN&=~BIT1;}while(0)
#define DTH11_DIRIN  do{P11DIR&=~BIT1;}while(0)
#define DTH11_STATE    (P11IN&BIT1)
#define IS_DTH11_LOW    ((P11IN&BIT1)==0)
#define IS_DTH11_HIGH    ((P11IN&BIT1)== BIT1)
#define DTH11_DIROUT   do{P11DIR|=BIT1;}while(0)
#define DTH11_LOW      do{P11OUT&=~BIT1;}while(0)
#define DTH11_HIGH     do{P11OUT|=BIT1;}while(0)
//#include "stm32f10x.h"
//extern unsigned char sbuf;
//extern  unsigned char tdata[4];

unsigned char start_DHT11(void);

unsigned long DHT11_Get_Data(void);//获取数据
void DTH11_RH(void);
void Send_DTH11(void);
void  DTH11_COM(void);

extern unsigned char  u8T_data_H,u8T_data_L,u8RH_data_H,u8RH_data_L,u8checkdata;
#endif									   

