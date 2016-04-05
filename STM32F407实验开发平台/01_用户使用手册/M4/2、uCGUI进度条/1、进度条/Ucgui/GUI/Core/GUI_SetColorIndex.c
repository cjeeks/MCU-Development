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
File        : GUI_DrawBitmap.C
Purpose     : Implementation of GUI_DrawBitmap
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
*       GUI_SetBkColorIndex
*/
void GUI_SetBkColorIndex(int Index) {
  GUI_LOCK(); {
    GUI_Context.BkColor = GUI_INVALID_COLOR;
    LCD_SetBkColorIndex(Index);
  } GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_SetColorIndex
*/
void GUI_SetColorIndex(int Index) {
  GUI_LOCK(); {
    GUI_Context.Color = GUI_INVALID_COLOR;
    LCD_SetColorIndex(Index);
  } GUI_UNLOCK();
}

/*************************** End of file ****************************/
