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
File        : FRAMEWIN_Default.c
Purpose     : Implementation of framewindow widget
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"
#include "FRAMEWIN_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       public functions (Set/Get defaults)
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_SetDefaultFont
*/
void FRAMEWIN_SetDefaultFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  FRAMEWIN__DefaultProps.pFont = pFont;
}

/*********************************************************************
*
*       FRAMEWIN_GetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR * FRAMEWIN_GetDefaultFont(void) {
  return FRAMEWIN__DefaultProps.pFont;
}

/*********************************************************************
*
*       FRAMEWIN_SetDefaultBarColor
*/
void FRAMEWIN_SetDefaultBarColor(unsigned Index, GUI_COLOR Color) {
  if (Index < GUI_COUNTOF(FRAMEWIN__DefaultProps.aBarColor)) {
    FRAMEWIN__DefaultProps.aBarColor[Index] = Color;
  }
}

/*********************************************************************
*
*       FRAMEWIN_GetDefaultBarColor
*/
GUI_COLOR FRAMEWIN_GetDefaultBarColor(unsigned Index) {
  GUI_COLOR Color = 0;
  if (Index < GUI_COUNTOF(FRAMEWIN__DefaultProps.aBarColor)) {
    Color = FRAMEWIN__DefaultProps.aBarColor[Index];
  }
  return Color;
}

/*********************************************************************
*
*       FRAMEWIN_SetDefaultClientColor
*/
void FRAMEWIN_SetDefaultClientColor(GUI_COLOR Color) {
  FRAMEWIN__DefaultProps.ClientColor = Color;
}

/*********************************************************************
*
*       FRAMEWIN_GetDefaultClientColor
*/
GUI_COLOR FRAMEWIN_GetDefaultClientColor(void) {
  return FRAMEWIN__DefaultProps.ClientColor;
}

/*********************************************************************
*
*       FRAMEWIN_SetDefaultTitleHeight
*/
void FRAMEWIN_SetDefaultTitleHeight(int Height) {
  FRAMEWIN__DefaultProps.TitleHeight = Height;
}

/*********************************************************************
*
*       FRAMEWIN_GetDefaultTitleHeight
*/
int FRAMEWIN_GetDefaultTitleHeight(void) {
  return FRAMEWIN__DefaultProps.TitleHeight;
}

/*********************************************************************
*
*       FRAMEWIN_SetDefaultBorderSize
*/
void FRAMEWIN_SetDefaultBorderSize(int DefaultBorderSize) {
  FRAMEWIN__DefaultProps.BorderSize = DefaultBorderSize;
}

/*********************************************************************
*
*       FRAMEWIN_GetDefaultBorderSize
*/
int FRAMEWIN_GetDefaultBorderSize(void) {
  return FRAMEWIN__DefaultProps.BorderSize;
}

/*********************************************************************
*
*       FRAMEWIN_SetDefaultTextColor
*/
void FRAMEWIN_SetDefaultTextColor(unsigned Index, GUI_COLOR Color) {
  if (Index < GUI_COUNTOF(FRAMEWIN__DefaultProps.aTextColor)) {
    FRAMEWIN__DefaultProps.aTextColor[Index] = Color;
  }
}

/*********************************************************************
*
*       FRAMEWIN_GetDefaultTextColor
*/
GUI_COLOR FRAMEWIN_GetDefaultTextColor(unsigned Index) {
  GUI_COLOR Color = 0;
  if (Index < GUI_COUNTOF(FRAMEWIN__DefaultProps.aTextColor)) {
    Color = FRAMEWIN__DefaultProps.aTextColor[Index];
  }
  return Color;
}

#else
  void FRAMEWIN_Default(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */
