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
File        : GUI_SetDefault.c
Purpose     : Implementation of GUI_SetDefault
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
*       GL_SetDefault
*/
void GL_SetDefault(void) {
  GUI_SetBkColor(GUI_DEFAULT_BKCOLOR);
  GUI_SetColor  (GUI_DEFAULT_COLOR);
  GUI_SetPenSize(1);
  GUI_SetTextAlign(0);
  GUI_SetTextMode(0);
  GUI_SetDrawMode(0);
  GUI_SetFont(GUI_DEFAULT_FONT);
  GUI_SetLineStyle(GUI_LS_SOLID);
}

/*********************************************************************
*
*       GUI_SetDefault
*/
void GUI_SetDefault(void) {
  GUI_LOCK();
  GL_SetDefault();
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
