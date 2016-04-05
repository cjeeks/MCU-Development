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
File        : LISTVIEW_SetColumnWidth.c
Purpose     : Implementation of LISTVIEW_SetColumnWidth
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
*       LISTVIEW_SetColumnWidth
*/
void LISTVIEW_SetColumnWidth(LISTVIEW_Handle hObj, unsigned int Index, int Width) {
  if (hObj) {
    LISTVIEW_Obj * pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    HEADER_SetItemWidth(pObj->hHeader, Index, Width);
    WM_UNLOCK();
  }
}


#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_SetColumnWidth_C(void);
  void LISTVIEW_SetColumnWidth_C(void) {}
#endif
