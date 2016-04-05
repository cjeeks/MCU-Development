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
File        : LISTBOX_SetBkColor.c
Purpose     : Implementation of listbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTBOX_SetBkColor
*/
void LISTBOX_SetBkColor(LISTBOX_Handle hObj, unsigned Index, GUI_COLOR color) {
  LISTBOX_Obj* pObj;
  if (hObj) {
    if ((unsigned int)Index < GUI_COUNTOF(pObj->Props.aBackColor)) {
      WM_LOCK();
      pObj = LISTBOX_H2P(hObj);
      ASSERT_IS_VALID_PTR(pObj);
      pObj->Props.aBackColor[Index] = color;
      LISTBOX__InvalidateInsideArea(hObj);
      WM_UNLOCK();
    }
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_SetBkColor_C(void) {}
#endif

/*************************** End of file ****************************/

