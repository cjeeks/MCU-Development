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
File        : SCROLLBAR_Create.c
Purpose     : Implementation of scrollbar widget
---------------------------END-OF-HEADER------------------------------
*/

#include "SCROLLBAR.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       SCROLLBAR_Create
*/
SCROLLBAR_Handle SCROLLBAR_Create (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int WinFlags, int SpecialFlags) {
  return SCROLLBAR_CreateEx(x0, y0, xsize, ysize, hParent, WinFlags, SpecialFlags, Id);
}

/*********************************************************************
*
*       SCROLLBAR_CreateAttached
*/
SCROLLBAR_Handle SCROLLBAR_CreateAttached(WM_HWIN hParent, int SpecialFlags) {
  SCROLLBAR_Handle  hThis;
  int Id;
  int WinFlags;
  if (SpecialFlags & SCROLLBAR_CF_VERTICAL) {
    Id = GUI_ID_VSCROLL;
    WinFlags = WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_ANCHOR_RIGHT | WM_CF_ANCHOR_TOP | WM_CF_ANCHOR_BOTTOM;
  } else {
    Id = GUI_ID_HSCROLL;
    WinFlags = WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_ANCHOR_BOTTOM | WM_CF_ANCHOR_LEFT | WM_CF_ANCHOR_RIGHT;
  }
  hThis = SCROLLBAR_CreateEx(0, 0, 0, 0, hParent, WinFlags, SpecialFlags, Id);
  WM_NotifyParent(hThis, WM_NOTIFICATION_SCROLLBAR_ADDED);
  return hThis;
}

#else  /* avoid empty object files */
  void SCROLLBAR_Create_C(void) {}
#endif
