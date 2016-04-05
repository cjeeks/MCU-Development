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
File        : WM_SendMessageNoPara.c
Purpose     : Implementation of WM_SendMessageNoPara
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
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
*       WM_SendMessageNoPara
*/
void WM_SendMessageNoPara(WM_HWIN hWin, int MsgId) {
  WM_LOCK();
  WM__SendMessageNoPara(hWin, MsgId);
  WM_UNLOCK();
}

#else
  void WM_SendMessageNoPara_c(void);
  void WM_SendMessageNoPara_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
