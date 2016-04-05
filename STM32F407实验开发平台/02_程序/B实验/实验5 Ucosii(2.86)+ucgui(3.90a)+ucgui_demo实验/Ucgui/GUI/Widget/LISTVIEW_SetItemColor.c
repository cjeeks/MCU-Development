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
File        : LISTVIEW_SetItemColor.c
Purpose     : Implementation of LISTVIEW_SetItemTextColor and LISTVIEW_SetItemBkColor
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>

#include "LISTVIEW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       _GetpItemInfo
*/
static LISTVIEW_ITEM_INFO * _GetpItemInfo(LISTVIEW_Handle hObj, unsigned Column, unsigned Row, unsigned int Index) {
  LISTVIEW_ITEM_INFO * pItemInfo = 0;
  LISTVIEW_ITEM      * pItem;
  LISTVIEW_Obj       * pObj;
  if (hObj) {
    if ((Column < LISTVIEW_GetNumColumns(hObj)) && (Row < LISTVIEW_GetNumRows(hObj)) && (Index < GUI_COUNTOF(pItemInfo->aTextColor))) {
      pObj = LISTVIEW_H2P(hObj);
      pItem = (LISTVIEW_ITEM *)GUI_ARRAY_GetpItem((GUI_ARRAY *)GUI_ARRAY_GetpItem(&pObj->RowArray, Row), Column);
      if (!pItem->hItemInfo) {
        int i;
        pItem->hItemInfo = GUI_ALLOC_AllocZero(sizeof(LISTVIEW_ITEM_INFO));
        pItemInfo = (LISTVIEW_ITEM_INFO *)GUI_ALLOC_h2p(pItem->hItemInfo);
        for (i = 0; i < GUI_COUNTOF(pItemInfo->aTextColor); i++) {
          pItemInfo->aTextColor[i] = LISTVIEW_GetTextColor(hObj, i);
          pItemInfo->aBkColor[i]   = LISTVIEW_GetBkColor  (hObj, i);
        }
      } else {
        pItemInfo = (LISTVIEW_ITEM_INFO *)GUI_ALLOC_h2p(pItem->hItemInfo);
      }
    }
  }
  return pItemInfo;
}

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_SetItemTextColor
*/
void LISTVIEW_SetItemTextColor(LISTVIEW_Handle hObj, unsigned Column, unsigned Row, unsigned int Index, GUI_COLOR Color) {
  LISTVIEW_ITEM_INFO * pItemInfo;
  WM_LOCK();
  pItemInfo = _GetpItemInfo(hObj, Column, Row, Index);
  if (pItemInfo) {
    pItemInfo->aTextColor[Index] = Color;
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       LISTVIEW_SetItemBkColor
*/
void LISTVIEW_SetItemBkColor(LISTVIEW_Handle hObj, unsigned Column, unsigned Row, unsigned int Index, GUI_COLOR Color) {
  LISTVIEW_ITEM_INFO * pItemInfo;
  WM_LOCK();
  pItemInfo = _GetpItemInfo(hObj, Column, Row, Index);
  if (pItemInfo) {
    pItemInfo->aBkColor[Index] = Color;
  }
  WM_UNLOCK();
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_SetItemColor_C(void);
  void LISTVIEW_SetItemColor_C(void) {}
#endif
