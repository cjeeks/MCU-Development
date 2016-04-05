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
File        : LCD111.C
Purpose     : Color conversion routines for 111 color mode
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Protected.h"    /* inter modul definitions */

/*********************************************************************
*
*       Public code, LCD_FIXEDPALETTE == 111, 8 basic colors
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_111
*/
unsigned LCD_Color2Index_111(LCD_COLOR Color) {
  int r,g,b;
  r = (Color>>(0+7))  &1;
  g = (Color>>(8+7))  &1;
  b = (Color>>(16+7)) &1;
  return r+(g<<1)+(b<<2);
}

/*********************************************************************
*
*       LCD_Index2Color_111
*/
LCD_COLOR LCD_Index2Color_111(int Index) {
  U16 r,g,b;
  r = (((Index>>0)&1)*0xff);
  g = (((Index>>1)&1)*0xff);
  b =   (Index>>2)   *0xff;
  return r | (g<<8) | ((U32)b<<16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_111
*/
unsigned LCD_GetIndexMask_111(void) {
  return 0x0007;
}

/*********************************************************************
*
*       Public code, LCD_FIXEDPALETTE == 111, 8 basic colors, SWAP_RB
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_M111
*/
unsigned LCD_Color2Index_M111(LCD_COLOR Color) {
  int r,g,b;
  r = (Color>>(0+7))  &1;
  g = (Color>>(8+7))  &1;
  b = (Color>>(16+7)) &1;
  return b+(g<<1)+(r<<2); 
}

/*********************************************************************
*
*       LCD_Index2Color_M111
*/
LCD_COLOR LCD_Index2Color_M111(int Index) {
  U16 r,g,b;
  r = (((Index>>0)&1)*0xff);
  g = (((Index>>1)&1)*0xff);
  b =   (Index>>2)   *0xff;
  return b | (g<<8) | ((U32)r<<16);
}

/*********************************************************************
*
*       LCD_GetIndexMask_M111
*/
unsigned LCD_GetIndexMask_M111(void) {
  return 0x0007;
}

/*************************** End of file ****************************/
