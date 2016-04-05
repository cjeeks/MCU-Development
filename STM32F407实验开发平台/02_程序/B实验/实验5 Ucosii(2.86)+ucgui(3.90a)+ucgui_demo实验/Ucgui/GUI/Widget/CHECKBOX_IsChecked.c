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
File        : CHECKBOX_IsChecked.c
Purpose     : Implementation of CHECKBOX_IsChecked
---------------------------END-OF-HEADER------------------------------
*/

#include "CHECKBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       CHECKBOX_IsChecked
*/
int CHECKBOX_IsChecked(CHECKBOX_Handle hObj) {
  return (CHECKBOX_GetState(hObj) == 1) ? 1 : 0;
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_IsChecked_C(void);
  void CHECKBOX_IsChecked_C(void) {}
#endif
