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
File        : GUI__CalcTextRect.c
Purpose     : Implementation of gui function
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "GUI_Protected.h"
#include "GUI.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__CalcTextRect
*/
void GUI__CalcTextRect(const char GUI_UNI_PTR* pText, const GUI_RECT* pTextRectIn, GUI_RECT* pTextRectOut, int TextAlign) {
  if (pText) {
    int xPos, yPos, TextWidth, TextHeight;

    /* Calculate X-pos of text */
    TextWidth = GUI_GetStringDistX(pText);
    switch (TextAlign & GUI_TA_HORIZONTAL) {
    case GUI_TA_HCENTER:
      xPos = pTextRectIn->x0 + ((pTextRectIn->x1 - pTextRectIn->x0 + 1) - TextWidth) / 2;
      break;
    case GUI_TA_RIGHT:
      xPos = pTextRectIn->x1 - TextWidth + 1;
      break;
    default:
      xPos = pTextRectIn->x0;
    }

    /* Calculate Y-pos of text*/
    TextHeight = GUI_GetFontDistY();
    switch (TextAlign & GUI_TA_VERTICAL) {
    case GUI_TA_VCENTER:
      yPos = pTextRectIn->y0 + ((pTextRectIn->y1 - pTextRectIn->y0 + 1) - TextHeight) / 2;
      break;
    case GUI_TA_BOTTOM:
      yPos = pTextRectIn->y1 - TextHeight + 1;
      break;
    case GUI_TA_BASELINE:
    default:
      yPos = pTextRectIn->y0;
    }

    /* Return text rectangle */
    pTextRectOut->x0 = xPos;
    pTextRectOut->y0 = yPos;
    pTextRectOut->x1 = xPos + TextWidth  - 1;
    pTextRectOut->y1 = yPos + TextHeight - 1;
  } else {
    *pTextRectOut = *pTextRectIn;
  }
}

/*************************** End of file ****************************/
