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
File        : MULTIPAGE.c
Purpose     : Implementation of MULTIPAGE widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Protected.h"
#include "GUI_ARRAY.h"
#include "MULTIPAGE_Private.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define MAX(a, b)	((a > b) ? a : b)

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/
 
/* Define default fonts */
#ifndef MULTIPAGE_FONT_DEFAULT
  #define MULTIPAGE_FONT_DEFAULT        &GUI_Font13_1
#endif

#ifndef MULTIPAGE_ALIGN_DEFAULT
  #define MULTIPAGE_ALIGN_DEFAULT       (MULTIPAGE_ALIGN_LEFT | MULTIPAGE_ALIGN_TOP)
#endif

/* Define colors */
#define MULTIPAGE_NUMCOLORS 2

#ifndef MULTIPAGE_BKCOLOR0_DEFAULT
  #define MULTIPAGE_BKCOLOR0_DEFAULT    0xD0D0D0 /* disabled page */
#endif

#ifndef MULTIPAGE_BKCOLOR1_DEFAULT
  #define MULTIPAGE_BKCOLOR1_DEFAULT    0xC0C0C0 /* enabled page */
#endif

#ifndef MULTIPAGE_TEXTCOLOR0_DEFAULT
  #define MULTIPAGE_TEXTCOLOR0_DEFAULT  0x808080 /* disabled page */
#endif

#ifndef MULTIPAGE_TEXTCOLOR1_DEFAULT
  #define MULTIPAGE_TEXTCOLOR1_DEFAULT  0x000000 /* enabled page */
#endif

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WM_HWIN hWin;
  U8      Status;
  char    acText;
} MULTIPAGE_PAGE;

typedef struct {
  WIDGET          Widget;
  WM_HWIN         hClient;
  GUI_ARRAY       Handles;
  unsigned        Selection;
  int             ScrollState;
  unsigned        Align;
  const GUI_FONT GUI_UNI_PTR * Font;
  GUI_COLOR       aBkColor[MULTIPAGE_NUMCOLORS];
  GUI_COLOR       aTextColor[MULTIPAGE_NUMCOLORS];
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} MULTIPAGE_Obj;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

const GUI_FONT GUI_UNI_PTR * MULTIPAGE__pDefaultFont        = MULTIPAGE_FONT_DEFAULT;
unsigned                     MULTIPAGE__DefaultAlign        = MULTIPAGE_ALIGN_DEFAULT;
GUI_COLOR                    MULTIPAGE__DefaultBkColor[2]   = { MULTIPAGE_BKCOLOR0_DEFAULT, MULTIPAGE_BKCOLOR1_DEFAULT };
GUI_COLOR                    MULTIPAGE__DefaultTextColor[2] = { MULTIPAGE_TEXTCOLOR0_DEFAULT, MULTIPAGE_TEXTCOLOR1_DEFAULT };

/*********************************************************************
*
*       Static code, helper functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _AddScrollbar
*/
static void _AddScrollbar(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj, int x, int y, int w, int h) {
  SCROLLBAR_Handle hScroll;
  if ((hScroll = WM_GetScrollbarH(hObj)) == 0) {
    hScroll = SCROLLBAR_Create(x, y, w, h, hObj, GUI_ID_HSCROLL, WM_CF_SHOW, 0);
    WIDGET_SetEffect(hScroll, pObj->Widget.pEffect);
  } else {
    WM_MoveChildTo(hScroll, x, y);
    WM_SetSize(hScroll, w, h);
  }
  pObj->Widget.State |= MULTIPAGE_STATE_SCROLLMODE;
}

/*********************************************************************
*
*       _SetScrollbar
*/
static void _SetScrollbar(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj, int NumItems) {
  SCROLLBAR_Handle hScroll;
  hScroll = WM_GetScrollbarH(hObj);
  SCROLLBAR_SetNumItems(hScroll, NumItems);
  SCROLLBAR_SetPageSize(hScroll, 1);
  if (pObj->ScrollState >= NumItems) {
    pObj->ScrollState = 0;
  }
  SCROLLBAR_SetValue(hScroll, pObj->ScrollState);
}

