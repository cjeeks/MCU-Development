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
File        : CHECKBOX.c
Purpose     : Implementation of checkbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Protected.h"
#include "CHECKBOX_Private.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef CHECKBOX_FONT_DEFAULT
  #define CHECKBOX_FONT_DEFAULT &GUI_Font13_1
#endif

/* Define default images */
#ifndef CHECKBOX_IMAGE0_DEFAULT
  #define CHECKBOX_IMAGE0_DEFAULT &CHECKBOX__abmCheck[0]
#endif

#ifndef CHECKBOX_IMAGE1_DEFAULT
  #define CHECKBOX_IMAGE1_DEFAULT &CHECKBOX__abmCheck[1]
#endif

/* Define widget background color */
#ifndef CHECKBOX_BKCOLOR_DEFAULT
  #define CHECKBOX_BKCOLOR_DEFAULT 0xC0C0C0           /* Text background color */
#endif

#ifndef CHECKBOX_SPACING_DEFAULT
  #define CHECKBOX_SPACING_DEFAULT 4
#endif

#ifndef CHECKBOX_TEXTCOLOR_DEFAULT
  #define CHECKBOX_TEXTCOLOR_DEFAULT GUI_BLACK
#endif

#ifndef CHECKBOX_TEXTALIGN_DEFAULT
  #define CHECKBOX_TEXTALIGN_DEFAULT (GUI_TA_LEFT | GUI_TA_VCENTER)
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

CHECKBOX_PROPS CHECKBOX__DefaultProps = {
  CHECKBOX_FONT_DEFAULT,
  CHECKBOX_BKCOLOR0_DEFAULT,
  CHECKBOX_BKCOLOR1_DEFAULT,
  CHECKBOX_BKCOLOR_DEFAULT,
  CHECKBOX_TEXTCOLOR_DEFAULT,
  CHECKBOX_TEXTALIGN_DEFAULT,
  CHECKBOX_SPACING_DEFAULT,
  CHECKBOX_IMAGE0_DEFAULT, 
  CHECKBOX_IMAGE1_DEFAULT
};

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define CHECKBOX_ID 0x4544   /* Magic numer, should be unique if possible */

#if GUI_DEBUG_LEVEL > 1
  #define CHECKBOX_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != CHECKBOX_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define CHECKBOX_INIT_ID(p)   p->DebugId = CHECKBOX_ID
  #define CHECKBOX_DEINIT_ID(p) p->DebugId = CHECKBOX_ID+1
#else
  #define CHECKBOX_ASSERT_IS_VALID_PTR(p)
  #define CHECKBOX_INIT_ID(p)
  #define CHECKBOX_DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _Paint
*/
static void _Paint(CHECKBOX_Obj* pObj, CHECKBOX_Handle hObj) {
  GUI_RECT RectBox = {0};
  int ColorIndex, EffectSize;
  EffectSize = pObj->Widget.pEffect->EffectSize;
  ColorIndex = WM__IsEnabled(hObj);
  /* Clear inside ... Just in case      */
  /* Fill with parents background color */
#if WM_SUPPORT_TRANSPARENCY
  if (!WM_GetHasTrans(hObj))
#endif
  {
    if (pObj->Props.BkColor == GUI_INVALID_COLOR) {
      LCD_SetBkColor(WIDGET__GetBkColor(hObj));
    } else {
      LCD_SetBkColor(pObj->Props.BkColor);
    }
    GUI_Clear();
  }
  /* Get size from bitmap */
  RectBox.x1 = pObj->Props.apBm[0]->XSize - 1 + 2 * EffectSize;
  RectBox.y1 = pObj->Props.apBm[0]->YSize - 1 + 2 * EffectSize;
  WM_SetUserClipRect(&RectBox);
  /* Clear inside  ... Just in case */
  LCD_SetBkColor(pObj->Props.aBkColorBox[ColorIndex]);
  GUI_Clear();
  if (pObj->CurrentState) {
    int Index = (pObj->CurrentState - 1) * 2 + ColorIndex;
    GUI_DrawBitmap(pObj->Props.apBm[Index], EffectSize, EffectSize);
  }
  /* Draw the effect arround the box */
  WIDGET__EFFECT_DrawDownRect(&pObj->Widget, &RectBox);
  WM_SetUserClipRect(NULL);
  /* Draw text if needed */
  if (pObj->hpText) {
    const char * s;
    GUI_RECT RectText;
    /* Draw the text */
    s = (const char *) GUI_ALLOC_h2p(pObj->hpText);
    WM_GetClientRect(&RectText);
    RectText.x0 += RectBox.x1 + 1 + pObj->Props.Spacing;
    GUI_SetTextMode(GUI_TM_TRANS);
    LCD_SetColor(pObj->Props.TextColor);
    GUI_SetFont(pObj->Props.pFont);
    GUI_DispStringInRect(s, &RectText, pObj->Props.Align);
    /* Draw focus rectangle */
    if (pObj->Widget.State & WIDGET_STATE_FOCUS) {
      int xSizeText = GUI_GetStringDistX(s);
      int ySizeText = GUI_GetFontSizeY();
      GUI_RECT RectFocus = RectText;
      switch (pObj->Props.Align & ~(GUI_TA_HORIZONTAL)) {
      case GUI_TA_VCENTER:
        RectFocus.y0 = (RectText.y1 - ySizeText) / 2;
        break;
      case GUI_TA_BOTTOM:
        RectFocus.y0 = RectText.y1 - ySizeText;
        break;
      }
      switch (pObj->Props.Align & ~(GUI_TA_VERTICAL)) {
      case GUI_TA_HCENTER:
        RectFocus.x0 += ((RectText.x1 - RectText.x0) - xSizeText) / 2;
        break;
      case GUI_TA_RIGHT:
        RectFocus.x0 += (RectText.x1 - RectText.x0) - xSizeText;
        break;
      }
      RectFocus.x1 = RectFocus.x0 + xSizeText;
      RectFocus.y1 = RectFocus.y0 + ySizeText;
      LCD_SetColor(GUI_BLACK);
      WIDGET__DrawFocusRect(&pObj->Widget, &RectFocus, 0);
    }
  }
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(CHECKBOX_Handle hObj, CHECKBOX_Obj* pObj, WM_MESSAGE*pMsg) {
  int Notification = 0;
  int Hit = 0;
  const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (!WM_HasCaptured(hObj)) {
      if (pState->Pressed) {
        WM_SetCapture(hObj, 1);
        pObj->CurrentState = (pObj->CurrentState + 1) % pObj->NumStates;
        WM_Invalidate(hObj);
        Notification = WM_NOTIFICATION_CLICKED;
      } else {
        Hit =1;
        Notification = WM_NOTIFICATION_RELEASED;
      }
    }
  } else {
    Notification = WM_NOTIFICATION_MOVED_OUT;
  }
  WM_NotifyParent(hObj, Notification);
  if (Hit == 1) {
    GUI_DEBUG_LOG("CHECKBOX: Hit\n");
    GUI_StoreKey(pObj->Widget.Id);
  }
}

