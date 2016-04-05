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
File        : SCROLLBAR.c
Purpose     : Implementation of scrollbar widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Protected.h"
#include "SCROLLBAR_Private.h"
#include "WIDGET.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Support for 3D effects */
#ifndef SCROLLBAR_USE_3D
  #define SCROLLBAR_USE_3D 1
#endif

/* Define colors */
#ifndef SCROLLBAR_BKCOLOR0_DEFAULT
  #define SCROLLBAR_BKCOLOR0_DEFAULT 0x808080
#endif

#ifndef SCROLLBAR_BKCOLOR1_DEFAULT
  #define SCROLLBAR_BKCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef SCROLLBAR_COLOR0_DEFAULT
  #define SCROLLBAR_COLOR0_DEFAULT 0xc0c0c0
#endif

#ifndef SCROLLBAR_COLOR1_DEFAULT
  #define SCROLLBAR_COLOR1_DEFAULT GUI_BLACK
#endif

#ifndef SCROLLBAR_DEFAULT_WIDTH
  #define SCROLLBAR_DEFAULT_WIDTH 11
#endif

/*********************************************************************
*
*       Module internal data
*
**********************************************************************
*/

GUI_COLOR SCROLLBAR__aDefaultBkColor[2] = {SCROLLBAR_BKCOLOR0_DEFAULT, SCROLLBAR_BKCOLOR1_DEFAULT};
GUI_COLOR SCROLLBAR__aDefaultColor[2]   = {SCROLLBAR_COLOR0_DEFAULT, SCROLLBAR_COLOR1_DEFAULT};
I16       SCROLLBAR__DefaultWidth       =  SCROLLBAR_DEFAULT_WIDTH;

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetArrowSize
*
*/
static int _GetArrowSize(SCROLLBAR_Obj* pObj) {
  unsigned int r;
  unsigned int xSize = WIDGET__GetXSize(&pObj->Widget);
  unsigned int ySize = WIDGET__GetYSize(&pObj->Widget);
  r = ySize/2 + 5;
  if (r > xSize-5)
    r = xSize-5;
  return r;
}

/*********************************************************************
*
*       _WIDGET__RECT2VRECT
*
* Purpose:
*   Convert rectangle in real coordinates into virtual coordinates
*
* Add. info:
*   This function could eventualy be made none-static and move into
*   a module of its own.
*/
static void _WIDGET__RECT2VRECT(const WIDGET* pWidget, GUI_RECT* pRect) {
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    int xSize = pWidget->Win.Rect.x1 - pWidget->Win.Rect.x0 + 1;
    int x0, x1;
    x0 = pRect->x0;
    x1 = pRect->x1;
    pRect->x0 = pRect->y0;
    pRect->x1 = pRect->y1;
    pRect->y1 = xSize - 1 - x0;
    pRect->y0 = xSize - 1 - x1;
  }
}

