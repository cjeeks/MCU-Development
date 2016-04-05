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
File        : WM_UserData.c
Purpose     : Implementation of WM_xxxUserData
----------------------------------------------------------------------
*/

#include "WM_Intern.h"
#include <string.h>           /* for memcpy, memset */

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _Min
*/
static int Min(int v0, int v1) {
  return (v0 < v1) ? v0 : v1;
}

/*********************************************************************
*
*       _CalcNumBytes
*/
static int _CalcNumBytes(WM_HWIN hWin, int NumBytes) {
  return Min(GUI_ALLOC_GetSize(hWin) - sizeof(WM_Obj), NumBytes);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_GetUserData
*
*  Purpose
*    Get the User data (extra bytes) associated with a window
*    These bytes have typically been set using WM_SetUserData first.
*    (If not, they are 0)
*  Return value:
*    Number of bytes fetched. (<= SizeofBuffer)
*/
int WM_GetUserData(WM_HWIN hWin, void* pDest, int NumBytes) {
  if (hWin) {
    WM_Obj *pWin;
    NumBytes = _CalcNumBytes(hWin, NumBytes);
    WM_LOCK();
    pWin = WM_H2P(hWin);
    memcpy(pDest, pWin + 1, NumBytes);
    WM_UNLOCK();
  }
  return NumBytes;
}

/*********************************************************************
*
*       WM_SetUserData
*
*  Purpose
*    Set the User data (extra bytes) associated with a window
*  Return value:
*    Number of bytes fetched. (<= SizeofBuffer)
*/
int WM_SetUserData(WM_HWIN hWin, const void* pSrc, int NumBytes) {
  if (hWin) {
    WM_Obj *pWin;
    NumBytes = _CalcNumBytes(hWin, NumBytes);
    WM_LOCK();
    pWin = WM_H2P(hWin);
    memcpy(pWin + 1, pSrc, NumBytes);
    WM_UNLOCK();
  }
  return NumBytes;
}

#else
  void WM_UserData_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
