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
File        : GUIDEMO_Navi.c
Purpose     : Navigation system demo
----------------------------------------------------------------------
*/

#include <math.h>

#include "GUI.h"
#include "GUIDEMO.h"

#if GUI_WINSUPPORT & GUI_SUPPORT_MEMDEV

#include "WM.h"
#include "FRAMEWIN.h"

#include "Map.h"

/*********************************************************************
*
*       defines
*
**********************************************************************
*/

#if GUIDEMO_TINY
  #define BORDER 0
#else
  #define BORDER 8
#endif

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

static int _MapX     = 0;
static int _MapY     = 0;
static int _MapHereX = 90;
static int _MapHereY = 15;

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbNaviWindow
*/
static void _cbNaviWindow(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
    GUI_SetTextMode(GUI_TM_TRANS);
    GUI_SetFont(&GUI_FontComic18B_ASCII);
    GUI_SetColor(0x0050FF);
    GUI_DrawBitmap(&bmMap, -_MapX, -_MapY);
    GUI_DrawCircle(_MapHereX - _MapX, _MapHereY - _MapY, 4);
    GUI_DrawCircle(_MapHereX - _MapX, _MapHereY - _MapY, 5);
    GUI_DispStringAt("You are here", _MapHereX - _MapX - 45, _MapHereY - _MapY - 22);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       _NavigationDriveTo
*/
static void _NavigationDriveTo(WM_HWIN hWin, int x1, int y1) {
  GUI_RECT Rect;
  int   x0  = _MapHereX;
  int   y0  = _MapHereY;
  float dx  = x1 - x0;
  float dy  = y1 - y0;
  float Len = sqrt((dx * dx) + (dy * dy));
  float sx  = dx / Len;
  float sy  = dy / Len;
  int   i, tRef;
  WM_GetClientRectEx(hWin, &Rect);
  for (i = 1; (i <= Len) && !GUIDEMO_CheckCancel(); i += 2) {
    tRef = GUI_GetTime();
    _MapHereX = x0 + (i * sx);
    _MapHereY = y0 + (i * sy);
    _MapX = _MapHereX - (Rect.x1 >> 1);
    _MapY = _MapHereY - (Rect.y1 >> 1);
    if (_MapX < 0) {
      _MapX = 0;
    } else if ((_MapX + Rect.x1) >= bmMap.XSize) {
      _MapX = bmMap.XSize - Rect.x1 - 1;
    }
    if (_MapY < 0) {
      _MapY = 0;
    } else if ((_MapY + Rect.y1) >= bmMap.YSize) {
      _MapY = bmMap.YSize - Rect.y1 - 1;
    }
    WM_InvalidateWindow(hWin);
    do {
      GUI_Exec();
    } while (((GUI_GetTime() - tRef) < 100) && !GUIDEMO_CheckCancel());
  }
  _MapHereX = x1;
  _MapHereY = y1;
  WM_InvalidateWindow(hWin);
}

/*********************************************************************
*
*       _ShowMovingMap
*/
static void _ShowMovingMap(void) {
  WM_HWIN hWin;
  WM_HWIN hClient;
  int i, x, y, w, h;
  int xSize = LCD_GetXSize();
  int ySize = LCD_GetYSize();
  const GUI_POINT aRouteToSegger[] = {
    { 90,  15}, {131,  54}, {141,  62},
    {166,  46}, {180,  40}, {204, 113},
    {213, 156}, {217, 172}, {206, 173},
    {205, 165}
  };
  #if GUIDEMO_LARGE
    y = 70;
  #else
    y = BORDER;
  #endif
  x = BORDER;
  w = xSize - x - BORDER;
  h = ySize - y - BORDER;
  if (w > bmMap.XSize) {
    w = bmMap.XSize;
  }
  if (h > bmMap.YSize) {
    h = bmMap.YSize;
  }
  /* Initialize starting point */
  _MapHereX = aRouteToSegger[0].x;
  _MapHereY = aRouteToSegger[0].y;
  /* Create framewin */
  hWin  = FRAMEWIN_CreateEx(x, y, w, h, WM_HBKWIN, WM_CF_SHOW | WM_CF_MEMDEV, 0, 0, "Map to Segger (Hilden)", _cbNaviWindow);
  FRAMEWIN_SetActive(hWin, 0);
  hClient = WM_GetClientWindow(hWin);
  WM_SetCallback(hClient, &_cbNaviWindow);
  /* Move over map */
  for (i = 1; (i < 10) && !GUIDEMO_CheckCancel(); i++) {
    _NavigationDriveTo(hClient, aRouteToSegger[i].x, aRouteToSegger[i].y);
  }
  GUIDEMO_Delay(1000);
  /* Delete framewin */
  WM_DeleteWindow(hWin);
}

#else

#define _ShowMovingMap()

#endif

/*********************************************************************
*
*       GUIDEMO_Navigation
*
**********************************************************************
*/

void GUIDEMO_Navigation(void) {
  GUIDEMO_ShowIntro("Navigation system",
                    "\nSamples used in"
                    "\nNavigation systems");
  _ShowMovingMap();
}
