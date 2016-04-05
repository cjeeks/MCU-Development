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
File        : WM_GetClientRect.c
Purpose     : Windows manager, submodule
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
*       WM_GetClientRectEx
*
  Purpose:
    Return the client rectangle in client coordinates.
    This means for all windows that
    x0 = y0 = 0
    x1 = width - 1
    y1 = height - 1
*/
void WM_GetClientRectEx(WM_HWIN hWin, GUI_RECT* pRect) {
  WM_Obj *pWin;
  WM_LOCK();
  if (hWin) {
    if (pRect) {
      pWin = WM_H2P(hWin);  
      WM__GetClientRectWin(pWin, pRect);
    }
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       WM_GetClientRect
*/
void WM_GetClientRect(GUI_RECT* pRect) {
  WM_HWIN hWin;
  WM_LOCK();
  #if WM_SUPPORT_TRANSPARENCY
    hWin = WM__hATransWindow ? WM__hATransWindow : GUI_Context.hAWin;
  #else
    hWin = GUI_Context.hAWin;
  #endif
  WM_GetClientRectEx(hWin, pRect);
  WM_UNLOCK();
}

#else
  void WM_GetClientRect_Dummy(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
