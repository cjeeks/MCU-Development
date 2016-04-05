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
File        : HEADER_Bitmap.c
Purpose     : HEADER bitmap support
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
*       HEADER_SetBitmapEx
*/
void HEADER_SetBitmapEx(HEADER_Handle hObj, unsigned Index, const GUI_BITMAP * pBitmap, int x, int y) {
  HEADER__SetDrawObj(hObj, Index, GUI_DRAW_BITMAP_Create(pBitmap, x, y));
  WM_InvalidateWindow(hObj);
}

/*********************************************************************
*
*       HEADER_SetBitmap
*/
void HEADER_SetBitmap(HEADER_Handle hObj, unsigned Index, const GUI_BITMAP* pBitmap) {
  HEADER_SetBitmapEx(hObj, Index, pBitmap, 0, 0);
}

#else                            /* Avoid problems with empty object modules */
  void HEADER_Bitmap_C(void) {}
#endif
