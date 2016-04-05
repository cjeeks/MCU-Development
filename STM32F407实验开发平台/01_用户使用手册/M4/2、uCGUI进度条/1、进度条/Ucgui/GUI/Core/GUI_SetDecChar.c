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
File        : GUI_SetDecChar.C
Purpose     : Routines to set the character used for decimal point
----------------------------------------------------------------------
*/

#include "GUI_Protected.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_SetDecChar
*/
char GUI_SetDecChar(char c) {
  char r = GUI_DecChar;
  GUI_DecChar = c;
  return r;
}

/*********************************************************************
*
*       GUI_GetDecChar
*/
char GUI_GetDecChar(void) {
  return GUI_DecChar;
}

/*************************** End of file ****************************/
