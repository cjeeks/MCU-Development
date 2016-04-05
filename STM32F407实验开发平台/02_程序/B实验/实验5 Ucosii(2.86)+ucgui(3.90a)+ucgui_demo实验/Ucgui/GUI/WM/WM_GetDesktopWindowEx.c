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
File        : WM_GetDesktopWindowEx.c
Purpose     : Implementation of WM_GetDesktopWindowEx
----------------------------------------------------------------------
*/

#include "WM_Intern_ConfDep.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_GetDesktopWindowEx
*/
WM_HWIN WM_GetDesktopWindowEx(unsigned int LayerIndex) {
  WM_HWIN r = WM_HWIN_NULL;
  if (LayerIndex < GUI_NUM_LAYERS) {
    r = WM__ahDesktopWin[LayerIndex];
  }
  return r;
}


#else
  void WM_GetDesktopWindowEx_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
