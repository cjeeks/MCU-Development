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
File        : GUIDEV_8.c
Purpose     : Implementation of memory devices
              This file handles 8 bit memory devices, but also 16 bit
              memory devices when included by GUIDEV_16.c
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
  #define BITSPERPIXEL                     8
  #define API_LIST      GUI_MEMDEV__APIList8
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
*       _XY2PTR
*/
static PIXELINDEX* _XY2PTR(int x, int y) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  U8 *pData = (U8*)(pDev + 1);
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    if ((x >= pDev->x0+pDev->XSize) | (x<pDev->x0) | (y >= pDev->y0+pDev->YSize) | (y<pDev->y0)) {
      GUI_DEBUG_ERROROUT2("_XY2PTR: parameters out of bounds",x,y);
    }
  #endif
  pData += (GUI_ALLOC_DATATYPE_U)(y - pDev->y0) * (GUI_ALLOC_DATATYPE_U)pDev->BytesPerLine;
  return ((PIXELINDEX*)pData) + x - pDev->x0;
}

/*********************************************************************
*
*       _DrawBitLine1BPP
*/
static void _DrawBitLine1BPP(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * p, int Diff, unsigned int xsize,
                             const LCD_PIXELINDEX* pTrans, GUI_MEMDEV* pDev, PIXELINDEX* pDest)
{
  PIXELINDEX Index1;
  PIXELINDEX IndexMask;
  unsigned pixels;
  unsigned PixelCnt;
  PixelCnt = 8 - Diff;
  pixels = LCD_aMirror[*p] >> Diff;

  GUI_DEBUG_ERROROUT3_IF( x < pDev->x0, "GUIDEV.c: DrawBitLine1BPP, Act= %d, Border= %d, Clip= %d", x,pDev->x0, GUI_Context.ClipRect.x0);

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
        *pDest++ = *(pTrans + (pixels & 1));
        pixels >>= 1;
      } while (--PixelCnt);
      /* Check if an other Source byte needs to be loaded */
      if (xsize == 0) {
        return;
      }
      PixelCnt = 8;
      pixels = LCD_aMirror[*++p];
    } while (1);
  case LCD_DRAWMODE_TRANS:
    Index1 = *(pTrans + 1);
    do {
      /* Prepare loop */
      if (PixelCnt > xsize) {
        PixelCnt = xsize;
      }
      xsize -= PixelCnt;
      if (pUsage) {
        do {
          if (pixels == 0) {      /* Early out optimization; not required */
            pDest += PixelCnt;
            x     += PixelCnt;
            break;
          }
          if ((pixels & 1)) {
            GUI_USAGE_AddPixel(pUsage, x, y);
            *pDest = Index1;
          }
          x++;
          pDest++;
          if (--PixelCnt == 0) {
            break;
          }
          pixels >>= 1;
        } while (1);
      } else {
        do {
          if (pixels == 0) {      /* Early out optimization; not required */
            pDest += PixelCnt;
            break;
          }
          if ((pixels & 1)) {
            *pDest = Index1;
          }
          pDest++;
          if (--PixelCnt == 0) {
            break;
          }
          pixels >>= 1;
        } while (1);
      }
      /* Check if an other Source byte needs to be loaded */
      if (xsize == 0) {
        return;
      }
      PixelCnt = 8;
      pixels = LCD_aMirror[*(++p)];
    } while (1);
  case LCD_DRAWMODE_XOR:
    IndexMask = pDev->pfGetIndexMask();
    do {
      /* Prepare loop */
      if (PixelCnt > xsize) {
        PixelCnt = xsize;
      }
      xsize -= PixelCnt;
      /* Write as many pixels as we are allowed to and have loaded in this inner loop */
      do {
        if ((pixels & 1)) {
          *pDest ^= IndexMask;
        }
        *pDest++;
        pixels >>= 1;
      } while (--PixelCnt);
      /* Check if an other Source byte needs to be loaded */
      if (xsize == 0) {
        return;
      }
      PixelCnt = 8;
      pixels = LCD_aMirror[*(++p)];
    } while (1);
  }
}

/*********************************************************************
*
*       _DrawBitLine2BPP
*/
static void _DrawBitLine2BPP(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * p, int Diff, int xsize,
                             const LCD_PIXELINDEX* pTrans, PIXELINDEX* pDest)
{
  U8 pixels;
  U8  PixelCnt;
  PixelCnt = 4 - Diff;
  pixels = (*p) << (Diff << 1);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
  PixelLoopWrite:
    if (PixelCnt > xsize) {
      PixelCnt = xsize;
    }
    xsize -= PixelCnt;
    do {
      *pDest++ = *(pTrans + (pixels >> 6));
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
        *pDest = *(pTrans + (pixels >> 6));
        if (pUsage) {
          GUI_USAGE_AddPixel(pUsage, x, y);
        }
      }
      pDest++;
      x++;
      pixels <<= 2;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt = 4;
      pixels = *(++p);
      goto PixelLoopTrans;
    }
    break;
  case LCD_DRAWMODE_XOR:;
  PixelLoopXor:
    if (PixelCnt > xsize)
      PixelCnt = xsize;
    xsize -= PixelCnt;
    do {
      if ((pixels & 0xc0))
        *pDest ^= 255;
      pDest++;
      pixels <<= 2;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt = 4;
      pixels = *(++p);
      goto PixelLoopXor;
    }
    break;
  }
}

