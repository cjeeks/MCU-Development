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
File        : SLIDER.c
Purpose     : Implementation of slider widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Protected.h"
#include "SLIDER.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

#ifndef SLIDER_SUPPORT_TRANSPARENCY
  #define SLIDER_SUPPORT_TRANSPARENCY WM_SUPPORT_TRANSPARENCY
#endif

/* Support for 3D effects */
#ifndef SLIDER_USE_3D
  #define SLIDER_USE_3D 1
#endif

/* Define colors */
#ifndef SLIDER_BKCOLOR0_DEFAULT
  #define SLIDER_BKCOLOR0_DEFAULT 0xc0c0c0
#endif

#ifndef SLIDER_BKCOLOR1_DEFAULT
  #define SLIDER_BKCOLOR1_DEFAULT GUI_WHITE
#endif

#ifndef SLIDER_COLOR0_DEFAULT
  #define SLIDER_COLOR0_DEFAULT 0xc0c0c0
#endif

#ifndef SLIDER_COLOR1_DEFAULT
  #define SLIDER_COLOR1_DEFAULT GUI_BLACK
#endif

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  GUI_COLOR aBkColor[2];
  GUI_COLOR aColor[2];
  int Min, Max, v;
  int Flags;
  int NumTicks;
  I16 Width;
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} SLIDER_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define SLIDER_ID 0x4544   /* Magic numer, should be unique if possible */

#define SLIDER_H2P(h) (SLIDER_Obj*) GUI_ALLOC_h2p(h)

#if GUI_DEBUG_LEVEL > 1
  #define SLIDER_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != SLIDER_ID, "SLIDER.c: Wrong handle type or Object not init'ed")
  #define SLIDER_INIT_ID(p)   p->DebugId = SLIDER_ID
  #define SLIDER_DEINIT_ID(p) p->DebugId = SLIDER_ID+1
#else
  #define SLIDER_ASSERT_IS_VALID_PTR(p)
  #define SLIDER_INIT_ID(p)
  #define SLIDER_DEINIT_ID(p)
#endif


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static GUI_COLOR _DefaultBkColor = SLIDER_BKCOLOR0_DEFAULT;

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
static void _Paint(SLIDER_Obj* pObj, WM_HWIN hObj) {
  GUI_RECT r, rFocus, rSlider, rSlot;
  int x0, xsize, i, Range, NumTicks;
  WIDGET__GetClientRect(&pObj->Widget, &rFocus);
  GUI__ReduceRect(&r, &rFocus, 1);
  NumTicks = pObj->NumTicks;
  xsize    = r.x1 - r.x0  + 1 - pObj->Width;
  x0       = r.x0 + pObj->Width / 2;
  Range    = pObj->Max - pObj->Min;
  if (Range == 0) {
    Range = 1;
  }
  /* Fill with parents background color */
  #if !SLIDER_SUPPORT_TRANSPARENCY   /* Not needed any more, since window is transparent*/
    if (pObj->aBkColor[0] == GUI_INVALID_COLOR) {
      LCD_SetBkColor(WIDGET__GetBkColor(hObj));
    } else {
      LCD_SetBkColor(pObj->aBkColor[0]);
    }
    GUI_Clear();
  #else
    if (!WM_GetHasTrans(hObj)) {
      LCD_SetBkColor(pObj->aBkColor[0]);
      GUI_Clear();
    }
  #endif
  /* Calculate Slider position */
  rSlider    = r;
  rSlider.y0 = 5;
  rSlider.x0 = x0 + (U32)xsize * (U32)(pObj->v - pObj->Min) / Range - pObj->Width / 2;
  rSlider.x1 = rSlider.x0 + pObj->Width;
  /* Calculate Slot position */
  rSlot.x0 = x0;
  rSlot.x1 = x0 + xsize;
  rSlot.y0 = (rSlider.y0 + rSlider.y1) / 2 - 1;
  rSlot.y1 = rSlot.y0 + 3;
  WIDGET__EFFECT_DrawDownRect(&pObj->Widget, &rSlot);        /* Draw slot */
  /* Draw the ticks */
  if (NumTicks < 0) {
    NumTicks = Range + 1;
    if (NumTicks > (xsize / 5)) {
      NumTicks = 11;
    }
  }
  if (NumTicks > 1) {
    LCD_SetColor(GUI_BLACK);
    for (i = 0; i < NumTicks; i++) {
      int x = x0 + xsize * i / (NumTicks - 1);
      WIDGET__DrawVLine(&pObj->Widget, x, 1, 3);
    }
  }
  /* Draw the slider itself */
  LCD_SetColor(pObj->aColor[0]);
  WIDGET__FillRectEx(&pObj->Widget, &rSlider);
  LCD_SetColor(GUI_BLACK);
  WIDGET__EFFECT_DrawUpRect(&pObj->Widget, &rSlider);
  /* Draw focus */
  if (pObj->Widget.State & WIDGET_STATE_FOCUS) {
    LCD_SetColor(GUI_BLACK);
    WIDGET__DrawFocusRect(&pObj->Widget, &rFocus, 0);
  }
}

