#ifndef _STEP_MOTOR_H_
#define _STEP_MOTOR_H_

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include "lcd.h"

/************步进电机控制管脚******************/
//PD12  PG2   PG4  PD11  OLD
//PF3   PF4   PE5  PE3   OLD
//PE6   PD12  PD6  PE5   NEW
 
#define IN1_RCC           RCC_AHB1Periph_GPIOE
#define IN1_GPIO          GPIOE
#define IN1_GPIO_PIN      GPIO_Pin_5
#define IN1_ONOFF(x)      GPIO_WriteBit(GPIOE,GPIO_Pin_5,x)

#define IN2_RCC           RCC_AHB1Periph_GPIOE
#define IN2_GPIO          GPIOE
#define IN2_GPIO_PIN      GPIO_Pin_6
#define IN2_ONOFF(x)      GPIO_WriteBit(GPIOE,GPIO_Pin_6,x)

#define IN3_RCC           RCC_AHB1Periph_GPIOD
#define IN3_GPIO          GPIOD
#define IN3_GPIO_PIN      GPIO_Pin_6
#define IN3_ONOFF(x)      GPIO_WriteBit(GPIOD,GPIO_Pin_6,x)

#define IN4_RCC           RCC_AHB1Periph_GPIOD
#define IN4_GPIO          GPIOD
#define IN4_GPIO_PIN      GPIO_Pin_12
#define IN4_ONOFF(x)      GPIO_WriteBit(GPIOD,GPIO_Pin_12,x)

void STEP_Motor_delay(u32 tim);
void STEP_Motor_GPIO_Init(void);
void BUJIN_port(u8 dat);
void STEP_Motor_test(void);

#endif