/*********************************************************************
*
*       _DeleteScrollbar
*/
static void _DeleteScrollbar(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj) {
  WM_DeleteWindow(WM_GetScrollbarH(hObj));
  pObj->Widget.State &= ~MULTIPAGE_STATE_SCROLLMODE;
}

/*********************************************************************
*
*       _ShowPage
*/
static void _ShowPage(MULTIPAGE_Obj* pObj, unsigned Index) {
  WM_HWIN hWin = 0;
  WM_HWIN hChild;
  WM_Obj* pChild;
  WM_Obj* pClient = WM_H2P(pObj->hClient);
  if ((int)Index < pObj->Handles.NumItems) {
    MULTIPAGE_PAGE* pPage;
    pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
    hWin = pPage->hWin;
  }
  for (hChild = pClient->hFirstChild; hChild; hChild = pChild->hNext) {
    pChild = WM_H2P(hChild);
    if (hChild == hWin) {
      WM_ShowWindow(hChild);
      WM_SetFocus(hChild);
    } else {
      WM_HideWindow(hChild);
    }
  }
}

/*********************************************************************
*
*       _SetEnable
*/
static void _SetEnable(MULTIPAGE_Obj* pObj, unsigned Index, int State) {
  if ((int)Index < pObj->Handles.NumItems) {
    MULTIPAGE_PAGE* pPage;
    pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
    if (State) {
      pPage->Status |= MULTIPAGE_STATE_ENABLED;
    } else {
      pPage->Status &= ~MULTIPAGE_STATE_ENABLED;
    }
  }
}

/*********************************************************************
*
*       _GetEnable
*/
static int _GetEnable(MULTIPAGE_Obj* pObj, unsigned Index) {
  int r = 0;
  if ((int)Index < pObj->Handles.NumItems) {
    MULTIPAGE_PAGE* pPage;
    pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
    r = (pPage->Status & MULTIPAGE_STATE_ENABLED) ? 1 : 0;
  }
  return r;
}

/*********************************************************************
*
*       _CalcClientRect
*
*  Calculates the rect of the client area.
*/
static void _CalcClientRect(MULTIPAGE_Obj* pObj, GUI_RECT* pRect) {
  WIDGET__GetInsideRect(&pObj->Widget, pRect);
  if (pObj->Align & MULTIPAGE_ALIGN_BOTTOM) {
    pRect->y1 -= GUI_GetYSizeOfFont(pObj->Font) + 6;
  } else {
    pRect->y0 += GUI_GetYSizeOfFont(pObj->Font) + 6;
  }
}

/*********************************************************************
*
*       _CalcBorderRect
*
*  Calculates the border rect of the client area.
*/
static void _CalcBorderRect(MULTIPAGE_Obj* pObj, GUI_RECT* pRect) {
  WM__GetClientRectWin(&pObj->Widget.Win, pRect);
  if (pObj->Align & MULTIPAGE_ALIGN_BOTTOM) {
    pRect->y1 -= GUI_GetYSizeOfFont(pObj->Font) + 6;
  } else {
    pRect->y0 += GUI_GetYSizeOfFont(pObj->Font) + 6;
  }
}

/*********************************************************************
*
*       _GetPageSizeX
*
*  Returns the width of a page item.
*/
static int _GetPageSizeX(MULTIPAGE_Obj* pObj, unsigned Index) {
  int r = 0;
  if ((int)Index < pObj->Handles.NumItems) {
    MULTIPAGE_PAGE* pPage;
    GUI_SetFont(pObj->Font);
    pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
    r = GUI_GetStringDistX(&pPage->acText) + 10;
  }
  return r;
}

/*********************************************************************
*
*       _GetPagePosX
*
*  Returns the x-position of a page item.
*/
static int _GetPagePosX(MULTIPAGE_Obj* pObj, unsigned Index) {
  unsigned i, r = 0;
  for (i = 0; i < Index; i++) {
    r += _GetPageSizeX(pObj, i);
  }
  return r;
}

/*********************************************************************
*
*       _GetTextWidth
*
*  Returns the width of all text items.
*/
static int _GetTextWidth(MULTIPAGE_Obj* pObj) {
  return _GetPagePosX(pObj, pObj->Handles.NumItems);
}

