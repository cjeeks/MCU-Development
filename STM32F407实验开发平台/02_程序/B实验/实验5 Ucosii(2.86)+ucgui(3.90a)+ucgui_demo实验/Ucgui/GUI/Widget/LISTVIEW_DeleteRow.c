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
File        : LISTVIEW_DeleteRow.c
Purpose     : Implementation of LISTVIEW_DeleteRow
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTVIEW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _InvalidateRowAndBelow
*/
static void _InvalidateRowAndBelow(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, int Sel) {
  if (Sel >= 0) {
    GUI_RECT Rect;
    int HeaderHeight, RowDistY;
    HeaderHeight = HEADER_GetHeight(pObj->hHeader);
    RowDistY     = LISTVIEW__GetRowDistY(pObj);
    WM_GetInsideRectExScrollbar(hObj, &Rect);
    Rect.y0 += HeaderHeight + (Sel - pObj->ScrollStateV.v) * RowDistY;
    WM_InvalidateRect(hObj, &Rect);
  }
}

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_DeleteRow
*/
void LISTVIEW_DeleteRow(LISTVIEW_Handle hObj, unsigned Index) {
  if (hObj) {
    LISTVIEW_Obj* pObj;
    unsigned NumRows;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    NumRows = GUI_ARRAY_GetNumItems(&pObj->RowArray);
    if (Index < NumRows) {
      unsigned NumColumns, i;
      GUI_ARRAY* pRow;
      pRow = (GUI_ARRAY*)GUI_ARRAY_GetpItem(&pObj->RowArray, Index);
      /* Delete attached info items */
      NumColumns = GUI_ARRAY_GetNumItems(pRow);
      for (i = 0; i < NumColumns; i++) {
        LISTVIEW_ITEM * pItem;
        pItem = (LISTVIEW_ITEM *)GUI_ARRAY_GetpItem(pRow, i);
        if (pItem->hItemInfo) {
          GUI_ALLOC_Free(pItem->hItemInfo);
        }
      }
      /* Delete row */
      GUI_ARRAY_Delete(pRow);
      GUI_ARRAY_DeleteItem(&pObj->RowArray, Index);
      /* Adjust properties */
      if (pObj->Sel == (signed int)Index) {
        pObj->Sel = -1;
      }
      if (pObj->Sel > (signed int)Index) {
        pObj->Sel--;
      }
      if (LISTVIEW__UpdateScrollParas(hObj, pObj)) {
        LISTVIEW__InvalidateInsideArea(hObj, pObj);
      } else {
        _InvalidateRowAndBelow(hObj, pObj, Index);
      }
    }
    WM_UNLOCK();
  }
}


#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_DeleteRow_C(void);
  void LISTVIEW_DeleteRow_C(void) {}
#endif
