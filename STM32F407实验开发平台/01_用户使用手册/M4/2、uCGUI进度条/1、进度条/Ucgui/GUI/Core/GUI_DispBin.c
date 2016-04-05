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
File        : GUI_DispBin.c
Purpose     : Routines to display values as binary
----------------------------------------------------------------------
*/

#include "GUI_Protected.h"
#include "GUIDebug.h"
#include "string.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*     GUI_DispBin
*/
void GUI_DispBin(U32 v, U8 Len) {
	char ac[33];
	char* s = ac;
  GUI_AddBin(v, Len, &s);
  GUI_DispString(ac);
}

/*********************************************************************
*
*     GUI_DispBinAt
*/
void GUI_DispBinAt(U32 v, I16P x, I16P y, U8 Len) {
	char ac[33];
	char* s = ac;
  GUI_AddBin(v, Len, &s);
  GUI_DispStringAt(ac, x, y);
}

/*************************** End of file ****************************/
