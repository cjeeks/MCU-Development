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
File        : LISTBOX_Default.c
Purpose     : Implementation of listbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTBOX_SetDefaultFont
*/
void LISTBOX_SetDefaultFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  LISTBOX_DefaultProps.pFont = pFont;
}

/*********************************************************************
*
*       LISTBOX_GetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR * LISTBOX_GetDefaultFont(void) {
  return LISTBOX_DefaultProps.pFont;
}

/*********************************************************************
*
*       LISTBOX_SetDefaultScrollStepH
*/
void LISTBOX_SetDefaultScrollStepH(int Value) {
  LISTBOX_DefaultProps.ScrollStepH = Value;
}

/*********************************************************************
*
*       LISTBOX_GetDefaultScrollStepH
*/
int LISTBOX_GetDefaultScrollStepH(void) {
  return LISTBOX_DefaultProps.ScrollStepH;
}

/*********************************************************************
*
*       LISTBOX_SetDefaultBkColor
*/
void LISTBOX_SetDefaultBkColor(unsigned Index, GUI_COLOR Color) {
  if (Index < GUI_COUNTOF(LISTBOX_DefaultProps.aBackColor)) {
    LISTBOX_DefaultProps.aBackColor[Index] = Color;
  }
}

/*********************************************************************
*
*       LISTBOX_GetDefaultBkColor
*/
GUI_COLOR LISTBOX_GetDefaultBkColor(unsigned Index) {
  if (Index < GUI_COUNTOF(LISTBOX_DefaultProps.aBackColor)) {
    return LISTBOX_DefaultProps.aBackColor[Index];
  }
  return GUI_INVALID_COLOR;
}

/*********************************************************************
*
*       LISTBOX_SetDefaultTextColor
*/
void LISTBOX_SetDefaultTextColor(unsigned Index, GUI_COLOR Color) {
  if (Index < GUI_COUNTOF(LISTBOX_DefaultProps.aTextColor)) {
    LISTBOX_DefaultProps.aTextColor[Index] = Color;
  }
}

/*********************************************************************
*
*       LISTBOX_GetDefaultTextColor
*/
GUI_COLOR LISTBOX_GetDefaultTextColor(unsigned Index) {
  if (Index < GUI_COUNTOF(LISTBOX_DefaultProps.aTextColor)) {
    return LISTBOX_DefaultProps.aTextColor[Index];
  }
  return GUI_INVALID_COLOR;
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_Default_C(void) {}
#endif

/*************************** End of file ****************************/
