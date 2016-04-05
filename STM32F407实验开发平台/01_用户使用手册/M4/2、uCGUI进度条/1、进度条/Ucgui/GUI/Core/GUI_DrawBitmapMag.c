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
File        : GUI_DrawBitmapMag.C
Purpose     : Implementation file for GUI_DrawBitmapMag
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DrawBitmapMag
*/
void GUI_DrawBitmapMag(const GUI_BITMAP GUI_UNI_PTR *pBitmap, int x0, int y0, int xMul, int yMul) {
  GUI_DRAWMODE PrevDraw;
  int xSize, ySize;
  const GUI_LOGPALETTE GUI_UNI_PTR * pPal;
  const LCD_PIXELINDEX* pTrans;
  GUI_LOCK();
  pPal = pBitmap->pPal;
  xSize = pBitmap->XSize;
  ySize = pBitmap->YSize;
  pTrans = LCD_GetpPalConvTable(pPal);
  if (!pTrans) {
    pTrans = (pBitmap->BitsPerPixel != 1) ? NULL : &LCD_BKCOLORINDEX;
  }
  PrevDraw = GUI_SetDrawMode((pPal && pPal->HasTrans) ? GUI_DRAWMODE_TRANS : 0);
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    {
      GUI_RECT r;
      r.x0 = x0;
      r.x1 = x0 + xSize * xMul -1;
      r.y0 = y0;
      r.y1 = y0 + ySize * yMul -1;
      WM_ITERATE_START(&r);
  #endif
  if (pBitmap->pMethods) {
    #if GUI_COMPILER_SUPPORTS_FP      /* Do not support this on VERY simple chips and compilers */
      pBitmap->pMethods->pfDraw(x0, y0, pBitmap->XSize ,pBitmap->YSize, (U8 const *)pBitmap->pData, pBitmap->pPal, xMul, yMul);
    #endif
  } else {
    LCD_DrawBitmap(x0, y0, xSize, ySize, xMul, yMul
                    ,pBitmap->BitsPerPixel, pBitmap->BytesPerLine
                    ,pBitmap->pData, pTrans);
  }
  #if (GUI_WINSUPPORT)
      WM_ITERATE_END();
    }
  #endif
  GUI_SetDrawMode(PrevDraw);
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
