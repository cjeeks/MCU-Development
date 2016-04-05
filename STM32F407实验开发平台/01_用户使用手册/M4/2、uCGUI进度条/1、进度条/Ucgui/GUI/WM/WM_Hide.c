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
File        : WM_Hide.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"
#define WM_DEBUG_LEVEL 1

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_HideWindow
*/
void WM_HideWindow(WM_HWIN hWin) {
  if (hWin) {
    WM_Obj *pWin;
    WM_LOCK();
    pWin = WM_HANDLE2PTR(hWin);  
    /* First check if this is necessary at all */
    if (pWin->Status & WM_SF_ISVIS) {
      /* Clear Visibility flag */
      pWin->Status &= ~WM_SF_ISVIS;
      /* Mark content as invalid */
      WM__InvalidateAreaBelow(&WM_HANDLE2PTR(hWin)->Rect, hWin);
      #if WM_SUPPORT_NOTIFY_VIS_CHANGED
        WM__SendMsgNoData(hWin, WM_NOTIFY_VIS_CHANGED);             /* Notify window that visibility may have changed */
      #endif
    }
    WM_UNLOCK();
  }
}

#else
  void WM_Hide(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
