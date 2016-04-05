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
File        : WIDGET_Effect_Simple.c
Purpose     : Effect routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#include "WIDGET.h"
#include "GUIDebug.h"
#include "GUI.h"
#include "GUI_Protected.h"
#include "WM_Intern.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _WIDGET_EFFECT_Simple_DrawUpRect
*/
static void _WIDGET_EFFECT_Simple_DrawUpRect(const GUI_RECT* pRect) {
  GUI_CONTEXT Context;
  GUI_SaveContext(&Context);
  LCD_SetColor(GUI_BLACK);
  GUI_DrawRect(pRect->x0, pRect->y0, pRect->x1, pRect->y1);          /* Draw rectangle around it */
  GUI_RestoreContext(&Context);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_Simple_DrawUp
*/
static void _WIDGET_EFFECT_Simple_DrawUp(void) {
  GUI_RECT r;
  WM_GetClientRect(&r);
  _WIDGET_EFFECT_Simple_DrawUpRect(&r);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_Simple_DrawDownRect
*/
static void _WIDGET_EFFECT_Simple_DrawDownRect(const GUI_RECT* pRect) {
  GUI_CONTEXT Context;
  GUI_SaveContext(&Context);
  LCD_SetColor(GUI_BLACK);
  GUI_DrawRect(pRect->x0, pRect->y0, pRect->x1, pRect->y1);          /* Draw rectangle around it */
  GUI_RestoreContext(&Context);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_Simple_DrawDown
*/
static void _WIDGET_EFFECT_Simple_DrawDown(void) {
  GUI_RECT r;
  WM_GetClientRect(&r);
  _WIDGET_EFFECT_Simple_DrawDownRect(&r);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_Simple_GetRect
*/
static void _WIDGET_EFFECT_Simple_GetRect(GUI_RECT* pRect) {
  WM_GetClientRect(pRect);
  GUI__ReduceRect(pRect, pRect, 1);
}

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WIDGET_SetDefaultEffect_Simple
*/
void WIDGET_SetDefaultEffect_Simple(void) {
  WIDGET_SetDefaultEffect(&WIDGET_Effect_Simple);
}

/*********************************************************************
*
*       Effect tables --- Mainly function pointers
*
**********************************************************************
*/

const WIDGET_EFFECT WIDGET_Effect_Simple = {
  _WIDGET_EFFECT_Simple_DrawUp,
  _WIDGET_EFFECT_Simple_DrawDown,
  _WIDGET_EFFECT_Simple_DrawUpRect,
  _WIDGET_EFFECT_Simple_DrawDownRect,
  _WIDGET_EFFECT_Simple_GetRect,
  1
};

#else                            /* Avoid problems with empty object modules */
  void WIDGET_Effect_Simple_C(void) {}
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
