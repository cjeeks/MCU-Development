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
File        : BUTTON_Default.c
Purpose     : Implementation of button widget
---------------------------END-OF-HEADER------------------------------
*/

#include "BUTTON_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_SetDefaultFont
*/
void BUTTON_SetDefaultFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  BUTTON__DefaultProps.pFont = pFont;
}

/*********************************************************************
*
*       BUTTON_SetDefaultTextColor
*/
void BUTTON_SetDefaultTextColor(GUI_COLOR Color, unsigned Index) {
  if (Index < GUI_COUNTOF(BUTTON__DefaultProps.aTextColor)) {
    BUTTON__DefaultProps.aTextColor[Index] = Color;
  }
}

/*********************************************************************
*
*       BUTTON_SetDefaultBkColor
*/
void BUTTON_SetDefaultBkColor(GUI_COLOR Color, unsigned Index) {
  if (Index < GUI_COUNTOF(BUTTON__DefaultProps.aBkColor)) {
    BUTTON__DefaultProps.aBkColor[Index] = Color;
  }
}

/*********************************************************************
*
*       BUTTON_SetDefaultTextAlign
*/
void BUTTON_SetDefaultTextAlign(int Align) {
  BUTTON__DefaultProps.Align = Align;
}

/*********************************************************************
*
*       BUTTON_GetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR * BUTTON_GetDefaultFont(void) {
  return BUTTON__DefaultProps.pFont;
}

/*********************************************************************
*
*       BUTTON_GetDefaultTextColor
*/
GUI_COLOR BUTTON_GetDefaultTextColor(unsigned Index) {
  GUI_COLOR Color = GUI_INVALID_COLOR;
  if (Index < GUI_COUNTOF(BUTTON__DefaultProps.aTextColor)) {
    Color = BUTTON__DefaultProps.aTextColor[Index];
  }
  return Color;
}

/*********************************************************************
*
*       BUTTON_GetDefaultBkColor
*/
GUI_COLOR BUTTON_GetDefaultBkColor(unsigned Index) {
  GUI_COLOR Color = GUI_INVALID_COLOR;
  if (Index < GUI_COUNTOF(BUTTON__DefaultProps.aBkColor)) {
    Color = BUTTON__DefaultProps.aBkColor[Index];
  }
  return Color;
}

/*********************************************************************
*
*       BUTTON_GetDefaultTextAlign
*/
int BUTTON_GetDefaultTextAlign(void) {
  return BUTTON__DefaultProps.Align;
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_Default_C(void);
  void BUTTON_Default_C(void) {}
#endif

