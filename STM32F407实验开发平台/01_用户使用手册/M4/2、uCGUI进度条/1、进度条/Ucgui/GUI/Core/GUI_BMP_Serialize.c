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
File        : GUI_BMP_Serialize.c
Purpose     : Implementation of GUI_BMP_Serialize
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define DIB_HEADER_MARKER ((U16) ('M' << 8) | 'B') /* DIB Header Marker - used in writing DIBs to files */

#define SIZEOF_BITMAPFILEHEADER 14
#define SIZEOF_BITMAPINFOHEADER 40

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SendU16
*/
static void _SendU16(GUI_CALLBACK_VOID_U8_P * pfSerialize, U16 Data, void * p) {
  (*pfSerialize)((U8)Data, p);
  (*pfSerialize)(Data >> 8, p);
}

/*********************************************************************
*
*       _SendU32
*/
static void _SendU32(GUI_CALLBACK_VOID_U8_P * pfSerialize, U32 Data, void * p) {
  _SendU16(pfSerialize, (U16)Data, p);
  _SendU16(pfSerialize, Data >> 16, p);
}

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_BMP_SerializeEx
*/
void GUI_BMP_SerializeEx(GUI_CALLBACK_VOID_U8_P * pfSerialize, int x0, int y0, int xSize, int ySize, void * p) {
  int x, y, i;
  U32 BitmapOffset, FileSize;
  int BPP          = LCD_GetBitsPerPixel();
  int BytesPerLine = ((BPP > 8) ? (2 * xSize + 2) : (xSize + 3)) & ~3;
  int NumColors    = (BPP > 8) ? 0 : (1 << BPP);
  /* Write BITMAPFILEHEADER */
  BitmapOffset   = SIZEOF_BITMAPFILEHEADER
                 + SIZEOF_BITMAPINFOHEADER
                 + NumColors * 4;
  FileSize       = BitmapOffset
                 + ySize * BytesPerLine;
  _SendU16(pfSerialize, DIB_HEADER_MARKER, p);       /* bfType */
  _SendU32(pfSerialize, FileSize, p);                /* bfSize */
  _SendU32(pfSerialize, 0, p);                       /* bfReserved1, bfReserved2 */
  _SendU32(pfSerialize, BitmapOffset, p);            /* bfOffBits */
  /* Write BITMAPINFOHEADER */
  _SendU32(pfSerialize, SIZEOF_BITMAPINFOHEADER, p); /* biSize */
  _SendU32(pfSerialize, xSize, p);                   /* biWidth */
  _SendU32(pfSerialize, ySize, p);                   /* biHeighth */
  _SendU16(pfSerialize, 1, p);                       /* biPlanes */
  _SendU16(pfSerialize, (BPP  <= 8) ? 8 : 16, p);    /* biBitCount */
  _SendU32(pfSerialize, 0, p);                       /* biCompression */
  _SendU32(pfSerialize, 0, p);                       /* biSizeImage */
  _SendU32(pfSerialize, 0, p);                       /* biXPelsPerMeter */
  _SendU32(pfSerialize, 0, p);                       /* biYPelsPerMeter */
  _SendU32(pfSerialize, NumColors, p);               /* biClrUsed */
  _SendU32(pfSerialize, 0, p);                       /* biClrImportant */
  /* Write palette */
  for (i = 0; i < NumColors; i++) {
    U32 Color;
    Color = GUI_Index2Color(i);
    Color = ((Color >> 16) & 255) | (Color & 0xff00) | ((Color & 0xff) << 16);
    _SendU32(pfSerialize, Color, p);
  }
  /* Write pixels */
  for (y = ySize - 1; y >= 0; y--) {
    for (x = 0; x < xSize; x++) {
      if (BPP <= 8) {
        pfSerialize(LCD_GetPixelIndex(x0 + x, y0 + y), p);
      } else {
        U16 Color16;
        U32 Color = LCD_GetPixelColor(x0 + x, y0 + y);
        int b = ((Color >> 16) * 31 + 127) / 255;
        int g = (((Color >> 8) & 255) * 31 + 127) / 255;
        int r = ((Color & 255) * 31 + 127) / 255;
        Color16 = (r << 10) | (g << 5) | b;       /* 16 bpp Bitmaps in windows are 555: rrrrrgggggbbbbb */
        _SendU16(pfSerialize, Color16, p);
      }
    }
    /* Align pointer to next U32 */
    for (i = BytesPerLine & 3; i > 0; i--) {
      pfSerialize(0, p);
    }
  }
}

/*********************************************************************
*
*       GUI_BMP_Serialize
*/
void GUI_BMP_Serialize(GUI_CALLBACK_VOID_U8_P * pfSerialize, void * p) {
  GUI_BMP_SerializeEx(pfSerialize, 0, 0, LCD_GetXSize(), LCD_GetYSize(), p);
}

/*************************** End of file ****************************/
