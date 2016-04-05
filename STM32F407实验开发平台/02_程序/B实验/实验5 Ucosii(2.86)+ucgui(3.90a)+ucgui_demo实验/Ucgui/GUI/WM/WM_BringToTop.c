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
File        : WM_BringToTop.c
Purpose     : Windows manager routine
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*         Data types
*
**********************************************************************
*/

typedef struct {
  GUI_RECT Rect;
} VCDATA;

/*********************************************************************
*
*         Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _cbInvalidateOne
*/
static void _cbInvalidateOne(WM_HWIN hWin, void * p) {
  GUI_USE_PARA(p);
  WM_InvalidateWindow(hWin);
}

/*********************************************************************
*
*       _InvalidateWindowAndDescs
*/
static void _InvalidateWindowAndDescs(WM_HWIN hWin) {
  WM_InvalidateWindow(hWin);
  WM_ForEachDesc(hWin, _cbInvalidateOne, 0);
}

/*********************************************************************
*
*       _BringToTop
*/
static void _BringToTop(WM_HWIN hWin) {
  WM_HWIN hNext, hParent;
  WM_Obj * pWin, * pNext;
  if (hWin) {
    pWin = WM_H2P(hWin);
    hNext = pWin->hNext;
    /* Is window alread on top ? If so, we are done. (Not required, just an optimization) */
    if (hNext == 0) {
      return;
    }
    /* For non-top windows, it is good enough if the next one is a stay-on-top-window (Not required, just an optimization) */
    if ((pWin->Status & WM_SF_STAYONTOP) == 0) {
      pNext = WM_H2P(hNext);
      if (pNext->Status & WM_SF_STAYONTOP) {
        return;
      }
    }
    hParent = pWin->hParent;
    WM__RemoveWindowFromList(hWin);
    WM__InsertWindowIntoList(hWin, hParent);
    _InvalidateWindowAndDescs(hWin);
  }
}

/*********************************************************************
*
*         Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_BringToTop
*/
void WM_BringToTop(WM_HWIN hWin) {
  WM_LOCK();
  _BringToTop(hWin);
  WM_UNLOCK();
}

#else
  void WM_BringToTop_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */


/*************************** End of file ****************************/
