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
File        : WM_IsCompletelyVisible.c
Purpose     : Windows manager, implementation of said function
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
*       _IsEqualRect
*
*/
static char _CompareRect(const GUI_RECT * pRect0, const GUI_RECT * pRect1 ) {
  if (pRect0->x0 != pRect1->x0) {
    return 1;                          /* Not equal */
  }
  if (pRect0->x1 != pRect1->x1) {
    return 1;                          /* Not equal */
  }
  if (pRect0->y0 != pRect1->y0) {
    return 1;                          /* Not equal */
  }
  if (pRect0->y1 != pRect1->y1) {
    return 1;                          /* Not equal */
  }
  return 0;                            /* Equal */
}

/*********************************************************************
*
*        _WindowSiblingsOverlapRect
*
*/
static char _WindowSiblingsOverlapRect(WM_HWIN iWin, GUI_RECT* pRect) {
  WM_Obj* pWin;
  for (; iWin; iWin = pWin->hNext) { 
    int Status = (pWin = WM_H2P(iWin))->Status;
    /* Check if this window affects us at all */    
    if (Status & WM_SF_ISVIS) {
      /* Check if this window affects us at all */    
      if (GUI_RectsIntersect(pRect, &pWin->Rect)) {
        return 1;
      }
    }
  }
  return 0;
}


/*********************************************************************
*
*       _HasOverlap
*/
static int _HasOverlap(WM_Obj * pWin, GUI_RECT * pRect) {
  WM_Obj * pParent;
  WM_HMEM hParent;
  /* Step 1:
   Check if there are any visible children. If this is so, then the
   window has an overlap.
   */
  /* Check all children */
  if (_WindowSiblingsOverlapRect(pWin->hFirstChild, pRect)) {
    return 1;
  }

  /* STEP 2:
       Find out the max. height (r.y1) if we are at the left border.
       Since we are using the same height for all IVRs at the same y0,
       we do this only for the leftmost one.
  */

  /* Iterate over all windows which are above */
  /* Check all siblings above (Iterate over Parents and top siblings (hNext) */
  for (hParent = pWin->hParent; hParent; hParent = pParent->hParent) {
    pParent = WM_H2P(hParent);
    if (_WindowSiblingsOverlapRect(pParent->hNext, pRect)) {
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _IsCompletelyVisible
*
*/
static char _IsCompletelyVisible(WM_HWIN hWin) {
  WM_Obj * pWin;
  GUI_RECT Rect;

  pWin = WM_H2P(hWin);
  Rect = pWin->Rect;
  if (WM__ClipAtParentBorders(&Rect, hWin) == 0) {
    return 0;                 /* Nothing is left */
  }
  /* Check if the window is still the original one */
  if (_CompareRect(&Rect, &pWin->Rect)) {
    return 0;                 /* Not completely visible */
  }
  /* Now the difficult part ...
     Find the rectangles.
  */
  if (_HasOverlap(pWin, &Rect)) {
    return 0;
  }
  return 1;                   /* Is completely visible */
}


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_IsCompletelyVisible
*
*/
char WM_IsCompletelyVisible(WM_HWIN hWin) {
  int r = 0;
  if (hWin) {
    WM_LOCK();
    r = _IsCompletelyVisible(hWin);
    WM_UNLOCK();
  }
  return r;
}

#else
  void WM_IsCompletelyVisible_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
