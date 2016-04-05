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
File        : LCD_Index2ColorEx.c
Purpose     : Implementation of LCD_Index2ColorEx
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"
#include "LCD_Private.h"      /* Required for configuration, APIList */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Index2ColorEx
*
* Purpose:
*   Convert Index to color for the given display
*/
LCD_COLOR LCD_Index2ColorEx(int i, unsigned int LayerIndex) {
  #if GUI_SUPPORT_DEVICES
  LCD_COLOR r = 0;
  if (LayerIndex < GUI_NUM_LAYERS) {
    r = LCD_aAPI[LayerIndex]->pfIndex2Color(i);
  }
  return r;
  #else
    GUI_USE_PARA(LayerIndex);
    return LCD_Index2Color(i);
  #endif
}

/*************************** End of file ****************************/
