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
File        : WM_MoveChildTo.C
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public API code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_MoveChildTo
*/
void WM_MoveChildTo(WM_HWIN hWin, int x, int y) {
  if (hWin) {
    WM_HWIN hParent;
    WM_LOCK();
    hParent = WM_GetParent(hWin);
    if (hParent) {
      WM_Obj * pParent, * pWin;
      pParent = WM_HANDLE2PTR(hParent);
      pWin    = WM_HANDLE2PTR(hWin);
      x -= pWin->Rect.x0 - pParent->Rect.x0;
      y -= pWin->Rect.y0 - pParent->Rect.y0;
      WM__MoveWindow(hWin, x, y);
    }
    WM_UNLOCK();
  }
}

#else
  void WM_MoveChildTo_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
