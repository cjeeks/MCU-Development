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
File        : WMTouch.c
Purpose     : Windows manager, touch support
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"
#include "GUIDebug.h"

#if (GUI_WINSUPPORT)

/*********************************************************************
*
*          Public data
*
**********************************************************************
*/

WM_CRITICAL_HANDLE  WM__CHWinModal;
WM_CRITICAL_HANDLE  WM__CHWinLast;

/*********************************************************************
*
*          Modul internal routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__IsInModalArea
*/
int WM__IsInModalArea(WM_HWIN hWin) {
  if ((WM__CHWinModal.hWin == 0) || WM__IsAncestor(hWin, WM__CHWinModal.hWin) || (hWin == WM__CHWinModal.hWin)) {
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       WM__SendPIDMessage
*
* Purpose:
*   Sends a PID -type message to the affected window.
*   All ancestors are notified of this by sending a WM_TOUCH_CHILD
*   message.
*
*/
void WM__SendPIDMessage(WM_HWIN hWin, WM_MESSAGE* pMsg) {
  WM_MESSAGE Msg;
  /* Send message to the affected window */
  Msg = *pMsg;                 /* Save message as it may be modified in callback (as return value) */
  WM__SendMessageIfEnabled(hWin, &Msg);
  /* Send notification to all ancestors.
     We need to check if the window which has received the last message still exists,
     since it may have deleted itself and its parent as result of the message.
  */
  Msg.hWinSrc = hWin;
  Msg.MsgId   = WM_TOUCH_CHILD;
  while (WM_IsWindow(hWin)) {
    hWin = WM_GetParent(hWin);
    if (hWin) {
      Msg.Data.p  = pMsg;            /* Needs to be set for each window, as callback is allowed to modify it */
      WM__SendMessageIfEnabled(hWin, &Msg);    /* Send message to the ancestors */
    }
  }
}

/*********************************************************************
*
*       WM__SendTouchMessage
*/
void WM__SendTouchMessage(WM_HWIN hWin, WM_MESSAGE* pMsg) {
  GUI_PID_STATE* pState;
  pState     = (GUI_PID_STATE*)pMsg->Data.p;
  if (pState) {
    WM_Obj* pWin;
    pWin       = WM_H2P(hWin);
    pState->x -= pWin->Rect.x0;
    pState->y -= pWin->Rect.y0;
  }
  WM__SendPIDMessage(hWin, pMsg);
}

/*********************************************************************
*
*          Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Screen2Win
*/
static WM_HWIN _Screen2Win(GUI_PID_STATE* pState) {
  if (WM__hCapture == 0) {
    return WM_Screen2hWin(pState->x, pState->y);
  } 
  return WM__hCapture;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_HandlePID       
*
* Polls the touch screen. If something has changed,
* sends a message to the concerned window.
*
* Return value:
*   0 if nothing has been done
*   1 if touch message has been sent
*/
int WM_HandlePID(void) {
  int r = 0;
  WM_MESSAGE Msg;
  WM_CRITICAL_HANDLE CHWin;
  GUI_PID_STATE State, StateNew;
  GUI_PID_GetState(&StateNew);
  WM_LOCK();
  WM__AddCriticalHandle(&CHWin);
  if ((WM_PID__StateLast.x != StateNew.x) || (WM_PID__StateLast.y != StateNew.y) || (WM_PID__StateLast.Pressed != StateNew.Pressed)) {
    #if GUI_SUPPORT_CURSOR
      GUI_CURSOR_SetPosition(StateNew.x, StateNew.y);
    #endif
    CHWin.hWin = _Screen2Win(&StateNew);
    if (WM__IsInModalArea(CHWin.hWin)) {
      /*
       * Send WM_PID_STATE_CHANGED message if state has changed (just pressed or just released)
       */
      if ((WM_PID__StateLast.Pressed != StateNew.Pressed) && CHWin.hWin) {
        WM_PID_STATE_CHANGED_INFO Info;
        WM_Obj* pWin;
        pWin = WM_H2P(CHWin.hWin);
        Info.State     = StateNew.Pressed;
        Info.StatePrev = WM_PID__StateLast.Pressed;
        Info.x         = StateNew.x - pWin->Rect.x0;
        Info.y         = StateNew.y - pWin->Rect.y0;
        Msg.Data.p = &Info;
        Msg.MsgId  = WM_PID_STATE_CHANGED;
        WM__SendMessageIfEnabled(CHWin.hWin, &Msg);
      }
      /*
       * Send WM_TOUCH message(s)
       * Note that we may have to send 2 touch messages.
       */
      if (WM_PID__StateLast.Pressed | StateNew.Pressed) {    /* Only if pressed or just released */
        Msg.MsgId = WM_TOUCH;
        r = 1;
        /*
         * Tell window if it is no longer pressed
         * This happens for 2 possible reasons:
         * a) PID is released
         * b) PID is moved out
         */
        if (WM__CHWinLast.hWin != CHWin.hWin) {
          if (WM__CHWinLast.hWin != 0) {
            if (StateNew.Pressed) {
              /* Moved out -> no longer in this window
               * Send a NULL pointer as data
               */
              Msg.Data.p = NULL;
            } else {
              /* Last window needs to know that it has been "Released"
               * Send last coordinates 
               */
              State.x       = WM_PID__StateLast.x;
              State.y       = WM_PID__StateLast.y;
              State.Pressed = 0;
              Msg.Data.p = (void*)&State;
            }
            GUI_DEBUG_LOG1 ("\nSending WM_Touch to LastWindow %d (out of area)", WM__CHWinLast.hWin);
            WM__SendTouchMessage(WM__CHWinLast.hWin, &Msg);
            WM__CHWinLast.hWin = 0;
          }
        }
        /* Sending WM_Touch to current window */
        if (CHWin.hWin) {
          /* convert screen into window coordinates */
          State = StateNew;
          /* Remember window */
          if (State.Pressed) {
            WM__CHWinLast.hWin = CHWin.hWin;
          } else {
            /* Handle automatic capture release */
            if (WM__CaptureReleaseAuto) {
              WM_ReleaseCapture();
            }
            WM__CHWinLast.hWin = 0;
          }
          Msg.Data.p = (void*)&State;
          WM__SendTouchMessage(CHWin.hWin, &Msg);
        }
      }
      /*
       * Send WM_MOUSEOVER message
       */
      #if GUI_SUPPORT_MOUSE
      else {
        /* Send WM_MOUSEOVER Message */
        if (CHWin.hWin) {
          /* Do not send messages to disabled windows */
          if (WM__IsEnabled(CHWin.hWin)) {
            State      = StateNew;
            Msg.MsgId  = WM_MOUSEOVER;
            Msg.Data.p = (void*)&State;
            WM__SendTouchMessage(CHWin.hWin, &Msg);
          }
        }
      }
      #endif
    }
    /* Store the new state */
    WM_PID__StateLast = StateNew;
  }
  WM__RemoveCriticalHandle(&CHWin);
  WM_UNLOCK();
  return r;
}

#else
  void WM_Touch_c(void) {} /* avoid empty object files */
#endif  /* (GUI_WINSUPPORT & GUI_SUPPORT_TOUCH) */

/*************************** End of file ****************************/

