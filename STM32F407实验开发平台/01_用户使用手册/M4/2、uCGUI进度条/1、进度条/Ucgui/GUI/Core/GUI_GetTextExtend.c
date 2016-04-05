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
File        : GUI_GetTextExtend.c
Purpose     : Implementation of GUI_GetTextExtend
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
*       GUI_GetTextExtend
*/
void GUI_GetTextExtend(GUI_RECT* pRect, const char GUI_UNI_PTR * s, int MaxNumChars) {
  int xMax      = 0;
  int NumLines  = 0;
  int LineSizeX = 0;
  U16 Char;
  pRect->x0 = GUI_Context.DispPosX;
  pRect->y0 = GUI_Context.DispPosY;
  while (MaxNumChars--) {
    Char = GUI_UC__GetCharCodeInc(&s);
    if ((Char == '\n') || (Char == 0)) {
      if (LineSizeX > xMax) {
        xMax = LineSizeX;
      }
      LineSizeX = 0;
      NumLines++;
      if (!Char) {
        break;
      }
    } else {
      LineSizeX += GUI_GetCharDistX(Char);
    }
  }
  if (LineSizeX > xMax) {
    xMax = LineSizeX;
  }
  if (!NumLines) {
    NumLines = 1;
  }
  pRect->x1 = pRect->x0 + xMax - 1;
  pRect->y1 = pRect->y0 + GUI__GetFontSizeY() * NumLines - 1;
}

/*************************** End of file ****************************/