/*********************************************************************
*
*       _GetTextRect
*/
static void _GetTextRect(MULTIPAGE_Obj* pObj, GUI_RECT* pRect) {
  GUI_RECT rBorder;
  int Width, Height;
  Height = GUI_GetYSizeOfFont(pObj->Font) + 6;
  _CalcBorderRect(pObj, &rBorder);
  /* Calculate Y-Position of text item */
  if (pObj->Align & MULTIPAGE_ALIGN_BOTTOM) {
    pRect->y0 = rBorder.y1;
  } else {
    pRect->y0 = 0;
  }
  pRect->y1 = pRect->y0 + Height;
  /* Calculate width of text items */
  if (pObj->Widget.State & MULTIPAGE_STATE_SCROLLMODE) {
    Width = rBorder.x1 - ((Height * 3) >> 1) - 3;
  } else {
    Width = _GetTextWidth(pObj);
  }
  /* Calculate X-Position of text item */
  if (pObj->Align & MULTIPAGE_ALIGN_RIGHT) {
    pRect->x0 = rBorder.x1 - Width;
    pRect->x1 = rBorder.x1;
  } else {
    pRect->x0 = 0;
    pRect->x1 = Width;
  }
}

/*********************************************************************
*
*       _UpdatePositions
*/
static void _UpdatePositions(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj) {
  GUI_RECT rBorder;
  int Width;
  Width = _GetTextWidth(pObj);
  _CalcBorderRect(pObj, &rBorder);
  /* Set scrollmode according to the text width */
  if (Width > rBorder.x1) {
    GUI_RECT rText;
    int Size, x0, y0, NumItems = 0;
    Size   = ((GUI_GetYSizeOfFont(pObj->Font) + 6) * 3) >> 2;
    x0     = (pObj->Align & MULTIPAGE_ALIGN_RIGHT)  ? (rBorder.x0) : (rBorder.x1 - 2*Size + 1);
    y0     = (pObj->Align & MULTIPAGE_ALIGN_BOTTOM) ? (rBorder.y1) : (rBorder.y0 -   Size + 1);
    /* A scrollbar is required so we add one to the multipage */
    _AddScrollbar(hObj, pObj, x0, y0, 2 * Size, Size);
    _GetTextRect(pObj, &rText);
    while (Width >= MAX((rText.x1 - rText.x0 + 1), 1)) {
      Width -= _GetPageSizeX(pObj, NumItems++);
    }
    _SetScrollbar(hObj, pObj, NumItems + 1);
  } else {
    /* Scrollbar is no longer required. We delete it if there was one */
    _DeleteScrollbar(hObj, pObj);
  }
  /* Move and resize the client area to the updated positions */
  _CalcClientRect(pObj, &rBorder);
  WM_MoveChildTo(pObj->hClient, rBorder.x0, rBorder.y0);
  WM_SetSize(pObj->hClient, rBorder.x1 - rBorder.x0 + 1, rBorder.y1 - rBorder.y0 + 1);
  WM_InvalidateWindow(hObj);
}

/*********************************************************************
*
*       Static code, drawing functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawTextItem
*/
static void _DrawTextItem(MULTIPAGE_Obj* pObj, const char* pText, unsigned Index,
                          const GUI_RECT* pRect, int x0, int w, int ColorIndex) {
  GUI_RECT r;
  r = *pRect;
  r.x0 += x0;
  r.x1  = r.x0 + w;
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &r);
  GUI__ReduceRect(&r, &r, pObj->Widget.pEffect->EffectSize);
  if (pObj->Selection == Index) {
    if (pObj->Align & MULTIPAGE_ALIGN_BOTTOM) {
      r.y0 -= pObj->Widget.pEffect->EffectSize + 1;
	    if (pObj->Widget.pEffect->EffectSize > 1) {
		    LCD_SetColor(GUI_WHITE);
		    GUI_DrawVLine(r.x0 - 1, r.y0, r.y0 + 1);
		    LCD_SetColor(0x555555);
		    GUI_DrawVLine(r.x1 + 1, r.y0, r.y0 + 1);
	    }
    } else {
      r.y1 += pObj->Widget.pEffect->EffectSize + 1;
	    if (pObj->Widget.pEffect->EffectSize > 1) {
		    LCD_SetColor(GUI_WHITE);
		    GUI_DrawVLine(r.x0 - 1, r.y1 - 2, r.y1 - 1);
		    LCD_SetColor(0x555555);
		    GUI_DrawVLine(r.x1 + 1, r.y1 - 2, r.y1 - 1);
	    }
    }
  }
  LCD_SetColor(pObj->aBkColor[ColorIndex]);
  WIDGET__FillRectEx(&pObj->Widget, &r);
  LCD_SetBkColor(pObj->aBkColor[ColorIndex]);
  LCD_SetColor(pObj->aTextColor[ColorIndex]);
  GUI_DispStringAt(pText, r.x0 + 4, pRect->y0 + 3);
}