/*********************************************************************
*
*       _DrawBitLine4BPP
*/
static void _DrawBitLine4BPP(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * p, int Diff, int xsize,
                             const LCD_PIXELINDEX* pTrans, PIXELINDEX* pDest)
{
  U8 pixels;
  U8 PixelCnt;
  PixelCnt = 2 - Diff;
  pixels = (*p) << (Diff << 2);
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
/*
          * Write mode *
*/
  case 0:
    /* Draw incomplete bytes to the left of center area */
    if (Diff) {
      *pDest = *(pTrans + (pixels >> 4));
      pDest++;
      xsize--;
      pixels = *++p;
    }
    /* Draw center area (2 pixels in one byte) */
    if (xsize >= 2) {
      int i = xsize >> 1;
      xsize &= 1;
      do {
        *pDest     = *(pTrans + (pixels >> 4));   /* Draw 1. (left) pixel */
        *(pDest+1) = *(pTrans + (pixels & 15));   /* Draw 2. (right) pixel */
        pDest += 2;
        pixels = *++p;
      } while (--i);
    }
    /* Draw incomplete bytes to the right of center area */
    if (xsize) {
      *pDest = * (pTrans + (pixels >> 4));
    }
    break;
/*
          * Transparent draw mode *
*/
  case LCD_DRAWMODE_TRANS:
    /* Draw incomplete bytes to the left of center area */
    if (Diff) {
      if (pixels & 0xF0) {
        *pDest = *(pTrans + (pixels >> 4));
        if (pUsage) {
          GUI_USAGE_AddPixel(pUsage, x, y);
        }
      }
      pDest++;
      x++;
      xsize--;
      pixels = *++p;
    }
    /* Draw center area (2 pixels in one byte) */
    while (xsize >= 2) {
      /* Draw 1. (left) pixel */
      if (pixels & 0xF0) {
        *pDest = *(pTrans + (pixels >> 4));
        if (pUsage) {
          GUI_USAGE_AddPixel(pUsage, x, y);
        }
      }
      /* Draw 2. (right) pixel */
      if (pixels &= 15) {
        *(pDest + 1) = *(pTrans + pixels);
        if (pUsage) {
          GUI_USAGE_AddPixel(pUsage, x + 1, y);
        }
      }
      pDest += 2;
      x += 2;
      xsize -= 2;
      pixels = *++p;
    }
    /* Draw incomplete bytes to the right of center area */
    if (xsize) {
      if (pixels >>= 4) {
        *pDest = *(pTrans + pixels);
        if (pUsage) {
          GUI_USAGE_AddPixel(pUsage, x, y);
        }
      }
    }
    break;
  case LCD_DRAWMODE_XOR:;
  PixelLoopXor:
    if (PixelCnt > xsize)
      PixelCnt = xsize;
    xsize -= PixelCnt;
    do {
      if ((pixels & 0xc0)) {
        *pDest ^= 255;
      }
      pDest++;
      pixels <<= 4;
    } while (--PixelCnt);
    if (xsize) {
      PixelCnt = 2;
      pixels = *(++p);
      goto PixelLoopXor;
    }
    break;
  }
}

