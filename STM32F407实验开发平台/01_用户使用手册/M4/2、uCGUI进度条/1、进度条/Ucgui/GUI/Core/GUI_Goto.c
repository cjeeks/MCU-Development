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
File        : GUI_Goto.c
Purpose     : Implementation of GUI_Goto... routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include <string.h>
#include "GUI_Protected.h"
 
/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _GotoY
*/
static char _GotoY(int y) {
  GUI_Context.DispPosY = y;
  return 0;
}

/*********************************************************************
*
*       _GotoX
*/
static char _GotoX(int x) {
  GUI_Context.DispPosX = x;
  return 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GotoY
*/
char GUI_GotoY(int y) {
  char r;
  GUI_LOCK();
  r = _GotoY(y);
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_GotoX
*/
char GUI_GotoX(int x) {
  char r;
  GUI_LOCK();
  r = _GotoX(x);
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_GotoXY
*/
char GUI_GotoXY(int x, int y) {
  char r;
  GUI_LOCK();
  r  = _GotoX(x);
  r |= _GotoY(y);
  GUI_UNLOCK();
  return r;
}

/*************************** End of file ****************************/
