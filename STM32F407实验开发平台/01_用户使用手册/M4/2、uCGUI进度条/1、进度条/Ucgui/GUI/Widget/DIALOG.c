/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : 
Purpose     : Dialog box include
----------------------------------------------------------------------
Open items:
None
--------------------END-OF-HEADER-------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "DIALOG.h"
#include "WIDGET.h"
#include "WM_Intern.h"



#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define colors */
#ifndef DIALOG_BKCOLOR0_DEFAULT
  #define DIALOG_BKCOLOR0_DEFAULT 0xc0c0c0
#endif

/*********************************************************************
*
*       static data;
*
**********************************************************************
*/

static LCD_COLOR _BkColor = DIALOG_BKCOLOR0_DEFAULT;

/*********************************************************************
*
*       Public code: API functions
*
**********************************************************************
*/
/*********************************************************************
*
*       DIALOG_GetBkColor
*/
LCD_COLOR DIALOG_GetBkColor(void) {
  return _BkColor;
}

/*********************************************************************
*
*       DIALOG_SetBkColor
*/
LCD_COLOR DIALOG_SetBkColor(LCD_COLOR BkColor) {
  LCD_COLOR r;
  r = _BkColor;
  _BkColor = BkColor;
  return r;
}
/*********************************************************************
*
*       GUI_SetDialogStatusPtr
*/
void GUI_SetDialogStatusPtr(WM_HWIN hDialog, WM_DIALOG_STATUS* pDialogStatus) {
  WM_MESSAGE Msg = {0};
  Msg.MsgId = WM_HANDLE_DIALOG_STATUS;
  Msg.Data.p = pDialogStatus;
  WM_SendMessage(hDialog, &Msg);
}

/*********************************************************************
*
*       GUI_GetDialogStatusPtr
*/
WM_DIALOG_STATUS*  GUI_GetDialogStatusPtr(WM_HWIN hDialog) {
  WM_MESSAGE Msg = {0};
  Msg.MsgId = WM_HANDLE_DIALOG_STATUS;
  WM_SendMessage(hDialog, &Msg);
  return (WM_DIALOG_STATUS*)Msg.Data.p;
}
/*********************************************************************
*
*       GUI_CreateDialogbox
*/
WM_HWIN GUI_CreateDialogBox(const GUI_WIDGET_CREATE_INFO* paWidget, int NumWidgets, WM_CALLBACK* cb, WM_HWIN hParent,
                            int x0, int y0)
{
  WM_HWIN hDialog = paWidget->pfCreateIndirect(paWidget, hParent, x0, y0, cb);     /* Create parent window */
  WM_HWIN hDialogClient = WM_GetClientWindow(hDialog);
  WIDGET_OrState(hDialog, paWidget->Flags);
  WM_ShowWindow(hDialog);
  WM_ShowWindow(hDialogClient);
  while (--NumWidgets > 0) {
    WM_HWIN hChild;
    paWidget++;
    hChild = paWidget->pfCreateIndirect(paWidget, hDialogClient, 0, 0, 0);     /* Create child window */
    WM_ShowWindow(hChild);
  }
  WM_SetFocusOnNextChild(hDialog);     /* Set the focus to the first child */
  WM_SendMessageNoPara(hDialogClient, WM_INIT_DIALOG);
  return hDialog;
}

/*********************************************************************
*
*       GUI_EndDialog
*/
void GUI_EndDialog(WM_HWIN hDialog, int r) {
  WM_DIALOG_STATUS* pStatus;
  pStatus = GUI_GetDialogStatusPtr(hDialog);
  if (pStatus) {
    pStatus->ReturnValue = r;
    pStatus->Done = 1;
  }
  WM_DeleteWindow(hDialog);
}


/*********************************************************************
*
*       GUI_ExecCreatedDialog
*/
int     GUI_ExecCreatedDialog (WM_HWIN hDialog) {
  WM_DIALOG_STATUS DialogStatus = {0};
  /* Let window know how to send feedback (close info & return value) */
  GUI_SetDialogStatusPtr(hDialog, &DialogStatus);
  while (!DialogStatus.Done) {
    if (!GUI_Exec()) {
      GUI_X_WAIT_EVENT();      /* Wait for event (keyboard, mouse or whatever) */
    }
  }
  return DialogStatus.ReturnValue;
}

/*********************************************************************
*
*       GUI_ExecDialogbox
*
* Purpose:
*  Create and execute a dialog
*  The name is somewhat confusing, it should really be something like
*  GUI_CreateExecDialog. However, we keep it like that for compatibility
*
*/
int GUI_ExecDialogBox(const GUI_WIDGET_CREATE_INFO* paWidget,
                      int NumWidgets, WM_CALLBACK* cb, WM_HWIN hParent, int x0, int y0)
{
  WM_HWIN hDialog;
  hDialog = GUI_CreateDialogBox(paWidget, NumWidgets, cb, hParent, x0, y0);
  return GUI_ExecCreatedDialog(hDialog);
}


#else
  void Dialog_c(void);    /* Avoid problems with empty object modules */
  void Dialog_c(void){}
#endif   /* GUI_WINSUPPORT */

