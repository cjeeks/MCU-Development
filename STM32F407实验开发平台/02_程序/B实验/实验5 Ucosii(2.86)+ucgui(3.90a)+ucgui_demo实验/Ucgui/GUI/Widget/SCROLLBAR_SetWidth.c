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
File        : SCROLLBAR_SetWidth.c
Purpose     : SCROLLBAR, optional routine
---------------------------END-OF-HEADER------------------------------
*/

#include "SCROLLBAR_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       SCROLLBAR_SetWidth
*/
int SCROLLBAR_SetWidth(SCROLLBAR_Handle hObj, int Width) {
  int r = 0;
  if (hObj) {
    WM_LOCK();
    r = WIDGET_SetWidth(hObj, Width);
    SCROLLBAR__InvalidatePartner(hObj);     /* Invalidate the partner, since it is also affected */
    WM_UNLOCK();
  }
  return r;
}




#else
  void SCROLLBAR_SetWidth_c(void) {}    /* Avoid empty object files */
#endif  /* #if GUI_WINSUPPORT */



