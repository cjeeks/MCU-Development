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
File        : GUI_Color2VisColor.C
Purpose     : Implementation of GUI_Color2VisColor
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
*       GUI_Color2VisColor
*/
GUI_COLOR GUI_Color2VisColor(GUI_COLOR color) {
  I16 Index;
  GUI_COLOR r;
  GUI_LOCK();
  Index = LCD_Color2Index(color);
  r = LCD_Index2Color(Index);  
  GUI_UNLOCK();
  return r;  
}

/*********************************************************************
*
*       GUI_ColorIsAvailable
*/
char GUI_ColorIsAvailable(GUI_COLOR color) {
  return (GUI_Color2VisColor(color) == color) ? 1 : 0;
}

/*********************************************************************
*
*       GUI_CalcVisColorError
*/
U32 GUI_CalcVisColorError(GUI_COLOR color) {
  return GUI_CalcColorDist(color, GUI_Color2VisColor(color));
}

/*************************** End of file ****************************/
