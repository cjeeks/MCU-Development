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
File        : GUIEncSJ.C
Purpose     : Implementation of Shift JIS decoding
----------------------------------------------------------------------
Version-Date---Author-Explanation
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       DB2SJIS
*/
static U16 DB2SJIS(U8 Byte0, U8 Byte1) {
  return Byte1 | (((U16)Byte0)<<8);
}

/*********************************************************************
*
*       _GetLineDistX_SJIS
*/
static int _GetLineDistX_SJIS(const char GUI_UNI_PTR *s, int Len) {
  int Dist =0;
  if (s) {
    U8 c0;
    while (((c0=*(const U8*)s) !=0) && Len >=0) {
      s++; Len--;
      if (c0 > 127) {
        U8  c1 = *(const U8*)s++;
        Len--;
        Dist += GUI_GetCharDistX(DB2SJIS(c0, c1));
      } else {
        Dist += GUI_GetCharDistX(c0);
      }
    }
  }
  return Dist;
}

/*********************************************************************
*
*       _GetLineLen_SJIS
* Purpose:
*   Returns the number of characters in a string.
*
* NOTE:
*   The return value can be used as offset into the
*   string, which means that double characters count double
*/
static int _GetLineLen_SJIS(const char GUI_UNI_PTR *s, int MaxLen) {
  int Len =0;
  U8 c0;
  while (((c0=*(const U8*)s) !=0) && Len < MaxLen) {
    s++;
    if (c0 > 127) {
      Len++; s++;
    } else {
      switch (c0) {
      case '\n': return Len;
      }
    }
    Len++;
  }
  return Len;
}

/*********************************************************************
*
*       _DispLine_SJIS
*/
static void _DispLine_SJIS(const char GUI_UNI_PTR *s, int Len) {
  U8 c0;
  while (--Len >=0) {
    c0=*(const U8*)s++;
    if (c0 > 127) {
      U8  c1 = *(const U8*)s++;
      Len--;
      GL_DispChar (DB2SJIS(c0, c1));
    } else {
      GL_DispChar(c0);
    }
  }
}

/*********************************************************************
*
*       GUI_ENC_APIList_SJIS, API list
*/
const tGUI_ENC_APIList GUI_ENC_APIList_SJIS = {
  _GetLineDistX_SJIS,
  _GetLineLen_SJIS,
  _DispLine_SJIS
};

/*************************** End of file ****************************/
