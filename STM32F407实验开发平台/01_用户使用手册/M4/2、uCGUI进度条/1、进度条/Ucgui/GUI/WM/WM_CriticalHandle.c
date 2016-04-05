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
File        : WM_CriticalHandle.c
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__AddCriticalHandle
*/
void WM__AddCriticalHandle(WM_CRITICAL_HANDLE* pCriticalHandle) {
  pCriticalHandle->pNext   = WM__pFirstCriticalHandle;
  WM__pFirstCriticalHandle = pCriticalHandle;
}

/*********************************************************************
*
*       WM__RemoveCriticalHandle
*/
void WM__RemoveCriticalHandle(WM_CRITICAL_HANDLE* pCriticalHandle) {
  if (WM__pFirstCriticalHandle) {
    WM_CRITICAL_HANDLE *pCH, *pLast = 0;
    for (pCH = WM__pFirstCriticalHandle; pCH; pCH = pCH->pNext) {
      if (pCH == pCriticalHandle) {
        if (pLast) {
          pLast->pNext = pCH->pNext;
        } else if (pCH->pNext) {
          WM__pFirstCriticalHandle = pCH->pNext;
        } else {
          WM__pFirstCriticalHandle = 0;
        }
        break;
      }
      pLast = pCH;
    }
  }
}

#else
  void WM_CriticalHandle_C(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
