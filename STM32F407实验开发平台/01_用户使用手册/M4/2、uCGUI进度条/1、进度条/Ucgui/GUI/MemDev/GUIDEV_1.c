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
File        : GUIDEV_1.c
Purpose     : Implementation of memory devices
              This file handles 1 bit memory devices.
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

#ifndef PIXELINDEX
  #define PIXELINDEX                      U8
  #define BITSPERPIXEL                     1
  #define API_LIST      GUI_MEMDEV__APIList1
#endif

/*********************************************************************
*
*       static consts
*
**********************************************************************
*/
/*********************************************************************
*
*       ID translation table
*
* This table serves as translation table for DDBs
*/
static const LCD_PIXELINDEX aID[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _XY2PTR_BITOFFSET
*/
static U8* _XY2PTR_BITOFFSET(int x, int y, int* pBitOffset) {
  GUI_ALLOC_DATATYPE_U Offset;
  GUI_MEMDEV* pDev;
  U8* pData;
  pDev  = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  pData = (U8*)(pDev + 1);
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    if ((x >= pDev->x0+pDev->XSize) | (x<pDev->x0) | (y >= pDev->y0+pDev->YSize) | (y<pDev->y0)) {
      GUI_DEBUG_ERROROUT2("_XY2PTR: parameters out of bounds", x, y);
    }
  #endif
  x -= pDev->x0;
  y -= pDev->y0;
  Offset = (GUI_ALLOC_DATATYPE_U)(y) * (GUI_ALLOC_DATATYPE_U)(pDev->BytesPerLine) + (x >> 3);
  if (pBitOffset) {
    *pBitOffset = 7 - (x & 7);
  }
  return pData + Offset;
}

/*********************************************************************
*
*       _DrawBitLine1BPP
*/
static void _DrawBitLine1BPP(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * p, int Diff, unsigned int xsize,
                             const LCD_PIXELINDEX* pTrans, GUI_MEMDEV* pDev, PIXELINDEX* pDest)
{
  PIXELINDEX pixels;
  PIXELINDEX Index1;
  unsigned int PixelCnt;
  GUI_USE_PARA(pUsage);
  PixelCnt = 8 - (Diff & 7);
  pixels = (*p) << (Diff & 7);
  GUI_DEBUG_ERROROUT3_IF( x < pDev->x0, "GUIDEV.c: DrawBitLine1BPP, Act= %d, Border= %d, Clip= %d"
                    ,x,pDev->x0, GUI_Context.ClipRect.x0);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    do {
      /* Prepare loop */
      if (PixelCnt > xsize) {
        PixelCnt = xsize;
      }
      xsize -= PixelCnt;
      /* Write as many pixels as we are allowed to and have loaded in this inner loop */
      do {
        (*pDev->pAPIList->pfSetPixelIndex)(x++, y, *(pTrans + ((U8)pixels >> 7)));
        pixels <<= 1;
      } while (--PixelCnt);
      /* Check if an other Source byte needs to be loaded */
      if (xsize == 0) {
        return;
      }
      PixelCnt = 8;
      pixels = *(++p);
    } while (1);
  case LCD_DRAWMODE_TRANS:
    Index1 = *(pTrans + 1);
    do {
      /* Prepare loop */
      if (PixelCnt > xsize) {
        PixelCnt = xsize;
      }
      xsize -= PixelCnt;
      while (pixels) {
        if ((pixels & 0x80)) {
          (*pDev->pAPIList->pfSetPixelIndex)(x, y, Index1);
        }
        x++;
        pixels <<= 1;
        if (--PixelCnt == 0) {
          break;
        }
      }
      /* Check if an other Source byte needs to be loaded */
      if (xsize == 0) {
        return;
      }
      x += PixelCnt;
      PixelCnt = 8;
      pixels = *(++p);
    } while (1);
  case LCD_DRAWMODE_XOR:;
  PixelLoopXor:
    if (PixelCnt > xsize) {
      PixelCnt = xsize;
    }
    xsize -= PixelCnt;
    do {
      if ((pixels & 0x80)) {
        (*pDev->pAPIList->pfXorPixel)(x, y);
      }
      x++;
      pDest++;
      pixels <<= 1;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt = 8;
      pixels = *(++p);
      goto PixelLoopXor;
    }
    break;
  }
}

