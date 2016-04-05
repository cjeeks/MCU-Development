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
File        : GUI_DispStringInRect.c
Purpose     : Implementation of GUI_DispStringInRect
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include "GUI_Protected.h"
#if GUI_WINSUPPORT
  #include "WM.h"
#endif
 
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__DispStringInRect
*/
void GUI__DispStringInRect(const char GUI_UNI_PTR *s, GUI_RECT* pRect, int TextAlign, int MaxNumChars) {
  GUI_RECT r;
  GUI_RECT rLine;
  int y = 0;
  const char GUI_UNI_PTR *sOrg =s;
  int FontYSize;
  int xLine = 0;
  int LineLen;
  int NumCharsRem;           /* Number of remaining characters */
  FontYSize = GUI_GetFontSizeY();
  if (pRect) {
    r = *pRect;
  } else {
    GUI_GetClientRect(&r);
  }
  /* handle vertical alignment */
  if ((TextAlign & GUI_TA_VERTICAL) == GUI_TA_TOP) {
		y = r.y0;
  } else {
    int NumLines;
    /* Count the number of lines */
    for (NumCharsRem = MaxNumChars, NumLines = 1; NumCharsRem ;NumLines++) {
      LineLen = GUI__GetLineNumChars(s, NumCharsRem);
      NumCharsRem -= LineLen;
      s += GUI_UC__NumChars2NumBytes(s, LineLen);
      if (GUI__HandleEOLine(&s))
        break;
    }
    /* Do the vertical alignment */
    switch (TextAlign & GUI_TA_VERTICAL) {
	  case GUI_TA_BASELINE:
	  case GUI_TA_BOTTOM:
	  y = r.y1 -NumLines * FontYSize+1;
      break;
	  case GUI_TA_VCENTER:
		  y = r.y0+(r.y1-r.y0+1 -NumLines * FontYSize) /2;
      break;
	  }
  }
  /* Output string */
  for (NumCharsRem = MaxNumChars, s = sOrg; NumCharsRem;) {
    int xLineSize;
    LineLen = GUI__GetLineNumChars(s, NumCharsRem);
    NumCharsRem -= LineLen;
    xLineSize = GUI__GetLineDistX(s, LineLen);
    switch (TextAlign & GUI_TA_HORIZONTAL) {
    case GUI_TA_HCENTER:
      xLine = r.x0+(r.x1-r.x0-xLineSize)/2; break;
    case GUI_TA_LEFT:
      xLine = r.x0; break;
    case GUI_TA_RIGHT:
      xLine = r.x1 -xLineSize + 1;
    }
    rLine.x0 = GUI_Context.DispPosX = xLine;
    rLine.x1 = rLine.x0 + xLineSize-1;
    rLine.y0 = GUI_Context.DispPosY = y;
    rLine.y1 = y + FontYSize-1;
    GUI__DispLine(s, LineLen, &rLine);
    s += GUI_UC__NumChars2NumBytes(s, LineLen);
    y += GUI_GetFontDistY();
    if (GUI__HandleEOLine(&s))
      break;
  }
}

/*********************************************************************
*
*       GUI_DispStringInRectMax
*/
#if (GUI_WINSUPPORT)
void GUI_DispStringInRectMax(const char GUI_UNI_PTR *s, GUI_RECT* pRect, int TextAlign, int MaxLen) {
  if (s) {
    const GUI_RECT *pOldClipRect = NULL;
    GUI_RECT r;
    GUI_LOCK();
    if (pRect) {
      pOldClipRect = WM_SetUserClipRect(pRect);
      if (pOldClipRect) {
        GUI__IntersectRects(&r, pRect, pOldClipRect);
        WM_SetUserClipRect(&r);
      }
    }
    GUI__DispStringInRect(s, pRect, TextAlign, MaxLen);
    WM_SetUserClipRect(pOldClipRect);
    GUI_UNLOCK();
  }
}

#else

void GUI_DispStringInRectMax(const char GUI_UNI_PTR *s, GUI_RECT* pRect, int TextAlign, int MaxLen) {
  GUI_RECT Rect_Old, r;
  if (s && pRect) {
    GUI_LOCK();
    Rect_Old = GUI_Context.ClipRect;
    GUI__IntersectRects(&r, pRect, &Rect_Old);
    LCD_SetClipRectEx(&r);
    GUI__DispStringInRect(s, pRect, TextAlign, MaxLen);
    LCD_SetClipRectEx(&Rect_Old);
    GUI_UNLOCK();
  }
}
#endif

/*********************************************************************
*
*       GUI_DispStringInRect
*/
void GUI_DispStringInRect(const char GUI_UNI_PTR *s, GUI_RECT* pRect, int TextAlign) {
  GUI_DispStringInRectMax(s, pRect, TextAlign, 0x7fff);
}

/*************************** End of file ****************************/
