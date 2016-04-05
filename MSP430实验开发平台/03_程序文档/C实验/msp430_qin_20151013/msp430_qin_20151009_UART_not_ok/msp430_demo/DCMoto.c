#include "msp430f5438a.h"
#include "DCMoto.h"
#include "macro.h"

void clockwise_run(){
  MOTO_1BL_OUTPUT;
  MOTO_1AL_INPUT;
  MOTO_1BL_OUT_H;
}

void clockwise_stop(){
  MOTO_1BL_OUT_L;
}

void aniclockwise_run(){
  MOTO_1AL_OUTPUT;
  MOTO_1BL_INPUT;
  MOTO_1AL_OUT_H;
}
void aniclockwise_stop(){
  MOTO_1AL_OUT_L;
}

void Dc_Moto_test(){
  //clockwise_run();
  //delay_s(3);
 // clockwise_stop();
 // delay_ms(10);
  aniclockwise_run();
  delay_s(3);
  aniclockwise_stop();
  
  //MOTO_1AL_INPUT FOR SAVE POWER
 // MOTO_1AL_INPUT;
}