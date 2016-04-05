#ifndef _DC_MOTOR_H_
#define _DC_MOTOR_H_
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include "lcd.h"

void DC_Motor_delay(u32 tim);
void DC_Motor_GPIO_Init(void);
void DC_Motor_test(void);

#endif