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
File        : LCD_API.C
Purpose     : Selection of LCD display
---------------------------END-OF-HEADER------------------------------
*/


#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_Private.h"      /* Required for configuration, APIList */

#if GUI_COMPILER_SUPPORTS_FP

/*********************************************************************
*
*             LCD Device
*       (if memory devices are supported)
*
**********************************************************************
*/

const tLCDDEV_APIList LCD_L0_APIList = {
#if LCD_YMAG==1
  #if LCD_DELTA_MODE
    LCD_L0_Color2Index,
    LCD_L0_Index2Color,
    LCD_L0_GetIndexMask,
    LCD_L0_DELTA_DrawBitmap,
    LCD_L0_DELTA_DrawHLine,
    LCD_L0_DELTA_DrawVLine,
    LCD_L0_DELTA_FillRect,
    LCD_L0_DELTA_GetPixelIndex,
    LCD_L0_GetRect,          /* Original routine is o.k. here, since we use the logical
                                   coordinates for clipping, which are not magnified */
    LCD_L0_DELTA_SetPixelIndex,
    LCD_L0_DELTA_XorPixel,
    LCD_L0_SetLUTEntry,
  #else
    LCD_L0_Color2Index,
    LCD_L0_Index2Color,
    LCD_L0_GetIndexMask,
    (tLCDDEV_DrawBitmap*)LCD_L0_DrawBitmap,
    LCD_L0_DrawHLine,
    LCD_L0_DrawVLine,
    LCD_L0_FillRect,
    LCD_L0_GetPixelIndex,
    LCD_L0_GetRect,
    LCD_L0_SetPixelIndex,
    LCD_L0_XorPixel,
    LCD_L0_SetLUTEntry,
  #endif
#else
  LCD_L0_Color2Index,
  LCD_L0_Index2Color,
  LCD_L0_GetIndexMask,
  LCD_L0_MAG_DrawBitmap,
  LCD_L0_MAG_DrawHLine,
  LCD_L0_MAG_DrawVLine,
  LCD_L0_MAG_FillRect,
  LCD_L0_MAG_GetPixelIndex,
  LCD_L0_GetRect,          /* Original routine is o.k. here, since we use the logical
                                 coordinates for clipping, which are not magnified */
  LCD_L0_MAG_SetPixelIndex,
  LCD_L0_MAG_XorPixel,
  LCD_L0_SetLUTEntry,
#endif
#if GUI_SUPPORT_MEMDEV
  NULL,                       /* pfFillPolygon */
  NULL,                       /* pfFillPolygonAA */
  #if LCD_BITSPERPIXEL <= 8
    &GUI_MEMDEV__APIList8
  #else
    &GUI_MEMDEV__APIList16
  #endif
#endif
};

/*
      *************************************************
      *                                               *
      *             LCD Device                        *
			*       (if memory devices are supported)       *
      *                                               *
      *************************************************
*/

#if GUI_NUM_LAYERS > 1
const tLCDDEV_APIList LCD_L0_1_APIList = {
#if LCD_YMAG_1 == 1
  LCD_L0_1_Color2Index,
  LCD_L0_1_Index2Color,
  LCD_L0_1_GetIndexMask,
  LCD_L0_1_DrawBitmap,
  LCD_L0_1_DrawHLine,
  LCD_L0_1_DrawVLine,
  LCD_L0_1_FillRect,
  LCD_L0_1_GetPixelIndex,
  LCD_L0_1_GetRect,
  LCD_L0_1_SetPixelIndex,
  LCD_L0_1_XorPixel,
  LCD_L0_1_SetLUTEntry,
#else
  LCD_L0_1_Color2Index,
  LCD_L0_1_Index2Color,
  LCD_L0_1_GetIndexMask,
  LCD_L0_1_MAG_DrawBitmap,
  LCD_L0_1_MAG_DrawHLine,
  LCD_L0_1_MAG_DrawVLine,
  LCD_L0_1_MAG_FillRect,
  LCD_L0_1_MAG_GetPixelIndex,
  LCD_L0_1_GetRect,          /* Original routine is o.k. here, since we use the logical
                                 coordinates for clipping, which are not magnified */
  LCD_L0_1_MAG_SetPixelIndex,
  LCD_L0_1_MAG_XorPixel,
  LCD_L0_1_SetLUTEntry,
#endif
#if GUI_SUPPORT_MEMDEV
  NULL,                       /* pfFillPolygon */
  NULL,                       /* pfFillPolygonAA */
  #if LCD_BITSPERPIXEL_1 <= 8
    &GUI_MEMDEV__APIList8
  #else
    &GUI_MEMDEV__APIList16
  #endif
#endif
};
#endif

