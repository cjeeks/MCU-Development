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
File        : WM_SetYSize.c
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
*       WM_SetYSize
*/
int WM_SetYSize(WM_HWIN hWin, int YSize) {
  WM_Obj* pWin;
  int dy;
  int r = 0;
  if (hWin) {
    WM_LOCK();
    pWin = WM_H2P(hWin);
    dy = YSize - (pWin->Rect.y1 - pWin->Rect.y0 + 1);
    WM_ResizeWindow(hWin, 0, dy);
    r = pWin->Rect.y1 - pWin->Rect.y0 + 1;
    WM_UNLOCK();
  }
  return r;
}

#else
  void WM_SetYSize_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