/*********************************************************************
*
*       _DrawBitLine2BPP
*/
static void _DrawBitLine2BPP(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * p, int Diff, int xsize,
                             const LCD_PIXELINDEX* pTrans, GUI_MEMDEV* pDev, PIXELINDEX* pDest)
{
  U8 pixels;
  U8  PixelCnt;
  GUI_USE_PARA(pUsage);
  GUI_USE_PARA(pDest);
  PixelCnt = 4 - (Diff & 3);
  pixels = (*p) << ((Diff & 3) << 1);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
  PixelLoopWrite:
    if (PixelCnt > xsize) {
      PixelCnt = xsize;
    }
    xsize -= PixelCnt;
    do {
      (*pDev->pAPIList->pfSetPixelIndex)(x++, y, *(pTrans + (pixels >> 6)));
      pixels <<= 2;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt = 4;
      pixels = *(++p);
      goto PixelLoopWrite;
    }
    break;
  case LCD_DRAWMODE_TRANS:
  PixelLoopTrans:
    if (PixelCnt > xsize)
      PixelCnt = xsize;
    xsize -= PixelCnt;
    do {
      if (pixels & 0xc0) {
        (*pDev->pAPIList->pfSetPixelIndex)(x, y, *(pTrans + (pixels >> 6)));
      }
      x++;
      pixels <<= 2;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt = 4;
      pixels = *(++p);
      goto PixelLoopTrans;
    }
    break;
  }
}

/*********************************************************************
*
*       _DrawBitLine4BPP
*/
static void _DrawBitLine4BPP(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * p, int Diff, int xsize,
                             const LCD_PIXELINDEX* pTrans, GUI_MEMDEV* pDev, PIXELINDEX* pDest)
{
  U8 pixels;
  GUI_USE_PARA(pUsage);
  GUI_USE_PARA(pDest);
  pixels = (*p) << ((Diff & 1) << 2);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
/*
          * Write mode *
*/
  case 0:
    /* Draw incomplete bytes to the left of center area */
    if (Diff) {
      (*pDev->pAPIList->pfSetPixelIndex)(x++, y, *(pTrans + (pixels >> 4)));
      xsize--;
      pixels = *++p;
    }
    /* Draw center area (2 pixels in one byte) */
    if (xsize >= 2) {
      int i = xsize >> 1;
      xsize &= 1;
      do {
        (*pDev->pAPIList->pfSetPixelIndex)(x++, y, *(pTrans + (pixels >>  4)));
        (*pDev->pAPIList->pfSetPixelIndex)(x++, y, *(pTrans + (pixels  & 15)));
        pixels = *++p;
      } while (--i);
    }
    /* Draw incomplete bytes to the right of center area */
    if (xsize) {
      (*pDev->pAPIList->pfSetPixelIndex)(x++, y, *(pTrans + (pixels >> 4)));
    }
    break;
/*
          * Transparent draw mode *
*/
  case LCD_DRAWMODE_TRANS:
    /* Draw incomplete bytes to the left of center area */
    if (Diff) {
      if (pixels & 0xF0) {
        (*pDev->pAPIList->pfSetPixelIndex)(x, y, *(pTrans + (pixels >> 4)));
      }
      x++;
      xsize--;
      pixels = *++p;
    }
    /* Draw center area (2 pixels in one byte) */
    while (xsize >= 2) {
      /* Draw 1. (left) pixel */
      if (pixels & 0xF0) {
        (*pDev->pAPIList->pfSetPixelIndex)(x, y, *(pTrans + (pixels >> 4)));
      }
      /* Draw 2. (right) pixel */
      if (pixels &= 15) {
        (*pDev->pAPIList->pfSetPixelIndex)(x + 1, y, *(pTrans + pixels));
      }
      x += 2;
      xsize -= 2;
      pixels = *++p;
    }
    /* Draw incomplete bytes to the right of center area */
    if (xsize) {
      if (pixels >>= 4) {
        (*pDev->pAPIList->pfSetPixelIndex)(x, y, *(pTrans + pixels));
      }
    }
    break;
  }
}

/*********************************************************************
*
*       _DrawBitLine8BPP
*/
static void _DrawBitLine8BPP(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * pSrc, int xsize,
                             const LCD_PIXELINDEX* pTrans, GUI_MEMDEV* pDev, PIXELINDEX* pDest) {
  GUI_USE_PARA(pUsage);
  GUI_USE_PARA(pDest);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    do {
      (*pDev->pAPIList->pfSetPixelIndex)(x++, y, *(pTrans + *pSrc));
      pSrc++;
    } while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      if (*pSrc) {
        (*pDev->pAPIList->pfSetPixelIndex)(x, y, *(pTrans + *pSrc));
      }
      x++;
      pSrc++;
    } while (--xsize);
    break;
  }
}

