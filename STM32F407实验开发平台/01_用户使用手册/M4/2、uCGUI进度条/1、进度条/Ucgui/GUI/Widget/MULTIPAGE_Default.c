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
File        : MULTIPAGE_Default.c
Purpose     : Implementation of MULTIPAGE widget
---------------------------END-OF-HEADER------------------------------
*/

#include "MULTIPAGE_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/
/*********************************************************************
*
*       MULTIPAGE_GetDefaultAlign
*/
unsigned MULTIPAGE_GetDefaultAlign(void) {
  return MULTIPAGE__DefaultAlign;
}

/*********************************************************************
*
*       MULTIPAGE_GetDefaultBkColor
*/
GUI_COLOR MULTIPAGE_GetDefaultBkColor(unsigned Index) {
  GUI_COLOR Color = GUI_INVALID_COLOR;
  if (Index < GUI_COUNTOF(MULTIPAGE__DefaultBkColor)) {
    Color = MULTIPAGE__DefaultBkColor[Index];
  }
  return Color;
}

/*********************************************************************
*
*       MULTIPAGE_GetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR * MULTIPAGE_GetDefaultFont(void) {
  return MULTIPAGE__pDefaultFont;
}

/*********************************************************************
*
*       MULTIPAGE_GetDefaultTextColor
*/
GUI_COLOR MULTIPAGE_GetDefaultTextColor(unsigned Index) {
  GUI_COLOR Color = GUI_INVALID_COLOR;
  if (Index < GUI_COUNTOF(MULTIPAGE__DefaultTextColor)) {
    Color = MULTIPAGE__DefaultTextColor[Index];
  }
  return Color;
}

/*********************************************************************
*
*       MULTIPAGE_SetDefaultAlign
*/
void MULTIPAGE_SetDefaultAlign(unsigned Align) {
  MULTIPAGE__DefaultAlign = Align;
}

/*********************************************************************
*
*       MULTIPAGE_SetDefaultBkColor
*/
void MULTIPAGE_SetDefaultBkColor(GUI_COLOR Color, unsigned Index) {
  if (Index < GUI_COUNTOF(MULTIPAGE__DefaultBkColor)) {
    MULTIPAGE__DefaultBkColor[Index] = Color;
  }
}

/*********************************************************************
*
*       MULTIPAGE_SetDefaultFont
*/
void MULTIPAGE_SetDefaultFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  MULTIPAGE__pDefaultFont = pFont;
}

/*********************************************************************
*
*       MULTIPAGE_SetDefaultTextColor
*/
void MULTIPAGE_SetDefaultTextColor(GUI_COLOR Color, unsigned Index) {
  if (Index < GUI_COUNTOF(MULTIPAGE__DefaultTextColor)) {
    MULTIPAGE__DefaultTextColor[Index] = Color;
  }
}

#else
  void MULTIPAGE_Default_C(void);
  void MULTIPAGE_Default_C(void) {} /* avoid empty object files */
#endif
