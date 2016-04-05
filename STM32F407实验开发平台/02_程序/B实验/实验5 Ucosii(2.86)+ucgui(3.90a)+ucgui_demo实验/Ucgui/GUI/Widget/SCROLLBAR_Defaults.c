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
File        : SCROLLBAR_Defaults.c
Purpose     : SCROLLBAR, optional routine
---------------------------END-OF-HEADER------------------------------
*/

#include "SCROLLBAR_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       SCROLLBAR_GetDefaultWidth
*/
int       SCROLLBAR_GetDefaultWidth(void) {  return SCROLLBAR__DefaultWidth; }

/*********************************************************************
*
*       SCROLLBAR_GetDefaultBkColor
*/
GUI_COLOR SCROLLBAR_GetDefaultBkColor(unsigned int Index) {
  if (Index < GUI_COUNTOF(SCROLLBAR__aDefaultBkColor)) {
    return SCROLLBAR__aDefaultBkColor[Index];
  }
  return 0; 
}

/*********************************************************************
*
*       SCROLLBAR_GetDefaultColor
*/
GUI_COLOR SCROLLBAR_GetDefaultColor(unsigned int Index) {
  if (Index < GUI_COUNTOF(SCROLLBAR__aDefaultColor)) {
    return SCROLLBAR__aDefaultColor[Index];
  }
  return 0; 
}

/*********************************************************************
*
*       SCROLLBAR_SetDefaultWidth
*/
int  SCROLLBAR_SetDefaultWidth(int DefaultWidth) {
  int OldWidth = SCROLLBAR__DefaultWidth;
  SCROLLBAR__DefaultWidth = DefaultWidth;
  return OldWidth;
}

/*********************************************************************
*
*       SCROLLBAR_SetDefaultBkColor
*/
GUI_COLOR SCROLLBAR_SetDefaultBkColor(GUI_COLOR Color, unsigned int Index) {
  GUI_COLOR OldColor = 0;
  if (Index < GUI_COUNTOF(SCROLLBAR__aDefaultBkColor)) {
    SCROLLBAR__aDefaultBkColor[Index] = Color;
  }
  return OldColor; 
}

/*********************************************************************
*
*       SCROLLBAR_SetDefaultColor
*/
GUI_COLOR SCROLLBAR_SetDefaultColor(GUI_COLOR Color, unsigned int Index) {
  GUI_COLOR OldColor = 0;
  if (Index < GUI_COUNTOF(SCROLLBAR__aDefaultColor)) {
    SCROLLBAR__aDefaultColor[Index] = Color;
  }
  return OldColor; 
}

#else
  void SCROLLBAR_Defaults_c(void) {}    /* Avoid empty object files */
#endif  /* #if GUI_WINSUPPORT */



