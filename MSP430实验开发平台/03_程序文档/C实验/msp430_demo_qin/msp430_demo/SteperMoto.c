#include "msp430f5438a.h"
#include "macro.h"
#include "SteperMoto.h"
void StepperMoto_IO_init(){
  MOTO_0L_OUTPUT;
  MOTO_1L_OUTPUT;
  MOTO_2L_OUTPUT;
  MOTO_3L_OUTPUT;
}

void DUJIN_port(uchar dat)
{
	//unsigned char dat=0x09;
	
    if((dat&0x01)==0x00)
         MOTO_3L_OUT_L;//   IN4_ONOFF(Bit_RESET);
    else MOTO_3L_OUT_H;//IN4_ONOFF(Bit_SET);
    
    if((dat&0x02)==0x00)
        MOTO_2L_OUT_L;//    IN3_ONOFF(Bit_RESET);
    else MOTO_2L_OUT_H;//IN3_ONOFF(Bit_SET);
    
    if((dat&0x04)==0x00)
        MOTO_1L_OUT_L;//    IN2_ONOFF(Bit_RESET);
    else MOTO_1L_OUT_H;//IN2_ONOFF(Bit_SET);
    
    if((dat&0x08)==0x00)
        MOTO_0L_OUT_L;//    IN1_ONOFF(Bit_RESET);
    else MOTO_0L_OUT_H;//IN1_ONOFF(Bit_SET);
	
}

void StepperMoto_run_clockwise(){
  uchar j;
  
  for(j=0;j<200;j++)
  {
    MOTO_3L_OUT_H;
    MOTO_2L_OUT_L;
    MOTO_1L_OUT_L;
    MOTO_0L_OUT_L;
    delay_msD(12);
    MOTO_3L_OUT_L;
    MOTO_2L_OUT_H;
    MOTO_1L_OUT_L;
    MOTO_0L_OUT_L;
    delay_msD(12);
    MOTO_3L_OUT_L;
    MOTO_2L_OUT_L;
    MOTO_1L_OUT_H;
    MOTO_0L_OUT_L;
    delay_msD(12);
    MOTO_3L_OUT_L;
    MOTO_2L_OUT_L;
    MOTO_1L_OUT_L;
    MOTO_0L_OUT_H;
    delay_msD(12); 
  }
  //STOP FOR SAVE POWER
  MOTO_3L_OUT_H;
  MOTO_2L_OUT_H;
  MOTO_1L_OUT_H;
  MOTO_0L_OUT_H;
}