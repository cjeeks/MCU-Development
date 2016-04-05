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
File        : WM_SetScrollPos.c
Purpose     : Windows manager, optional routines
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/



/*********************************************************************
*
*       WM_CheckScrollBounds
*
*/
void WM_CheckScrollBounds(WM_SCROLL_STATE* pScrollState) {
  int Max;
  Max = pScrollState->NumItems - pScrollState->PageSize;
  if (Max < 0) {
    Max = 0;
  }
  /* Make sure scroll pos is in bounds */
  if (pScrollState->v < 0) {
    pScrollState->v = 0;
  }
  if (pScrollState->v > Max) {
    pScrollState->v = Max;
  }
}


/*********************************************************************
*
*       WM_CheckScrollPos
*
* Return value: Difference between old an new Scroll value.
*               Therefor 0 if settings have not changed.
*/
int  WM_CheckScrollPos(WM_SCROLL_STATE* pScrollState, int Pos, int LowerDist, int UpperDist) {
  int vOld;
  vOld = pScrollState->v;
  /* Check upper limit */
  if (Pos > pScrollState->v + pScrollState->PageSize - 1) {
    pScrollState->v = Pos - (pScrollState->PageSize - 1) + UpperDist;
  }
  /* Check lower limit */
  if (Pos < pScrollState->v) {
    pScrollState->v = Pos - LowerDist;
  }
  WM_CheckScrollBounds(pScrollState);
  return pScrollState->v - vOld;
}

/*********************************************************************
*
*       WM_SetScrollValue
*
* Return value: Difference between old an new Scroll value.
*               Therefor 0 if settings have not changed.
*/
int  WM_SetScrollValue(WM_SCROLL_STATE* pScrollState, int v) {
  int vOld;
  vOld = pScrollState->v;
  pScrollState->v = v;
  WM_CheckScrollBounds(pScrollState);
  return pScrollState->v - vOld;
}

#else
  void WM_CheckScrollPos_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
