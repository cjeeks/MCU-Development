#include "msp430f5438a.h"
#include "macro.h"
#include "adc.h"

//P6.4
void adc_init(){
  //WDTCTL= WDTPW+WDTHOLD;
 // P6SEL |= 0x08;
}

unsigned char get_adc_value(){
  return 0;
}
