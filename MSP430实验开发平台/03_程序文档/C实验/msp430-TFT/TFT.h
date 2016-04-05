#ifndef _TFT_H
#define _TFT_H

#include "delay.h"

//定义LCD的尺寸
#define LCD_W 480
#define LCD_H 272

//画笔颜色
#define WHITE  0xFFFF
#define BLACK  0x0000	  
#define BLUE   0x001F  
#define BRED   0XF81F
#define GRED   0XFFE0
#define GBLUE  0X07FF
#define RED    0xF800
#define MAGENTA   0xF81F
#define GREEN  0x07E0
#define CYAN   0x7FFF
#define YELLOW    0xFFE0
#define BROWN  0XBC40 //棕色
#define BRRED  0XFC07 //棕红色
#define GRAY   0X8430 //灰色

//GUI颜色（前三种颜色为PANEL的颜色）
#define DARKBLUE   0X01CF //深蓝色
#define LIGHTBLUE  0X7D7C //浅蓝色
#define GRAYBLUE   0X5458 //灰蓝色
#define LIGHTGREEN  0X841F //浅绿色
#define LGRAY 	    0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE   0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE      0X2B12 //浅棕蓝色(选择条目的反色)

//16位数据模式，如果使用8位数据模式，请注释掉该语句
#define Bus_16

//IO口连接
#define RD_LCD_DataPortH  P4IN//读高8位数据口，8位模式下只使用高8位
#define WT_LCD_DataPortH  P4OUT//写高8位数据口，8位模式下只使用高8位

#define RD_LCD_DataPortL  P2IN//读第8位数据口，8位模式下低8位可以不接线，请确认低8位已经上拉10K电阻
#define WT_LCD_DataPortL  P2OUT//写第8位数据口，8位模式下低8位可以不接线，请确认低8位已经上拉10K电阻

#define SET_LCD_RS  P3OUT|=BIT2//置位数据命令切换引脚
#define CLR_LCD_RS  P3OUT&=~BIT2//复位数据命令切换引脚
#define GET_LCD_RS  P3IN&BIT2//读数据命令切换引脚状态（1为高，0为低）

#define SET_LCD_WR  P3OUT|=BIT3//置位写控制引脚
#define CLR_LCD_WR  P3OUT&=~BIT3//复位写控制引脚
#define GET_LCD_WR  P3OUT&BIT3//读写控制引脚状态（1为高，0为低）

#define SET_LCD_RD  P3OUT|=BIT1//置位读控制引脚
#define CLR_LCD_RD  P3OUT&=~BIT1//复位读控制引脚
#define GET_LCD_RD  P3OUT&BIT1//读读控制引脚状态（1为高，0为低）

#define SET_LCD_CS  P3OUT|=BIT6//置位片选引脚
#define CLR_LCD_CS  P3OUT&=~BIT6//复位片选引脚
#define GET_LCD_CS  P3OUT&BIT6//读片选引脚状态（1为高，0为低）

#define SET_LCD_REST  P3OUT|=BIT7//置位复位引脚
#define CLR_LCD_REST  P3OUT&=~BIT7//复位复位引脚
#define GET_LCD_REST  P3OUT&BIT7//读复位引脚状态（1为高，0为低）

extern uint BACK_COLOR, POINT_COLOR;   //背景色，画笔色

void LCD_Init(void);
void LCD_Clear(uint);
void LCD_Address_set(uint,uint,uint,uint);
void LCD_WR_DATA8(char VH,char VL); //发送数据，8位参数
void LCD_WR_DATA(int);
void LCD_WR_REG(int);
void LCD_DrawPoint(uint,uint);//画点
void LCD_DrawPoint_big(uint,uint);//画一个大点
uint LCD_ReadPoint(uint,uint); //读点
void LCD_Draw_Circle(uint ,uint,uchar);
void LCD_DrawLine(uint, uint, uint, uint);
void LCD_DrawRectangle(uint, uint, uint, uint);		   
void LCD_Fill(uint,uint,uint,uint,uint);
void LCD_ShowChar(uint x,uint y,uchar num,uchar mode);//显示一个字符
void LCD_ShowNum(uint x,uint y,ulong num,uchar len);//显示数字
void LCD_Show2Num(uint x,uint y,uint num,uchar len);//显示2个数字
void LCD_ShowString(uint x,uint y,const uchar *p);//显示一个字符串
void LCD_showhanzi(uint x,uint y,uchar index);

void showimage(void);

#endif