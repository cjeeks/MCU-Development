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
File        : WINDOW.c
Purpose     : Window routines
---------------------------END-OF-HEADER------------------------------
*/

#include "DIALOG.h"
#include "WINDOW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       WINDOW_SetDefaultBkColor
*/
void WINDOW_SetDefaultBkColor(GUI_COLOR Color) {
  WINDOW__DefaultBkColor = Color;
}

#else
  void WINDOW_Default_C(void);
  void WINDOW_Default_C(void) {} /* avoid empty object files */
#endif
