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
File        : WM_GetOrg.c
Purpose     : Implementation of WM_GetOrg and related functions
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
*       WM_GetWindowOrgX
*/
int WM_GetWindowOrgX(WM_HWIN hWin) {
  int r = 0;
  if (hWin) {
    WM_LOCK();
    r = WM_HANDLE2PTR(hWin)->Rect.x0;
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       WM_GetWindowOrgY
*/
int WM_GetWindowOrgY(WM_HWIN hWin) {
  int r = 0;
  if (hWin) {
    WM_LOCK();
    r = WM_HANDLE2PTR(hWin)->Rect.y0;
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       WM_GetOrgX
*/
int WM_GetOrgX(void) {
  return WM_GetWindowOrgX(GUI_Context.hAWin);
}

/*********************************************************************
*
*       WM_GetOrgY
*/
int WM_GetOrgY(void) {
  return WM_GetWindowOrgY(GUI_Context.hAWin);
}


#else
  void WM_GetOrg_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
