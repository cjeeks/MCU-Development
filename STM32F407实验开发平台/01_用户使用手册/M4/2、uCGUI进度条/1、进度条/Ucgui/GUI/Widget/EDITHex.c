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
File        : EditHex
Purpose     : Edit hexadecimal values
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
#ifndef EDIT_HEX_DIGITONLY
  #define EDIT_HEX_DIGITONLY     0
#endif

/*********************************************************************
*
*             Helpers
*
**********************************************************************
*/
/*********************************************************************
*
*       _HexChar2Int
*/
static int _HexChar2Int(int Char) {
  if ((Char >= '0') && (Char <= '9'))
    return Char - '0';
  Char &= ~0x20;
  if ((Char >= 'A') && (Char <= 'F'))
    return Char - 'A' + 10;
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
  GUI_AddHex(pObj->CurrentValue, pObj->MaxLen, &s);
}

/*********************************************************************
*
*       _EditHex
*/
static void _EditHex(int Nibble, EDIT_Obj* pObj, EDIT_Handle hObj) {
  int Pos = pObj->MaxLen - pObj->CursorPos - 1;   /* Nibble position */
  U32 AndMask = ~(15     << (Pos << 2));
  U32 OrMask  =   Nibble << (Pos << 2);
  I32 Result  = pObj->CurrentValue & AndMask;
  Result     |= OrMask;
  EDIT_SetValue(hObj, Result);
}

/*********************************************************************
*
*       _GetCurrentNibble
*/
#if EDIT_HEX_DIGITONLY
  static U8 _GetCurrentNibble(EDIT_Obj* pObj) {
    int Pos = pObj->MaxLen - pObj->CursorPos - 1;   /* Nibble position */
    U32 AndMask = 0xf << (Pos << 2);
    U8 Nibble = (pObj->CurrentValue & AndMask) >> (Pos << 2);
    return Nibble;
  }
#endif

/*********************************************************************
*
*       _GetNumDigits
*/
static int _GetNumDigits(U32 Value) {
  int Ret;
  for (Ret = 0; Value; Value >>= 4, Ret++);
  return Ret;
}

/*********************************************************************
*
*       _AddPosition
*/
static void _AddPosition(EDIT_Obj* pObj, EDIT_Handle hObj, int Sign) {
  int Pos;
  U32 v;
  v = 1;
  Pos = pObj->MaxLen - pObj->CursorPos - 1;
  while (Pos--) {
    v <<= 4;
  }
  if (Sign < 0)
    v = ~v + 1;
  EDIT_SetValue(hObj, pObj->CurrentValue + v);
}

/*********************************************************************
*
*             Handle input
*
**********************************************************************
*/
/*********************************************************************
*
*       _AddKeyHex
*/
static void _AddKeyHex(EDIT_Handle hObj, int Key) {
  EDIT_Obj * pObj;
  pObj = EDIT_H2P(hObj); /* The GUI needs not to be locked here. This function is called only from EDIT_AddKey which has already locked the GUI */
  if (pObj) {
    switch (Key) {
      #if EDIT_HEX_DIGITONLY
      case GUI_KEY_UP:
        {
          int Nibble = (_GetCurrentNibble(pObj) + 1) & 15;
          _EditHex(Nibble, pObj, hObj);
        }
        break;
      case GUI_KEY_DOWN:
        {
          int Nibble = (_GetCurrentNibble(pObj) + 1) & 15;
          _EditHex(Nibble, pObj, hObj);
        }
        break;
      #else
      case GUI_KEY_UP:
        _AddPosition(pObj, hObj, 1);
        break;
      case GUI_KEY_DOWN:
        _AddPosition(pObj, hObj, -1);
        break;
      #endif
      case GUI_KEY_RIGHT:
        EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
        break;
      case GUI_KEY_LEFT:
        EDIT__SetCursorPos(pObj, pObj->CursorPos - 1);
        break;
      default:
        {
          int Nibble = _HexChar2Int(Key);
          if (Nibble >= 0) {
            _EditHex(Nibble, pObj, hObj);
            EDIT__SetCursorPos(pObj, pObj->CursorPos + 1);
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
*       EDIT_SetHexMode
*/
void EDIT_SetHexMode(EDIT_Handle hEdit, U32 Value, U32 Min, U32 Max) {
  EDIT_Obj* pObj;
  WM_LOCK();
  if (hEdit) {
    int MaxLen;
    pObj = EDIT_H2P(hEdit);
    pObj->pfAddKeyEx = _AddKeyHex;
    pObj->pfUpdateBuffer= _UpdateBuffer;
    pObj->CurrentValue = Value;
    pObj->CursorPos = 0;
    MaxLen = pObj->MaxLen;
    if (MaxLen <= 0 ) {
      MaxLen = _GetNumDigits(Max);
    }
    if (MaxLen > 8) {
      MaxLen = 8;
    }
    if (MaxLen != pObj->MaxLen) {
      EDIT_SetMaxLen(hEdit, MaxLen);
    }
    pObj->Min = Min;
    pObj->Max = Max;
    pObj->EditMode = GUI_EDIT_MODE_OVERWRITE;
    _UpdateBuffer(hEdit);
    WM_Invalidate(hEdit);
  }
  WM_UNLOCK();
}

#else  /* avoid empty object files */

void EditHex_C(void);
void EditHex_C(void){}

#endif /* GUI_WINSUPPORT */