/*********************************************************************
*
*       _DrawBitLine8BPP_DDB
*/
static void _DrawBitLine8BPP_DDB(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * pSrc, int xsize, GUI_MEMDEV* pDev, PIXELINDEX* pDest) {
  GUI_USE_PARA(pUsage);
  GUI_USE_PARA(pDest);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    do {
      (*pDev->pAPIList->pfSetPixelIndex)(x++, y, *pSrc);
      pSrc++;
    } while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      if (*pSrc) {
        (*pDev->pAPIList->pfSetPixelIndex)(x, y, *pSrc);
      }
      x++;
      pSrc++;
    } while (--xsize);
    break;
  }
}

/*********************************************************************
*
*       _DrawBitmap
*/
static void _DrawBitmap(int x0, int y0, int xsize, int ysize,
                        int BitsPerPixel, int BytesPerLine,
                        const U8 GUI_UNI_PTR * pData, int Diff, const LCD_PIXELINDEX* pTrans)
{
  int i;
  GUI_MEMDEV* pDev   = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  GUI_USAGE*  pUsage = (pDev->hUsage) ? GUI_USAGE_H2P(pDev->hUsage) : 0;
  unsigned    BytesPerLineDest;
  PIXELINDEX* pDest;
  BytesPerLineDest = pDev->BytesPerLine;
  x0 += Diff;
  /* Mark all affected pixels dirty unless transparency is set */
  if (pUsage) {
    if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0) {
      GUI_USAGE_AddRect(pUsage, x0, y0 , xsize, ysize);
    }
  }
  pDest = _XY2PTR_BITOFFSET(x0, y0, 0);
#if BITSPERPIXEL == 16
  /* handle 16 bpp bitmaps in high color modes, but only without palette */
  if (BitsPerPixel == 16) {
    for (i = 0; i < ysize; i++) {
      _DrawBitLine16BPP_DDB(pUsage, x0, i + y0, (const U16*)pData, xsize, pDev, pDest);
      pData += BytesPerLine;
      pDest = (PIXELINDEX*)((U8*)pDest + BytesPerLineDest); 
    }
    return;
  }
#endif
  /* Handle 8 bpp bitmaps seperately as we have different routine bitmaps with or without palette */
  if (BitsPerPixel == 8) {
    for (i = 0; i < ysize; i++) {
      if (pTrans) {
        _DrawBitLine8BPP(pUsage, x0, i + y0, pData, xsize, pTrans, pDev, pDest);
      } else {
        _DrawBitLine8BPP_DDB(pUsage, x0, i + y0, pData, xsize, pDev, pDest);
      }
      pData += BytesPerLine;
      pDest = (PIXELINDEX*)((U8*)pDest + BytesPerLineDest); 
    }
    return;
  }
  /* Use aID for bitmaps without palette */
  if (!pTrans) {
    pTrans = aID;
  }
  for (i = 0; i < ysize; i++) {
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(pUsage, x0, i + y0, pData, Diff, xsize, pTrans, pDev, pDest);
      break;
    case 2:
      _DrawBitLine2BPP(pUsage, x0, i + y0, pData, Diff, xsize, pTrans, pDev, pDest);
      break;
    case 4:
      _DrawBitLine4BPP(pUsage, x0, i + y0, pData, Diff, xsize, pTrans, pDev, pDest);
      break;
    }
    pData += BytesPerLine;
    pDest = (PIXELINDEX*)((U8*)pDest + BytesPerLineDest); 
  }
}

