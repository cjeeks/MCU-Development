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
File        : MULTIEDIT_Create.c
Purpose     : Implementation of multiedit widget
---------------------------END-OF-HEADER------------------------------
*/

#include "MULTIEDIT.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       MULTIEDIT_Create
*/
MULTIEDIT_HANDLE MULTIEDIT_Create(int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags, int ExFlags, const char * pText, int MaxLen) {
  return MULTIEDIT_CreateEx(x0, y0, xsize, ysize, hParent, Flags, ExFlags, Id, MaxLen, pText);
}

#else  /* avoid empty object files */
  void MULTIEDIT_Create_C(void) {}
#endif
