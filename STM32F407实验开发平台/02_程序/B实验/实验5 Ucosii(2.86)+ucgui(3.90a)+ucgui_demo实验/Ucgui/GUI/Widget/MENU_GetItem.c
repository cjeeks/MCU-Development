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
File        : MENU_GetItem.c
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
*       MENU_GetItem
*/
void MENU_GetItem(MENU_Handle hObj, U16 ItemId, MENU_ITEM_DATA* pItemData) {
  if (hObj && pItemData) {
    int Index;
    WM_LOCK();
    Index = MENU__FindItem(hObj, ItemId, &hObj);
    if (Index >= 0) {
      MENU_Obj*  pObj;
      MENU_ITEM* pItem;
      pObj  = MENU_H2P(hObj);
      pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
      pItemData->Flags    = pItem->Flags;
      pItemData->Id       = pItem->Id;
      pItemData->hSubmenu = pItem->hSubmenu;
      pItemData->pText    = 0;
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void MENU_GetItem_C(void) {}
#endif

/*************************** End of file ****************************/