/*********************************************************************
*
*       _DrawBitLine8BPP
*/
static void _DrawBitLine8BPP(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * pSrc, int xsize,
                             const LCD_PIXELINDEX* pTrans, PIXELINDEX* pDest) {
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    do {
      *pDest = *(pTrans + *pSrc);
      pDest++;
      pSrc++;
    } while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
      if (*pSrc) {
        *pDest = *(pTrans + *pSrc);
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

#if GUI_UNI_PTR_USED
/*********************************************************************
*
*       _Memcopy
*/
static void _Memcopy(PIXELINDEX * pDest, const U8 GUI_UNI_PTR * pSrc, int NumBytes) {
  while(NumBytes--) {
    *pDest++ = *pSrc++;
  }
}
#endif

/*********************************************************************
*
*       _DrawBitLine8BPP_DDB
*/
static void _DrawBitLine8BPP_DDB(GUI_USAGE* pUsage, int x, int y, const U8 GUI_UNI_PTR * pSrc, int xsize, PIXELINDEX* pDest) {
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:    /* Write mode */
    #if GUI_UNI_PTR_USED
      _Memcopy(pDest, pSrc, xsize);
    #else
      memcpy(pDest, pSrc, xsize);
    #endif
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
  pDest = _XY2PTR(x0, y0);
#if BITSPERPIXEL == 16
  /* handle 16 bpp bitmaps in high color modes, but only without palette */
  if (BitsPerPixel == 16) {
    for (i = 0; i < ysize; i++) {
      _DrawBitLine16BPP_DDB(pUsage, x0, i + y0, (const U16*)pData, xsize, pDest);
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
        _DrawBitLine8BPP(pUsage, x0, i + y0, pData, xsize, pTrans, pDest);
      } else {
        _DrawBitLine8BPP_DDB(pUsage, x0, i + y0, pData, xsize, pDest);
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
      _DrawBitLine2BPP(pUsage, x0, i + y0, pData, Diff, xsize, pTrans, pDest);
      break;
    case 4:
      _DrawBitLine4BPP(pUsage, x0, i + y0, pData, Diff, xsize, pTrans, pDest);
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
  unsigned BytesPerLine;
  int Len;
  GUI_MEMDEV* pDev   = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  PIXELINDEX* pData  = _XY2PTR(x0, y0);
  BytesPerLine = pDev->BytesPerLine;
  Len = x1 - x0 + 1;
  /* Mark rectangle as modified */
  if (pDev->hUsage) {
    GUI_USAGE_AddRect(GUI_USAGE_H2P(pDev->hUsage), x0, y0, Len, y1 - y0 + 1);
  }
  /* Do the drawing */
  for (; y0 <= y1; y0++) {
    if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
      int RemPixels;
      PIXELINDEX* pDest;
      PIXELINDEX IndexMask;
      RemPixels = Len;
      pDest  = pData;
      IndexMask = pDev->pfGetIndexMask();
      do {
        *pDest = *pDest ^ IndexMask;
        pDest++;
      } while (--RemPixels);
    } else {  /* Fill */
      #if BITSPERPIXEL == 8
        GUI_MEMSET(pData, LCD_COLORINDEX, Len);
      #elif BITSPERPIXEL == 16
        GUI__memset16(pData, LCD_COLORINDEX, Len);
      #else
        #error Unsupported
      #endif
    }
    pData = (PIXELINDEX*)((U8*)pData + BytesPerLine); 
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
  PIXELINDEX* pData  = _XY2PTR(x, y0);
  unsigned BytesPerLine = pDev->BytesPerLine;

  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    PIXELINDEX IndexMask;
    IndexMask = pDev->pfGetIndexMask();
    do {
      if (hUsage) {
        GUI_USAGE_AddPixel(pUsage, x, y0);
      }
      *pData = *pData ^ IndexMask;
      pData = (PIXELINDEX*)((U8*)pData + pDev->BytesPerLine); /* Same as "pData += pDev->BytesPerLine >> 1;", Just more efficient */
    } while (++y0 <= y1);
  } else {
    if (hUsage) {
      do {
        GUI_USAGE_AddPixel(pUsage, x, y0);
        *pData = LCD_COLORINDEX;
        pData = (PIXELINDEX*)((U8*)pData + BytesPerLine); /* Same as "pData += pDev->BytesPerLine >> 1;", Just more efficient */
      } while (++y0 <= y1);
    } else {
      unsigned NumPixels;
      NumPixels = y1 - y0 + 1;
      do {
        *pData = LCD_COLORINDEX;
        pData = (PIXELINDEX*)((U8*)pData + BytesPerLine); /* Same as "pData += pDev->BytesPerLine >> 1;", Just more efficient */
      } while (--NumPixels);
    }
  }
}

/*********************************************************************
*
*       _SetPixelIndex
*/
static void _SetPixelIndex(int x, int y, int Index) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  GUI_USAGE_h hUsage = pDev->hUsage; 
  PIXELINDEX* pData = _XY2PTR(x, y);
  *pData = Index;
  if (hUsage) {
    GUI_USAGE_AddPixel(GUI_USAGE_H2P(hUsage), x, y);
  }
}

/*********************************************************************
*
*       _XorPixel
*/
static void _XorPixel(int x, int y) {
  PIXELINDEX IndexMask;
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  GUI_USAGE_h hUsage = pDev->hUsage; 
  PIXELINDEX* pData = _XY2PTR(x, y);
  IndexMask = pDev->pfGetIndexMask();
  *pData = *pData ^ IndexMask;
  if (hUsage) {
    GUI_USAGE_AddPixel(GUI_USAGE_H2P(hUsage), x, y);
  }
}

/*********************************************************************
*
*       _GetPixelIndex
*/
static unsigned int _GetPixelIndex(int x, int y) {
  PIXELINDEX* pData = _XY2PTR(x, y);
  return *pData;
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

void GUIDEV8_C(void) {}

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
