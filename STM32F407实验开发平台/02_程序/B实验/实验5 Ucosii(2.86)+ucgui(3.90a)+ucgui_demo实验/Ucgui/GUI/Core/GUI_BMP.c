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
File        : GUI_BMP.c
Purpose     : Implementation of GUI_BMP... functions
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI_Private.h"

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _GetStep
*/
static int _GetStep(int * pYSize, int * pY) {
  if (*pYSize > 0) {
    *pY = *pYSize - 1;
    return -1;
  } else if (*pYSize < 0) {
    *pYSize = -*pYSize;
    *pY = 0;
    return 1;
  } else {
    return 0;
  }
}

/*********************************************************************
*
*       _DrawBitmap_Pal
*/
static int _DrawBitmap_Pal(const U8 * pData, int x0, int y0, int XSize, int YSize, int Bpp, int NumColors) {
  int i, y, Step;
  int BytesPerLine = 0;
  Step = _GetStep(&YSize, &y);
  if (!Step) {
    return 1;
  }
  for (i = 0; i < NumColors; i++) {
    U8 r, g, b;
    b = *(pData);
    g = *(pData + 1);
    r = *(pData + 2);
    pData += 4;
    LCD__aConvTable[i] = LCD_Color2Index(((U32)b << 16) | (g << 8) | r);
  }
  switch (Bpp) {
    case 1:
      BytesPerLine = ((XSize + 31) >> 5) << 2;
      break;
    case 4:
      BytesPerLine = (((XSize << 2) + 31) >> 5) << 2;
      break;
    case 8:
      BytesPerLine = ((XSize +  3) >> 2) << 2;
      break;
  }
  for (; (y < YSize) && (y >= 0); y += Step) {
    LCD_DrawBitmap(x0, y0 + y, XSize, 1, 1, 1, Bpp, XSize, pData, LCD__aConvTable);
    pData += BytesPerLine;
  }
  return 0;
}

/*********************************************************************
*
*       _DrawBitmap_24bpp
*/
static int _DrawBitmap_24bpp(const U8 * pData, int x0, int y0, int XSize, int YSize) {
  int x, y, BytesPerLine, Step;
  Step = _GetStep(&YSize, &y);
  if (!Step) {
    return 1;
  }
  BytesPerLine = ((24 * XSize + 31) >> 5) << 2;
  for (; (y < YSize) && (y >= 0); y += Step) {
    for (x = 0; x < XSize; x++) {
      const U8 * pColor = pData + 3 * x;
      U8 r, g, b;
      b = *(pColor);
      g = *(pColor + 1);
      r = *(pColor + 2);
      LCD_SetPixelIndex(x0 + x, y0 + y, LCD_Color2Index(((U32)b << 16) | (g << 8) | r));
    }
    pData += BytesPerLine;
  }
  return 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_BMP_GetXSize
*/
int GUI_BMP_GetXSize(const void * pBMP) {
  const U8 * pSrc = (const U8 *)pBMP;
  if (!pBMP) {
    return 0;
  }
  pSrc += 18;                   /* skip rest of BITMAPFILEHEADER */
  return GUI__Read32(&pSrc);
}

/*********************************************************************
*
*       GUI_BMP_GetYSize
*/
int GUI_BMP_GetYSize(const void * pBMP) {
  const U8 * pSrc = (const U8 *)pBMP;
  if (!pBMP) {
    return 0;
  }
  pSrc += 22;
  return labs((int)GUI__Read32(&pSrc));
}

/*********************************************************************
*
*       GUI_BMP_Draw
*/
int GUI_BMP_Draw(const void * pBMP, int x0, int y0) {
  #if (GUI_WINSUPPORT)
    GUI_RECT r;
  #endif
  int Ret = 0;
  I32 Width, Height;
  U16 BitCount, Type;
  U32 ClrUsed, Compression;
  int NumColors;
  const U8 * pSrc = (const U8 *)pBMP;
  Type        = GUI__Read16(&pSrc); /* get type from BITMAPFILEHEADER */
  pSrc += 12;                   /* skip rest of BITMAPFILEHEADER */
  /* get values from BITMAPINFOHEADER */
  pSrc += 4;
  Width       = GUI__Read32(&pSrc);
  Height      = GUI__Read32(&pSrc);
  pSrc += 2;
  BitCount    = GUI__Read16(&pSrc);
  Compression = GUI__Read32(&pSrc);
  pSrc += 12;
  ClrUsed     = GUI__Read32(&pSrc);
  pSrc += 4;
  /* calculate number of colors */
  switch (BitCount) {
    case 0:   return 1; /* biBitCount = 0 (JPEG format) not supported. Please convert image ! */
    case 1:   NumColors = 2;   break;
    case 4:   NumColors = 16;  break;
    case 8:   NumColors = 256; break;
    case 24:  NumColors = 0;   break;
    default:
      return 1; /* biBitCount should be 1, 4, 8 or 24 */
  }
  if (NumColors && ClrUsed) {
    NumColors = ClrUsed;
  }
  /* check validity of bmp */
  if ((NumColors > LCD_MAX_LOG_COLORS) ||
      (Type != 0x4d42)                 || /* 'BM' */
      (Compression)                    || /* only uncompressed bitmaps */
      (Width  > 1024)                  ||
      (Height > 1024)) {
    return 1;
  }
  /* start output */
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    r.x1 = (r.x0 = x0) + Width - 1;
    r.y1 = (r.y0 = y0) + Height - 1;
    WM_ITERATE_START(&r) {
  #endif
  /* Show bitmap */
  switch (BitCount) {
    case 1:
    case 4:
    case 8:
      Ret = _DrawBitmap_Pal(pSrc, x0, y0, Width, Height, BitCount, NumColors);
      break;
    case 24:
      Ret = _DrawBitmap_24bpp(pSrc, x0, y0, Width, Height);
      break;
  }
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
  return Ret;
}

/*************************** End of file ****************************/
