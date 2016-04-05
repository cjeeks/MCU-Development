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
File        : WM_GetScrollState.c
Purpose     : Implementation of WM_GetScrollState
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_GetScrollState
*/
void WM_GetScrollState(WM_HWIN hObj, WM_SCROLL_STATE* pScrollState) {
  WM_MESSAGE Msg;
  Msg.MsgId  = WM_GET_SCROLL_STATE;
  Msg.Data.p = pScrollState;
  WM_SendMessage(hObj, &Msg);
}

#else
  void WM_GetScrollState_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
