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
File        : CHECKBOX_Create.c
Purpose     : Implementation of checkbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include "CHECKBOX.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       CHECKBOX_Create
*/
CHECKBOX_Handle CHECKBOX_Create(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags) {
  return CHECKBOX_CreateEx(x0, y0, xsize, ysize, hParent, Flags, 0, Id);
}

#else
  void CHECKBOX_Create_C(void) {}
#endif  /* #if GUI_WINSUPPORT */



