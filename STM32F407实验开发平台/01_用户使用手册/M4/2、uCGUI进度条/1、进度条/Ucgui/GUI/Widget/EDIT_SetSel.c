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
File        : EDIT_SetSel.c
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
*       EDIT_SetSel
*/
void EDIT_SetSel(EDIT_Handle hObj, int FirstChar, int LastChar) {
  if (hObj) {
    EDIT_Obj* pObj;
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    if (FirstChar == -1) {
      pObj->SelSize = 0;
    } else {
      if (FirstChar > (pObj->BufferSize - 1)) {
        FirstChar = pObj->BufferSize - 1;
      }
      if (LastChar > (pObj->BufferSize - 1)) {
        LastChar = pObj->BufferSize - 1;
      }
      if (LastChar == -1) {
        LastChar = EDIT_GetNumChars(hObj);
      }
      if (LastChar >= FirstChar) {
        pObj->CursorPos = FirstChar;
        pObj->SelSize   = LastChar - FirstChar + 1;
      }
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void EDIT_SetSel_C(void);
void EDIT_SetSel_C(void) {}

#endif /* GUI_WINSUPPORT */


