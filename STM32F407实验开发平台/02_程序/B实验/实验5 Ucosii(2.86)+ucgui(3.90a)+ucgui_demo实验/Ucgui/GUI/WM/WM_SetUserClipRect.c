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
File        : WM_SetUserClipArea.c
Purpose     : Windows manager, add. module
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
*       WM_SetUserClipRect
*/
const GUI_RECT* WM_SetUserClipRect(const GUI_RECT* pRect) {
  const GUI_RECT* pRectReturn;
  WM_LOCK();
  pRectReturn = GUI_Context.WM__pUserClipRect;
  GUI_Context.WM__pUserClipRect = pRect;
/* Activate it ... */
  WM__ActivateClipRect();
  WM_UNLOCK();
  return pRectReturn;
}

#else
  void WM_SetUserClipRect(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
