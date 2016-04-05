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
File        : CHECKBOX_SetText.c
Purpose     : Implementation of CHECKBOX_SetText
---------------------------END-OF-HEADER------------------------------
*/

#include "CHECKBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       CHECKBOX_SetText
*/
void CHECKBOX_SetText(CHECKBOX_Handle hObj, const char * s) {
  CHECKBOX_Obj * pObj;
  if (hObj && s) {
    WM_LOCK();
    pObj = CHECKBOX_H2P(hObj);
    if (GUI__SetText(&pObj->hpText, s)) {
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_SetText_C(void);
  void CHECKBOX_SetText_C(void) {}
#endif
