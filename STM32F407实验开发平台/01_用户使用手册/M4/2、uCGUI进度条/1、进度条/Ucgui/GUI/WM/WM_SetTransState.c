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
File        : WM_SetTransState.c
Purpose     : Implementation of WM_SetTransState
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT && WM_SUPPORT_TRANSPARENCY

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

void WM_SetTransState(WM_HWIN hWin, unsigned State) {
  WM_Obj *pWin;
  WM_LOCK();
  if (hWin) {
    pWin = WM_H2P(hWin);
    if (State & WM_CF_HASTRANS) {
      WM_SetHasTrans(hWin);
    } else {
      WM_ClrHasTrans(hWin);
    }
    if (State & WM_CF_CONST_OUTLINE) {
      if (!(pWin->Status & WM_CF_CONST_OUTLINE)) {
        pWin->Status |= WM_CF_CONST_OUTLINE;
        WM_InvalidateWindow(hWin);
      }
    } else {
      if (pWin->Status & WM_CF_CONST_OUTLINE) {
        pWin->Status &= ~WM_CF_CONST_OUTLINE;
        WM_InvalidateWindow(hWin);
      }
    }
  }
  WM_UNLOCK();
}

#else
  void WM_SetTransState_c(void);
  void WM_SetTransState_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/

