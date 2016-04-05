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
File        : WIDGET.c
Purpose     : Widget core routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

const WIDGET_EFFECT* _pEffectDefault = &WIDGET_Effect_3D;

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _UpdateChildPositions
*/
static void _UpdateChildPostions(WM_HWIN hObj, int Diff) {
  WM_Obj* pObj;
  WM_LOCK();
  pObj = (WM_Obj*)WM_H2P(hObj);
  WM__UpdateChildPositions(pObj, -Diff, -Diff, Diff, Diff);
  WM_UNLOCK();
}

/*********************************************************************
*
*       _EffectRequiresRedraw
*
* Purpose
*   Check if the effect to draw is inside the invalid rectangle.
* Returns:
*   0 if nothing need to be done.
*   1 if the effect needs to be drawn
*/
static int _EffectRequiresRedraw(const WIDGET* pWidget, const GUI_RECT * pRect) {
  int EffectSize = pWidget->pEffect->EffectSize;
  GUI_RECT InvalidRect;
  InvalidRect = pWidget->Win.InvalidRect;
  WM__Client2Screen(&pWidget->Win, &InvalidRect);
  /* Check if there a part of the effect is inside the invalid rectangle */
  if ((pRect->x0 + EffectSize) > InvalidRect.x0) {
    return 1;               /* Overlap ... Drawing required */
  }
  if ((pRect->x1 - EffectSize) < InvalidRect.x1) {
    return 1;               /* Overlap ... Drawing required */
  }
  if ((pRect->y0 + EffectSize) > InvalidRect.y0) {
    return 1;               /* Overlap ... Drawing required */
  }
  if ((pRect->y1 - EffectSize) < InvalidRect.y1) {
    return 1;               /* Overlap ... Drawing required */
  }
  return 0;                 /* No overlap ! */
}


/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WIDGET__RotateRect90
*/
void WIDGET__RotateRect90(WIDGET* pWidget, GUI_RECT* pDest, const GUI_RECT* pRect) {
  int x0, x1, XSize;
  x0 = pRect->x0;
  x1 = pRect->x1;
  XSize = pWidget->Win.Rect.x1 - pWidget->Win.Rect.x0;
  pDest->x0 = XSize - pRect->y1;
  pDest->x1 = XSize - pRect->y0;
  pDest->y0 = x0;
  pDest->y1 = x1;

}

/*********************************************************************
*
*       WIDGET__GetClientRect

  Returns the logical client rectangle, which means the normal
  client rectangle for widgets with their standard orientation
  and the rotated one for rotated widgets.
*/
void WIDGET__GetClientRect(WIDGET* pWidget, GUI_RECT* pRect) {
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    GUI_RECT Rect;
    WM_GetClientRect(&Rect);
    pRect->x0 = Rect.y0;
    pRect->x1 = Rect.y1;
    pRect->y0 = Rect.x0;
    pRect->y1 = Rect.x1;
  } else {
    WM_GetClientRect(pRect);
  }
}

/*********************************************************************
*
*       WIDGET__GetBkColor
*/
GUI_COLOR WIDGET__GetBkColor(WM_HWIN hObj) {
  GUI_COLOR BkColor = WM_GetBkColor(WM_GetParent(hObj));
  if (BkColor == GUI_INVALID_COLOR) {
    BkColor = DIALOG_GetBkColor();
  }
  return BkColor;
}

/*********************************************************************
*
*       WIDGET__GetInsideRect
*/
void WIDGET__GetInsideRect(WIDGET* pWidget, GUI_RECT* pRect) {
  WM__GetClientRectWin(&pWidget->Win, pRect);
  GUI__ReduceRect(pRect, pRect, pWidget->pEffect->EffectSize);
}

/*********************************************************************
*
*       WIDGET__GetXSize
*/
int WIDGET__GetXSize(const WIDGET* pWidget) {
  int r;
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    r = pWidget->Win.Rect.y1 - pWidget->Win.Rect.y0;
  } else {
    r = pWidget->Win.Rect.x1 - pWidget->Win.Rect.x0;
  }
  return r + 1;
}

/*********************************************************************
*
*       WIDGET__GetYSize
*/
int WIDGET__GetYSize(const WIDGET* pWidget) {
  int r;
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    r = pWidget->Win.Rect.x1 - pWidget->Win.Rect.x0;
  } else {
    r = pWidget->Win.Rect.y1 - pWidget->Win.Rect.y0;
  }
  return r + 1;
}

