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
File        : GUITOUCH_StoreState.C
Purpose     : Implementation of GUITOUCH_StoreState
----------------------------------------------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_TOUCH_StoreState
*
* NOTE:
*   This is the older version. Prefer GUI_TOUCH_StoreStateEx in new code
*/
void GUI_TOUCH_StoreState(int x, int y) {
  static GUI_PID_STATE _State;  /* static so we retain coordinates when touch is released */
  if ((x >= 0) && (y >= 0)) {
    _State.Pressed = 1;
    _State.x = x;
    _State.y = y;
  } else {
    _State.Pressed = 0;
  }
  GUI_TOUCH_StoreStateEx(&_State);
}

/*************************** End of file ****************************/
