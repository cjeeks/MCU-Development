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
File        : WM_Show.c
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
*       WM_InvalidateWindowDescs

  Invalidate window and all descendents (children and grandchildren and ...
*/
void WM_InvalidateWindowDescs(WM_HWIN hWin) {
  WM_HWIN hChild;
  if (hWin) {
    WM_InvalidateWindow(hWin);    /* Invalidate window itself */
    for (hChild = WM_GetFirstChild(hWin); hChild;) {
      WM_Obj* pChild = WM_H2P(hChild);
      WM_InvalidateWindowDescs(hChild);
      hChild = pChild->hNext;
    }
  }
}

/*********************************************************************
*
*       WM_ShowWindow
*/
void WM_ShowWindow(WM_HWIN hWin) {
  if (hWin) {
    WM_Obj *pWin;
    WM_LOCK();
    pWin = WM_H2P(hWin);  
    if ((pWin->Status & WM_SF_ISVIS) == 0) {  /* First check if this is necessary at all */
      pWin->Status |= WM_SF_ISVIS;  /* Set Visibility flag */
      WM_InvalidateWindowDescs(hWin);    /* Mark content as invalid */
      #if WM_SUPPORT_NOTIFY_VIS_CHANGED
        WM__NotifyVisChanged(hWin, &pWin->Rect);
      #endif
    }
    WM_UNLOCK();
  }
}

#else
  void WM_Show_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
