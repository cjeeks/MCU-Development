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
File        : GUI_GetVersionString.c
Purpose     : Version information functions
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static char _acVersion[] = {"X.XX\0\0"};

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GetVersionString
*/
const char* GUI_GetVersionString(void) {
  _acVersion[0] = '0' + (GUI_VERSION / 10000);
  _acVersion[2] = '0' + (GUI_VERSION /  1000) % 10;
  _acVersion[3] = '0' + (GUI_VERSION /   100) % 10;
  #if GUI_VERSION%100
    _acVersion[4] = 'a' - 1 + (GUI_VERSION % 100);
  #endif
  return _acVersion;
}

/*************************** End of file ****************************/
