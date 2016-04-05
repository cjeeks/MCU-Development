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
File        : GUI__AddSpaceHex.C
Purpose     : Internal function
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code (module internal)
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__AddSpaceHex
*/
void GUI__AddSpaceHex(U32 v, U8 Len, char** ps) {
  char* s = *ps;
  *s++ = ' ';
  *ps = s;
  GUI_AddHex(v, Len, ps);
}

/*************************** End of file ****************************/
