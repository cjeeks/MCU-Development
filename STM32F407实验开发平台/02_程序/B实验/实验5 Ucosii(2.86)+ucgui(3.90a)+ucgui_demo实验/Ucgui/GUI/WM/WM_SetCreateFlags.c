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
File        : WM_SetCreateFlags.C
Purpose     : Implementation of WM_SetCreateFlags
----------------------------------------------------------------------
*/

#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */
#include "GUIDebug.h"

/*******************************************************************
*
*           Public code
*
********************************************************************
*/
/*********************************************************************
*
*       WM_SetCreateFlags
*/
U16 WM_SetCreateFlags(U16 Flags) {
  U16 r = WM__CreateFlags;
  WM__CreateFlags = Flags;
  return r;
}

#else
  void WM_SetCreateFlags(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
