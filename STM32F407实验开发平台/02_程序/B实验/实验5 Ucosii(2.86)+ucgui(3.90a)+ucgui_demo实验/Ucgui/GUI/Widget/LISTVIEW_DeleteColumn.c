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
File        : LISTVIEW_DeleteColumn.c
Purpose     : Implementation of LISTVIEW_DeleteColumn
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
*       LISTVIEW_DeleteColumn
*/
void LISTVIEW_DeleteColumn(LISTVIEW_Handle hObj, unsigned Index) {
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    if (Index < GUI_ARRAY_GetNumItems(&pObj->AlignArray)) {
      unsigned NumRows, i;
      GUI_ARRAY* pRow;
      HEADER_DeleteItem(pObj->hHeader, Index);
      GUI_ARRAY_DeleteItem(&pObj->AlignArray, Index);
      NumRows = GUI_ARRAY_GetNumItems(&pObj->RowArray);
      for (i = 0; i < NumRows; i++) {
        LISTVIEW_ITEM * pItem;
        pRow = (GUI_ARRAY*)GUI_ARRAY_GetpItem(&pObj->RowArray, i);
        /* Delete attached info items */
        pItem = (LISTVIEW_ITEM *)GUI_ARRAY_GetpItem(pRow, Index);
        if (pItem->hItemInfo) {
          GUI_ALLOC_Free(pItem->hItemInfo);
        }
        /* Delete cell */
        GUI_ARRAY_DeleteItem(pRow, Index);
      }
      LISTVIEW__UpdateScrollParas(hObj, pObj);
      LISTVIEW__InvalidateInsideArea(hObj, pObj);
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_DeleteColumn_C(void);
  void LISTVIEW_DeleteColumn_C(void) {}
#endif
