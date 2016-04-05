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
File        : GUIDEMO_Speed.c
Purpose     : Speed demo
----------------------------------------------------------------------
*/

#include <stdlib.h>  /* for rand */
#include "GUI.h"
#include "GUIDEMO.h"

static const GUI_COLOR _aColor[8] = {
  0x000000, 
  0x0000FF, 
  0x00FF00, 
  0x00FFFF, 
  0xFF0000, 
  0xFF00FF, 
  0xFFFF00, 
  0xFFFFFF
};

/*********************************************************************
*
*       GUIDEMO_Speed
*
**********************************************************************
*/

void GUIDEMO_Speed(void) {
  int t, i;
  I32 NumPixels = 0;
  U16 aColorIndex[8];
  GUIDEMO_ShowIntro("High speed",
                    "\nmulti layer clipping"
                    "\nhighly optimized drivers"
                    );
  for (i = 0; i< 8; i++) {
    aColorIndex[i] = GUI_Color2Index(_aColor[i]);
  }  
  t = GUI_GetTime();
  for (i = 0; ((GUI_GetTime() - t) < 8000) && !GUIDEMO_CheckCancel(); i++) {
    GUI_RECT r;
    GUI_SetColorIndex(aColorIndex[i&7]);
    /* Calculate random positions */
    r.x0 = rand() % LCD_XSIZE - LCD_XSIZE / 2;
    r.y0 = rand() % LCD_YSIZE - LCD_YSIZE / 2;
    r.x1 = r.x0 + 20 + rand() % LCD_XSIZE;
    r.y1 = r.y0 + 20 + rand() % LCD_YSIZE;
    GUI_FillRect(r.x0, r.y0, r.x1, r.y1);
    /* Clip rectangle to visible area and add the number of pixels (for speed computation) */
    if (r.x1 >= LCD_XSIZE)
      r.x1 = LCD_XSIZE - 1;
    if (r.y1 >= LCD_YSIZE)
      r.y1 = LCD_YSIZE - 1;
    if (r.x0 < 0 )
      r.x0 = 0;
    if (r.y1 < 0)
      r.y1 = 0;
    NumPixels += (r.x1 - r.x0) * (r.y1 - r.y0);
    /* Allow short breaks so we do not use all available CPU time ... */
  }
  t = (GUI_GetTime() - t) / 100;
  GUI_Clear();
  GUIDEMO_NotifyStartNext();
  #if GUIDEMO_LARGE
    GUI_SetFont(&GUI_FontComic24B_ASCII);
  #elif !(GUIDEMO_TINY)
    GUI_SetFont(&GUI_Font16B_ASCII);
  #else
    GUI_SetFont(&GUI_Font13B_ASCII);
  #endif
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringAt("Pixels/sec: ", 5, (LCD_YSIZE - GUI_GetFontSizeY()) / 2);
  if (t == 0)
    t++;
  GUI_DispDecMin(10 * (NumPixels / t));
  GUIDEMO_Wait();
}
