#ifndef _STEPPER_MOTO_H
#define _STEPPER_MOTO_H

#define MOTO_0L_OUT_H do{P6OUT|=BIT3;}while(0)
#define MOTO_0L_OUT_L do{P6OUT&=~BIT3;}while(0)
#define MOTO_0L_OUTPUT do{P6DIR|=BIT3;}while(0)
#define MOTO_0L_INPUT do{P6DIR&=~BIT3;}while(0)

#define MOTO_1L_OUT_H do{P6OUT|=BIT7;}while(0)
#define MOTO_1L_OUT_L do{P6OUT&=~BIT7;}while(0)
#define MOTO_1L_OUTPUT do{P6DIR|=BIT7;}while(0)
#define MOTO_1L_INPUT do{P6DIR&=~BIT7;}while(0)

#define MOTO_2L_OUT_H do{P7OUT|=BIT5;}while(0)
#define MOTO_2L_OUT_L do{P7OUT&=~BIT5;}while(0)
#define MOTO_2L_OUTPUT do{P7DIR|=BIT5;}while(0)
#define MOTO_2L_INPUT do{P7DIR&=~BIT5;}while(0)

#define MOTO_3L_OUT_H do{P6OUT|=BIT0;}while(0)
#define MOTO_3L_OUT_L do{P6OUT&=~BIT0;}while(0)
#define MOTO_3L_OUTPUT do{P6DIR|=BIT0;}while(0)
#define MOTO_3L_INPUT do{P6DIR&=~BIT0;}while(0)


void StepperMoto_IO_init();
void StepperMoto_run_clockwise();

#endif