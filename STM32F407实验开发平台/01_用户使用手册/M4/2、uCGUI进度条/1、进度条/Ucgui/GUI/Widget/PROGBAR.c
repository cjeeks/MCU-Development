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
File        : ProgBar.c
Purpose     : Implementation of progress bar
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Protected.h"
#include "PROGBAR.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

#ifndef PROGBAR_DEFAULT_FONT
  #define PROGBAR_DEFAULT_FONT GUI_DEFAULT_FONT
#endif

#ifndef PROGBAR_DEFAULT_BARCOLOR0
  #define PROGBAR_DEFAULT_BARCOLOR0 0x555555
#endif

#ifndef PROGBAR_DEFAULT_BARCOLOR1
  #define PROGBAR_DEFAULT_BARCOLOR1 0xAAAAAA
#endif

#ifndef PROGBAR_DEFAULT_TEXTCOLOR0
  #define PROGBAR_DEFAULT_TEXTCOLOR0 0xFFFFFF
#endif

#ifndef PROGBAR_DEFAULT_TEXTCOLOR1
  #define PROGBAR_DEFAULT_TEXTCOLOR1 0x000000
#endif

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  int v;
  const GUI_FONT GUI_UNI_PTR * pFont;
  GUI_COLOR BarColor[2];
  GUI_COLOR TextColor[2];
  WM_HMEM hpText;
  I16 XOff, YOff;
  I16 TextAlign;
  int Min, Max;
/*  I16 Options; */
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    int DebugId;
  #endif  
} PROGBAR_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define Invalidate(h) WM_InvalidateWindow(h)

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define OBJECT_ID 0x4569   /* Magic nubmer, should be unique if possible */
  #define INIT_ID(p)   p->DebugId = OBJECT_ID
  #define DEINIT_ID(p) p->DebugId = OBJECT_ID+1
#else
  #define INIT_ID(p)
  #define DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  PROGBAR_Obj* PROGBAR_h2p(PROGBAR_Handle h) {
    PROGBAR_Obj* p = (PROGBAR_Obj*)GUI_ALLOC_h2p(h);
    if (p) {
      if (p->DebugId != OBJECT_ID) {
        GUI_DEBUG_ERROROUT("PROGBAR.C: Wrong handle type or Object not init'ed");
        return 0;
      }
    }
    return p;
  }
  #define PROGBAR_H2P(h) PROGBAR_h2p(h)
#else
  #define PROGBAR_H2P(h) (PROGBAR_Obj*) GUI_ALLOC_h2p(h)
#endif

/*********************************************************************
*
*       _FreeText
*/
static void _FreeText(PROGBAR_Handle hObj) {
  PROGBAR_Obj* pObj = PROGBAR_H2P(hObj);
  GUI_ALLOC_FreePtr(&pObj->hpText);
}

/*********************************************************************
*
*       _Value2X
*/
static int _Value2X(const PROGBAR_Obj* pObj, int v) {
  int EffectSize = pObj->Widget.pEffect->EffectSize;
  int xSize = pObj->Widget.Win.Rect.x1 - pObj->Widget.Win.Rect.x0 + 1;
  int Min   = pObj->Min;
  int Max   = pObj->Max;
  if (v < Min) {
	  v = Min;
  }
  if (v > Max) {
	  v = Max;
  }
  return EffectSize + ((xSize - 2 * EffectSize) * (I32)(v - Min)) / (Max - Min);
}

/*********************************************************************
*
*       _DrawPart
*/
static void _DrawPart(const PROGBAR_Obj* pObj, int Index,
										  int xText, int yText, const char* pText) {
  LCD_SetBkColor(pObj->BarColor[Index]);
  LCD_SetColor(pObj->TextColor[Index]);
  GUI_Clear();
  GUI_GotoXY(xText, yText);
  GUI_DispString(pText);
}

/*********************************************************************
*
*       _GetText
*/
static const char* _GetText(const PROGBAR_Obj* pObj, char* pBuffer) {
  char* pText;
  if (pObj->hpText) {
    pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
  } else {
    pText = pBuffer;
    GUI_AddDecMin((100 * (I32)(pObj->v - pObj->Min)) / (pObj->Max - pObj->Min), &pBuffer);
    *pBuffer++ = '%';
		*pBuffer   = 0;
	}
  return (const char*)pText;
}