/*********************************************************************
*
*       _SliderPressed
*/
static void _SliderPressed(SLIDER_Handle hObj, SLIDER_Obj* pObj) {
  WIDGET_OrState(hObj, SLIDER_STATE_PRESSED);
  if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
    WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
  }
}

/*********************************************************************
*
*       _SliderReleased
*/
static void _SliderReleased(SLIDER_Handle hObj, SLIDER_Obj* pObj) {
  WIDGET_AndState(hObj, SLIDER_STATE_PRESSED);
  if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
    WM_NotifyParent(hObj, WM_NOTIFICATION_RELEASED);
  }
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(SLIDER_Handle hObj, SLIDER_Obj* pObj, WM_MESSAGE*pMsg) {
  const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      int x0, xsize, x, Sel, Range;
      Range = (pObj->Max - pObj->Min);
      x0    = 1 + pObj->Width / 2;  /* 1 pixel focus rectangle + width of actual slider */
      x     = (pObj->Widget.State & WIDGET_STATE_VERTICAL) ? pState->y : pState->x;
      x    -= x0;
      xsize = WIDGET__GetWindowSizeX(hObj) - 2 * x0;
      if (x <= 0) {
        Sel = pObj->Min;
      } else if (x >= xsize) {
        Sel = pObj->Max;
      } else {
        int Div;
        Div = xsize ? xsize : 1;     /* Make sure we do not divide by 0, even though xsize should never be 0 in this case anyhow */
        Sel = pObj->Min + ((U32)Range * (U32)x + Div / 2) / Div;
      }
      if (WM_IsFocussable(hObj)) {
        WM_SetFocus(hObj);
      }
      WM_SetCapture(hObj, 1);
      SLIDER_SetValue(hObj, Sel);
      if ((pObj->Widget.State & SLIDER_STATE_PRESSED) == 0){   
        _SliderPressed(hObj, pObj);
      }
    } else {
      /* React only if button was pressed before ... avoid problems with moving / hiding windows above (such as dropdown) */
      if (pObj->Widget.State & SLIDER_STATE_PRESSED) {   
        _SliderReleased(hObj, pObj);
      }
    }
  }
}

/*********************************************************************
*
*       _OnKey
*/
static void  _OnKey(SLIDER_Handle hObj, WM_MESSAGE*pMsg) {
  const WM_KEY_INFO* pKeyInfo;
  int Key;
  pKeyInfo = (const WM_KEY_INFO*)(pMsg->Data.p);
  Key = pKeyInfo->Key;
  if (pKeyInfo->PressedCnt > 0) {
    switch (Key) {
      case GUI_KEY_RIGHT:
        SLIDER_Inc(hObj);
        break;                    /* Send to parent by not doing anything */
      case GUI_KEY_LEFT:
        SLIDER_Dec(hObj);
        break;                    /* Send to parent by not doing anything */
      default:
        return;
    }
  }
}

