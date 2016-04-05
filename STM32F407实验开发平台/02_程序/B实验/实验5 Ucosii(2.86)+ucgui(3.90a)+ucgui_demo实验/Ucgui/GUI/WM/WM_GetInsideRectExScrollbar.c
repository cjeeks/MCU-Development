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
File        : WM_GetInsideRect.c
Purpose     : Windows manager, submodule
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
*       WM_GetInsideRectExScrollbar
*
  Purpose:
    Return the inside rectangle in client coordinates.
    The inside rectangle is the client rectangle minus the effect,
    which typically reduces the rectangle by 0 - 3 pixels on either side
    (2 for the standard 3D effect).
*/      
void WM_GetInsideRectExScrollbar(WM_HWIN hWin, GUI_RECT* pRect) {
  GUI_RECT rWin, rInside, rScrollbar;
  WM_HWIN hBarV, hBarH;
  U16 WinFlags;
  if (hWin) {
    if (pRect) {
      hBarH = WM_GetDialogItem(hWin, GUI_ID_HSCROLL);
      hBarV = WM_GetDialogItem(hWin, GUI_ID_VSCROLL);
      WM_GetWindowRectEx(hWin, &rWin);     /* The entire window in screen coordinates */
      WM_GetInsideRectEx(hWin, &rInside);
      if (hBarV) {
         WM_GetWindowRectEx(hBarV, &rScrollbar);
         GUI_MoveRect(&rScrollbar, -rWin.x0, -rWin.y0);
         WinFlags = WM_GetFlags(hBarV);
         if ((WinFlags & WM_SF_ANCHOR_RIGHT) && (WinFlags & WM_SF_ISVIS)) {
           rInside.x1 = rScrollbar.x0 - 1;
         }
      }
      if (hBarH) {
         WM_GetWindowRectEx(hBarH, &rScrollbar);
         GUI_MoveRect(&rScrollbar, -rWin.x0, -rWin.y0);
         WinFlags = WM_GetFlags(hBarH);
         if ((WinFlags & WM_SF_ANCHOR_BOTTOM) && (WinFlags & WM_SF_ISVIS)) {
           rInside.y1 = rScrollbar.y0 - 1;
         }
      }
      *pRect = rInside;
    }
  }
}

#else
  void WM_GetInsideRectExScrollbar(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
