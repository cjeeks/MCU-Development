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
File        : GUI_PID.C
Purpose     : PID (Pointer input device) management
----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Protected.h"

#if GUI_WINSUPPORT
  #include "WM.h"
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static GUI_PID_STATE _State;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _PID_Load
*
* Purpose:
*   If the window manager is available, write the function pointer for
*   the PID handler.
*/
static void _PID_Load(void) {
  #if (GUI_WINSUPPORT)
    WM_pfHandlePID = WM_HandlePID;
  #endif
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_PID_GetState
*/
int GUI_PID_GetState(GUI_PID_STATE *pState) {
  *pState = _State;
  return (pState->Pressed != 0) ? 1 : 0;
}

/*********************************************************************
*
*       GUI_PID_StoreState
*/
void GUI_PID_StoreState(const GUI_PID_STATE *pState) {
  _PID_Load();
  if (memcmp(&_State, pState, sizeof(_State))) {
    _State = *pState;
    GUI_X_SIGNAL_EVENT();
  }
}

/*************************** End of file ****************************/
