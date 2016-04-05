#ifndef _RELAY_H_
#define _RELAY_H_
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

void Relay_delay_tim(u32 tim);
void Relay_Gpio_Init(void);
void Relay_test(void);

#endif
