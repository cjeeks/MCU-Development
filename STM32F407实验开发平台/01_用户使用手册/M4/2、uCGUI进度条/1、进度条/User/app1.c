#include "ucos_ii.h"
#include <stdio.h>
//#include "usart.h"
#include "stm32f4xx.h"
#include "Gpio.h"

/***********************************************************/
//#include "usart.h"
#include "gui.h"
#include "GUIType.h"
#include "stm32f4xx.h"
#include "WM.h"
#include "checkbox.h"
#include "button.h"
#include "edit.h"
#include "checkbox.h"
#include "listbox.h"
#include "framewin.h"
#include "PROGBAR.h"
#include "radio.h"
#include "SCROLLBAR.h"
#include "SLIDER.h"
#include "text.h"
#include "touch.h"
#include "uart.h"
#include "gui.h"
#include "GUIType.h"
//#include "stm32f10x.h"
#include "WM.h"
#include "checkbox.h"
#include "button.h"
#include "edit.h"
#include "checkbox.h"
#include "listbox.h"
#include "framewin.h"
#include "PROGBAR.h"
#include "radio.h"
#include "SCROLLBAR.h"
#include "SLIDER.h"
#include "text.h"
//#include "APP_RTC.H"
/***********************************************************/



/************************************led宏定义***************************************/
/************************************************************************************/
//#define	LED_1	GPIO_Pin_6	
//#define	LED_2	GPIO_Pin_7
//#define	LED_3	GPIO_Pin_8
//
//#define	LED1(x)	GPIOF->BSRR=(x<1)?(1<<6):(1<<(16+6))
//#define	LED2(x)	GPIOF->BSRR=(x<1)?(1<<7):(1<<(16+7))
//#define	LED3(x)	GPIOF->BSRR=(x<1)?(1<<8):(1<<(16+8))

/*************************************全局变量申明***********************************/
/************************************************************************************/
OS_EVENT*	Sem1;

/*************************************资源表定义**********************************/
/************************************************************************************/
#define	RRAMEWIN_ID		0+200
#define	TEXT_ID1			1+200
#define	LED1_ID1			2+200
#define	LED2_ID2			3+200
#define	LED3_ID3			4+200
#define	TEXT_ID2			5+200
#define	TEXT_ID3			6+200
#define	TEXT_ID4			7+200
#define	TEXT_ID5			8+200
#define	SLIDER_ID			9+200
#define BUTTON1_ID			10+200
#define BUTTON2_ID			11+200

/*LED开关状态*/
char LED1_Status;
char LED2_Status;
char LED3_Status;
/*LED工作模式:占空比模式，还是开关模式*/
unsigned char LED_TEST_MODE;
/*led占空比*/
unsigned short led_duty;
/*描述符申明*/
WM_HWIN hWin;
WM_HWIN text0,text1,text2,text3,text4,checkbox0,checkbox1,checkbox2,slider0;
/* 定义了对话框资源列表 */
static const GUI_WIDGET_CREATE_INFO aDialogCreate[] = {
	
	/*框架窗口*/
	{ FRAMEWIN_CreateIndirect, "LED Demo", RRAMEWIN_ID, 0, 0, 320, 240, /*FRAMEWIN_CF_ACTIVE*/0 ,0 },
	/*文本控件*/
	{ TEXT_CreateIndirect, "Test 1 - LED On/Off", TEXT_ID1, 40, 10, 152, 13, 0,TEXT_CF_LEFT  },
	/*复选框*/
	{ CHECKBOX_CreateIndirect, "LED1", LED1_ID1, 80, 60, 15, 15, 0 ,0 },
	{ CHECKBOX_CreateIndirect, "LED2", LED2_ID2, 160, 60, 15, 15, 0 ,0 },
	{ CHECKBOX_CreateIndirect, "LED3", LED3_ID3, 240, 60, 15, 15,/* TEXT_CF_HCENTER*/0 ,0 },
	/*文本控件*/
	{ TEXT_CreateIndirect, "LED1", TEXT_ID2, 75, 38, 30, 13, 0,TEXT_CF_LEFT  },
	{ TEXT_CreateIndirect, "LED2", TEXT_ID3, 155, 38, 30, 13, 0,TEXT_CF_LEFT  },
	{ TEXT_CreateIndirect, "LED3", TEXT_ID4, 235, 38, 30, 13, 0,TEXT_CF_LEFT  },

	/*文本控件*/
	{ TEXT_CreateIndirect, "Test 2 - LED duty cyle", TEXT_ID5, 40, 120, 176, 13, 0,TEXT_CF_LEFT },
	/*滑动条*/
	{ SLIDER_CreateIndirect, 0, SLIDER_ID, 80, 175, 150, 15, TEXT_CF_LEFT ,0 },
	/*button*/
	{ BUTTON_CreateIndirect, "select1", BUTTON1_ID, 250, 10, 60, 15, 0 ,0 },
	{ BUTTON_CreateIndirect, "select2", BUTTON2_ID, 250, 120, 60, 15 ,0,0 },
};

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::**
** 函数名称: GPIO_Configuration
** 功能描述: IO引脚配置
** 参数描述：无
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
//void Led_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;					//定义一个GPIO结构体变量
//
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);	//使能各个端口时钟，重要！！！
//	
//	GPIO_InitStructure.GPIO_Pin = LED_1 | LED_2 
//	| LED_3; 											//配置LED端口挂接到6、12、13
//  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//通用输出推挽
//  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//配置端口速度为50M
//  	GPIO_Init(GPIOF, &GPIO_InitStructure);				   	//将端口GPIOD进行初始化配置
//}

