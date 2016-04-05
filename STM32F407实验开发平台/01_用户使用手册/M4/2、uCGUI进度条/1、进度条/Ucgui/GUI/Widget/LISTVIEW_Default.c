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
File        : LISTVIEW_Default.c
Purpose     : Implementation of listview widget
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTVIEW_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTVIEW_SetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR * LISTVIEW_SetDefaultFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  const GUI_FONT GUI_UNI_PTR * pOldFont = LISTVIEW_DefaultProps.pFont;
  LISTVIEW_DefaultProps.pFont = pFont;
  return pOldFont;
}

/*********************************************************************
*
*       LISTVIEW_SetDefaultTextColor
*/
GUI_COLOR LISTVIEW_SetDefaultTextColor(unsigned Index, GUI_COLOR Color) {
  GUI_COLOR OldColor = 0;
  if (Index < GUI_COUNTOF(LISTVIEW_DefaultProps.aTextColor)) {
    OldColor = LISTVIEW_DefaultProps.aTextColor[Index];
    LISTVIEW_DefaultProps.aTextColor[Index] = Color;
  }
  return OldColor;
}

/*********************************************************************
*
*       LISTVIEW_SetDefaultBkColor
*/
GUI_COLOR LISTVIEW_SetDefaultBkColor(unsigned Index, GUI_COLOR Color) {
  GUI_COLOR OldColor = 0;
  if (Index < GUI_COUNTOF(LISTVIEW_DefaultProps.aBkColor)) {
    OldColor = LISTVIEW_DefaultProps.aBkColor[Index];
    LISTVIEW_DefaultProps.aBkColor[Index] = Color;
  }
  return OldColor;
}

/*********************************************************************
*
*       LISTVIEW_SetDefaultGridColor
*/
GUI_COLOR LISTVIEW_SetDefaultGridColor(GUI_COLOR Color) {
  GUI_COLOR OldColor = LISTVIEW_DefaultProps.GridColor;
  LISTVIEW_DefaultProps.GridColor = Color;
  return OldColor;
}

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_Default_C(void) {}
#endif

/*************************** End of file ****************************/
