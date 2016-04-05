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
File        : GUIDEV_CmpWithLCD.c
Purpose     : Implementation of Checking for memory devices
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
1.00    000418 RS     First version for release (all tests O.K.)
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>
#include "GUI_Private.h"
#include "GUIDebug.h"

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
*       GUI_MEMDEV_CompareWithLCD
*/
int GUI_MEMDEV_CompareWithLCD(GUI_MEMDEV_Handle hMem, int*px, int*py, int *pExp, int*pAct) {
  int Ret = 0;
  /* Make sure memory handle is valid */
  if (!hMem) {
    hMem = GUI_Context.hDevData;
  }
  if (!hMem) {
    return 1;
  }
  GUI_LOCK();
  {
    GUI_MEMDEV * pDevData = (GUI_MEMDEV*) GUI_ALLOC_h2p(hMem);  /* Convert to pointer */
    int y    = pDevData->y0;
    int x0   = pDevData->x0;
    int XMax = pDevData->XSize + x0;
    int YMax = pDevData->YSize + y;
    int Max;
    int MagX = LCD_GetXMag();
    int MagY = LCD_GetYMag();
    /* Calculate limits */
    if (y < 0) {
			y = 0;
    }
    if (x0 < 0) {
			x0 = 0;
    }
    Max = LCD_GET_YSIZE();
		if (YMax > Max) {
			YMax = Max;
    }
    Max = LCD_GET_XSIZE();
		if (XMax > Max) {
			XMax = Max;
    }
    for (; y < YMax; y++) {
      int x = x0;
      U8 * pData = (U8 *)GUI_MEMDEV__XY2PTR(x, y);
      for (x = x0; x < XMax; x++) {
        int Exp = *pData++;
        int Act = LCD_L0_GetPixelIndex(x * MagX, y * MagY);
        #if (GUI_NUM_LAYERS > 1)
        if (LCD_GetBitsPerPixelEx(GUI_Context.SelLayer) > 8)
        #else
        if (LCD_GetBitsPerPixel() > 8)
        #endif
        {
          Exp |= (*pData++) << 8;
        }
        if (Act != Exp) {
          *px    = x;
          *py    = y;
          *pAct  = Act;
          *pExp  = Exp;
          Ret = 1;
          goto Skip;
        }
      }
    }
  }
Skip:
  GUI_UNLOCK();
  return Ret;
}

#else

void GUIDEV_CmpWithLCD(void) {} /* avoid empty object files */

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
