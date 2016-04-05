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
File        : GUIDEMO_Messagebox.c
Purpose     : Messagebox samples
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI.h"
#include "GUIDEMO.h"
#include "LCD_ConfDefaults.h"

#if GUI_WINSUPPORT

#include "WM.h"
#include "DIALOG.h"

/*********************************************************************
*
*       GUIDEMO_Dialog
*
**********************************************************************
*/

void GUIDEMO_Messagebox(void) {
  GUI_COLOR Color;
  GUIDEMO_ShowIntro("Message boxes",
                    "Message boxes" "\ncan easily be created");
  Color = WM_SetDesktopColor(GUI_RED);
  GUI_MessageBox("Message", "Text", 0);
  GUI_Delay(1000);
  GUI_MessageBox("2. Message", "Text", 0);
  GUI_Delay(1000);
  WM_SetDesktopColor(Color);
  GUIDEMO_NotifyStartNext();

}

#else

void GUIDEMO_Messagebox(void) {}

#endif /* GUI_SUPPORT_MEMDEV */
