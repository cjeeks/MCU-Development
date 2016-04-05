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
File        : MENU_Default.c
Purpose     : Implementation of menu widget
---------------------------END-OF-HEADER------------------------------
*/

#include "MENU.h"
#include "MENU_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code, set defaults
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU_SetDefaultTextColor
*/
void MENU_SetDefaultTextColor(unsigned ColorIndex, GUI_COLOR Color) {
  if (ColorIndex <= GUI_COUNTOF(MENU__DefaultProps.aTextColor)) {
    MENU__DefaultProps.aTextColor[ColorIndex] = Color;
  }
}

/*********************************************************************
*
*       MENU_SetDefaultBkColor
*/
void MENU_SetDefaultBkColor(unsigned ColorIndex, GUI_COLOR Color) {
  if (ColorIndex <= GUI_COUNTOF(MENU__DefaultProps.aBkColor)) {
    MENU__DefaultProps.aBkColor[ColorIndex] = Color;
  }
}

/*********************************************************************
*
*       MENU_SetDefaultBorderSize
*/
void MENU_SetDefaultBorderSize(unsigned BorderIndex, U8 BorderSize) {
  if (BorderIndex <= GUI_COUNTOF(MENU__DefaultProps.aBorder)) {
    MENU__DefaultProps.aBorder[BorderIndex] = BorderSize;
  }
}

/*********************************************************************
*
*       MENU_SetDefaultEffect
*/
void MENU_SetDefaultEffect(const WIDGET_EFFECT* pEffect) {
  MENU__pDefaultEffect = pEffect;
}

/*********************************************************************
*
*       MENU_SetDefaultFont
*/
void MENU_SetDefaultFont(const GUI_FONT GUI_UNI_PTR* pFont) {
  MENU__DefaultProps.pFont = pFont;
}

/*********************************************************************
*
*       Public code, get defaults
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU_GetDefaultTextColor
*/
GUI_COLOR MENU_GetDefaultTextColor(unsigned ColorIndex) {
  GUI_COLOR Color = GUI_INVALID_COLOR;
  if (ColorIndex <= GUI_COUNTOF(MENU__DefaultProps.aTextColor)) {
    Color = MENU__DefaultProps.aTextColor[ColorIndex];
  }
  return Color;
}

/*********************************************************************
*
*       MENU_GetDefaultBkColor
*/
GUI_COLOR MENU_GetDefaultBkColor(unsigned ColorIndex) {
  GUI_COLOR Color = GUI_INVALID_COLOR;
  if (ColorIndex <= GUI_COUNTOF(MENU__DefaultProps.aBkColor)) {
    Color = MENU__DefaultProps.aBkColor[ColorIndex];
  }
  return Color;
}

/*********************************************************************
*
*       MENU_GetDefaultBorderSize
*/
U8 MENU_GetDefaultBorderSize(unsigned BorderIndex) {
  U8 BorderSize = 0;
  if (BorderIndex <= GUI_COUNTOF(MENU__DefaultProps.aBorder)) {
    BorderSize = MENU__DefaultProps.aBorder[BorderIndex];
  }
  return BorderSize;
}

/*********************************************************************
*
*       MENU_GetDefaultEffect
*/
const WIDGET_EFFECT* MENU_GetDefaultEffect(void) {
  return MENU__pDefaultEffect;
}

/*********************************************************************
*
*       MENU_GetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR* MENU_GetDefaultFont(void) {
  return MENU__DefaultProps.pFont;
}

#else  /* avoid empty object files */
  void MENU_Default_C(void) {}
#endif

/*************************** End of file ****************************/
