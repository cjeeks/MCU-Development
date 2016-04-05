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
File        : WM_GetPrevSibling.c
Purpose     : Windows manager, add. module
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
*       WM_GetPrevSibling
*/
WM_HWIN WM_GetPrevSibling(WM_HWIN hWin) {
  WM_HWIN hPrev = 0;
  WM_LOCK();
  if (hWin) {
    hPrev = WM__GetPrevSibling(hWin);
  }
  WM_UNLOCK();
  return hPrev;
}

#else                                       /* Avoid empty object files */
  void WM_GetPrevSibling_C(void);
  void WM_GetPrevSibling_C(void) {}
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
