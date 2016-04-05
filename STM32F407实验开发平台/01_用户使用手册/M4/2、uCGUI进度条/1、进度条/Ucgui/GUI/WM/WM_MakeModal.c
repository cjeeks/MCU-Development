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
File        : WM_MakeModal.c
Purpose     : Windows manager, modal windows
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"
#include "GUIDebug.h"

#if (GUI_WINSUPPORT)

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_MakeModal
*
* Purpose:
*   Makes the window modal.
*   We also need to send a message to the window which has received
*   the last "pressed" message
*
* Return value:
*/
void WM_MakeModal(WM_HWIN hWin) {
  WM_LOCK();
  WM__CHWinModal.hWin = hWin;
  /* Send a message to the window that it is no longer pressed (WM_TOUCH(0)) 
     if it is outside the modal area, because otherwise it will not receive this message any more.
  */
  if (WM__CHWinLast.hWin) {
    if (!WM__IsInModalArea(WM__CHWinLast.hWin)) {
      WM_MESSAGE Msg = {0};
      Msg.MsgId = WM_TOUCH;
      WM__SendPIDMessage(WM__CHWinLast.hWin, &Msg);
      WM__CHWinLast.hWin = 0;
    } 
  }
  WM_UNLOCK();
}

#else
  void WM_MakeModal_c(void) {} /* avoid empty object files */
#endif  /* (GUI_WINSUPPORT & GUI_SUPPORT_TOUCH) */

/*************************** End of file ****************************/
