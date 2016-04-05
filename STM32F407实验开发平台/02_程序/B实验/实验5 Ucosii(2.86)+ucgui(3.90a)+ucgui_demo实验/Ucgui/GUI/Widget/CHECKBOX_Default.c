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
File        : CHECKBOX_Default.c
Purpose     : Implementation of checkbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include "CHECKBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       CHECKBOX_SetDefaultSpacing
*/
void CHECKBOX_SetDefaultSpacing(int Spacing) {
  CHECKBOX__DefaultProps.Spacing = Spacing;
}

/*********************************************************************
*
*       CHECKBOX_SetDefaultTextColor
*/
void CHECKBOX_SetDefaultTextColor(GUI_COLOR Color) {
  CHECKBOX__DefaultProps.TextColor = Color;
}

/*********************************************************************
*
*       CHECKBOX_SetDefaultBkColor
*/
void CHECKBOX_SetDefaultBkColor(GUI_COLOR Color) {
  CHECKBOX__DefaultProps.BkColor = Color;
}

/*********************************************************************
*
*       CHECKBOX_SetDefaultFont
*/
void CHECKBOX_SetDefaultFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  CHECKBOX__DefaultProps.pFont = pFont;
}

/*********************************************************************
*
*       CHECKBOX_SetDefaultAlign
*/
void CHECKBOX_SetDefaultAlign(int Align) {
  CHECKBOX__DefaultProps.Align = Align;
}

/*********************************************************************
*
*       CHECKBOX_GetDefaultSpacing
*/
int CHECKBOX_GetDefaultSpacing(void) {
  return CHECKBOX__DefaultProps.Spacing;
}

/*********************************************************************
*
*       CHECKBOX_GetDefaultTextColor
*/
GUI_COLOR CHECKBOX_GetDefaultTextColor(void) {
  return CHECKBOX__DefaultProps.TextColor;
}

/*********************************************************************
*
*       CHECKBOX_GetDefaultBkColor
*/
GUI_COLOR CHECKBOX_GetDefaultBkColor(void) {
  return CHECKBOX__DefaultProps.BkColor;
}

/*********************************************************************
*
*       CHECKBOX_GetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR * CHECKBOX_GetDefaultFont(void) {
  return CHECKBOX__DefaultProps.pFont;
}

/*********************************************************************
*
*       CHECKBOX_GetDefaultAlign
*/
int CHECKBOX_GetDefaultAlign(void) {
  return CHECKBOX__DefaultProps.Align;
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_Default_C(void);
  void CHECKBOX_Default_C(void) {}
#endif

