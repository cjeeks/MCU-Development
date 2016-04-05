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
File        : GUIDEMO_HardwareInfo.c
Purpose     : Displays hardware info
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"
#include "LCD_ConfDefaults.h"      /* valid LCD configuration */

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

#if (LCD_CONTROLLER == 1375) | (LCD_CONTROLLER == 13705) | (LCD_CONTROLLER == 1386) | (LCD_CONTROLLER == 13806)
static void _Show(const char* s0, const char* s1) {
  GUIDEMO_SetColor(GUI_WHITE);
  #if (LCD_YSIZE < 160)
    GUI_SetFont(&GUI_Font8_ASCII);
  #else
    GUI_SetFont(&GUI_Font13B_ASCII);
  #endif
  GUI_DispString("\n");
  #if (LCD_YSIZE < 128)
    GUIDEMO_Delay(200);
    GUI_GotoXY(0, LCD_YSIZE / 2 - 6);
    GUI_ClearRect(0, 24, LCD_XSIZE - 1, LCD_YSIZE - 1);
    GUIDEMO_Delay(200);
  #endif
  GUI_DispString(s0);
  GUIDEMO_Delay(500);
  #if GUIDEMO_LARGE
    GUI_GotoX(110);
    GUIDEMO_SetColor(GUI_GREEN);
  #else
    GUI_GotoX(100);
    GUIDEMO_SetColor(GUI_BLUE);
  #endif
  #if (LCD_XSIZE < 320)
    GUI_DispString("\n");
    #if (LCD_XSIZE < 200)
      GUI_GotoX(10);
    #else
      GUI_GotoX(LCD_XSIZE / 6);
    #endif
  #endif
  GUI_DispString(s1);
  GUIDEMO_Delay(1000);
}
#endif

/*********************************************************************
*
*       GUIDEMO_HardwareInfo
*
**********************************************************************
*/

void GUIDEMO_HardwareInfo(void) {
  #if (LCD_CONTROLLER == 1375) | (LCD_CONTROLLER == 13705) | (LCD_CONTROLLER == 1386) | (LCD_CONTROLLER == 13806)
    GUIDEMO_ShowIntro("Hardware info",   "" );
    GUI_Clear();
    #if GUIDEMO_LARGE
      GUI_SetFont(&GUI_FontComic24B_ASCII);
    #else
      GUI_SetFont(&GUI_FontComic18B_ASCII);
    #endif
    GUIDEMO_SetColor(GUI_WHITE);
    #if (LCD_CONTROLLER == 1375) | (LCD_CONTROLLER == 13705)
      #if GUIDEMO_LARGE
        GUI_DispStringAt("EPSON 13705\n", 10, 65 );
      #else
        GUI_DispStringHCenterAt("EPSON 13705\n", LCD_XSIZE >> 1, LCD_YSIZE / 14);
      #endif
      _Show("On chip VRAM",  "80 kb");
      _Show("Max. colors",   "4096 (4 bit per color)");
      _Show("Display types", "Mono / color / TFT");
      _Show("LUT",           "256 index colors");
    #elif (LCD_CONTROLLER == 1386) | (LCD_CONTROLLER == 13806)
      #if GUIDEMO_LARGE
        GUI_DispStringAt("EPSON 13806\n", 10, 65 );
      #else
        GUI_DispStringHCenterAt("EPSON 13806\n", LCD_XSIZE >> 1, LCD_YSIZE / 14);
      #endif
      _Show("On chip VRAM",  "1200 kb");
      _Show("Max. colors",   "65536 (up to 16 bpp)");
      _Show("Display types", "Mono / color / TFT (analog / digital)");
      _Show("LUT",           "256 index colors");
    #endif
    GUIDEMO_Delay(1500);
  #endif
}
