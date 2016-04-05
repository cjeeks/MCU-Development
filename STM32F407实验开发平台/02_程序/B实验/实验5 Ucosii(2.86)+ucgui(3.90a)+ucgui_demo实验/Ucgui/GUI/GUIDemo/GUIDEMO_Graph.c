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
File        : GUIDEMO_Graph.c
Purpose     : Several GUIDEMO routines
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "LCD_ConfDefaults.h"      /* valid LCD configuration */
#include <math.h>
#include <stdlib.h>
#include "GUIDEMO.h"

#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       Structure containing information for drawing routine
*
**********************************************************************
*/

typedef struct {
  I16 * aY;
} PARAM;

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#if GUIDEMO_LARGE
  #define YSIZE   (LCD_YSIZE - 100)
#else
  #define YSIZE   (LCD_YSIZE - 30)
#endif

#define DEG2RAD (3.1415926f / 180)

#if LCD_BITSPERPIXEL == 1
  #define COLOR_GRAPH0 GUI_WHITE
  #define COLOR_GRAPH1 GUI_WHITE
#else
  #define COLOR_GRAPH0 GUI_GREEN
  #define COLOR_GRAPH1 GUI_YELLOW
#endif

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

static int _YSize;

/*********************************************************************
*
*       Draws the graph
*
**********************************************************************
*/

static void _Draw(void * p) {
  int i;
  PARAM * pParam = (PARAM *)p;
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetColor(GUI_DARKGRAY);
  GUI_ClearRect(19, (LCD_YSIZE - 20) - _YSize, (LCD_XSIZE - 2), (LCD_YSIZE - 21));
  for (i = 0; i < (_YSize / 2); i += 20) {
    GUI_DrawHLine((LCD_YSIZE - 20) - (_YSize / 2) + i, 19, (LCD_XSIZE - 2));
    if (i) {
      GUI_DrawHLine((LCD_YSIZE - 20) - (_YSize / 2) - i, 19, (LCD_XSIZE - 2));
    }
  }
  for (i = 40; i < (LCD_XSIZE - 20); i += 40) {
    GUI_DrawVLine(18 + i, (LCD_YSIZE - 20) - _YSize, (LCD_YSIZE - 21));
  }
  GUIDEMO_SetColor(COLOR_GRAPH0);
  GUI_DrawGraph(pParam->aY, (LCD_XSIZE - 20), 19, (LCD_YSIZE - 20) - _YSize);
}

static void _Draw2(void * p) {
  PARAM * pParam = (PARAM *)p;
  _Draw(p);
  GUI_SetColor(COLOR_GRAPH1);
  GUI_DrawGraph(pParam->aY+15, (LCD_XSIZE - 20), 19, (LCD_YSIZE - 20) - _YSize);
}

/*********************************************************************
*
*       Labels the x & y-axis
*
**********************************************************************
*/

static void _Label(void) {
  int x, y;
  GUI_SetPenSize(1);
  GUI_ClearRect(0, (LCD_YSIZE - 21) - _YSize, (LCD_XSIZE - 1), (LCD_YSIZE - 1));
  GUI_DrawRect(18, (LCD_YSIZE - 21) - _YSize, (LCD_XSIZE - 1), (LCD_YSIZE - 20));
  GUI_SetFont(&GUI_Font6x8);
  for (x = 0; x < (LCD_XSIZE - 20); x += 40) {
    int xPos = x + 18;
    GUI_DrawVLine(xPos, (LCD_YSIZE - 20), (LCD_YSIZE - 14));
    GUI_DispDecAt(x / 40, xPos - 2, (LCD_YSIZE - 9), 1);
  }
  for (y = 0; y < _YSize / 2; y += 20) {
    int yPos = (LCD_YSIZE - 20) - _YSize / 2 + y;
    GUI_DrawHLine(yPos, 13, 18);
    if (y) {
      GUI_GotoXY(1, yPos - 4);
      GUI_DispSDec(-y / 20, 2);
      yPos = (LCD_YSIZE - 20) - _YSize / 2 - y;
      GUI_DrawHLine(yPos, 13, 18);
      GUI_GotoXY(1, yPos - 4);
      GUI_DispSDec(y / 20, 2);
    } else {
      GUI_DispCharAt('0', 7, yPos - 4);
    }
  }
}

