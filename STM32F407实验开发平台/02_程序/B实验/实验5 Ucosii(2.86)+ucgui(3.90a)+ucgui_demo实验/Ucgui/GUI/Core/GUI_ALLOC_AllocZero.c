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
File        : GUIAlloc.C
Purpose     : Dynamic memory management
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <string.h>           /* for memcpy, memset */

#include "GUI_Protected.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       Internal memory management
*
**********************************************************************
*/

/*********************************************************************
*
*       GUI_ALLOC_AllocZero
*/
GUI_HMEM GUI_ALLOC_AllocZero(GUI_ALLOC_DATATYPE Size) {
  GUI_HMEM hMem;
  GUI_LOCK();
  GUI_DEBUG_LOG2("\nGUI_ALLOC_Alloc... requesting %d, %d avail", Size, GUI_ALLOC_GetMaxSize());
  hMem = GUI_ALLOC_AllocNoInit(Size);
  if (hMem) {
    GUI_MEMSET((U8*)GUI_ALLOC_h2p(hMem), 0, Size);   /* Zeroinit ! */
  }
  GUI_UNLOCK();
  return hMem;
}

/*************************** End of file ****************************/
