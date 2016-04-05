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
File        : WM_DIAG.c
Purpose     : Implementation of WM_DIAG_ ... functions
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "WM_Intern.h"

#if defined (__WATCOMC__)
  #define Sleep()
#else
  #if GUI_WINSUPPORT
    #if WM_SUPPORT_DIAG      /* Only defined if GUI_WINSUPPORT >= 0 */
      #include "windows.h"   /* Required for sleep only */
    #endif
  #endif
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/

/*********************************************************************
*
*       _ShowInvalid
*
* Function:
*   Debug code: shows invalid areas
*/
#if (WM_SUPPORT_DIAG)
static void _ShowInvalid(WM_HWIN hWin) {
  GUI_CONTEXT Context = GUI_Context;
  GUI_RECT rClient;
  WM_Obj * pWin;
  pWin = WM_H2P(hWin);
  rClient = pWin->InvalidRect;
  GUI_MoveRect(&rClient, -pWin->Rect.x0, -pWin->Rect.y0);
  WM_SelectWindow(hWin);
  GUI_SetColor(GUI_GREEN);
  GUI_SetBkColor(GUI_GREEN);
  GUI_FillRect(rClient.x0, rClient.y0, rClient.x1, rClient.y1);
  Sleep(20);
  GUI_Context = Context;
}
#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_DIAG_EnableInvalidationColoring
*/
#if (WM_SUPPORT_DIAG)
void WM_DIAG_EnableInvalidationColoring(int OnOff) {
  if (OnOff) {
    WM__pfShowInvalid = _ShowInvalid;
  } else {
    WM__pfShowInvalid = NULL;
  }
}

#else
  void WM_DIAG_C(void);   /* Avoid "no prototype" warnings */
  void WM_DIAG_C(void) {} /* Avoid empty object files */
#endif

/*************************** End of file ****************************/
