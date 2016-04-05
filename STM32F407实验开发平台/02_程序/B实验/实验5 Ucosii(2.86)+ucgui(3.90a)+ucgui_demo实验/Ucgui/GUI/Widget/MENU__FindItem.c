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
File        : MENU__FindItem.c
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
*       MENU__FindItem
*/
int MENU__FindItem(MENU_Handle hObj, U16 ItemId, MENU_Handle* phMenu) {
  int ItemIndex = -1;
  MENU_Obj* pObj;
  pObj = MENU_H2P(hObj);
  if (pObj) {
    MENU_ITEM* pItem;
    unsigned NumItems, i;
    NumItems = MENU__GetNumItems(pObj);
    for (i = 0; (i < NumItems) && (ItemIndex < 0); i++) {
      pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, i);
      if (pItem->Id == ItemId) {
        *phMenu   = hObj;
        ItemIndex = i;
      } else if (pItem->hSubmenu) {
        ItemIndex = MENU__FindItem(pItem->hSubmenu, ItemId, phMenu);
      }
    }
  }
  return ItemIndex;
}

#else  /* avoid empty object files */
  void MENU__FindItem_C(void) {}
#endif

/*************************** End of file ****************************/
