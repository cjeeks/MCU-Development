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
File        : WM__GetFocussedChild.c
Purpose     : Implementation of WM__GetFocussedChild
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
*       WM__GetFocussedChild
*/
WM_HWIN WM__GetFocussedChild(WM_HWIN hWin) {
  WM_HWIN r = 0;
  if (WM__IsChild(WM__hWinFocus, hWin)) {
    r = WM__hWinFocus;
  }
  return r;
}

#else
  void WM__GetFocussedChild_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
