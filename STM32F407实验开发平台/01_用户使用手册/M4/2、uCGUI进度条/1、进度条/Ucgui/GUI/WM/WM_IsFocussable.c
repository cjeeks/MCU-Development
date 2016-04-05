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
File        : WM_IsFocussable.c
Purpose     : Windows manager, implementation of WM_IsFocussable
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_IsFocussable
*/
int WM_IsFocussable(WM_HWIN hWin) {
  int r = 0;
  if (hWin) {
    WM_MESSAGE Msg;
    Msg.Data.v = 0;
    Msg.MsgId  = WM_GET_ACCEPT_FOCUS;
    WM_SendMessage(hWin, &Msg);
    r = Msg.Data.v;
  }
  return r;
}

#else
  void WM_IsFocussable_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
