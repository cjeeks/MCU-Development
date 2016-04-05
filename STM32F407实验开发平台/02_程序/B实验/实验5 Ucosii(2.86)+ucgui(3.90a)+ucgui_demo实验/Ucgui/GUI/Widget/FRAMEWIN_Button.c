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
File        : FRAMEWIN_Button.c
Purpose     : 
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "FRAMEWIN_Private.h"
#include "BUTTON.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_AddButton
*/
WM_HWIN FRAMEWIN_AddButton(FRAMEWIN_Handle hObj, int Flags, int Off, int Id) {
  WM_HWIN r = 0;
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    POSITIONS Pos;
    int Size       = FRAMEWIN_GetTitleHeight(hObj);
    int BorderSize = FRAMEWIN_GetBorderSize(hObj);
    int WinFlags, x;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    FRAMEWIN__CalcPositions(pObj, &Pos);
    if (Flags & FRAMEWIN_BUTTON_RIGHT) {
      x = Pos.rTitleText.x1 - (Size - 1) - Off;
      WinFlags = WM_CF_SHOW | WM_CF_ANCHOR_RIGHT;
    } else {
      x = Pos.rTitleText.x0 + Off;
      WinFlags = WM_CF_SHOW;
    }
    r = BUTTON_CreateAsChild(x, BorderSize, Size, Size, hObj, Id, WinFlags);
    BUTTON_SetFocussable(r, 0);
    WM_UNLOCK();
  }
  return r;
}

#else
  void FRAMEWIN_Button_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
