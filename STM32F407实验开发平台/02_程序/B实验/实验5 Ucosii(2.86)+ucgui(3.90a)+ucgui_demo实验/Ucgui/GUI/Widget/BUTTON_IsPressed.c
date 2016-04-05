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
File        : BUTTON_IsPressed.c
Purpose     : Button widget, various (optional) Get routines
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "BUTTON.h"
#include "BUTTON_Private.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_IsPressed
*/
unsigned BUTTON_IsPressed(BUTTON_Handle hObj) {
  unsigned r = 0;
  if (hObj) {
    BUTTON_Obj* pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    r = (pObj->Widget.State & BUTTON_STATE_PRESSED) ? 1 : 0;
    WM_UNLOCK();
  }
  return r;
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_IsPressed_C(void) {}
#endif
