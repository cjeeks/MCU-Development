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
File        : GUIARCFloat.C
Purpose     : Draw Arc routines based on floating point
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
2.00.00 000325 RS     First release of the new algorithm
----------------------------------------------------------------------
Known problems or limitations with current version
----------------------------------------------------------------------
None.
----------------------------------------------------------------------
Open issues
----------------------------------------------------------------------
None
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <math.h>
#include "GUI_Protected.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _CalcX
*/
static void _CalcX(int*px, int y, U32 r2) {
  int x =*px;
  U32 y2 = (U32)y*(U32)y;
  U32 r2y2 = r2-y2;
  U32 x2;
  if (y2>=r2) {
    *px=0;
		return;
	}
  /* x2 = r2-y2 */
  do {
    x++;
    x2 =(U32)x*(U32)x;
	} while (x2 < r2y2);
	*px = x-1;
}

/*********************************************************************
*
*       _CalcInterSectLin
*/
static float _CalcInterSectLin(float y, float y0, float y1, float x0, float x1) {
  if (y1==y0) {
	  return y0;
	} else {
    float Slope = (x1-x0)/(y1-y0);
   return (y-y0)*Slope+x0;
	}
}

/*********************************************************************
*
*       _DrawArc
*/
static void _DrawArc(int x0, int y0, int rx, int ry, int Angle0, int Angle1, int xMul, int yMul) {
  float afx[4];
  float afy[4];
	float ri = rx-(GUI_Context.PenSize+1.5)/2;
	float ro = rx+(GUI_Context.PenSize+1.5)/2;
  float fAngle0 = Angle0*3.1415926/180;
  float fAngle1 = Angle1*3.1415926/180;
  float sin0 = sin(fAngle0); 
  float sin1 = sin(fAngle1); 
  float cos0 = cos(fAngle0); 
  float cos1 = cos(fAngle1); 
  U32   ri2 = ri*ri;
  U32   ro2 = ro*ro;
	int y, yMax, yMin;
	afy[0] = ri*sin0;
	afy[1] = ro*sin0;
	afy[2] = ri*sin1;
	afy[3] = ro*sin1;
	afx[0] = ri*cos0;
	afx[1] = ro*cos0;
	afx[2] = ri*cos1;
	afx[3] = ro*cos1;
	yMin = ceil(afy[0]);
  yMax = floor(afy[3]);
  /* Use Clipping rect to reduce calculation (if possible) */
  if (GUI_Context.pClipRect_HL) {
    if (yMul ==1) {
      if (yMax > (GUI_Context.pClipRect_HL->y1 -y0))
        yMax = (GUI_Context.pClipRect_HL->y1 -y0);
      if (yMin < (GUI_Context.pClipRect_HL->y0 -y0))
        yMin = (GUI_Context.pClipRect_HL->y0 -y0);
    }
    if (yMul == -1) {
      if (yMin > (GUI_Context.pClipRect_HL->y1 -y0))
        yMin = (GUI_Context.pClipRect_HL->y1 -y0);
      if (yMax < (GUI_Context.pClipRect_HL->y0 -y0))
        yMax = (GUI_Context.pClipRect_HL->y0 -y0);
    }
  }
  /* Start drawing lines ... */
  {
  int xMinDisp, xMaxDisp, xMin=0,xMax=0;
    for (y=yMax; y>=yMin; y--) {
      _CalcX(&xMin, y, ri2);
      _CalcX(&xMax, y, ro2);
      if ((float)y< afy[1]) {
        xMaxDisp = _CalcInterSectLin(y,afy[0], afy[1], afx[0], afx[1]);
			} else {
        xMaxDisp = xMax;			
			}
      if ((float)y > afy[2]) {
        xMinDisp = _CalcInterSectLin(y,afy[2], afy[3], afx[2], afx[3]);
			} else {
        xMinDisp = xMin;			
			}
      if (xMul>0)
        LCD_HL_DrawHLine(xMinDisp+x0, yMul*y+y0, xMaxDisp+x0);
      else
        LCD_HL_DrawHLine(-xMaxDisp+x0, yMul*y+y0, -xMinDisp+x0);
    }
	}
#if 0  /* Test code */
{
  int i;
  GUI_SetColor( GUI_WHITE ); 
	for (i=0; i<4; i++)
    LCD_HL_DrawPixel(afx[i]+x0, afy[i]+y0);
}
#endif
  GUI_USE_PARA(ry);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GL_DrawArc
*/
void GL_DrawArc(int x0, int y0, int rx, int ry, int a0, int a1) {
  int aEnd;
  a0+=360;
	a1+=360;
	while (a0>=360) {
    a0 -= 360;
    a1 -= 360;
	}
/* Do first quadrant 0-90 degree */
DoFirst:
  if (a1<=0)
	  return;
	if (a0<90) {
    if (a0<0)
		  a0=0;
    aEnd = (a1<90) ? a1 : 90;
    _DrawArc(x0,y0,rx,ry,a0,aEnd, 1, -1);
	}
  a1-=90;
	a0-=90;
/* Do second quadrant 90-180 degree */
  if (a1<=0)
	  return;
	if (a0<90) {
    if (a0<0)
		  a0=0;
    aEnd = (a1<90) ? a1 : 90;
    _DrawArc(x0,y0,rx,ry,90-aEnd, 90-a0,-1,-1);
	}
  a1-=90;
	a0-=90;
/* Do third quadrant 180-270 degree */
  if (a1<=0)
	  return;
	if (a0<90) {
    if (a0<0)
		  a0=0;
    aEnd = (a1<90) ? a1 : 90;
    _DrawArc(x0,y0,rx,ry,a0,aEnd, -1, 1);
	}
  a1-=90;
	a0-=90;
/* Do last quadrant 270-360 degree */
  if (a1<=0)
	  return;
	if (a0<90) {
    if (a0<0)
		  a0=0;
    aEnd = (a1<90) ? a1 : 90;
    _DrawArc(x0,y0,rx,ry,90-aEnd, 90-a0,1,1);
	}
  a1-=90;
	a0-=90;
goto DoFirst;
}

/*********************************************************************
*
*       GUI_DrawArc
*/
void GUI_DrawArc(int x0, int y0, int rx, int ry, int a0, int a1) {
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    WM_ITERATE_START(NULL) {
  #endif
  GL_DrawArc( x0, y0, rx, ry, a0, a1);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
