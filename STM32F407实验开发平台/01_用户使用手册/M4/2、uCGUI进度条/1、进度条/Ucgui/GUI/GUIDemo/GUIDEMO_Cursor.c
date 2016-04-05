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
File        : GUIDEMO_Cursor.c
Purpose     : shows Cursor-API
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"

#if (GUI_SUPPORT_CURSOR & GUI_SUPPORT_TOUCH)

/*********************************************************************
*
*       defines
*
**********************************************************************
*/

#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

#if GUIDEMO_LARGE
  #define NUM_CURSORS   3
  #define XMAX  28
#else
  #define NUM_CURSORS   2
  #define XMAX  24
#endif

/*********************************************************************
*
*       types
*
**********************************************************************
*/

typedef struct {
  const GUI_CURSOR* pCursor;
  char              Size;
} CURSOR_INFO;

typedef struct {
  const CURSOR_INFO aCursor[NUM_CURSORS];
  const char*       pType;
} CURSORTYPE_INFO;

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

static const CURSORTYPE_INFO _CursorArrow = {
  &GUI_CursorArrowS, 'S',
  &GUI_CursorArrowM, 'M',
  #if (NUM_CURSORS == 3)
    &GUI_CursorArrowL, 'L',
    "arrow cursors"
  #else
    "arrow\ncursors"
  #endif
};

#if !(GUIDEMO_TINY)
  static const CURSORTYPE_INFO _CursorArrowI = {
    &GUI_CursorArrowSI, 'S',
    &GUI_CursorArrowMI, 'M',
    #if (NUM_CURSORS == 3)
      &GUI_CursorArrowLI, 'L',
      "inverted arrow cursors"
    #else
      "inverted\narrow cursors"
    #endif
  };
#endif

static const CURSORTYPE_INFO _CursorCross = {
  &GUI_CursorCrossS, 'S',
  &GUI_CursorCrossM, 'M',
  #if (NUM_CURSORS == 3)
    &GUI_CursorCrossL, 'L',
    "cross cursors"
  #else
    "cross\ncursors"
  #endif
};

#if !(GUIDEMO_TINY)
  static const CURSORTYPE_INFO _CursorCrossI = {
    &GUI_CursorCrossSI, 'S',
    &GUI_CursorCrossMI, 'M',
    #if (NUM_CURSORS == 3)
      &GUI_CursorCrossLI, 'L',
      "inverted cross cursors"
    #else
      "inverted\ncross cursors"
    #endif
  };
#endif

static const GUI_CURSOR* _aCursor[] = { 
  &GUI_CursorArrowM,
  #if !(GUIDEMO_TINY)
    &GUI_CursorArrowMI,
  #endif
  &GUI_CursorCrossM,
  #if !(GUIDEMO_TINY)
    &GUI_CursorCrossMI,
  #endif
};

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _ShowCursorType
*/
static void _ShowCursorType(const CURSORTYPE_INFO* pCursorType, int x0, int y0) {
  const GUI_CURSOR* pCursor;
  char Char;
  int i, x, y;
  int yMax = 0;
  int yHot = 0;
  /* Calculate height and width of biggest cursor */
  for (i = 0; i < NUM_CURSORS; i++) {
    pCursor = pCursorType->aCursor[i].pCursor;
    if (pCursor->pBitmap->YSize > yMax) {
      yMax = pCursor->pBitmap->YSize;
      yHot = pCursor->yHot;
    }
  }
  #if ((LCD_YSIZE >= 220) && (LCD_XSIZE >= 300))
    GUI_SetFont(&GUI_FontComic18B_ASCII);
  #else
    GUI_SetFont(&GUI_Font13B_ASCII);
  #endif
  #if (NUM_CURSORS != 3)
    GUI_SetLBorder(x0);
  #endif
  GUI_DispStringAt(pCursorType->pType, x0, y0);
  #if GUIDEMO_LARGE
    y0 += GUI_GetFontDistY() + 1;
    GUI_SetFont(&GUI_Font13B_ASCII);
  #else
    #if (LCD_YSIZE < 80)
      x0 += 50;
    #else
      y0 += GUI_GetFontDistY() * 2 + 1;
    #endif
    GUI_SetFont(&GUI_Font10_ASCII);
  #endif
  for (i = 0; i < NUM_CURSORS; i++) {
    pCursor = pCursorType->aCursor[i].pCursor;
    Char    = pCursorType->aCursor[i].Size;
    y = y0 + yHot - pCursor->yHot;
    x = ((pCursor->pBitmap->XSize - GUI_GetCharDistX(Char)) >> 1);
    GUI_DrawBitmap(pCursor->pBitmap, x0 + XMAX * i + 5,     y);
    GUI_DispCharAt(Char,             x0 + XMAX * i + 5 + x, y0 + yMax + 2);
  }
}