/*********************************************************************
*
*       Static code, multipage callbacks
*
**********************************************************************
*/
/*********************************************************************
*
*       _Paint
*/
static void _Paint(MULTIPAGE_Obj* pObj) {
  GUI_RECT rBorder;
  /* Draw border of multipage */
  _CalcBorderRect(pObj, &rBorder);
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &rBorder);
  /* Draw text items */
  if (pObj->Handles.NumItems > 0) {
    MULTIPAGE_PAGE* pPage;
    GUI_RECT rText, rClip;
    int i, w = 0, x0 = 0;
    if (pObj->Widget.State & MULTIPAGE_STATE_SCROLLMODE) {
      if (pObj->Align & MULTIPAGE_ALIGN_RIGHT) {
        x0 = -_GetPagePosX(pObj, pObj->ScrollState);
      } else {
        x0 = -_GetPagePosX(pObj, pObj->ScrollState);
      }
    }
    _GetTextRect(pObj, &rText);
    rClip = rText;
    rClip.y0 = rText.y0 - 1;
    rClip.y1 = rText.y1 + 1;
    WM_SetUserClipRect(&rClip);
    GUI_SetFont(pObj->Font);
    for (i = 0; i < pObj->Handles.NumItems; i++) {
      pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, i);
      x0 += w;
      w   = GUI_GetStringDistX(&pPage->acText) + 10;
      _DrawTextItem(pObj, &pPage->acText, i, &rText, x0, w, (pPage->Status & MULTIPAGE_STATE_ENABLED) ? 1 : 0);
    }    
    WM_SetUserClipRect(NULL);
  }
}

/*********************************************************************
*
*       _ClickedOnMultipage
*/
static int _ClickedOnMultipage(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj, int x, int y) {
  GUI_RECT rText;
  _GetTextRect(pObj, &rText);
  if ((y >= rText.y0) && (y <= rText.y1)) {
    if ((pObj->Handles.NumItems > 0) && (x >= rText.x0) && (x <= rText.x1)) {
      int i, w = 0, x0 = rText.x0;
      /* Check if another page must be selected */
      if (pObj->Widget.State & MULTIPAGE_STATE_SCROLLMODE) {
        x0 -= _GetPagePosX(pObj, pObj->ScrollState);
      }
      for (i = 0; i < pObj->Handles.NumItems; i++) {
        x0 += w;
        w   = _GetPageSizeX(pObj, i);
        if (x >= x0 && x <= (x0 + w - 1)) {
          MULTIPAGE_SelectPage(hObj, i);
          WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
          return 1;
        }
      }
    }
    return 0;
  }
  return 1;
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(MULTIPAGE_Handle hObj, MULTIPAGE_Obj* pObj, WM_MESSAGE*pMsg) {
  GUI_PID_STATE* pState;
  int Notification;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    pState = (GUI_PID_STATE*)pMsg->Data.p;
    if (pState->Pressed) {
      int x = pState->x;
      int y = pState->y;
      if (!_ClickedOnMultipage(hObj, pObj, x, y)) {
        WM_HWIN hBelow;
        x += WM_GetWindowOrgX(hObj);
        y += WM_GetWindowOrgY(hObj);
        hBelow = WM_Screen2hWinEx(hObj, x, y);
        if (hBelow) {
          pState->x = x - WM_GetWindowOrgX(hBelow);
          pState->y = y - WM_GetWindowOrgY(hBelow);
          pMsg->hWin = hBelow;
          (*WM_H2P(hBelow)->cb)(pMsg);
        }
      } else {
        WM_BringToTop(hObj);
      }
      Notification = WM_NOTIFICATION_CLICKED;
    } else {
      Notification = WM_NOTIFICATION_RELEASED;
    }
  } else {
    Notification = WM_NOTIFICATION_MOVED_OUT;
  }
  WM_NotifyParent(hObj, Notification);
}

