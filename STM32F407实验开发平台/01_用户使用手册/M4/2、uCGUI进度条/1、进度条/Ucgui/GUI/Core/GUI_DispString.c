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
File        : GUI_DispString.C
Purpose     : Implementation of GUI_DispString function.
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <stdio.h>
#include "GUI_Protected.h"
 
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DispString
*/
void GUI_DispString(const char GUI_UNI_PTR *s) {
  int xAdjust, yAdjust, xOrg;
  int FontSizeY;
  if (!s)
    return;
  GUI_LOCK();
  FontSizeY = GUI_GetFontDistY();
  xOrg = GUI_Context.DispPosX;
 /* Adjust vertical position */
  yAdjust = GUI_GetYAdjust();
  GUI_Context.DispPosY -= yAdjust;
  for (; *s; s++) {
    GUI_RECT r;
    int LineNumChars = GUI__GetLineNumChars(s, 0x7fff);
    int xLineSize    = GUI__GetLineDistX(s, LineNumChars);
  /* Check if x-position needs to be changed due to h-alignment */
    switch (GUI_Context.TextAlign & GUI_TA_HORIZONTAL) { 
      case GUI_TA_CENTER: xAdjust = xLineSize / 2; break;
      case GUI_TA_RIGHT:  xAdjust = xLineSize; break;
      default:            xAdjust = 0;
    }
    r.x0 = GUI_Context.DispPosX -= xAdjust;
    r.x1 = r.x0 + xLineSize - 1;    
    r.y0 = GUI_Context.DispPosY;
    r.y1 = r.y0 + FontSizeY - 1;    
    GUI__DispLine(s, LineNumChars, &r);
    GUI_Context.DispPosY = r.y0;
    s += GUI_UC__NumChars2NumBytes(s, LineNumChars);
    if ((*s == '\n') || (*s == '\r')) {
      switch (GUI_Context.TextAlign & GUI_TA_HORIZONTAL) { 
      case GUI_TA_CENTER:
      case GUI_TA_RIGHT:
        GUI_Context.DispPosX = xOrg;
        break;
      default:
        GUI_Context.DispPosX = GUI_Context.LBorder;
        break;
      }
      if (*s == '\n')
        GUI_Context.DispPosY += FontSizeY;
    } else {
      GUI_Context.DispPosX = r.x0 + xLineSize;
    }
    if (*s == 0)    /* end of string (last line) reached ? */
      break;
  }
  GUI_Context.DispPosY += yAdjust;
  GUI_Context.TextAlign &= ~GUI_TA_HORIZONTAL;
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
