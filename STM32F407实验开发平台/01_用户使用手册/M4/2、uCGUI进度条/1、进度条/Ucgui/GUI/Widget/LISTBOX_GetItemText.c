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
File        : LISTBOX_GetItemText.c
Purpose     : Implementation of said function
---------------------------END-OF-HEADER------------------------------
*/

#include "LISTBOX_Private.h"
#include <string.h>

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported routines:  Various methods
*
**********************************************************************
*/
/*********************************************************************
*
*       LISTBOX_GetItemText
*/
void LISTBOX_GetItemText(LISTBOX_Handle hObj, unsigned Index, char * pBuffer, int MaxSize) {
  if (hObj) {
    unsigned NumItems;
    LISTBOX_Obj* pObj;
    WM_LOCK();
    pObj = LISTBOX_H2P(hObj);
    NumItems = LISTBOX__GetNumItems(pObj);
    if (Index < NumItems) {
      const char * pString;
      int CopyLen;
      pString = LISTBOX__GetpString(pObj, Index);
      CopyLen = strlen(pString);
      if (CopyLen > (MaxSize - 1)) {
        CopyLen = MaxSize - 1;
      }
      memcpy(pBuffer, pString, CopyLen);
      pBuffer[CopyLen] = 0;
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_GetItemText_C(void) {}
#endif

/*************************** End of file ****************************/

