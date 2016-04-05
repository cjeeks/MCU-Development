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
File        : LISTBOX_InsertString.c
Purpose     : Implementation of LISTBOX_InsertString
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
*       LISTBOX_InsertString
*/
void LISTBOX_InsertString(LISTBOX_Handle hObj, const char* s, unsigned int Index) {
  if (hObj && s) {
    LISTBOX_Obj* pObj;
    unsigned int NumItems;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    NumItems = LISTBOX__GetNumItems(pObj);
    if (Index < NumItems) {
      WM_HMEM hItem;
      hItem = GUI_ARRAY_InsertItem(&pObj->ItemArray, Index, sizeof(LISTBOX_ITEM) + strlen(s));
      if (hItem) {
        LISTBOX_ITEM* pItem = (LISTBOX_ITEM*)GUI_ALLOC_h2p(hItem);
        pItem->Status = 0;
        strcpy(pItem->acText, s);
        LISTBOX_InvalidateItem(hObj, Index);
      }
    } else {
      LISTBOX_AddString(hObj, s);
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_InsertString_C(void) {}
#endif
