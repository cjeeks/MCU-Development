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
File        : WM_ValidateWindow.c
Purpose     : Implementation of WM_ValidateWindow
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
*       WM_ValidateWindow
*/
void WM_ValidateWindow(WM_HWIN hWin) {
  WM_Obj* pWin;
  WM_LOCK();
  if (hWin) {
    pWin = WM_HANDLE2PTR(hWin);
    if (pWin->Status & WM_SF_INVALID) {
      pWin->Status &= ~WM_SF_INVALID;
      WM__NumInvalidWindows--;
    }
  }
  WM_UNLOCK();
}

#else
  void WM_ValidateWindow_C(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
