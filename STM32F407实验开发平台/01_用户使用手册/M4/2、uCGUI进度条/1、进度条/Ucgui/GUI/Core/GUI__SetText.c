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
File        : GUI__SetText.C
Purpose     : Implementation of said function
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__SetText
*/
int GUI__SetText(GUI_HMEM* phText, const char* s) {
  int r = 0;
  if (GUI__strcmp_hp(*phText, s) != 0) {            /* Make sure we have a quick out if nothing changes */
    GUI_HMEM hMem;
    hMem = GUI_ALLOC_AllocNoInit(GUI__strlen(s) + 1);
    if (hMem) {
      char* pMem;
      pMem = (char*) GUI_ALLOC_h2p(hMem);
      strcpy(pMem, s);
      GUI_ALLOC_FreePtr(phText);
      *phText = hMem;
      r = 1;
    }
  }
  return r;
}

/*************************** End of file ****************************/