/*********************************************************************
*
*       _GetTextRect
*/
static void _GetTextRect(const PROGBAR_Obj* pObj, GUI_RECT* pRect, const char* pText) {
  int xSize      = pObj->Widget.Win.Rect.x1 - pObj->Widget.Win.Rect.x0 + 1;
  int ySize      = pObj->Widget.Win.Rect.y1 - pObj->Widget.Win.Rect.y0 + 1;
  int TextWidth  = GUI_GetStringDistX(pText);
  int TextHeight = GUI_GetFontSizeY();
  int EffectSize = pObj->Widget.pEffect->EffectSize;
  switch (pObj->TextAlign & GUI_TA_HORIZONTAL) {
  case GUI_TA_CENTER:
    pRect->x0 = (xSize - TextWidth) / 2;
		break;
  case GUI_TA_RIGHT:
    pRect->x0 = xSize - TextWidth - 1 - EffectSize;
		break;
  default:
    pRect->x0 = EffectSize;
	}
  pRect->y0  = (ySize - TextHeight) / 2;
  pRect->x0 += pObj->XOff;
  pRect->y0 += pObj->YOff;
  pRect->x1  = pRect->x0 + TextWidth  - 1;
  pRect->y1  = pRect->y0 + TextHeight - 1;
}

/*********************************************************************
*
*       _Paint
*/
static void _Paint(PROGBAR_Handle hObj) {
  PROGBAR_Obj* pObj;
  GUI_RECT r, rInside, rClient, rText;
  const char* pText;
  char ac[5];
  int tm, xPos;
  pObj = PROGBAR_H2P(hObj);
  WM_GetClientRect(&rClient);
  GUI__ReduceRect(&rInside, &rClient, pObj->Widget.pEffect->EffectSize);
  xPos  = _Value2X(pObj, pObj->v);
  pText = _GetText(pObj, ac);
  GUI_SetFont(pObj->pFont);
  _GetTextRect(pObj, &rText, pText);
  tm = GUI_SetTextMode(GUI_TM_TRANS);
  /* Draw left bar */
  r    = rInside;
  r.x1 = xPos - 1;
  WM_SetUserClipArea(&r);
  _DrawPart(pObj, 0, rText.x0, rText.y0, pText);
  /* Draw right bar */
  r    = rInside;
  r.x0 = xPos;
  WM_SetUserClipArea(&r);
  _DrawPart(pObj, 1, rText.x0, rText.y0, pText);
  WM_SetUserClipArea(NULL);
  GUI_SetTextMode(tm);
  WIDGET__EFFECT_DrawDownRect(&pObj->Widget, &rClient);
}

/*********************************************************************
*
*       _Delete
*/
static void _Delete(PROGBAR_Handle hObj) {
  _FreeText(hObj);
  DEINIT_ID(PROGBAR_H2P(hObj));
}

