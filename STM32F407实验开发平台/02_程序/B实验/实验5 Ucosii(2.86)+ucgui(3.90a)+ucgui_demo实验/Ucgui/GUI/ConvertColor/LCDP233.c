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
File        : LCDP233.C
Purpose     : Color conversion routines for 233 mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 233, 256 colors, BBGGGRRR
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_233
*/
unsigned LCD_Color2Index_233(LCD_COLOR Color) {
  int r, g, b;
  r = Color & 255;
  g = (Color >> 8 ) & 255;
  b = Color >> 16;
  r = (r * 7 + 127) / 255;
  g = (g * 7 + 127) / 255;
  b = (b + 42) / 85;
  return r + (g << 3) + (b << 6);
}

/*********************************************************************
*
*       LCD_Index2Color_233
*/
LCD_COLOR LCD_Index2Color_233(int Index) {
  int r, g, b;
  r = (Index & 7) * 255 / 7;
  g = ((Index >> 3) & 7) * 255 / 7;
  b = ((Index >> 6) & 3) * 85;
  return r + (g << 8) + (((U32)b) << 16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_233
*/
unsigned LCD_GetIndexMask_233(void) {
  return 0xff;
}

/*************************** End of file ****************************/
