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
File        : GUIDEMO_Circle.c
Purpose     : Drawing circles
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"

/*********************************************************************
*
*       GUIDEMO_Circle
*
**********************************************************************
*/

void GUIDEMO_Circle(void) {
  int x0, y0, r;
  GUIDEMO_ShowIntro("Circles",
                    "\nArbitrary circles"
                    "\nand arcs.");
  GUI_Clear();
  GUI_SetFont(&GUI_Font8x16);
  GUI_SetColor(GUI_WHITE);
  x0 = LCD_XSIZE >> 1;
  y0 = LCD_YSIZE >> 1;
  #if GUIDEMO_LARGE
    r = 50;
    GUI_DispStringAt("Circle", 0, 0);
  #elif !(GUIDEMO_TINY)
    r = 40;
  #else
    #if (LCD_YSIZE < 80)
      r = 23;
    #else
      r = 30;
    #endif
  #endif
  GUI_FillCircle (x0, y0, r);
  GUIDEMO_Wait();
  GUI_SetDrawMode(GUI_DM_XOR);
  #if GUIDEMO_LARGE
    GUI_FillCircle (x0, y0, r + 10);
  #elif !(GUIDEMO_TINY)
    GUI_FillCircle (x0, y0, r + 8);
  #else
    GUI_FillCircle (x0, y0, r + 6);
  #endif
  GUI_SetDrawMode(0);
  GUIDEMO_Wait();
  #if GUI_SUPPORT_AA
    #if GUIDEMO_LARGE
      GUIDEMO_ShowInfo("Circles with\nAntialiasing");
    #endif
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    #if GUIDEMO_LARGE
      GUI_DispStringAt("Antialiased\ncircle", 0, 0);
    #endif
    GUI_AA_FillCircle(x0, y0, r - 2);
    GUIDEMO_Wait();
  #endif
}
