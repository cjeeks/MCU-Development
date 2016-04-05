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
File        : GUI_ARRAY_InsertItem.c
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
*       GUI_ARRAY_InsertBlankItem
*
* Purpose:
*   Inserts a blank element in a GUI_ARRAY.
*
* Parameters:
*   Index   Index of the element to insert before
*           0 means: Insert before first element
*           1 means: Insert before second element
*
* Return value:
*   1 if successful
*   0 if failed
*
* Notes:
*   (1) Index changes
*       The index of all items after the one inserted will change
*       (Increment by 1)
*/
char GUI_ARRAY_InsertBlankItem(GUI_ARRAY* pThis, unsigned int Index) {
  GUI_ARRAY_CHECK(pThis);    /* Sanity checks at higher debug levels only */

  if (Index >= (unsigned)pThis->NumItems) {
    GUI_DEBUG_ERROROUT("GUI_ARRAY_InsertBlankItem: Illegal index");
  } else {
    WM_HMEM hNewBuffer;
    hNewBuffer = GUI_ALLOC_AllocZero(sizeof(WM_HMEM) * (pThis->NumItems + 1));
    if (hNewBuffer == 0) {
      GUI_DEBUG_ERROROUT("GUI_ARRAY_InsertBlankItem: Failed to alloc buffer");
    } else {
      WM_HMEM *pOldBuffer;
      WM_HMEM *pNewBuffer;
      pNewBuffer = (WM_HMEM*) GUI_ALLOC_h2p(hNewBuffer);
      pOldBuffer = (WM_HMEM*) GUI_ALLOC_h2p(pThis->haHandle);
      memcpy(pNewBuffer, pOldBuffer, Index * sizeof(WM_HMEM));
      memcpy(pNewBuffer + (Index + 1), pOldBuffer + Index, (pThis->NumItems - Index) * sizeof(WM_HMEM));
      GUI_ALLOC_Free(pThis->haHandle);
      pThis->haHandle = hNewBuffer;
      pThis->NumItems++;
      return 1;               /* Successfull */
    }
  }
  return 0;                   /* Failed */
}

/*********************************************************************
*
*       GUI_ARRAY_InsertItem
*
* Purpose:
*   Inserts an element in a GUI_ARRAY.
*
*
* Parameters:
*   Index   Index of the element to insert before
*           0 means: Insert before first element
*           1 means: Insert before second element
*
* Return value:
*   Handle of allocated memory block if successful
*   0 if failed
*
* Notes:
*   (1) Index changes
*       The index of all items after the one inserted will change
*       (Increment by 1)
*/
WM_HMEM GUI_ARRAY_InsertItem(GUI_ARRAY* pThis, unsigned int Index, int Len) {
  WM_HMEM hNewBuffer = 0;
  if (GUI_ARRAY_InsertBlankItem(pThis, Index)) {
    hNewBuffer = GUI_ARRAY_SetItem(pThis, Index, 0, Len);
  }
  return hNewBuffer;
}

#else  /* avoid empty object files */

void GUI_ARRAY_InsertItem_C(void);
void GUI_ARRAY_InsertItem_C(void){}

#endif
