#ifndef _TIMER_H
#define _TIMER_H

extern void Init_Timer0_A5(void);
extern void Timer0_A5_Start(void);
extern void Timer0_A5_Stop(void);
extern unsigned char sign;//全局变量，会被main函数引用，所以此处extern
#endif