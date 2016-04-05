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
File        : LCDInfo1.C
Purpose     : Routines returning info at runtime
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.h"		          /* interface definitions */
#include "LCD_Private.h"      /* private modul definitions & config */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

#if GUI_NUM_LAYERS > 1
  int LCD_GetXSize_1(void)        { return LCD_XSIZE_1; }
  int LCD_GetYSize_1(void)        { return LCD_YSIZE_1; }
  int LCD_GetVXSize_1(void)       { return LCD_VXSIZE_1; }
  int LCD_GetVYSize_1(void)       { return LCD_VYSIZE_1; }
  int LCD_GetBitsPerPixel_1(void) { return LCD_BITSPERPIXEL_1; }
  U32 LCD_GetNumColors_1(void)    { return LCD_NUM_COLORS_1; }
  int LCD_GetYMag_1(void)         { return LCD_YMAG_1; }
  int LCD_GetXMag_1(void)         { return LCD_XMAG_1; }
  int LCD_GetFixedPalette_1(void) { return LCD_FIXEDPALETTE_1; }
#else
  int LCD_GetXSize_1(void)        { return 0; }
  int LCD_GetYSize_1(void)        { return 0; }
  int LCD_GetVXSize_1(void)       { return 0; }
  int LCD_GetVYSize_1(void)       { return 0; }
  int LCD_GetBitsPerPixel_1(void) { return 0; }
  U32 LCD_GetNumColors_1(void)    { return 0; }
  int LCD_GetYMag_1(void)         { return 0; }
  int LCD_GetXMag_1(void)         { return 0; }
  int LCD_GetFixedPalette_1(void) { return 0; }
#endif

/*************************** End of file ****************************/
