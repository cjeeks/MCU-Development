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
File        : TEXT_SetText.c
Purpose     : Implementation of TEXT_SetText
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "TEXT.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       TEXT_SetText
*/
void TEXT_SetText(TEXT_Handle hObj, const char* s) {
  if (hObj) {
    TEXT_Obj* pObj;
    WM_LOCK();
    pObj = TEXT_H2P(hObj);
    if (GUI__SetText(&pObj->hpText, s)) {
      WM_Invalidate(hObj);
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void TEXT_SetText_c(void);
void TEXT_SetText_c(void){}

#endif  /* #if GUI_WINSUPPORT */