/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(CHECKBOX_Handle hObj, CHECKBOX_Obj * pObj, WM_MESSAGE * pMsg) {
  WM_KEY_INFO * pKeyInfo;
  if (WM__IsEnabled(hObj)) {
    pKeyInfo = (WM_KEY_INFO *)(pMsg->Data.p);
    if (pKeyInfo->PressedCnt > 0) {
      switch (pKeyInfo->Key) {
      case GUI_KEY_SPACE:
        pObj->CurrentState = (pObj->CurrentState + 1) % pObj->NumStates;
        WM_Invalidate(hObj);
        break;                    /* Send to parent by not doing anything */
      }
    }
  }
}

/*********************************************************************
*
*       _CHECKBOX_Callback
*/
static void _CHECKBOX_Callback (WM_MESSAGE *pMsg) {
  CHECKBOX_Handle hObj;
  CHECKBOX_Obj* pObj;
  hObj = pMsg->hWin;
  pObj = CHECKBOX_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_KEY:
    _OnKey(hObj, pObj, pMsg);
    break;
  case WM_PAINT:
    GUI_DEBUG_LOG("CHECKBOX: _Callback(WM_PAINT)\n");
    _Paint(pObj, hObj);
    return;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
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
*       CHECKBOX_CreateEx
*/
CHECKBOX_Handle CHECKBOX_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                    int WinFlags, int ExFlags, int Id)
{
  CHECKBOX_Handle hObj;
  GUI_USE_PARA(ExFlags);
  WM_LOCK();
  /* Calculate size if needed */
  if ((xsize == 0) || (ysize == 0)) {
    int EffectSize;
    EffectSize = WIDGET_GetDefaultEffect()->EffectSize;
    if (xsize == 0) {
      xsize = CHECKBOX__DefaultProps.apBm[0]->XSize + 2 * EffectSize;
    }
    if (ysize == 0) {
      ysize = CHECKBOX__DefaultProps.apBm[0]->YSize + 2 * EffectSize;
    }
  }
#if WM_SUPPORT_TRANSPARENCY
  if (CHECKBOX__DefaultProps.BkColor == GUI_INVALID_COLOR) {
    WinFlags |= WM_CF_HASTRANS;
  }
#endif
  /* Create the window */
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, _CHECKBOX_Callback,
                                sizeof(CHECKBOX_Obj) - sizeof(WM_Obj));
  if (hObj) {
    CHECKBOX_Obj* pObj = CHECKBOX_H2P(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
    CHECKBOX_INIT_ID(pObj);
    /* init member variables */
    pObj->Props = CHECKBOX__DefaultProps;
    pObj->NumStates   = 2; /* Default behaviour is 2 states: checked and unchecked */
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "CHECKBOX_Create failed")
  }
  WM_UNLOCK();
  return hObj;
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_C(void);
  void CHECKBOX_C(void) {}
#endif  /* #if GUI_WINSUPPORT */



