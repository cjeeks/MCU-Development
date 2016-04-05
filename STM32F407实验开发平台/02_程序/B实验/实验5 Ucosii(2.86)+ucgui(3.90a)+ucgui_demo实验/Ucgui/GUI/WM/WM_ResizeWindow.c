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
File        : WM_ResizeWindow.C
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include <stddef.h>
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
*       WM_ResizeWindow
*/
void WM_ResizeWindow(WM_HWIN hWin, int dx, int dy) {
  GUI_RECT rOld, rNew, rMerge;
  WM_Obj* pWin;
  if (((dx | dy) == 0) || (hWin == 0)){ /* Early out if there is nothing to do */
    return;
  }
  WM_LOCK();
  pWin = WM_HANDLE2PTR(hWin);
  rOld = pWin->Rect;
  rNew = rOld;
  if (dx) {
    if ((pWin->Status & WM_SF_ANCHOR_RIGHT) && (!(pWin->Status & WM_SF_ANCHOR_LEFT))) {
      rNew.x0 -= dx;
    } else {
      rNew.x1 += dx;
    }
  }
  if (dy) {
    if ((pWin->Status & WM_SF_ANCHOR_BOTTOM) && (!(pWin->Status & WM_SF_ANCHOR_TOP))) {
      rNew.y0 -= dy;
    } else {
      rNew.y1 += dy;
    }
  }
  GUI_MergeRect(&rMerge, &rOld, &rNew);
  pWin->Rect = rNew;
  WM_InvalidateArea(&rMerge);
  WM__UpdateChildPositions(pWin, rNew.x0 - rOld.x0, rNew.y0 - rOld.y0, rNew.x1 - rOld.x1, rNew.y1 - rOld.y1);
  GUI__IntersectRect(&pWin->InvalidRect, &pWin->Rect); /* Make sure invalid area is not bigger than window itself */
  WM__SendMsgNoData(hWin, WM_SIZE);                    /* Send size message to the window */
  WM_UNLOCK();
}

#else
  void WM_ResizeWindow(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
