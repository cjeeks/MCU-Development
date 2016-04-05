#ifndef _RELAY_H
#define _RELAY_H

//#define RELAY1 P10.3
//#define RELAY2 P10.6
//#define RELAY3 P1.5
#define RELAY_1_DIR_OUT   do{P10DIR|=BIT3;}while(0)
#define RELAY_1_OUT_LOW   do{P10OUT&=~BIT3;}while(0)
#define RELAY_1_OUT_HIGHT do{P10OUT|=BIT3;}while(0)

#define RELAY_2_DIR_OUT   do{P10DIR|=BIT6;}while(0)
#define RELAY_2_OUT_LOW   do{P10OUT&=~BIT6;}while(0)
#define RELAY_2_OUT_HIGHT do{P10OUT|=BIT6;}while(0)

#define RELAY_3_DIR_OUT   do{P1DIR|=BIT5;}while(0)
#define RELAY_3_OUT_LOW   do{P1OUT&=~BIT5;}while(0)
#define RELAY_3_OUT_HIGHT do{P1OUT|=BIT5;}while(0)

void Relay_test(void);

#endif