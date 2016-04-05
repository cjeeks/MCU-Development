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
File        : GUIDEV_Clear.c
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
*       GUI_MEMDEV_Clear
*/
void GUI_MEMDEV_Clear(GUI_MEMDEV_Handle hMem) {
  if (!hMem) {
    if ((hMem = GUI_Context.hDevData) == 0) {
      return;
    }
  }
  {
    GUI_MEMDEV* pDev;
    GUI_USAGE_h hUsage;
    GUI_LOCK();
    pDev = GUI_MEMDEV_H2P(hMem);  /* Convert to pointer */
    hUsage = pDev->hUsage; 
    if (hUsage) {
      GUI_USAGE* pUsage = GUI_USAGE_H2P(hUsage);
      GUI_USAGE_Clear(pUsage);
    }
    GUI_UNLOCK();
  }
}

#else

void GUIDEV_Clear(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */

/*************************** end of file ****************************/
