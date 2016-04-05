#ifndef _BODY_H
#define _BODY_H
//net KEY1L

#define BODY_PULLUP do{P5REN|=BIT4;}while(0)
#define BODY_DIR_IN  do{P5DIR&=~BIT4;}while(0)
#define BODY_STATE    (P5IN&BIT4)
#define IS_BODY_LOW    ((P5IN&BIT4)==0)
#define IS_BODY_HIGH    ((P5IN&BIT4)== BIT4)
#define BODY_DIROUT   do{P5DIR|=BIT4;}while(0)
#define BODY_LOW      do{P5OUT&=~BIT4;}while(0)
#define BODY_HIGH     do{P5OUT|=BIT4;}while(0)

void BODY_init();
char is_BODY_alarm();

#endif