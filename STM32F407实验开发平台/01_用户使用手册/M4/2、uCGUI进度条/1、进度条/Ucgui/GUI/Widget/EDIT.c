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
File        : EDIT.c
Purpose     : Implementation of edit widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#define EDIT_C       /* Required to generate intermodule data */

#include "EDIT.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default fonts */
#ifndef EDIT_FONT_DEFAULT
  #define EDIT_FONT_DEFAULT &GUI_Font13_1
#endif

#ifndef EDIT_ALIGN_DEFAULT
  #define EDIT_ALIGN_DEFAULT GUI_TA_LEFT | GUI_TA_VCENTER
#endif

/* Define colors */
#ifndef EDIT_BKCOLOR0_DEFAULT
  #define EDIT_BKCOLOR0_DEFAULT 0xC0C0C0
#endif

#ifndef EDIT_BKCOLOR1_DEFAULT
  #define EDIT_BKCOLOR1_DEFAULT GUI_WHITE
#endif

#ifndef EDIT_TEXTCOLOR0_DEFAULT
  #define EDIT_TEXTCOLOR0_DEFAULT GUI_BLACK
#endif

#ifndef EDIT_TEXTCOLOR1_DEFAULT
  #define EDIT_TEXTCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef EDIT_BORDER_DEFAULT
  #define EDIT_BORDER_DEFAULT 1
#endif

