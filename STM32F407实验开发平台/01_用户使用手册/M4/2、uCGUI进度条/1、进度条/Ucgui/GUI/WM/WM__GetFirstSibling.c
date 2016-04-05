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
File        : WM__GetFirstSibling.c
Purpose     : Implementation of WM__GetFirstSibling
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
*       WM__GetFirstSibling

  Return value: Handle of parent, 0 if none
*/
WM_HWIN WM__GetFirstSibling(WM_HWIN hWin) {
  hWin = WM_GetParent(hWin);
  return (hWin) ? WM_HANDLE2PTR(hWin)->hFirstChild : 0;
}

#else
  void WM__GetFirstSibling_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