/*********************************************************************
*
*       _CalcPositions
*
*  Calculates all positions required for drawing or for mouse / touch
*  evaluation.
*/
static void _CalcPositions(SCROLLBAR_Obj* pObj, SCROLLBAR_POSITIONS* pPos) {
  int xSizeArrow, xSize, xSizeMoveable, ThumbSize, NumItems, xSizeThumbArea;
  WM_HWIN hWin;
  GUI_RECT r, rSub;
  int x0, y0;
  r = pObj->Widget.Win.Rect;
  x0 = r.x0;
  y0 = r.y0;
  pPos->x1  = (pObj->Widget.State & WIDGET_STATE_VERTICAL) ? r.y1 : r.x1;
  /* Subtract the rectangle of the other scrollbar (if existing and visible) */
  if (pObj->Widget.Id == GUI_ID_HSCROLL) {
    hWin = WM_GetScrollbarV(pObj->Widget.Win.hParent);
    if (hWin) {
      WM_GetWindowRectEx(hWin, &rSub);
      if (r.x1 == rSub.x1) {
        r.x1 = rSub.x0 -1;
      }
    }
  }
  if (pObj->Widget.Id == GUI_ID_VSCROLL) {
    hWin = WM_GetScrollbarH(pObj->Widget.Win.hParent);
    if (hWin) {
      WM_GetWindowRectEx(hWin, &rSub);
      if (r.y1 == rSub.y1) {
        r.y1 = rSub.y0 -1;
      }
    }
  }
  /* Convert coordinates of this window */
  GUI_MoveRect(&r, -x0, -y0);
  /* Convert real into virtual coordinates */
  _WIDGET__RECT2VRECT(&pObj->Widget, &r);
  NumItems      = pObj->NumItems;
  xSize         = r.x1 - r.x0 + 1;
  xSizeArrow    = _GetArrowSize(pObj);
  xSizeThumbArea= xSize - 2 * xSizeArrow;     /* Number of pixels available for thumb and movement */
  ThumbSize     = GUI__DivideRound(xSizeThumbArea * pObj->PageSize, NumItems);
  if (ThumbSize < 4) {
    ThumbSize = 4;
  }
  if (ThumbSize > xSizeThumbArea) {
    ThumbSize = xSizeThumbArea;
  }
  xSizeMoveable = xSizeThumbArea - ThumbSize;
  pPos->x0_LeftArrow  = r.x0;
  pPos->x1_LeftArrow  = xSizeArrow - 1;
  pPos->x1_RightArrow = xSize - 1;
  pPos->x0_RightArrow = xSize - xSizeArrow;
  pPos->x0_Thumb      = pPos->x1_LeftArrow + 1+ GUI__DivideRound(xSizeMoveable * pObj->v, NumItems - pObj->PageSize);
  pPos->x1_Thumb      = pPos->x0_Thumb + ThumbSize - 1;
  pPos->xSizeMoveable = xSizeMoveable;
  pPos->ThumbSize     = ThumbSize;
}

/*********************************************************************
*
*       _DrawTriangle
*/
static void _DrawTriangle(WIDGET* pWidget, int x, int y, int Size, int Inc) {
  if (pWidget->State & WIDGET_STATE_VERTICAL) {
    for (; Size >= 0; Size--, x += Inc) {
      GUI_DrawHLine(x, y - Size, y + Size);
    }
  } else {
    for (; Size >= 0; Size--, x += Inc) {
      GUI_DrawVLine(x, y - Size, y + Size);
    }
  }
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(SCROLLBAR_Obj* pObj) {
  int ArrowSize, ArrowOff;
  SCROLLBAR_POSITIONS Pos;
  GUI_RECT r, rClient;
  /*
    Get / calc position info
  */
  _CalcPositions(pObj, &Pos);
  WIDGET__GetClientRect(&pObj->Widget, &rClient);
  r = rClient;
  ArrowSize = ((r.y1 - r.y0) /3) - 1;
  ArrowOff = 3 + ArrowSize+ ArrowSize/3;
  /*
    Draw left Arrow
  */
  LCD_SetColor(pObj->aColor[0]);
  r = rClient;
  r.x0 = Pos.x0_LeftArrow;
  r.x1 = Pos.x1_LeftArrow;
  WIDGET__FillRectEx(&pObj->Widget, &r);
  LCD_SetColor(pObj->aBkColor[1]);
  _DrawTriangle(&pObj->Widget, r.x0 + ArrowOff, (r.y1 - r.y0) >> 1, ArrowSize, -1);
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &r);
  /*
    Draw the thumb area which is not covered by the thumb
  */
  LCD_SetColor(pObj->aBkColor[0]);
  r.x0 = Pos.x1_LeftArrow + 1;
  r.x1 = Pos.x0_Thumb - 1;
  WIDGET__FillRectEx(&pObj->Widget, &r);
  r = rClient;
  r.x0 = Pos.x1_Thumb + 1;
  r.x1 = Pos.x0_RightArrow - 1;
  WIDGET__FillRectEx(&pObj->Widget, &r);
  /*
    Draw Thumb
  */
  r = rClient;
  r.x0 = Pos.x0_Thumb;
  r.x1 = Pos.x1_Thumb;
  LCD_SetColor(pObj->aColor[0]);
  WIDGET__FillRectEx(&pObj->Widget, &r);
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &r);
  /*
    Draw right Arrow
  */
  LCD_SetColor(pObj->aColor[0]);
  r.x0 = Pos.x0_RightArrow;
  r.x1 = Pos.x1_RightArrow;
  WIDGET__FillRectEx(&pObj->Widget, &r);
  LCD_SetColor(pObj->aBkColor[1]);
  _DrawTriangle(&pObj->Widget, r.x1 - ArrowOff, (r.y1 - r.y0) >> 1, ArrowSize, 1);
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &r);
  /*
    Draw overlap area (if any ...)
  */
  if (Pos.x1_RightArrow != Pos.x1) {
    r.x0 = Pos.x1_RightArrow + 1;
    r.x1 = Pos.x1;
    LCD_SetColor(pObj->aColor[0]);
    WIDGET__FillRectEx(&pObj->Widget, &r);
  }
}

