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
File        : WM__GetPrevSibling.c
Purpose     : Implementation of WM__GetPrevSibling
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
*       WM__GetPrevSibling

  Return value: Handle of previous sibling (if any), otherwise 0
*/
WM_HWIN WM__GetPrevSibling(WM_HWIN hWin) {
  WM_HWIN hi;
  WM_Obj* pi;
  for (hi = WM__GetFirstSibling(hWin); hi; hi = pi->hNext) {
    if (hi == hWin) {
      hi = 0;                 /* There is no previous sibling. Return 0 */
      break;
    }
    pi = WM_H2P(hi);
    if (pi->hNext == hWin) {
      break;                  /* We found the previous one ! */
    }
  }
  return hi;
}

#else
  void WM__GetPrevSibling_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
