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
File        : GUITime.C
Purpose     : Time related routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GetTime
*/
int GUI_GetTime(void) {
  return GUI_X_GetTime();
}

/*********************************************************************
*
*       GUI_Delay
*/
void GUI_Delay(int Period) {
  int EndTime = GUI_GetTime()+Period;
  int tRem; /* remaining Time */
  GUI_ASSERT_NO_LOCK();
  while (tRem = EndTime- GUI_GetTime(), tRem>0) {
    GUI_Exec();
    GUI_X_Delay((tRem >5) ? 5 : tRem);
  }
}

/*************************** End of file ****************************/