/*********************************************************************
*
*       _FillRect
*/
static void _FillRect(int x0, int y0, int x1, int y1) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  U8* pData;
  int Bit, Len;
  int RemPixels;
  Len = x1 - x0 + 1;
  /* Mark rectangle as modified */
  if (pDev->hUsage) {
    GUI_USAGE_AddRect(GUI_USAGE_H2P(pDev->hUsage), x0, y0, Len, y1 - y0 + 1);
  }
  /* Do the drawing */
  for (; y0 <= y1; y0++) {
    pData = _XY2PTR_BITOFFSET(x0, y0, &Bit);
    RemPixels = Len;
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      if (Bit < 7) {
        while ((Bit >= 0) && RemPixels--) {
          *pData ^= 1 << (Bit--);
        }
        pData++;
      }
      if (RemPixels > 0) {
        int NumBytes = RemPixels >> 3;
        if (NumBytes > 0) {
          RemPixels -= NumBytes << 3;
          do {
            *pData ^= *pData;
            pData++;
          } while (--NumBytes);
        }
        Bit = 7;
        while (RemPixels--) {
          *pData ^= 1 << (Bit--);
        }
      }
    } else {  /* Fill */
      int Color, FillByte;
      Color    = (LCD_COLORINDEX & 1);
      FillByte = (-Color) & 0xFF;
      if (Bit < 7) {
        while ((Bit >= 0) && RemPixels--) {
          *pData &= ~(1 << Bit);
          *pData |= Color << (Bit--);
        }
        pData++;
      }
      if (RemPixels > 0) {
        int NumBytes = RemPixels >> 3;
        if (NumBytes > 0) {
          GUI_MEMSET(pData, FillByte, NumBytes);
          pData += NumBytes;
          RemPixels -= NumBytes << 3;
        }
        Bit = 7;
        while (RemPixels--) {
          *pData &= ~(1 << Bit);
          *pData |= Color << (Bit--);
        }
      }
    }
  }
}

/*********************************************************************
*
*       _DrawHLine
*/
static void _DrawHLine(int x0, int y, int x1) {
  _FillRect(x0, y, x1, y);
}

/*********************************************************************
*
*       _DrawVLine
*/
static void _DrawVLine(int x , int y0, int y1) {
  GUI_MEMDEV* pDev   = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  GUI_USAGE_h hUsage = pDev->hUsage; 
  GUI_USAGE*  pUsage = hUsage ? GUI_USAGE_H2P(hUsage) : NULL;
  U8* pData;
  int Bit, Mask;
  pData = _XY2PTR_BITOFFSET(x, y0, &Bit);
  Mask  = (1 << Bit);
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    do {
      *pData ^= Mask;
      if (pUsage) {
        GUI_USAGE_AddPixel(pUsage, x, y0);
      }
      pData += pDev->BytesPerLine;
    } while (++y0 <= y1);
  } else {
    int Pixel;
    Pixel = (LCD_COLORINDEX & 1) << Bit;
    do {
      *pData &= ~Mask;
      *pData |= Pixel;
      if (pUsage) {
        GUI_USAGE_AddPixel(pUsage, x, y0);
      }
      pData += pDev->BytesPerLine;
    } while (++y0 <= y1);
  }
}

/*********************************************************************
*
*       _SetPixelIndex
*/
static void _SetPixelIndex(int x, int y, int Index) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  U8* pData;
  int Bit;
  pData   = _XY2PTR_BITOFFSET(x, y, &Bit);
  *pData &= ~(1 << Bit);
  *pData |= (Index & 1) << Bit;
  if (pDev->hUsage) {
    GUI_USAGE_AddPixel(GUI_USAGE_H2P(pDev->hUsage), x, y);
  }
}

/*********************************************************************
*
*       _XorPixel
*/
static void _XorPixel(int x, int y) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  U8* pData;
  int Bit;
  pData   = _XY2PTR_BITOFFSET(x, y, &Bit);
  *pData ^= (1 << Bit);
  if (pDev->hUsage) {
    GUI_USAGE_AddPixel(GUI_USAGE_H2P(pDev->hUsage), x, y);
  }
}

/*********************************************************************
*
*       _GetPixelIndex
*/
static unsigned int _GetPixelIndex(int x, int y) {
  U8* pData;
  int Bit;
  pData = _XY2PTR_BITOFFSET(x, y, &Bit);
  return (*pData >> Bit) & 1;
}

/*********************************************************************
*
*       Device structure
*
**********************************************************************
*/

const tLCDDEV_APIList API_LIST = {
  GUI_MEMDEV__Color2Index,
  GUI_MEMDEV__Index2Color,
  GUI_MEMDEV__GetIndexMask,
  (tLCDDEV_DrawBitmap*)_DrawBitmap,
  _DrawHLine,
  _DrawVLine,
  _FillRect,
  _GetPixelIndex,
  GUI_MEMDEV__GetRect,
  _SetPixelIndex,
  _XorPixel,
  NULL,               /* pfSetLUTEntry   */
  NULL,               /* pfFillPolygon   */
  NULL,               /* pfFillPolygonAA */
  NULL,               /* MemDevAPI       */
  BITSPERPIXEL        /* BitsPerPixel    */
};

#else

void GUIDEV1_C(void) {}

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
