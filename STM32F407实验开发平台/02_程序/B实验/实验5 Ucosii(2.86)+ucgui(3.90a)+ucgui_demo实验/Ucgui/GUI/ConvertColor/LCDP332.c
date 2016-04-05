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
File        : LCDP332.C
Purpose     : Color conversion routines for 332 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 332, 256 colors, BBBGGGRR
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_332
*/
unsigned LCD_Color2Index_332(LCD_COLOR Color) {
  int r, g, b;
  r = Color & 255;
  g = (Color >> 8 ) & 255;
  b = Color >> 16;
  r = (r + 42) / 85;
  g = (g * 7 + 127) / 255;
  b = (b * 7 + 127) / 255;
  return r + (g << 2) + (b << 5);
}

/*********************************************************************
*
*       LCD_Index2Color_332
*/
LCD_COLOR LCD_Index2Color_332(int Index) {
  unsigned r, g, b;
  r = (Index & 3) * 85;
  g = ((Index >> 2) & 7) * 255 / 7;
  b = ((Index >> 5) & 7) * 255 / 7;
  return r + (g << 8) + (((U32)b) << 16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_332
*/
unsigned LCD_GetIndexMask_332(void) {
  return 0xff;
}

/*************************** End of file ****************************/