/*********************************************************************
*
*       Draws random data
*
**********************************************************************
*/

static void _GetRandomData(I16 * paY, int Time, int n) {
  int aDiff, i;
  if (Time > 5000)
    Time -= 5000;
  if (Time > 2500)
    Time = 5000 - Time;
  Time /= 200;
  aDiff = Time * Time + 1;
  for (i = 0; i < n; i++) {
    if (!i) {
      paY[i] = rand() % _YSize;
    } else {
      int Rnd0, Rnd1, yD;
      I16 yNew;
      Rnd0 = rand();
      yD = aDiff - (Rnd0 % aDiff);
      Rnd1 = rand();
      if (Rnd1 > Rnd0) {
        yNew = paY[i-1] + yD;
      } else {
        yNew = paY[i-1] - yD;
      }
      if (yNew > _YSize) {
        yNew -= yD;
      } else { if (yNew < 0)
        yNew += yD;
      }
      paY[i] = yNew;
    }
  }
}

static void _ShowText(const char * sText) {
  GUIDEMO_SetColor(GUI_WHITE);
  GUIDEMO_SetBkColor(GUI_RED);
  #if GUIDEMO_LARGE
    GUI_ClearRect(0, 0, LCD_XSIZE, 60);
    GUI_SetFont(&GUI_FontComic18B_ASCII);
    GUI_DispStringAt(sText, 10, 20);
  #else
    sText = sText;  /* Avoid warning */
  #endif
}

static void _LabelMS(void) {
  GUI_SetFont(&GUI_Font6x8);
  #if GUIDEMO_LARGE
    GUI_DispStringAt("msec/graph:", 10, 50);
  #endif
}

static void _DisplayTime(int tDiff) {
  #if GUIDEMO_LARGE
    GUI_GotoXY(80, 50);
    GUIDEMO_SetColor(GUI_WHITE);
    GUIDEMO_SetBkColor(GUI_RED);
    GUI_DispDecSpace(tDiff, 3);
  #else
    tDiff = tDiff; /* Avoid warning */
  #endif
}

static void _DemoRandomGraph(void) {
  PARAM Param;
  int tDiff, t0;
  int Cnt = 0;
  GUI_HMEM hMem;
  GUI_RECT Rect;
  Rect.x0 = 19;
  Rect.y0 = (LCD_YSIZE - 20) - _YSize;
  Rect.x1 = LCD_XSIZE - 2;
  Rect.y1 = LCD_YSIZE - 21;
  hMem = GUI_ALLOC_AllocZero((LCD_XSIZE - 20) * sizeof(I16));
  _ShowText("Random graph");
  GUI_LOCK();
  Param.aY = (I16*)GUI_ALLOC_h2p(hMem);
  GUI_UNLOCK();    /* Note: unlocking is permitted only if no further allocation is done so hMem stays valid */
  /*
  GUI_SetFont(&GUI_Font6x8);
  GUI_DispStringAt("msec/graph:", 10, 50);
  */
  _LabelMS();
  t0 = GUI_GetTime();
  while(((tDiff = (GUI_GetTime() - t0)) < 10000) && !GUIDEMO_CheckCancel()) {
    U32 t1, tDiff2;
    _GetRandomData(Param.aY, tDiff, (LCD_XSIZE - 20));
    t1 = GUI_GetTime();
    GUI_MEMDEV_Draw(&Rect, _Draw, &Param, 0, GUI_MEMDEV_NOTRANS);
    tDiff2 = GUI_GetTime() - t1;
    if (tDiff2 < 100) {
      GUI_Delay(100 - tDiff2);
    }
    if(!((++Cnt)%10)) {
      _DisplayTime(tDiff2);
      /*
      GUI_GotoXY(80, 50);
      GUI_SetColor(GUI_WHITE);
      GUI_SetBkColor(GUI_RED);
      GUI_DispDecSpace(tDiff2, 3);
      */
    }
  }
  GUI_ALLOC_Free(hMem);
}

/*********************************************************************
*
*       Draws a sine wave
*
**********************************************************************
*/

static void _GetSineData(I16 * paY, int n) {
  int i;
  for (i = 0; i < n; i++) {
    float s = sin(i * DEG2RAD * 4);
    paY[i] = s * _YSize / 2 + _YSize / 2;
  }
}

