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
File        : WM_SetSize.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"
#define WM_DEBUG_LEVEL 1

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetSize
*/
void WM_SetSize(WM_HWIN hWin, int xSize, int ySize) {
  WM_Obj* pWin;
  int dx, dy;
  if (hWin) {
    WM_LOCK();
    pWin = WM_H2P(hWin);
    dx = xSize - (pWin->Rect.x1 - pWin->Rect.x0 + 1);
    dy = ySize - (pWin->Rect.y1 - pWin->Rect.y0 + 1);
    WM_ResizeWindow(hWin, dx, dy);
    WM_UNLOCK();
  }
}

#else
  void WM_SetSize_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
