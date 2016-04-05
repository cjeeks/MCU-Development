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
File        : WM_GetDiagInfo.c
Purpose     : Implementation of diagnostics info
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
*       WM_GetNumWindows
*
*/

int WM_GetNumWindows(void) {
  return WM__NumWindows;
}

/*********************************************************************
*
*       WM_GetNumInvalidWindows
*
*/
int WM_GetNumInvalidWindows(void) {
  return WM__NumInvalidWindows;
}




#else
  void WM_GetDiagInfo_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
