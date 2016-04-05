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
File        : EditDec
Purpose     : Edit decimal values
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>

#include "EDIT.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT


/*********************************************************************
*
*        Defaults for config switches
*
**********************************************************************
*/
#ifndef EDIT_DEC_DIGITONLY
  #define EDIT_DEC_DIGITONLY     0
#endif


/*********************************************************************
*
*        static Helpers
*
**********************************************************************
*/
/*********************************************************************
*
*       _DecChar2Int
*/
static int _DecChar2Int(int Char) {
  if ((Char >= '0') && (Char <= '9'))
    return Char - '0';
  return -1;
}

/*********************************************************************
*
*       _UpdateBuffer
*/
static void _UpdateBuffer(EDIT_Handle hObj) {
  char * s;
  EDIT_Obj * pObj;
  pObj = EDIT_H2P(hObj); /* The GUI needs not to be locked here. This function is called only from EDIT_AddKey which has already locked the GUI */
  s = (char*) GUI_ALLOC_h2p(pObj->hpText);
  if (pObj->Flags == GUI_EDIT_SIGNED) {
    I32 Result = GUI_AddSign(pObj->CurrentValue, &s);
    GUI_AddDecShift(Result, pObj->MaxLen - 1, pObj->NumDecs, &s);
  } else {
    GUI_AddDecShift(pObj->CurrentValue, pObj->MaxLen, pObj->NumDecs, &s);
  }
}

/*********************************************************************
*
*       _EditDec
*/
static void _EditDec(int Digit, EDIT_Obj* pObj, EDIT_Handle hObj) {
  I32 Result = 0;
  int i, Pos = 0;
  char * s = (char*) GUI_ALLOC_h2p(pObj->hpText);
  for (i = 0; i < pObj->MaxLen; i++) {
    int Index = pObj->MaxLen - i - 1;
    if (Index == pObj->CursorPos) {
      Result += GUI_Pow10[Pos++] * Digit;
    } else {
      char c = *(s + Index);
      int Value = _DecChar2Int(c);
      if (Value >= 0) {
        Result += GUI_Pow10[Pos++] * Value;
      }
      if (c == '-') {
        Result *= -1;
      }
    }
  }
  EDIT_SetValue(hObj, Result);
}

/*********************************************************************
*
*       EDIT_DEC_DIGITONLY
*/
#if EDIT_DEC_DIGITONLY
static int GetCurrentDigit(EDIT_Obj* pObj) {
  return _DecChar2Int(EDIT__GetCurrentChar(pObj));
}
#endif

/*********************************************************************
*
*       _MakePositive
*/
static void _MakePositive(EDIT_Obj* pObj, EDIT_Handle hObj) {
  if ((I32)pObj->CurrentValue < 0) {
    EDIT_SetValue(hObj, (I32)pObj->CurrentValue * -1);
  }
}

/*********************************************************************
*
*       _MakeNegative
*/
static void _MakeNegative(EDIT_Obj* pObj, EDIT_Handle hObj) {
  if ((I32)pObj->CurrentValue > 0) {
    EDIT_SetValue(hObj, (I32)pObj->CurrentValue * -1);
  }
}

/*********************************************************************
*
*       _SwapSign
*/
static void _SwapSign(EDIT_Obj* pObj, EDIT_Handle hObj) {
  if ((I32)pObj->CurrentValue > 0)
    _MakeNegative(pObj, hObj);
  else
    _MakePositive(pObj, hObj);
}

/*********************************************************************
*
*       _IncrementCursor
*/
static void _IncrementCursor(EDIT_Obj* pObj) {
  EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
  if (EDIT__GetCurrentChar(pObj) == '.') {
    if (pObj->CursorPos < (pObj->MaxLen - 1)) {
      EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
    } else {
      EDIT__SetCursorPos(pObj, pObj->CursorPos - 1);
    }
  }
}

/*********************************************************************
*
*       _AddPosition
*/
#if !EDIT_DEC_DIGITONLY
static void _AddPosition(EDIT_Obj* pObj, EDIT_Handle hObj, int Sign) {
  int Pos;
  I32 v;
  v = Sign;
  Pos = pObj->MaxLen - pObj->CursorPos-1;
  if (pObj->NumDecs && (Pos > pObj->NumDecs)) {
    Pos--;
  }
  while (Pos--) {
    v *= 10;
  }
  EDIT_SetValue(hObj, (I32)pObj->CurrentValue + v);
}
#endif

