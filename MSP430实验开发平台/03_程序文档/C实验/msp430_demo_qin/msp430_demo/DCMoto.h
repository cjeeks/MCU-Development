#ifndef _DC_MOTO_H
#define _DC_MOTO_H

#define MOTO_1BL_PULLUP do{P7REN|=BIT7;}while(0)
#define MOTO_1BL_OUT_H do{P7OUT|=BIT7;}while(0)
#define MOTO_1BL_OUT_L do{P7OUT&=~BIT7;}while(0)
#define MOTO_1BL_INPUT do{P7DIR&=~BIT7;}while(0)
#define MOTO_1BL_OUTPUT do{P7DIR|=BIT7;}while(0)

#define MOTO_1AL_PULLUP do{P6REN|=BIT2;}while(0)
#define MOTO_1AL_OUT_H do{P6OUT|=BIT2;}while(0)
#define MOTO_1AL_OUT_L do{P6OUT&=~BIT2;}while(0)
#define MOTO_1AL_INPUT do{P6DIR&=~BIT2;}while(0)
#define MOTO_1AL_OUTPUT do{P6DIR|=BIT2;}while(0)

/*
#define MOTO_1AL_PULLUP do{P2REN|=BIT2;}while(0)
#define MOTO_1AL_OUT_H do{P2OUT|=BIT2;}while(0)
#define MOTO_1AL_OUT_L do{P2OUT&=~BIT2;}while(0)
#define MOTO_1AL_INPUT do{P2DIR&=~BIT2;}while(0)
#define MOTO_1AL_OUTPUT do{P2DIR|=BIT2;}while(0)


*/


void Dc_Moto_test();

#endif