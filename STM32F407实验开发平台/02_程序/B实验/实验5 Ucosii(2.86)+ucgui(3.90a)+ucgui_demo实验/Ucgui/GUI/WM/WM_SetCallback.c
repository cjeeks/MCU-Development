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
File        : WM_SetCallback.C
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"

/*********************************************************************
*
*        Exported routines:  Set callback
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetCallback
*/
WM_CALLBACK* WM_SetCallback (WM_HWIN hWin, WM_CALLBACK* cb) {
  WM_CALLBACK* r = NULL;  
  if (hWin) {
    WM_Obj* pWin;
    WM_LOCK();
    pWin = WM_H2P(hWin);
    r = pWin->cb;
    pWin->cb = cb; 
    WM_InvalidateWindow(hWin);
    WM_UNLOCK();
  }
  return r;
}

#else
  void WM_SetCallBack(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
