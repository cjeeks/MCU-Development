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
File        : FRAMEWIN__UpdateButtons.c
Purpose     : 
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "FRAMEWIN_Private.h"

#if GUI_WINSUPPORT


/*********************************************************************
*
*        Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN__UpdateButtons
*
* Purpose:
*   Adjust button positions & size.
*   This is required after resizing the title bar
*/
void FRAMEWIN__UpdateButtons(FRAMEWIN_Obj* pObj, int OldHeight) {
  int TitleHeight = FRAMEWIN__CalcTitleHeight(pObj);
  int Diff = TitleHeight - OldHeight;
  if (Diff) {
    WM_HWIN hLeft;
    WM_HWIN hRight;
    WM_HWIN hChild;
    WM_Obj* pChild;
    GUI_RECT r;
    int xLeft, xRight, n;
    n = 0;
    do {
      hLeft  = hRight = 0;
      xLeft  = GUI_XMAX;
      xRight = GUI_XMIN;
      for (hChild = pObj->Widget.Win.hFirstChild; hChild; hChild = pChild->hNext) {
        pChild = WM_H2P(hChild);
        r = pChild->Rect;
        GUI_MoveRect(&r, -pObj->Widget.Win.Rect.x0, -pObj->Widget.Win.Rect.y0);
        if ((r.y0 == pObj->Props.BorderSize) && ((r.y1 - r.y0 + 1) == OldHeight)) {
          if (pChild->Status & WM_SF_ANCHOR_RIGHT) {
            if (r.x1 > xRight) {
              hRight = hChild;
              xRight = r.x0;
            }
          } else {
            if (r.x0 < xLeft) {
              hLeft = hChild;
              xLeft = r.x0;
            }
          }
        }
      }
      if (hLeft) {
        WM_ResizeWindow(hLeft, Diff, Diff);
        WM_MoveWindow(hLeft, n * Diff, 0);
      }
      if (hRight) {
        WM_ResizeWindow(hRight, Diff, Diff);
        WM_MoveWindow(hRight, -(n * Diff), 0);
      }
      n++;
    } while (hLeft || hRight);
  }
}



#else
  void FRAMEWIN__UpdateButtons_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
