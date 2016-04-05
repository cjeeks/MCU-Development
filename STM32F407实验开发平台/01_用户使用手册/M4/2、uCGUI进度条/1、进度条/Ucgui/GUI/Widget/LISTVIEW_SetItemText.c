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
File        : LISTVIEW_SetItemText.c
Purpose     : Implementation of LISTVIEW_SetItemText
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>

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
*       LISTVIEW_SetItemText
*/
void LISTVIEW_SetItemText(LISTVIEW_Handle hObj, unsigned Column, unsigned Row, const char * s) {
  if (hObj) {
    if ((Column < LISTVIEW_GetNumColumns(hObj)) && (Row < LISTVIEW_GetNumRows(hObj))) {
      int NumBytes;
      LISTVIEW_ITEM * pItem;
      LISTVIEW_Obj  * pObj;
      WM_LOCK();
      pObj = LISTVIEW_H2P(hObj);
      NumBytes = GUI__strlen(s) + 1;
      pItem = (LISTVIEW_ITEM *)GUI_ARRAY_ResizeItem((GUI_ARRAY *)GUI_ARRAY_GetpItem(&pObj->RowArray, Row), Column, sizeof(LISTVIEW_ITEM) + NumBytes);
      if (NumBytes > 1) {
        strcpy(pItem->acText, s);
      }
      LISTVIEW__InvalidateRow(hObj, pObj, Row);
      WM_UNLOCK();
    }
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_SetItemText_C(void);
  void LISTVIEW_SetItemText_C(void) {}
#endif
