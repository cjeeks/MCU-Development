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
File        : GUIDEMO_Intro.c
Purpose     : Introduction for emWin generic demo
              (This is also a good file to demo and explain basic
              emWin features by setting breakpoints)
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"
#include <string.h>

/*********************************************************************
*
*       GUIDEMO_Intro
*
**********************************************************************
*/

#if GUIDEMO_LARGE

void GUIDEMO_Intro(void) {
  int xCenter = LCD_XSIZE >> 1;
  int y, yPos;
  char acText[50] = "Version of emWin: ";
  strcat(acText, GUI_GetVersionString());
  GUIDEMO_SetBkColor(GUI_BLUE);
  GUIDEMO_SetColor(GUI_WHITE);
  GUI_Clear();
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_DispStringHCenterAt("emWin", xCenter, y = 12);
  GUI_SetFont(&GUI_Font13H_ASCII);
  GUI_DispStringHCenterAt("Universal graphic software"
                          "\nfor embedded applications"
                          , xCenter, y += 23);
  GUI_SetColor(GUI_RED);
  GUI_SetFont(&GUI_Font16_ASCII);
  GUI_DispStringHCenterAt("Any CPU - Any LCD - Any Application"
                          , xCenter, y += 32);
  GUI_SetFont(&GUI_Font10S_ASCII);
  GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, xCenter, y += 18);
  GUI_SetFont(&GUI_Font13HB_ASCII);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringHCenterAt(acText, xCenter, y += 15);
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringHCenterAt("www.segger.com", LCD_XSIZE >> 1, LCD_YSIZE - 20);
  yPos  = y + 15 + ((LCD_YSIZE - y - 33) >> 1);
  yPos -= bmSeggerLogoBlue.YSize >> 1;
  if (yPos > 160) {
    yPos = 160;
  }
  GUI_DrawBitmap(&bmSeggerLogoBlue, (LCD_XSIZE - bmSeggerLogoBlue.XSize) >> 1, yPos);
  #if (LCD_YSIZE >= 220)
    GUI_SetFont(&GUI_Font10S_ASCII);
    GUI_DispStringAt("GUI_OS: ", 0, LCD_YSIZE - 30); GUI_DispDecMin(GUI_OS);
    GUI_DispStringAt("GUI_ALLOC_SIZE: ",0, LCD_YSIZE - 20); GUI_DispDecMin(GUI_ALLOC_SIZE);
    GUI_DispStringAt("Compiler: "
    #ifdef _MSC_VER
      "Microsoft"
    #elif defined (NC308)
      "Mitsubishi NC308"
    #elif defined (NC30)
      "Mitsubishi NC30"
    #elif defined (__TID__)
      #if (((__TID__ >>8) &0x7f) == 48)            /* IAR MC80 */
        "IAR M32C"
      #elif (((__TID__ >>8) &0x7f) == 85)          /* IAR V850 */
        "IAR V850"
      #elif defined (__ICCARM__)                   /* IAR ARM  */
        "IAR ARM"
      #else                                        /* IAR MC16 */
        "IAR M32C"
      #endif
    #elif defined __WATCOMC__                      /* WATCOM */
        "WATCOM"
    #elif defined __GNUC__
        "GNU"
    #else
      "Unknown"
    #endif
      ,0, LCD_YSIZE - 10);
  #endif
  GUIDEMO_Delay(5000);
  GUIDEMO_NotifyStartNext();
}

#else /* GUIDEMO_LARGE */

void GUIDEMO_Intro(void) {
  #if GUIDEMO_TINY
    char acText[20] = "Version: ";
  #else
    char acText[32] = "Version of emWin: ";
  #endif
  int xCenter, dy, y0 = 0;
  xCenter = LCD_XSIZE >> 1;
  #if (LCD_YSIZE < 72)
    dy = 0;
  #else
    dy = ((LCD_YSIZE - 72) >> 3);
    if (dy > 14) dy = 14;
  #endif
  strcat(acText, GUI_GetVersionString());
  /* Clear the background */
  GUIDEMO_SetBkColor(GUI_BLUE);
  GUIDEMO_SetColor(GUI_WHITE);
  GUI_Clear();
  /* Display headline */
  GUI_SetFont(&GUI_Font13B_ASCII);
  GUI_DispStringHCenterAt("emWin", xCenter, dy + 1);
  /* Display description */
  #if (LCD_XSIZE < 140)
    GUI_SetFont(&GUI_Font8_ASCII);
  #else
    GUI_SetFont(&GUI_Font10_ASCII);
  #endif
  GUI_DispStringHCenterAt("Universal graphic software\n"
                          "for embedded applications", xCenter, 2 * dy + 18);
  /* Display compile time */
  GUI_SetFont(&GUI_Font10S_ASCII);
  GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, xCenter, 3 * dy + 37);
  /* Display version number */
  #if (LCD_YSIZE < 80)
    GUI_DispStringAt(acText, 6, LCD_YSIZE - 13);
  #else
    GUI_DispStringHCenterAt(acText, xCenter, 4 * dy + 49);
  #endif
  GUIDEMO_Delay(5000);
  GUIDEMO_NotifyStartNext();
  /* Show SEGGER logo */
  GUI_Clear();
  #if GUIDEMO_TINY
    y0 = 2;
  #endif
  #if (LCD_YSIZE >= 90)
    y0 += (LCD_YSIZE - 90) >> 1;
  #endif
  GUI_DrawBitmap(&bmSeggerLogoBlue, xCenter - (bmSeggerLogoBlue.XSize >> 1), y0);
  /* Display URL */
  #if (LCD_YSIZE < 80)
    GUI_SetFont(&GUI_Font10_ASCII);
  #else
    GUI_SetFont(&GUI_Font13B_ASCII);
  #endif
  y0 += bmSeggerLogoBlue.YSize + 1;
  GUI_DispStringHCenterAt("www.segger.com", xCenter, y0);
  GUIDEMO_Delay(5000);
  GUIDEMO_NotifyStartNext();
}

#endif
