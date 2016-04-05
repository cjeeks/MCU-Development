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
File        : WM__IsEnabled.c
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
*       WM__IsEnabled
*/
int WM__IsEnabled(WM_HWIN hWin) {
  int r = 1;
  if ((WM_H2P(hWin)->Status) & WM_SF_DISABLED) {
    r = 0;
  }
  return r;
}

#else
  void WM__IsEnabled_c(void) {} /* avoid empty object files */
#endif  /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
