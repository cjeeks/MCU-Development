

#ifndef __LCD_H__
#define __LCD_H__	1
//#include "main.h"
#include "stm32f4xx.h"


#define   HDP	479

#define   HT	531
#define   HPS	43
#define   LPS	8
#define   HPW	10

#define   VDP	271
#define   VT	288
#define   VPS	12
#define   FPS	4
#define    VPW	10


/***********************************************************************************
设置颜色宏定义
***********************************************************************************/
#define   Black        0x0000                    // 黑色： 0, 0, 0              
#define   Navy         0x000F                    // 深蓝色： 0, 0, 128          
#define   Dgreen       0x03E0                    // 深绿色： 0, 128, 0          
#define   Dcyan        0x03EF                    // 深青色： 0, 128, 128        
#define   Marooon       0x7800                    // 深红色：128, 0, 0           
#define   Purple       0x780F                    // 紫色： 128, 0, 128          
#define   Olive        0x7BE0                    // 橄榄绿：128, 128, 0         
#define   Lgray        0xC618                    // 灰白色：192, 192, 192        
#define   Dgray        0x7BEF                    // 深灰色：128, 128, 128        
#define   Blue         0x001F                    // 蓝色： 0, 0, 255            
#define   Green        0x07E0                 	 // 绿色： 0, 255, 0             
#define   Cyan         0x07FF                    // 青色： 0, 255, 255           
#define   Red          0xF800                    // 红色： 255, 0, 0             
#define   Magenta      0xF81F                    // 品红： 255, 0, 255          
#define   Yellow       0xFFE0                    // 黄色： 255, 255, 0           
#define   White        0xFFFF                    // 白色： 255, 255, 255   

/********************************************************************************/
/*********************宏定义*****************************************************/
/* Private typedef -----------------------------------------------------------*/
//typedef struct
//{
//  vu16 LCD_REG;
//  vu16 LCD_RAM;
//} LCD_TypeDef;

/* LCD is connected to the FSMC_Bank1_NOR/SRAM4 and NE4 is used as ship select signal */
//#define LCD_BASE    ((u32)(0x60000000 | 0x0C000000))
//#define LCD         ((LCD_TypeDef *) LCD_BASE)

//#define LCD_REG (*(volatile unsigned int*)(0x6c000000))
//#define LCD_RAM (*(volatile unsigned int*)(0x6c000002))
//写命令
//#define LCD_WriteCom(LCD_Reg) LCD->LCD_REG=(LCD_Reg)
//
////写数据
//#define LCD_WriteRAM(RGB_Code) LCD->LCD_RAM=(RGB_Code)
//


//函数申明
void lcd_clear(u16 Color);
void lcd_init(void);
void write_data_Prepare(void);
void LCD_ShowString(u16 x0, u16 y0, u8 *pcStr, u16 PenColor, u16 BackColor);
void LCD_Fill(uint8_t xsta, uint16_t ysta, uint8_t xend, uint16_t yend, uint16_t colour);
void LCD_DrawLine(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);

#endif
