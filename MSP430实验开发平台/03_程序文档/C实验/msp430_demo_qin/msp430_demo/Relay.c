#include "msp430f5438a.h"
#include "macro.h"
#include "Relay.h"

void Relay_test(void)
{
  //init 
  RELAY_1_DIR_OUT;
  RELAY_1_OUT_HIGHT;
  RELAY_2_DIR_OUT;
  RELAY_2_OUT_HIGHT;
  RELAY_3_DIR_OUT;
  RELAY_3_OUT_HIGHT;
  
  delay_s(1);
  RELAY_1_OUT_LOW;
  delay_s(1);
  RELAY_2_OUT_LOW;
  delay_s(1);
  RELAY_3_OUT_LOW;
  
  delay_s(1);
  RELAY_1_OUT_HIGHT;
  delay_s(1);
  RELAY_2_OUT_HIGHT;
  delay_s(1);
  RELAY_3_OUT_HIGHT;
   
  
}