/*********************************************************************
*
*       _SLIDER_Callback
*/
static void _SLIDER_Callback (WM_MESSAGE *pMsg) {
  SLIDER_Handle hObj;
  SLIDER_Obj* pObj;
  hObj = pMsg->hWin;
  pObj = SLIDER_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_DEBUG_LOG("SLIDER: _Callback(WM_PAINT)\n");
    _Paint(pObj, hObj);
    return;
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_KEY:
    _OnKey(hObj, pMsg);
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
*       SLIDER_CreateEx
*/
SLIDER_Handle SLIDER_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                              int WinFlags, int ExFlags, int Id)
{
  SLIDER_Handle hObj;
  /* Create the window */
  WM_LOCK();
  #if SLIDER_SUPPORT_TRANSPARENCY
    WinFlags |= WM_CF_HASTRANS;
  #endif
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, _SLIDER_Callback, sizeof(SLIDER_Obj) - sizeof(WM_Obj));
  if (hObj) {
    SLIDER_Obj* pObj = SLIDER_H2P(hObj);
    U16 InitState;
    /* Handle SpecialFlags */
    InitState = WIDGET_STATE_FOCUSSABLE;
    if (ExFlags & SLIDER_CF_VERTICAL) {
      InitState |= WIDGET_CF_VERTICAL;
    }
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, InitState);
    /* init member variables */
    SLIDER_INIT_ID(pObj);
    pObj->aBkColor[0] = _DefaultBkColor;
    pObj->aBkColor[1] = SLIDER_BKCOLOR1_DEFAULT;
    pObj->aColor[0]   = SLIDER_COLOR0_DEFAULT;
    pObj->aColor[1]   = SLIDER_COLOR1_DEFAULT;
    pObj->Width       = 8;
    pObj->Max         = 100;
    pObj->Min         = 0;
    pObj->NumTicks    = -1;
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "SLIDER_Create failed")
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
*       SLIDER_Dec
*/
void SLIDER_Dec(SLIDER_Handle hObj) {
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    if (pObj->v > pObj->Min) {
      pObj->v--;
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SLIDER_Inc
*/
void SLIDER_Inc(SLIDER_Handle hObj) {
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    if (pObj->v < pObj->Max) {
      pObj->v++;
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SLIDER_SetWidth
*/
void SLIDER_SetWidth(SLIDER_Handle hObj, int Width) {
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    if (pObj->Width != Width) {
      pObj->Width = Width;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SLIDER_SetValue
*/
void SLIDER_SetValue(SLIDER_Handle hObj, int v) {
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    /* Put in min/max range */
    if (v < pObj->Min) {
      v = pObj->Min;
    }
    if (v > pObj->Max) {
      v = pObj->Max;
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
*       SLIDER_SetRange
*/
void SLIDER_SetRange(SLIDER_Handle hObj, int Min, int Max) {
  if (hObj) {
    SLIDER_Obj* pObj;
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    if (Max < Min) {
      Max = Min;
    }
    pObj->Min = Min;
    pObj->Max = Max;
    if (pObj->v < Min) {
      pObj->v = Min;
    }
    if (pObj->v > Max) {
      pObj->v = Max;
    }
    WM_InvalidateWindow(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SLIDER_SetNumTicks
*/
void SLIDER_SetNumTicks(SLIDER_Handle hObj, int NumTicks) {
  if (hObj && (NumTicks >= 0)) {
    SLIDER_Obj* pObj;
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    pObj->NumTicks = NumTicks;
    WM_InvalidateWindow(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SLIDER_SetBkColor
*/
void SLIDER_SetBkColor(SLIDER_Handle hObj, GUI_COLOR Color) {
  if (hObj) {
    SLIDER_Obj * pObj;
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    pObj->aBkColor[0] = Color;
    #if SLIDER_SUPPORT_TRANSPARENCY
      if (Color <= 0xFFFFFF) {
        WM_ClrHasTrans(hObj);
      } else {
        WM_SetHasTrans(hObj);
      }
    #endif
    WM_InvalidateWindow(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       SLIDER_SetDefaultBkColor
*/
void SLIDER_SetDefaultBkColor(GUI_COLOR Color) {
  _DefaultBkColor = Color;
}

/*********************************************************************
*
*       Query state
*
**********************************************************************
*/
/*********************************************************************
*
*       SLIDER_GetValue
*/
int SLIDER_GetValue(SLIDER_Handle hObj) {
  int r = 0;
  SLIDER_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = SLIDER_H2P(hObj);
    r = pObj->v;
    WM_UNLOCK();
  }
  return r;
}


#else /* avoid empty object files */

void SLIDER_C(void);
void SLIDER_C(void){}

#endif  /* #if GUI_WINSUPPORT */



