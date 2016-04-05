#ifndef _DOT_MATRIX_H_
#define _DOT_MATRIX_H_
#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include "lcd.h"


// DIP_A: PC9   66
// DIP_B: PC7		64
// DIP_C: PA8		67
// DIP_D: PC8		65
// DIP_G: PB0		35
// DIP_DI:PC4		33
// DIP_DCLK: PB8 95
// DIP_LAT:PA1	24

/************点阵显示接口******************/
#define D_RCC           RCC_APB2Periph_GPIOC
#define D_GPIO          GPIOC
#define D_GPIO_PIN      GPIO_Pin_8
#define D_ONOFF(x)      GPIO_WriteBit(GPIOC,GPIO_Pin_8,x)

#define C_RCC           RCC_APB2Periph_GPIOA
#define C_GPIO          GPIOA
#define C_GPIO_PIN      GPIO_Pin_8
#define C_ONOFF(x)      GPIO_WriteBit(GPIOA,GPIO_Pin_8,x)

#define B_RCC           RCC_APB2Periph_GPIOC
#define B_GPIO          GPIOC
#define B_GPIO_PIN      GPIO_Pin_7
#define B_ONOFF(x)      GPIO_WriteBit(GPIOC,GPIO_Pin_7,x)

#define A_RCC           RCC_APB2Periph_GPIOC
#define A_GPIO          GPIOC
#define A_GPIO_PIN      GPIO_Pin_9
#define A_ONOFF(x)      GPIO_WriteBit(GPIOC,GPIO_Pin_9,x)

#define G_RCC           RCC_APB2Periph_GPIOB
#define G_GPIO          GPIOB
#define G_GPIO_PIN      GPIO_Pin_0
#define G_ONOFF(x)      GPIO_WriteBit(GPIOB,GPIO_Pin_0,x)

#define DI_RCC           RCC_APB2Periph_GPIOC
#define DI_GPIO          GPIOC
#define DI_GPIO_PIN      GPIO_Pin_4
#define DI_ONOFF(x)      GPIO_WriteBit(GPIOC,GPIO_Pin_4,x)

#define DCLK_RCC           RCC_APB2Periph_GPIOB
#define DCLK_GPIO          GPIOB
#define DCLK_GPIO_PIN      GPIO_Pin_8
#define DCLK_ONOFF(x)      GPIO_WriteBit(GPIOB,GPIO_Pin_8,x)

#define LAT_RCC           RCC_APB2Periph_GPIOA
#define LAT_GPIO          GPIOA
#define LAT_GPIO_PIN      GPIO_Pin_1
#define LAT_ONOFF(x)      GPIO_WriteBit(GPIOA, GPIO_Pin_1, x)


typedef struct{
    uint32_t     rcc;
    GPIO_TypeDef *gpio;
    uint16_t     pin;
}Gpio_Info;

#define DP_NUMBER          8    //点阵控制管脚

void Dot_Matric_Gpio_init(void);
void Dot_Matrix_test(void);


#endif