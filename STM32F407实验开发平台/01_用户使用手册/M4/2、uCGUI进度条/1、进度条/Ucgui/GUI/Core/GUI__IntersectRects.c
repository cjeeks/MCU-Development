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
File        : GUI_IntersectRects.c
Purpose     : Implementation of GUI_IntersectRects
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Macros
*
**********************************************************************
*/

#define MIN(v0,v1) ((v0>v1) ? v1 : v0)
#define MAX(v0,v1) ((v0>v1) ? v0 : v1)

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__IntersectRects
*
* Purpose:
*   Calc intersection of rectangles
*
* Return value:
*   1 if they do intersect,
*   0 if there is no intersection
*
* Add. info:
*   Rectangles are passed as pointers. These pointers need to be valid;
*   a NULL pointer may not be passed. There is no check for NULL pointers
*   implemented in order to avoid avoid performance penalty.
*/
int GUI__IntersectRects(GUI_RECT* pDest, const GUI_RECT* pr0, const GUI_RECT* pr1) {
  pDest->x0 = MAX (pr0->x0, pr1->x0);
  pDest->y0 = MAX (pr0->y0, pr1->y0);
  pDest->x1 = MIN (pr0->x1, pr1->x1);
  pDest->y1 = MIN (pr0->y1, pr1->y1);
  if (pDest->x1 < pDest->x0) {
    return 0;
  }
  if (pDest->y1 < pDest->y0) {
    return 0;
  }
  return 1;
}

/*************************** End of file ****************************/