/**/
/*************************************硬件平台初始化***********************************/
/**************************************************************************************/
void BSP_Init()
{	
	/*串口初始化*/
	uart_init();
	//Usart_Configuration(115200);
	printf("USART Init。。。OK/r/n");
	
	/*led初始化*/
	//Led_Init();
    	
    LEDGpio_Init();
	/*GUI 初始化，这是必须地 */
	GUI_Init();

	/*触屏的Io配置*/
	//Touch_Configuration();

}
/*******************************************GUI任务***********************************/
/**************************************************************************************/
/*视窗回调函数*/
void Window1_CallBack(WM_MESSAGE* pMsg)
{
	/*对消息散转，处理对应消息*/
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
		{
			GUI_SetBkColor(GUI_LIGHTMAGENTA);
			GUI_Clear();
			break;
		}
		default:
		{/*默认消息处理方式*/
			WM_DefaultProc(pMsg);
		}
	}
}
/*视窗回调函数*/
void Window2_CallBack(WM_MESSAGE* pMsg)
{
	/*对消息散转，处理对应消息*/
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
		{
			GUI_SetBkColor(GUI_DARKCYAN);
			GUI_Clear();
			break;
		}
		default:
		{/*默认消息处理方式*/
			WM_DefaultProc(pMsg);
		}

	}
}
/*单击处理*/
static void _IsCLICKED(WM_HWIN hDlg, int Id) {

  if ((Id == LED1_ID1)) {/*返回复选框状态*/						
    LED1_Status = CHECKBOX_IsChecked(checkbox0);						
  }	
  else if ((Id == LED2_ID2)) {				
    LED2_Status = CHECKBOX_IsChecked(checkbox1);						
  }	
  else if ((Id == LED3_ID3)) {				
    LED3_Status = CHECKBOX_IsChecked(checkbox2);						
  }	 
  else if ((Id == BUTTON1_ID)) {/*选择模式1*/
    LED_TEST_MODE = 1;						
  }	 
   else if ((Id == BUTTON2_ID)) {/*选择模式2*/
    LED_TEST_MODE = 2;						
  }	
 
}
/*滑动条值改变处理*/
void _IsValueChanged(hDlg,Id)
{
	if((Id == SLIDER_ID)){/*在这里得到滚动条的值*/
		led_duty=SLIDER_GetValue(slider0);					 //获得slider0的值	
	}		
}
/****************************************************************************
* 名    称：static void _cbCallback(WM_MESSAGE * pMsg)  
* 功    能：窗体回调函数 
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void _cbCallback(WM_MESSAGE * pMsg) {    
  int NCode, Id;
  WM_HWIN hDlg;
  hDlg = pMsg->hWin;	  
  switch (pMsg->MsgId) {     
    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);      /*获得窗体部件的ID*/
      NCode = pMsg->Data.v;                 /*动作代码 */
      switch (NCode) {	          
        case WM_NOTIFICATION_CLICKED: /*窗体部件的值被改变 */
		{	   
			_IsCLICKED(hDlg, Id);	 
			break;
		}
		case WM_NOTIFICATION_VALUE_CHANGED:
		{
			_IsValueChanged(hDlg,Id);
			break;
		}
		 
        default:
          break;
      }
      break;  
    default:
      WM_DefaultProc(pMsg);
  }
}

