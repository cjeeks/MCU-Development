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
File        : WM_GetFocussedWindow.c
Purpose     : Implementation of said function
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
*       WM_GetFocussedWindow
*/
WM_HWIN WM_GetFocussedWindow(void) {
  WM_HWIN r;
  WM_LOCK();
  r = WM__hWinFocus;
  WM_UNLOCK();
  return r;
}

#else
  void WM_GetFocussedWindow_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
