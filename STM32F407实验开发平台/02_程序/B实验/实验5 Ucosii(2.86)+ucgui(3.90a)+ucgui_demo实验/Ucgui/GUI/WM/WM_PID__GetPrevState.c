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
File        : WM_PID__GetPrevState.c
Purpose     : Touch support
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"

#if (GUI_WINSUPPORT)

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_PID__GetPrevState
*/
void WM_PID__GetPrevState(GUI_PID_STATE* pPrevState) {
  *pPrevState = WM_PID__StateLast;
}

#else
  void WM_PID__GetPrevState_c(void) {} /* avoid empty object files */
#endif  /* (GUI_WINSUPPORT) */

/*************************** End of file ****************************/

