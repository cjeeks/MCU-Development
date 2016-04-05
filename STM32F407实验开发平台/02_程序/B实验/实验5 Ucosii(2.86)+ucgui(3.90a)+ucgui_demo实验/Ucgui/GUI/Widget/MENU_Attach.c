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
File        : MENU_Attach.c
Purpose     : Implementation of menu widget
---------------------------END-OF-HEADER------------------------------
*/

#include "MENU.h"
#include "MENU_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU_Attach
*/
void MENU_Attach(MENU_Handle hObj, WM_HWIN hDestWin, int x, int y, int xSize, int ySize, int Flags) {
  GUI_USE_PARA(Flags);
  if (hObj) {
    MENU_Obj* pObj;
    WM_LOCK();
    pObj = MENU_H2P(hObj);
    if (pObj) {
      pObj->Width  = ((xSize > 0) ? xSize : 0);
      pObj->Height = ((ySize > 0) ? ySize : 0);
      WM_AttachWindowAt(hObj, hDestWin, x, y);
      MENU__ResizeMenu(hObj, pObj);
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void MENU_Attach_C(void) {}
#endif

/*************************** End of file ****************************/
