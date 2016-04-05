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
File        : LCD_SetPixelIndex.c
Purpose     : Implementation of optional routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include "GUI_Private.h"
#include "LCD_Private.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define RETURN_IF_Y_OUT() \
  if (y < GUI_Context.ClipRect.y0) return;             \
  if (y > GUI_Context.ClipRect.y1) return;

#define RETURN_IF_X_OUT() \
  if (x < GUI_Context.ClipRect.x0) return;             \
  if (x > GUI_Context.ClipRect.x1) return;

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_SetPixelIndex
*
* Purpose:
*   Writes 1 pixel into the display.
*/
void LCD_SetPixelIndex(int x, int y, int ColorIndex) {
  RETURN_IF_X_OUT();
  RETURN_IF_Y_OUT();
  LCDDEV_L0_SetPixelIndex(x, y, ColorIndex);
}

/*************************** End of file ****************************/
