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
File        : LCDL0Delta.c
Purpose     : Link between GUI and LCD_L0... if delta display needs to
              be supported
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>             /* needed for definition of NULL */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_Private.h"        /* private modul definitions & config */

#if LCD_DELTA_MODE

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static       U8             _aPixelData_0[LCD_XSIZE];
static       U8             _aPixelData_1[LCD_XSIZE];
static const GUI_LOGPALETTE _Pal;
static       GUI_BITMAP     _Bm;
static       int            _y;
static       U8             _aRGB[3];

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetRGB
*/
static void _SetRGB(LCD_PIXELINDEX ColorIndex) {
  _aRGB[0] = ColorIndex & 0x00f;
  _aRGB[1] = (ColorIndex & 0x0f0) >> 4;
  _aRGB[2] = (ColorIndex & 0xf00) >> 8;
}

/*********************************************************************
*
*       _SetPixel
*/
static void _SetPixelIndex(int x, LCD_PIXELINDEX ColorIndex) {
  _SetRGB(ColorIndex);
  _aPixelData_0[x] = _aRGB[(x + (_y & 1)) % 3];
}

/*********************************************************************
*
*       _InitBM
*/
static void _InitBM(int xsize, int x0) {
  _Bm.XSize        = xsize;
  _Bm.YSize        = 1;
  _Bm.BytesPerLine = xsize;
  _Bm.BitsPerPixel = 8;
  _Bm.pfDraw       = 0;
  _Bm.pData        = &_aPixelData_0[x0];
  _Bm.pPal         = &_Pal;
  _Bm.pfDraw       = 0;
}

