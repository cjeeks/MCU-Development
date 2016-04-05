#ifndef _RELAY_H
#define _RELAY_H

//#define RELAY1 P10.3
//#define RELAY2 P10.6
//#define RELAY3 P1.5
#define RELAY_2_DIR_OUT   do{P6DIR|=BIT0;}while(0)
#define RELAY_2_OUT_LOW   do{P6OUT&=~BIT0;}while(0)
#define RELAY_2_OUT_HIGHT do{P6OUT|=BIT0;}while(0)

#define RELAY_3_DIR_OUT   do{P6DIR|=BIT1;}while(0)
#define RELAY_3_OUT_LOW   do{P6OUT&=~BIT1;}while(0)
#define RELAY_3_OUT_HIGHT do{P6OUT|=BIT1;}while(0)

#define RELAY_1_DIR_OUT   do{P6DIR|=BIT2;}while(0)
#define RELAY_1_OUT_LOW   do{P6OUT&=~BIT2;}while(0)
#define RELAY_1_OUT_HIGHT do{P6OUT|=BIT2;}while(0)

void Relay_test(void);

#endif