/*********************************************************************
*
*       _MoveCursor
*/
static void _MoveCursor(const GUI_CURSOR* Cursor){
  int x, y;
  int xMax = LCD_XSIZE >> 1;
  int yMax = LCD_YSIZE >> 1;
  #if !GUIDEMO_LARGE
    xMax *= 1.3;
    yMax *= 1.3;
  #endif
  GUI_CURSOR_Select(Cursor);  
  for(x = y = 0; ((x < xMax) && (y < yMax) && !GUIDEMO_CheckCancel()); x += 6, y += 6) {
    if ( x == xMax) {
      x = xMax;
    }
    if ( y == yMax) {
      y = yMax;
    }
    GUI_CURSOR_SetPosition(x, y);
    GUIDEMO_Delay(75);
  }
}

/*********************************************************************
*
*       _DispCursor
*/
static void _DispCursor(void) {
  #if !(GUIDEMO_LARGE)
    int x0 = 0;
  #endif
  int y0, dx, dy;
  GUI_CURSOR_Hide();
  GUI_SetTextMode(GUI_TM_TRANS);
  #if GUIDEMO_LARGE
    GUI_SetFont(&GUI_FontComic24B_ASCII);
    GUI_DispStringAt("Available\n  cursors:", 18, 12);
  #else
    #if GUIDEMO_TINY
      GUI_SetFont(&GUI_Font13B_ASCII);
    #else
      GUI_SetFont(&GUI_FontComic18B_ASCII);
    #endif
    GUI_DispStringHCenterAt("Available cursors:", LCD_XSIZE >> 1,  LCD_YSIZE >> 5);
  #endif
  /* Display the cursors */
  #if GUIDEMO_LARGE
    y0 = 68;
    dx = LCD_XSIZE / 2.5;
    #if (LCD_YSIZE > 240)
      dy = LCD_YSIZE / 3.2;
    #else
      dy = 75;
    #endif
    #if ((LCD_YSIZE < 220) || (LCD_XSIZE < 300))
      y0 -=  3;
      dy -= 12;
    #endif
    _ShowCursorType(&_CursorArrow,    0, y0);
    _ShowCursorType(&_CursorCross,    0, y0 + dy);
    _ShowCursorType(&_CursorArrowI,  dx, y0);
    _ShowCursorType(&_CursorCrossI,  dx, y0 + dy);
  #else
    #if GUIDEMO_TINY
      y0 = 20;
    #else
      y0 = 30;
    #endif
    #if ((LCD_XSIZE < 160) && ((LCD_YSIZE >= 160) || (LCD_YSIZE < 90)))
      x0 = 10;
    #endif
    dx = LCD_XSIZE / 2.2;
    dy = LCD_YSIZE / 2.6;
    _ShowCursorType(&_CursorArrow,    x0, y0);
    #if (LCD_YSIZE >= 160)
      _ShowCursorType(&_CursorCross,  x0, y0 + dy);
    #elif (LCD_YSIZE < 90)
      GUIDEMO_Delay(2000);
      GUI_ClearRect(0, 20, LCD_XSIZE - 1, LCD_YSIZE - 1);
      _ShowCursorType(&_CursorCross,  x0, y0);
    #else
      _ShowCursorType(&_CursorCross,  dx, y0);
    #endif
    #if ((LCD_YSIZE >= 160) && (LCD_XSIZE >= 160))
      _ShowCursorType(&_CursorArrowI, dx, y0);
      _ShowCursorType(&_CursorCrossI, dx, y0 + dy);
    #endif
  #endif
}

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIDEMO_Cursor
*/
void GUIDEMO_Cursor(void) {
  int i = 0;
  GUIDEMO_ShowIntro("Cursor",
                    "\nemWin supports"
                    "\nsoftware cursor");
  GUIDEMO_SetBkColor(GUI_BLUE);
  GUI_Clear();
  _DispCursor();
  GUIDEMO_Delay(1500);
  GUIDEMO_NotifyStartNext();
  GUI_CURSOR_Show();
  for ( i = 0;(i < countof(_aCursor) && !GUIDEMO_CheckCancel()); i++) {
      _MoveCursor(_aCursor[i]);
  }
  GUI_CURSOR_SetPosition(0,0);
  GUI_CURSOR_Select(&GUI_CursorArrowM);  
}

#else

void GUIDEMO_Cursor(void) {}

#endif
