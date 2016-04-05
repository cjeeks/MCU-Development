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
File        : WM_SetXSize.c
Purpose     : Windows manager, add. module
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
*       WM_SetXSize
*/
int WM_SetXSize(WM_HWIN hWin, int XSize) {
  WM_Obj* pWin;
  int dx;
  int r = 0;
  if (hWin) {
    WM_LOCK();
    pWin = WM_H2P(hWin);
    dx = XSize - (pWin->Rect.x1 - pWin->Rect.x0 + 1);
    WM_ResizeWindow(hWin, dx, 0);
    r = pWin->Rect.x1 - pWin->Rect.x0 + 1;
    WM_UNLOCK();
  }
  return r;
}

#else
  void WM_SetXSize_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
