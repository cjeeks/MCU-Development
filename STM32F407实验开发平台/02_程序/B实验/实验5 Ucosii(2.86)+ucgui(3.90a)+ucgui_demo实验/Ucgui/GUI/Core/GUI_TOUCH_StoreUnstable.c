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
File        : GUITOUCH_StoreUnstable.C
Purpose     : Implementation of GUITOUCH_StoreUnstable
----------------------------------------------------------------------
*/

#include <stdlib.h>
#include "GUI_Protected.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static int _x, _y;

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_TOUCH_StoreUnstable
*/
void GUI_TOUCH_StoreUnstable(int x, int y) {
  int xDiff, yDiff;
  xDiff = abs (x - _x);
  yDiff = abs (y - _y);
  if (xDiff + yDiff > 2) {
    _x = x;
    _y = y;
    GUI_TOUCH_StoreState(x, y);
  }
}

/*********************************************************************
*
*       GUI_TOUCH_GetUnstable
*/
void GUI_TOUCH_GetUnstable(int* px, int* py) {
  *px = _x;
  *py = _y;
}

/*************************** End of file ****************************/
