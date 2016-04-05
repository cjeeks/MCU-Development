#ifndef _GAS_H
#define _GAS_H
//net KEY1L

#define GAS_PULLUP do{P1REN|=BIT0;}while(0)
#define GAS_DIR_IN  do{P1DIR&=~BIT0;}while(0)
#define GAS_STATE    (P1IN&BIT0)
#define IS_GAS_LOW    ((P1IN&BIT0)==0)
#define IS_GAS_HIGH    ((P1IN&BIT0)== BIT0)
#define GAS_DIROUT   do{P1DIR|=BIT0;}while(0)
#define GAS_LOW      do{P1OUT&=~BIT0;}while(0)
#define GAS_HIGH     do{P1OUT|=BIT0;}while(0)

void gas_init();
char is_gas_alarm();

#endif