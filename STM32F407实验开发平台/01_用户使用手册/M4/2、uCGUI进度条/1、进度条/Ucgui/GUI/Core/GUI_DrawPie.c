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
File        : GUIARCFloat.C
Purpose     : Draw Arc routines based on floating point
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawPie
*/
static void _DrawPie(int x0, int y0, unsigned int r, int Angle0, int Angle1, int Type) {
  int PenSizeOld;
  PenSizeOld = GUI_GetPenSize();
  GUI_SetPenSize(r);
  r /= 2;
  GL_DrawArc(x0,y0,r,r,Angle0, Angle1);
  GUI_SetPenSize(PenSizeOld);
  GUI_USE_PARA(Type);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawPie
*/
void GUI_DrawPie(int x0, int y0, int r, int a0, int a1, int Type) {
  GUI_LOCK();
  #if GUI_WINSUPPORT
    WM_ADDORG(x0,y0);
    WM_ITERATE_START(NULL) {
  #endif
  _DrawPie( x0, y0, r, a0, a1, Type);
  #if GUI_WINSUPPORT
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
