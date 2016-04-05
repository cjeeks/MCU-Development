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
File        : WM_SetCapture.c
Purpose     : Implementation of WM_SetCapture
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Public data
*
**********************************************************************
*/


/*********************************************************************
*
*        Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__ReleaseCapture
*/
static void WM__ReleaseCapture(void) {
  if (WM__hCapture) {
    WM_MESSAGE Msg;
    Msg.MsgId  = WM_CAPTURE_RELEASED;
    WM_SendMessage(WM__hCapture, &Msg);
    WM__hCapture = 0;
  }
}

/*********************************************************************
*
*        Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetCapture
*/
void WM_SetCapture(WM_HWIN hObj, int AutoRelease) {
  WM_LOCK();
  if (WM__hCapture != hObj) {
    WM__ReleaseCapture();
  }
  WM__hCapture = hObj;
  WM__CaptureReleaseAuto = AutoRelease;
  WM_UNLOCK();
}

/*********************************************************************
*
*       WM_ReleaseCapture
*/
void WM_ReleaseCapture(void) {
  WM_LOCK();
  WM__ReleaseCapture();
  WM_UNLOCK();
}

#else
  void WM_SetCapture_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
