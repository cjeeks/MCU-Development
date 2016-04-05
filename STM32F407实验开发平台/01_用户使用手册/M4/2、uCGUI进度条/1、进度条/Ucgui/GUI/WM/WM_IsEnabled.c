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
File        : WM_IsEnabled.c
Purpose     : Windows manager function
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_IsEnabled
*/
int WM_IsEnabled(WM_HWIN hObj) {
  int r = 0;
  if (hObj) {
    WM_LOCK();
    r = WM__IsEnabled(hObj);
    WM_UNLOCK();
  }
  return r;
}

#else
  void WM_IsEnabled_c(void) {} /* avoid empty object files */
#endif  /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