/*********************************************************************
*
*       _Callback
*/
static void _Callback (WM_MESSAGE *pMsg) {
  MULTIPAGE_Handle hObj = pMsg->hWin;
  MULTIPAGE_Obj* pObj;
  int Handled;
  WM_LOCK();
  pObj    = MULTIPAGE_H2P(hObj);
  Handled = WIDGET_HandleActive(hObj, pMsg);
  switch (pMsg->MsgId) {
  case WM_PAINT:
    _Paint(pObj);
    break;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_NOTIFY_PARENT:
    if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED) {
      if (WM_GetId(pMsg->hWinSrc) == GUI_ID_HSCROLL) {
        pObj->ScrollState = SCROLLBAR_GetValue(pMsg->hWinSrc);
        WM_InvalidateWindow(hObj);
      }
    }
    break;
  case WM_GET_CLIENT_WINDOW:
    pMsg->Data.v = (int)pObj->hClient;
    break;
  case WM_GET_INSIDE_RECT:
    _CalcClientRect(pObj, (GUI_RECT*)(pMsg->Data.p));
    break;
  case WM_WIDGET_SET_EFFECT:
    WIDGET_SetEffect(WM_GetScrollbarH(hObj), (WIDGET_EFFECT const *)pMsg->Data.p);
  case WM_SIZE:
    _UpdatePositions(hObj, pObj);
    break;
  case WM_DELETE:
    GUI_ARRAY_Delete(&pObj->Handles);
    /* No break here ... WM_DefaultProc needs to be called */
  default:
    /* Let widget handle the standard messages */
    if (Handled) {
      WM_DefaultProc(pMsg);
    }
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       _ClientCallback
*/
static void _ClientCallback(WM_MESSAGE* pMsg) {
  WM_HWIN hObj = pMsg->hWin;
  WM_HWIN hParent = WM_GetParent(hObj);
  MULTIPAGE_Obj* pParent;
  WM_LOCK();
  pParent = MULTIPAGE_H2P(hParent);
  switch (pMsg->MsgId) {
  case WM_PAINT:
    LCD_SetBkColor(pParent->aBkColor[1]);
    GUI_Clear();
    break;
  case WM_TOUCH:
    WM_SetFocus(hParent);
    WM_BringToTop(hParent);
    break;
  case WM_GET_CLIENT_WINDOW:
    pMsg->Data.v = (int)hObj;
    break;
  case WM_GET_INSIDE_RECT:
    WM_DefaultProc(pMsg);
  }
  WM_UNLOCK();
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
*       MULTIPAGE_CreateEx
*/
MULTIPAGE_Handle MULTIPAGE_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                    int WinFlags, int ExFlags, int Id)
{
  MULTIPAGE_Handle hObj;
  GUI_USE_PARA(ExFlags);
  /* Create the window */
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags | WM_CF_HASTRANS, &_Callback,
                                sizeof(MULTIPAGE_Obj) - sizeof(WM_Obj));
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    GUI_RECT rClient;
    int Flags;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    /* Init sub-classes */
    GUI_ARRAY_CREATE(&pObj->Handles);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
    /* init member variables */
    MULTIPAGE_INIT_ID(pObj);
    pObj->aBkColor[0]     = MULTIPAGE__DefaultBkColor[0];
    pObj->aBkColor[1]     = MULTIPAGE__DefaultBkColor[1];
    pObj->aTextColor[0]   = MULTIPAGE__DefaultTextColor[0];
    pObj->aTextColor[1]   = MULTIPAGE__DefaultTextColor[1];
    pObj->Font            = MULTIPAGE__pDefaultFont;
    pObj->Align           = MULTIPAGE__DefaultAlign;
    pObj->Selection       = 0xffff;
    pObj->ScrollState     = 0;
    pObj->Widget.State    = 0;
    _CalcClientRect(pObj, &rClient);
    Flags = WM_CF_SHOW | WM_CF_ANCHOR_LEFT | WM_CF_ANCHOR_RIGHT | WM_CF_ANCHOR_TOP | WM_CF_ANCHOR_BOTTOM;
    pObj->hClient = WM_CreateWindowAsChild(rClient.x0, rClient.y0,
                                           rClient.x1 - rClient.x0 + 1,
                                           rClient.y1 - rClient.y0 + 1,
                                           hObj, Flags, &_ClientCallback, 0);
    _UpdatePositions(hObj, pObj);
    WM_UNLOCK();
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "MULTIPAGE_Create failed")
  }
  return hObj;
}

