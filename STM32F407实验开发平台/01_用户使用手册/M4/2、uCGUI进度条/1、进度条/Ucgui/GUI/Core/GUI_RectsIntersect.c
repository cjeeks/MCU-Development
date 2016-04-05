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
File        : GUI_RectsIntersect.C
Purpose     : Implementation of GUI_RectsIntersect
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_RectsIntersect
*
* Purpose:
*   Check if rectangle do intersect.
*
* Return value:
*   0 if they do not.
*   1 if they do.
*/
int GUI_RectsIntersect(const GUI_RECT* pr0, const GUI_RECT* pr1) {
  if (pr0->y0 <= pr1->y1) {
    if (pr1->y0 <= pr0->y1) {
      if (pr0->x0 <= pr1->x1) {
        if (pr1->x0 <= pr0->x1) {
          return 1;
        }
      }
    }
  }
  return 0;
}

/*************************** End of file ****************************/
