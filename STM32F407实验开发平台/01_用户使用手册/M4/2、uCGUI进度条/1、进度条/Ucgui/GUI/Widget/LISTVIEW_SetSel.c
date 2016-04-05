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
File        : LISTVIEW_SetSel.c
Purpose     : Implementation of LISTVIEW_SetSel
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTVIEW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_SetSel
*/
void LISTVIEW_SetSel(LISTVIEW_Handle hObj, int NewSel) {
  if (hObj) {
    LISTVIEW_Obj* pObj;
    int MaxSel;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    MaxSel = GUI_ARRAY_GetNumItems(&pObj->RowArray) - 1;
    if (NewSel > MaxSel) {
      NewSel = MaxSel;
    }
    if (NewSel < 0) {
      NewSel = -1;
    }
    if (NewSel != pObj->Sel) {
      int OldSel;
      OldSel    = pObj->Sel;
      pObj->Sel = NewSel;
      if (LISTVIEW__UpdateScrollPos(hObj, pObj)) {
        LISTVIEW__InvalidateInsideArea(hObj, pObj);
      } else {
        LISTVIEW__InvalidateRow(hObj, pObj, OldSel);
        LISTVIEW__InvalidateRow(hObj, pObj, NewSel);
      }
      WM_NotifyParent(hObj, WM_NOTIFICATION_SEL_CHANGED);
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_SetSel_C(void);
  void LISTVIEW_SetSel_C(void) {}
#endif
