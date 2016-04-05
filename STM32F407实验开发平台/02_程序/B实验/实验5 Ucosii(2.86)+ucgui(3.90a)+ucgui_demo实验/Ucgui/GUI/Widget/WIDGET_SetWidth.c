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
File        : WIDGET_SetWidth.c
Purpose     : Implementation of WIDGET_SetWidth
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
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WIDGET_SetWidth
*
* Function:
*   Set width of the given widget. Width can be X-Size or Y-Size,
*   depending on if the widget is rotated.
*/
int WIDGET_SetWidth(WM_HWIN hObj, int Width) {
  WIDGET* pWidget;
  int r = 0;
  if (hObj) {
    WM_LOCK();
    pWidget = WIDGET_H2P(hObj);
    if (pWidget->State & WIDGET_STATE_VERTICAL) {
      r = WM_SetXSize(hObj, Width);
    } else {
      r = WM_SetYSize(hObj, Width);
    }
    WM_UNLOCK();
  }
  return r;
}


#else                            /* Avoid problems with empty object modules */
  void WIDGET_SetWidth_C(void) {}
#endif /* GUI_WINSUPPORT */




