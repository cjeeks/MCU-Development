#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f4xx.h"

void SysTick_Init(void);
void Delay(uint32_t nTime);
void TimingDelay_Decrement(void);

#endif
