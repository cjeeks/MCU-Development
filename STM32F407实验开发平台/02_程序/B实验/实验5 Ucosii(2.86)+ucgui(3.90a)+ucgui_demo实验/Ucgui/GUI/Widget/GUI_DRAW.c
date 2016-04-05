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
File        : GUI_DRAW.c
Purpose     : member functions of GUI_DRAW Object
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUI_Protected.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       puplic code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DRAW__Draw
*/
void GUI_DRAW__Draw(GUI_DRAW_HANDLE hDrawObj, int x, int y) {
  if (hDrawObj) {
    GUI_DRAW * pDrawObj;
    pDrawObj = (GUI_DRAW *)GUI_ALLOC_h2p(hDrawObj);
    pDrawObj->pConsts->pfDraw(pDrawObj, x, y);
  }
}

/*********************************************************************
*
*       GUI_DRAW__GetXSize
*/
int GUI_DRAW__GetXSize(GUI_DRAW_HANDLE hDrawObj) {
  if (hDrawObj) {
    GUI_DRAW * pDrawObj;
    pDrawObj = (GUI_DRAW *)GUI_ALLOC_h2p(hDrawObj);
    return pDrawObj->pConsts->pfGetXSize(pDrawObj);
  }
  return 0;
}

/*********************************************************************
*
*       GUI_DRAW__GetYSize
*/
int GUI_DRAW__GetYSize(GUI_DRAW_HANDLE hDrawObj) {
  if (hDrawObj) {
    GUI_DRAW * pDrawObj;
    pDrawObj = (GUI_DRAW *)GUI_ALLOC_h2p(hDrawObj);
    return pDrawObj->pConsts->pfGetYSize(pDrawObj);
  }
  return 0;
}

#else                            /* Avoid problems with empty object modules */
  void GUI_DRAW_C(void) {}
#endif

/*************************** End of file ****************************/

