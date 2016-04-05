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
File        : WM_OnKey.c
Purpose     : Implementation of WM_OnKey
---------------------------END-OF-HEADER------------------------------
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
*       WM_OnKey

  Returns:
    0 if message could not be handled
*/
int WM_OnKey(int Key, int Pressed) {
  int r = 0;
  WM_MESSAGE Msg;
  WM_LOCK();
  if (WM__hWinFocus != 0) {
    WM_KEY_INFO Info;
    Info.Key = Key;
    Info.PressedCnt = Pressed;
    Msg.MsgId = WM_KEY;
    Msg.Data.p = &Info;
    WM__SendMessage(WM__hWinFocus, &Msg);
    r = 1;
  }
  WM_UNLOCK();
  return r;
}

#else
  void WM_OnKey_c(void);
  void WM_OnKey_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
