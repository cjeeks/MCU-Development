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
File        : WM_AttachWindow.c
Purpose     : Windows manager routines
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*         Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_DetachWindow
*/
void WM_DetachWindow(WM_HWIN hWin) {
  if (hWin) {
    WM_HWIN hParent;
    WM_Obj* pWin;
    WM_LOCK();
    pWin = WM_H2P(hWin);
    hParent = pWin->hParent;
    if (hParent) {
      WM_Obj* pParent;
      WM__DetachWindow(hWin);
      pParent = WM_H2P(hParent);
      WM_MoveWindow(hWin, -pParent->Rect.x0,  -pParent->Rect.y0);   /* Convert screen coordinates -> parent coordinates */
      /* ToDo: Invalidate. If Parent window is located at (0,0). */
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       WM_AttachWindow
*/
void WM_AttachWindow(WM_HWIN hWin, WM_HWIN hParent) {
  WM_LOCK();
  if (hParent && (hParent != hWin)) {
    WM_Obj* pWin    = WM_H2P(hWin);
    WM_Obj* pParent = WM_H2P(hParent);
    if (pWin->hParent != hParent) {
      WM_DetachWindow(hWin);
      WM__InsertWindowIntoList(hWin, hParent);
      WM_MoveWindow(hWin, pParent->Rect.x0,  pParent->Rect.y0);    /* Convert parent coordinates -> screen coordinates */
    }
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       WM_AttachWindowAt
*/
void WM_AttachWindowAt(WM_HWIN hWin, WM_HWIN hParent, int x, int y) {
  WM_DetachWindow(hWin);
  WM_MoveTo(hWin, x, y);
  WM_AttachWindow(hWin, hParent);
}


#else
  void WM_AttachWindow_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/