/*********************************************************************
*
*       _Callback
*/
static void _PROGBAR_Callback(WM_MESSAGE*pMsg) {
  PROGBAR_Handle hObj = (PROGBAR_Handle)pMsg->hWin;
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_PAINT:
    _Paint(hObj);
    return;
  case WM_DELETE:
    _Delete(hObj);
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
/*********************************************************************
*
*       PROGBAR_CreateEx
*/
PROGBAR_Handle PROGBAR_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                int WinFlags, int ExFlags, int Id)
{
  PROGBAR_Handle hObj;
  GUI_USE_PARA(ExFlags);
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WinFlags, _PROGBAR_Callback,
                                sizeof(PROGBAR_Obj) - sizeof(WM_Obj));
  if (hObj) {
    PROGBAR_Obj* pObj;
    WM_LOCK();
    pObj = (PROGBAR_Obj*) GUI_ALLOC_h2p(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, 0);
    WIDGET_SetEffect(hObj, &WIDGET_Effect_None); /* Standard effect for progbar: None */
    INIT_ID(pObj);
    /* init member variables */
    pObj->pFont        = GUI_DEFAULT_FONT;
    pObj->BarColor[0]  = PROGBAR_DEFAULT_BARCOLOR0;
    pObj->BarColor[1]  = PROGBAR_DEFAULT_BARCOLOR1;
    pObj->TextColor[0] = PROGBAR_DEFAULT_TEXTCOLOR0;
    pObj->TextColor[1] = PROGBAR_DEFAULT_TEXTCOLOR1;
    pObj->TextAlign    = GUI_TA_CENTER;
    pObj->Max          = 100;
    pObj->Min          = 0;
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
*       PROGBAR_SetValue
*/
void PROGBAR_SetValue(PROGBAR_Handle hObj, int v) {
  if (hObj) {
    PROGBAR_Obj* pObj;
    WM_LOCK();
    pObj= PROGBAR_H2P(hObj);
    /* Put v into legal range */
    if (v < pObj->Min) {
	    v = pObj->Min;
    }
    if (v > pObj->Max) {
	    v = pObj->Max;
    }
    if (pObj->v != v) {
      GUI_RECT r;
      /* Get x values */
      if (v < pObj->v) {
        r.x0 = _Value2X(pObj, v);
        r.x1 = _Value2X(pObj, pObj->v);
      } else {
        r.x0 = _Value2X(pObj, pObj->v);
        r.x1 = _Value2X(pObj, v);
      }
		  r.y0    = 0;
		  r.y1    = 4095;
      if (pObj->hpText == 0) {
        const GUI_FONT GUI_UNI_PTR * pOldFont;
        char acBuffer[5];
        GUI_RECT rText;
        pOldFont = GUI_SetFont(pObj->pFont);
        _GetTextRect(pObj, &rText, _GetText(pObj, acBuffer));
        GUI_MergeRect(&r, &r, &rText);
        pObj->v = v;
        _GetTextRect(pObj, &rText, _GetText(pObj, acBuffer));
        GUI_MergeRect(&r, &r, &rText);
        GUI_SetFont(pOldFont);
      } else {
        pObj->v = v;
      }
      WM_InvalidateRect(hObj, &r);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       PROGBAR_SetFont
*/
void PROGBAR_SetFont(PROGBAR_Handle hObj, const GUI_FONT GUI_UNI_PTR * pfont) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pObj->pFont = pfont;
    WM_InvalidateWindow(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       PROGBAR_SetBarColor
*/
void PROGBAR_SetBarColor(PROGBAR_Handle hObj, unsigned int Index, GUI_COLOR color) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->BarColor)) {
      pObj->BarColor[Index] = color;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       PROGBAR_SetTextColor
*/
void PROGBAR_SetTextColor(PROGBAR_Handle hObj, unsigned int Index, GUI_COLOR color) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->TextColor)) {
      pObj->TextColor[Index] = color;
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       PROGBAR_SetText
*/
void PROGBAR_SetText(PROGBAR_Handle hObj, const char* s) {
  if (hObj) {
    PROGBAR_Obj* pObj;
    const GUI_FONT GUI_UNI_PTR * pOldFont;
    GUI_RECT r1;
    char acBuffer[5];
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pOldFont = GUI_SetFont(pObj->pFont);
    _GetTextRect(pObj, &r1, _GetText(pObj, acBuffer));
    if (GUI__SetText(&pObj->hpText, s)) {
      GUI_RECT r2;
      _GetTextRect(pObj, &r2, _GetText(pObj, acBuffer));
      GUI_MergeRect(&r1, &r1, &r2);
      WM_InvalidateRect(hObj, &r1);
    }
    GUI_SetFont(pOldFont);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       PROGBAR_SetTextAlign
*/
void PROGBAR_SetTextAlign(PROGBAR_Handle hObj, int Align) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pObj->TextAlign = Align;
    WM_InvalidateWindow(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       PROGBAR_SetTextPos
*/
void PROGBAR_SetTextPos(PROGBAR_Handle hObj, int XOff, int YOff) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    pObj->XOff = XOff;
    pObj->YOff = YOff;
    WM_InvalidateWindow(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       PROGBAR_SetMinMax
*/
void PROGBAR_SetMinMax(PROGBAR_Handle hObj, int Min, int Max) {
  PROGBAR_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = PROGBAR_H2P(hObj);
    if (Max > Min) {
      if ((Max != pObj->Max) || (Min != pObj->Min)) {
        pObj->Min = Min;
        pObj->Max = Max;
        WM_InvalidateWindow(hObj);
      }
    }
    WM_UNLOCK();
  }
}

#else

void WIDGET_Progbar(void) {} /* avoid empty object files */

#endif /* GUI_WINSUPPORT */
