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
File        : WM_Paint.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       WM_Paint
*/

void WM_Paint(WM_HWIN hWin) {
  GUI_CONTEXT Context;
  WM_PAINTINFO PaintInfo;
  WM_Obj* pWin;

  WM_ASSERT_NOT_IN_PAINT();
  if (hWin) {
    WM_LOCK();
    GUI_SaveContext(&Context);
    pWin = WM_H2P(hWin);
    WM_SelectWindow(hWin);
    WM_SetDefault();
    WM_InvalidateWindow(hWin);  /* Important ... Window procedure is informed about invalid rect and may optimize */
    /* Paint the window and its overlaying transparent windows */
    PaintInfo.hWin = hWin;
    PaintInfo.pWin = pWin;
    WM__PaintWinAndOverlays(&PaintInfo);
    WM_ValidateWindow(hWin);
    GUI_RestoreContext(&Context);
    WM_UNLOCK();
  }
}

#else
  void WM_Paint(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
