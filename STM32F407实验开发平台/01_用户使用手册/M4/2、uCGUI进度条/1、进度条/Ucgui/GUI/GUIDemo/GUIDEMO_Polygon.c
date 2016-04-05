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
File        : GUIDEMO_Polygon.c
Purpose     : Several GUIDEMO routines
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"

#define COUNTOF(Obj) (sizeof(Obj)/sizeof(Obj[0]))

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const GUI_POINT _aArrow[] = {
  {  0,  30 },
  {-40,   0 },
  {-10,  10 },
  {-10, -50 },
  { 10, -50 },
  { 10,  10 },
  { 40,   0 }
};

static const GUI_POINT _aTriangle[] = {
	{  0,  0 }, 
  {-30, 30 },
  { 30, 30 },
};

#if GUI_SUPPORT_AA
static const GUI_POINT _aiCursor[] = {
  {  0,  -10 }, 
  { 50,    0 }, 
  {  0, -100 }, 
  {-50,    0 }
};
#endif

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _MagnifyPolygon
*/
#if ((LCD_XSIZE != 320) || (LCD_YSIZE != 240))
static void _MagnifyPolygon(GUI_POINT* pDest, const GUI_POINT* pSrc, int NumPoints, float Mag) {
  int j;
  for (j = 0; j < NumPoints; j++) {
    (pDest + j)->x = (pSrc + j)->x * Mag;
    (pDest + j)->y = (pSrc + j)->y * Mag;
  }
}
#endif

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIDEMO_DemoPolygon
*/
void GUIDEMO_DemoPolygon(void) {
  GUI_COLOR Color;
  int XMid  = (LCD_XSIZE >> 1);
  int YMid  = (LCD_YSIZE >> 1);
  GUIDEMO_ShowIntro("Arbitrary Polygons", 
                    "\nStandard and antialiased");
  GUI_SetColor(GUI_WHITE);
  #if GUIDEMO_LARGE
    GUI_SetFont(&GUI_FontComic18B_ASCII);
    GUI_DispStringAt("Arbitrary\nPolygons", 0, 0);
    YMid += 10;
  #endif
  #if ((LCD_XSIZE != 320) || (LCD_YSIZE != 240))
    {
      GUI_POINT aPolygon[8];
      float Factor;
      #if ((LCD_XSIZE / 320) < (LCD_YSIZE / 240))
        Factor = LCD_XSIZE / 320.f;
      #else
        Factor = LCD_YSIZE / 240.f;
      #endif
      #if !(GUIDEMO_LARGE)
        Factor *= 1.2f;
      #endif
      /* Draw arrows */
      _MagnifyPolygon(aPolygon, _aArrow, COUNTOF(_aArrow), Factor);
      GUI_FillPolygon(aPolygon, 7, XMid - (50 * Factor), YMid);
      GUI_FillPolygon(aPolygon, 7, XMid + (50 * Factor), YMid);
      /* Draw triangle */
      _MagnifyPolygon(aPolygon, _aTriangle, COUNTOF(_aTriangle), Factor);
      Color = GUIDEMO_SetColor(GUI_GREEN);
      if (Color != GUI_GREEN) {
        GUI_SetColor(GUI_YELLOW);
      }
      GUI_FillPolygon(aPolygon, 3, XMid, YMid + (10 * Factor));
      /* Draw cursor */
      #if GUI_SUPPORT_AA
        GUI_SetColor(GUI_WHITE);
        GUI_AA_EnableHiRes();
        _MagnifyPolygon(aPolygon, _aiCursor, COUNTOF(_aiCursor), Factor);
        GUI_AA_FillPolygon(aPolygon, 4, XMid * 3, (YMid - (10 * Factor)) * 3);
      #endif
    }
  #else
    GUI_FillPolygon(_aArrow, 7, XMid - 50, YMid);
    GUI_FillPolygon(_aArrow, 7, XMid + 50, YMid);
    /* Draw triangle */
    Color = GUIDEMO_SetColor(GUI_GREEN);
    if (Color != GUI_GREEN) {
      GUI_SetColor(GUI_YELLOW);
    }
    GUI_FillPolygon(_aTriangle, 3, XMid, YMid + 10);
    /* Draw cursor */
    #if GUI_SUPPORT_AA
      GUI_SetColor(GUI_WHITE);
      GUI_AA_EnableHiRes();
      GUI_AA_FillPolygon((GUI_POINT*)_aiCursor, 4, XMid * 3, (YMid - 10) * 3);
    #endif
  #endif
  GUIDEMO_Wait();
}
