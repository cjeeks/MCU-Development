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
File        : LISTVIEW_GetNumColumns.c
Purpose     : Implementation of LISTVIEW_GetNumColumns
---------------------------END-OF-HEADER------------------------------
*/

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
*       LISTVIEW_GetNumColumns
*/
unsigned LISTVIEW_GetNumColumns(LISTVIEW_Handle hObj) {
  unsigned NumColumns = 0;
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    NumColumns = GUI_ARRAY_GetNumItems(&pObj->AlignArray);
    WM_UNLOCK();
  }
  return NumColumns;
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_GetNumColumns_C(void);
  void LISTVIEW_GetNumColumns_C(void) {}
#endif
