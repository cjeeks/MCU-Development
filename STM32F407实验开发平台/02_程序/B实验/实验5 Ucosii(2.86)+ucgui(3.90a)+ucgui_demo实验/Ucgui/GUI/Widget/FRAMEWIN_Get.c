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
File        : FRAMEWIN_Get.c
Purpose     : 
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "FRAMEWIN_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_GetFont
*/
const GUI_FONT GUI_UNI_PTR * FRAMEWIN_GetFont(FRAMEWIN_Handle hObj) {
  const GUI_FONT GUI_UNI_PTR * r = NULL;
  GUI_LOCK();
  if (hObj) {
    FRAMEWIN_Obj* pObj = FRAMEWIN_H2P(hObj);
    r = pObj->Props.pFont;
    FRAMEWIN_Invalidate(hObj);
  }
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       FRAMEWIN_GetTitleHeight
*/
int FRAMEWIN_GetTitleHeight(FRAMEWIN_Handle hObj) {
  int r = 0;
  POSITIONS Pos;
  /* Move client window accordingly */
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    FRAMEWIN__CalcPositions(pObj, &Pos);
    r = pObj->Props.TitleHeight;
    if (r == 0) {
      r = Pos.TitleHeight;
    }
    WM_UNLOCK();
  }
  return r;
}

/*********************************************************************
*
*       FRAMEWIN_GetBorderSize
*/
int FRAMEWIN_GetBorderSize(FRAMEWIN_Handle hObj) {
  int r = 0;
  /* Move client window accordingly */
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    r = pObj->Props.BorderSize;
    WM_UNLOCK();
  }
  return r;
}


#else
  void FRAMEWIN_Get_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
