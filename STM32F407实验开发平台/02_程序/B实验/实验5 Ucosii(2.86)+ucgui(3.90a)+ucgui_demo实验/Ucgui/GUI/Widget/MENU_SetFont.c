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
File        : MENU_SetFont.c
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
*       MENU_SetFont
*/
void MENU_SetFont(MENU_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont) {
  if (hObj) {
    MENU_Obj* pObj;
    WM_LOCK();
    pObj = MENU_H2P(hObj);
    if (pObj) {
      if (pFont != pObj->Props.pFont) {
        pObj->Props.pFont = pFont;
        MENU__RecalcTextWidthOfItems(pObj);
        MENU__ResizeMenu(hObj, pObj);
      }
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void MENU_SetFont_C(void) {}
#endif

/*************************** End of file ****************************/
