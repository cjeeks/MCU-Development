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
File        : LISTBOX_DeleteItem.c
Purpose     : Implementation of LISTBOX_DeleteItem
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "LISTBOX_Private.h"

#if GUI_WINSUPPORT


/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/

/*********************************************************************
*
*       LISTBOX_DeleteItem
*/
void LISTBOX_DeleteItem(LISTBOX_Handle hObj, unsigned int Index) {
  if (hObj) {
    int Sel;
    LISTBOX_Obj* pObj;
    unsigned int NumItems;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    NumItems = LISTBOX__GetNumItems(pObj);
    if (Index < NumItems) {
      GUI_ARRAY_DeleteItem(&pObj->ItemArray, Index);
      /*
       * Update selection
       */
      Sel = pObj->Sel;
      if (Sel >= 0) {                     /* Valid selction ? */
        if ((int)Index == Sel) {          /* Deleting selected item ? */
          pObj->Sel = -1;                 /* Invalidate selection */
        } else if ((int)Index < Sel) {    /* Deleting item above selection ? */
          pObj->Sel--;
        }
      }
      if (LISTBOX_UpdateScrollers(hObj)) {
        LISTBOX__InvalidateInsideArea(hObj);
      } else {
        LISTBOX__InvalidateItemAndBelow(hObj, pObj, Index);
      }
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_DeleteString_C(void) {}
#endif
