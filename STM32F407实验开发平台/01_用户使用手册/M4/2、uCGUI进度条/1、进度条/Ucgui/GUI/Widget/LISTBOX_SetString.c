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
File        : LISTBOX_SetString.c
Purpose     : Implementation of LISTBOX_SetString
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
*       LISTBOX_SetString
*/
void LISTBOX_SetString(LISTBOX_Handle hObj, const char* s, unsigned int Index) {
  if (hObj) {
    LISTBOX_Obj* pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    if (Index < (unsigned int)LISTBOX__GetNumItems(pObj)) {
      LISTBOX_ITEM* pItem;
      pItem = (LISTBOX_ITEM*)GUI_ARRAY_ResizeItem(&pObj->ItemArray, Index, sizeof(LISTBOX_ITEM) + strlen(s));
      if (pItem) {
        strcpy(pItem->acText, s);
        LISTBOX__InvalidateItemSize(pObj, Index);
        LISTBOX_UpdateScrollers(hObj);
        LISTBOX__InvalidateItem(hObj, pObj, Index);
      }
    }
    WM_UNLOCK();
  }
}


#else                            /* Avoid problems with empty object modules */
  void LISTBOX_SetString_C(void) {}
#endif
