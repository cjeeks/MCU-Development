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
File        : WM_SetFocus.c
Purpose     : Implementation of WM_SetFocus
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
*       WM_SetFocus
*
* Purpose:
*   Sets the focus to the specified child. It sends 2 messages:
*    WM_SET_FOCUS(1) to window to receive focus
*    WM_SET_FOCUS(0) to window to lose focus
*
* Return value:
*   0    on success (Focus could be set)
*   !=0  on failure (Windows could not take the focus)
*/
int WM_SetFocus(WM_HWIN hWin) {
  int r;
  WM_MESSAGE Msg = {0};
  WM_LOCK();
  if ((hWin) && (hWin != WM__hWinFocus)) {
    WM_NOTIFY_CHILD_HAS_FOCUS_INFO Info;
    Info.hOld = WM__hWinFocus;
    Info.hNew = hWin;
    Msg.MsgId  = WM_SET_FOCUS;
    /* Send a "no more focus" message to window losing focus */
    Msg.Data.v = 0;
    if (WM__hWinFocus) {
      WM_SendMessage(WM__hWinFocus, &Msg);
    }
    /* Send "You have the focus now" message to the window */
    Msg.Data.v = 1;
    WM_SendMessage(WM__hWinFocus = hWin, &Msg);
    if ((r = Msg.Data.v) == 0) { /* On success only */
      /* Set message to ancestors of window getting the focus */
      while ((hWin = WM_GetParent(hWin)) != 0) {
        Msg.MsgId   = WM_NOTIFY_CHILD_HAS_FOCUS;
        Msg.Data.p = &Info;
        WM_SendMessage(hWin, &Msg);
      }
      /* Set message to ancestors of window loosing the focus */
      hWin = Info.hOld;
      if (WM_IsWindow(hWin)) {    /* Make sure window has not been deleted in the mean time. Can be optimized: _DeleteWindow could clear the handle to avoid this check (RS) */
        while ((hWin = WM_GetParent(hWin)) != 0) {
          Msg.MsgId  = WM_NOTIFY_CHILD_HAS_FOCUS;
          Msg.Data.p = &Info;
          WM_SendMessage(hWin, &Msg);
        }
      }
    }
  } else {
    r = 1;
  }
  WM_UNLOCK();
  return r;
}

#else
  void WM_SetFocus_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