/*********************************************************************
*
*       _ScrollbarPressed
*/
static void _ScrollbarPressed(SCROLLBAR_Handle hObj, SCROLLBAR_Obj* pObj) {
  WIDGET_OrState(hObj, SCROLLBAR_STATE_PRESSED);
  if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
    WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
  }
}

/*********************************************************************
*
*       _ScrollbarReleased
*/
static void _ScrollbarReleased(SCROLLBAR_Handle hObj, SCROLLBAR_Obj* pObj) {
  WIDGET_AndState(hObj, SCROLLBAR_STATE_PRESSED);
  if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
    WM_NotifyParent(hObj, WM_NOTIFICATION_RELEASED);
  }
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(SCROLLBAR_Handle hObj, SCROLLBAR_Obj* pObj, WM_MESSAGE*pMsg) {
  SCROLLBAR_POSITIONS Pos;
  GUI_PID_STATE* pState = (GUI_PID_STATE*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      int Sel;
      int Range;
      int x;
      Sel = pObj->v;
      _CalcPositions(pObj, &Pos);
      Range = pObj->NumItems - pObj->PageSize;
      /* Swap mouse coordinates if necessary */
      if (pObj->Widget.State & WIDGET_STATE_VERTICAL) {
        int t = pState->x;
        pState->x = pState->y;
        pState->y = t;
      }
      x = pState->x;
      if (x <= Pos.x1_LeftArrow) {         /* left arrow (line left) */
        Sel--;
      } else if (x < Pos.x0_Thumb) {       /* left area  (page left) */
        Sel -= pObj->PageSize;
      } else if (x <= Pos.x1_Thumb) {      /* Thumb area */
        if (Pos.xSizeMoveable > 0) {
          x = x - Pos.ThumbSize/2 - Pos.x1_LeftArrow-1;
          Sel = GUI__DivideRound(Range * x, Pos.xSizeMoveable);
        }
      } else if (x < Pos.x0_RightArrow) {  /* right area (page right) */
        Sel += pObj->PageSize;
      } else  if (x <= Pos.x1_RightArrow) {
        Sel++;
      }
      /* WM_SetFocus(hObj); */
      WM_SetCapture(hObj, 1);
      SCROLLBAR_SetValue(hObj, Sel);
      if ((pObj->Widget.State & SCROLLBAR_STATE_PRESSED) == 0){   
        _ScrollbarPressed(hObj, pObj);
      }
    } else {
      /* React only if button was pressed before ... avoid problems with moving / hiding windows above (such as dropdown) */
      if (pObj->Widget.State & SCROLLBAR_STATE_PRESSED) {   
        _ScrollbarReleased(hObj, pObj);
      }
    }
  }
}

