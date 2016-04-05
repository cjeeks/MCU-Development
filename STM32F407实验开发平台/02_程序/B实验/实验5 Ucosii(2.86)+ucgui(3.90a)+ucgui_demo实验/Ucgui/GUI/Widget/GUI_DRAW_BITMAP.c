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
File        : GUI_DRAW_BITMAP.c
Purpose     : 
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUI_Protected.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawBitmap
*/
static void _DrawBitmap(const GUI_DRAW* pObj, int x, int y) {
  GUI_DrawBitmap((const GUI_BITMAP *)pObj->Data.pData, x + pObj->xOff, y + pObj->yOff);
}

/*********************************************************************
*
*       _GetXSize
*/
static int _GetXSize(const GUI_DRAW* pObj) {
  return ((const GUI_BITMAP *)pObj->Data.pData)->XSize;
}

/*********************************************************************
*
*       _GetYSize
*/
static int _GetYSize(const GUI_DRAW* pObj) {
  return ((const GUI_BITMAP *)pObj->Data.pData)->YSize;
}

/*********************************************************************
*
*       static data, ConstObj
*
**********************************************************************
*/
static const GUI_DRAW_CONSTS _ConstObjData = {
  _DrawBitmap,
  _GetXSize,
  _GetYSize
};

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DRAW_BITMAP_Create
*/
WM_HMEM GUI_DRAW_BITMAP_Create(const GUI_BITMAP* pBitmap, int x, int y) {
  GUI_DRAW* pObj;
  WM_HMEM hMem;
  hMem = GUI_ALLOC_AllocZero(sizeof(GUI_DRAW));
  if (hMem) {
    WM_LOCK();
    pObj = (GUI_DRAW*)GUI_ALLOC_h2p(hMem);
    pObj->pConsts    = &_ConstObjData;
    pObj->Data.pData = (const void*)pBitmap;
    pObj->xOff       = x;
    pObj->yOff       = y;
    WM_UNLOCK();
  }
  return hMem;
}


#else                            /* Avoid problems with empty object modules */
  void GUI_DRAW_BITMAP_C(void) {}
#endif
