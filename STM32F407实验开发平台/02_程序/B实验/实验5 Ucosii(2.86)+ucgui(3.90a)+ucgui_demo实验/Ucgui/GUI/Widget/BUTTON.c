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
File        : BUTTON.c
Purpose     : Implementation of button widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "BUTTON_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef   BUTTON_FONT_DEFAULT
  #define BUTTON_FONT_DEFAULT &GUI_Font13_1
#endif

/* Support for 3D effects */
#ifndef   BUTTON_USE_3D
  #define BUTTON_USE_3D 1
#endif

#ifndef   BUTTON_3D_MOVE_X
  #define BUTTON_3D_MOVE_X 1
#endif
#ifndef   BUTTON_3D_MOVE_Y
  #define BUTTON_3D_MOVE_Y 1
#endif

/* Define colors */
#ifndef   BUTTON_BKCOLOR0_DEFAULT
  #define BUTTON_BKCOLOR0_DEFAULT   0xAAAAAA
#endif

#ifndef   BUTTON_BKCOLOR1_DEFAULT
  #define BUTTON_BKCOLOR1_DEFAULT   GUI_WHITE
#endif

#ifndef   BUTTON_BKCOLOR2_DEFAULT
  #define BUTTON_BKCOLOR2_DEFAULT   GUI_LIGHTGRAY
#endif

#ifndef   BUTTON_TEXTCOLOR0_DEFAULT
  #define BUTTON_TEXTCOLOR0_DEFAULT GUI_BLACK
#endif

#ifndef   BUTTON_TEXTCOLOR1_DEFAULT
  #define BUTTON_TEXTCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef   BUTTON_TEXTCOLOR2_DEFAULT
  #define BUTTON_TEXTCOLOR2_DEFAULT GUI_DARKGRAY
#endif

#ifndef   BUTTON_REACT_ON_LEVEL
  #define BUTTON_REACT_ON_LEVEL 0
#endif

#ifndef   BUTTON_ALIGN_DEFAULT
  #define BUTTON_ALIGN_DEFAULT GUI_TA_HCENTER | GUI_TA_VCENTER
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
BUTTON_PROPS BUTTON__DefaultProps = {
  BUTTON_BKCOLOR0_DEFAULT,
  BUTTON_BKCOLOR1_DEFAULT,
  BUTTON_BKCOLOR2_DEFAULT,
  BUTTON_TEXTCOLOR0_DEFAULT,
  BUTTON_TEXTCOLOR1_DEFAULT,
  BUTTON_TEXTCOLOR2_DEFAULT,
  BUTTON_FONT_DEFAULT,
  BUTTON_ALIGN_DEFAULT
};

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
static void _Paint(BUTTON_Obj* pObj, BUTTON_Handle hObj) {
  const char* s = NULL;
  unsigned int Index;
  int State, PressedState, ColorIndex;
  GUI_RECT rClient, rInside;
  State = pObj->Widget.State;
  PressedState = (State & BUTTON_STATE_PRESSED) ? 1 : 0;
  ColorIndex   = (WM__IsEnabled(hObj)) ? PressedState : 2;
  GUI_SetFont(pObj->Props.pFont);
  GUI_DEBUG_LOG("BUTTON: Paint(..)\n");
  if (pObj->hpText) {
    s = (const char*) GUI_ALLOC_h2p(pObj->hpText);
  }
  GUI_GetClientRect(&rClient);
  /* Start drawing */
  rInside = rClient;
/* Draw the 3D effect (if configured) */
  #if BUTTON_USE_3D
  {
    int EffectSize;
    if ((PressedState) == 0) {
      pObj->Widget.pEffect->pfDrawUp();  /* _WIDGET_EFFECT_3D_DrawUp(); */
      EffectSize = pObj->Widget.pEffect->EffectSize;
    } else {
      LCD_SetColor(0x000000);
      GUI_DrawRect(rClient.y0, rClient.x0, rClient.x1, rClient.y1);
      EffectSize = 1;
    }
    GUI__ReduceRect(&rInside, &rInside, EffectSize); 
  }
  #endif
  /* Draw background */
  LCD_SetBkColor (pObj->Props.aBkColor[ColorIndex]);
  LCD_SetColor   (pObj->Props.aTextColor[ColorIndex]);
  WM_SetUserClipRect(&rInside);
  GUI_Clear();
  /* Draw bitmap.
     If we have only one, we will use it.
     If we have to we will use the second one (Index 1) for the pressed state
  */
  if (ColorIndex < 2) {
    Index = (pObj->ahDrawObj[BUTTON_BI_PRESSED] && PressedState) ? BUTTON_BI_PRESSED : BUTTON_BI_UNPRESSED;
  } else {
    Index = pObj->ahDrawObj[BUTTON_BI_DISABLED] ? BUTTON_BI_DISABLED : BUTTON_BI_UNPRESSED;
  }
  GUI_DRAW__Draw(pObj->ahDrawObj[Index], 0, 0);
/* Draw the actual button (background and text) */  
  {
    GUI_RECT r;
    r = rInside;
    #if BUTTON_USE_3D
      if (PressedState) {
        GUI_MoveRect(&r, BUTTON_3D_MOVE_X,BUTTON_3D_MOVE_Y);
      }
    #endif
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_DispStringInRect(s, &r, pObj->Props.Align);
  }
  /* Draw focus */
  if (State & BUTTON_STATE_FOCUS) {
    LCD_SetColor(GUI_BLACK);
    GUI_DrawFocusRect(&rClient, 2);
  }
  WM_SetUserClipRect(NULL);
}

