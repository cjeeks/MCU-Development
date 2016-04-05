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
File        : LCDColor.C
Purpose     : Color conversion routines for LCD-drivers
---------------------------END-OF-HEADER------------------------------
*/

#define LCDCOLOR_C

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"
#include "LCD_Private.h"      /* inter modul definitions & Config */

/*********************************************************************
*
*       Defines, config defaults
*
**********************************************************************
*/

#ifndef  LCD_SIZEOF_COLORCACHE
  #define LCD_SIZEOF_COLORCACHE 0
#endif

#if  LCD_SIZEOF_COLORCACHE
  static  const LCD_LOGPALETTE * pLogPalCache;
#endif

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/

LCD_PIXELINDEX LCD__aConvTable[LCD_MAX_LOG_COLORS];

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_GetpPalConvTableUncached
*/
LCD_PIXELINDEX* LCD_GetpPalConvTableUncached(const LCD_LOGPALETTE GUI_UNI_PTR *  pLogPal) {
  if (pLogPal == NULL) {
    return NULL;
  }
  if (!pLogPal->pPalEntries) {
    return NULL;
  }
  /* Check if sufficient space is available */
  if (pLogPal->NumEntries > LCD_MAX_LOG_COLORS) {
    return NULL;
  }
  /* Build conversion table */
  {
    int i;
    int NumEntries = pLogPal->NumEntries;
    const LCD_COLOR GUI_UNI_PTR * pPalEntry = &pLogPal->pPalEntries[0];
    for (i=0; i< NumEntries; i++) {
      LCD__aConvTable[i] = LCD_Color2Index(*(pPalEntry+i));
    }
  }
  return &LCD__aConvTable[0];
}

/*********************************************************************
*
*       LCD_GetpPalConvTable
*/
LCD_PIXELINDEX* LCD_GetpPalConvTable(const LCD_LOGPALETTE GUI_UNI_PTR *  pLogPal) {
/* Check cache */
  #if  LCD_SIZEOF_COLORCACHE
    if (pLogPalCache == pLogPal) {
      return &LCD__aConvTable[0];
    }
    pLogPalCache = pLogPal;
  #endif
  return LCD_GetpPalConvTableUncached(pLogPal);
}

/*********************************************************************
*
*       LCD_InitLUT
*/
void LCD_InitLUT(void) {
  #if (LCD_BITSPERPIXEL <= 8)
    {
      int i;
      for (i=0; i < LCD_NUM_COLORS; i++) {
        LCD_COLOR color = LCD_Index2Color((U8)i);
        #if LCD_REVERSE_LUT
          color ^= 0xffffff;    /* Invert R,G,B components */
        #endif
        LCD_L0_SetLUTEntry((U8)i, color);
      }
    }
  #endif
  #if (GUI_NUM_LAYERS > 1)
    #if (LCD_BITSPERPIXEL_1 <= 8)
    {
      int i;
      int DisplayOld = GUI_SelectLayer(1);
      for (i=0; i < LCD_NUM_COLORS_1; i++) {
        LCD_COLOR color = LCD_Index2Color((U8)i);
        #if LCD_REVERSE_LUT_1
          color ^= 0xffffff;    /* Invert R,G,B components */
        #endif
        LCD_L0_1_SetLUTEntry((U8)i, color);
      }
      GUI_SelectLayer(DisplayOld);
    }
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 2)
    #if (LCD_BITSPERPIXEL_2 <= 8)
    {
      int i;
      int DisplayOld = GUI_SelectLayer(2);
      for (i=0; i < LCD_NUM_COLORS_2; i++) {
        LCD_COLOR color = LCD_Index2Color((U8)i);
        #if LCD_REVERSE_LUT_2
          color ^= 0xffffff;    /* Invert R,G,B components */
        #endif
        LCD_L0_2_SetLUTEntry((U8)i, color);
      }
      GUI_SelectLayer(DisplayOld);
    }
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 3)
    #if (LCD_BITSPERPIXEL_3 <= 8)
    {
      int i;
      int DisplayOld = GUI_SelectLayer(3);
      for (i=0; i < LCD_NUM_COLORS_3; i++) {
        LCD_COLOR color = LCD_Index2Color((U8)i);
        #if LCD_REVERSE_LUT_3
          color ^= 0xffffff;    /* Invert R,G,B components */
        #endif
        LCD_L0_3_SetLUTEntry((U8)i, color);
      }
      GUI_SelectLayer(DisplayOld);
    }
    #endif
  #endif
  #if (GUI_NUM_LAYERS > 4)
    #if (LCD_BITSPERPIXEL_4 <= 8)
    {
      int i;
      int DisplayOld = GUI_SelectLayer(4);
      for (i=0; i < LCD_NUM_COLORS_4; i++) {
        LCD_COLOR color = LCD_Index2Color((U8)i);
        #if LCD_REVERSE_LUT_4
          color ^= 0xffffff;    /* Invert R,G,B components */
        #endif
        LCD_L0_4_SetLUTEntry((U8)i, color);
      }
      GUI_SelectLayer(DisplayOld);
    }
    #endif
  #endif
}

/*************************** End of file ****************************/
