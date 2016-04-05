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
File        : GUI_EditFloat.c
Purpose     : Widget, add. module
----------------------------------------------------------------------
*/

#include "EDIT.h"
#include "GUI_Protected.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_EditFloat
*/
float GUI_EditFloat(float Value, float Min, float Max, int Len, int xsize, int Shift, U8 Flags) {
  float Ret;
  int Key, x, y, ysize, Id;
  EDIT_Handle hEdit;
  EDIT_Obj* pObj;
  const GUI_FONT GUI_UNI_PTR * pOldFont = GUI_SetFont(EDIT_GetDefaultFont());
  x = GUI_GetDispPosX();
  y = GUI_GetDispPosY();
  if (xsize == 0)
    xsize = GUI_GetCharDistX('X') * Len;
  ysize = GUI_GetFontSizeY();
  Id = 0x1234;
  hEdit = EDIT_Create(x, y, xsize, ysize, Id, Len, 0);
  pObj = EDIT_H2P(hEdit);
  EDIT_SetFloatMode(hEdit, Value, Min, Max, Shift, Flags);
  do {
    Key = GUI_WaitKey();
    switch (Key) {
    case GUI_KEY_ESCAPE:
      break;
    default:
      EDIT_AddKey(hEdit, Key);
    }
  } while ((Key != GUI_KEY_ESCAPE) && (Key != GUI_KEY_ENTER) && (Key != 0));
  GUI_SetFont(pOldFont);
  Ret = (I32)pObj->CurrentValue / (float)GUI_Pow10[pObj->NumDecs];
  EDIT_Delete(hEdit);
  return Ret;
}

#else /* avoid empty object files */

void GUI_EditFloat_C(void);
void GUI_EditFloat_C(void){}

#endif
