#ifndef _GPIO_H_
#define _GIPO_H_

#define LED_NUMBER         4    //LED总数
#define KEY_NUMBER         5    //按键总数
/************LED灯接口******************/
#define LED1_RCC           RCC_AHB1Periph_GPIOA
#define LED1_GPIO          GPIOA
#define LED1_GPIO_PIN      GPIO_Pin_6
#define LED1_ONOFF(x)      GPIO_WriteBit(GPIOA,GPIO_Pin_6,x)

#define LED2_RCC           RCC_AHB1Periph_GPIOA
#define LED2_GPIO          GPIOA
#define LED2_GPIO_PIN      GPIO_Pin_4
#define LED2_ONOFF(x)      GPIO_WriteBit(GPIOA,GPIO_Pin_4,x)

#define LED3_RCC           RCC_AHB1Periph_GPIOB
#define LED3_GPIO          GPIOB
#define LED3_GPIO_PIN      GPIO_Pin_6
#define LED3_ONOFF(x)      GPIO_WriteBit(GPIOB,GPIO_Pin_6,x)

#define LED4_RCC           RCC_AHB1Periph_GPIOC
#define LED4_GPIO          GPIOC
#define LED4_GPIO_PIN      GPIO_Pin_6
#define LED4_ONOFF(x)      GPIO_WriteBit(GPIOC,GPIO_Pin_6,x)
/************按键接口******************/
#define KEY_S1_RCC         RCC_AHB1Periph_GPIOB
#define KEY_S1_GPIO        GPIOB
#define KEY_S1_GPIO_PIN    GPIO_Pin_2
#define KEY_S1_UPDOWM()    GPIO_ReadInputDataBit(KEY_S1_GPIO,KEY_S1_GPIO_PIN)

#define KEY_S2_RCC         RCC_AHB1Periph_GPIOA
#define KEY_S2_GPIO        GPIOA
#define KEY_S2_GPIO_PIN    GPIO_Pin_0
#define KEY_S2_UPDOWM()    GPIO_ReadInputDataBit(KEY_S2_GPIO,KEY_S2_GPIO_PIN)

#define KEY_S3_RCC         RCC_AHB1Periph_GPIOD
#define KEY_S3_GPIO        GPIOD
#define KEY_S3_GPIO_PIN    GPIO_Pin_3
#define KEY_S3_UPDOWM()    GPIO_ReadInputDataBit(KEY_S3_GPIO,KEY_S3_GPIO_PIN)

#define KEY_S4_RCC         RCC_AHB1Periph_GPIOF
#define KEY_S4_GPIO        GPIOF
#define KEY_S4_GPIO_PIN    GPIO_Pin_7
#define KEY_S4_UPDOWM()    GPIO_ReadInputDataBit(KEY_S4_GPIO,KEY_S4_GPIO_PIN)

#define KEY_S5_RCC         RCC_AHB1Periph_GPIOF
#define KEY_S5_GPIO        GPIOF
#define KEY_S5_GPIO_PIN    GPIO_Pin_6
#define KEY_S5_UPDOWM()    GPIO_ReadInputDataBit(KEY_S5_GPIO,KEY_S5_GPIO_PIN)

typedef struct{
    uint32_t     rcc;
    GPIO_TypeDef *gpio;
    uint16_t     pin;
}Gpio_Info;

void LEDGpio_Init(void);
void KEYGpio_Init(void);

#endif
