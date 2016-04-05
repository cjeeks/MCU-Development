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
File        : HEADER_StreamedBitmap.c
Purpose     : HEADER streamed bitmap support
---------------------------END-OF-HEADER------------------------------
*/

#include "HEADER.h"
#include "HEADER_Private.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/
/*********************************************************************
*
*       HEADER_SetStreamedBitmapEx
*/
void HEADER_SetStreamedBitmapEx(HEADER_Handle hObj, unsigned int Index, const GUI_BITMAP_STREAM * pBitmap, int x, int y) {
  HEADER__SetDrawObj(hObj, Index, GUI_DRAW_STREAMED_Create(pBitmap, x, y));
  WM_InvalidateWindow(hObj);
}

/*********************************************************************
*
*       HEADER_SetStreamedBitmap
*/
void HEADER_SetStreamedBitmap(HEADER_Handle hObj, unsigned int Index, const GUI_BITMAP_STREAM * pBitmap) {
  HEADER_SetStreamedBitmapEx(hObj, Index, pBitmap, 0, 0);
}

#else                            /* Avoid problems with empty object modules */
  void HEADER_StreamedBitmap_C(void) {}
#endif
