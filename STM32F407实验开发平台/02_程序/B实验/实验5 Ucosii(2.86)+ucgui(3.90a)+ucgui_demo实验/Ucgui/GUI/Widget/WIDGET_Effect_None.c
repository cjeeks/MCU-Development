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
File        : WIDGET_Effect_None.c
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
*       _WIDGET_EFFECT_None_DrawDown
*/
static void _WIDGET_EFFECT_None_DrawDown(void) {
}

/*********************************************************************
*
*       _WIDGET_EFFECT_None_DrawUp
*/
static void _WIDGET_EFFECT_None_DrawUp(void) {
}

/*********************************************************************
*
*       _WIDGET_EFFECT_None_DrawDownRect
*/
static void _WIDGET_EFFECT_None_DrawDownRect(const GUI_RECT* pRect) {
  GUI_USE_PARA(pRect);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_None_DrawUpRect
*/
static void _WIDGET_EFFECT_None_DrawUpRect(const GUI_RECT* pRect) {
  GUI_USE_PARA(pRect);
}

/*********************************************************************
*
*       _WIDGET_EFFECT_None_GetRect
*/
static void _WIDGET_EFFECT_None_GetRect(GUI_RECT * pRect) {
  WM_GetClientRect(pRect);
}

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WIDGET_SetDefaultEffect_None
*/
void WIDGET_SetDefaultEffect_None(void) {
  WIDGET_SetDefaultEffect(&WIDGET_Effect_None);
}

/*********************************************************************
*
*       Effect tables --- Mainly function pointers
*
**********************************************************************
*/

const WIDGET_EFFECT WIDGET_Effect_None = {
  _WIDGET_EFFECT_None_DrawUp,
  _WIDGET_EFFECT_None_DrawDown,
  _WIDGET_EFFECT_None_DrawUpRect,
  _WIDGET_EFFECT_None_DrawDownRect,
  _WIDGET_EFFECT_None_GetRect,
  0
};

#else                            /* Avoid problems with empty object modules */
  void WIDGET_Effect_None_C(void) {}
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
