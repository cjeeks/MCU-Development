#ifndef _GAS_H
#define _GAS_H
//net KEY1L

#define GAS_PULLUP do{P5REN|=BIT5;}while(0)
#define GAS_DIR_IN  do{P5DIR&=~BIT5;}while(0)
#define GAS_STATE    (P5IN&BIT5)
#define IS_GAS_LOW    ((P5IN&BIT5)==0)
#define IS_GAS_HIGH    ((P5IN&BIT5)== BIT0)
#define GAS_DIROUT   do{P5DIR|=BIT5;}while(0)
#define GAS_LOW      do{P5OUT&=~BIT5;}while(0)
#define GAS_HIGH     do{P5OUT|=BIT5;}while(0)

void gas_init();
char is_gas_alarm();

#endif