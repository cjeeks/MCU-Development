#include "msp430f5438a.h"
#include "macro.h"
#include "gas.h"


void gas_init(){
  
  GAS_DIR_IN;
  // GAS_DIROUT;
  // GAS_LOW;
 // delay_s(5);
//  GAS_HIGH;
}

char is_gas_alarm(){
  if(IS_GAS_LOW) return 1;
  else return 0;
}