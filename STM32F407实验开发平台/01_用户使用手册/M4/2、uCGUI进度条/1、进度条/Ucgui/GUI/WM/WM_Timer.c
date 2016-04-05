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
File        : WM_Timer.c
Purpose     : Implementetion of WM_CreateTimer, WM_DeleteTimer
              for systems with external one shot timers.
              (--> Philips, 2003)

              This module requires 2 macros in order to work and
              generate code:
              GUI_X_CREATE_TIMER(Period, void (*cb)(int))
              GUI_X_DELETE_TIMER(ID)

              Note that the delete macro is optional, since
              one-shot-timers are expected to delete themselves.
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"


/* Typical configuration: */

#if GUI_WINSUPPORT && !defined(GUI_X_CREATE_TIMER)   /* If 0, WM will not generate any code */


/*********************************************************************
*
*       Required data structures
*
**********************************************************************
*/

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/


/*********************************************************************
*
*       WM_DeleteTimer
*
* Purpose:
*   API function (optional).
*   Allows the application to delete a timer. 
*/
void WM_DeleteTimer    (WM_HWIN hWin, int UserId) {
  WM_LOCK();
  GUI_USE_PARA(hWin);
  GUI_USE_PARA(UserId);
  WM_UNLOCK();
}


/*********************************************************************
*
*       WM_CreateTimer
*
*  Returns:    0 if failed, else != 0
*  Parameters:
*                hWin        Window handle of the window to receive the WM_TIMER message
*                UserId      User defined Id. If not needed, use 0.
*                Period      Number of time units (ticks)
*                Mode        0: one-shot
*
*/
int WM_CreateTimer               (WM_HWIN hWin, int UserId, int Period, int Mode) {
  int r = 0;
  WM_LOCK();
  GUI_USE_PARA(hWin);
  GUI_USE_PARA(UserId);
  GUI_USE_PARA(Period);
  GUI_USE_PARA(Mode);
  WM_UNLOCK();
  return r;
}

#else
  void WM_Timer_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
