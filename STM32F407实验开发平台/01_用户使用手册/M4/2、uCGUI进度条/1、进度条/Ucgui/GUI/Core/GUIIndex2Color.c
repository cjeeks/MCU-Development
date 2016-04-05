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
File        : GUIIndex2Color.C
Purpose     : Converts a color index to a RGB-value
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
*       GUI_Index2Color
*/
GUI_COLOR GUI_Index2Color(int Index) {
  GUI_COLOR Color;
  GUI_LOCK();
  Color = LCD_Index2Color(Index);
  GUI_UNLOCK();
  return Color;
}

/*************************** End of file ****************************/