/*********************************************************************
*
*             Handle input
*
**********************************************************************
*/
/*********************************************************************
*
*       _AddKeyDec
*/
static void _AddKeyDec(EDIT_Handle hObj, int Key) {
  char c;
  EDIT_Obj * pObj;
  pObj = EDIT_H2P(hObj); /* The GUI needs not to be locked here. This function is called only from EDIT_AddKey which has already locked the GUI */
  if (pObj) {
    switch (Key) {
      case '+':
        if (pObj->CursorPos == 0) {
          _MakePositive(pObj, hObj);
          _IncrementCursor(pObj);
        }
        break;
      case '-':
        if (pObj->CursorPos == 0) {
          _MakeNegative(pObj, hObj);
          _IncrementCursor(pObj);
        }
        break;
      #if EDIT_DEC_DIGITONLY
        case GUI_KEY_UP:
          c = EDIT__GetCurrentChar(pObj);
          if ((c == '-') || (c == '+')) {
            _SwapSign(pObj, hObj);
          } else {
            int Digit = GetCurrentDigit(pObj) + 1;
            if (Digit > 9)
              Digit = 0;
            _EditDec(Digit, pObj, hObj);
          }
          break;
        case GUI_KEY_DOWN:
          c = EDIT__GetCurrentChar(pObj);
          if ((c == '-') || (c == '+')) {
            _SwapSign(pObj, hObj);
          } else {
            int Digit = GetCurrentDigit(pObj) - 1;
            if (Digit < 0)
              Digit = 9;
            _EditDec(Digit, pObj, hObj);
          }
          break;
      #else
        case GUI_KEY_UP:
          c = EDIT__GetCurrentChar(pObj);
          if ((c == '-') || (c == '+')) {
            _SwapSign(pObj, hObj);
          } else {
            _AddPosition(pObj, hObj, 1);
          }
          break;
        case GUI_KEY_DOWN:
          c = EDIT__GetCurrentChar(pObj);
          if ((c == '-') || (c == '+')) {
            _SwapSign(pObj, hObj);
          } else {
            _AddPosition(pObj, hObj, -1);
          }
          break;
      #endif
      case GUI_KEY_RIGHT:
        _IncrementCursor(pObj);
        break;
      case GUI_KEY_LEFT:
        EDIT__SetCursorPos(pObj, pObj->CursorPos - 1);
        if (EDIT__GetCurrentChar(pObj) == '.') {
          if (pObj->CursorPos > 0) {
            EDIT__SetCursorPos(pObj, pObj->CursorPos - 1);
          } else {
            EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
          }
        }
        break;
      default:
        {
          char c = EDIT__GetCurrentChar(pObj);
          if ((c != '-') && (c != '+')) {
            int Digit = _DecChar2Int(Key);
            if (Digit >= 0) {
              _EditDec(Digit, pObj, hObj);
              _IncrementCursor(pObj);
            }
          }
        }
        break;
    }
  }
  _UpdateBuffer(hObj);
}

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_SetDecMode
*/
void EDIT_SetDecMode(EDIT_Handle hEdit, I32 Value, I32 Min, I32 Max, int Shift, U8 Flags) {
  EDIT_Obj* pObj;
  WM_LOCK();
  if (hEdit) {
    pObj = EDIT_H2P(hEdit);
    pObj->pfAddKeyEx    = _AddKeyDec;
    pObj->pfUpdateBuffer= _UpdateBuffer;
    pObj->CurrentValue  = Value;
    pObj->CursorPos     = 0;
    pObj->Min           = Min;
    pObj->Max           = Max;
    pObj->NumDecs       = Shift;
    pObj->Flags         = Flags;
    pObj->EditMode      = GUI_EDIT_MODE_OVERWRITE;
    _UpdateBuffer(hEdit);
    if (EDIT__GetCurrentChar(pObj) == '.') {
      EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
    }
    WM_Invalidate(hEdit);
  }
  WM_UNLOCK();
}

#else  /* avoid empty object files */

void EditDec_C(void);
void EditDec_C(void){}

#endif /* GUI_WINSUPPORT */
