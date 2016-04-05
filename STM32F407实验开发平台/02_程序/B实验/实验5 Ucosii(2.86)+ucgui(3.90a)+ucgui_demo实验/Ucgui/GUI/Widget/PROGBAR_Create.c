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
File        : PROGBAR_Create.c
Purpose     : Implementation of progbar widget
---------------------------END-OF-HEADER------------------------------
*/

#include "PROGBAR.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       PROGBAR_Create
*/
PROGBAR_Handle PROGBAR_Create(int x0, int y0, int xsize, int ysize, int Flags) {
  return PROGBAR_CreateEx(x0, y0, xsize, ysize, 0, Flags, 0, 0);
}

/*********************************************************************
*
*       PROGBAR_CreateAsChild
*/
PROGBAR_Handle PROGBAR_CreateAsChild(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags) {
  return PROGBAR_CreateEx(x0, y0, xsize, ysize, hParent, Flags, 0, Id);
}

#else  /* avoid empty object files */
  void PROGBAR_Create_C(void) {}
#endif