/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(SCROLLBAR_Handle hObj, WM_MESSAGE*pMsg) {
  const WM_KEY_INFO* pKeyInfo;
  int Key;
  pKeyInfo = (const WM_KEY_INFO*)(pMsg->Data.p);
  Key = pKeyInfo->Key;
  if (pKeyInfo->PressedCnt > 0) {
    switch (Key) {
      case GUI_KEY_RIGHT:
      case GUI_KEY_DOWN:
        SCROLLBAR_Inc(hObj);
        break;                    /* Send to parent by not doing anything */
      case GUI_KEY_LEFT:
      case GUI_KEY_UP:
        SCROLLBAR_Dec(hObj);
        break;                    /* Send to parent by not doing anything */
      default:
        return;
    }
  }
}

/*********************************************************************
*
*       _OnSetScrollState 
*/
static void _OnSetScrollState(SCROLLBAR_Handle hObj, SCROLLBAR_Obj* pObj, const WM_SCROLL_STATE* pState) {
  if (  (pState->NumItems != pObj->NumItems)
      || (pObj->PageSize   != pState->PageSize)
      || (pObj->v          != pState->v))
  {
    pObj->NumItems = pState->NumItems;
    pObj->PageSize = pState->PageSize;
    pObj->v        = pState->v;
    WM_InvalidateWindow(hObj);
  }
}

/*********************************************************************
*
*       SCROLLBAR__InvalidatePartner
*/
void SCROLLBAR__InvalidatePartner(SCROLLBAR_Handle hObj) {     /* Invalidate the partner, since it is also affected */
  WM_InvalidateWindow(WM_GetScrollPartner(hObj));
  WM_SendMessageNoPara(WM_GetParent(hObj), WM_NOTIFY_CLIENTCHANGE);   /* Client area may have changed */
}

/*********************************************************************
*
*       _SCROLLBAR_Callback
*/
static void _SCROLLBAR_Callback (WM_MESSAGE *pMsg) {
  SCROLLBAR_Handle hObj;
  SCROLLBAR_Obj* pObj;
  hObj = pMsg->hWin;
  pObj = SCROLLBAR_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_DELETE:
    SCROLLBAR__InvalidatePartner(hObj);
    break;
  case WM_PAINT:
    GUI_DEBUG_LOG("SCROLLBAR: _Callback(WM_PAINT)\n");
    _Paint(pObj);
    return;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_KEY:
    _OnKey(hObj, pMsg);
    break;
  case WM_SET_SCROLL_STATE:
    _OnSetScrollState(hObj, pObj, (const WM_SCROLL_STATE*)pMsg->Data.p);
    break;
  case WM_GET_SCROLL_STATE:
    ((WM_SCROLL_STATE*)pMsg->Data.p)->NumItems = pObj->NumItems;
    ((WM_SCROLL_STATE*)pMsg->Data.p)->PageSize = pObj->PageSize;
    ((WM_SCROLL_STATE*)pMsg->Data.p)->v        = pObj->v;
    break;
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/

/* Note: the parameters to a create function may vary.
         Some widgets may have multiple create functions */

/*********************************************************************
*
*       SCROLLBAR_CreateEx
*/
SCROLLBAR_Handle SCROLLBAR_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                    int WinFlags, int ExFlags, int Id)
{
  SCROLLBAR_Handle hObj;
  WM_LOCK();
  /* Set defaults if necessary */
  if ((xsize == 0) && (ysize == 0)) {
    GUI_RECT Rect;
    WM_GetInsideRectEx(hParent, &Rect);
    if (ExFlags & SCROLLBAR_CF_VERTICAL) {
      xsize = SCROLLBAR__DefaultWidth;
      x0    = Rect.x1 + 1 - xsize;
      y0    = Rect.y0;
      ysize = Rect.y1 - Rect.y0 + 1;
    } else {
      ysize = SCROLLBAR__DefaultWidth;
      y0    = Rect.y1 + 1 - ysize;
      x0    = Rect.x0;
      xsize = Rect.x1 - Rect.x0 + 1;
    }
  }
  /* Create the window */
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, _SCROLLBAR_Callback,
                                sizeof(SCROLLBAR_Obj) - sizeof(WM_Obj));
  if (hObj) {
    SCROLLBAR_Obj* pObj = SCROLLBAR_H2P(hObj);
    U16 InitState;
    /* Handle SpecialFlags */
    InitState = 0;
    if (ExFlags & SCROLLBAR_CF_VERTICAL) {
      InitState |= WIDGET_CF_VERTICAL;
    }
    if (ExFlags & SCROLLBAR_CF_FOCUSSABLE) {
      InitState |= WIDGET_STATE_FOCUSSABLE;
    }
    if ((Id != GUI_ID_HSCROLL) && (Id != GUI_ID_VSCROLL)) {
      InitState |= WIDGET_STATE_FOCUSSABLE;
    }
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, InitState);
    /* init member variables */
    SCROLLBAR_INIT_ID(pObj);
    pObj->aBkColor[0]   = SCROLLBAR__aDefaultBkColor[0];
    pObj->aBkColor[1]   = SCROLLBAR__aDefaultBkColor[1];
    pObj->aColor[0]     = SCROLLBAR__aDefaultColor[0];
    pObj->aColor[1]     = SCROLLBAR__aDefaultColor[1];
    pObj->NumItems      = 100;
    pObj->PageSize      =  10;
    pObj->v             =   0;
    SCROLLBAR__InvalidatePartner(hObj);
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "SCROLLBAR_Create failed")
  }
  WM_UNLOCK();
  return hObj;
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       SCROLLBAR_Dec
*/
void SCROLLBAR_Dec(SCROLLBAR_Handle hObj) {
  SCROLLBAR_AddValue(hObj, -1);
}

