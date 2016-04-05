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
File        : GUI_ARRAY_ResizeItem.c
Purpose     : Array handling routines
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_ARRAY.h"
#include <string.h>

#if GUI_WINSUPPORT

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_ARRAY_ResizeItem
*
* Purpose:
*   Resizes one element in a GUI_ARRAY.
* Return value:
*   Handle of allocated memory block if successful
*   0 if failed
*
*/
void* GUI_ARRAY_ResizeItem(GUI_ARRAY* pThis, unsigned int Index, int Len) {
  void* r = NULL;
  WM_HMEM hNew;
  hNew = GUI_ALLOC_AllocZero(Len);
  if (hNew) {
    void* pOld = GUI_ARRAY_GetpItem(pThis, Index);
    void* pNew = GUI_ALLOC_h2p(hNew);
    memcpy(pNew, pOld, Len);
    if (GUI_ARRAY_SethItem(pThis, Index, hNew)) {
      GUI_ALLOC_FreePtr(&hNew);    /* Free on error */
    } else {
      r = pNew;
    }
  }
  return r;
}

#else  /* avoid empty object files */

void GUI_ARRAY_ResizeItem_C(void);
void GUI_ARRAY_ResizeItem_C(void){}

#endif
