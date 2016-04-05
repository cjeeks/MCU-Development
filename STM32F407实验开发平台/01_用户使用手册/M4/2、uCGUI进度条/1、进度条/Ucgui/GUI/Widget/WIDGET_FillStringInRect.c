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
File        : WIDGET_FillStringInRect.c
Purpose     : Implementation of widget function
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI_Protected.h"

#if GUI_WINSUPPORT

#include "WM.h"
#include "WIDGET.h"

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

#ifndef WIDGET_FILL_TEXT_USES_TRANS
  #define WIDGET_FILL_TEXT_USES_TRANS 0
#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       WIDGET__FillStringInRect
*
* Purpose
*
* Parameters
*
* Notes
*/
void WIDGET__FillStringInRect(const char GUI_UNI_PTR * pText, const GUI_RECT * pFillRect, const GUI_RECT * pTextRectMax, const GUI_RECT * pTextRectAct) {
  /* Check if we have anything to do at all ... */
  if (GUI_Context.pClipRect_HL) {
    GUI_RECT r;
    r = *pFillRect;
    WM_ADDORG(r.x0, r.y0);
    WM_ADDORG(r.x1, r.y1);
    if (GUI_RectsIntersect(GUI_Context.pClipRect_HL, &r) == 0)
      return;
  }

  if (pText) {
    if (*pText) {             /* Speed optimization, not required */
      const GUI_RECT* pOldClipRect;


      /* Fill border */
      #if WIDGET_FILL_TEXT_USES_TRANS
        GUI_ClearRectEx(pFillRect);
      #else
        {
          GUI_RECT rText;
          GUI__IntersectRects(&rText, pTextRectMax, pTextRectAct);
          GUI_ClearRect(pFillRect->x0, pFillRect->y0, pFillRect->x1, rText.y0 - 1); /* Top */
          GUI_ClearRect(pFillRect->x0, rText.y0,      rText.x0 - 1 , rText.y1);     /* Left */
          GUI_ClearRect(rText.x1 + 1,  rText.y0,      pFillRect->x1, rText.y1);     /* Right */
          GUI_ClearRect(pFillRect->x0, rText.y1 + 1,  pFillRect->x1, pFillRect->y1);/* Bottom */
        }
      #endif

      /* Set clipping rectangle */
      pOldClipRect = WM_SetUserClipRect(pTextRectMax);

      /* Display text */
      #if WIDGET_FILL_TEXT_USES_TRANS
        GUI_SetTextMode(GUI_TM_TRANS);
      #else
        GUI_SetTextMode(GUI_TM_NORMAL);
      #endif
      GUI_DispStringAt(pText, pTextRectAct->x0, pTextRectAct->y0);

      /* Restore clipping rectangle */
      WM_SetUserClipRect(pOldClipRect);
      return;
    }
  }
  GUI_ClearRectEx(pFillRect);
}

#else  /* avoid empty object files */

void WIDGET__FillStringInRect_C(void) {}

#endif

/*************************** End of file ****************************/
