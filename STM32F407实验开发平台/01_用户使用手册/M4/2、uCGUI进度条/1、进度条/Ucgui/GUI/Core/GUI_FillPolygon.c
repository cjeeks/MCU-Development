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
File        : GUI_FillPolygon.C
Purpose     : Fill polygon routine
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       defines, Configs
*
**********************************************************************
*/

#define GUI_FP_MAXCOUNT 12

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

static int GL_FP_Cnt;
static I16 _aX[GUI_FP_MAXCOUNT];

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawHLine
*/
static void _DrawHLine(int x0, int y, int x1) {
  if (x0 < x1) {
    LCD_HL_DrawHLine(x0, y, x1);
  } else {
    LCD_HL_DrawHLine(x1, y, x0);
  }
}

/*********************************************************************
*
*       _CheckYInterSect
*
*  This function returns the x-coordinate of the intersection
*  of the given line at the given y-coordinate.
*  If there is no intersection, GUI_XMAX is returned.
*  This routine does not work for horizontal lines, as there
*  would be more than a single point as intersection. This situation
*  needs to be checked prior to calling the routine.
*  Returns:
*    0 if no intersection
*    1 if we have an intersection
*/
static int _CheckYInterSect(int y, int* px, const GUI_POINT*paPoint0, const GUI_POINT*paPoint1) {
  int x0, y0, x1, y1;
  if (paPoint0->y <= (paPoint1)->y) {
    y0 = paPoint0->y;
    if (y0 > y)      /* Check if there is an intersection ... (early out) */
      return 0;
    y1 = paPoint1->y;
    if (y1 < y)      /* Check if there is an intersection ... (early out) */
      return 0;
    x0 = paPoint0->x;
    x1 = paPoint1->x;
  } else {
    y0 = paPoint1->y;
    if (y0 > y)      /* Check if there is an intersection ... (early out) */
      return 0;
    y1 = paPoint0->y;
    if (y1 < y)      /* Check if there is an intersection ... (early out) */
      return 0;
    x0 = paPoint1->x;
    x1 = paPoint0->x;
  }
/* Calculate intersection */
  {
    I32 Mul = (I32)(x1 - x0) * (I32)(y - y0);
    if (Mul > 0) {
      Mul += (y1 - y0) >> 1;	          /* for proper rounding */
    } else {
      Mul -= ((y1 - y0) >> 1) - 1;	    /* for proper rounding */
    }
    x0 += Mul / (y1 - y0);
  }
  *px = x0;
  return 1;
} 

/*********************************************************************
*
*       _Add
*
*  This function adds a point into the sorted array
*/
static void _Add(int x) {
  if (GL_FP_Cnt < GUI_FP_MAXCOUNT) {
    int i;
    /* Move all entries to the right (bigger x-value) */
    for (i=GL_FP_Cnt; i ; i--) {
      if (_aX[i-1] < x)
        break;
      _aX[i] = _aX[i-1];
    }
    /* Insert new entry */
    _aX[i]    = x;
    GL_FP_Cnt++;
  }
}

/*********************************************************************
*
*       _Init
*
*  This function initialise the sorted array
*/
static void _Init(void) {
  GL_FP_Cnt = 0;
}

/*********************************************************************
*
*       _Flush
*
*  This function draw lines between points in the array
*/
static void _Flush(int x0, int y) {
  int i, x = 0;
  char On=0;
  for (i=0; i<GL_FP_Cnt; i++) {
    int xNew = _aX[i];
    if (On) {
      LCD_HL_DrawHLine(x0 + x, y, x0 + xNew);
    }
    On ^= 1;
    x = xNew;
  }
}

/*********************************************************************
*
*       _AddPoint
*
*  This function decides either if there a V-point or a
*  X-point. An X-point is added to the array, a V-point
*  is drawn.
*/
static void _AddPoint(int x, int y, int y0, int y1, int xOff, int yOff) {
  if ((y0 ^ y1) >= 0) {
    x += xOff;
    LCD_HL_DrawHLine(x, y + yOff, x);    /* V-point, not crossing the polygon */
  } else {
    _Add(x);
  }
}

/*********************************************************************
*
*       _GetPrevPointDiffy
*
*  Find previous point which is not on the same height
*/
static int _GetPrevPointDiffy(const GUI_POINT* paPoint, int i,
                              const int NumPoints, const int y0) {
  int j, y1;
  for (j = 0; j < (NumPoints - 1) ; j++) {
    i = (i != 0) ? i - 1 : NumPoints - 1;
    y1 = (paPoint + i)->y;
    if (y1 != y0) {
      return y1;
    }
  }
  return y0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GL_FillPolygon
*
*  This function calculates the polygon
*/
void GL_FillPolygon  (const GUI_POINT*paPoint, int NumPoints, int xOff, int yOff) {
  int i, y;
  int yMin = GUI_YMAX;
  int yMax = GUI_YMIN;
/* First step : find uppermost and lowermost coordinates */
  for (i=0; i<NumPoints; i++) {
    y = (paPoint + i)->y;
    if (y < yMin)
      yMin = y;
    if (y > yMax)
      yMax = y;
  }
/* Use Clipping rect to reduce calculation (if possible) */
  if (GUI_Context.pClipRect_HL) {
    if (yMax > (GUI_Context.pClipRect_HL->y1 - yOff))
      yMax = (GUI_Context.pClipRect_HL->y1 - yOff);
    if (yMin < (GUI_Context.pClipRect_HL->y0 - yOff))
      yMin = (GUI_Context.pClipRect_HL->y0 - yOff);
  }
/* Second step: Calculate and draw horizontal lines */
  for (y=yMin; y<=yMax; y++) {
    _Init();
    /* find next intersection and count lines*/
    for (i=0; i<NumPoints; i++) {
      int i1 = (i < (NumPoints - 1)) ? i + 1 : 0;
      int y0 = (paPoint + i )->y;
      int y1 = (paPoint + i1)->y;
      /* Check if starting point is on line */
      if (y0 == y) {
        if (y1 == y) {  /* Add the entire line */
          _DrawHLine((paPoint + i )->x + xOff , y + yOff, (paPoint + i1)->x + xOff);
        } else {        /* Add only one point */
          int yPrev = _GetPrevPointDiffy(paPoint, i, NumPoints, y);
          if (yPrev != y) {
            _AddPoint((paPoint + i)->x, y, yPrev - y, y1 - y, xOff, yOff);
          } 
        }
      } else if (y1 != y) {  /* Ignore if end-point is on the line */
        if (((y1 >= y) && (y0 <= y)) || ((y0 >= y) && (y1 <= y))) {
          int xIntersect;
          if (_CheckYInterSect(y, &xIntersect, paPoint + i, paPoint + i1)) {
            _Add(xIntersect);
          }
        }
      }
    }
    _Flush(xOff, y + yOff);
  }  
}

/*********************************************************************
*
*       GUI_FillPolygon
*/
void GUI_FillPolygon(const GUI_POINT* pPoints, int NumPoints, int x0, int y0) {
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0, y0);
    WM_ITERATE_START(NULL); {
  #endif
  GL_FillPolygon (pPoints, NumPoints, x0, y0);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
