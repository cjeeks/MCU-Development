#ifndef _TOUCH_H_
#define _TOUCH_H_

#define   uchar        unsigned char

/*****TOUCH_SPI接口声明*****/
#define TOUCH_SPI_RCC            RCC_APB1Periph_SPI2
#define TOUCH_SPI                SPI2
#define SPI_RCC_APB2Periph       RCC_APB2Periph_GPIOG
#define SPI_SCK_GPIO_Pin         GPIO_Pin_10
#define SPI_MISO_GPIO_Pin        GPIO_Pin_14
#define SPI_MOSI_GPIO_Pin        GPIO_Pin_15
#define SPI_GPIO                 GPIOB

/*****TOUCH_CS接口声明*****/
#define TOUCH_CS_APB2Periph      RCC_APB2Periph_GPIOG
#define TOUCH_CS_GPIO            GPIOG
#define TOUCH_CS_GPIO_Pin        GPIO_Pin_15

/*****TOUCH_IRQ接口声明*****/
#define TOUCH_IRQ_APB2Periph     RCC_APB2Periph_GPIOG
#define TOUCH_IRQ_GPIO           GPIOG
#define TOUCH_IRQ_GPIO_Pin       GPIO_Pin_8
#define TOUCH_IRQ_CONFIG         GPIO_PinSource8
#define TOUCH_IRQ_LINE		     EXTI_Line8

/*****FLASH_CS接口声明*****/
#define FLASH_CS_APB2Periph      RCC_APB2Periph_GPIOC
#define FLASH_CS_GPIO            GPIOC
#define FLASH_CS_GPIO_Pin        GPIO_Pin_13

/*****SD_CS接口声明*****/
#define SD_CS_APB2Periph         RCC_APB2Periph_GPIOF
#define SD_CS_GPIO               GPIOF
#define SD_CS_GPIO_Pin           GPIO_Pin_6

#define TP_IO_STATE				 GPIO_ReadInputDataBit(TOUCH_IRQ_GPIO,TOUCH_IRQ_GPIO_Pin)

#define Select_TOUCH_CS()        GPIO_ResetBits(TOUCH_CS_GPIO,TOUCH_CS_GPIO_Pin) //TOUCH 选择
#define NotSelect_TOUCH_CS()     GPIO_SetBits(TOUCH_CS_GPIO,TOUCH_CS_GPIO_Pin)   //TOUCH 禁止

#define Select_FLASH_CS()        GPIO_ResetBits(FLASH_CS_GPIO,FLASH_CS_GPIO_Pin) //FLASH 选择
#define NotSelect_FLASH_CS()     GPIO_SetBits(FLASH_CS_GPIO,FLASH_CS_GPIO_Pin)   //FLASH 禁止

#define Select_SD_CS()           GPIO_ResetBits(SD_CS_GPIO,SD_CS_GPIO_Pin)        //SD 选择
#define NotSelect_SD_CS()        GPIO_SetBits(SD_CS_GPIO,SD_CS_GPIO_Pin)          //SD 禁止


/* ADS7843/7846/UH7843/7846/XPT2046/TSC2046 指令集 */
#define CMD_RDY 0X90  //0B10010000即用差分方式读X坐标
#define CMD_RDX	0XD0  //0B11010000即用差分方式读Y坐标 

/* 按键状态	*/ 
#define Key_Down 0x01
#define Key_Up   0x00 

/* 笔杆结构体 */
typedef struct 
{
	u16 X0;//原始坐标
	u16 Y0;
	u16 X; //最终/暂存坐标
	u16 Y;						   	    
	u8  Key_Sta;//笔的状态			  
	//触摸屏校准参数
	float xfac;
	float yfac;
	short xoff;
	short yoff;
}Pen_Holder;

void Touch_Init(void);
u8 Read_ADS(u16 *x,u16 *y);
void Touch_IRQ(void);
void Convert_Pos(void);
void Refreshes_Screen(void);
void Draw_Big_Point(u16 x,u16 y);
void Pen_Int_Set(u8 en);
#endif

