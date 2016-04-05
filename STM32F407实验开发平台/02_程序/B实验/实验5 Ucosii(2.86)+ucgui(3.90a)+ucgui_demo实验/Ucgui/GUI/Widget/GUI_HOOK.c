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
File        : GUI_HOOK.C
Purpose     : Implementation of GUI_HOOK
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "GUI_HOOK.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_HOOK_Add
*/
void GUI_HOOK_Add(GUI_HOOK** ppFirstHook, GUI_HOOK* pNewHook, GUI_HOOK_FUNC* pHookFunc) {
  pNewHook->pNext     = *ppFirstHook; /* New entry points to former first one in list */
  pNewHook->pHookFunc = pHookFunc;
  *ppFirstHook        = pNewHook;     /* New one is first one now */
}

/*********************************************************************
*
*       GUI_HOOK_Remove
*/
void GUI_HOOK_Remove(GUI_HOOK** ppFirstHook, GUI_HOOK* pHook) {
  GUI_USE_PARA(pHook);
  *ppFirstHook = NULL;
}

#else
  void GUI_HOOK_C(void);
  void GUI_HOOK_C(void) {} /* avoid empty object files */
#endif

/*************************** End of file ****************************/
