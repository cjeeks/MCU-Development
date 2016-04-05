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
File        : LCD2.C
Purpose     : Color conversion routines for 4 bpp gray LCDs
---------------------------END-OF-HEADER------------------------------
*/

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
*       LCD_Color2Index_2
*
* Purpose
*   API table for this color conversion mode. Only used by memory
*   devices in this mode.
*/
const LCD_API_COLOR_CONV LCD_API_ColorConv_2 = {
  LCD_Color2Index_2,
  LCD_Index2Color_2,
  LCD_GetIndexMask_2
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
*       LCD_Color2Index_2
*/
unsigned LCD_Color2Index_2(LCD_COLOR Color) {
  int r,g,b;
  r = Color      &255;
  g = (Color>>8) &255;
  b = Color>>16;
  return (r+g+b+127) /255;
}

/*********************************************************************
*
*       LCD_Index2Color_2
*/
LCD_COLOR LCD_Index2Color_2(int Index) {
  return ((U32)Index)*0x555555;
}

/*********************************************************************
*
*       LCD_GetIndexMask_2
*/
unsigned LCD_GetIndexMask_2(void) {
  return 0x03;
}

/*************************** End of file ****************************/