#if GUI_NUM_LAYERS > 2
const tLCDDEV_APIList LCD_L0_2_APIList = {
#if LCD_YMAG_2 == 1
  LCD_L0_2_Color2Index,
  LCD_L0_2_Index2Color,
  LCD_L0_2_GetIndexMask,
  LCD_L0_2_DrawBitmap,
  LCD_L0_2_DrawHLine,
  LCD_L0_2_DrawVLine,
  LCD_L0_2_FillRect,
  LCD_L0_2_GetPixelIndex,
  LCD_L0_2_GetRect,
  LCD_L0_2_SetPixelIndex,
  LCD_L0_2_XorPixel,
  LCD_L0_2_SetLUTEntry,
#else
  LCD_L0_2_Color2Index,
  LCD_L0_2_Index2Color,
  LCD_L0_2_GetIndexMask,
  LCD_L0_2_MAG_DrawBitmap,
  LCD_L0_2_MAG_DrawHLine,
  LCD_L0_2_MAG_DrawVLine,
  LCD_L0_2_MAG_FillRect,
  LCD_L0_2_MAG_GetPixelIndex,
  LCD_L0_2_GetRect,          /* Original routine is o.k. here, since we use the logical
                                 coordinates for clipping, which are not magnified */
  LCD_L0_2_MAG_SetPixelIndex,
  LCD_L0_2_MAG_XorPixel,
  LCD_L0_2_SetLUTEntry,
#endif
#if GUI_SUPPORT_MEMDEV
  NULL,                       /* pfFillPolygon */
  NULL,                       /* pfFillPolygonAA */
  #if LCD_BITSPERPIXEL_2 <= 8
    &GUI_MEMDEV__APIList8
  #else
    &GUI_MEMDEV__APIList16
  #endif
#endif
};
#endif

#if GUI_NUM_LAYERS > 3
const tLCDDEV_APIList LCD_L0_3_APIList = {
#if LCD_YMAG_3 == 1
  LCD_L0_3_Color2Index,
  LCD_L0_3_Index2Color,
  LCD_L0_3_GetIndexMask,
  LCD_L0_3_DrawBitmap,
  LCD_L0_3_DrawHLine,
  LCD_L0_3_DrawVLine,
  LCD_L0_3_FillRect,
  LCD_L0_3_GetPixelIndex,
  LCD_L0_3_GetRect,
  LCD_L0_3_SetPixelIndex,
  LCD_L0_3_XorPixel,
  LCD_L0_3_SetLUTEntry,
#else
  LCD_L0_3_Color2Index,
  LCD_L0_3_Index2Color,
  LCD_L0_3_GetIndexMask,
  LCD_L0_3_MAG_DrawBitmap,
  LCD_L0_3_MAG_DrawHLine,
  LCD_L0_3_MAG_DrawVLine,
  LCD_L0_3_MAG_FillRect,
  LCD_L0_3_MAG_GetPixelIndex,
  LCD_L0_3_GetRect,          /* Original routine is o.k. here, since we use the logical
                                 coordinates for clipping, which are not magnified */
  LCD_L0_3_MAG_SetPixelIndex,
  LCD_L0_3_MAG_XorPixel,
  LCD_L0_3_SetLUTEntry,
#endif
#if GUI_SUPPORT_MEMDEV
  NULL,                       /* pfFillPolygon */
  NULL,                       /* pfFillPolygonAA */
  #if LCD_BITSPERPIXEL_3 <= 8
    &GUI_MEMDEV__APIList8
  #else
    &GUI_MEMDEV__APIList16
  #endif
#endif
};
#endif

#if GUI_NUM_LAYERS > 4
const tLCDDEV_APIList LCD_L0_4_APIList = {
#if LCD_YMAG_4 == 1
  LCD_L0_4_Color2Index,
  LCD_L0_4_Index2Color,
  LCD_L0_4_GetIndexMask,
  LCD_L0_4_DrawBitmap,
  LCD_L0_4_DrawHLine,
  LCD_L0_4_DrawVLine,
  LCD_L0_4_FillRect,
  LCD_L0_4_GetPixelIndex,
  LCD_L0_4_GetRect,
  LCD_L0_4_SetPixelIndex,
  LCD_L0_4_XorPixel,
  LCD_L0_4_SetLUTEntry,
#else
  LCD_L0_4_Color2Index,
  LCD_L0_4_Index2Color,
  LCD_L0_4_GetIndexMask,
  LCD_L0_4_MAG_DrawBitmap,
  LCD_L0_4_MAG_DrawHLine,
  LCD_L0_4_MAG_DrawVLine,
  LCD_L0_4_MAG_FillRect,
  LCD_L0_4_MAG_GetPixelIndex,
  LCD_L0_4_GetRect,          /* Original routine is o.k. here, since we use the logical
                                 coordinates for clipping, which are not magnified */
  LCD_L0_4_MAG_SetPixelIndex,
  LCD_L0_4_MAG_XorPixel,
  LCD_L0_4_SetLUTEntry,
#endif
#if GUI_SUPPORT_MEMDEV
  NULL,                       /* pfFillPolygon */
  NULL,                       /* pfFillPolygonAA */
  #if LCD_BITSPERPIXEL_4 <= 8
    &GUI_MEMDEV__APIList8
  #else
    &GUI_MEMDEV__APIList16
  #endif
#endif
};
#endif

/***********************************************************
*
*                 LCD_aAPI
*
* Purpose:
*  This table lists the available displays/layers by a single pointer.
*  It is important that these are non-constants, because some high level
*  software (such as the VNC server, but maybe also the mouse "Cursor" mdoule)
*  may need to override these pointers in order to link itself into the chain
*  of drawing routines.
*  However, the API tables may of course be constants.
*
*/

const tLCDDEV_APIList* /*const*/ LCD_aAPI[] = {
  &LCD_L0_APIList
#if GUI_NUM_LAYERS > 1
  ,&LCD_L0_1_APIList
#endif
#if GUI_NUM_LAYERS > 2
  ,&LCD_L0_2_APIList
#endif
#if GUI_NUM_LAYERS > 3
  ,&LCD_L0_3_APIList
#endif
#if GUI_NUM_LAYERS > 4
  ,&LCD_L0_4_APIList
#endif
};

#endif

/*************************** End of file ****************************/

