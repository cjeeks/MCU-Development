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
File        : GUIDEV_SetOrg.c
Purpose     : Implementation of memory devices, add. module
---------------------------END-OF-HEADER------------------------------
*/


#include "GUI_Protected.h"
#include "GUIDebug.h"
#include <string.h>

/* Memory device capabilities are compiled only if support for them is enabled. */ 
#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MEMDEV_SetOrg
*/
void GUI_MEMDEV_SetOrg(GUI_MEMDEV_Handle hMem, int x0, int y0) {
  /* Make sure memory handle is valid */
  if (!hMem) {
    if ((hMem = GUI_Context.hDevData) ==0) {
      return;
    }
  }
  GUI_LOCK();
  {
    GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(hMem);  /* Convert to pointer */
    pDev->y0 = y0;
    pDev->x0 = x0;
    LCD_SetClipRectMax();
    /* Move usage along */
    if (pDev->hUsage) {
      GUI_USAGE* pUsage = GUI_USAGE_H2P(pDev->hUsage);
      if (((pUsage->XSize = pDev->XSize) != 0) && ((pUsage->YSize = pDev->YSize) != 0)) {
        pUsage->x0 = x0;
        pUsage->y0 = y0;
      }
    }
  }
  GUI_UNLOCK();
}

#else

void GUIDEV_SetOrg(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */

/*************************** end of file ****************************/
