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
File        : WM_SetTrans.C
Purpose     : Windows manager, optional routines
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT
#if WM_SUPPORT_TRANSPARENCY   /* If 0, WM will not generate any code */

#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetHasTrans
*/
void WM_SetHasTrans(WM_HWIN hWin) {
  WM_Obj *pWin;
  WM_LOCK();
  if (hWin) {
    pWin = WM_H2P(hWin);  
    /* First check if this is necessary at all */
    if ((pWin->Status & WM_SF_HASTRANS) == 0) {
      pWin->Status |= WM_SF_HASTRANS; /* Set Transparency flag */
      WM__TransWindowCnt++;          /* Increment counter for transparency windows */
      WM_InvalidateWindow(hWin);      /* Mark content as invalid */
    }
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       WM_ClrHasTrans
*/
void WM_ClrHasTrans(WM_HWIN hWin) {
  WM_Obj *pWin;
  WM_LOCK();
  if (hWin) {
    pWin = WM_H2P(hWin);  
    /* First check if this is necessary at all */
    if (pWin->Status & WM_SF_HASTRANS) {
      pWin->Status &= ~WM_SF_HASTRANS;
      WM__TransWindowCnt--;            /* Decrement counter for transparency windows */
      WM_InvalidateWindow(hWin);        /* Mark content as invalid */
    }
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       WM_GetHasTrans
*/
int WM_GetHasTrans(WM_HWIN hWin) {
  int r = 0;
  WM_Obj *pWin;
  WM_LOCK();
  if (hWin) {
    pWin = WM_H2P(hWin);  
    r = pWin->Status & WM_SF_HASTRANS;
  }
  WM_UNLOCK();
  return r;
}

#endif /*WM_SUPPORT_TRANSPARENCY*/

#else
  void WM_SetTrans_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