/*************************************************************????????????????????????????????????*/
unsigned int test_stk[2048];
void test1_Task(char *p)
{	
	/*清除屏幕*/
	GUI_Clear();

	/*建立框架函数*/  
  	hWin = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), _cbCallback, 0, 0, 0);

	/* 获得TEXT 部件的句柄 */
  	text0 = WM_GetDialogItem(hWin, TEXT_ID1);
	text1 = WM_GetDialogItem(hWin, TEXT_ID2);
	text2 = WM_GetDialogItem(hWin, TEXT_ID3);
	text3 = WM_GetDialogItem(hWin, TEXT_ID4);
	text4 = WM_GetDialogItem(hWin, TEXT_ID5);

	/*获得复选框描述符*/
	checkbox0 = WM_GetDialogItem(hWin, LED1_ID1);
	checkbox1 = WM_GetDialogItem(hWin, LED2_ID2);
	checkbox2 = WM_GetDialogItem(hWin, LED3_ID3);
										
	/*滚动条控件*/
	slider0 = WM_GetDialogItem(hWin, SLIDER_ID);

	/* 设置文本字体 */
	TEXT_SetFont(text0, &GUI_Font8x13_ASCII);
	TEXT_SetFont(text1, &GUI_Font6x9);
	TEXT_SetFont(text2, &GUI_Font6x9);
	TEXT_SetFont(text3, &GUI_Font6x9);
	TEXT_SetFont(text4, &GUI_Font8x13_ASCII);

	/* 设置TEXT部件的字体颜色 */        	
	TEXT_SetTextColor(text0,0XFf);	
	TEXT_SetTextColor(text1,0XFF);		 //蓝
	TEXT_SetTextColor(text2,0XFF);
	TEXT_SetTextColor(text3,0XFF);
	TEXT_SetTextColor(text4,0XFf);
//
//	TEXT_SetText(text0,"TesDFSFDSDt 1");
//	TEXT_SetText(text1,"LEDFSADFSAD1");
//	TEXT_SetText(text2,"LEFDFSDFD2");
//	TEXT_SetText(text3,"LEASDFDSAD3");
//	TEXT_SetText(text4,"TeDAFADFst 2");
	
	/*滑动条设置数值范围*/
	SLIDER_SetRange(slider0,1,400);

	
	while(1)
	{
		GUI_CURSOR_Show();
		GUI_TOUCH_Exec();
//		OSTimeDlyHMSM(0,0,0,15);
        OSTimeDly(15);
		WM_Exec();
	}
}
/*******************************************串口任务***********************************/
/**************************************************************************************/
unsigned int usart_stk[128];
void Usart_Task(char *p_arg)
{
	INT8U	err;

	while(1){
		/*请求信号量*/
		OSSemPend(Sem1,0,&err);

		printf(p_arg);
		printf("err=0x%x\r\n",err);
		/**/
//		OSTimeDlyHMSM(0,0,0,500);
        OSTimeDly(500);

		/*释放信号量*/
		OSSemPost(Sem1);		
	}
	
}
/*led任务*/
/*****************************************led任务**********************************/
/**************************************************************************************/
void led_delay(unsigned short i)
{
	unsigned short j;
	for(i=i;i>0;i--)
		for(j=0x5ff;j>0;j--);
}
unsigned int led_stk[128];
void Led_Task(char *p_arg)
{
	while(1){
		if(LED_TEST_MODE == 1)
		{
			if(LED1_Status == 1){
				LED1_ONOFF(Bit_SET);	
			}
			else{
				LED1_ONOFF(Bit_RESET);	
			}
	
			if(LED2_Status == 1){
				LED2_ONOFF(Bit_SET);	
			}
			else{
				LED2_ONOFF(Bit_RESET);	
			}
	
			if(LED3_Status == 1){
				LED3_ONOFF(Bit_SET);	
			}
			else{
				LED3_ONOFF(Bit_RESET);	
			}
	
			//OSTimeDlyHMSM(0,0,0,10);
            OSTimeDly(10);
		}
		else if(LED_TEST_MODE == 2)
		{
			LED1_ONOFF(Bit_RESET);
			LED2_ONOFF(Bit_RESET);
			LED3_ONOFF(Bit_RESET);
			led_delay(led_duty);
			
			LED1_ONOFF(Bit_SET);
			LED2_ONOFF(Bit_SET);
			LED3_ONOFF(Bit_SET);
			led_delay(400-led_duty);
		}

        OSTimeDly(10);
	}
}

/**/
/************************************创建所有任务**************************************/
/**************************************************************************************/
void Task_Start(void)
{
	/*保存任务返回*/
	unsigned  char err;


#if	OS_SEM_EN>0
	/*创建一个拥有1个资源的信号量*/
	Sem1 = OSSemCreate(1);
	if(Sem1!=0){
		printf("Error->Sem1 = OSSemCreate(3);\r\n");
	}
#endif	


	/*创建任务*/
	err = OSTaskCreate((void (*) (void *)) &Led_Task,
					   (void*)0,
					   (OS_STK *)&led_stk[128-1],
					   2);
//
//	printf("err=0x%x\r\n",err);
//
//	err = OSTaskCreate((void (*) (void *)) &Usart_Task,
//					   (void*)"hello",
//					   (OS_STK *)&usart_stk[128-1],
//					   3);
//
//	printf("err=0x%x\r\n",err);

	err = OSTaskCreate((void (*) (void *)) &test1_Task,
					   (void*)0,
					   (OS_STK *)&test_stk[2048-1],
					   4);

	printf("err=0x%x\r\n",err);
	
}
