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
File        : WM_SetScrollbar.c
Purpose     : Implementation of WM_SetScrollbarV, WM_SetScrollbarH
----------------------------------------------------------------------
*/

#include "WM_Intern.h"
#include "SCROLLBAR.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetScrollbar
*
* Return value: 1 if scrollbar was visible, 0 if not
*/
static int _SetScrollbar(WM_HWIN hWin, int OnOff, int Id, int Flags) {
  WM_HWIN hBar;
  hBar = WM_GetDialogItem(hWin, Id);
  if (OnOff) {
    if (!hBar) {
      SCROLLBAR_CreateAttached(hWin, Flags);
    }
  } else {
    WM_HideWindow(hBar);
    if (hBar) {
      WM_DeleteWindow(hBar);
    }
  }
  return (hBar ? 1 : 0);
}


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__SetScrollbarV
*
*/
int WM__SetScrollbarV(WM_HWIN hWin, int OnOff) {
  return _SetScrollbar(hWin, OnOff, GUI_ID_VSCROLL, SCROLLBAR_CF_VERTICAL);
}

/*********************************************************************
*
*       WM__SetScrollbarH
*
*/
int WM__SetScrollbarH(WM_HWIN hWin, int OnOff) {
  return _SetScrollbar(hWin, OnOff, GUI_ID_HSCROLL, 0);
}

/*********************************************************************
*
*       WM_SetScrollbarH
*
*/
int WM_SetScrollbarH(WM_HWIN hWin, int OnOff) {
  int r;
  WM_LOCK();
  r = WM__SetScrollbarH(hWin, OnOff);
  WM_UNLOCK();
  return r;
}

/*********************************************************************
*
*       WM_SetScrollbarV
*
*/
int WM_SetScrollbarV(WM_HWIN hWin, int OnOff) {
  int r;
  WM_LOCK();
  r = WM__SetScrollbarV(hWin, OnOff);
  WM_UNLOCK();
  return r;
}

#else
  void WM_SetScrollbar_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
