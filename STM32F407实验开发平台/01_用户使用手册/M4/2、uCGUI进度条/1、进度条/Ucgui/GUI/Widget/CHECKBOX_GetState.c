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
File        : CHECKBOX_GetState.c
Purpose     : Implementation of CHECKBOX_GetState
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
*       CHECKBOX_GetState
*/
int CHECKBOX_GetState(CHECKBOX_Handle hObj) {
  int Result = 0;
  CHECKBOX_Obj * pObj;
  if (hObj) {
    WM_LOCK();
    pObj = CHECKBOX_H2P(hObj);
    Result = pObj->CurrentState;
    WM_UNLOCK();
  }
  return Result;
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_GetState_C(void);
  void CHECKBOX_GetState_C(void) {}
#endif
