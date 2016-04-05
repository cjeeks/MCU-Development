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
File        : GUIDEV_GetDataPtr.c
Purpose     : Implementation of said function
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MEMDEV_GetDataPtr
*/
void* GUI_MEMDEV_GetDataPtr(GUI_MEMDEV_Handle hMem) {
  GUI_MEMDEV* pDev;
  void *pData;
  GUI_LOCK();                   /* Needed so the memory management does not complain */
  pDev  = GUI_MEMDEV_H2P(hMem);
  GUI_UNLOCK();
  pData = (void*)(pDev + 1);
  return pData;
}


#else

void GUI_MEMDEV_GetDataPtr_C(void) {}

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
