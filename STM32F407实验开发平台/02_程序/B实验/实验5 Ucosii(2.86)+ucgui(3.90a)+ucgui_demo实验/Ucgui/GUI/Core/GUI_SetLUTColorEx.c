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
File        : GUI_SetLUTColorEx.c
Purpose     : Implementation of GUI_SetLUTColorEx
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "GUI_Private.h"
#include "LCD_Private.h"      /* Required for configuration, APIList */

#if GUI_COMPILER_SUPPORTS_FP

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const LCD_LUT_INFO _aLutInfo[GUI_NUM_LAYERS] = {
  #if GUI_NUM_LAYERS > 1
    {
      #if (LCD_FIXEDPALETTE == 0) && (LCD_PHYSCOLORS_IN_RAM)
        LCD_PhysColors, (I16)(1 << LCD_BITSPERPIXEL_0)
      #else
        NULL, 0
      #endif
    },
    {
      #if (LCD_FIXEDPALETTE_1 == 0) && (LCD_PHYSCOLORS_IN_RAM)
        LCD_PhysColors_1, (I16)(1 << LCD_BITSPERPIXEL_1)
      #else
        NULL, 0
      #endif
    },
    #if GUI_NUM_LAYERS > 2
    {
      #if (LCD_FIXEDPALETTE_1 == 0) && (LCD_PHYSCOLORS_IN_RAM)
        LCD_PhysColors_2, (I16)(1 << LCD_BITSPERPIXEL_2)
      #else
        NULL, 0
      #endif
    },
    #endif
    #if GUI_NUM_LAYERS > 3
    {
      #if (LCD_FIXEDPALETTE_3 == 0) && (LCD_PHYSCOLORS_IN_RAM)
        LCD_PhysColors_3, (I16)(1 << LCD_BITSPERPIXEL_3)
      #else
        NULL, 0
      #endif
    },
    #endif
    #if GUI_NUM_LAYERS > 4
    {
      #if (LCD_FIXEDPALETTE_4 == 0) && (LCD_PHYSCOLORS_IN_RAM)
        LCD_PhysColors_4, (I16)(1 << LCD_BITSPERPIXEL_4)
      #else
        NULL, 0
      #endif
    },
    #endif
  #else
    {
      #if (LCD_FIXEDPALETTE == 0) && (LCD_PHYSCOLORS_IN_RAM)
        LCD_PhysColors, 1 << LCD_BITSPERPIXEL
      #else
        NULL, 0
      #endif
    }
  #endif
};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SetLUTColorEx
*/
void GUI_SetLUTColorEx(U8 Pos, LCD_COLOR Color, unsigned int LayerIndex) {
  if (LayerIndex < GUI_NUM_LAYERS) {
    if (Pos < _aLutInfo[LayerIndex].NumEntries) {
      LCD_aAPI[LayerIndex]->pfSetLUTEntry(Pos, Color);
      _aLutInfo[LayerIndex].paColor[Pos] = Color;
    }
  }
}

#endif

/*************************** End of file ****************************/
