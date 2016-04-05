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
File        : RADIO.c
Purpose     : Implementation of radio button widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "GUI_Protected.h"
#include "RADIO_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default image inactiv */
#ifndef RADIO_IMAGE0_DEFAULT
  #define RADIO_IMAGE0_DEFAULT        &RADIO__abmRadio[0]
#endif

/* Define default image activ */
#ifndef RADIO_IMAGE1_DEFAULT
  #define RADIO_IMAGE1_DEFAULT        &RADIO__abmRadio[1]
#endif

/* Define default image check */
#ifndef RADIO_IMAGE_CHECK_DEFAULT
  #define RADIO_IMAGE_CHECK_DEFAULT   &RADIO__bmCheck
#endif

/* Define default font */
#ifndef RADIO_FONT_DEFAULT
  #define RADIO_FONT_DEFAULT          &GUI_Font13_1
#endif

/* Define default text color */
#ifndef RADIO_DEFAULT_TEXT_COLOR
  #define RADIO_DEFAULT_TEXT_COLOR    GUI_BLACK
#endif

/* Define default background color */
#ifndef RADIO_DEFAULT_BKCOLOR
  #define RADIO_DEFAULT_BKCOLOR       0xC0C0C0
#endif

#define RADIO_BORDER                  2

/*********************************************************************
*
*       Public data, modul internal
*
**********************************************************************
*/

tRADIO_SetValue* RADIO__pfHandleSetValue;

GUI_COLOR         RADIO__DefaultTextColor       = RADIO_DEFAULT_TEXT_COLOR;
const GUI_FONT GUI_UNI_PTR* RADIO__pDefaultFont = RADIO_FONT_DEFAULT;
const GUI_BITMAP* RADIO__apDefaultImage[]       = {RADIO_IMAGE0_DEFAULT, RADIO_IMAGE1_DEFAULT};
const GUI_BITMAP* RADIO__pDefaultImageCheck     = RADIO_IMAGE_CHECK_DEFAULT;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define RADIO_ID 0x4544   /* Magic numer, should be unique if possible */

#if GUI_DEBUG_LEVEL > 1
  #define RADIO_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != RADIO_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define RADIO_INIT_ID(p)   p->DebugId = RADIO_ID
  #define RADIO_DEINIT_ID(p) p->DebugId = RADIO_ID+1
#else
  #define RADIO_ASSERT_IS_VALID_PTR(p)
  #define RADIO_INIT_ID(p)
  #define RADIO_DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _ResizeRect
*/
static void _ResizeRect(GUI_RECT* pDest, const GUI_RECT* pSrc, int Diff) {
  pDest->y0 = pSrc->y0 - Diff;
  pDest->y1 = pSrc->y1 + Diff;
  pDest->x0 = pSrc->x0 - Diff;
  pDest->x1 = pSrc->x1 + Diff;
}

