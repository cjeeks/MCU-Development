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
File        : WM__ForEachDesc.c
Purpose     : Implementation of WM__ForEachDesc
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
*       WM__ForEachDesc
*/
void WM__ForEachDesc(WM_HWIN hWin, WM_tfForEach * pcb, void * pData) {
  WM_HWIN hChild;
  WM_Obj* pChild;
  WM_Obj* pWin;
  pWin = WM_H2P(hWin);
  for (hChild = pWin->hFirstChild; hChild; hChild = pChild->hNext) {
    pChild = WM_H2P(hChild);
    pcb(hChild, pData);
    WM_ForEachDesc(hChild, pcb, pData);
  }
}

#else
  void WM__ForEachDesc_C(void);
  void WM__ForEachDesc_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
