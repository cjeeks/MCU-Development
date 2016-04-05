#ifndef _LED_ARRAY_H
#define _LED_ARRAY_

//#include "macro.h"
/*
#define KEY1_PULLUP do{P6REN|=BIT3;}while(0)//上拉电阻使能
#define KEY1_OUT_H do{P6OUT|=BIT3;}while(0)//
#define KEY1_IN (P6IN&BIT3)

#define KEY2_PULLUP do{P6REN|=BIT5;}while(0)
#define KEY2_OUT_H do{P6OUT|=BIT5;}while(0)
#define KEY2_IN (P6IN&BIT5)

#define KEY3_PULLUP do{P6REN|=BIT6;}while(0)
#define KEY3_OUT_H do{P6OUT|=BIT6;}while(0)
#define KEY3_IN (P6IN&BIT6)

#define KEY4_PULLUP do{P6REN|=BIT7;}while(0)
#define KEY4_OUT_H do{P6OUT|=BIT7;}while(0)
#define KEY4_IN (P6IN&BIT7)

#define KEY5_PULLUP do{P7REN|=BIT7;}while(0)
#define KEY5_OUT_H do{P7OUT|=BIT7;}while(0)
#define KEY5_IN (P7IN&BIT7)

#define LED1_DIROUT do{P1DIR|=BIT4;}while(0)
#define LED2_DIROUT do{P1DIR|=BIT5;}while(0)
#define LED3_DIROUT do{P1DIR|=BIT6;}while(0)
#define LED4_DIROUT do{P1DIR|=BIT7;}while(0)

#define LED1_ON do{P1OUT&=~BIT4;}while(0)
#define LED1_OFF do{P1OUT|=BIT4;}while(0)
#define LED2_ON do{P1OUT&=~BIT5;}while(0)
#define LED2_OFF do{P1OUT|=BIT5;}while(0)
#define LED3_ON do{P1OUT&=~BIT6;}while(0)
#define LED3_OFF do{P1OUT|=BIT6;}while(0)
#define LED4_ON do{P1OUT&=~BIT7;}while(0)
#define LED4_OFF do{P1OUT|=BIT7;}while(0)

#define BUZZER_DIROUT do{P11DIR|=BIT2;}while(0)
#define BUZZER_ON do{P11OUT|=BIT2;}while(0)
#define BUZZER_OFF do{P11OUT&=~BIT2;}while(0)

*/
//for LED ARRAY
#define DATA_DIROUT   do{P8DIR|=BIT5;}while(0)
#define DATA_LOW      do{P8OUT&=~BIT5;}while(0)
#define DATA_HIGH     do{P8OUT|=BIT5;}while(0)

#define C_DIROUT   do{P8DIR|=BIT4;}while(0)
#define C_LOW      do{P8OUT&=~BIT4;}while(0)
#define C_HIGH     do{P8OUT|=BIT4;}while(0)

#define G_DIROUT   do{P8DIR|=BIT3;}while(0)
#define G_LOW      do{P8OUT&=~BIT3;}while(0)
#define G_HIGH     do{P8OUT|=BIT3;}while(0)

#define D_DIROUT   do{P8DIR|=BIT2;}while(0)
#define D_LOW      do{P8OUT&=~BIT2;}while(0)
#define D_HIGH     do{P8OUT|=BIT2;}while(0)

#define A_DIROUT   do{P11DIR|=BIT2;}while(0)
#define A_LOW      do{P11OUT&=~BIT2;}while(0)
#define A_HIGH     do{P11OUT|=BIT2;}while(0)

#define LATCH_DIROUT   do{P11DIR|=BIT1;}while(0)
#define LATCH_LOW      do{P11OUT&=~BIT1;}while(0)
#define LATCH_HIGH     do{P11OUT|=BIT1;}while(0)

#define B_DIROUT   do{P11DIR|=BIT0;}while(0)
#define B_LOW      do{P11OUT&=~BIT0;}while(0)
#define B_HIGH     do{P11OUT|=BIT0;}while(0)

#define CLK_DIROUT   do{P10DIR|=BIT7;}while(0)
#define CLK_LOW      do{P10OUT&=~BIT7;}while(0)
#define CLK_HIGH     do{P10OUT|=BIT7;}while(0)



extern void Init_LED_array_GPIO(void);
//extern void LED_array_ABCD_port(uchar dat);
extern void LED_array_show_font();
void LED_array_hide();
#endif