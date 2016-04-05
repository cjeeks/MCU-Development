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
File        : EDIT_SetpfAddKeyEx.c
Purpose     : Implementation of edit widget
---------------------------END-OF-HEADER------------------------------
*/

#include "EDIT.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_SetpfAddKeyEx
*/
void EDIT_SetpfAddKeyEx(EDIT_Handle hObj, tEDIT_AddKeyEx * pfAddKeyEx) {
  if (hObj) {
    EDIT_Obj* pObj;
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    pObj->pfAddKeyEx = pfAddKeyEx;
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void EDIT_SetpfAddKeyEx_C(void);
void EDIT_SetpfAddKeyEx_C(void) {}

#endif /* GUI_WINSUPPORT */