/*******************************************************************
*
*       WIDGET__GetWindowSizeX

  Return width (or height in case of rotation) of window in pixels
*/
int WIDGET__GetWindowSizeX(WM_HWIN hWin) {
  WIDGET* pWidget = WIDGET_H2P(hWin);
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    return WM_GetWindowSizeY(hWin);
  } else {
    return WM_GetWindowSizeX(hWin);
  }
}

/*********************************************************************
*
*       WIDGET_SetState
*/
void WIDGET_SetState(WM_HWIN hObj, int State) {
  WIDGET* pWidget;
  WM_LOCK();
  pWidget = WIDGET_H2P(hObj);
  if (State != pWidget->State) {
    pWidget->State = State;
    WM_Invalidate(hObj);
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       WIDGET_GetState
*/
int WIDGET_GetState(WM_HWIN hObj) {
  int Ret = 0;
  WIDGET * pWidget;
  if (hObj) {
    WM_LOCK();
    pWidget = WIDGET_H2P(hObj);
    Ret = pWidget->State;
    WM_UNLOCK();
  }
  return Ret;
}

/*********************************************************************
*
*       WIDGET_OrState
*/
void WIDGET_OrState(WM_HWIN hObj, int State) {
  if (hObj) {
    WIDGET* pWidget;
    WM_LOCK();
    pWidget = WIDGET_H2P(hObj);
    if (State != (pWidget->State & State)) {
      pWidget->State |= State;
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       WIDGET_AndState

  Purpose:
    Clear flags in the State element of the widget.
    The bits to be cleared are set.
  Example:
    ...(..., 3);   // Clears bit 0, 1 int the state member 

*/
void WIDGET_AndState(WM_HWIN hObj, int Mask) {
  U16 StateNew;
  if (hObj) {
    WIDGET* pWidget;
    WM_LOCK();
    pWidget = WIDGET_H2P(hObj);
    StateNew = pWidget->State & (~Mask);
    if (pWidget->State != StateNew) {
      pWidget->State = StateNew;
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       WIDGET__Init
*/
void WIDGET__Init(WIDGET* pWidget, int Id, U16 State) {
  pWidget->pEffect       = _pEffectDefault;
  pWidget->State         = State;
  pWidget->Id            = Id;
}


/*********************************************************************
*
*       WIDGET_HandleActive
*/
int WIDGET_HandleActive(WM_HWIN hObj, WM_MESSAGE* pMsg) {
  int Diff, Notification;
  WIDGET* pWidget = WIDGET_H2P(hObj);
  switch (pMsg->MsgId) {
  case WM_WIDGET_SET_EFFECT:
    Diff = pWidget->pEffect->EffectSize;
    pWidget->pEffect = (const WIDGET_EFFECT*)pMsg->Data.p;
    Diff -= pWidget->pEffect->EffectSize;
    _UpdateChildPostions(hObj, Diff);
    WM_InvalidateWindow(hObj);
    return 0;                        /* Message handled -> Return */
  case WM_GET_ID:
    pMsg->Data.v = pWidget->Id;
    return 0;                        /* Message handled -> Return */
  case WM_PID_STATE_CHANGED:
    if (pWidget->State & WIDGET_STATE_FOCUSSABLE) {
      const WM_PID_STATE_CHANGED_INFO * pInfo = (const WM_PID_STATE_CHANGED_INFO*)pMsg->Data.p;
      if (pInfo->State) {
        WM_SetFocus(hObj);
      }
    }
    break;
  case WM_TOUCH_CHILD:
    /* A descendent (child) has been touched or released.
       If it has been touched, we need to get to top.
     */
    {
      const WM_MESSAGE * pMsgOrg;
      const GUI_PID_STATE * pState;
      pMsgOrg = (const WM_MESSAGE*)pMsg->Data.p;      /* The original touch message */
      pState = (const GUI_PID_STATE*)pMsgOrg->Data.p;
      if (pState) {          /* Message may not have a valid pointer (moved out) ! */
        if (pState->Pressed) {
          WM_BringToTop(hObj);
          return 0;                    /* Message handled -> Return */
        }
      }
    }
    break;
  case WM_SET_ID:
    pWidget->Id = pMsg->Data.v;
    return 0;                        /* Message handled -> Return */
  case WM_SET_FOCUS:
    if (pMsg->Data.v == 1) {
      WIDGET_SetState(hObj, pWidget->State |  WIDGET_STATE_FOCUS);
      Notification = WM_NOTIFICATION_GOT_FOCUS;
    } else {
      WIDGET_SetState(hObj, pWidget->State & ~WIDGET_STATE_FOCUS);
      Notification = WM_NOTIFICATION_LOST_FOCUS;
    }
    WM_NotifyParent(hObj, Notification);
    pMsg->Data.v = 0;   /* Focus change accepted */
    return 0;
  case WM_GET_ACCEPT_FOCUS:
    pMsg->Data.v = (pWidget->State & WIDGET_STATE_FOCUSSABLE) ? 1 : 0;               /* Can handle focus */
    return 0;                         /* Message handled */
  case WM_GET_INSIDE_RECT:
    WIDGET__GetInsideRect(pWidget, (GUI_RECT*)pMsg->Data.p);
    return 0;                         /* Message handled */
  }
  return 1;                           /* Message NOT handled */
}

/*********************************************************************
*
*       WIDGET__SetScrollState
*/
void WIDGET__SetScrollState(WM_HWIN hWin, const WM_SCROLL_STATE* pVState, const WM_SCROLL_STATE* pHState) {
  WM_HWIN hScroll;
  /* vertical scrollbar */
  hScroll = WM_GetDialogItem(hWin, GUI_ID_VSCROLL);
  WM_SetScrollState(hScroll, pVState);
  /* horizontal scrollbar */
  hScroll = WM_GetDialogItem(hWin, GUI_ID_HSCROLL);
  WM_SetScrollState(hScroll, pHState);
}

/*********************************************************************
*
*       WIDGET__DrawFocusRect
*/
void WIDGET__DrawFocusRect(WIDGET* pWidget, const GUI_RECT* pRect, int Dist) {
  GUI_RECT Rect;
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    WIDGET__RotateRect90(pWidget, &Rect, pRect);
    pRect = &Rect;
  }
  GUI_DrawFocusRect(pRect, Dist);
}

/*********************************************************************
*
*       WIDGET__DrawVLine
*/
void WIDGET__DrawVLine(WIDGET* pWidget, int x, int y0, int y1) {
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    GUI_RECT r0, r1;
    r0.x0 = x;
    r0.x1 = x;
    r0.y0 = y0;
    r0.y1 = y1;
    WIDGET__RotateRect90(pWidget, &r1, &r0);
    GUI_DrawHLine(r1.y0, r1.x0, r1.x1);
  } else {
    GUI_DrawVLine(x, y0, y1);
  }
}

/*********************************************************************
*
*       WIDGET__FillRectEx
*/
void WIDGET__FillRectEx(WIDGET* pWidget, const GUI_RECT* pRect) {
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    GUI_RECT r;
    WIDGET__RotateRect90(pWidget, &r, pRect);
    pRect = &r;
  }
  GUI_FillRectEx(pRect);
}

/*********************************************************************
*
*       WIDGET__EFFECT_DrawDownRect
*/
void WIDGET__EFFECT_DrawDownRect(WIDGET* pWidget, GUI_RECT* pRect) {
  GUI_RECT Rect;
  if (pRect == NULL) {
    WM_GetClientRect(&Rect);
    pRect = &Rect;
  }
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    WIDGET__RotateRect90(pWidget, &Rect, pRect);
    pRect = &Rect;
  }
  if (_EffectRequiresRedraw(pWidget, pRect)) {
    pWidget->pEffect->pfDrawDownRect(pRect);
  }
}

/*********************************************************************
*
*       WIDGET__EFFECT_DrawDown
*/
void WIDGET__EFFECT_DrawDown(WIDGET* pWidget) {
  WIDGET__EFFECT_DrawDownRect(pWidget, NULL);
}

/*********************************************************************
*
*       WIDGET__EFFECT_DrawUpRect
*/
void WIDGET__EFFECT_DrawUpRect(WIDGET* pWidget, GUI_RECT* pRect) {
  GUI_RECT Rect;
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    WIDGET__RotateRect90(pWidget, &Rect, pRect);
    pRect = &Rect;
  }
  if (_EffectRequiresRedraw(pWidget, pRect)) {
    pWidget->pEffect->pfDrawUpRect(pRect);
  }
}

/*********************************************************************
*
*       WIDGET_SetDefaultEffect
*/
const WIDGET_EFFECT* WIDGET_SetDefaultEffect(const WIDGET_EFFECT* pEffect) {
  const WIDGET_EFFECT* r;
  r = _pEffectDefault;
  _pEffectDefault = pEffect;
  return r;
}

/*********************************************************************
*
*       WIDGET_GetDefaultEffect
*/
const WIDGET_EFFECT*  WIDGET_GetDefaultEffect(void) {
  return _pEffectDefault;
}


#else                            /* Avoid problems with empty object modules */
  void WIDGET_C(void) {}
#endif /* GUI_WINSUPPORT */




