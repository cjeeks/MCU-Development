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
File        : GUIDEMO_DemoFrameWin.c
Purpose     : Demonstrates the FRAMEWIN widget
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "GUI.h"
#include "GUIDEMO.h"

#if GUI_WINSUPPORT

#include "WM.h"
#include "LISTBOX.h"
#include "FRAMEWIN.h"

/*********************************************************************
*
*       defines
*
**********************************************************************
*/

#if GUIDEMO_LARGE
  #define BORDER 10
#elif !(GUIDEMO_TINY)
  #define BORDER  8
#else
  #define BORDER  4
#endif

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

static const GUI_ConstString _asLang[] = {
  "English", 
  "Deutsch", 
  "Français", 
  "Espa\xf1ol", /* "Español" -> "Espa\xf1ol" to avoid problems with NC308 */
  "Italiano", 
  NULL 
};

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIDEMO_DemoFrameWin
*/
void GUIDEMO_DemoFrameWin(void) {
  FRAMEWIN_Handle hFrame;
  LISTBOX_Handle hListBox;
  int xSize = LCD_GetXSize();
  int ySize = LCD_GetYSize();
  int i, x, y, w, h;
  const GUI_FONT* pFont = &GUI_FontComic18B_1;
  GUI_COLOR DesktopColorOld;
  #if GUIDEMO_LARGE
    GUIDEMO_ShowIntro("Frame Window & Listbox", NULL);
  #else
    GUIDEMO_ShowIntro("Frame Window\n & Listbox", NULL);
  #endif
  DesktopColorOld = GUIDEMO_SetBkColor(GUI_RED);
  DesktopColorOld = WM_SetDesktopColor(DesktopColorOld);      /* Automatically update desktop window */
  x = BORDER;
  #if GUIDEMO_LARGE
    y = 75;
  #else
    y = BORDER;
  #endif
  w = xSize - x - BORDER;
  h = ySize - y - BORDER;
  if (w > 140) {
    w = 140;
  }
  if (h > 120) {
    h = 120;
  }
  hFrame = FRAMEWIN_Create("Select language", NULL, WM_CF_SHOW, x, y, w, h);
  FRAMEWIN_SetActive(hFrame, 1);
  FRAMEWIN_SetMoveable(hFrame, 1);
  FRAMEWIN_AddMaxButton(hFrame, FRAMEWIN_BUTTON_RIGHT, 0);
  FRAMEWIN_AddMinButton(hFrame, FRAMEWIN_BUTTON_RIGHT, 1);
  FRAMEWIN_SetFont(hFrame, &GUI_Font13_ASCII);
  hListBox = LISTBOX_CreateAsChild(_asLang, WM_GetClientWindow(hFrame), 0, 0, 0, 0, WM_CF_SHOW | WM_SF_ANCHOR_LEFT | WM_SF_ANCHOR_TOP | WM_SF_ANCHOR_RIGHT | WM_SF_ANCHOR_BOTTOM);
  WM_SetFocus(hListBox);
  LISTBOX_SetFont(hListBox, pFont);
  GUIDEMO_Wait();
  for (i = 0; (i < 10) && !GUIDEMO_CheckCancel(); i++) {
    LISTBOX_IncSel(hListBox);
    GUIDEMO_Delay(250);
	}
  for (i = 0; (i < 10) && !GUIDEMO_CheckCancel(); i++) {
    LISTBOX_DecSel(hListBox);
    GUIDEMO_Delay(250);
	}
  GUIDEMO_Delay(500);
  LISTBOX_Delete(hListBox);
  FRAMEWIN_Delete(hFrame);
  WM_SetDesktopColor(DesktopColorOld);
}

#elif defined(NC30) || defined(NC308)

void GUIDEMO_FrameWin(void) {}

#endif