/*********************************************************************
*
*       Exported routines:  Page management
*
**********************************************************************
*/
/*********************************************************************
*
*       MULTIPAGE_AddPage
*/
void MULTIPAGE_AddPage(MULTIPAGE_Handle hObj, WM_HWIN hWin ,const char* pText) {
  MULTIPAGE_Obj* pObj;
  GUI_USE_PARA(hWin);
  if (hObj) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (!hWin) {
      /* If we get no handle we must find it. To do this, we search      */
      /* all children until we found one that has not yet become a page. */
      MULTIPAGE_PAGE* pPage;
      WM_HWIN hChild;
      WM_Obj* pChild;
      WM_Obj* pClient = WM_H2P(pObj->hClient);
      int i;
      for (hChild = pClient->hFirstChild; hChild && !hWin; hChild = pChild->hNext) {
        pChild = WM_H2P(hChild);
        hWin = hChild;
        for (i = 0; i < pObj->Handles.NumItems; i++) {
          pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, i);
          if (pPage->hWin == hChild) {
            hWin = 0;
            break;
          }
        }
      }
    } else {
      /* If we get a handle we must ensure that it was attached to the multipage */
      WM_AttachWindowAt(hWin, pObj->hClient, 0, 0);
    }
    if (hWin) {
      MULTIPAGE_PAGE Page;
      char NullByte = 0;
      if (!pText) {
        pText = &NullByte;
      }
      Page.hWin   = hWin;
      Page.Status = MULTIPAGE_STATE_ENABLED;
      if (GUI_ARRAY_AddItem(&pObj->Handles, &Page, sizeof(MULTIPAGE_PAGE) + strlen(pText)) == 0) {
        MULTIPAGE_PAGE* pPage;
        pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, pObj->Handles.NumItems - 1);
        memcpy(&pPage->acText, pText, strlen(pText) + 1);
      }
      MULTIPAGE_SelectPage(hObj, pObj->Handles.NumItems - 1);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_DeletePage
