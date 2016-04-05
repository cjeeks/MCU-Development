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
File        : TEXT.c
Purpose     : Implementation of text widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "TEXT_Private.h"
#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef TEXT_FONT_DEFAULT
  #define TEXT_FONT_DEFAULT &GUI_Font13_1
#endif

#ifndef TEXT_DEFAULT_TEXT_COLOR
  #define TEXT_DEFAULT_TEXT_COLOR GUI_BLACK
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const GUI_FONT GUI_UNI_PTR * _pDefaultFont = TEXT_FONT_DEFAULT;
static GUI_COLOR        _DefaultTextColor = TEXT_DEFAULT_TEXT_COLOR;

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _FreeAttached
*/
static void _FreeAttached(TEXT_Obj* pObj) {
  GUI_ALLOC_FreePtr(&pObj->hpText);
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(TEXT_Handle hObj, TEXT_Obj* pObj) {
  const char * s;
  GUI_RECT Rect;
  GUI_USE_PARA(hObj);
  LCD_SetColor(pObj->TextColor);
  GUI_SetFont    (pObj->pFont);
  /* Fill with parents background color */
  #if !TEXT_SUPPORT_TRANSPARENCY   /* Not needed any more, since window is transparent*/
    if (pObj->BkColor == GUI_INVALID_COLOR) {
      LCD_SetBkColor(WIDGET__GetBkColor(hObj));
    } else {
      LCD_SetBkColor(pObj->BkColor);
    }
    GUI_Clear();
  #else
    if (!WM_GetHasTrans(hObj)) {
      LCD_SetBkColor(pObj->BkColor);
      GUI_Clear();
    }
  #endif
  /* Show the text */
  if (pObj->hpText) {
    s = (const char*) GUI_ALLOC_h2p(pObj->hpText);
    GUI_SetTextMode(GUI_TM_TRANS);
    WM_GetClientRect(&Rect);
    GUI_DispStringInRect(s, &Rect, pObj->Align);
  }
}

/*********************************************************************
*
*       _Delete
*/
static void _Delete(TEXT_Obj* pObj) {
  /* Delete attached objects (if any) */
  GUI_DEBUG_LOG("TEXT: Delete() Deleting attached items");
  _FreeAttached(pObj);
}

/*********************************************************************
*
*       _TEXT_Callback
*/
static void _TEXT_Callback (WM_MESSAGE*pMsg) {
  TEXT_Handle hObj = pMsg->hWin;
  TEXT_Obj* pObj = TEXT_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DEBUG_LOG("TEXT: _Callback(WM_PAINT)\n");
    _Paint(hObj, pObj);
    return;
  case WM_DELETE:
    GUI_DEBUG_LOG("TEXT: _Callback(WM_DELETE)\n");
    _Delete(pObj);
    break;       /* No return here ... WM_DefaultProc needs to be called */
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
*       TEXT_CreateEx
*/
TEXT_Handle TEXT_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                          int WinFlags, int ExFlags, int Id, const char* pText)
{
  TEXT_Handle hObj;
  /* Create the window */
  #if TEXT_SUPPORT_TRANSPARENCY
    WinFlags |= WM_CF_HASTRANS;
  #endif
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, _TEXT_Callback,
                                sizeof(TEXT_Obj) - sizeof(WM_Obj));
  if (hObj) {
    TEXT_Obj* pObj;
    WM_HMEM hMem = 0;
    WM_LOCK();
    pObj = TEXT_H2P(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, 0);
    /* init member variables */
    TEXT_INIT_ID(pObj);
    if (pText) {
      hMem = GUI_ALLOC_AllocZero(strlen(pText) + 1);
      if (hMem) {
        strcpy((char*) GUI_ALLOC_h2p(hMem), pText);
      }
    }
    pObj->hpText = hMem;
    pObj->Align  = ExFlags;
    pObj->pFont  = _pDefaultFont;
    pObj->BkColor = GUI_INVALID_COLOR;
    pObj->TextColor = _DefaultTextColor;
    WM_UNLOCK();
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "TEXT_Create failed")
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
*       TEXT_SetDefaultFont
*/
void TEXT_SetDefaultFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  _pDefaultFont = pFont;
}

/*********************************************************************
*
*       TEXT_SetDefaultTextColor
*/
void TEXT_SetDefaultTextColor(GUI_COLOR Color) {
  _DefaultTextColor = Color;
}

/*********************************************************************
*
*       TEXT_GetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR * TEXT_GetDefaultFont(void) {
  return _pDefaultFont;
}

#else /* avoid empty object files */

void TEXT_C(void);
void TEXT_C(void){}

#endif  /* #if GUI_WINSUPPORT */


