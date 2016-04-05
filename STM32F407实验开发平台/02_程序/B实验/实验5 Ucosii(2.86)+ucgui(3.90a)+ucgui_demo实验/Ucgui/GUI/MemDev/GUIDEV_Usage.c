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
File        : GUIDEV_Usage.C
Purpose     : Implementation of memory devices
---------------------------END-OF-HEADER------------------------------
*/


#include <string.h>
#include "GUI_Protected.h"
#include "GUIDebug.h"

/* Memory device capabilities are compiled only if support for them is enabled.*/ 
#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_USAGE_Select
*/
void GUI_USAGE_Select(GUI_USAGE_Handle hUsage) {
  GUI_MEMDEV * pDev;
  GUI_LOCK();
  pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  pDev->hUsage = hUsage;
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_USAGE_DecUseCnt
*
* Purpose: Decrements the usage count and deletes the usage object if
*          the counter reaches 0.
*/
void GUI_USAGE_DecUseCnt(GUI_USAGE_Handle  hUsage) {
  GUI_USAGE* pThis;
  GUI_LOCK();
  pThis = GUI_USAGE_H2P(hUsage);
  if (--pThis->UseCnt == 0) {
    GUI_ALLOC_Free(hUsage);
  }
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_USAGE_AddRect
*
* Parameters:
*   hUsage: Handle to usage object. May not be 0 !
*/
void GUI_USAGE_AddRect(GUI_USAGE*  pUsage, int x0, int y0, int xSize, int ySize) {
  do {
    GUI_USAGE_AddHLine(pUsage, x0, y0++, xSize);
  } while (--ySize);
}

#else

void GUIDEV_Usage(void) {} /* avoid empty object files */

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
