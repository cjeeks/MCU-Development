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
File        : GUIAALine.C
Purpose     : Drawing lines with antialiasing
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"
#include <stddef.h>

#if GUI_SUPPORT_AA

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _AA_DrawLine
*/
static void _AA_DrawLine(int x0, int y0, int x1, int y1) {
  int xMin, xMax;
  U8 PenSizeOld = GUI_GetPenSize();
  U8 PenSizeHR  = PenSizeOld * GUI_Context.AA_Factor;
  U8 OldPenShape = GUI_SetPenShape(GUI_PS_FLAT);
  /* Calculate left and right borders for AA module */
  if (x0 < x1) {
    xMin = x0;
    xMax = x1;
  } else {
    xMin = x1;
    xMax = x0;
  }
  if (GUI_Context.AA_HiResEnable) {
    xMin -= PenSizeHR;
    xMax += PenSizeHR;
    xMin /= GUI_Context.AA_Factor;
    xMax /= GUI_Context.AA_Factor;
  } else {
    xMin -= PenSizeOld;
    xMax += PenSizeOld;
    x0 *= GUI_Context.AA_Factor;
    x1 *= GUI_Context.AA_Factor;
    y0 *= GUI_Context.AA_Factor;
    y1 *= GUI_Context.AA_Factor;
  }
  /* Do the actual drawing */
  GUI_AA_Init(xMin, xMax);
  GUI_SetPenSize(PenSizeHR);
  GL_DrawLine(x0 , y0 , x1 ,  y1 );
  GUI_AA_Exit();
  /* Draw end points (can be optimized away in future, TBD*/
  switch (OldPenShape) {
  case GUI_PS_ROUND:
    {
      int r = GUI_Context.AA_Factor * PenSizeOld / 2;
      GL_FillCircleAA_HiRes(x0 , y0 , r);
      GL_FillCircleAA_HiRes(x1 , y1 , r);
    }
    break;
  }
  GUI_SetPenSize(PenSizeOld);
  GUI_SetPenShape(OldPenShape);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_AA_DrawLine
*/
void GUI_AA_DrawLine(int x0, int y0, int x1, int y1) {
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG_AA(x0,y0);
    WM_ADDORG_AA(x1,y1);
    WM_ITERATE_START(NULL); {
  #endif
  _AA_DrawLine(x0, y0, x1, y1);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

#else                            /* Avoid problems with empty object modules */
  void GUIAALine_C(void);
  void GUIAALine_C(void) {}
#endif /* GUI_SUPPORT_AA */

/*************************** End of file ****************************/