#ifndef EDIT_XOFF
  #define EDIT_XOFF 1
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
EDIT_PROPS EDIT__DefaultProps = {
  EDIT_ALIGN_DEFAULT,
  EDIT_BORDER_DEFAULT,
  EDIT_FONT_DEFAULT,
  EDIT_TEXTCOLOR0_DEFAULT,
  EDIT_TEXTCOLOR1_DEFAULT,
  EDIT_BKCOLOR0_DEFAULT,
  EDIT_BKCOLOR1_DEFAULT
};

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define OBJECT_ID 0x4569   /* Magic nubmer, should be unique if possible */
  #define INIT_ID(p)   p->DebugId = OBJECT_ID
  #define DEINIT_ID(p) p->DebugId = 0
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
/*********************************************************************
*
*       EDIT_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
EDIT_Obj* EDIT_h2p(EDIT_Handle h) {
  EDIT_Obj* p = (EDIT_Obj*)GUI_ALLOC_h2p(h);
  if (p) {
	  //houhh 20061022...
    if (p->DebugId != OBJECT_ID) {
      GUI_DEBUG_ERROROUT("EDIT.C: Wrong handle type or Object not init'ed");
      return 0;
    }
  }
  return p;
}
#endif

///////////houhh 20061018...
static GUI_TIMER_HANDLE Timer1 = 0;	//houhh 20061018...
static void _Paint(EDIT_Obj* pObj, EDIT_Handle hObj) ;

void ShowCurrsor(GUI_TIMER_MESSAGE* TimeMsg)
{
	EDIT_Handle hObj = (EDIT_Handle) TimeMsg->Context;
	EDIT_Obj*   pObj = (EDIT_Obj*) GUI_ALLOC_h2p(hObj);

    WM_Obj* pWin = WM_H2P(hObj);
	GUI_DEBUG_LOG("EDIT: _Callback(WM_PAINT)\n");
    WM_SelectWindow(hObj);
	_Paint(pObj, hObj);
	pObj->CurrsorShow++;
	GUI_TIMER_Restart(Timer1);

}
///////

/*********************************************************************
*
*       _Paint
*/
static void _Paint(EDIT_Obj* pObj, EDIT_Handle hObj) {
  GUI_RECT rFillRect, rInside, r, rText, rInvert;
  const char GUI_UNI_PTR * pText = NULL;
  int IsEnabled, CursorWidth;
  IsEnabled = WM__IsEnabled(hObj);
  /* Set colors and font */
  LCD_SetBkColor(pObj->Props.aBkColor[IsEnabled]);
  LCD_SetColor(pObj->Props.aTextColor[0]);
  GUI_SetFont(pObj->Props.pFont);
  /* Calculate size */
  WM__GetClientRectWin(&pObj->Widget.Win, &r);
  WIDGET__GetInsideRect(&pObj->Widget, &rFillRect);
  if (pObj->hpText) {
    pText = (const char*) GUI_ALLOC_h2p(pObj->hpText);
  }
  rInside = rFillRect;
  rInside.x0 += pObj->Props.Border + EDIT_XOFF;
  rInside.x1 -= pObj->Props.Border + EDIT_XOFF;
  GUI__CalcTextRect(pText, &rInside, &rText, pObj->Props.Align);
  /* Calculate position and size of cursor */
  if (pObj->Widget.State & WIDGET_STATE_FOCUS) {
    const char GUI_UNI_PTR * p = pText;
    CursorWidth = ((pObj->XSizeCursor > 0) ? (pObj->XSizeCursor) : (1));
    if (pText) {
      U16 Char;
      int i;
	//  pObj->SelSize = 3;	//houhh 20061023...
      if ((pObj->EditMode != GUI_EDIT_MODE_INSERT) || (pObj->SelSize)) {
        int NumChars, CursorOffset;
        NumChars = GUI__GetNumChars(pText);
        if (pObj->CursorPos < NumChars) {
          if (pObj->SelSize) {
            CursorWidth = 0;
            for (i = pObj->CursorPos; i < (int)(pObj->CursorPos + pObj->SelSize); i++) {
              CursorOffset = GUI_UC__NumChars2NumBytes(pText, i);
              Char         = GUI_UC_GetCharCode      (pText + CursorOffset);
              CursorWidth += GUI_GetCharDistX        (Char);
            }
            if (!CursorWidth) {
              CursorWidth = 1;
            }
          } else {
            CursorOffset = GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
            Char = GUI_UC_GetCharCode(pText + CursorOffset);
            CursorWidth = GUI_GetCharDistX(Char);
          }
        }
      }
      rInvert = rText;
      for (i = 0; i != pObj->CursorPos; i++) {
        Char = GUI_UC__GetCharCodeInc(&p);
        rInvert.x0 += GUI_GetCharDistX(Char);
      }
    }
  }
  /* WM loop */
  WM_ITERATE_START(NULL) {
    /* Set clipping rectangle */
    WM_SetUserClipRect(&rFillRect);
    /* Display text */
    WIDGET__FillStringInRect(pText, &rFillRect, &rInside, &rText);
    /* Display cursor if needed */
    if (pObj->Widget.State & WIDGET_STATE_FOCUS) {
		///////////////houhh 20061020...
		//  static GUI_TIMER_HANDLE Timer1 = NULL;	//houhh 20061018...
		if(!Timer1){
			  Timer1 = GUI_TIMER_Create((GUI_TIMER_CALLBACK*)ShowCurrsor, 1000*2, 0, 0);	//houhh 20061018...
			  GUI_TIMER_SetTime(Timer1, 1000*2);
			  GUI_TIMER_SetPeriod(Timer1, 500);
		  }
		if(Timer1) GUI_TIMER_Context(Timer1, hObj);
		if(pObj->CurrsorShow%2) //houhh 20061022...
		  GUI_InvertRect(rInvert.x0, rInvert.y0, rInvert.x0 + CursorWidth - 1, rInvert.y1);
		/////////////
		GUI_InvertRect(rInvert.x0, rInvert.y0, rInvert.x0 + CursorWidth - 1, rInvert.y1);
    }
    WM_SetUserClipRect(NULL);
    /* Draw the 3D effect (if configured) */
    WIDGET__EFFECT_DrawDown(&pObj->Widget);
  } WM_ITERATE_END();
}

/*********************************************************************
*
*       _Delete
*/
static void _Delete(EDIT_Obj* pObj) {
  GUI_ALLOC_FreePtr(&pObj->hpText);
}

