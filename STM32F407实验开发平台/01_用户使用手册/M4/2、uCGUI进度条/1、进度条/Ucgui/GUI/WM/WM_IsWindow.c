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
File        : WM_IsWindow.c
Purpose     : Windows manager, implementation of WM_IsWindow
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
*       WM_IsWindow
*/
int WM_IsWindow(WM_HWIN hWin) {
  int r;
  WM_LOCK();
  r = WM__IsWindow(hWin);
  WM_UNLOCK();
  return r;
}

#else
  void WM_IsWindow_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
