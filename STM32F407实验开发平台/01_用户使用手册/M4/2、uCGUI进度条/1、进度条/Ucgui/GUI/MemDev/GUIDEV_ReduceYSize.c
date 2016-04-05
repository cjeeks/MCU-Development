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
File        : GUIDEV_ReduceYSize.c
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
*       GUI_MEMDEV_ReduceYSize
*/
void GUI_MEMDEV_ReduceYSize(GUI_MEMDEV_Handle hMem, int YSize) {
  /* Make sure memory handle is valid */
  if (!hMem)
    hMem = GUI_Context.hDevData;
  if (!hMem)
    return;
  { 
    GUI_MEMDEV * pDevData;
    GUI_LOCK();
    pDevData = (GUI_MEMDEV*) GUI_ALLOC_h2p(hMem);  /* Convert to pointer */
    if (YSize < pDevData->YSize) {
      pDevData->YSize = YSize;
    }
    GUI_UNLOCK();
  }
}

#else
        
void GUIDEV_ReduceYSize(void) {} /* avoid empty object files */

#endif /* GUI_MEMDEV_SUPPORT */

/*************************** end of file ****************************/
