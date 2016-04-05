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
File        : WM_GetBkColor.c
Purpose     : Windows manager, submodule
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
*       WM_GetBkColor
*
  Purpose:
    Return the clients background color.
    If a window does not define a background color, the default
    procedure returns GUI_INVALID_COLOR
*/
GUI_COLOR WM_GetBkColor(WM_HWIN hObj) {
  if (hObj) {
    WM_MESSAGE Msg;
    Msg.MsgId  = WM_GET_BKCOLOR;
    WM_SendMessage(hObj, &Msg);
    return Msg.Data.Color;
  }
  return GUI_INVALID_COLOR;
}

#else
  void WM_GetBkColor_C(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
