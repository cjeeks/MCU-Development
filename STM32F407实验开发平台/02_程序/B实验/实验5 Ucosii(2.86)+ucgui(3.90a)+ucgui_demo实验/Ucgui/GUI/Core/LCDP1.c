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
File        : LCD1.C
Purpose     : Color conversion routines for 1 bpp (b/w) mode
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "LCD_Protected.h"    /* inter modul definitions */


/*********************************************************************
*
*       Public data
*
**********************************************************************
*/

#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       LCD_Color2Index_1
*
* Purpose
*   API table for this color conversion mode. Only used by memory
*   devices in this mode.
*/
const LCD_API_COLOR_CONV LCD_API_ColorConv_1 = {
  LCD_Color2Index_1,
  LCD_Index2Color_1,
  LCD_GetIndexMask_1
};

#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_1
*/
unsigned LCD_Color2Index_1(LCD_COLOR Color) {
  int r,g,b;
  r = Color      &255;
  g = (Color>>8) &255;
  b = Color>>16;
  return (r+g+b+383) /(3*255);
}

/*********************************************************************
*
*       LCD_Index2Color_1
*/
LCD_COLOR LCD_Index2Color_1(int Index) {
  return Index ? 0xFFFFFF : 0;
}

/*********************************************************************
*
*       LCD_GetIndexMask_1
*/
unsigned LCD_GetIndexMask_1(void) {
  return 0x01;
}

/*************************** End of file ****************************/
