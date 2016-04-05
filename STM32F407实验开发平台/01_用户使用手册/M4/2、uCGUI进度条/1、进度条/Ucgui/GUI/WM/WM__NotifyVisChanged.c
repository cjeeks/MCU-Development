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
File        : WM__NotifyVisChanged.c
Purpose     : Windows manager routine
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*         Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _NotifyVisChanged
*
* Description
*   Notify all descendents
*/
static void _NotifyVisChanged(WM_HWIN hWin, GUI_RECT * pRect) {
  WM_Obj* pWin;

  for (hWin = WM_GetFirstChild(hWin); hWin; hWin = pWin->hNext) {
    pWin = WM_H2P(hWin);
    if (pWin->Status & WM_SF_ISVIS) {
      if (GUI_RectsIntersect(&pWin->Rect, pRect)) {
        WM__SendMsgNoData(hWin, WM_NOTIFY_VIS_CHANGED);             /* Notify window that visibility may have changed */
        _NotifyVisChanged(hWin, pRect);
      }
    }
  }
}


/*********************************************************************
*
*         Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       WM__NotifyVisChanged
*
* Description
*   Notify all siblings & descendents
*/
void WM__NotifyVisChanged(WM_HWIN hWin, GUI_RECT * pRect) {
  WM_Obj * pWin;
  WM_HWIN hParent;
  pWin = WM_H2P(hWin);
  hParent = pWin->hParent;
  if (hParent) {
    _NotifyVisChanged(hParent, pRect);
  }
}

#else
  void WM__NotifyVisChanged_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */


/*************************** End of file ****************************/
