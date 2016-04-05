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
File        : GUI_GetBitmapPixelIndex.c
Purpose     : Implementation of GUI_GetBitmapPixelIndex
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GetBitmapPixelIndex
*/
int GUI_GetBitmapPixelIndex(const GUI_BITMAP GUI_UNI_PTR * pBMP, unsigned x, unsigned y) {
  unsigned Off, Value;
  switch (pBMP->BitsPerPixel) {
  case 1:
    Off = (x >> 3) + (y * pBMP->BytesPerLine);
    Value = *(pBMP->pData + Off);
    Value = Value >> (7 - (x & 0x7)) & 0x1;
    break;
  case 2:
    Off = (x >> 2) + (y * pBMP->BytesPerLine);
    Value = *(pBMP->pData + Off);
    Value = Value >> (6 - ((x << 1) & 0x6)) & 0x3;
    break;
  case 4:
    Off = (x >> 1) + (y * pBMP->BytesPerLine);
    Value = *(pBMP->pData + Off);
    Value = (x & 1) ? (Value & 0xF) : (Value >> 4);
    break;
  case 8:
    Off = x + y * pBMP->BytesPerLine;
    Value = *(pBMP->pData + Off);
    break;
  case 16:
    Off = (x << 1) + y * pBMP->BytesPerLine;
    Value = *(pBMP->pData + Off) | (*(pBMP->pData + Off + 1) << 8);
    break;
  default:
    Value = 0;
  }
  return Value;
}

/*************************** End of file ****************************/
