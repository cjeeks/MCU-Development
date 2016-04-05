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
File        : WM_GetScrollbar.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*         Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_GetScrollbarH
*/
WM_HWIN WM_GetScrollbarH(WM_HWIN hWin) {
  return WM_GetDialogItem(hWin, GUI_ID_HSCROLL);
}

/*********************************************************************
*
*       WM_GetScrollbarV
*/
WM_HWIN WM_GetScrollbarV(WM_HWIN hWin) {
  return WM_GetDialogItem(hWin, GUI_ID_VSCROLL);
}

#else                                       /* Avoid empty object files */
  void WM_GetScrollbar_C(void) {}
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
