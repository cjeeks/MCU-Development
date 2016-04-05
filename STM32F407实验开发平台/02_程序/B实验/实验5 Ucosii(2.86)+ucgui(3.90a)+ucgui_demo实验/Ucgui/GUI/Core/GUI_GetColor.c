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
File        : GUI_GetColor.C
Purpose     : Implementation of different GUI_GetColor routines
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GetBkColorIndex
*/
int GUI_GetBkColorIndex(void) {
  int r;
  GUI_LOCK();
  r = LCD_GetBkColorIndex();
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_GetBkColor
*/
GUI_COLOR GUI_GetBkColor(void) {
  GUI_COLOR r;
  GUI_LOCK();
  r = LCD_Index2Color(LCD_GetBkColorIndex());
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_GetColorIndex
*/
int GUI_GetColorIndex(void) {
  int r;
  GUI_LOCK();
  r = LCD_GetColorIndex();
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_GetColor
*/
GUI_COLOR GUI_GetColor(void) {
  GUI_COLOR r;
  GUI_LOCK();
  r = LCD_Index2Color(LCD_GetColorIndex());
  GUI_UNLOCK();
  return r;
}

/*************************** End of file ****************************/
