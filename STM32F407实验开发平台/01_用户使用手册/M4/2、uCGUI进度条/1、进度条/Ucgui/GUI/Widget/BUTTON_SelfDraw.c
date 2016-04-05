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
File        : BUTTON_SelfDraw.c
Purpose     : Button self draw support
---------------------------END-OF-HEADER------------------------------
*/

#include "BUTTON.h"
#include "BUTTON_Private.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_SetSelfDrawEx
*/
void BUTTON_SetSelfDrawEx(BUTTON_Handle hObj,unsigned int Index, GUI_DRAW_SELF_CB* pDraw, int x, int y) {
  BUTTON__SetDrawObj(hObj, Index, GUI_DRAW_SELF_Create(pDraw, x, y));
}

/*********************************************************************
*
*       BUTTON_SetSelfDraw
*/
void BUTTON_SetSelfDraw(BUTTON_Handle hObj,unsigned int Index, GUI_DRAW_SELF_CB* pDraw) {
  BUTTON_SetSelfDrawEx(hObj, Index, pDraw, 0, 0);
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_SelfDraw_C(void) {}
#endif
