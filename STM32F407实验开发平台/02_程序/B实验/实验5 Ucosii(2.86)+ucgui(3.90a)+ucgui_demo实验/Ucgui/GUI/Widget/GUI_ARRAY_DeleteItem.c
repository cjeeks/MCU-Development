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
File        : GUI_ARRAY_DeleteItem.c
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
*       GUI_ARRAY_DeleteItem
*
* Purpose:
*   Eliminate one element in a GUI_ARRAY.
*   This means:
*     - freeing the memory block
*     - moving the last item to the position of the deleted item
*     - possible reducing the size of the memory used for management (opt)
*
*/
void GUI_ARRAY_DeleteItem(GUI_ARRAY* pThis, unsigned int Index) {
  WM_HMEM ha;
  WM_HMEM* pa;
  int i;
  if (Index < (unsigned)pThis->NumItems) {
    ha = pThis->haHandle;
    if (ha) {
      int NumItems;
      WM_LOCK();
      pa = (WM_HMEM*) GUI_ALLOC_h2p(ha);
      /* Free the attached item */
      GUI_ALLOC_FreePtr(pa + Index);
      /* Move the last items to the position of the deleted item */
      NumItems = --pThis->NumItems;
      for (i = Index; i <= NumItems - 1; i++) {
        *(pa + i) = *(pa + i + 1);
      }
      WM_UNLOCK();
    }
  }
}

#else

void GUI_ARRAY_DeleteItem(void) {}

#endif
