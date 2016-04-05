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
File        : BUTTON_Create.c
Purpose     : Implementation of button widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "BUTTON_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_Create
*/
BUTTON_Handle BUTTON_Create(int x0, int y0, int xsize, int ysize, int Id, int Flags) {
  return BUTTON_CreateEx(x0, y0, xsize, ysize, WM_HMEM_NULL, Flags, 0, Id);
}

/*********************************************************************
*
*       BUTTON_CreateAsChild
*/
BUTTON_Handle BUTTON_CreateAsChild (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags) {
  return BUTTON_CreateEx(x0, y0, xsize, ysize, hParent, Flags, 0, Id);
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_Create_C(void) {}
#endif /* GUI_WINSUPPORT */




