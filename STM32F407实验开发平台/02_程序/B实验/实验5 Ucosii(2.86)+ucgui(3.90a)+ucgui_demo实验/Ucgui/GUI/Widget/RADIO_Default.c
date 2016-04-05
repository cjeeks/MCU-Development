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
File        : RADIO_Default.c
Purpose     : Implementation of radio widget
---------------------------END-OF-HEADER------------------------------
*/

#include "RADIO.h"
#include "RADIO_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/
/*********************************************************************
*
*       RADIO_GetDefaultFont
*/
const GUI_FONT GUI_UNI_PTR* RADIO_GetDefaultFont(void) {
  return RADIO__pDefaultFont;
}

/*********************************************************************
*
*       RADIO_GetDefaultTextColor
*/
GUI_COLOR RADIO_GetDefaultTextColor(void) {
  return RADIO__DefaultTextColor;
}

/*********************************************************************
*
*       RADIO_SetDefaultFont
*/
void RADIO_SetDefaultFont(const GUI_FONT GUI_UNI_PTR* pFont) {
  RADIO__pDefaultFont = pFont;
}

/*********************************************************************
*
*       RADIO_SetDefaultTextColor
*/
void RADIO_SetDefaultTextColor(GUI_COLOR TextColor) {
  RADIO__DefaultTextColor = TextColor;
}

#else                            /* Avoid problems with empty object modules */
  void RADIO_Default_C(void);
  void RADIO_Default_C(void) {}
#endif

/************************* end of file ******************************/
