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
File        : DROPDOWN_DeleteItem.c
Purpose     : Implementation of dropdown widget
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
*       DROPDOWN_DeleteItem
*/
void DROPDOWN_DeleteItem(DROPDOWN_Handle hObj, unsigned int Index) {
  if (hObj) {
    DROPDOWN_Obj * pObj;
    unsigned int NumItems;
    NumItems = DROPDOWN_GetNumItems(hObj);
    if (Index < NumItems) {
      WM_LOCK();
      pObj = DROPDOWN_H2P(hObj);
      GUI_ARRAY_DeleteItem(&pObj->Handles, Index);
      WM_InvalidateWindow(hObj);
      if (pObj->hListWin) {
        LISTBOX_DeleteItem(pObj->hListWin, Index);
      }
      WM_UNLOCK();
    }
  }
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_DeleteItem_C(void);
  void DROPDOWN_DeleteItem_C(void) {}
#endif
