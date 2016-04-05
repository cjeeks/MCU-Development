#ifndef _GPIO_H_
#define _GIPO_H_

#define LED_NUMBER         4    //LED总数
#define KEY_NUMBER         5    //按键总数
#define DP_NUMBER          8    //点阵控制管脚
#define TM1638_NUMBER      2    //tm1638总数
#define STEP_NUMBER        4
#define  RELAY_NUMBER      3
/************继电器接口******************/
#define RELAY1_RCC           RCC_AHB1Periph_GPIOG
#define RELAY1_GPIO          GPIOG
#define RELAY1_GPIO_PIN      GPIO_Pin_10
#define RELAY1_ONOFF(x)      GPIO_WriteBit(GPIOG,GPIO_Pin_10,x);

#define RELAY2_RCC           RCC_AHB1Periph_GPIOE
#define RELAY2_GPIO          GPIOE
#define RELAY2_GPIO_PIN      GPIO_Pin_1
#define RELAY2_ONOFF(x)      GPIO_WriteBit(GPIOE,GPIO_Pin_1,x);

#define RELAY3_RCC           RCC_AHB1Periph_GPIOE
#define RELAY3_GPIO          GPIOE
#define RELAY3_GPIO_PIN      GPIO_Pin_0
#define RELAY3_ONOFF(x)      GPIO_WriteBit(GPIOE,GPIO_Pin_0,x);

/************LED灯接口******************/
#define LED1_RCC           RCC_AHB1Periph_GPIOB
#define LED1_GPIO          GPIOB
#define LED1_GPIO_PIN      GPIO_Pin_6
#define LED1_ONOFF(x)      GPIO_WriteBit(GPIOB,GPIO_Pin_6,x);

#define LED2_RCC           RCC_AHB1Periph_GPIOA
#define LED2_GPIO          GPIOA
#define LED2_GPIO_PIN      GPIO_Pin_4
#define LED2_ONOFF(x)      GPIO_WriteBit(GPIOA,GPIO_Pin_4,x);

#define LED3_RCC           RCC_AHB1Periph_GPIOA
#define LED3_GPIO          GPIOA
#define LED3_GPIO_PIN      GPIO_Pin_6
#define LED3_ONOFF(x)      GPIO_WriteBit(GPIOA,GPIO_Pin_6,x);

#define LED4_RCC           RCC_AHB1Periph_GPIOC
#define LED4_GPIO          GPIOC
#define LED4_GPIO_PIN      GPIO_Pin_6
#define LED4_ONOFF(x)      GPIO_WriteBit(GPIOC,GPIO_Pin_6,x);



/************TM1638灯接口******************/
////TM1638 STB接PB9  CLK接PB4    DIO接PB8
#define CLK_RCC           RCC_AHB1Periph_GPIOF
#define CLK_GPIO          GPIOF
#define CLK_GPIO_PIN      GPIO_Pin_13
//#define CLK_ONOFF(x)      x?GPIO_SetBits(GPIOF,GPIO_Pin_13):GPIO_ResetBits(GPIOF,GPIO_Pin_13)
#define CLK_ONOFF(x)			GPIO_WriteBit(GPIOF,GPIO_Pin_13,x)
#define F13_ONOFF(x)      GPIO_WriteBit(GPIOF,GPIO_Pin_13,x)

#define STB_RCC           RCC_AHB1Periph_GPIOF
#define STB_GPIO          GPIOF
#define STB_GPIO_PIN      GPIO_Pin_15
//#define STB_ONOFF(x)      x?GPIO_SetBits(GPIOF,GPIO_Pin_15):GPIO_ResetBits(GPIOF,GPIO_Pin_15)
#define STB_ONOFF(x)				GPIO_WriteBit(GPIOF,GPIO_Pin_15,x)
#define F15_ONOFF(x)      GPIO_WriteBit(GPIOF,GPIO_Pin_13,x)

/************点阵显示接口******************/
#define D_RCC           RCC_AHB1Periph_GPIOB
#define D_GPIO          GPIOB
#define D_GPIO_PIN      GPIO_Pin_0
#define D_ONOFF(x)      GPIO_WriteBit(GPIOB,GPIO_Pin_0,x)

#define C_RCC           RCC_AHB1Periph_GPIOA
#define C_GPIO          GPIOA
#define C_GPIO_PIN      GPIO_Pin_3
#define C_ONOFF(x)      GPIO_WriteBit(GPIOA,GPIO_Pin_3,x)

#define B_RCC           RCC_AHB1Periph_GPIOF
#define B_GPIO          GPIOF
#define B_GPIO_PIN      GPIO_Pin_11
#define B_ONOFF(x)      GPIO_WriteBit(GPIOF,GPIO_Pin_11,x)

#define A_RCC           RCC_AHB1Periph_GPIOB
#define A_GPIO          GPIOB
#define A_GPIO_PIN      GPIO_Pin_1
#define A_ONOFF(x)      GPIO_WriteBit(GPIOB,GPIO_Pin_1,x)

