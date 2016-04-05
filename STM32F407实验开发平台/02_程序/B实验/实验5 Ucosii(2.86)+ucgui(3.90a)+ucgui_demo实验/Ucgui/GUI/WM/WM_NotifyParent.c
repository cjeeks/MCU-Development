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
File        : WM_NotifyParent.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_NotifyParent
*/
void WM_NotifyParent(WM_HWIN hWin, int Notification) {
  WM_MESSAGE Msg;
  Msg.MsgId   = WM_NOTIFY_PARENT;
  Msg.Data.v  = Notification;
  WM_SendToParent(hWin, &Msg);
}

#else
  void WM_NotifyParent_C(void) {}   /* Avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
