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
File        : GUITOUCH.C
Purpose     : Generic touch screen routines
----------------------------------------------------------------------
*/

#include <string.h>
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static GUI_PID_STATE _State;

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_TOUCH_GetState
*/
int GUI_TOUCH_GetState(GUI_PID_STATE *pState) {
  *pState = _State;
  return (_State.Pressed != 0) ? 1 : 0;
}

/*********************************************************************
*
*       GUI_TOUCH_StoreStateEx
*/
void GUI_TOUCH_StoreStateEx(const GUI_PID_STATE *pState) {
  if (memcmp(pState, &_State, sizeof(_State))) {
    _State = *pState;
    GUI_PID_StoreState(pState);
  }
}

/*************************** End of file ****************************/
