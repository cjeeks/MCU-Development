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
File        : EDIT_SetCursorAtChar.c
Purpose     : Implementation of EDIT_SetCursorAtChar
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>

#include "EDIT.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
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
*       EDIT_SetCursorAtChar
*/
void EDIT_SetCursorAtChar(EDIT_Handle hObj, int Pos) {
  if (hObj) {
    EDIT_Obj* pObj;
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    EDIT__SetCursorPos(pObj, Pos);
    EDIT_Invalidate(hObj);
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void EDIT_SetCursorAtChar_C(void);
void EDIT_SetCursorAtChar_C(void){}

#endif /* GUI_WINSUPPORT */
