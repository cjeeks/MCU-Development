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
File        : WM_ForEachDesc.c
Purpose     : Implementation of WM_ForEachDesc
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*         Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       WM_ForEachDesc
*/
void WM_ForEachDesc(WM_HWIN hWin, WM_tfForEach * pcb, void * pData) {
  WM_LOCK();
  WM__ForEachDesc(hWin, pcb, pData);
  WM_UNLOCK();
}

#else
  void WM_ForEachDesc_C(void);
  void WM_ForEachDesc_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
