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
File        : WM__SendMessageIfEnabled.c
Purpose     : Implementation of WM__SendMessageIfEnabled
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
*       WM__SendMessageIfEnabled
*/
void WM__SendMessageIfEnabled(WM_HWIN hWin, WM_MESSAGE* pMsg) {
  if (WM__IsEnabled(hWin)) {
    WM__SendMessage(hWin, pMsg);
  }
}

#else
  void WM__SendMessageIfEnabled_c(void);
  void WM__SendMessageIfEnabled_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
