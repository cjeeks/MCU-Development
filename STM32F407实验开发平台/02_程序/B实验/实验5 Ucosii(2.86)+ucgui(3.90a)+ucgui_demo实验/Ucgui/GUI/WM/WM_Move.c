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
File        : WM_Move.C
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/


/*********************************************************************
*
*       _MoveDescendents
*
* Description
*   Moves _MoveDescendents.
*   Since the parent has already been moved, there is no need to
*   take care of invalidation.
*
* Parameters
*   hWin    The first of all descendents to be moved (first child)
*/
static void _MoveDescendents(WM_HWIN hWin, int dx, int dy) {
  WM_Obj* pWin;

  for (;hWin; hWin = pWin->hNext) {
    pWin = WM_HANDLE2PTR(hWin);
    GUI_MoveRect(&pWin->Rect, dx, dy);
    GUI_MoveRect(&pWin->InvalidRect, dx, dy);
    _MoveDescendents(pWin->hFirstChild, dx, dy);  /* Children need to be moved along ...*/
    WM__SendMsgNoData(hWin, WM_MOVE);
  }
}

/*********************************************************************
*
*       Public module internal code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__MoveWindow
*/
void WM__MoveWindow(WM_HWIN hWin, int dx, int dy) {
  GUI_RECT r;
  WM_Obj* pWin;
  if (hWin) {
    pWin = WM_HANDLE2PTR(hWin);
    r = pWin->Rect;
    GUI_MoveRect(&pWin->Rect, dx, dy);
    GUI_MoveRect(&pWin->InvalidRect, dx, dy);
    _MoveDescendents(pWin->hFirstChild, dx, dy);  /* Children need to be moved along ...*/
    /* Invalidate old and new area ... */
    if (pWin->Status & WM_SF_ISVIS) {
      WM_InvalidateArea(&pWin->Rect);     /* Invalidate new area */
      WM_InvalidateArea(&r)         ;     /* Invalidate old area */
    }
    WM__SendMsgNoData(hWin, WM_MOVE);             /* Notify window it has been moved */
  }
}

/*********************************************************************
*
*       WM__MoveTo
*/
void WM__MoveTo(WM_HWIN hWin, int x, int y) {
  if (hWin) {
    WM_Obj* pWin = WM_HANDLE2PTR(hWin);
    x -= pWin->Rect.x0;
    y -= pWin->Rect.y0;
    WM__MoveWindow(hWin, x, y);
  }
}

/*********************************************************************
*
*       Public API code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_MoveWindow
*/
void WM_MoveWindow(WM_HWIN hWin, int dx, int dy) {
  WM_LOCK(); {
    WM__MoveWindow(hWin, dx, dy);
  } WM_UNLOCK();
}

/*********************************************************************
*
*       WM_MoveTo
*/
void WM_MoveTo(WM_HWIN hWin, int x, int y) {
  WM_LOCK(); {
    WM__MoveTo(hWin, x, y);
  } WM_UNLOCK();
}

#else
  void WM_Move_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