static void _DemoSineWave(void) {
  PARAM Param;
  I16 * pStart;
  int t0, Cnt = 0;
  GUI_HMEM hMem;
  GUI_RECT Rect;
  Rect.x0 = 19;
  Rect.y0 = (LCD_YSIZE - 20) - _YSize;
  Rect.x1 = LCD_XSIZE - 2;
  Rect.y1 = LCD_YSIZE - 21;
  hMem = GUI_ALLOC_AllocZero((LCD_XSIZE + 90) * sizeof(I16));
  _ShowText("Sine wave");
  GUI_LOCK();
  pStart = (I16*)GUI_ALLOC_h2p(hMem);
  GUI_UNLOCK();    /* Note: unlocking is permitted only if no further allocation is done so hMem stays valid */
  _GetSineData(pStart, LCD_XSIZE + 90);
  /*
  GUI_SetFont(&GUI_Font6x8);
  GUI_DispStringAt("msec/graph:", 10, 50);
  */
  _LabelMS();
  t0 = GUI_GetTime();
  while(((GUI_GetTime() - t0) < 10000) && !GUIDEMO_CheckCancel()) {
    U32 t1, tDiff2;
    if (Cnt % 90) {
      Param.aY++;
    } else {
      Param.aY = pStart;
    }
    t1 = GUI_GetTime();
    GUI_MEMDEV_Draw(&Rect, _Draw2, &Param, 0, GUI_MEMDEV_NOTRANS);
    tDiff2 = GUI_GetTime() - t1;
    if (tDiff2 < 100) {
      GUI_Delay(100 - tDiff2);
    }
    if(!((++Cnt) % 10)) {
      _DisplayTime(tDiff2);
      /*
      GUI_GotoXY(80, 50);
      GUI_SetColor(GUI_WHITE);
      GUI_SetBkColor(GUI_RED);
      GUI_DispDecSpace(tDiff2, 3);
      */
    }
  }
  GUI_ALLOC_Free(hMem);
}

/*********************************************************************
*
*       Adds several waves
*
**********************************************************************
*/

static void _DrawOrData(GUI_COLOR Color, I16 * paY) {
  GUIDEMO_SetColor(Color);
  GUI_DrawGraph(paY, (LCD_XSIZE - 20), 19, (LCD_YSIZE - 20) - _YSize);
}

static void _DemoOrData(void) {
  int i;
  PARAM Param;
  GUI_RECT Rect;
  GUI_HMEM hMem;
  Rect.x0  = 19;
  Rect.y0  = (LCD_YSIZE - 20) - _YSize;
  Rect.x1  = LCD_XSIZE - 2;
  Rect.y1  = LCD_YSIZE - 21;
  hMem     = GUI_ALLOC_AllocZero((LCD_XSIZE + 90) * sizeof(I16));
  _ShowText("Several waves...");
  GUI_LOCK();
  Param.aY = (I16*)GUI_ALLOC_h2p(hMem);
  GUI_UNLOCK();
  _GetSineData(Param.aY, LCD_XSIZE + 90);
  GUI_MEMDEV_Draw(&Rect, _Draw, &Param, 0, GUI_MEMDEV_NOTRANS);
  for (i = 0; (i < 90) && !GUIDEMO_CheckCancel(); i++) {
    _DrawOrData(GUI_GREEN, ++Param.aY);
    GUI_Delay(10);
  }
  GUI_ALLOC_Free(hMem);
}

/*********************************************************************
*
*       GUIDEMO_Graph
*
**********************************************************************
*/

void GUIDEMO_Graph(void) {
  #if GUIDEMO_LARGE
    _YSize = (LCD_YSIZE - 100);
  #else
    _YSize = (LCD_YSIZE -  30);
  #endif
  GUIDEMO_ShowIntro("Drawing a graph",
                    "\nOptimized drawing routine"
                    "\nfor drawing graph data");
  GUI_Clear();
  _Label();
  _DemoRandomGraph();
  GUIDEMO_NotifyStartNext();
  _DemoSineWave();
  GUIDEMO_NotifyStartNext();
  _DemoOrData();
}

#elif defined(NC30) || defined(NC308)

void GUIDEMO_Graph(void) {}

#endif
