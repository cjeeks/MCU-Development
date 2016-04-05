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
File        : WM_BringToBottom.c
Purpose     : Window manager routine
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_BringToBottom
*/
void WM_BringToBottom(WM_HWIN hWin) {
  WM_HWIN hParent;
  WM_HWIN hPrev;
  WM_Obj* pWin;
  WM_Obj* pPrev;
  WM_Obj* pParent;
  WM_LOCK();
  if (hWin) {
    pWin = WM_H2P(hWin);
    hPrev = WM__GetPrevSibling(hWin);
    if (hPrev) {                   /* If there is no previous one, there is nothing to do ! */
      hParent = WM_GetParent(hWin);
      pParent = WM_H2P(hParent);
      /* unlink hWin */
      pPrev = WM_H2P(hPrev);
      pPrev->hNext = pWin->hNext;
      /* Link from parent (making it the first child) */
      pWin->hNext = pParent->hFirstChild;
      pParent->hFirstChild = hWin;
      /* Send message in order to make sure top window will be drawn */
      WM_InvalidateArea(&pWin->Rect);
    }
  }
  WM_UNLOCK();
}

#else
  void WM_BringToBottom_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
