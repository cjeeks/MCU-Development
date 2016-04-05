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
File        : GUI_OnKey.c
Purpose     : Implementation of GUI_StoreKeyMsg
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

#if GUI_WINSUPPORT
  #include "WM.h"
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

#if GUI_WINSUPPORT

static int _KeyMsgCnt;
static struct {
  int Key;
  int PressedCnt;
} _KeyMsg;

#endif

static int _Key;

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/

GUI_KEY_MSG_HOOK* GUI_pfKeyMsgHook;

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GetKey
*/
int GUI_GetKey(void) {
  int r = _Key;
  _Key = 0;
  return r;
}

/*********************************************************************
*
*       GUI_StoreKey
*/
void GUI_StoreKey(int Key) {
  if (!_Key) {
    _Key = Key;
  }
  GUI_X_SIGNAL_EVENT();
}

/*********************************************************************
*
*       GUI_ClearKeyBuffer
*/
void GUI_ClearKeyBuffer(void) {
  while (GUI_GetKey());
}

/*********************************************************************
*
*       GUI_StoreKeyMsg
*/
void GUI_StoreKeyMsg(int Key, int PressedCnt) {
  #if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
  _KeyMsg.Key = Key;
  _KeyMsg.PressedCnt = PressedCnt;
  _KeyMsgCnt = 1;
  GUI_X_SIGNAL_EVENT();
  #else
    GUI_USE_PARA(PressedCnt);
    GUI_StoreKey(Key);
  #endif
}

/*********************************************************************
*
*       GUI_PollKeyMsg
*/
#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
int GUI_PollKeyMsg(void) {
  int r = 0;
  GUI_LOCK();
  if (_KeyMsgCnt) {
    int Key;
    _KeyMsgCnt--;
    Key = _KeyMsg.Key;
    WM_OnKey(Key, _KeyMsg.PressedCnt);
    if (_KeyMsg.PressedCnt == 1) {
      GUI_StoreKey(Key);
    }
    r = 1;              /* We have done something */
  }
  GUI_UNLOCK();
  return r;
}
#endif

/*********************************************************************
*
*       GUI_SendKeyMsg
*
* Purpose:
*   Send the key to a window using the window manager (if available).
*   If no window is ready to take the input, we call the store routine
*   and wait for somebody to poll the buffer.
*/
void GUI_SendKeyMsg(int Key, int PressedCnt) {
  #if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
    if (!WM_OnKey(Key, PressedCnt)) {
      GUI_StoreKeyMsg(Key, PressedCnt);
    }
  #else
    GUI_StoreKeyMsg(Key, PressedCnt);
  #endif
}

/*************************** End of file ****************************/
