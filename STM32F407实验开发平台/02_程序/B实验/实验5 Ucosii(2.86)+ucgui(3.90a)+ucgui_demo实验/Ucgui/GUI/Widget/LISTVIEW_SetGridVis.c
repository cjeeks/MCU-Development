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
File        : LISTVIEW_SetGridVis.c
Purpose     : Implementation of LISTVIEW_SetGridVis
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
*       LISTVIEW_SetGridVis
*/
int LISTVIEW_SetGridVis(LISTVIEW_Handle hObj, int Show) {
  int ShowGrid = 0;
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj     = LISTVIEW_H2P(hObj);
    ShowGrid = pObj->ShowGrid;
    if (Show != ShowGrid) {
      pObj->ShowGrid = Show;
      LISTVIEW__UpdateScrollParas(hObj, pObj);
      LISTVIEW__InvalidateInsideArea(hObj, pObj);
    }
    WM_UNLOCK();
  }
  return ShowGrid;
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_SetGridVis_C(void);
  void LISTVIEW_SetGridVis_C(void) {}
#endif
