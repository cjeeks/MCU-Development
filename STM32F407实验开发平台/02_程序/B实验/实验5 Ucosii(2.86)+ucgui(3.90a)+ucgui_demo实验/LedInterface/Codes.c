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
void OnMultiEditSelChanged(WM_MESSAGE * pMsg);
void OnButton2Release(WM_MESSAGE * pMsg);
void OnButton1Released(WM_MESSAGE * pMsg);
//void OnButton3Release(WM_MESSAGE * pMsg);
void OnDropDown2SelChanged(WM_MESSAGE * pMsg);
void OnDropDown1SelChanged(WM_MESSAGE * pMsg);

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
    { FRAMEWIN_CreateIndirect,  "TEX&BMP Test",           0,                       0,  0,  320,240,FRAMEWIN_CF_MOVEABLE,0},
    { DROPDOWN_CreateIndirect,   NULL,               GUI_ID_DROPDOWN0,        1,  4,  82, 80, 0,0},
    { DROPDOWN_CreateIndirect,   NULL,               GUI_ID_DROPDOWN1,        157,4,  82, 80, 0,0},
    { BUTTON_CreateIndirect,    "OPEN",           GUI_ID_BUTTON0,          89, 2,  62, 23, 0,0},
    { BUTTON_CreateIndirect,    "OPEN",           GUI_ID_BUTTON1,          245,1,  64, 23, 0,0},
    { MULTIEDIT_CreateIndirect, "MULTIEDIT",         GUI_ID_MULTIEDIT0,       0,  29, 317,195,0,0}
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
	/*我们不用关闭按键*/
//    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
    FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
    //
    //GUI_ID_DROPDOWN0
    //
    DROPDOWN_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),0,0xccedc7);
//    DROPDOWN_SetAutoScroll(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),1);

//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"df");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"dsaf");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"adsfsd");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"hgfsg");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"afsdf");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"asdfs");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"fads");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"asdf");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"fdas");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"asdf");
//    DROPDOWN_AddString(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),"af");
    //
    //GUI_ID_DROPDOWN1
    //
    DROPDOWN_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN1),0,0xccedc7);
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
        case WM_INIT_DIALOG:	 /*初始准备*/
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
                case GUI_ID_DROPDOWN0:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_SEL_CHANGED:
                            OnDropDown1SelChanged(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_DROPDOWN1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_SEL_CHANGED:
                            OnDropDown2SelChanged(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON0:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButton1Released(pMsg);
                            break;
                    }
                    break;
                case GUI_ID_BUTTON1:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_RELEASED:
                            OnButton2Release(pMsg);
                            break;
//						case WM_NOTIFICATION_MOVED_OUT:
//							break;
//						case WM_NOTIFICATION_SEL_CHANGED:
//							break;
//						case WM_NOTIFICATION_VALUE_CHANGED:
//							break;
//						case WM_NOTIFICATION_LOST_FOCUS:
//							break;

                    }
                    break;
                case GUI_ID_MULTIEDIT0:
                    switch(NCode)
                    {
                        case WM_NOTIFICATION_SEL_CHANGED:
                            OnMultiEditSelChanged(pMsg);
                            break;
                    }
                    break;
//				case 0x1ff: /*在打开位图button创建的又一个button*/
//                    switch(NCode)
//                    {
//                        case WM_NOTIFICATION_RELEASED:
//                            OnButton3Release(pMsg);
//                            break;
//                    }
//                    break;

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
//extern const GUI_FONT GUI_FontHZ_SimSun_13;
short hwin,hGUI_ID_DROPDOWN0,hGUI_ID_DROPDOWN1,hGUI_ID_BUTTON0,hGUI_ID_BUTTON1,hGUI_ID_BUTTON2,hGUI_ID_MULTIEDIT0;
void Win_Init(void) 
{ 	
	
    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */

    hwin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);

	/*获取描述符*/
	hGUI_ID_DROPDOWN0 = WM_GetDialogItem(hwin,GUI_ID_DROPDOWN0);
	hGUI_ID_DROPDOWN1 = WM_GetDialogItem(hwin,GUI_ID_DROPDOWN1);
	hGUI_ID_BUTTON0 = WM_GetDialogItem(hwin,GUI_ID_BUTTON0);
	hGUI_ID_BUTTON1 = WM_GetDialogItem(hwin,GUI_ID_BUTTON1);
	hGUI_ID_MULTIEDIT0 = WM_GetDialogItem(hwin,GUI_ID_MULTIEDIT0);

	/*设置下拉列表的字体*/
	DROPDOWN_SetFont(hGUI_ID_DROPDOWN0,&GUI_Font8x13_ASCII);
	DROPDOWN_SetFont(hGUI_ID_DROPDOWN1,&GUI_Font8x13_ASCII);

	/*开启下了列表的自动滚动条*/
	DROPDOWN_SetAutoScroll(hGUI_ID_DROPDOWN0,1);
	DROPDOWN_SetAutoScroll(hGUI_ID_DROPDOWN1,1);

	/*設置多行編輯器字體*/
	MULTIEDIT_SetFont(hGUI_ID_MULTIEDIT0,&GUI_Font8x13_ASCII);

	/*设置只读*/
	MULTIEDIT_SetReadOnly(hGUI_ID_MULTIEDIT0,0);

	/*设置多行编辑的自动滚动条*/
	MULTIEDIT_SetAutoScrollH(hGUI_ID_MULTIEDIT0,1);
	MULTIEDIT_SetAutoScrollV(hGUI_ID_MULTIEDIT0,1);

	/*不允许框架结构移动*/
	FRAMEWIN_SetMoveable(hwin,0);
}

