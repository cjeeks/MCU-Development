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
File        : WM_SetpfPollPID.c
Purpose     : Implementation of WM_SetpfPollPID
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SetpfPollPID
*/
WM_tfPollPID* WM_SetpfPollPID(WM_tfPollPID* pf) {
  WM_tfPollPID* r = WM_pfPollPID;
  WM_pfPollPID = pf;
  return r;
}

#else
  void WM_SetpfPollPID_c(void);
  void WM_SetpfPollPID_c(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
