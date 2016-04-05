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
File        : DROPDOWN_ItemSpacing.c
Purpose     : Implementation of DROPDOWN_SetItemSpacing & DROPDOWN_GetItemSpacing
---------------------------END-OF-HEADER------------------------------
*/

#include "DROPDOWN_Private.h"
#include "LISTBOX.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/

/*********************************************************************
*
*       DROPDOWN_SetItemSpacing
*/
void DROPDOWN_SetItemSpacing(DROPDOWN_Handle hObj, unsigned Value) {
  if (hObj) {
    DROPDOWN_Obj* pObj;
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    pObj->ItemSpacing = Value;
    if (pObj->hListWin) {
      LISTBOX_SetItemSpacing(pObj->hListWin, Value);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       DROPDOWN_GetItemSpacing
*/
unsigned DROPDOWN_GetItemSpacing(DROPDOWN_Handle hObj) {
  unsigned Value = 0;
  if (hObj) {
    DROPDOWN_Obj* pObj;
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    Value = pObj->ItemSpacing;
    WM_UNLOCK();
  }
  return Value;
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_ItemSpacing_C(void);
  void DROPDOWN_ItemSpacing_C(void) {}
#endif
