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
File        : WM__UpdateChildPositions.C
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
*       WM__UpdateChildPositions
*
* Purpose:
*   Move and/or resize all children of a resized window.
*   What exactly happens to the window depends on how the edges are
*   anchored.
*/
void WM__UpdateChildPositions(WM_Obj* pObj, int dx0, int dy0, int dx1, int dy1) {
  WM_HWIN hChild;
  WM_Obj* pChild;
  int dx, dy, dw, dh;
  for (hChild = pObj->hFirstChild; hChild; hChild = pChild->hNext) {
    int Status;
    GUI_RECT rOld, rNew;
    pChild = WM_H2P(hChild);
    /* Compute size of new rectangle */
    rOld = pChild->Rect;
    rNew = rOld;
    Status = pChild->Status & (WM_SF_ANCHOR_RIGHT | WM_SF_ANCHOR_LEFT);
    switch (Status) {
      case WM_SF_ANCHOR_RIGHT:                      /* Right ANCHOR : Move window with right side */
        rNew.x0 += dx1;
        rNew.x1 += dx1;
        break;
      case WM_SF_ANCHOR_RIGHT | WM_SF_ANCHOR_LEFT:    /* Left & Right ANCHOR: Resize window */
        rNew.x0 += dx0;
        rNew.x1 += dx1;
        break;
      default:                                    /* Left ANCHOR: Move window with left side of parent */
        rNew.x0 += dx0;
        rNew.x1 += dx0;
    }
    Status = pChild->Status & (WM_SF_ANCHOR_TOP   | WM_SF_ANCHOR_BOTTOM);
    switch (Status) {
      case WM_SF_ANCHOR_BOTTOM:                     /* Bottom ANCHOR */
        rNew.y0 += dy1;
        rNew.y1 += dy1;
        break;
      case WM_SF_ANCHOR_BOTTOM | WM_SF_ANCHOR_TOP:    /* resize window */
        rNew.y0 += dy0;
        rNew.y1 += dy1;
        break;
      default:                                    /* Top ANCHOR */
        rNew.y0 += dy0;
        rNew.y1 += dy0;
    }
    /* Set new window position using Move and Resize as required */
    dx = rNew.x0 - rOld.x0;
    dy = rNew.y0 - rOld.y0;
    if (dx || dy) {
      WM_MoveWindow(hChild, dx, dy);
    }
    dw = (rNew.x1 - rNew.x0) - (rOld.x1 - rOld.x0);
    dh = (rNew.y1 - rNew.y0) - (rOld.y1 - rOld.y0);
    if (dw || dh) {
      WM_ResizeWindow(hChild, dw, dh);
    }
  }
}

#else
  void WM_UpdateChildPositions_C(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
