#ifndef _WATCHDOG1_H
#define _WATCHDOG1_H

#define WDT_STOP  do{WDTCTL = WDTPW+WDTHOLD;}while(0)
#define WDT_CLEAR  do{WDTCTL|= WDTPW+WDTCNTCL;}while(0)
#define WDT_INTENABLE  do{SFRIE1|=WDTIE;}while(0) // 使能WDT中断
#define WDT_INTDISABLE  do{SFRIE1&=~WDTIE;}while(0) // 禁能WDT中断

extern void WatchDog_init1(void);

#endif