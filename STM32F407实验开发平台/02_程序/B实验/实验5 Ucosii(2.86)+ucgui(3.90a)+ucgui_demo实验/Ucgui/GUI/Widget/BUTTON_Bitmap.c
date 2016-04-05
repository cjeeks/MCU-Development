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
File        : BUTTON_Bitmap.c
Purpose     : Button bitmap support
---------------------------END-OF-HEADER------------------------------
*/

#include "BUTTON_Private.h"

#if GUI_WINSUPPORT


/*********************************************************************
*
*       Exported functions
*
**********************************************************************
*/
/*********************************************************************
*
*       BUTTON_SetBitmapEx
*/
void BUTTON_SetBitmapEx(BUTTON_Handle hObj, unsigned int Index, const GUI_BITMAP * pBitmap, int x, int y) {
  BUTTON__SetDrawObj(hObj, Index, GUI_DRAW_BITMAP_Create(pBitmap, x, y));
}

/*********************************************************************
*
*       BUTTON_SetBitmap
*/
void BUTTON_SetBitmap(BUTTON_Handle hObj,unsigned int Index, const GUI_BITMAP* pBitmap) {
  BUTTON_SetBitmapEx(hObj, Index, pBitmap, 0, 0);
}

#else                            /* Avoid problems with empty object modules */
  void BUTTON_Bitmap_C(void) {}
#endif
