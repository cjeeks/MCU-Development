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
File        : WM_EnableWindow.c
Purpose     : Implementation of WM_EnableWindow, WM_DisableWindow
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
*       WM_SetEnableState
*/
void WM_SetEnableState(WM_HWIN hWin, int State) {
  WM_Obj* pWin;
  U16 Status;
  WM_LOCK();
  pWin = WM_H2P(hWin);
  Status = pWin->Status;
  if (State) {
    Status &= ~WM_SF_DISABLED;
  } else {
    Status |=  WM_SF_DISABLED;
  }
  if (pWin->Status != Status) {
    WM_MESSAGE Msg;
    pWin->Status = Status;
    Msg.MsgId  = WM_NOTIFY_ENABLE;
    Msg.Data.v = State;
    WM_SendMessage(hWin, &Msg);
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       WM_EnableWindow
*/
void WM_EnableWindow(WM_HWIN hWin) {
  WM_SetEnableState(hWin, 1);
}

/*********************************************************************
*
*       WM_DisableWindow
*/
void WM_DisableWindow(WM_HWIN hWin) {
  WM_SetEnableState(hWin, 0);
}
#else
  void WM_EnableWindow_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
