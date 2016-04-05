#ifndef _SPI_H
#define _SPI_H
#include <stdbool.h>

#define UCB2_SPI_RESET  do{UCB2CTL1|=BIT0;}while(0) //Enabled. USCI logic held in reset state.
#define UCB2_SPI_UNRESET  do{UCB2CTL1&=~BIT0;}while(0)//Disabled. USCI reset released for operation.
#define SSN_DIROUT do{P9DIR|=BIT0;}while(0)
#define SSN_LOW do{P9OUT&=~BIT0;}while(0)//Ƭѡ
#define SSN_HIGH do{P9DIR|=BIT0;}while(0)//��Ƭѡ

extern void SPI_Init(void);
extern bool SD_Init(void);
extern bool SD_Block_W(unsigned char *, unsigned long);
extern bool SD_Block_R(unsigned char *, unsigned long);

#endif