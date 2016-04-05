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
File        : LISTBOX.c
Purpose     : Implementation of listbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_ARRAY.h"
#include "LISTBOX_Private.h"
#include "SCROLLBAR.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Support for 3D effects */
#ifndef LISTBOX_USE_3D
  #define LISTBOX_USE_3D 1
#endif

/* Define default fonts */
#ifndef LISTBOX_FONT_DEFAULT
  #define LISTBOX_FONT_DEFAULT &GUI_Font13_1
#endif


/* Define colors */
#ifndef LISTBOX_BKCOLOR0_DEFAULT
  #define LISTBOX_BKCOLOR0_DEFAULT GUI_WHITE     /* Not selected */
#endif

#ifndef LISTBOX_BKCOLOR1_DEFAULT
  #define LISTBOX_BKCOLOR1_DEFAULT GUI_GRAY      /* Selected, no focus */
#endif

#ifndef LISTBOX_BKCOLOR2_DEFAULT
  #define LISTBOX_BKCOLOR2_DEFAULT GUI_BLUE      /* Selected, focus */
#endif

#ifndef LISTBOX_BKCOLOR3_DEFAULT
  #define LISTBOX_BKCOLOR3_DEFAULT 0xC0C0C0      /* Disabled */
#endif


#ifndef LISTBOX_TEXTCOLOR0_DEFAULT
  #define LISTBOX_TEXTCOLOR0_DEFAULT GUI_BLACK   /* Not selected */
#endif

#ifndef LISTBOX_TEXTCOLOR1_DEFAULT
  #define LISTBOX_TEXTCOLOR1_DEFAULT GUI_WHITE   /* Selected, no focus */
#endif

#ifndef LISTBOX_TEXTCOLOR2_DEFAULT
  #define LISTBOX_TEXTCOLOR2_DEFAULT GUI_WHITE   /* Selected, focus */
#endif

#ifndef LISTBOX_TEXTCOLOR3_DEFAULT
  #define LISTBOX_TEXTCOLOR3_DEFAULT GUI_GRAY    /* Disabled */
#endif


#ifndef LISTBOX_SCROLLSTEP_H_DEFAULT
  #define LISTBOX_SCROLLSTEP_H_DEFAULT 10
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/


LISTBOX_PROPS LISTBOX_DefaultProps = {
  LISTBOX_FONT_DEFAULT,
  LISTBOX_SCROLLSTEP_H_DEFAULT,
  LISTBOX_BKCOLOR0_DEFAULT,
  LISTBOX_BKCOLOR1_DEFAULT,
  LISTBOX_BKCOLOR2_DEFAULT,
  LISTBOX_BKCOLOR3_DEFAULT,
  LISTBOX_TEXTCOLOR0_DEFAULT,
  LISTBOX_TEXTCOLOR1_DEFAULT,
  LISTBOX_TEXTCOLOR2_DEFAULT,
  LISTBOX_TEXTCOLOR3_DEFAULT,
};


/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _CallOwnerDraw
*/
static int _CallOwnerDraw(LISTBOX_Handle hObj, const LISTBOX_Obj* pObj, int Cmd, int ItemIndex) {
  WIDGET_ITEM_DRAW_INFO ItemInfo;
  int r;
  ItemInfo.Cmd       = Cmd;
  ItemInfo.hWin      = hObj;
  ItemInfo.ItemIndex = ItemIndex;
  if (pObj->pfDrawItem) {
    r = pObj->pfDrawItem(&ItemInfo);
  } else {
    r = LISTBOX_OwnerDraw(&ItemInfo);
  }
  return r;
}

/*********************************************************************
*
*       LISTBOX__GetNumItems
*
*  Returns:
*    Number of items
*/
unsigned LISTBOX__GetNumItems(const LISTBOX_Obj* pObj) {
  return GUI_ARRAY_GetNumItems(&pObj->ItemArray);
}

