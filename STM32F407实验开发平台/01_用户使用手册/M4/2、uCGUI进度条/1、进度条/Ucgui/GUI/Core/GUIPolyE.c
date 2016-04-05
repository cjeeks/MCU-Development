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
File        : GUIPolyE.c
Purpose     : Polygon enlarge
----------------------------------------------------------------------
*/

#include <math.h>
#include "GUI.h"
#include "GUIDebug.h"

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef struct {
  float x, y;
} tfPoint;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _fround
*/
static int _fround(float f) {
  if (f>0)
    return f+0.5;
  return f-0.5;
}

/*********************************************************************
*
*       _Normalize
*/
static void _Normalize(tfPoint* pfPoint) {
  float fx = pfPoint->x;
  float fy = pfPoint->y;
  float r = sqrt(fx*fx + fy*fy);
  if (r > 0) {
    pfPoint->x = fx/r;
    pfPoint->y = fy/r;
  }
}

/*********************************************************************
*
*       _ReverseLen
*/
static void _ReverseLen(tfPoint* pfPoint) {
  float fx = pfPoint->x;
  float fy = pfPoint->y;
  float r = sqrt(fx*fx/2 + fy*fy/2);
  if (r > 0) {
    pfPoint->x = fx/r/r;
    pfPoint->y = fy/r/r;
  }
}

/*********************************************************************
*
*       _GetVect
*/
static void _GetVect(tfPoint* pfPoint, const GUI_POINT* pSrc, int NumPoints, int Index) {
  int Off0 = (Index + NumPoints-1) % NumPoints;
  int Off1 = Index % NumPoints;
  pfPoint->x = pSrc[Off1].x - pSrc[Off0].x; 
  pfPoint->y = pSrc[Off1].y - pSrc[Off0].y; 
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_EnlargePolygon
*/
#if 0
void GUI_EnlargePolygon(GUI_POINT* pDest, const GUI_POINT* pSrc, int NumPoints, int Len) {
  int j;
  /* Calc destination points */
  for (j=0; j<NumPoints; j++) {
    int x, y;
    tfPoint aVect[2];
    /* Get the vectors */
    _GetVect(&aVect[0], pSrc, NumPoints, j);
    _GetVect(&aVect[1], pSrc, NumPoints, j+1);
    /* Normalize the vectors and add vectors */
    _Normalize(&aVect[0]);
    _Normalize(&aVect[1]);
    aVect[0].x += aVect[1].x;
    aVect[0].y += aVect[1].y;
    /* Resulting vector needs to be normalized again */
    _Normalize(&aVect[0]);
    x =  _fround(aVect[0].y * Len);
    y = -_fround(aVect[0].x * Len);
    /* Store destination */
    (pDest+j)->x = (pSrc+j)->x + x;
    (pDest+j)->y = (pSrc+j)->y + y;
  }
}

#else

void GUI_EnlargePolygon(GUI_POINT* pDest, const GUI_POINT* pSrc, int NumPoints, int Len) {
  int j;
  /* Calc destination points */
  for (j=0; j<NumPoints; j++) {
    int x, y;
    tfPoint aVect[2];
    /* Get the vectors */
    _GetVect(&aVect[0], pSrc, NumPoints, j);
    _GetVect(&aVect[1], pSrc, NumPoints, j+1);
    /* Normalize the vectors and add vectors */
    _Normalize(&aVect[0]);
    _Normalize(&aVect[1]);
    aVect[0].x += aVect[1].x;
    aVect[0].y += aVect[1].y;
    /* Resulting vector needs to be normalized again */
    _ReverseLen(&aVect[0]);
    x =  _fround(aVect[0].y * Len);
    y = -_fround(aVect[0].x * Len);
    /* Store destination */
    (pDest+j)->x = (pSrc+j)->x + x;
    (pDest+j)->y = (pSrc+j)->y + y;
  }
}
#endif

/*************************** End of file ****************************/
