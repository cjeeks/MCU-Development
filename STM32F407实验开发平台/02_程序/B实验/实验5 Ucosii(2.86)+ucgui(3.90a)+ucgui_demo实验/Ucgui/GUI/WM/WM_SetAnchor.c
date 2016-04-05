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
File        : WM_SetAnchor.c
Purpose     : Windows manager, implementation of said function
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetAnchor
*/
void WM_SetAnchor(WM_HWIN hWin, U16 AnchorFlags) {
  if (hWin) {
    WM_Obj* pWin;
    U16 Mask;
    WM_LOCK();
    pWin = WM_H2P(hWin);
    Mask = (WM_SF_ANCHOR_LEFT | WM_SF_ANCHOR_RIGHT | WM_SF_ANCHOR_TOP | WM_SF_ANCHOR_BOTTOM);

    GUI_DEBUG_WARN_IF(AnchorFlags & ~(Mask), "WM_SetAnchor.c: Wrong anchor flags");
    #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_PARA
      AnchorFlags &= Mask;
    #endif

    pWin->Status &= ~(Mask);
    pWin->Status |= AnchorFlags;
    WM_UNLOCK();
  }
}

#else
  void WM_SetAnchor_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
