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
File        : FRAMEWIN.c
Purpose     : FRAMEWIN_SetBorderSize
---------------------------END-OF-HEADER------------------------------
*/

#include "FRAMEWIN_Private.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/

/*********************************************************************
*
*       FRAMEWIN_SetBorderSize
*/
void FRAMEWIN_SetBorderSize(FRAMEWIN_Handle hObj, unsigned Size) {
  GUI_LOCK();
  if (hObj) {
    GUI_RECT r;
    WM_Obj * pChild;
    int Diff, OldSize, OldHeight;
    WM_HWIN hChild;
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    OldHeight          = FRAMEWIN__CalcTitleHeight(pObj);
    OldSize            = pObj->Props.BorderSize;
    Diff               = Size - OldSize;
    for (hChild = pObj->Widget.Win.hFirstChild; hChild; hChild = pChild->hNext) {
      pChild = WM_H2P(hChild);
      r = pChild->Rect;
      GUI_MoveRect(&r, -pObj->Widget.Win.Rect.x0, -pObj->Widget.Win.Rect.y0);
      if ((r.y0 == pObj->Props.BorderSize) && ((r.y1 - r.y0 + 1) == OldHeight)) {
        if (pChild->Status & WM_SF_ANCHOR_RIGHT) {
          WM_MoveWindow(hChild, -Diff, Diff);
        } else {
          WM_MoveWindow(hChild, Diff, Diff);
        }
      }
    }
    pObj->Props.BorderSize   = Size;
    FRAMEWIN__UpdatePositions(pObj);
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
}

#else
  void FRAMEWIN_SetBorderSize_C(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
