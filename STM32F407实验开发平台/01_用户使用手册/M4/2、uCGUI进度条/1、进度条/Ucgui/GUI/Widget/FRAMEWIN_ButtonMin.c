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
File        : FRAMEWIN_ButtonMin.c
Purpose     : 
---------------------------END-OF-HEADER------------------------------
*/


#include <stdlib.h>
#include <string.h>
#include "GUI_Protected.h"
#include "FRAMEWIN_Private.h"
#include "BUTTON.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       Callback
*
* This is the overwritten callback routine for the button.
* The primary reason for overwriting it is that we define the default
* action of the Framewindow here.
* It works as follows:
* - User clicks and releases the button
*   -> BUTTON sends WM_NOTIFY_PARENT to FRAMEWIN
*     -> FRAMEWIN either a) reacts or b)sends WM_NOTIFY_PARENT_REFLECTION back
*       In case of a) This module reacts !
*/
static void _cbMin(WM_MESSAGE* pMsg) {
  if (pMsg->MsgId == WM_NOTIFY_PARENT_REFLECTION) {
    WM_HWIN hWin = pMsg->hWinSrc;
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hWin);
    if (pObj->Flags & FRAMEWIN_SF_MINIMIZED) {
      FRAMEWIN_Restore(hWin);
    } else {
      FRAMEWIN_Minimize(hWin);
    }
    return;                                       /* We are done ! */
  }
  BUTTON_Callback(pMsg);
}

/*********************************************************************
*
*       _DrawMin
*/
static void _DrawMin(void) {
  GUI_RECT r;
  int i, Size;
  WM_GetInsideRect(&r);
  WM_ADDORG(r.x0, r.y0);
  WM_ADDORG(r.x1, r.y1);
  Size = (r.x1 - r.x0 + 1) >> 1;
  WM_ITERATE_START(&r); {
    for (i = 1; i < Size; i++) {
      LCD_DrawHLine(r.x0 + i, r.y1 - i - (Size >> 1), r.x1 - i);
    }
  } WM_ITERATE_END();
}

/*********************************************************************
*
*       _DrawRestore
*/
static void _DrawRestore(void) {
  GUI_RECT r;
  int i, Size;
  WM_GetInsideRect(&r);
  WM_ADDORG(r.x0, r.y0);
  WM_ADDORG(r.x1, r.y1);
  Size = (r.x1 - r.x0 + 1) >> 1;
  WM_ITERATE_START(&r); {
    for (i = 1; i < Size; i++) {
      LCD_DrawHLine(r.x0 + i, r.y0 + i + (Size >> 1), r.x1 - i);
    }
  } WM_ITERATE_END();
}

/*********************************************************************
*
*       _Draw
*/
static void _Draw(void) {
  FRAMEWIN_Obj* pObj;
  WM_HWIN hWin;
  hWin = WM_GetActiveWindow();
  hWin = WM_GetParent(hWin);
  pObj = FRAMEWIN_H2P(hWin);
  if (pObj->Flags & FRAMEWIN_SF_MINIMIZED) {
    _DrawRestore();
  } else {
    _DrawMin();
  }
}

/*********************************************************************
*
*        Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_AddMinButton
*/
WM_HWIN FRAMEWIN_AddMinButton(FRAMEWIN_Handle hObj, int Flags, int Off) {
  WM_HWIN hButton;
  hButton = FRAMEWIN_AddButton(hObj, Flags, Off, GUI_ID_MINIMIZE);
  BUTTON_SetSelfDraw(hButton, 0, &_Draw);
  WM_SetCallback(hButton, _cbMin);
  return hButton;
}

#else
  void FRAMEWIN_ButtonMin_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
