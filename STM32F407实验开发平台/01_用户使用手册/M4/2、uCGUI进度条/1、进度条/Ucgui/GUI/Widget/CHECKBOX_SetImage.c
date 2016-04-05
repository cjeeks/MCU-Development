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
File        : CHECKBOX_SetImage.c
Purpose     : Implementation of checkbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include "CHECKBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/
void CHECKBOX_SetImage(CHECKBOX_Handle hObj, const GUI_BITMAP * pBitmap, unsigned int Index) {
  if (hObj) {
    CHECKBOX_Obj * pObj;
    GUI_LOCK();
    pObj = CHECKBOX_H2P(hObj);
    if (Index <= GUI_COUNTOF(pObj->Props.apBm)) {
      pObj->Props.apBm[Index] = pBitmap;
    }
    GUI_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_SetImage_C(void);
  void CHECKBOX_SetImage_C(void) {}
#endif