#define G_RCC           RCC_AHB1Periph_GPIOG
#define G_GPIO          GPIOG
#define G_GPIO_PIN      GPIO_Pin_0
#define G_ONOFF(x)      GPIO_WriteBit(GPIOG,GPIO_Pin_0,x)

#define DI_RCC           RCC_AHB1Periph_GPIOF
#define DI_GPIO          GPIOF
#define DI_GPIO_PIN      GPIO_Pin_14
#define DI_ONOFF(x)      GPIO_WriteBit(GPIOF,GPIO_Pin_14,x)

#define DCLK_RCC           RCC_AHB1Periph_GPIOA
#define DCLK_GPIO          GPIOA
#define DCLK_GPIO_PIN      GPIO_Pin_5
#define DCLK_ONOFF(x)      GPIO_WriteBit(GPIOA,GPIO_Pin_5,x)

#define LAT_RCC           RCC_AHB1Periph_GPIOA
#define LAT_GPIO          GPIOA
#define LAT_GPIO_PIN      GPIO_Pin_0
#define LAT_ONOFF(x)      GPIO_WriteBit(GPIOA,GPIO_Pin_0,x)
/************按键接口******************/

#define KEY_S1_RCC         RCC_AHB1Periph_GPIOB  //k12 boot1
#define KEY_S1_GPIO        GPIOB
#define KEY_S1_GPIO_PIN    GPIO_Pin_2
#define KEY_S1_UPDOWM()    GPIO_ReadInputDataBit(KEY_S1_GPIO,KEY_S1_GPIO_PIN)

#define KEY_S2_RCC         RCC_AHB1Periph_GPIOA //K1 A0
#define KEY_S2_GPIO        GPIOA
#define KEY_S2_GPIO_PIN    GPIO_Pin_0
#define KEY_S2_UPDOWM()    GPIO_ReadInputDataBit(KEY_S2_GPIO,KEY_S2_GPIO_PIN)

#define KEY_S3_RCC         RCC_AHB1Periph_GPIOC //K2 ULPI_DIR( <-- OTG_FS_POWERSWITCHON)
#define KEY_S3_GPIO        GPIOC
#define KEY_S3_GPIO_PIN    GPIO_Pin_2
#define KEY_S3_UPDOWM()    GPIO_ReadInputDataBit(KEY_S3_GPIO,KEY_S3_GPIO_PIN)

#define KEY_S4_RCC         RCC_AHB1Periph_GPIOC //K5 ULPI_STP
#define KEY_S4_GPIO        GPIOC
#define KEY_S4_GPIO_PIN    GPIO_Pin_0
#define KEY_S4_UPDOWM()    GPIO_ReadInputDataBit(KEY_S4_GPIO,KEY_S4_GPIO_PIN)

#define KEY_S5_RCC         RCC_AHB1Periph_GPIOE //K4 A20
#define KEY_S5_GPIO        GPIOE
#define KEY_S5_GPIO_PIN    GPIO_Pin_4
#define KEY_S5_UPDOWM()    GPIO_ReadInputDataBit(KEY_S5_GPIO,KEY_S5_GPIO_PIN)
/*old board
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
*/
/************步进电机控制管脚******************/
//PD12  PG2   PG4  PD11  OLD
// PF3  PF4   PE5  PE3   NEW


#define IN1_RCC           RCC_AHB1Periph_GPIOF
#define IN1_GPIO          GPIOF
#define IN1_GPIO_PIN      GPIO_Pin_3
#define IN1_ONOFF(x)      GPIO_WriteBit(GPIOF,GPIO_Pin_3,x)

#define IN2_RCC           RCC_AHB1Periph_GPIOF
#define IN2_GPIO          GPIOF
#define IN2_GPIO_PIN      GPIO_Pin_4
#define IN2_ONOFF(x)      GPIO_WriteBit(GPIOF,GPIO_Pin_4,x)

#define IN3_RCC           RCC_AHB1Periph_GPIOE
#define IN3_GPIO          GPIOE
#define IN3_GPIO_PIN      GPIO_Pin_5
#define IN3_ONOFF(x)      GPIO_WriteBit(GPIOE,GPIO_Pin_5,x)

#define IN4_RCC           RCC_AHB1Periph_GPIOE
#define IN4_GPIO          GPIOE
#define IN4_GPIO_PIN      GPIO_Pin_3
#define IN4_ONOFF(x)      GPIO_WriteBit(GPIOE,GPIO_Pin_3,x)
typedef struct{
    uint32_t     rcc;
    GPIO_TypeDef *gpio;
    uint16_t     pin;
}Gpio_Info;

void LEDGpio_Init(void);
void KEYGpio_Init(void);
void DPGpio_Init(void);
void DuojiGpio_Init(void);
void DUJIN_port(u8 dat);
void RELAYGpio_Init(void);

#endif
