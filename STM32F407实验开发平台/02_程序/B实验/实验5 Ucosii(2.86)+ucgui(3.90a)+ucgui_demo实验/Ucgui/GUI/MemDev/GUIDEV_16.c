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
File        : GUIDEV_16.c
Purpose     : Implementation of memory devices
---------------------------END-OF-HEADER------------------------------
*/


#include <string.h>
#include "GUI_Private.h"
#include "GUIDebug.h"
#if GUI_WINSUPPORT
  #include "WM.h"
#endif

/* Memory device capabilities are compiled only if support for them is enabled.*/ 
#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       Macros
*
**********************************************************************
*/

#define PIXELINDEX                      U16
#define BITSPERPIXEL                     16
#define API_LIST      GUI_MEMDEV__APIList16

/*********************************************************************
*
*       _DrawBitLine16BPP_DDB
*/
static void _DrawBitLine16BPP_DDB(GUI_USAGE* pUsage, int x, int y, const U16 *pSrc, int xsize, PIXELINDEX* pDest) {
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    memcpy(pDest, pSrc, xsize * 2);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      if (*pSrc) {
        *pDest = *pSrc;
        if (pUsage) {
          GUI_USAGE_AddPixel(pUsage, x, y);
        }
      }
      x++;
      pDest++;
      pSrc++;
    } while (--xsize);
    break;
  }
}

/*********************************************************************
*
*       #include GUIDev code
*
**********************************************************************
*
* The main code is in an other "C" file.
* This has been done to avoid duplication of code.
*/
#include "GUIDEV_8.c"

#else

void GUIDEV16_C(void) {}

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
