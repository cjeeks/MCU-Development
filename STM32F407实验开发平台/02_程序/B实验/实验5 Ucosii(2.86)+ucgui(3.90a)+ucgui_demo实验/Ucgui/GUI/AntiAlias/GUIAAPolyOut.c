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
File        : GUIPolyOutAA.C
Purpose     : Draw Polygon outline routines with Antialiasing
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include <string.h>

#include "GUI.h"

#if GUI_SUPPORT_AA

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_AA_DrawPolyOutline
*/
void GUI_AA_DrawPolyOutline(const GUI_POINT* pSrc, int NumPoints, int Thickness, int x, int y) {
  U8 PrevDraw;
  GUI_POINT aiTemp[10];
  GUI_EnlargePolygon(&aiTemp[0], pSrc, NumPoints, Thickness);
  GUI_AA_FillPolygon( &aiTemp[0], NumPoints, x, y );
  PrevDraw = LCD_SetDrawMode(GUI_DRAWMODE_REV);
/* Copy points due to const qualifier */
  memcpy(aiTemp, pSrc, NumPoints*2*sizeof(GUI_POINT));
  GUI_AA_FillPolygon( aiTemp, NumPoints, x, y );
  LCD_SetDrawMode(PrevDraw);
}

#else                            /* Avoid problems with empty object modules */
  void GUIAAPolyOut_C(void);
  void GUIAAPolyOut_C(void) {}
#endif /* GUI_SUPPORT_AA */

/*************************** End of file ****************************/
