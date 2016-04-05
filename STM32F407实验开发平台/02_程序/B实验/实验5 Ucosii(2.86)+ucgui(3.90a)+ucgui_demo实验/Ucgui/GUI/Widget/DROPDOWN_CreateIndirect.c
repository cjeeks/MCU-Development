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
File        : DROPDOWN_CreateIndirect.c
Purpose     : Implementation of dropdown widget
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "DROPDOWN.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       DROPDOWN_CreateIndirect
*/
DROPDOWN_Handle DROPDOWN_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo,
                                        WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb) {
  DROPDOWN_Handle  hThis;
  GUI_USE_PARA(cb);
  hThis = DROPDOWN_CreateEx(pCreateInfo->x0 + x0, pCreateInfo->y0 + y0,
                            pCreateInfo->xSize, pCreateInfo->ySize,
                            hWinParent, 0, pCreateInfo->Flags, pCreateInfo->Id);
  return hThis;
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_CreateIndirect_C(void) {}
#endif