/*********************************************************************
*
*       _DrawBitLine1BPP
*/
static void _DrawBitLine1BPP(int x, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  int xx;
  LCD_PIXELINDEX Index0 = *(pTrans+0);
  LCD_PIXELINDEX Index1 = *(pTrans+1);
  x += Diff;
  xx = x;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    do {
      _SetPixelIndex(xx++, (*p & (0x80 >> Diff)) ? Index1 : Index0);
			if (++Diff == 8) {
        Diff = 0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    do {
  		if (*p & (0x80 >> Diff)) {
        _SetPixelIndex(xx, Index1);
      } else {
        _SetPixelIndex(xx, LCD_L0_GetPixelIndex(xx, _y));
      }
      xx++;
			if (++Diff == 8) {
        Diff = 0;
				p++;
			}
		} while (--xsize);
    break;
  case LCD_DRAWMODE_XOR:;
    do {
  		if (*p & (0x80 >> Diff)) {
        int Pixel = LCD_L0_GetPixelIndex(xx, _y);
        _SetPixelIndex(xx, LCD_NUM_COLORS - 1 - Pixel);
      }
      xx++;
			if (++Diff == 8) {
        Diff = 0;
				p++;
			}
		} while (--xsize);
    break;
	}
  LCD_L0_DrawBitmap(x, _y, _Bm.XSize, 1, _Bm.BitsPerPixel, _Bm.BytesPerLine, _Bm.pData, 0, 0);
}

/*********************************************************************
*
*       _DrawBitLine2BPP
*/
static void _DrawBitLine2BPP(int x, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  int xx;
  LCD_PIXELINDEX Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  xx = x;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    if (pTrans) {
      do {
        int Shift = (3 - CurrentPixel) << 1;
        int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
        _SetPixelIndex(xx++, PixelIndex);
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    } else {
      do {
        int Shift = (3 - CurrentPixel) << 1;
        int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        _SetPixelIndex(xx++, Index);
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    }
    break;
  case LCD_DRAWMODE_TRANS:
    if (pTrans) {
      do {
        int Shift = (3 - CurrentPixel) << 1;
        int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        if (Index) {
          LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
          _SetPixelIndex(xx, PixelIndex);
        } else {
          _SetPixelIndex(xx, LCD_L0_GetPixelIndex(xx, _y));
        }
        xx++;
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    } else {
      do {
        int Shift = (3 - CurrentPixel) << 1;
        int Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        if (Index) {
          _SetPixelIndex(xx, Index);
        } else {
          _SetPixelIndex(xx, LCD_L0_GetPixelIndex(xx, _y));
        }
        xx++;
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    }
    break;
  }
  LCD_L0_DrawBitmap(x, _y, _Bm.XSize, 1, _Bm.BitsPerPixel, _Bm.BytesPerLine, _Bm.pData, 0, 0);
}

/*********************************************************************
*
*       _DrawBitLine4BPP
*/
static void _DrawBitLine4BPP(int x, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  int xx;
  U8 Pixels = *p;
  int CurrentPixel = Diff;
  x += Diff;
  xx = x;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    if (pTrans) {
      do {
        int Shift = (1 - CurrentPixel) << 2;
        int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        LCD_PIXELINDEX PixelIndex = *(pTrans + Index);
        _SetPixelIndex(xx++, PixelIndex);
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    } else {
      do {
        int Shift = (1 - CurrentPixel) << 2;
        int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        _SetPixelIndex(xx++, Index);
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    }
    break;
  case LCD_DRAWMODE_TRANS:
    if (pTrans) {
      do {
        int Shift = (1 - CurrentPixel) << 2;
        int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        if (Index) {
          U8 PixelIndex = *(pTrans + Index);
          _SetPixelIndex(xx, PixelIndex);
        } else {
          _SetPixelIndex(xx, LCD_L0_GetPixelIndex(xx, _y));
        }
        xx++;
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    } else {
      do {
        int Shift = (1 - CurrentPixel) << 2;
        int Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        if (Index) {
          _SetPixelIndex(xx, Index);
        } else {
          _SetPixelIndex(xx, LCD_L0_GetPixelIndex(xx, _y));
        }
        xx++;
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
		  } while (--xsize);
    }
    break;
  }
  LCD_L0_DrawBitmap(x, _y, _Bm.XSize, 1, _Bm.BitsPerPixel, _Bm.BytesPerLine, _Bm.pData, 0, 0);
}

/*********************************************************************
*
*       _DrawBitLine8BPP
*/
static void _DrawBitLine8BPP(int x, U8 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  int xx = x;
  LCD_PIXELINDEX Pixel;
  switch (GUI_Context.DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
    if (pTrans) {
      for (; xsize > 0; xsize--, xx++, p++) {
        Pixel = *p;
        _SetPixelIndex(xx, *(pTrans + Pixel));
      }
    } else {
      for (; xsize > 0; xsize--, xx++, p++) {
        _SetPixelIndex(xx, *p);
      }
    }
    break;
  case LCD_DRAWMODE_TRANS:
    if (pTrans) {
      for (; xsize > 0; xsize--, xx++, p++) {
        Pixel = *p;
        if (Pixel) {
          _SetPixelIndex(xx, *(pTrans + Pixel));
        } else {
          _SetPixelIndex(xx, LCD_L0_GetPixelIndex(xx, _y));
        }
      }
    } else {
      for (; xsize > 0; xsize--, xx++, p++) {
        Pixel = *p;
        if (Pixel) {
          _SetPixelIndex(xx, Pixel);
        } else {
          _SetPixelIndex(xx, LCD_L0_GetPixelIndex(xx, _y));
        }
      }
    }
    break;
  }
  LCD_L0_DrawBitmap(x, _y, _Bm.XSize, 1, _Bm.BitsPerPixel, _Bm.BytesPerLine, _Bm.pData, 0, 0);
}

/*********************************************************************
*
*       _DrawBitLine16BPP
*/
static void _DrawBitLine16BPP(int x, U16 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  int xx = x;
  LCD_PIXELINDEX pixel;
  if ((GUI_Context.DrawMode & LCD_DRAWMODE_TRANS) == 0) {
    if (pTrans) {
      for (; xsize > 0; xsize--, xx++, p++) {
        pixel = *p;
        _SetPixelIndex(xx, *(pTrans + pixel));
      }
    } else {
      for (;xsize > 0; xsize--, xx++, p++) {
        _SetPixelIndex(xx, *p);
      }
    }
  } else {
    if (pTrans) {
      for (; xsize > 0; xsize--, xx++, p++) {
        pixel = *p;
        if (pixel) {
          _SetPixelIndex(xx, *(pTrans + pixel));
        } else {
          _SetPixelIndex(xx, LCD_L0_GetPixelIndex(xx, _y));
        }
      }
    } else {
      for (; xsize > 0; xsize--, xx++, p++) {
        pixel = *p;
        if (pixel) {
          _SetPixelIndex(xx, pixel);
        } else {
          _SetPixelIndex(xx, LCD_L0_GetPixelIndex(xx, _y));
        }
      }
    }
  }
  LCD_L0_DrawBitmap(x, _y, _Bm.XSize, 1, _Bm.BitsPerPixel, _Bm.BytesPerLine, _Bm.pData, 0, 0);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_L0_DELTA_DrawBitmap
*/
void LCD_L0_DELTA_DrawBitmap(int x0, int y0,
                             int xsize, int ysize,
                             int BitsPerPixel, 
                             int BytesPerLine,
                             const U8 GUI_UNI_PTR * pData, int Diff,
                             const LCD_PIXELINDEX* pTrans)
{
  int i;
  _InitBM(xsize, x0 + Diff);
  for (i = 0; i < ysize; i++) {
    _y = i + y0;
    switch (BitsPerPixel) {
    case 1:
      _DrawBitLine1BPP(x0, pData, Diff, xsize, pTrans);
      break;
    #if (LCD_MAX_LOG_COLORS > 2)
      case 2:
        _DrawBitLine2BPP(x0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 4)
      case 4:
        _DrawBitLine4BPP(x0, pData, Diff, xsize, pTrans);
        break;
    #endif
    #if (LCD_MAX_LOG_COLORS > 16)
      case 8:
        _DrawBitLine8BPP(x0, pData, xsize, pTrans);
        break;
    #endif
    #if (LCD_BITSPERPIXEL > 8)
      case 16:
        _DrawBitLine16BPP(x0, (const U16 *)pData, xsize, pTrans);
        break;
    #endif
    }
    pData += BytesPerLine;
  }
}

/*********************************************************************
*
*       LCD_L0_DELTA_DrawHLine
*/
void LCD_L0_DELTA_DrawHLine(int x0, int y,  int x1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; x0 <= x1; x0++) {
      LCD_L0_XorPixel(x0, y);
    }
  } else {
    LCD_L0_DELTA_FillRect(x0, y, x1, y);
  }
}

/*********************************************************************
*
*       LCD_L0_DELTA_DrawVLine
*/
void LCD_L0_DELTA_DrawVLine(int x , int y0,  int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; y0 <= y1; y0++) {
      LCD_L0_XorPixel(x, y0);
    }
  } else {
    int aIndex[2];
    _SetRGB(LCD_COLORINDEX);
    aIndex[0] = x % 3;
    aIndex[1] = (x + 1) % 3;
    for (; y0 <= y1; y0++) {
      LCD_L0_SetPixelIndex(x, y0, _aRGB[aIndex[y0 & 1]]);
    }
  }
}

/*********************************************************************
*
*       LCD_L0_DELTA_FillRect
*/
void LCD_L0_DELTA_FillRect(int x0, int y0, int x1, int y1) {
  if (GUI_Context.DrawMode & LCD_DRAWMODE_XOR) {
    for (; y0 <= y1; y0++) {
      LCD_L0_DELTA_DrawHLine(x0, y0, x1);
    }
  } else {
    int x, y, aInit_0 = 0, aInit_1 = 0;
    _InitBM(x1 - x0 + 1, x0);/**/
    _SetRGB(LCD_COLORINDEX);
    for (y = y0; y <= y1; y++) {
      int Index = y & 1;
      if (Index) {
        if (!aInit_1) {
          for (x = x0; x <= x1; x++) {
            _aPixelData_1[x] = _aRGB[(x + 1) % 3];
          }
          aInit_1 = 1;
        }
        LCD_L0_DrawBitmap(x0, y, _Bm.XSize, 1, _Bm.BitsPerPixel, _Bm.BytesPerLine, &_aPixelData_1[x0], 0, 0);
      } else {
        if (!aInit_0) {
          for (x = x0; x <= x1; x++) {
            _aPixelData_0[x] = _aRGB[x % 3];
          }
          aInit_0 = 1;
        }
        LCD_L0_DrawBitmap(x0, y, _Bm.XSize, 1, _Bm.BitsPerPixel, _Bm.BytesPerLine, _Bm.pData, 0, 0);
     }
    }
  }
}

/*********************************************************************
*
*       LCD_L0_DELTA_GetPixelIndex
*/
unsigned int LCD_L0_DELTA_GetPixelIndex(int x, int y) {
  return LCD_L0_GetPixelIndex(x, y);
}

/*********************************************************************
*
*       LCD_L0_DELTA_SetPixelIndex
*/
void LCD_L0_DELTA_SetPixelIndex(int x, int y, int ColorIndex) {
  LCD_L0_SetPixelIndex(x, y, ColorIndex);
}

/*********************************************************************
*
*       LCD_L0_DELTA_XorPixel
*/
void LCD_L0_DELTA_XorPixel(int x, int y) {
  LCD_L0_XorPixel(x, y);
}

#else

void LCDL0Delta_c(void);
void LCDL0Delta_c(void) { } /* avoid empty object files */

#endif

/*************************** End of file ****************************/
