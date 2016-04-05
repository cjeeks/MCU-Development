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
File        : EDIT_GetNumChars.c
Purpose     : Implementation of edit widget
---------------------------END-OF-HEADER------------------------------
*/

#include "EDIT.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_GetNumChars
*/
int EDIT_GetNumChars(EDIT_Handle hObj) {
  int NumChars = 0;
  if (hObj) {
    EDIT_Obj* pObj;
    WM_LOCK();
    pObj = EDIT_H2P(hObj);
    if (pObj->hpText) {
      char * pText;
      pText    = (char*) GUI_ALLOC_h2p(pObj->hpText);
      NumChars = GUI__GetNumChars(pText);
    }
    WM_UNLOCK();
  }
  return NumChars;
}

#else  /* avoid empty object files */

void EDIT_GetNumChars_C(void);
void EDIT_GetNumChars_C(void) {}

#endif /* GUI_WINSUPPORT */


