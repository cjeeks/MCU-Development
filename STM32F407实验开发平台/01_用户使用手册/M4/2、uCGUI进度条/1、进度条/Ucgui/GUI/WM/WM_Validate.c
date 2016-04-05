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
File        : WM_Validate.C
Purpose     : Windows manager, add. module
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*        Macros for internal use
*
**********************************************************************
*/

#define Min(v0,v1) ((v0>v1) ? v1 : v0)
#define Max(v0,v1) ((v0>v1) ? v0 : v1)

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__SubRect       

  The result is the smallest rectangle which includes the entire
  remaining area.

  *pDest = *pr0- *pr1;
*/
static void _SubRect(GUI_RECT* pDest, const GUI_RECT* pr0, const GUI_RECT* pr1) {
  if ((pDest == NULL) || (pr0 == NULL))
    return;
  *pDest = *pr0;	 
  if (pr1 == NULL)
    return;
  /* Check left/right sides */
  if (  (pr1->y0 <= pr0->y0)
      &&(pr1->y1 >= pr0->y1)) {
    pDest->x0 = Max(pr0->x0, pr1->x1);
    pDest->x1 = Min(pr0->x1, pr1->x0);
  }
  /* Check top/bottom sides */
  if (  (pr1->x0 <= pr0->x0)
      &&(pr1->x1 >= pr0->x1)) {
    pDest->y0 = Max(pr0->y0, pr1->y1);
    pDest->y1 = Min(pr0->y1, pr1->y0);
  }
}

/*********************************************************************
*
*       WM_ValidateRect
*
  Use this function with great care ! It should under most circumstances not
  be necessary to use it, as validation is done automatically as soon as
  a window has been redrawn. If you validate a section of a window, this
  part will not be included in the paint-command and could therefor not
  be updated.
*/
void WM_ValidateRect(WM_HWIN hWin, const GUI_RECT*pRect) {
  WM_Obj* pWin;
  if (hWin) {
    WM_LOCK();
    pWin = WM_HANDLE2PTR(hWin);
    if (pWin->Status & WM_SF_INVALID) {
      if (pRect) {
        _SubRect(&pWin->InvalidRect, &pWin->InvalidRect, pRect);
        if (WM__RectIsNZ(&pWin->InvalidRect))
          goto Done;
      }
      pWin->Status &= ~WM_SF_INVALID;
      WM__NumInvalidWindows--;
    }
  Done:
    WM_UNLOCK();
  }
}

#else
  void WM_Validate(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