/*********************************************************************
*
*       LISTBOX__GetpString
*
*  Returns:
*    Pointer to the specified item
*/
const char* LISTBOX__GetpString(const LISTBOX_Obj* pObj, int Index) {
  const char* s = NULL;
  LISTBOX_ITEM* pItem = (LISTBOX_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
  if (pItem) {
    s = pItem->acText;
  }
  return s;
}

/*********************************************************************
*
*       _GetYSize
*/
static int _GetYSize(LISTBOX_Handle hObj) {
  GUI_RECT Rect;
  WM_GetInsideRectExScrollbar(hObj, &Rect);
  return (Rect.y1 - Rect.y0 + 1);
}

/*********************************************************************
*
*       _GetItemSizeX
*/
static int _GetItemSizeX(LISTBOX_Handle hObj, const LISTBOX_Obj* pObj, unsigned Index) {
  LISTBOX_ITEM* pItem;
  int xSize = 0;
  pItem = (LISTBOX_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
  if (pItem) {
    xSize = pItem->xSize;
  }
  if (xSize == 0) {
    const GUI_FONT GUI_UNI_PTR* pOldFont;
    pOldFont = GUI_SetFont(pObj->Props.pFont);
    xSize    = _CallOwnerDraw(hObj, pObj, WIDGET_ITEM_GET_XSIZE, Index);
    GUI_SetFont(pOldFont);
  }
  if (pItem) {
    pItem->xSize = xSize;
  }
  return xSize;
}

/*********************************************************************
*
*       _GetItemSizeY
*/
static int _GetItemSizeY(LISTBOX_Handle hObj, const LISTBOX_Obj* pObj, unsigned Index) {
  LISTBOX_ITEM* pItem;
  int ySize = 0;
  pItem = (LISTBOX_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
  if (pItem) {
    ySize = pItem->ySize;
  }
  if (ySize == 0) {
    const GUI_FONT GUI_UNI_PTR* pOldFont;
    pOldFont = GUI_SetFont(pObj->Props.pFont);
    ySize    = _CallOwnerDraw(hObj, pObj, WIDGET_ITEM_GET_YSIZE, Index);
    GUI_SetFont(pOldFont);
  }
  if (pItem) {
    pItem->ySize = ySize;
  }
  return ySize;
}

/*********************************************************************
*
*       _GetContentsSizeX
*/
static int _GetContentsSizeX(LISTBOX_Handle hObj) {
  LISTBOX_Obj* pObj;
  int i, NumItems, SizeX;
  int Result = 0;
  pObj = LISTBOX_H2P(hObj);
  NumItems = LISTBOX__GetNumItems(pObj);
  for (i = 0; i < NumItems; i++) {
    SizeX = _GetItemSizeX(hObj, pObj, i);
    if (Result < SizeX) {
      Result = SizeX;
    }
  }
  return Result;
}

/*********************************************************************
*
*       _GetItemPosY
*/
static int _GetItemPosY(LISTBOX_Handle hObj, const LISTBOX_Obj* pObj, unsigned Index) {
  if (Index < LISTBOX__GetNumItems(pObj)) {
    if ((int)Index >= pObj->ScrollStateV.v) {
      unsigned i;
      int PosY = 0;
      for (i = pObj->ScrollStateV.v; i < Index; i++) {
        PosY += _GetItemSizeY(hObj, pObj, i);
      }
      return PosY;
    }
  }
  return -1;
}

/*********************************************************************
*
*       _IsPartiallyVis
*/
static int _IsPartiallyVis(LISTBOX_Handle hObj, const LISTBOX_Obj* pObj) {
  int Index;
  Index = pObj->Sel;
  if (Index < (int)LISTBOX__GetNumItems(pObj)) {
    if (Index >= pObj->ScrollStateV.v) {
      int y;
      y  = _GetItemPosY (hObj, pObj, Index);
      y += _GetItemSizeY(hObj, pObj, Index);
      if (y > _GetYSize(hObj)) {
        return 1;
      }
    }
  }
  return 0;
}

/*********************************************************************
*
*       _GetNumVisItems
*
*  Returns:
*   Number of fully or partially visible items
*/
static unsigned _GetNumVisItems(const LISTBOX_Obj* pObj, LISTBOX_Handle hObj) {
  int NumItems, r = 1;
  NumItems = LISTBOX__GetNumItems(pObj);
  if (NumItems > 1) {
    int i, ySize, DistY = 0;
    ySize = _GetYSize(hObj);
    for (i = NumItems - 1; i >= 0; i--) {
      DistY += _GetItemSizeY(hObj, pObj, i);
      if (DistY > ySize) {
        break;
      }
    }
    r = NumItems - i - 1;
    if (r < 1) {
      return 1;
    }
  }
  return r;
}

/*********************************************************************
*
*       _NotifyOwner
*
* Purpose:
*   Notify owner of the window.
*   If no owner is registered, the parent is considered owner.
*/
static void _NotifyOwner(WM_HWIN hObj, int Notification) {
  WM_MESSAGE Msg = {0};
  WM_HWIN hOwner;
  LISTBOX_Obj* pObj    = LISTBOX_H2P(hObj);
  hOwner = pObj->hOwner ? pObj->hOwner : WM_GetParent(hObj);
  Msg.MsgId  = WM_NOTIFY_PARENT;
  Msg.Data.v = Notification;
  Msg.hWinSrc= hObj;
  WM_SendMessage(hOwner, &Msg);
}

/*********************************************************************
*
*       LISTBOX_OwnerDraw
*/
int LISTBOX_OwnerDraw(const WIDGET_ITEM_DRAW_INFO* pDrawItemInfo) {
  switch (pDrawItemInfo->Cmd) {
    case WIDGET_ITEM_GET_XSIZE: {
      LISTBOX_Obj* pObj;
      const GUI_FONT GUI_UNI_PTR* pOldFont;
      const char* s;
      int DistX;
      pObj = LISTBOX_H2P(pDrawItemInfo->hWin);
      pOldFont = GUI_SetFont(pObj->Props.pFont);
      s = LISTBOX__GetpString(pObj, pDrawItemInfo->ItemIndex);
      DistX = GUI_GetStringDistX(s);
      GUI_SetFont(pOldFont);
      return DistX;
    }
    case WIDGET_ITEM_GET_YSIZE: {
      LISTBOX_Obj* pObj;
      pObj = LISTBOX_H2P(pDrawItemInfo->hWin);
      return GUI_GetYDistOfFont(pObj->Props.pFont) + pObj->ItemSpacing;
    }
    case WIDGET_ITEM_DRAW: {
      LISTBOX_Obj* pObj;
      LISTBOX_ITEM* pItem;
      WM_HMEM hItem;
      GUI_RECT r;
      int FontDistY;
      int ItemIndex = pDrawItemInfo->ItemIndex;
      const char* s;
      int ColorIndex;
      char IsDisabled;
      char IsSelected;
      pObj = LISTBOX_H2P(pDrawItemInfo->hWin);
      hItem = GUI_ARRAY_GethItem(&pObj->ItemArray, ItemIndex);
      pItem = (LISTBOX_ITEM *)GUI_ALLOC_h2p(hItem);
      WM_GetInsideRect(&r);
      FontDistY = GUI_GetFontDistY();
      /* Calculate color index */
      IsDisabled = (pItem->Status & LISTBOX_ITEM_DISABLED) ? 1 : 0;
      IsSelected = (pItem->Status & LISTBOX_ITEM_SELECTED) ? 1 : 0;
      if (pObj->Flags & LISTBOX_SF_MULTISEL) {
        if (IsDisabled) {
          ColorIndex = 3;
        } else {
          ColorIndex = (IsSelected) ? 2 : 0;
        }
      } else {
        if (IsDisabled) {
          ColorIndex = 3;
        } else {
          if (ItemIndex == pObj->Sel) {
            ColorIndex = (pObj->Widget.State & WIDGET_STATE_FOCUS) ? 2 : 1;
          } else {
            ColorIndex = 0;
          }
        }
      }
      /* Display item */
      LCD_SetBkColor(pObj->Props.aBackColor[ColorIndex]);
      LCD_SetColor  (pObj->Props.aTextColor[ColorIndex]);
      s = LISTBOX__GetpString(pObj, ItemIndex);
      GUI_SetTextMode(GUI_TM_TRANS);
      GUI_Clear();
      GUI_DispStringAt(s, pDrawItemInfo->x0 + 1, pDrawItemInfo->y0);
      /* Display focus rectangle */
      if ((pObj->Flags & LISTBOX_SF_MULTISEL) && (ItemIndex == pObj->Sel)) {
        GUI_RECT rFocus;
        rFocus.x0 = pDrawItemInfo->x0;
        rFocus.y0 = pDrawItemInfo->y0;
        rFocus.x1 = r.x1;
        rFocus.y1 = pDrawItemInfo->y0 + FontDistY - 1;
        LCD_SetColor(GUI_WHITE - pObj->Props.aBackColor[ColorIndex]);
        GUI_DrawFocusRect(&rFocus, 0);
      }
      return 0;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _UpdateScrollPos
*
* Purpose:
*   Checks whether if we must scroll up or scroll down to ensure
*   that selection is in the visible area. This function also
*   makes sure that scroll positions are in valid ranges.
*
* Return value:
*   Difference between old and new vertical scroll pos.
*/
static int _UpdateScrollPos(LISTBOX_Handle hObj, LISTBOX_Obj* pObj) {
  int PrevScrollStateV;
  PrevScrollStateV = pObj->ScrollStateV.v;
  if (pObj->Sel >= 0) {
    /* Check upper limit */
    if (_IsPartiallyVis(hObj, pObj)) {
      pObj->ScrollStateV.v = pObj->Sel - (pObj->ScrollStateV.PageSize - 1);
    }
    /* Check lower limit */
    if (pObj->Sel < pObj->ScrollStateV.v) {
      pObj->ScrollStateV.v = pObj->Sel;
    }
  }
  WM_CheckScrollBounds(&pObj->ScrollStateV);
  WM_CheckScrollBounds(&pObj->ScrollStateH);
  WIDGET__SetScrollState(hObj, &pObj->ScrollStateV, &pObj->ScrollStateH);
  return pObj->ScrollStateV.v - PrevScrollStateV;
}

/*********************************************************************
*
*       LISTBOX__InvalidateItemSize
*/
void LISTBOX__InvalidateItemSize(const LISTBOX_Obj* pObj, unsigned Index) {
  LISTBOX_ITEM* pItem;
  pItem = (LISTBOX_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
  if (pItem) {
    pItem->xSize = 0;
    pItem->ySize = 0;
  }
}

/*********************************************************************
*
*       LISTBOX__InvalidateInsideArea
*/
void LISTBOX__InvalidateInsideArea(LISTBOX_Handle hObj) {
  GUI_RECT Rect;
  WM_GetInsideRectExScrollbar(hObj, &Rect);
  WM_InvalidateRect(hObj, &Rect);
}

/*********************************************************************
*
*       LISTBOX__InvalidateItem
*/
void LISTBOX__InvalidateItem(LISTBOX_Handle hObj, const LISTBOX_Obj* pObj, int Sel) {
  if (Sel >= 0) {
    int ItemPosY;
    ItemPosY = _GetItemPosY(hObj, pObj, Sel);
    if (ItemPosY >= 0) {
      GUI_RECT Rect;
      int ItemDistY;
      ItemDistY = _GetItemSizeY(hObj, pObj, Sel);
      WM_GetInsideRectExScrollbar(hObj, &Rect);
      Rect.y0 += ItemPosY;
      Rect.y1  = Rect.y0 + ItemDistY - 1;
      WM_InvalidateRect(hObj, &Rect);
    }
  }
}

/*********************************************************************
*
*       LISTBOX__InvalidateItemAndBelow
*/
void LISTBOX__InvalidateItemAndBelow(LISTBOX_Handle hObj, const LISTBOX_Obj* pObj, int Sel) {
  if (Sel >= 0) {
    int ItemPosY;
    ItemPosY = _GetItemPosY(hObj, pObj, Sel);
    if (ItemPosY >= 0) {
      GUI_RECT Rect;
      WM_GetInsideRectExScrollbar(hObj, &Rect);
      Rect.y0 += ItemPosY;
      WM_InvalidateRect(hObj, &Rect);
    }
  }
}

/*********************************************************************
*
*       LISTBOX__SetScrollbarWidth
*/
void LISTBOX__SetScrollbarWidth(LISTBOX_Handle hObj, const LISTBOX_Obj* pObj) {
  WM_HWIN hBarH, hBarV;
  int Width;
  Width = pObj->ScrollbarWidth;
  if (Width == 0) {
    Width = SCROLLBAR_GetDefaultWidth();
  }
  hBarH = WM_GetDialogItem(hObj, GUI_ID_HSCROLL);
  hBarV = WM_GetDialogItem(hObj, GUI_ID_VSCROLL);
  SCROLLBAR_SetWidth(hBarH, Width);
  SCROLLBAR_SetWidth(hBarV, Width);
}

/*********************************************************************
*
*       _CalcScrollParas
*/
static int _CalcScrollParas(LISTBOX_Handle hObj) {
  GUI_RECT Rect;
  LISTBOX_Obj* pObj = LISTBOX_H2P(hObj);
  /* Calc vertical scroll parameters */
  pObj->ScrollStateV.NumItems = LISTBOX__GetNumItems(pObj);
  pObj->ScrollStateV.PageSize = _GetNumVisItems(pObj, hObj);
  /* Calc horizontal scroll parameters */
  WM_GetInsideRectExScrollbar(hObj, &Rect);
  pObj->ScrollStateH.NumItems = _GetContentsSizeX(hObj);
  pObj->ScrollStateH.PageSize = Rect.x1 - Rect.x0 + 1;
  return _UpdateScrollPos(hObj, pObj);
}

/*********************************************************************
*
*       _ManageAutoScroll
*/
static void _ManageAutoScroll(LISTBOX_Handle hObj) {
  char IsRequired;
  LISTBOX_Obj* pObj = LISTBOX_H2P(hObj);
  if (pObj->Flags & LISTBOX_SF_AUTOSCROLLBAR_V) {
    IsRequired = (_GetNumVisItems(pObj, hObj) < LISTBOX__GetNumItems(pObj));
    WM_SetScrollbarV(hObj, IsRequired);
  }
  if (pObj->Flags & LISTBOX_SF_AUTOSCROLLBAR_H) {
    GUI_RECT Rect;
    int xSize, xSizeContents;
    xSizeContents = _GetContentsSizeX(hObj);
    WM_GetInsideRectExScrollbar(hObj, &Rect);
    xSize = Rect.x1 - Rect.x0 + 1;
    IsRequired = (xSizeContents > xSize);
    WM_SetScrollbarH(hObj, IsRequired);
  }
  if (pObj->ScrollbarWidth) {
    LISTBOX__SetScrollbarWidth(hObj, pObj);
  }
}

/*********************************************************************
*
*       LISTBOX_UpdateScrollers
*/
int LISTBOX_UpdateScrollers(LISTBOX_Handle hObj) {
  _ManageAutoScroll(hObj);
  return _CalcScrollParas(hObj);
}

/*********************************************************************
*
*       _Tolower
*/
static int _Tolower(int Key) {
  if ((Key >= 0x41) && (Key <= 0x5a)) {
    Key += 0x20;
  }
  return Key;
}

/*********************************************************************
*
*       _IsAlphaNum
*/
static int _IsAlphaNum(int Key) {
  Key = _Tolower(Key);
  if (Key >= 'a' && Key <= 'z') {
    return 1;
  }
  if (Key >= '0' && Key <= '9') {
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _SelectByKey
*/
static void _SelectByKey(LISTBOX_Handle hObj, int Key) {
  unsigned i;
  LISTBOX_Obj* pObj;
  pObj = LISTBOX_H2P(hObj);
  Key = _Tolower(Key);
  for (i = 0; i < LISTBOX__GetNumItems(pObj); i++) {
    const char* s = LISTBOX__GetpString(pObj, i);
    if (_Tolower(*s) == Key) {
      LISTBOX_SetSel(hObj, i);
      break;
    }
  }
}

/*********************************************************************
*
*       _FreeAttached
*/
static void _FreeAttached(LISTBOX_Obj* pObj) {
  GUI_ARRAY_Delete(&pObj->ItemArray);
}

/*********************************************************************
*
*       _OnPaint
*/
static void _OnPaint(LISTBOX_Handle hObj, LISTBOX_Obj* pObj, WM_MESSAGE* pMsg) {
  WIDGET_ITEM_DRAW_INFO ItemInfo;
  GUI_RECT RectInside, RectItem, ClipRect;
  int ItemDistY, NumItems, i;
  NumItems = LISTBOX__GetNumItems(pObj);
  GUI_SetFont(pObj->Props.pFont);
  /* Calculate clipping rectangle */
  ClipRect = *(const GUI_RECT*)pMsg->Data.p;
  GUI_MoveRect(&ClipRect, -pObj->Widget.Win.Rect.x0, -pObj->Widget.Win.Rect.y0);
  WM_GetInsideRectExScrollbar(hObj, &RectInside);
  GUI__IntersectRect(&ClipRect, &RectInside);
  RectItem.x0 = ClipRect.x0;
  RectItem.x1 = ClipRect.x1;
  /* Fill item info structure */
  ItemInfo.Cmd  = WIDGET_ITEM_DRAW;
  ItemInfo.hWin = hObj;
  ItemInfo.x0   = RectInside.x0 - pObj->ScrollStateH.v;
  ItemInfo.y0   = RectInside.y0;
  /* Do the drawing */
  for (i = pObj->ScrollStateV.v; i < NumItems; i++) {
    RectItem.y0 = ItemInfo.y0;
    /* Break when all other rows are outside the drawing area */
    if (RectItem.y0 > ClipRect.y1) {
      break;
    }
    ItemDistY = _GetItemSizeY(hObj, pObj, i);
    RectItem.y1 = RectItem.y0 + ItemDistY - 1;
    /* Make sure that we draw only when row is in drawing area */
    if (RectItem.y1 >= ClipRect.y0) {
      /* Set user clip rect */
      WM_SetUserClipArea(&RectItem);
      /* Fill item info structure */
      ItemInfo.ItemIndex = i;
      /* Draw item */
      if (pObj->pfDrawItem) {
        pObj->pfDrawItem(&ItemInfo);
      } else {
        LISTBOX_OwnerDraw(&ItemInfo);
      }
    }
    ItemInfo.y0 += ItemDistY;
  }
  WM_SetUserClipArea(NULL);
  /* Calculate & clear 'data free' area */
  RectItem.y0 = ItemInfo.y0;
  RectItem.y1 = RectInside.y1;
  LCD_SetBkColor(pObj->Props.aBackColor[0]);
  GUI_ClearRectEx(&RectItem);
  /* Draw the 3D effect (if configured) */
  WIDGET__EFFECT_DrawDown(&pObj->Widget);
}

/*********************************************************************
*
*       _ToggleMultiSel
*/
static void _ToggleMultiSel(LISTBOX_Handle hObj, LISTBOX_Obj* pObj, int Sel) {
  if (pObj->Flags & LISTBOX_SF_MULTISEL) {
    WM_HMEM hItem = GUI_ARRAY_GethItem(&pObj->ItemArray, Sel);
    if (hItem) {
      LISTBOX_ITEM * pItem = (LISTBOX_ITEM *)GUI_ALLOC_h2p(hItem);
      if (!(pItem->Status & LISTBOX_ITEM_DISABLED)) {
        pItem->Status ^= LISTBOX_ITEM_SELECTED;
        _NotifyOwner(hObj, WM_NOTIFICATION_SEL_CHANGED);
        LISTBOX__InvalidateItem(hObj, pObj, Sel);
      }
    }
  }
}

/*********************************************************************
*
*       _GetItemFromPos
*/
static int _GetItemFromPos(LISTBOX_Handle hObj, LISTBOX_Obj* pObj, int x, int y) {
  int Sel = -1;
  GUI_RECT Rect;
  WM_GetInsideRectExScrollbar(hObj, &Rect);
  if ((x >= Rect.x0) && (y >= Rect.y0)) {
    if ((x <= Rect.x1) && (y <= Rect.y1)) {
      int NumItems = LISTBOX__GetNumItems(pObj);
      int i, y0 = Rect.y0;
      for (i = pObj->ScrollStateV.v; i < NumItems; i++) {
        if (y >= y0) {
          Sel = i;
        }
        y0 += _GetItemSizeY(hObj, pObj, i);
      }
    }
  }
  return Sel;
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(LISTBOX_Handle hObj, WM_MESSAGE* pMsg) {
  const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed == 0) {
      _NotifyOwner(hObj, WM_NOTIFICATION_RELEASED);
    }
  } else {     /* Mouse moved out */
    _NotifyOwner(hObj, WM_NOTIFICATION_MOVED_OUT);
  }
}

/*********************************************************************
*
*       _OnMouseOver
*/
#if GUI_SUPPORT_MOUSE
static int _OnMouseOver(LISTBOX_Handle hObj, LISTBOX_Obj* pObj, WM_MESSAGE* pMsg) {
  const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
  if (pObj->hOwner) {
    if (pState) {  /* Something happened in our area (pressed or released) */
      int Sel;
      Sel = _GetItemFromPos(hObj, pObj, pState->x, pState->y);
      if (Sel >= 0) {
        if (Sel < (int)(pObj->ScrollStateV.v + _GetNumVisItems(pObj, hObj))) {
          LISTBOX_SetSel(hObj, Sel);
        }
      }
    }
  }
  return 0;                        /* Message handled */
}
#endif

/*********************************************************************
*
*       _LISTBOX_Callback
*/
static void _LISTBOX_Callback(WM_MESSAGE*pMsg) {
  LISTBOX_Handle hObj = pMsg->hWin;
  LISTBOX_Obj* pObj = LISTBOX_H2P(hObj);
  WM_SCROLL_STATE ScrollState;
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    /* Owner needs to be informed about focus change */
    if (pMsg->MsgId == WM_SET_FOCUS) {
      if (pMsg->Data.v == 0) {            /* Lost focus ? */
        _NotifyOwner(hObj, LISTBOX_NOTIFICATION_LOST_FOCUS);
      }
    }
    return;
  }
  switch (pMsg->MsgId) {
  case WM_NOTIFY_PARENT:
    switch (pMsg->Data.v) {
    case WM_NOTIFICATION_VALUE_CHANGED:
      if (pMsg->hWinSrc  == WM_GetScrollbarV(hObj)) {
        WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
        pObj->ScrollStateV.v = ScrollState.v;
        LISTBOX__InvalidateInsideArea(hObj);
        _NotifyOwner(hObj, WM_NOTIFICATION_SCROLL_CHANGED);
      } else if (pMsg->hWinSrc == WM_GetScrollbarH(hObj)) {
        WM_GetScrollState(pMsg->hWinSrc, &ScrollState);
        pObj->ScrollStateH.v = ScrollState.v;
        LISTBOX__InvalidateInsideArea(hObj);
        _NotifyOwner(hObj, WM_NOTIFICATION_SCROLL_CHANGED);
      }
      break;
    case WM_NOTIFICATION_SCROLLBAR_ADDED:
      LISTBOX_UpdateScrollers(hObj);
      break;
    }
    break;
  case WM_PAINT:
    _OnPaint(hObj, pObj, pMsg);
    break;
  case WM_PID_STATE_CHANGED:
    {
      const WM_PID_STATE_CHANGED_INFO* pInfo = (const WM_PID_STATE_CHANGED_INFO*)pMsg->Data.p;
      if (pInfo->State) {
        int Sel;
        Sel = _GetItemFromPos(hObj, pObj, pInfo->x, pInfo->y);
        if (Sel >= 0) {
          _ToggleMultiSel(hObj, pObj, Sel);
          LISTBOX_SetSel(hObj, Sel);
        }
        _NotifyOwner(hObj, WM_NOTIFICATION_CLICKED);
        return;
      }
    }
    break;
  case WM_TOUCH:
    _OnTouch(hObj, pMsg);
    return;
#if GUI_SUPPORT_MOUSE
  case WM_MOUSEOVER:
    if (_OnMouseOver(hObj, pObj, pMsg) == 0)
      return;
    break;
#endif
  case WM_DELETE:
    _FreeAttached(pObj);
    break;       /* No return here ... WM_DefaultProc needs to be called */
  case WM_KEY:
    if (((const WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt > 0) {
      int Key;
      Key = ((const WM_KEY_INFO*)(pMsg->Data.p))->Key;
      if (LISTBOX_AddKey(hObj, Key)) {
        return;
      }
    }
    break;
  case WM_SIZE:
    LISTBOX_UpdateScrollers(hObj);
    WM_InvalidateWindow(hObj);
    break;
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       _MoveSel
*
*  Moves the selection/focus to the next valid item
*/
static void _MoveSel(LISTBOX_Handle hObj, int Dir) {
  int Index, NewSel = -1, NumItems;
  LISTBOX_Obj * pObj;
  pObj = LISTBOX_H2P(hObj);
  Index = LISTBOX_GetSel(hObj);
  NumItems = LISTBOX__GetNumItems(pObj);
  do {
    WM_HMEM hItem;
    Index += Dir;
    if ((Index < 0) || (Index >= NumItems)) {
      break;
    }
    hItem = GUI_ARRAY_GethItem(&pObj->ItemArray, Index);
    if (hItem) {
      LISTBOX_ITEM * pItem = (LISTBOX_ITEM *)GUI_ALLOC_h2p(hItem);
      if (!(pItem->Status & LISTBOX_ITEM_DISABLED)) {
        NewSel = Index;
      }
    }
  } while(NewSel < 0);
  if (NewSel >= 0) {
    LISTBOX_SetSel(hObj, NewSel);
  }
}

/*********************************************************************
*
*       _AddKey
*
* Returns: 1 if Key has been consumed
*          0 else 
*/
static int _AddKey(LISTBOX_Handle hObj, int Key) {
  LISTBOX_Obj* pObj;
  pObj = LISTBOX_H2P(hObj);
  switch (Key) {
  case ' ':
    _ToggleMultiSel(hObj, pObj, pObj->Sel);
    return 1;               /* Key has been consumed */
  case GUI_KEY_RIGHT:
    if (WM_SetScrollValue(&pObj->ScrollStateH, pObj->ScrollStateH.v + pObj->Props.ScrollStepH)) {
      LISTBOX_UpdateScrollers(hObj);
      LISTBOX__InvalidateInsideArea(hObj);
    }
    return 1;               /* Key has been consumed */
  case GUI_KEY_LEFT:
    if (WM_SetScrollValue(&pObj->ScrollStateH, pObj->ScrollStateH.v - pObj->Props.ScrollStepH)) {
      LISTBOX_UpdateScrollers(hObj);
      LISTBOX__InvalidateInsideArea(hObj);
    }
    return 1;               /* Key has been consumed */
  case GUI_KEY_DOWN:
    LISTBOX_IncSel(hObj);
    return 1;               /* Key has been consumed */
  case GUI_KEY_UP:
    LISTBOX_DecSel(hObj);
    return 1;               /* Key has been consumed */
  default:
    if(_IsAlphaNum(Key)) {
      _SelectByKey(hObj, Key);
      return 1;               /* Key has been consumed */
    }
  }
  return 0;
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTBOX_CreateEx
*/
LISTBOX_Handle LISTBOX_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                int WinFlags, int ExFlags, int Id, const GUI_ConstString* ppText)
{
  LISTBOX_Handle hObj;
  GUI_USE_PARA(ExFlags);
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, _LISTBOX_Callback,
                                sizeof(LISTBOX_Obj) - sizeof(WM_Obj));
  if (hObj) {
    LISTBOX_Obj* pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
     /* Init sub-classes */
    GUI_ARRAY_CREATE(&pObj->ItemArray);
   /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
    pObj->Props = LISTBOX_DefaultProps;
    if (ppText) {
      /* init member variables */
      /* Set non-zero attributes */
      LISTBOX_SetText(hObj, ppText);
    }
    INIT_ID(pObj);
    LISTBOX_UpdateScrollers(hObj);
    WM_UNLOCK();
  }
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
*       LISTBOX_InvalidateItem
*/
void LISTBOX_InvalidateItem(LISTBOX_Handle hObj, int Index) {
  if (hObj) {
    LISTBOX_Obj* pObj;
    int NumItems;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    NumItems = LISTBOX__GetNumItems(pObj);
    if (Index < NumItems) {
      if (Index < 0) {
        int i;
        for (i = 0; i < NumItems; i++) {
          LISTBOX__InvalidateItemSize(pObj, i);
        }
        LISTBOX_UpdateScrollers(hObj);
        LISTBOX__InvalidateInsideArea(hObj);
      } else {
        LISTBOX__InvalidateItemSize(pObj, Index);
        LISTBOX_UpdateScrollers(hObj);
        LISTBOX__InvalidateItemAndBelow(hObj, pObj, Index);
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTBOX_AddKey
*
* Returns: 1 if Key has been consumed
*          0 else 
*/
int LISTBOX_AddKey(LISTBOX_Handle hObj, int Key) {
  int r = 0;
  if (hObj) {
    WM_LOCK();
    r = _AddKey(hObj, Key);
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       LISTBOX_AddString
*/
void LISTBOX_AddString(LISTBOX_Handle hObj, const char* s) {
  if (hObj && s) {
    LISTBOX_Obj* pObj;
    LISTBOX_ITEM Item = {0, 0};
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    if (GUI_ARRAY_AddItem(&pObj->ItemArray, &Item, sizeof(LISTBOX_ITEM) + strlen(s)) == 0) {
      unsigned ItemIndex = GUI_ARRAY_GetNumItems(&pObj->ItemArray) - 1;
      LISTBOX_ITEM* pItem= (LISTBOX_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, ItemIndex);
      strcpy(pItem->acText, s);
      LISTBOX__InvalidateItemSize(pObj, ItemIndex);
      LISTBOX_UpdateScrollers(hObj);
      LISTBOX__InvalidateItem(hObj, pObj, ItemIndex);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTBOX_SetText
*/
void LISTBOX_SetText(LISTBOX_Handle hObj, const GUI_ConstString* ppText) {
  if (hObj) {
    int i;
    const char* s;
    WM_LOCK();
    if (ppText) {
      for (i = 0; (s = *(ppText+i)) != 0; i++) {
        LISTBOX_AddString(hObj, s);
      }
    }
    LISTBOX_InvalidateItem(hObj, LISTBOX_ALL_ITEMS);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTBOX_SetSel
*/
void LISTBOX_SetSel (LISTBOX_Handle hObj, int NewSel) {
  if (hObj) {
    LISTBOX_Obj* pObj;
    int MaxSel;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    MaxSel = LISTBOX__GetNumItems(pObj);
    MaxSel = MaxSel ? MaxSel - 1 : 0;
    if (NewSel > MaxSel) {
      NewSel = MaxSel;
    }
    if (NewSel < 0) {
      NewSel = -1;
    } else {
      WM_HMEM hItem = GUI_ARRAY_GethItem(&pObj->ItemArray, NewSel);
      if (hItem) {
        LISTBOX_ITEM* pItem = (LISTBOX_ITEM*)GUI_ALLOC_h2p(hItem);
        if (pItem->Status & LISTBOX_ITEM_DISABLED) {
          NewSel = -1;
        }
      }
    }
    if (NewSel != pObj->Sel) {
      int OldSel;
      OldSel    = pObj->Sel;
      pObj->Sel = NewSel;
      if (_UpdateScrollPos(hObj, pObj)) {
        LISTBOX__InvalidateInsideArea(hObj);
      } else {
        LISTBOX__InvalidateItem(hObj, pObj, OldSel);
        LISTBOX__InvalidateItem(hObj, pObj, NewSel);
      }
      _NotifyOwner(hObj, WM_NOTIFICATION_SEL_CHANGED);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTBOX_GetSel
*/
int  LISTBOX_GetSel (LISTBOX_Handle hObj) {
  int r = -1;
  LISTBOX_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    ASSERT_IS_VALID_PTR(pObj);
    r = pObj->Sel;
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       LISTBOX_IncSel
*/
void LISTBOX_IncSel      (LISTBOX_Handle hObj) {
  if (hObj) {
    WM_LOCK();
    _MoveSel(hObj, 1);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       LISTBOX_DecSel
*/
void LISTBOX_DecSel      (LISTBOX_Handle hObj) {
  if (hObj) {
    WM_LOCK();
    _MoveSel(hObj, -1);
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_C(void) {}
#endif

/*************************** End of file ****************************/

