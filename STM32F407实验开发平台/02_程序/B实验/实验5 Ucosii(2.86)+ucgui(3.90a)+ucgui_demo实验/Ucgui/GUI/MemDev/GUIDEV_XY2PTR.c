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
File        : GUIDEV_XY2PTR.c
Purpose     : Implementation of memory devices
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"
#include "GUIDebug.h"

#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       modul internal routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MEMDEV__XY2PTR
*/
void* GUI_MEMDEV__XY2PTR(int x, int y) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  U8 *pData = (U8*)(pDev + 1);
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    if ((x >= pDev->x0+pDev->XSize) | (x<pDev->x0) | (y >= pDev->y0+pDev->YSize) | (y<pDev->y0)) {
      GUI_DEBUG_ERROROUT2("GUI_MEMDEV__XY2PTR: parameters out of bounds",x,y);
    }
  #endif
  pData += (y - pDev->y0) * pDev->BytesPerLine;
  return pData + (x - pDev->x0) * (pDev->BitsPerPixel / 8);
}

/*********************************************************************
*
*       GUI_MEMDEV__XY2PTREx
*/
void* GUI_MEMDEV__XY2PTREx(GUI_MEMDEV* pDev, int x, int y) {
  U8 *pData = (U8*)(pDev + 1);
  pData += y * pDev->BytesPerLine;
  return pData + x * (pDev->BitsPerPixel / 8);
}

#else

void GUIDEV_XY2PTR_C(void) {}

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
