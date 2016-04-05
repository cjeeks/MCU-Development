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
File        : GUIDEMO_Lut.c
Purpose     : Modify lookup table
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"
#include "LCD_ConfDefaults.h"  /* valid LCD configuration */

#if (LCD_BITSPERPIXEL > 2) && (LCD_BITSPERPIXEL <= 8)

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

static void _ModifyLUT(int RFaktor, int GFaktor, int BFaktor) {
  int NumColors = LCD_GetDevCap(LCD_DEVCAP_NUMCOLORS);
  int i;
  for (i = 0; (i < NumColors) && !GUIDEMO_CheckCancel(); i++) {    
    U32 Color = LCD_GetDevCap(LCD_DEVCAP_COLOR + i);
    U32 R = Color & 0xff;
    U32 G = (Color >> 8)  & 0xff;
    U32 B = (Color >> 16) & 0xff;
    /* Now modify color */
    R = (R * RFaktor) / 100; if (R > 255) R = 255;
    G = (G * GFaktor) / 100; if (G > 255) G = 255;
    B = (B * BFaktor) / 100; if (B > 255) B = 255;
    /* Write modified color into lookup table */
    Color = R | (G << 8) | (B << 16);
    GUI_SetLUTEntry((U8)i, Color);    
  }
}

/*********************************************************************
*
*       GUIDEMO_DemoLUT
*
**********************************************************************
*/

void GUIDEMO_DemoLUT(void) {
  int i;
  GUIDEMO_ShowIntro("Modify LUT", "... after drawing color bars");
  GUIDEMO_ShowColorBar();
	for (i = 100; (i >= 0) && !GUIDEMO_CheckCancel(); i -= 2) {
    _ModifyLUT(100, 100, i);
    GUI_Delay(20);
	}
	for (i = 100; (i >= 0) && !GUIDEMO_CheckCancel(); i -= 2) {
    _ModifyLUT(100, i, 0);
    GUI_Delay(20);
	}
	for (i = 100; (i >= 0) && !GUIDEMO_CheckCancel(); i -= 2) {
    _ModifyLUT(i, i, i);
    GUI_Delay(20);
	}
  LCD_InitLUT();
  GUIDEMO_Wait();
}

#else

void GUIDEMO_DemoLUT(void) {}

#endif
