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
File        : WINDOW.c
Purpose     : Window routines
---------------------------END-OF-HEADER------------------------------
*/


#include <stdlib.h>
#include <string.h>
#include "DIALOG.h"
#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

#ifndef WINDOW_BKCOLOR_DEFAULT
  #define WINDOW_BKCOLOR_DEFAULT 0xC0C0C0
#endif

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  WM_CALLBACK* cb;
  WM_HWIN hFocussedChild;
  WM_DIALOG_STATUS* pDialogStatus;
} WINDOW_OBJ;

#define WINDOW_H2P(h) (WINDOW_OBJ*)WM_H2P(h)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

GUI_COLOR WINDOW__DefaultBkColor = WINDOW_BKCOLOR_DEFAULT;

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _OnChildHasFocus
*/
static void _OnChildHasFocus(WM_HWIN hWin, WINDOW_OBJ* pObj, const WM_MESSAGE* pMsg) {
  if (pMsg->Data.p) {
    const WM_NOTIFY_CHILD_HAS_FOCUS_INFO * pInfo = (const WM_NOTIFY_CHILD_HAS_FOCUS_INFO *)pMsg->Data.p;
    int IsDesc = WM__IsAncestorOrSelf(pInfo->hNew, hWin);
    if (!IsDesc) {  /* A child has received the focus, Framewindow needs to be activated */
      /* Remember the child which had the focus so we can reactive this child */
      if (WM__IsAncestor(pInfo->hOld, hWin)) {
        pObj->hFocussedChild = pInfo->hOld;
      }
    }
  }
}

/*********************************************************************
*
*       _cb
*/
static void _cb(WM_MESSAGE* pMsg) {
  WM_HWIN hObj;
  WINDOW_OBJ* pObj;
  WM_CALLBACK* cb;
  hObj = pMsg->hWin;
  pObj = WINDOW_H2P(hObj);
  cb   = pObj->cb;
  switch (pMsg->MsgId) {
  case WM_HANDLE_DIALOG_STATUS:
    if (pMsg->Data.p) {                           /* set pointer to Dialog status */
      pObj->pDialogStatus = (WM_DIALOG_STATUS*)pMsg->Data.p;
    } else {                                      /* return pointer to Dialog status */
      pMsg->Data.p = pObj->pDialogStatus;      
    }
    return;
  case WM_SET_FOCUS:
    if (pMsg->Data.v) {   /* Focus received */
      if (pObj->hFocussedChild && (pObj->hFocussedChild != hObj)) {
        WM_SetFocus(pObj->hFocussedChild);
      } else {
        pObj->hFocussedChild = WM_SetFocusOnNextChild(hObj);
      }
      pMsg->Data.v = 0;   /* Focus change accepted */
    }
    return;
  case WM_GET_ACCEPT_FOCUS:
    WIDGET_HandleActive(hObj, pMsg);
    return;
  case WM_NOTIFY_CHILD_HAS_FOCUS:
    _OnChildHasFocus(hObj, pObj, pMsg);
    return;
  case WM_KEY:
    if (((const WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt > 0) {
      int Key = ((const WM_KEY_INFO*)(pMsg->Data.p))->Key;
      switch (Key) {
      case GUI_KEY_TAB:
        pObj->hFocussedChild = WM_SetFocusOnNextChild(hObj);
        break;                    /* Send to parent by not doing anything */
      }
    }
    break;
  case WM_PAINT:
    LCD_SetBkColor(WINDOW__DefaultBkColor);
    GUI_Clear();
    break;
  case WM_GET_BKCOLOR:
    pMsg->Data.Color = WINDOW__DefaultBkColor;
    return;                       /* Message handled */
  }  
  if (cb) {
    (*cb)(pMsg);
  } else {
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WINDOW_CreateIndirect
*/
WM_HWIN WINDOW_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  WM_HWIN hObj;
  hObj = WM_CreateWindowAsChild(
    pCreateInfo->x0 + x0, pCreateInfo->y0 + y0, pCreateInfo->xSize, pCreateInfo->ySize, hWinParent,
    pCreateInfo->Flags, _cb, sizeof(WINDOW_OBJ) - sizeof(WM_Obj));
  if (hObj) {
    WINDOW_OBJ* pObj;
    WM_LOCK();
    pObj = WINDOW_H2P(hObj);
    WIDGET__Init(&pObj->Widget, pCreateInfo->Id, WIDGET_STATE_FOCUSSABLE);
    pObj->cb             = cb;
    pObj->hFocussedChild = 0;
    WM_UNLOCK();
  }
  return hObj;
}

#else
  void WINDOW_c(void);
  void WINDOW_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