/*********************************************************************
*
*       _OnPaint
*
* Purpose:
*   Paints the RADIO button.
*   The button can actually consist of multiple buttons (NumItems).
*   The focus rectangle will be drawn on top of the text if any text is set,
*   otherwise around the entire buttons.
*/
static void _OnPaint(RADIO_Handle hObj, RADIO_Obj* pObj) {
  const GUI_BITMAP* pBmRadio;
  const GUI_BITMAP* pBmCheck;
  const char* pText;
  GUI_FONTINFO FontInfo;
  GUI_RECT Rect, r, rFocus = {0};
  int i, y, HasFocus, FontDistY;
  U8 SpaceAbove, CHeight, FocusBorder;

  /* Init some data */
  WIDGET__GetClientRect(&pObj->Widget, &rFocus);
  HasFocus  = (pObj->Widget.State & WIDGET_STATE_FOCUS) ? 1 : 0;
  pBmRadio  = pObj->apBmRadio[WM__IsEnabled(hObj)];
  pBmCheck  = pObj->pBmCheck;
  rFocus.x1 = pBmRadio->XSize + RADIO_BORDER * 2 - 1;
  rFocus.y1 = pObj->Height + ((pObj->NumItems - 1) * pObj->Spacing) - 1;

  /* Select font and text color */
  LCD_SetColor(pObj->TextColor);
  GUI_SetFont(pObj->pFont);
  GUI_SetTextMode(GUI_TM_TRANS);

  /* Get font infos */
  GUI_GetFontInfo(pObj->pFont, &FontInfo);
  FontDistY   = GUI_GetFontDistY();
  CHeight     = FontInfo.CHeight;
  SpaceAbove  = FontInfo.Baseline - CHeight;
  Rect.x0     = pBmRadio->XSize + RADIO_BORDER * 2 + 2;
  Rect.y0     = (CHeight <= pObj->Height) ? ((pObj->Height - CHeight) / 2) : 0;
  Rect.y1     = Rect.y0 + CHeight - 1;
  FocusBorder = (FontDistY <= 12) ? 2 : 3;
  if (Rect.y0 < FocusBorder) {
    FocusBorder = Rect.y0;
  }

  /* Clear inside ... Just in case      */
  /* Fill with parents background color */
#if WM_SUPPORT_TRANSPARENCY
  if (!WM_GetHasTrans(hObj))
#endif
  {
    if (pObj->BkColor != GUI_INVALID_COLOR) {
      LCD_SetBkColor(pObj->BkColor);
    } else {
      LCD_SetBkColor(RADIO_DEFAULT_BKCOLOR);
    }
    GUI_Clear();
  }

  /* Iterate over all items */
  for (i = 0; i < pObj->NumItems; i++) {
    y = i * pObj->Spacing;
    /* Draw the radio button bitmap */
    GUI_DrawBitmap(pBmRadio, RADIO_BORDER, RADIO_BORDER + y);
    /* Draw the check bitmap */
    if (pObj->Sel == i) {
      GUI_DrawBitmap(pBmCheck, RADIO_BORDER +  (pBmRadio->XSize - pBmCheck->XSize) / 2, 
                               RADIO_BORDER + ((pBmRadio->YSize - pBmCheck->YSize) / 2) + y);
    }
    /* Draw text if available */
    pText = (const char*)GUI_ARRAY_GetpItem(&pObj->TextArray, i);
    if (pText) {
      if (*pText) {
        r = Rect;
        r.x1 = r.x0 + GUI_GetStringDistX(pText) - 2;
        GUI_MoveRect(&r, 0, y);
        GUI_DispStringAt(pText, r.x0, r.y0 - SpaceAbove);
        /* Calculate focus rect */
        if (HasFocus && (pObj->Sel == i)) {
          _ResizeRect(&rFocus, &r, FocusBorder);
        }
      }
    }
  }

  /* Draw the focus rect */
  if (HasFocus) {
    LCD_SetColor(GUI_BLACK);
    WIDGET__DrawFocusRect(&pObj->Widget, &rFocus, 0);
  }
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(RADIO_Handle hObj, RADIO_Obj* pObj, WM_MESSAGE*pMsg) {
  int Notification;
  int Hit = 0;
  GUI_PID_STATE* pState = (GUI_PID_STATE*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      int y, Sel;
      y   = pState->y;
      Sel = y   / pObj->Spacing;
      y  -= Sel * pObj->Spacing;
      if (y <= pObj->Height) {
        RADIO_SetValue(hObj, Sel);
      }
      if (WM_IsFocussable(hObj)) {
        WM_SetFocus(hObj);
      }
      Notification = WM_NOTIFICATION_CLICKED;
    } else {
      Hit = 1;
      Notification = WM_NOTIFICATION_RELEASED;
    }
  } else {
    Notification = WM_NOTIFICATION_MOVED_OUT;
  }
  WM_NotifyParent(hObj, Notification);
  if (Hit == 1) {
    GUI_DEBUG_LOG("RADIO: Hit\n");
    GUI_StoreKey(pObj->Widget.Id);
  }
}

/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(RADIO_Handle hObj, WM_MESSAGE* pMsg) {
  WM_KEY_INFO* pKeyInfo;
  pKeyInfo = (WM_KEY_INFO*)(pMsg->Data.p);
  if (pKeyInfo->PressedCnt > 0) {
    switch (pKeyInfo->Key) {
    case GUI_KEY_RIGHT:
    case GUI_KEY_DOWN:
      RADIO_Inc(hObj);
      break;                    /* Send to parent by not doing anything */
    case GUI_KEY_LEFT:
    case GUI_KEY_UP:
      RADIO_Dec(hObj);
      break;                    /* Send to parent by not doing anything */
    default:
      return;
    }
  }
}

