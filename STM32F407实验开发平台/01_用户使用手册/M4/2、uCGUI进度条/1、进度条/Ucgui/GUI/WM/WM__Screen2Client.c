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
File        : WM__Screen2Client.c
Purpose     : Implementation of WM__Screen2Client
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__Screen2Client
*/
void WM__Screen2Client(const WM_Obj* pWin, GUI_RECT *pRect) {
  GUI_MoveRect(pRect, -pWin->Rect.x0, -pWin->Rect.y0);
}

#else
  void WM__Screen2Client_c(void);
  void WM__Screen2Client_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