/*********************************************************************
*
*       _Delete
*
* Delete attached objects (if any)
*/
static void _Delete(BUTTON_Obj* pObj) {
  GUI_ALLOC_FreePtr(&pObj->hpText);
  GUI_ALLOC_FreePtr(&pObj->ahDrawObj[0]);
  GUI_ALLOC_FreePtr(&pObj->ahDrawObj[1]);
}

/*********************************************************************
*
*       _ButtonPressed
*/
static void _ButtonPressed(BUTTON_Handle hObj, BUTTON_Obj* pObj) {
  WIDGET_OrState(hObj, BUTTON_STATE_PRESSED);
  if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
    WM_NotifyParent(hObj, WM_NOTIFICATION_CLICKED);
  }
}

/*********************************************************************
*
*       _ButtonReleased
*/
static void _ButtonReleased(BUTTON_Handle hObj, BUTTON_Obj* pObj, int Notification) {
  WIDGET_AndState(hObj, BUTTON_STATE_PRESSED);
  if (pObj->Widget.Win.Status & WM_SF_ISVIS) {
    WM_NotifyParent(hObj, Notification);
  }
  if (Notification == WM_NOTIFICATION_RELEASED) {
    GUI_DEBUG_LOG("BUTTON: Hit\n");
    GUI_StoreKey(pObj->Widget.Id);
  }
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(BUTTON_Handle hObj, BUTTON_Obj* pObj, WM_MESSAGE*pMsg) {
  const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
#if BUTTON_REACT_ON_LEVEL
  if (!pMsg->Data.p) {  /* Mouse moved out */
    _ButtonReleased(hObj, pObj, WM_NOTIFICATION_MOVED_OUT);
  }
#else
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
    if (pState->Pressed) {
      if ((pObj->Widget.State & BUTTON_STATE_PRESSED) == 0){   
       _ButtonPressed(hObj, pObj);
      }
    } else {
      /* React only if button was pressed before ... avoid problems with moving / hiding windows above (such as dropdown) */
      if (pObj->Widget.State & BUTTON_STATE_PRESSED) {   
        _ButtonReleased(hObj, pObj, WM_NOTIFICATION_RELEASED);
      }
    }
  } else {
    _ButtonReleased(hObj, pObj, WM_NOTIFICATION_MOVED_OUT);
  }

#endif
}

