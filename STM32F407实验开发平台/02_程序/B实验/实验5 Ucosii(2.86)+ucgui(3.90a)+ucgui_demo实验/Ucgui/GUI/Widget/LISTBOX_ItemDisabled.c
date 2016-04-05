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
File        : LISTBOX_ItemDisabled.c
Purpose     : Implementation of listbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "GUI_ARRAY.h"
#include "LISTBOX_Private.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTBOX_GetItemDisabled
*/
int LISTBOX_GetItemDisabled(LISTBOX_Handle hObj, unsigned Index) {
  int Ret = 0;
  if (hObj) {
    unsigned NumItems;
    LISTBOX_Obj* pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    NumItems = LISTBOX__GetNumItems(pObj);
    if (Index < NumItems) {
      WM_HMEM hItem = GUI_ARRAY_GethItem(&pObj->ItemArray, Index);
      if (hItem) {
        LISTBOX_ITEM * pItem = (LISTBOX_ITEM *)GUI_ALLOC_h2p(hItem);
        if (pItem->Status & LISTBOX_ITEM_DISABLED) {
          Ret = 1;
        }
      }
    }
    WM_UNLOCK();
  }
  return Ret;
}

/*********************************************************************
*
*       LISTBOX_SetItemDisabled
*/
void LISTBOX_SetItemDisabled(LISTBOX_Handle hObj, unsigned Index, int OnOff) {
  if (hObj) {
    unsigned NumItems;
    LISTBOX_Obj* pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    NumItems = LISTBOX__GetNumItems(pObj);
    if (Index < NumItems) {
      WM_HMEM hItem = GUI_ARRAY_GethItem(&pObj->ItemArray, Index);
      if (hItem) {
        LISTBOX_ITEM * pItem = (LISTBOX_ITEM *)GUI_ALLOC_h2p(hItem);
        if (OnOff) {
          if (!(pItem->Status & LISTBOX_ITEM_DISABLED)) {
            pItem->Status |= LISTBOX_ITEM_DISABLED;
            LISTBOX__InvalidateItem(hObj, pObj, Index);
          }
        } else {
          if (pItem->Status & LISTBOX_ITEM_DISABLED) {
            pItem->Status &= ~LISTBOX_ITEM_DISABLED;
            LISTBOX__InvalidateItem(hObj, pObj, Index);
          }
        }
      }
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_ItemDisabled_C(void) {}
#endif
