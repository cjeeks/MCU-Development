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
File        : FRAMEWIN_SetColors.c
Purpose     : Implementation of framewindow widget
---------------------------END-OF-HEADER------------------------------
*/

#include "FRAMEWIN_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Exported routines:  Set Properties
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_SetBarColor
*/
void FRAMEWIN_SetBarColor(FRAMEWIN_Handle hObj, unsigned Index, GUI_COLOR Color) {
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    GUI_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aBarColor)) {
      pObj->Props.aBarColor[Index] = Color;
      FRAMEWIN_Invalidate(hObj);
    }
    GUI_UNLOCK();
  }
}

/*********************************************************************
*
*       FRAMEWIN_SetTextColor
*/
void FRAMEWIN_SetTextColor(FRAMEWIN_Handle hObj, GUI_COLOR Color) {
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    int i;
    GUI_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    for (i = 0; i < GUI_COUNTOF(pObj->Props.aTextColor); i++) {
      pObj->Props.aTextColor[i] = Color;
    }
    FRAMEWIN_Invalidate(hObj);
    GUI_UNLOCK();
  }
}

/*********************************************************************
*
*       FRAMEWIN_SetTextColorEx
*/
void FRAMEWIN_SetTextColorEx(FRAMEWIN_Handle hObj, unsigned Index, GUI_COLOR Color) {
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    GUI_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (Index < GUI_COUNTOF(pObj->Props.aTextColor)) {
      pObj->Props.aTextColor[Index] = Color;
      FRAMEWIN_Invalidate(hObj);
    }
    GUI_UNLOCK();
  }
}

/*********************************************************************
*
*       FRAMEWIN_SetClientColor
*/
void FRAMEWIN_SetClientColor(FRAMEWIN_Handle hObj, GUI_COLOR Color) {
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    GUI_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (pObj->Props.ClientColor != Color) {
      pObj->Props.ClientColor = Color;
      FRAMEWIN_Invalidate(pObj->hClient);
    }
    GUI_UNLOCK();
  }
}

#else
  void FRAMEWIN_SetColors_C(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
