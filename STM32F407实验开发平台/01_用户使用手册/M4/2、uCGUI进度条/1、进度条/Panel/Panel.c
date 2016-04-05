#include "stm32f4xx.h"
#include "ucos_ii.h"
#include "GUI.h"
#include "Panel.h"
#include "Gpio.h"
#include "progbar.h"

/********************************************************************************************
*函数名称：void Panel(void)
*
*入口参数：无
*
*出口参数：无
*
*功能说明：进度条示例
*******************************************************************************************/
void Panel(void)
{
    int i = 0;
    PROGBAR_Handle ahProgBar;

	GUI_SetBkColor(GUI_BLACK);   //设置背景颜色
	GUI_SetColor(GUI_RED);       //设置前景颜色，及字体和绘图的颜色
    GUI_Clear();                 //按指定颜色清屏
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringAt("www.openmcu.com",50,10); //显示字符

    ahProgBar = PROGBAR_Create(  60, 180, 100,20,WM_CF_SHOW );    //建立一个进度条
    PROGBAR_SetBarColor(ahProgBar,0,GUI_GREEN);                   //设置进度条的左部分色值
    PROGBAR_SetBarColor(ahProgBar,1,GUI_RED);                     //设置进度条的右部分色值
    PROGBAR_SetTextColor(ahProgBar,0,GUI_BLUE);                   //设置进度条字体的右部分色值
    PROGBAR_SetTextColor(ahProgBar,1,GUI_BLACK);                  //设置进度条字体的右部分色值

    while(1)
    {
        LED3_ONOFF(Bit_RESET);        //打开灯LED3

        for(i = 0; i < 100 ; i++)
        {
            PROGBAR_SetValue(ahProgBar,i);       //设置进度条数值
            OSTimeDly(50);
        }

        LED3_ONOFF(Bit_SET);       //关闭灯LED3

        for(i = 100; i >0 ; i--)
        {
            PROGBAR_SetValue(ahProgBar,i);       //设置进度条数值
            OSTimeDly(50);
        }

    }
}




