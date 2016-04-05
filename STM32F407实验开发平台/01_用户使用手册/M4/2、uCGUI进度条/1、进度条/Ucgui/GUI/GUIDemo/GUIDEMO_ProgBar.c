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
File        : GUIDEMO_DemoProgBar.c
Purpose     : Progress bar demo
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"

#if GUI_WINSUPPORT

#include "PROGBAR.h"

/*********************************************************************
*
*       GUIDEMO_DemoProgBar
*
**********************************************************************
*/

void GUIDEMO_DemoProgBar(void) {
  PROGBAR_Handle ahProgBar[2];
  int i, iRep;
  int XMid = LCD_GetXSize() / 2;
  int YMid = LCD_GetYSize() / 2;
  #if GUIDEMO_LARGE
    int MaxReps = 2;
    int Length[2] = {110, 140};
    int Height[2] = {20, 10};
    int y0 = YMid - 40;
    int dy = 10;
  #elif !(GUIDEMO_TINY)
    int MaxReps = 1;
    int Length[2] = {100, 130};
    int Height[2] = {18, 10};
    int y0 = YMid - 38;
    int dy = 9;
  #else
    int MaxReps = 1;
    int Length[2] = {85, 115};
    int Height[2] = {16, 8};
    int y0 = YMid - 35;
    int dy = 8;
  #endif
  if (YMid < 40) {
    Height[0] = 14;
    y0 = 1;
    dy = 4;
  }
  GUIDEMO_ShowIntro("Widgets", 
                    "\nProgressbars in"
                    "\nall variations");
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font8x16);
  GUI_DispStringHCenterAt("Progress bar", XMid, y0);
  /* Create `em */  
  ahProgBar[0] = PROGBAR_Create(XMid - Length[0] / 2,
                                YMid - Height[0],
                                Length[0], 
                                Height[0], 
                                WM_CF_SHOW);
  ahProgBar[1] = PROGBAR_Create(XMid - Length[1] / 2,
                                YMid + dy,
                                Length[1], 
                                Height[1], 
                                WM_CF_SHOW);
  /* Use memory device (optional, for better looks) */
  #if GUI_SUPPORT_MEMDEV
    PROGBAR_EnableMemdev(ahProgBar[0]);
    PROGBAR_EnableMemdev(ahProgBar[1]);
  #endif
  GUIDEMO_Delay (800);
  PROGBAR_SetMinMax(ahProgBar[1], 0, 500);
  for (iRep = 0; iRep < MaxReps; iRep++) {
    #if !(GUIDEMO_TINY)
      PROGBAR_SetFont(ahProgBar[0], &GUI_Font8x16);
    #endif
    #if   (LCD_BITSPERPIXEL == 2)
      PROGBAR_SetBarColor(ahProgBar[0], 0, GUI_DARKGRAY);
      PROGBAR_SetBarColor(ahProgBar[1], 0, GUI_DARKGRAY);
      PROGBAR_SetBarColor(ahProgBar[0], 1, GUI_WHITE);
      PROGBAR_SetBarColor(ahProgBar[1], 1, GUI_WHITE);
    #elif (LCD_BITSPERPIXEL <= 4)
      PROGBAR_SetBarColor(ahProgBar[0], 0, GUI_DARKGRAY);
      PROGBAR_SetBarColor(ahProgBar[0], 1, GUI_LIGHTGRAY);
    #else
      PROGBAR_SetBarColor(ahProgBar[0], 0, GUI_GREEN);
      PROGBAR_SetBarColor(ahProgBar[0], 1, GUI_RED);
    #endif
    for (i = 0; (i <= 100) && !GUIDEMO_CheckCancel(); i++) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], i);
      GUI_Delay(5);
    }
    PROGBAR_SetText(ahProgBar[0], "Tank empty");
    for (; (i >= 0)&& !GUIDEMO_CheckCancel(); i--) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], 200 - i);
      GUI_Delay(5);
    }
    PROGBAR_SetText(ahProgBar[0], "Any text ...");
    PROGBAR_SetTextAlign(ahProgBar[0], GUI_TA_LEFT);
    for (; (i <= 100)&& !GUIDEMO_CheckCancel(); i++) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], 200 + i);
      GUI_Delay(5);
    }
    for (; (i >= 0)&& !GUIDEMO_CheckCancel(); i--) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], 400 - i);
      GUI_Delay(5);
    }
    PROGBAR_SetFont(ahProgBar[0], &GUI_FontComic18B_1);
    PROGBAR_SetText(ahProgBar[0], "Any font ...");
    for (; (i <= 100)&& !GUIDEMO_CheckCancel(); i++) {
      PROGBAR_SetValue(ahProgBar[0], i);
      PROGBAR_SetValue(ahProgBar[1], 400 + i);
      GUI_Delay(5);
    }
    GUIDEMO_Delay(1000);
  }
  GUIDEMO_Delay(1000);
  PROGBAR_Delete(ahProgBar[0]);
  PROGBAR_Delete(ahProgBar[1]);
  GUIDEMO_Delay(1000);
  GUI_SetFont(&GUI_Font10S_ASCII);
}

#elif defined(NC30) || defined(NC308)

void GUIDEMO_ProgBar(void) {}

#endif /* GUI_WINSUPPORT */
