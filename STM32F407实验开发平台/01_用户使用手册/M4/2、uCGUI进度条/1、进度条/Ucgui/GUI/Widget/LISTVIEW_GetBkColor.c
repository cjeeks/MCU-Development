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
File        : LISTVIEW_GetBkColor.c
Purpose     : Implementation of LISTVIEW_GetBkColor
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
*       LISTVIEW_GetBkColor
*/
GUI_COLOR LISTVIEW_GetBkColor(LISTVIEW_Handle hObj, unsigned Index) {
  GUI_COLOR Color = GUI_INVALID_COLOR;
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    if (Index <= GUI_COUNTOF(pObj->Props.aBkColor)) {
      Color = pObj->Props.aBkColor[Index];
    }
    WM_UNLOCK();
  }
  return Color;
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_GetBkColor_C(void);
  void LISTVIEW_GetBkColor_C(void) {}
#endif
