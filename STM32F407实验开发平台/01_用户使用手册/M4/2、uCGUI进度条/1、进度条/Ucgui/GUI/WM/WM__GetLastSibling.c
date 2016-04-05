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
File        : WM__GetLastSibling.c
Purpose     : Implementation of WM__GetLastSibling
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
*       WM__GetLastSibling

  Return value: Handle of last sibling
*/
WM_HWIN WM__GetLastSibling(WM_HWIN hWin) {
  WM_Obj* pWin;
  for (; hWin; hWin = pWin->hNext) {
    pWin = WM_H2P(hWin);
    if (pWin->hNext == 0) {
      break;
    }
  }
  return hWin;
}

#else
  void WM__GetLastSibling_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