/*********************************************************************
*
*       EDIT_SetCursorAtPixel
*/
void EDIT_SetCursorAtPixel(EDIT_Handle hObj, int xPos) {
  if (hObj) {
    EDIT_Obj* pObj;
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    if (pObj->hpText) {    
      const GUI_FONT GUI_UNI_PTR *pOldFont;
      int xSize, TextWidth, NumChars;
      const char GUI_UNI_PTR * pText;
      pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
      pOldFont = GUI_SetFont(pObj->Props.pFont);
      xSize = WM_GetWindowSizeX(hObj);
      TextWidth = GUI_GetStringDistX(pText);
      switch (pObj->Props.Align & GUI_TA_HORIZONTAL) {
      case GUI_TA_HCENTER:
        xPos -= (xSize - TextWidth + 1) / 2;
        break;
      case GUI_TA_RIGHT:
        xPos -= xSize - TextWidth - (pObj->Props.Border + EDIT_XOFF);
        break;
      default:
        xPos -= (pObj->Props.Border + EDIT_XOFF) + pObj->Widget.pEffect->EffectSize;
      }
      NumChars = GUI__GetNumChars(pText);
      if (xPos < 0) {
        EDIT__SetCursorPos(pObj, 0);
      } else if (xPos > TextWidth) {
        EDIT__SetCursorPos(pObj, NumChars);
      } else {
        int i, x, xLenChar;
        U16 Char;
        for (i = 0, x = 0; (i < NumChars) && (x < xPos); i++) {
          Char     = GUI_UC__GetCharCodeInc(&pText);
          xLenChar = GUI_GetCharDistX(Char);
          if (xPos < (x + xLenChar))
            break;
          x += xLenChar;
        }
        EDIT__SetCursorPos(pObj, i);
      }
      GUI_SetFont(pOldFont);
      EDIT_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       _IncrementBuffer
*
* Increments the buffer size by AddBytes.
*/
static int _IncrementBuffer(EDIT_Obj* pObj, unsigned AddBytes) {
  WM_HMEM hNew;
  int NewSize;
  NewSize = pObj->BufferSize + AddBytes;
  hNew    = GUI_ALLOC_Realloc(pObj->hpText, NewSize);
  if (hNew) {
    if (!(pObj->hpText)) {
      char* pText;
      pText  = (char*) GUI_ALLOC_h2p(hNew);
      *pText = 0;
    }
    pObj->BufferSize = NewSize;
    pObj->hpText     = hNew;
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _IsSpaceInBuffer
*
* Checks the available space in the buffer. If there is not enough
* space left this function attempts to get more.
*
* Returns:
*  1 = requested space is available
*  0 = failed to get enough space
*/
static int _IsSpaceInBuffer(EDIT_Obj* pObj, int BytesNeeded) {
  int NumBytes = 0;
  if (pObj->hpText) {
    NumBytes = strlen((char*)GUI_ALLOC_h2p(pObj->hpText));
  }
  BytesNeeded = (BytesNeeded + NumBytes + 1) - pObj->BufferSize;
  if (BytesNeeded > 0) {
    if (!_IncrementBuffer(pObj, BytesNeeded + EDIT_REALLOC_SIZE)) {
      return 0;
    }
  }
  return 1;
}

/*********************************************************************
*
*       _IsCharsAvailable
*
* Checks weither the maximum number of characters is reached or not.
*
* Returns:
*  1 = requested number of chars is available
*  0 = maximum number of chars have reached
*/
static int _IsCharsAvailable(EDIT_Obj* pObj, int CharsNeeded) {
  if ((CharsNeeded > 0) && (pObj->MaxLen > 0)) {
    int NumChars = 0;
    if (pObj->hpText) {
      NumChars = GUI__GetNumChars((char*)GUI_ALLOC_h2p(pObj->hpText));
    }
    if ((CharsNeeded + NumChars) > pObj->MaxLen) {
      return 0;
    }
  }
  return 1;
}

/*********************************************************************
*
*       _DeleteChar
*
* Deletes a character at the current cursor position and moves
* all bytes after the cursor position.
*/
static void _DeleteChar(EDIT_Handle hObj, EDIT_Obj* pObj) {
  if (pObj->hpText) {
    unsigned CursorOffset;
    char* pText;
    pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
    CursorOffset = GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
    if (CursorOffset < strlen(pText)) {
      int NumBytes;
      pText += CursorOffset;
      NumBytes = GUI_UC_GetCharSize(pText);
      strcpy(pText, pText + NumBytes);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
  }
}

/*********************************************************************
*
*       _InsertChar
*
* Create space at the current cursor position and inserts a character.
*/
static int _InsertChar(EDIT_Handle hObj, EDIT_Obj* pObj, U16 Char) {
  if (_IsCharsAvailable(pObj, 1)) {
    int BytesNeeded;
    BytesNeeded = GUI_UC__CalcSizeOfChar(Char);
    if (_IsSpaceInBuffer(pObj, BytesNeeded)) {
      int CursorOffset;
      char* pText;
      pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
      CursorOffset = GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
      pText += CursorOffset;
      memmove(pText + BytesNeeded, pText, strlen(pText) + 1);
      GUI_UC_Encode(pText, Char);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*       EDIT__GetCurrentChar
*/
U16 EDIT__GetCurrentChar(EDIT_Obj* pObj) {
  U16 Char = 0;
  if (pObj->hpText) {
    const char* pText;
    pText  = (const char*) GUI_ALLOC_h2p(pObj->hpText);
    pText += GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
    Char   = GUI_UC_GetCharCode(pText);
  }
  return Char;
}

/*********************************************************************
*
*       EDIT__SetCursorPos
*
* Sets a new cursor position.
*/
void EDIT__SetCursorPos(EDIT_Obj* pObj, int CursorPos) {
  if (pObj->hpText) {
    char* pText;
    int NumChars, Offset;
    pText    = (char*) GUI_ALLOC_h2p(pObj->hpText);
    NumChars = GUI__GetNumChars(pText);
    Offset   = (pObj->EditMode == GUI_EDIT_MODE_INSERT) ? 0 : 1;
    if (CursorPos < 0) {
      CursorPos = 0;
    }
    if (CursorPos > NumChars) {
      CursorPos = NumChars;
    }
    if (CursorPos > (pObj->MaxLen - Offset)) {
      CursorPos = pObj->MaxLen - Offset;
    }
    if (pObj->CursorPos != CursorPos) {
      pObj->CursorPos = CursorPos;
    }
    pObj->SelSize = 0;
  }
}

/*********************************************************************
*
*       _OnTouch
*/
static void _OnTouch(EDIT_Handle hObj, EDIT_Obj* pObj, WM_MESSAGE*pMsg) {
  const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
  GUI_USE_PARA(pObj);
  if (pMsg->Data.p) {  /* Something happened in our area (pressed or released) */
	  static int StartPress = 0;	//houhh 20061023...
    if (pState->Pressed) {
      GUI_DEBUG_LOG1("EDIT__Callback(WM_TOUCH, Pressed, Handle %d)\n",1);
      EDIT_SetCursorAtPixel(hObj, pState->x);
	  StartPress = pObj->CursorPos;	//houhh 20061023...
    } else {
      GUI_DEBUG_LOG1("EDIT__Callback(WM_TOUCH, Released, Handle %d)\n",1);
    }
  } else {
    GUI_DEBUG_LOG1("_EDIT_Callback(WM_TOUCH, Moved out, Handle %d)\n",1);
  }
}

/*********************************************************************
*
*       EDIT__Callback
*/
static void EDIT__Callback (WM_MESSAGE * pMsg) {
  int IsEnabled;
  EDIT_Handle hObj = (EDIT_Handle) pMsg->hWin;
  EDIT_Obj*   pObj = (EDIT_Obj*) GUI_ALLOC_h2p(hObj);
  IsEnabled = WM__IsEnabled(hObj);
  /* Let widget handle the standard messages */
  if (WIDGET_HandleActive(hObj, pMsg) == 0) {
    return;
  }
  switch (pMsg->MsgId) {
  case WM_TOUCH:
    _OnTouch(hObj, pObj, pMsg);
    break;
  case WM_PAINT:
    GUI_DEBUG_LOG("EDIT: _Callback(WM_PAINT)\n");
    _Paint(pObj, hObj);
    return;
  case WM_DELETE:
    GUI_DEBUG_LOG("EDIT: _Callback(WM_DELETE)\n");
    _Delete(pObj);
    break;       /* No return here ... WM_DefaultProc needs to be called */
  case WM_KEY:
    if (IsEnabled) {
      if ( ((const WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt >0) {
        int Key = ((const WM_KEY_INFO*)(pMsg->Data.p))->Key;
        switch (Key) {
          case GUI_KEY_TAB:
            break;                    /* Send to parent by not doing anything */
          default:
            EDIT_AddKey(hObj, Key);
            return;
        }
      }
    }
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
*       EDIT_CreateEx
*/
EDIT_Handle EDIT_CreateEx(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int WinFlags, int ExFlags,
                          int Id, int MaxLen)
{
  EDIT_Handle hObj;
  GUI_USE_PARA(ExFlags);
  /* Alloc memory for obj */
  WinFlags |= WM_CF_LATE_CLIP;    /* Always use late clipping since widget is optimized for it. */
  hObj = WM_CreateWindowAsChild(x0, y0, xsize, ysize, hParent, WM_CF_SHOW | WinFlags, EDIT__Callback,
                                sizeof(EDIT_Obj) - sizeof(WM_Obj));
  if (hObj) {
    EDIT_Obj* pObj;
    WM_LOCK();
    pObj = (EDIT_Obj*)GUI_ALLOC_h2p(hObj);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
    /* init member variables */
    INIT_ID(pObj);
    pObj->Props         = EDIT__DefaultProps;
    pObj->XSizeCursor   = 1;
    pObj->MaxLen        = (MaxLen == 0) ? 8 : MaxLen;
    pObj->BufferSize    = 0;
    pObj->hpText        = 0;
    if (_IncrementBuffer(pObj, pObj->MaxLen + 1) == 0) {
      GUI_DEBUG_ERROROUT("EDIT_Create failed to alloc buffer");
      EDIT_Delete(hObj);
      hObj = 0;
    }
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
*       EDIT_AddKey
*/
void EDIT_AddKey(EDIT_Handle hObj, int Key) {
  if (hObj) {
    EDIT_Obj* pObj;
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    if (pObj) {
      if (pObj->pfAddKeyEx) {
        pObj->pfAddKeyEx(hObj, Key);
      } else {
        switch (Key) {
        case GUI_KEY_UP:
          if (pObj->hpText) {
            char* pText;
            U16 Char;
            pText  = (char*) GUI_ALLOC_h2p(pObj->hpText);
            pText += GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
            Char   = GUI_UC_GetCharCode(pText);
            if (Char < 0x7f) {  
              *pText = Char + 1;
              WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
            }
          }
          break;
        case GUI_KEY_DOWN:
          if (pObj->hpText) {
            char* pText;
            U16 Char;
            pText  = (char*) GUI_ALLOC_h2p(pObj->hpText);
            pText += GUI_UC__NumChars2NumBytes(pText, pObj->CursorPos);
            Char   = GUI_UC_GetCharCode(pText);
            if (Char > 0x20) {  
              *pText = Char - 1;
              WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
            }
          }
          break;
        case GUI_KEY_RIGHT:
          EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
          break;
        case GUI_KEY_LEFT:
          EDIT__SetCursorPos(pObj, pObj->CursorPos - 1);
          break;
        case GUI_KEY_BACKSPACE:
          EDIT__SetCursorPos(pObj, pObj->CursorPos - 1);
          _DeleteChar(hObj, pObj);
          break;
        case GUI_KEY_DELETE:
          _DeleteChar(hObj, pObj);
          break;
        case GUI_KEY_INSERT:
          if (pObj->EditMode == GUI_EDIT_MODE_OVERWRITE) {
            pObj->EditMode = GUI_EDIT_MODE_INSERT;
          } else {
            pObj->EditMode = GUI_EDIT_MODE_OVERWRITE;
            EDIT__SetCursorPos(pObj, pObj->CursorPos);
          }
          break;
        case GUI_KEY_ENTER:
        case GUI_KEY_ESCAPE:
          break;
        default:
          if (Key >= 0x20) {
            if (pObj->EditMode != GUI_EDIT_MODE_INSERT) {
              _DeleteChar(hObj, pObj);
            }
            if (_InsertChar(hObj, pObj, Key)) {
              EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
            }
          }
        }
      }
      EDIT_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       EDIT_SetFont
*/
void EDIT_SetFont(EDIT_Handle hObj, const GUI_FONT GUI_UNI_PTR * pfont) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    pObj->Props.pFont = pfont;
    EDIT_Invalidate(hObj);
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       EDIT_SetBkColor
*/
void EDIT_SetBkColor(EDIT_Handle hObj, unsigned int Index, GUI_COLOR color) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    if (Index < GUI_COUNTOF(pObj->Props.aBkColor)) {
      pObj->Props.aBkColor[Index] = color;
      EDIT_Invalidate(hObj);
    }
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       EDIT_SetTextColor
*/
void EDIT_SetTextColor(EDIT_Handle hObj, unsigned int Index, GUI_COLOR color) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    if (Index < GUI_COUNTOF(pObj->Props.aTextColor)) {
      pObj->Props.aTextColor[Index] = color;
      EDIT_Invalidate(hObj);
    }
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       EDIT_SetText
*/
void EDIT_SetText(EDIT_Handle hObj, const char* s) {
  if (hObj) {
    EDIT_Obj* pObj;
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    if (s) {
      int NumBytesNew, NumBytesOld = 0;
      int NumCharsNew;
      if (pObj->hpText) {
        char* pText;
        pText       = (char*) GUI_ALLOC_h2p(pObj->hpText);
        NumBytesOld = strlen(pText) + 1;
      }
      NumCharsNew = GUI__GetNumChars(s);
      if (NumCharsNew > pObj->MaxLen) {
        NumCharsNew = pObj->MaxLen;
      }
      NumBytesNew = GUI_UC__NumChars2NumBytes(s, NumCharsNew) + 1;
      if (_IsSpaceInBuffer(pObj, NumBytesNew - NumBytesOld)) {
        char* pText;
        pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
        memcpy(pText, s, NumBytesNew);
        pObj->CursorPos = NumBytesNew - 1;
        if (pObj->CursorPos == pObj->MaxLen) {
          if (pObj->EditMode == GUI_EDIT_MODE_OVERWRITE) {
            pObj->CursorPos--;
          }
        }
      }
    } else {
      GUI_ALLOC_FreePtr(&pObj->hpText);
      pObj->BufferSize = 0;
      pObj->CursorPos  = 0;
    }
    EDIT_Invalidate(hObj);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       EDIT_GetText
*/
void EDIT_GetText(EDIT_Handle hObj, char* sDest, int MaxLen) {
  if (sDest) {
    *sDest = 0;
    if (hObj) {
      EDIT_Obj* pObj;
      WM_LOCK();
      pObj = EDIT_H2P(hObj);
      if (pObj->hpText) {
        char* pText;
        int NumChars, NumBytes;
        pText = (char*) GUI_ALLOC_h2p(pObj->hpText);
        NumChars = GUI__GetNumChars(pText);
        if (NumChars > MaxLen) {
          NumChars = MaxLen;
        }
        NumBytes = GUI_UC__NumChars2NumBytes(pText, NumChars);
        memcpy(sDest, pText, NumBytes);
        *(sDest + NumBytes) = 0;
      }
      WM_UNLOCK();
    }
  }
}

/*********************************************************************
*
*       EDIT_GetValue
*/
I32  EDIT_GetValue(EDIT_Handle hObj) {
  EDIT_Obj* pObj;
  I32 r = 0;
  if (hObj) {
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    r = pObj->CurrentValue;
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       EDIT_SetValue
*/
void EDIT_SetValue(EDIT_Handle hObj, I32 Value) {
  EDIT_Obj* pObj;
  if (hObj) {
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    /* Put in min/max range */
    if (Value < pObj->Min) {
      Value = pObj->Min;
    }
    if (Value > pObj->Max) {
      Value = pObj->Max;
    }
    if (pObj->CurrentValue != (U32)Value) {
      pObj->CurrentValue = Value;
      if (pObj->pfUpdateBuffer) {
        pObj->pfUpdateBuffer(hObj);
      }
      WM_InvalidateWindow(hObj);
      WM_NotifyParent(hObj, WM_NOTIFICATION_VALUE_CHANGED);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       EDIT_SetMaxLen
*/
void EDIT_SetMaxLen(EDIT_Handle  hObj, int MaxLen) {
  if (hObj) {
    EDIT_Obj* pObj;
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    if (MaxLen != pObj->MaxLen) {
      if (MaxLen < pObj->MaxLen) {
        if (pObj->hpText) {
          char* pText;
          int   NumChars;
          pText    = (char*) GUI_ALLOC_h2p(pObj->hpText);
          NumChars = GUI__GetNumChars(pText);
          if (NumChars > MaxLen) {
            int NumBytes;
            NumBytes = GUI_UC__NumChars2NumBytes(pText, MaxLen);
            *(pText + NumBytes) = 0;
          }
        }
      }
      _IncrementBuffer(pObj, MaxLen - pObj->BufferSize + 1);
      pObj->MaxLen = MaxLen;
      EDIT_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       EDIT_SetTextAlign
*/
void EDIT_SetTextAlign(EDIT_Handle hObj, int Align) {
  EDIT_Obj* pObj;
  if (hObj == 0)
    return;
  WM_LOCK();
  pObj = EDIT_H2P(hObj);
  if (pObj) {
    pObj->Props.Align = Align;
    EDIT_Invalidate(hObj);
  }
  WM_UNLOCK();
}

#else  /* avoid empty object files */

void Edit_C(void) {}

#endif
