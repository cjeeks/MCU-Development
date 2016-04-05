#include "GUI.h"
#include "LedTest.h"
#include "BUTTON.h"
#include "FRAMEWIN.h"
//
//#define GUI_ID_ON         1
//#define GUI_ID_OFF        2
//#define GUI_ID_EXIT       3
//
extern GUI_CONST_STORAGE GUI_BITMAP bmon1;
extern GUI_CONST_STORAGE GUI_BITMAP bmoff1;
//
//extern GUI_PID_STATE pState;	//读取按键的状态
//
//void LedTest(void)
//{
//    int i = 0;
//
//	BUTTON_Handle hButton[3];
//
//	int Key=0;
//
//
//	//WM_SetBkWindowColor(GUI_RED); 
//	   
////	hButton[0]=BUTTON_Create(0,281,80,39,GUI_ID_ON,WM_CF_SHOW);
////	//hButton[1]=BUTTON_Create(80,281,80,39,GUI_ID_EXIT,WM_CF_SHOW);
////	hButton[2]=BUTTON_Create(160,281,80,39,GUI_ID_OFF,WM_CF_SHOW);
//	hButton[0]=BUTTON_CreateAsChild(0,281,80,39,0,GUI_ID_ON,WM_CF_SHOW);
//	//hButton[1]=BUTTON_CreateAsChild(80,281,80,39,GUI_ID_EXIT,WM_CF_SHOW);
//	hButton[2]=BUTTON_CreateAsChild(160,281,80,39,0,GUI_ID_OFF,WM_CF_SHOW);
//
////	BUTTON_SetBkColor(hButton, 1, GUI_RED);
//    BUTTON_SetFont(hButton[0], &GUI_Font8x16);
//    BUTTON_SetFont(hButton[1], &GUI_Font8x16);
//	BUTTON_SetFont(hButton[2], &GUI_Font8x16);
//
//	BUTTON_SetText(hButton[0],"ON");
//	//BUTTON_SetText(hButton[1],"Exit");
//	BUTTON_SetText(hButton[2],"OFF");
//
//	//BUTTON_SetBkColor(hButton[0],0,GUI_RED);
//	BUTTON_SetTextColor(hButton[0], 0, GUI_BLUE);
//	BUTTON_SetTextColor(hButton[1], 0, GUI_BLUE);
//	BUTTON_SetTextColor(hButton[2], 0, GUI_BLUE);
//
//	//WM_Exec();
//    GUI_Exec();
////	WM_Paint();
////	BUTTON_Delete(hButton);
//
//	//WM_Paint();//重绘图
//
//	GUI_DrawBitmap(&bmoff1,0,0);//绘制背景图
//
//    while(i != 1)
//	{
//	    Key=GUI_WaitKey();
//		switch(Key)
//		{
//			case GUI_ID_ON:
//			{
//			    GUI_DrawBitmap(&bmon1,0,0);
//				break;
//			}
//			case GUI_ID_OFF:
//			{
//			    GUI_DrawBitmap(&bmoff1,0,0);
//				break;
//			}
//			case GUI_ID_EXIT:
//			{
//			    i = 1;//退出本测试
//			} 
//			default:
//			    break;  
//		}
////		if(Key == GUI_ID_ON)
////		{
////		    break;	 //退出本测试任务
////		}
//
//
//
//
////		if( GUI_TOUCH_GetState(&pState) == 1)	  //检测触摸
////		{
////		    if(0)			 //如果坐标落在退出键，退出本测试
////			{
////			    break;
////			}
////		    else if(i == 0)
////			{
////			    i = 1;
////			    GUI_DrawBitmap(&bmon1,0,0);
////			}
////			else
////			{
////			    i = 0;
////			    GUI_DrawBitmap(&bmoff1,0,0);
////			}
////		}
//
//	}
//}





/*
******************************************************************
**                      uCGUIBuilder                            **
**                  Version:   4.0.0.0                          **
**                     2012 / 04                               **
**                   CpoyRight to: wyl                          **
**              Email:ucguibuilder@163.com                        **
**          This text was Created by uCGUIBuilder               **
******************************************************************/

#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"





//EventsFunctionList
void OnButtonReleased(WM_MESSAGE * pMsg);
void ExitButtonReleased(WM_MESSAGE * pMsg);
void OffButtonReleased(WM_MESSAGE * pMsg);
//EndofEventsFunctionList


/*********************************************************************
*
*       static data
*
**********************************************************************
*/



/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Caption",           0,                       0,  0,  240,320,FRAMEWIN_CF_MOVEABLE,0},
    { BUTTON_CreateIndirect,    "ON",                GUI_ID_BUTTON0,          -2, 258,80, 44, 0,0},
    { BUTTON_CreateIndirect,    "EXIT",              GUI_ID_BUTTON1,          78, 258,80, 44, 0,0},
    { BUTTON_CreateIndirect,    "OFF",               GUI_ID_BUTTON2,          158,258,80, 44, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetClientColor(hWin,0x0000ff);
    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
    FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
    //
    //GUI_ID_BUTTON0
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),BUTTON_CI_UNPRESSED,0xd0e040);
    //
    //GUI_ID_BUTTON1
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_CI_UNPRESSED,0xffff00);
    //
    //GUI_ID_BUTTON2
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),BUTTON_CI_UNPRESSED,0xffff00);

}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_BUTTON0:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButtonReleased(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            ExitButtonReleased(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON2:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OffButtonReleased(pMsg);
                            break;
                    }
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}


/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
short hwin,hGUI_ID_BUTTON0,hGUI_ID_BUTTON1;
void LedMainTask(void) 
{ 
    //GUI_Init();
    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */

    WM_SetCreateFlags(WM_CF_SHOW);  /* Use memory devices on all windows to avoid flicker */
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    //PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    //BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    //CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    //DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    //SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    //SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    //RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	//阻塞
    //GUI_ExecDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
    //非阻塞
	hwin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);

//    hGUI_ID_BUTTON0 = WM_GetDialogItem(hwin,GUI_ID_BUTTON0);
//	hGUI_ID_BUTTON1 = WM_GetDialogItem(hwin,GUI_ID_BUTTON1);
//
//    DROPDOWN_SetFont(hGUI_ID_BUTTON0,&GUI_Font8x13_ASCII);

    WM_Exec();
//	while(1)
//	{
//
//		//GUI_CURSOR_Show();
//		GUI_TOUCH_Exec();
//		Delay(10);
//	    
//	}
}


void OnButtonReleased(WM_MESSAGE * pMsg)
{
    //GUI_DrawBitmap(&bmon1,0,0);
	    
}
void ExitButtonReleased(WM_MESSAGE * pMsg)
{

}
void OffButtonReleased(WM_MESSAGE * pMsg)
{
   // GUI_DrawBitmap(&bmoff1,0,0);
}
