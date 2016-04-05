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
File        : GUI_GetFontInfo.C
Purpose     : Get GUI_FONTINFO structure
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"
#include <stddef.h>

#if GUI_COMPILER_SUPPORTS_FP

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GetFontInfo
*/
void GUI_GetFontInfo(const GUI_FONT GUI_UNI_PTR * pFont, GUI_FONTINFO * pFontInfo) {
  GUI_LOCK();
  if (pFont == NULL) {
    pFont = GUI_Context.pAFont;
  }
  pFontInfo->Baseline = pFont->Baseline;
  pFontInfo->CHeight  = pFont->CHeight;
  pFontInfo->LHeight  = pFont->LHeight;
  pFont->pfGetFontInfo(pFont, pFontInfo);
  GUI_UNLOCK();
}

#endif

/*************************** End of file ****************************/
