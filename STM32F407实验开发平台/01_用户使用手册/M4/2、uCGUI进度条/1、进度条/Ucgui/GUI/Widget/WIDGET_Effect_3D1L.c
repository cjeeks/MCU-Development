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
File        : WIDGET_Effect_3D1L.c
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
*       Macros for internal use
*
**********************************************************************
*/

#define WIDGET_H2P(hWin)        ((WIDGET*)GUI_ALLOC_h2p(hWin))

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _WIDGET_EFFECT_3D1L_DrawUpRect
*
* Add. info:
*   This routine does not preserve the drawing colors for speed
*   reasons. If this is required, it should be done in the calling
*   routine.
*/
static void _WIDGET_EFFECT_3D1L_DrawUpRect(const GUI_RECT* pRect) {
  GUI_RECT r;
  r = *pRect;
  /* Draw the upper left sides */
  LCD_SetColor(0xE7E7E7);
  GUI_DrawHLine(r.y0, r.x0, r.x1 - 1);
  GUI_DrawVLine(r.x0, r.y0 + 1, r.y1 - 1);
  /* Draw the lower right sides */
  LCD_SetColor(0x606060);
  GUI_DrawHLine(r.y1, r.x0, r.x1);
  GUI_DrawVLine(r.x1, r.y0, r.y1 - 1);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_3D1L_DrawUp
*/
static void _WIDGET_EFFECT_3D1L_DrawUp(void) {
  GUI_RECT r;
  WM_GetClientRect(&r);
  _WIDGET_EFFECT_3D1L_DrawUpRect(&r);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_3D1L_DrawDownRect
*/
static void _WIDGET_EFFECT_3D1L_DrawDownRect(const GUI_RECT* pRect) {
  GUI_RECT r;
  r = *pRect;
  /* Draw the upper left sides */
  LCD_SetColor(0x606060);
  GUI_DrawHLine(r.y0, r.x0, r.x1 - 1);
  GUI_DrawVLine(r.x0, r.y0 + 1, r.y1 - 1);
  /* Draw the lower right sides */
  LCD_SetColor(0xE7E7E7);
  GUI_DrawHLine(r.y1, r.x0, r.x1);
  GUI_DrawVLine(r.x1, r.y0, r.y1 - 1);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_3D1L_DrawDown
*/
static void _WIDGET_EFFECT_3D1L_DrawDown(void) {
  GUI_RECT r;
  WM_GetClientRect(&r);
  _WIDGET_EFFECT_3D1L_DrawDownRect(&r);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_3D1L_GetRect
*/
static void _WIDGET_EFFECT_3D1L_GetRect(GUI_RECT* pRect) {
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
*       WIDGET_SetDefaultEffect_3D1L
*/
void WIDGET_SetDefaultEffect_3D1L(void) {
  WIDGET_SetDefaultEffect(&WIDGET_Effect_3D1L);
}

/*********************************************************************
*
*       Effect tables --- Mainly function pointers
*
**********************************************************************
*/

const WIDGET_EFFECT WIDGET_Effect_3D1L = {
  _WIDGET_EFFECT_3D1L_DrawUp,
  _WIDGET_EFFECT_3D1L_DrawDown,
  _WIDGET_EFFECT_3D1L_DrawUpRect,
  _WIDGET_EFFECT_3D1L_DrawDownRect,
  _WIDGET_EFFECT_3D1L_GetRect,
  1
};

#else                            /* Avoid problems with empty object modules */
  void WIDGET_Effect_3D1L_C(void) {}
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