/*********************************************************************
*
*       SCROLLBAR_Inc
*/
void SCROLLBAR_Inc(SCROLLBAR_Handle hObj) {
  SCROLLBAR_AddValue(hObj,  1);
}

/*********************************************************************
*
*       SCROLLBAR_AddValue
*/
void SCROLLBAR_AddValue(SCROLLBAR_Handle hObj, int Add) {
  SCROLLBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    SCROLLBAR_SetValue(hObj, pObj->v + Add);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SCROLLBAR_SetValue
*/
void SCROLLBAR_SetValue(SCROLLBAR_Handle hObj, int v) {
  SCROLLBAR_Obj* pObj;
  int Max;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    Max = pObj->NumItems - pObj->PageSize;
    if (Max < 0)
      Max =0;
    /* Put in min/max range */
    if (v < 0) {
      v = 0;
    }
    if (v > Max) {
      v = Max;
    }
    if (pObj->v != v) {
      pObj->v = v;
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SCROLLBAR_SetNumItems
*/
void SCROLLBAR_SetNumItems(SCROLLBAR_Handle hObj, int NumItems) {
  SCROLLBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    if (pObj->NumItems != NumItems) {
      pObj->NumItems = NumItems;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SCROLLBAR_SetPageSize
*/
void SCROLLBAR_SetPageSize(SCROLLBAR_Handle hObj, int PageSize) {
  SCROLLBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SCROLLBAR_H2P(hObj);
    if (pObj->PageSize != PageSize) {
      pObj->PageSize = PageSize;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SCROLLBAR_SetState
*/
void  SCROLLBAR_SetState   (SCROLLBAR_Handle hObj, const WM_SCROLL_STATE* pState) {
  if (hObj) {
    SCROLLBAR_SetPageSize(hObj, pState->PageSize);
    SCROLLBAR_SetNumItems(hObj, pState->NumItems);
    SCROLLBAR_SetValue   (hObj, pState->v);
  }
}


#else /* avoid empty object files */

void SCROLLBAR_C(void);
void SCROLLBAR_C(void){}

#endif  /* #if GUI_WINSUPPORT */



