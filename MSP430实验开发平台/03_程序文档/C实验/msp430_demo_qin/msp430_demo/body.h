#ifndef _BODY_H
#define _BODY_H
//net KEY1L

#define BODY_PULLUP do{P7REN|=BIT3;}while(0)
#define BODY_DIR_IN  do{P7DIR&=~BIT3;}while(0)
#define BODY_STATE    (P7IN&BIT3)
#define IS_BODY_LOW    ((P7IN&BIT3)==0)
#define IS_BODY_HIGH    ((P7IN&BIT3)== BIT3)
#define BODY_DIROUT   do{P7DIR|=BIT3;}while(0)
#define BODY_LOW      do{P7OUT&=~BIT3;}while(0)
#define BODY_HIGH     do{P7OUT|=BIT3;}while(0)

void BODY_init();
char is_BODY_alarm();

#endif