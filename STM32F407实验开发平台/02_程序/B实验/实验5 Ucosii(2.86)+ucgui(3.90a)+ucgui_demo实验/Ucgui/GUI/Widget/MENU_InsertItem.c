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
File        : MENU_InsertItem.c
Purpose     : Implementation of menu widget
---------------------------END-OF-HEADER------------------------------
*/

#include "MENU.h"
#include "MENU_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU_InsertItem
*/
void MENU_InsertItem(MENU_Handle hObj, U16 ItemId, const MENU_ITEM_DATA* pItemData) {
  if (hObj && pItemData) {
    int Index;
    WM_LOCK();
    Index = MENU__FindItem(hObj, ItemId, &hObj);
    if (Index >= 0) {
      MENU_Obj* pObj;
      pObj = MENU_H2P(hObj);
      if (GUI_ARRAY_InsertBlankItem(&pObj->ItemArray, Index) != 0) {
        if (MENU__SetItem(hObj, pObj, Index, pItemData) == 0) {
          GUI_ARRAY_DeleteItem(&pObj->ItemArray, Index);
        } else {
          MENU__ResizeMenu(hObj, pObj);
        }
      }
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void MENU_InsertItem_C(void) {}
#endif

/*************************** End of file ****************************/
