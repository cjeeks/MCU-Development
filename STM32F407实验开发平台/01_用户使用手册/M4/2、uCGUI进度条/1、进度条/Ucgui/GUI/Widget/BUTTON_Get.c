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
File        : BUTTON_Get.c
Purpose     : Button widget, various (optional) Get routines
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "BUTTON.h"
#include "BUTTON_Private.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_GetBkColor  
*/
GUI_COLOR BUTTON_GetBkColor(BUTTON_Handle hObj,unsigned int Index) {
  GUI_COLOR Color = 0;
  if (hObj && (Index < 2)) {
    BUTTON_Obj * pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    Color = pObj->Props.aBkColor[Index];
    WM_UNLOCK();
  }
  return Color;
}

/*********************************************************************
*
*       BUTTON_GetFont     
*/
const GUI_FONT GUI_UNI_PTR * BUTTON_GetFont(BUTTON_Handle hObj) {
  const GUI_FONT GUI_UNI_PTR * pFont = 0;
  if (hObj) {
    BUTTON_Obj * pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    pFont = pObj->Props.pFont;
    WM_UNLOCK();
  }
  return pFont;
}

/*********************************************************************
*
*       BUTTON_GetText  
*/
void BUTTON_GetText(BUTTON_Handle hObj, char * pBuffer, int MaxLen) {
  if (hObj) {
    BUTTON_Obj * pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    if (pObj->hpText) {
      const char * pText = (const char*) GUI_ALLOC_h2p(pObj->hpText);
      int Len = strlen(pText);
      if (Len > (MaxLen - 1))
        Len = MaxLen - 1;
      memcpy((void *)pBuffer, (const void *)pText, Len);
      *(pBuffer + Len) = 0;
    } else {
      *pBuffer = 0;     /* Empty string */
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       BUTTON_GetTextColor  
*/
GUI_COLOR BUTTON_GetTextColor(BUTTON_Handle hObj,unsigned int Index) {
  GUI_COLOR Color = 0;
  if (hObj && (Index < 2)) {
    BUTTON_Obj * pObj;
    WM_LOCK();
    pObj = BUTTON_H2P(hObj);
    Color = pObj->Props.aTextColor[Index];
    WM_UNLOCK();
  }
  return Color;
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_Get_C(void) {}
#endif
