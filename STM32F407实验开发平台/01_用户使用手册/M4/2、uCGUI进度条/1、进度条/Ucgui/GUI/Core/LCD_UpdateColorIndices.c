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
File        : LCD_UpdateColorIndices.c
Purpose     : Implementation of LCD_UpdateColorIndices
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Private.h"
#include "GUI_Private.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_UpdateColorIndices
*/
void LCD_UpdateColorIndices(void) {
  LCD_SetColorIndex(LCD_Color2Index(GUI_Context.Color));
  LCD_SetBkColorIndex(LCD_Color2Index(GUI_Context.BkColor));
}

/*************************** End of file ****************************/
