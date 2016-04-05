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
File        : DROPDOWN_InsertString.c
Purpose     : Implementation of dropdown widget
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "DROPDOWN.h"
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
*       DROPDOWN_InsertString
*/
void DROPDOWN_InsertString(DROPDOWN_Handle hObj, const char * s, unsigned int Index) {
  if (hObj && s) {
    DROPDOWN_Obj* pObj;
    unsigned int NumItems;
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    NumItems = DROPDOWN_GetNumItems(hObj);
    if (Index < NumItems) {
      WM_HMEM hItem;
      hItem = GUI_ARRAY_InsertItem(&pObj->Handles, Index, strlen(s) + 1);
      if (hItem) {
        char * pBuffer = (char *)GUI_ALLOC_h2p(hItem);
        strcpy(pBuffer, s);
      }
      WM_InvalidateWindow(hObj);
      if (pObj->hListWin) {
        LISTBOX_InsertString(pObj->hListWin, s, Index);
      }
    } else {
      DROPDOWN_AddString(hObj, s);
      if (pObj->hListWin) {
        LISTBOX_AddString(pObj->hListWin, s);
      }
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_InsertString_C(void);
  void DROPDOWN_InsertString_C(void) {}
#endif
