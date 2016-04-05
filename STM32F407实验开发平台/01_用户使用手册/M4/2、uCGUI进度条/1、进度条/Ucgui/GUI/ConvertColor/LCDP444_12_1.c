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
File        : LCDP444_12_1.c
Purpose     : Color conversion routines for LCD-drivers
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code,
*
*       LCD_FIXEDPALETTE == 444, 4096 colors, RRRRGGGGBBBB----
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_444_12_1
*/
unsigned LCD_Color2Index_444_12_1(LCD_COLOR Color) {
  unsigned int r,g,b;
  r = Color         & 255;
  g = (Color >> 8)  & 255;
  b = (Color >> 16) & 255;
  r = (r + 8) / 17;
  g = (g + 8) / 17;
  b = (b + 8) / 17;
  return (b << 4) + (g << 8) + (r << 12);
}

/*********************************************************************
*
*       LCD_Index2Color_444_12_1
*/
LCD_COLOR LCD_Index2Color_444_12_1(int Index) {
  unsigned int r,g,b;
  /* Seperate the color masks */
  r = ((unsigned)Index >> 12) & 0xf;
  g = ((unsigned)Index >>  8) & 0xf;
  b = ((unsigned)Index >>  4) & 0xf;
  /* Convert the color masks */
  r = r * 17;
  g = g * 17;
  b = b * 17;
  return r + (g << 8) + (((U32)b) << 16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_444_12_1
*/
unsigned LCD_GetIndexMask_444_12_1(void) {
  return 0xfff0;
}

/*************************** End of file ****************************/
