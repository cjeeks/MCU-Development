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
File        : LCD_SetAPI.C
Purpose     : Implementation of said function
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Private.h"
#include "GUIDebug.h"
#include "LCD_Private.h"      /* Required for configuration, APIList */

#if GUI_SUPPORT_DEVICES

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_SetAPI
*
* Purpose:
*   Sets the API table for a layer.
*   Some high level software (such as the VNC server, but maybe also the mouse "Cursor" module)
*   may need to override these pointers in order to link itself into the chain
*   of drawing routines.
*/
const tLCDDEV_APIList* LCD_SetAPI(const tLCDDEV_APIList* pAPI, int Index) {
  const tLCDDEV_APIList* pOldAPI;
  pOldAPI = LCD_aAPI[Index];
  /* Also aplly changes to current context if LCD of this layer is selected */
  if ((GUI_Context.SelLayer == Index) && (GUI_Context.hDevData == 0)) {
    GUI_Context.pDeviceAPI = pAPI;
  }
  LCD_aAPI[Index] = pAPI;
  return pOldAPI;
}

#else

void LCD_SetAPI_C(void);
void LCD_SetAPI_C(void) {}

#endif

/*************************** End of file ****************************/