*/
void MULTIPAGE_DeletePage(MULTIPAGE_Handle hObj, unsigned Index, int Delete) {
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      if ((int)Index < pObj->Handles.NumItems) {
        WM_HWIN hWin;
        MULTIPAGE_PAGE* pPage;
        pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
        hWin = pPage->hWin;
        /* Remove the page from the multipage object */
        if (Index == pObj->Selection) {
          if (Index == ((unsigned)pObj->Handles.NumItems - 1)) {
            _ShowPage(pObj, Index - 1);
            pObj->Selection--;
          } else {
            _ShowPage(pObj, Index + 1);
          }
        } else {
          if (Index < pObj->Selection) {
            pObj->Selection--;
          }
        }
        GUI_ARRAY_DeleteItem(&pObj->Handles, Index);
        _UpdatePositions(hObj, pObj);
        /* Delete the window of the page */
        if (Delete) {
          WM_DeleteWindow(hWin);
        }
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SelectPage
*/
void MULTIPAGE_SelectPage(MULTIPAGE_Handle hObj, unsigned Index) {
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      if ((int)Index < pObj->Handles.NumItems) {
        if (Index != pObj->Selection && _GetEnable(pObj, Index)) {
          _ShowPage(pObj, Index);
          pObj->Selection = Index;
          _UpdatePositions(hObj, pObj);
        }
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_DisablePage
*/
void MULTIPAGE_DisablePage(MULTIPAGE_Handle hObj, unsigned Index) {
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      _SetEnable(pObj, Index, 0);
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_EnablePage
*/
void MULTIPAGE_EnablePage(MULTIPAGE_Handle hObj, unsigned Index) {
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      _SetEnable(pObj, Index, 1);
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       MULTIPAGE_SetText
*/
void MULTIPAGE_SetText(MULTIPAGE_Handle hObj, const char* pText, unsigned Index) {
  MULTIPAGE_Obj* pObj;
  if (hObj && pText) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      if ((int)Index < pObj->Handles.NumItems) {
        MULTIPAGE_PAGE* pPage;
        MULTIPAGE_PAGE Page;
        pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
        Page.hWin   = pPage->hWin;
        Page.Status = pPage->Status;
        if (GUI_ARRAY_SetItem(&pObj->Handles, Index, &Page, sizeof(MULTIPAGE_PAGE) + strlen(pText))) {
          pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
          memcpy(&pPage->acText, pText, strlen(pText) + 1);          
          _UpdatePositions(hObj, pObj);
        }
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SetBkColor
*/
void MULTIPAGE_SetBkColor(MULTIPAGE_Handle hObj, GUI_COLOR Color, unsigned Index) {
  MULTIPAGE_Obj* pObj;
  if (hObj && ((int)Index < MULTIPAGE_NUMCOLORS)) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      pObj->aBkColor[Index] = Color;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SetTextColor
*/
void MULTIPAGE_SetTextColor(MULTIPAGE_Handle hObj, GUI_COLOR Color, unsigned Index) {
  MULTIPAGE_Obj* pObj;
  if (hObj && ((int)Index < MULTIPAGE_NUMCOLORS)) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      pObj->aTextColor[Index] = Color;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SetFont
*/
void MULTIPAGE_SetFont(MULTIPAGE_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont) {
  MULTIPAGE_Obj* pObj;
  if (hObj && pFont) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      pObj->Font = pFont;
      _UpdatePositions(hObj, pObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_SetAlign
*/
void MULTIPAGE_SetAlign(MULTIPAGE_Handle hObj, unsigned Align) {
  MULTIPAGE_Obj* pObj;
  GUI_RECT rClient;
  if (hObj) {
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      pObj->Align = Align;
      _CalcClientRect(pObj, &rClient);
      WM_MoveTo(pObj->hClient, rClient.x0 + pObj->Widget.Win.Rect.x0,
                               rClient.y0 + pObj->Widget.Win.Rect.y0);
      _UpdatePositions(hObj, pObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MULTIPAGE_GetSelection
*/
int MULTIPAGE_GetSelection(MULTIPAGE_Handle hObj) {
  int r = 0;
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      r = pObj->Selection;
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       MULTIPAGE_GetWindow
*/
WM_HWIN MULTIPAGE_GetWindow(MULTIPAGE_Handle hObj, unsigned Index) {
  WM_HWIN r = 0;
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      if ((int)Index < pObj->Handles.NumItems) {
        MULTIPAGE_PAGE* pPage;
        pPage = (MULTIPAGE_PAGE*) GUI_ARRAY_GetpItem(&pObj->Handles, Index);
        r = pPage->hWin;
      }
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       MULTIPAGE_IsPageEnabled
*/
int MULTIPAGE_IsPageEnabled(MULTIPAGE_Handle hObj, unsigned Index) {
  int r = 0;
  if (hObj) {
    MULTIPAGE_Obj* pObj;
    WM_LOCK();
    pObj = MULTIPAGE_H2P(hObj);
    MULTIPAGE_ASSERT_IS_VALID_PTR(pObj);
    if (pObj) {
      r = _GetEnable(pObj, Index);
    }
    WM_UNLOCK();
  }
  return r;
}

#else /* avoid empty object files */

void MULTIPAGE_C(void);
void MULTIPAGE_C(void){}

#endif  /* #if GUI_WINSUPPORT */