/*********************************************************************
*
*       _OnPidStateChange
*/
#if BUTTON_REACT_ON_LEVEL
static void _OnPidStateChange(BUTTON_Handle hObj, BUTTON_Obj * pObj, WM_MESSAGE * pMsg) {
  const WM_PID_STATE_CHANGED_INFO * pState = (const WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
  if ((pState->StatePrev == 0) && (pState->State == 1)) {
    if ((pObj->Widget.State & BUTTON_STATE_PRESSED) == 0){   
      _ButtonPressed(hObj, pObj);
    }
  } else if ((pState->StatePrev == 1) && (pState->State == 0)) {
    if (pObj->Widget.State & BUTTON_STATE_PRESSED) {   
      _ButtonReleased(hObj, pObj, WM_NOTIFICATION_RELEASED);
    }
  }
}
#endif

/*********************************************************************
*
*       BUTTON_Callback
*/
void BUTTON_Callback(WM_MESSAGE *pMsg) {
  BUTTON_Handle hObj = pMsg->hWin;
  BUTTON_Obj* pObj = BUTTON_H2P(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
#if BUTTON_REACT_ON_LEVEL
  case WM_PID_STATE_CHANGED:
    _OnPidStateChange(hObj, pObj, pMsg);
    return;      /* Message handled. Do not call WM_DefaultProc, because the window may have been destroyed */
#endif
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    return;      /* Message handled. Do not call WM_DefaultProc, because the window may have been destroyed */
  case WM_PAINT:
    GUI_DEBUG_LOG("BUTTON: _BUTTON_Callback(WM_PAINT)\n");
    _Paint(pObj, hObj);
    return;
  case WM_DELETE:
    GUI_DEBUG_LOG("BUTTON: _BUTTON_Callback(WM_DELETE)\n");
    _Delete(pObj);
    break;       /* No return here ... WM_DefaultProc needs to be called */
  #if 0     /* TBD: Button should react to space & Enter */
  case WM_KEY:
    {
      int PressedCnt = ((WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt;
      int Key = ((WM_KEY_INFO*)(pMsg->Data.p))->Key;
      if (PressedCnt > 0) {   /* Key pressed? */
        switch (Key) {
        case ' ':
          _ButtonPressed(hObj, pObj);
          return;
        }
      } else {
        switch (Key) {
        case ' ':
          _ButtonReleased(hObj, pObj, WM_NOTIFICATION_RELEASED);
          return;
        }
      }
    }
    break;
  #endif
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Exported routines:  Create
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_CreateEx
*/
BUTTON_Handle BUTTON_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id) {
  BUTTON_Handle hObj;
  GUI_USE_PARA(ExFlags);
  /* Create the window */
  WM_LOCK();
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, BUTTON_Callback,
                                sizeof(BUTTON_Obj) - sizeof(WM_Obj));
  if (hObj) {
    BUTTON_Obj* pObj = BUTTON_H2P(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
    /* init member variables */
    BUTTON_INIT_ID(pObj);
    pObj->Props = BUTTON__DefaultProps;
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "BUTTON_Create failed")
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
*       BUTTON_SetText
*/
void BUTTON_SetText(BUTTON_Handle hObj, const char* s) {
  if (hObj) {
    BUTTON_Obj* pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    if (GUI__SetText(&pObj->hpText, s)) {
      BUTTON_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       BUTTON_SetFont
*/
void BUTTON_SetFont(BUTTON_Handle hObj, const GUI_FONT GUI_UNI_PTR * pfont) {
  if (hObj) {
    BUTTON_Obj* pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    pObj->Props.pFont = pfont;
    BUTTON_Invalidate(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       BUTTON_SetBkColor
*/
void BUTTON_SetBkColor(BUTTON_Handle hObj,unsigned int Index, GUI_COLOR Color) {
  if (hObj && (Index <= 2)) {
    BUTTON_Obj* pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    pObj->Props.aBkColor[Index] = Color;
    BUTTON_Invalidate(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       BUTTON_SetTextColor
*/
void BUTTON_SetTextColor(BUTTON_Handle hObj,unsigned int Index, GUI_COLOR Color) {
  if (hObj && (Index <= 2)) {
    BUTTON_Obj* pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    BUTTON_ASSERT_IS_VALID_PTR(pObj);
    pObj->Props.aTextColor[Index] = Color;
    BUTTON_Invalidate(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       BUTTON_SetState
*/
void BUTTON_SetState(BUTTON_Handle hObj, int State) {
  WIDGET_SetState(hObj, State);
}

/*********************************************************************
*
*       BUTTON_SetPressed
*/
void BUTTON_SetPressed(BUTTON_Handle hObj, int State) {
  if (State) {
    WIDGET_OrState(hObj, BUTTON_STATE_PRESSED);
  } else {
    WIDGET_AndState(hObj, BUTTON_STATE_PRESSED);
  }
}

/*********************************************************************
*
*       BUTTON_SetFocussable
*/
void BUTTON_SetFocussable(BUTTON_Handle hObj, int State) {
  if (State) {
    WIDGET_OrState(hObj, WIDGET_STATE_FOCUSSABLE);
  } else {
    WIDGET_AndState(hObj, WIDGET_STATE_FOCUSSABLE);
  }
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_C(void) {}
#endif /* GUI_WINSUPPORT */




