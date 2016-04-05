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
File        : FRAMEWIN_ButtonClose.c
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
static void _cbClose(WM_MESSAGE* pMsg) {
  if (pMsg->MsgId == WM_NOTIFY_PARENT_REFLECTION) {
    WM_DeleteWindow(pMsg->hWinSrc);
    return;                                       /* We are done ! */
  }
  BUTTON_Callback(pMsg);
}

/*********************************************************************
*
*       _Draw
*/
static void _Draw(void) {
  GUI_RECT r;
  int i, Size;
  WM_GetInsideRect(&r);
  WM_ADDORG(r.x0, r.y0);
  WM_ADDORG(r.x1, r.y1);
  Size = r.x1 - r.x0 - 2;
  WM_ITERATE_START(&r); {
    for (i = 2; i < Size; i++) {
      LCD_DrawHLine(r.x0 + i,     r.y0 + i, r.x0 + i + 1);
      LCD_DrawHLine(r.x1 - i - 1, r.y0 + i, r.x1 - i);
    }
  } WM_ITERATE_END();
}


/*********************************************************************
*
*        Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_AddCloseButton
*/
WM_HWIN FRAMEWIN_AddCloseButton(FRAMEWIN_Handle hObj, int Flags, int Off) {
  WM_HWIN hButton;
  hButton = FRAMEWIN_AddButton(hObj, Flags, Off, GUI_ID_CLOSE);
  BUTTON_SetSelfDraw(hButton, 0, &_Draw);
  WM_SetCallback(hButton, _cbClose);
  return hButton;
}

#else
  void FRAMEWIN_ButtonClose_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
