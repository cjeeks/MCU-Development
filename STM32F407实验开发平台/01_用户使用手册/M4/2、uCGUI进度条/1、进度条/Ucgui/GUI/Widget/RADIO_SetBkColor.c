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
File        : RADIO_SetBkColor.c
Purpose     : Implementation of RADIO_SetBkColor
---------------------------END-OF-HEADER------------------------------
*/

#include "RADIO_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       RADIO_SetBkColor
*/
void RADIO_SetBkColor(RADIO_Handle hObj, GUI_COLOR Color) {
  if (hObj) {
    RADIO_Obj* pObj;
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    if (Color != pObj->BkColor) {
      pObj->BkColor = Color;
      #if WM_SUPPORT_TRANSPARENCY
        if (Color <= 0xFFFFFF) {
          WM_SetTransState(hObj, 0);
        } else {
          WM_SetTransState(hObj, WM_CF_HASTRANS);
        }
      #endif
      WM_InvalidateWindow(hObj);
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void RADIO_SetBkColor_c(void);
void RADIO_SetBkColor_c(void) {}

#endif  /* #if GUI_WINSUPPORT */

/************************* end of file ******************************/
