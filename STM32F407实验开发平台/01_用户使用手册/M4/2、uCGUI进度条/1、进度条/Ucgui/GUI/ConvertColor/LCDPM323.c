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
File        : LCDPM323.C
Purpose     : Color conversion routines for -323 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == -323, 256 colors, RRRGGBBB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_M323
*/
unsigned LCD_Color2Index_M323(LCD_COLOR Color) {
  unsigned r, g, b;
  r = Color & 255;
  g = (Color >> 8 ) & 255;
  b = Color >> 16;
  r = (r * 7 + 127) / 255;
  g = (g + 42) / 85;
  b = (b * 7 + 127) / 255;
  return b + (g << 3) + (r << 5);
}

/*********************************************************************
*
*       LCD_Index2Color_M323
*/
LCD_COLOR LCD_Index2Color_M323(int Index) {
  unsigned r, g, b;
  b = (Index & 7) * 255 / 7;
  g = ((Index >> 3) & 3) * 85;
  r = ((Index >> 5) & 7) * 255 / 7;
  return r + (g << 8) + (((U32)b) << 16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_M323
*/
unsigned LCD_GetIndexMask_M323(void) {
  return 0xff;
}

/*************************** End of file ****************************/
