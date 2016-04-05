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
File        : LISTVIEW_GetFont.c
Purpose     : Implementation of LISTVIEW_GetFont
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>

#include "LISTVIEW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_GetFont
*/
const GUI_FONT GUI_UNI_PTR * LISTVIEW_GetFont(LISTVIEW_Handle hObj) {
  const GUI_FONT GUI_UNI_PTR * pFont = NULL;
  if (hObj) {
    LISTVIEW_Obj* pObj;
    WM_LOCK();
    pObj = LISTVIEW_H2P(hObj);
    pFont = pObj->Props.pFont;
    WM_UNLOCK();
  }
  return pFont;
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_GetFont_C(void);
  void LISTVIEW_GetFont_C(void) {}
#endif
