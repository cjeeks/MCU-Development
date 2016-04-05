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
File        : WM_SetFocusOnPrevChild.c
Purpose     : Implementation of WM_SetFocusOnPrevChild
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
*       _GetPrevChild
*
* Purpose:
*   Returns a handle to the previous child of a window.
*
* Parameters:
*   hParent:  Handle of parent window.
*   hChild:   Handle of child to begin our search to its previous sibling.
*
* Return value:
*   Handle to previous child if we found one.
*   0 if window has no other children.
*/
static WM_HWIN _GetPrevChild(WM_HWIN hChild) {
  WM_HWIN hObj = 0;
  if (hChild) {
    hObj = WM__GetPrevSibling(hChild);
  }
  if (!hObj) {
    hObj = WM__GetLastSibling(hChild);
  }
  if (hObj != hChild) {
    return hObj;
  }
  return 0;
}

/*********************************************************************
*
*       _SetFocusOnPrevChild
*
* Purpose:
*   Sets the focus on previous focussable child of a window.
*
* Return value:
*   Handle of focussed child, if we found an other focussable child
*   as the current. Otherwise the return value is zero.
*/
static WM_HWIN _SetFocusOnPrevChild(WM_HWIN hParent) {
  WM_HWIN hChild, hWin;
  hChild = WM__GetFocussedChild(hParent);
  hChild = _GetPrevChild(hChild);
  hWin   = hChild;
  while ((WM_IsFocussable(hWin) == 0) && hWin) {
    hWin = _GetPrevChild(hWin);
    if (hWin == hChild) {
      break;
    }
  }
  if (WM_SetFocus(hWin) == 0) {
    return hWin;
  }
  return 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetFocusOnPrevChild
*/
WM_HWIN WM_SetFocusOnPrevChild(WM_HWIN hParent) {
  WM_HWIN r = 0;
  if (hParent) {
    WM_LOCK();
    r = _SetFocusOnPrevChild(hParent);
    WM_UNLOCK();
  }
  return r;
}

#else
  void WM_SetFocusOnPrevChild_C(void);
  void WM_SetFocusOnPrevChild_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
