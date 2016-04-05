#include "msp430f5438a.h"
#include "macro.h"
#include "body.h"

void BODY_init(){
  //BODY_DIROUT;
 //BODY_LOW;
  //BODY_HIGH;
  BODY_DIR_IN;
}

char is_BODY_alarm(){
  if(IS_BODY_HIGH) return 0;
  else return 1;
}