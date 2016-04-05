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
File        : GUI_DispHex.C
Purpose     : Routines to display hex
----------------------------------------------------------------------
*/

#include "GUI_Protected.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DispHex
*/
void GUI_DispHex(U32 v, U8 Len) {
  char ac[9];
	char* s = ac;
  GUI_AddHex(v, Len, &s);
  GUI_DispString(ac);
}

/*********************************************************************
*
*       GUI_DispHexAt
*/
void GUI_DispHexAt(U32 v, I16P x, I16P y, U8 Len) {
  char ac[9];
	char* s = ac;
  GUI_AddHex(v, Len, &s);
  GUI_DispStringAt(ac, x, y);
}

/*************************** End of file ****************************/

