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
File        : WM_SendToParent.c
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
*       WM_SendToParent
*/
void WM_SendToParent(WM_HWIN hChild, WM_MESSAGE* pMsg) {
  if (pMsg) {
    WM_HWIN hParent;
    WM_LOCK();
    hParent = WM_GetParent(hChild);
    if (hParent) {
      pMsg->hWinSrc = hChild;
      WM_SendMessage(hParent, pMsg);
    }
    WM_UNLOCK();
  }
}

#else
  void WM_SendToParent_C(void) {}   /* Avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
