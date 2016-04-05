/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIDev.C
Purpose     : Implementation of memory devices
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "GUI_Private.h"
#include "GUIDebug.h"

/* Memory device capabilities are compiled only if support for them is enabled.*/ 
#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*        GUI_MEMDEV_WriteAt
*/
void GUI_MEMDEV_WriteAt(GUI_MEMDEV_Handle hMem, int x, int y) {
  if (hMem) {
    GUI_MEMDEV* pDevData;
    #if (GUI_WINSUPPORT)
      GUI_RECT r;
    #endif
    GUI_LOCK();
    pDevData = (GUI_MEMDEV*) GUI_ALLOC_h2p(hMem);  /* Convert to pointer */
    if (x == GUI_POS_AUTO) {
      x = pDevData->x0;
      y = pDevData->y0;
    }
    #if (GUI_WINSUPPORT)
      /* Calculate rectangle */
      r.x1 = (r.x0 = x) + pDevData->XSize-1;
      r.y1 = (r.y0 = y) + pDevData->YSize-1;;
      /* Do the drawing. WIndow manager has to be on */
      WM_ITERATE_START(&r) {
        GUI_MEMDEV__WriteToActiveAt(hMem,x,y);
      } WM_ITERATE_END();
    #else
      GUI_MEMDEV__WriteToActiveAt(hMem,x,y);
    #endif
    GUI_UNLOCK();
  }
}

/*********************************************************************
*
*       GUI_MEMDEV_Write
*/
void GUI_MEMDEV_Write(GUI_MEMDEV_Handle hMem) {
  GUI_MEMDEV_WriteAt(hMem, GUI_POS_AUTO, GUI_POS_AUTO);
}

#else

void GUIDEV_Write_C(void) {}

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
