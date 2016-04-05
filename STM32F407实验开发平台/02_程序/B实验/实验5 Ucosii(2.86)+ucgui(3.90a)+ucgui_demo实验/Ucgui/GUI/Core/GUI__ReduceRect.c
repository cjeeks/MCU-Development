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
File        : GUI__ReduceRect.C
Purpose     : Implementation of GUI__ReduceRect
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__ReduceRect
*/
void GUI__ReduceRect(GUI_RECT* pDest, const GUI_RECT *pRect, int Dist) {
  pDest->x0 = pRect->x0 + Dist;
  pDest->x1 = pRect->x1 - Dist;
  pDest->y0 = pRect->y0 + Dist;
  pDest->y1 = pRect->y1 - Dist;
}

/*************************** End of file ****************************/