/*********************************************************************
*
*       _RADIO_Callback
*/
static void _RADIO_Callback (WM_MESSAGE* pMsg) {
  RADIO_Handle hObj;
  RADIO_Obj*   pObj;
  hObj = pMsg->hWin;
  pObj = RADIO_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DEBUG_LOG("RADIO: _Callback(WM_PAINT)\n");
    _OnPaint(hObj, pObj);
    return;
  case WM_GET_RADIOGROUP:
    pMsg->Data.v = pObj->GroupId;
    return;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_KEY:
    _OnKey(hObj, pMsg);
    break;
  case WM_DELETE:
    GUI_ARRAY_Delete(&pObj->TextArray);
    break;
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Exported routines, modul internal
*
**********************************************************************
*/
/*********************************************************************
*
*       RADIO__SetValue
*/
void RADIO__SetValue(RADIO_Handle hObj, RADIO_Obj* pObj, int v) {
  if (v >= pObj->NumItems) {
    v = (int)pObj->NumItems - 1;
  }
  if (v != pObj->Sel) {
    pObj->Sel = v;
    WM_InvalidateWindow(hObj);
    WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
  }
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
*       RADIO_CreateEx
*/
RADIO_Handle RADIO_CreateEx(int x0, int y0, int xSize, int ySize, WM_HWIN hParent,
                            int WinFlags, int ExFlags, int Id, int NumItems, int Spacing)
{
  RADIO_Handle hObj;
  int Height, i;
  /* Calculate helper variables */
  Height   = RADIO__apDefaultImage[0]->YSize + RADIO_BORDER * 2;
  Spacing  = (Spacing  <= 0) ? 20 : Spacing;
  NumItems = (NumItems <= 0) ?  2 : NumItems;
  if (ySize == 0) {
    ySize  = Height + ((NumItems - 1) * Spacing);
  }
  if (xSize == 0) {
    xSize  = RADIO__apDefaultImage[0]->XSize + RADIO_BORDER * 2;
  }
#if WM_SUPPORT_TRANSPARENCY
  WinFlags |= WM_CF_HASTRANS;
#endif
  /* Create the window */
  hObj = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent, WinFlags, _RADIO_Callback, sizeof(RADIO_Obj) - sizeof(WM_Obj));
  if (hObj) {
    RADIO_Obj* pObj;
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    /* Init sub-classes */
    GUI_ARRAY_CREATE(&pObj->TextArray);
    for (i = 0; i < NumItems; i++) {
      GUI_ARRAY_AddItem(&pObj->TextArray, NULL, 0);
    }
    /* Init widget specific variables */
    ExFlags &= RADIO_TEXTPOS_LEFT;
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE | ExFlags);
    /* Init member variables */
    RADIO_INIT_ID(pObj);
    pObj->apBmRadio[0] = RADIO__apDefaultImage[0];
    pObj->apBmRadio[1] = RADIO__apDefaultImage[1];
    pObj->pBmCheck     = RADIO__pDefaultImageCheck;
    pObj->pFont        = RADIO__pDefaultFont;
    pObj->TextColor    = RADIO__DefaultTextColor;
    pObj->BkColor      = WM_GetBkColor(hParent);
    pObj->NumItems     = NumItems;
    pObj->Spacing      = Spacing;
    pObj->Height       = Height;
    WM_UNLOCK();
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "RADIO_Create failed")
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
*       RADIO_AddValue
*/
void RADIO_AddValue(RADIO_Handle hObj, int Add) {
  if (hObj) {
    RADIO_Obj* pObj;
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    RADIO_SetValue(hObj, pObj->Sel + Add);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       RADIO_Dec
*/
void RADIO_Dec(RADIO_Handle hObj) {
  RADIO_AddValue(hObj, -1);
}

/*********************************************************************
*
*       RADIO_Inc
*/
void RADIO_Inc(RADIO_Handle hObj) {
  RADIO_AddValue(hObj,  1);
}

/*********************************************************************
*
*       RADIO_SetValue
*/
void RADIO_SetValue(RADIO_Handle hObj, int v) {
  if (hObj) {
    RADIO_Obj* pObj;
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    if (pObj->GroupId && RADIO__pfHandleSetValue) {
      (*RADIO__pfHandleSetValue)(hObj, pObj, v);
    } else {
      if (v < 0) {
        v = 0;
      }
      RADIO__SetValue(hObj, pObj, v);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       Exported routines:  Query state
*
**********************************************************************
*/
/*********************************************************************
*
*       RADIO_GetValue
*/
int RADIO_GetValue(RADIO_Handle hObj) {
  int r = 0;
  if (hObj) {
    RADIO_Obj* pObj;
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    r = pObj->Sel;
    WM_UNLOCK();
  }
  return r;
}

#else /* avoid empty object files */

void RADIO_C(void);
void RADIO_C(void){}

#endif  /* #if GUI_WINSUPPORT */

/************************* end of file ******************************/
