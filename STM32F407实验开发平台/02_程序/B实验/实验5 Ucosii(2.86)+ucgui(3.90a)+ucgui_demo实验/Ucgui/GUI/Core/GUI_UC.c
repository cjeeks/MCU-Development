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
File        : GUI_UC_EncodeUTF8.c
Purpose     : Encoding routines
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_UC_GetCharSize
*/
int GUI_UC_GetCharSize(const char GUI_UNI_PTR * s) {
  int r;
  GUI_LOCK();
  r =  GUI_Context.pUC_API->pfGetCharSize(s);
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_UC_GetCharCode
*/
U16 GUI_UC_GetCharCode(const char GUI_UNI_PTR * s) {
  U16 r;
  GUI_LOCK();
  r =  GUI_Context.pUC_API->pfGetCharCode(s);
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_UC_Encode
*/
int GUI_UC_Encode(char* s, U16 Char) {
  #if GUI_COMPILER_SUPPORTS_FP
    int r;
    GUI_LOCK();
    r = GUI_Context.pUC_API->pfEncode(s, Char);
    GUI_UNLOCK();
    return r;
  #else
    GUI_USE_PARA(s);
    GUI_USE_PARA(Char);
    return 0;
  #endif
}

/*********************************************************************
*
*       GUI_UC__CalcSizeOfChar
*/
int GUI_UC__CalcSizeOfChar(U16 Char) {
  return GUI_Context.pUC_API->pfCalcSizeOfChar(Char);
}

/*********************************************************************
*
*       GUI_UC__GetCharCodeInc
*/
U16 GUI_UC__GetCharCodeInc(const char GUI_UNI_PTR ** ps) {
  const char GUI_UNI_PTR * s;
  U16 r;
  s   = *ps;
  r   = GUI_UC__GetCharCode(s);
  s  += GUI_UC__GetCharSize(s);
  *ps = s;
  return r;
}

/*********************************************************************
*
*       GUI_UC__NumChars2NumBytes
*/
int GUI_UC__NumChars2NumBytes(const char GUI_UNI_PTR * s, int NumChars) {
  int CharSize, NumBytes = 0;
  while (NumChars--) {
    CharSize = GUI_UC__GetCharSize(s);
    s += CharSize;    
    NumBytes += CharSize;
  }
  return NumBytes;
}

/*********************************************************************
*
*       GUI_UC__NumBytes2NumChars
*/
int GUI_UC__NumBytes2NumChars(const char GUI_UNI_PTR * s, int NumBytes) {
  int CharSize, Chars = 0, Bytes = 0;
  while (NumBytes > Bytes) {
    CharSize = GUI_UC__GetCharSize(s + Bytes);
    Bytes += CharSize;
    Chars++;
  }
  return Chars;
}

/*************************** End of file ****************************/
