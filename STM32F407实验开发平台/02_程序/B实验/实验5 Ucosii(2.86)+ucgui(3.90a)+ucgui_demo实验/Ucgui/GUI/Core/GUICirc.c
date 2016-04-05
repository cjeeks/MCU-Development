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
File        : GUICirc.C
Purpose     : Circle and ellipse drawing functions
----------------------------------------------------------------------
Version-Date---Author-Explanation
----------------------------------------------------------------------
1.00.02 011115 JE     a) GL_FillEllipse, GL_FillCircle, GL_DrawCircle changed
1.00.01 011113 JE     a) GL_DrawEllipse changed
1.00.00 991206 RS     First release
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
#include "GUI_Private.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       Draw8Point
*/
static void Draw8Point(int x0,int y0, int xoff, int yoff) {
  LCD_HL_DrawPixel(x0+xoff,y0+yoff);
  LCD_HL_DrawPixel(x0-xoff,y0+yoff);
  LCD_HL_DrawPixel(x0+yoff,y0+xoff);
  LCD_HL_DrawPixel(x0+yoff,y0-xoff);
  if (yoff) {
    LCD_HL_DrawPixel(x0+xoff,y0-yoff);
    LCD_HL_DrawPixel(x0-xoff,y0-yoff);
    LCD_HL_DrawPixel(x0-yoff,y0+xoff);
    LCD_HL_DrawPixel(x0-yoff,y0-xoff);
  }
}

/*********************************************************************
*
*       Public code, circle
*
**********************************************************************
*/
/*********************************************************************
*
*       GL_DrawCircle
*/
void GL_DrawCircle(int x0, int y0, int r) {
  I32 i;
  int imax = ((I32)((I32)r*707))/1000+1;
  I32 sqmax = (I32)r*(I32)r+(I32)r/2;
  I32 y=r;
  Draw8Point(x0,y0,r,0);
  for (i=1; i<= imax; i++) {
    if ((i*i+y*y) >sqmax) {
      Draw8Point(x0,y0,i,y);
      y--;
    }
    Draw8Point(x0,y0,i,y);
  }
}

/*********************************************************************
*
*       GUI_DrawCircle
*/
void GUI_DrawCircle(int x0, int y0, int r) {
  #if (GUI_WINSUPPORT)
    GUI_RECT Rect;
  #endif
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    Rect.x0 = x0-r;
    Rect.x1 = x0+r;
    Rect.y0 = y0-r;
    Rect.y1 = y0+r;
    WM_ITERATE_START(&Rect); {
  #endif
    GL_DrawCircle( x0, y0, r);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GL_FillCircle
*/
void GL_FillCircle(int x0, int y0, int r) {
  I32 i;
  int imax = ((I32)((I32)r*707))/1000+1;
  I32 sqmax = (I32)r*(I32)r+(I32)r/2;
  I32 x=r;
  LCD_HL_DrawHLine(x0-r,y0,x0+r);
  for (i=1; i<= imax; i++) {
    if ((i*i+x*x) >sqmax) {
      /* draw lines from outside */
      if (x>imax) {
        LCD_HL_DrawHLine (x0-i+1,y0+x, x0+i-1);
        LCD_HL_DrawHLine (x0-i+1,y0-x, x0+i-1);
      }
      x--;
    }
    /* draw lines from inside (center) */
    LCD_HL_DrawHLine(x0-x,y0+i, x0+x);
    LCD_HL_DrawHLine(x0-x,y0-i, x0+x);
  }
}

/*********************************************************************
*
*       GUI_FillCircle
*/
void GUI_FillCircle(int x0, int y0, int r) {
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    WM_ITERATE_START(NULL); {
  #endif
  GL_FillCircle(x0,y0,r);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*********************************************************************
*
*       Public code, ellipse
*
* The most efficient way to calculate the ellipse positions is using
* the knowledge that the ellipse is just circle which has compressed
* (or stretched) in one direction. For a circle, the following
* equation holds true for all points located on the border of it:
*
*               x^2 + y(x)^2 = r^2 = const
*
* Therefor, for an ellipse we can make use of the following equation:
*
*               (ry*x)^2 + (rx*y(x))^2 = (ry*rx)^2 = const
*
**********************************************************************
*/
/*********************************************************************
*
*       GL_FillEllipse
*/
void GL_FillEllipse(int x0, int y0, int rx, int ry) {
  I32 OutConst, Sum, SumY;
  int x,y;
  U32 _rx = rx;
  U32 _ry = ry;
  OutConst = _rx*_rx*_ry*_ry  /* Constant as explaint above */
            +(_rx*_rx*_ry>>1); /* To compensate for rounding */
  x = rx;
  for (y=0; y<=ry; y++) {
    SumY =((I32)(rx*rx))*((I32)(y*y)); /* Does not change in loop */
    while (Sum = SumY + ((I32)(ry*ry))*((I32)(x*x)),
           (x>0) && (Sum>OutConst))
    {
      x--;
    }
    LCD_HL_DrawHLine(x0-x, y0+y, x0+x);
    if (y)
      LCD_HL_DrawHLine(x0-x, y0-y, x0+x);
  }
}

/*********************************************************************
*
*       GUI_FillEllipse
*/
void GUI_FillEllipse(int x0, int y0, int rx, int ry) {
  #if (GUI_WINSUPPORT)
    GUI_RECT r;
  #endif
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
    /* Calc rectangle in order to avoid unnecessary drawing ops. */
    r.x0 = x0-rx; r.x1 = x0+rx; r.y0 = y0-ry; r.y1 = y0+ry;
    WM_ITERATE_START(&r); {
  #endif
  GL_FillEllipse (x0,y0, rx, ry);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GL_DrawEllipse
*/
void GL_DrawEllipse(int x0, int y0, int rx, int ry) {
  I32 OutConst, Sum, SumY;
  int x,y;
  int xOld;
  U32 _rx = rx;
  U32 _ry = ry;
  OutConst = _rx*_rx*_ry*_ry  /* Constant as explaint above */
            +(_rx*_rx*_ry>>1); /* To compensate for rounding */
  xOld = x = rx;
  for (y=0; y<=ry; y++) {
    if (y==ry) {
      x=0;
    } else {
      SumY =((I32)(rx*rx))*((I32)(y*y)); /* Does not change in loop */
      while (Sum = SumY + ((I32)(ry*ry))*((I32)(x*x)),
             (x>0) && (Sum>OutConst)) x--;
    }
    /* Since we draw lines, we can not draw on the first
        iteration
    */
    if (y) {
      GL_DrawLine1(x0-xOld,y0-y+1,x0-x,y0-y);
      GL_DrawLine1(x0-xOld,y0+y-1,x0-x,y0+y);
      GL_DrawLine1(x0+xOld,y0-y+1,x0+x,y0-y);
      GL_DrawLine1(x0+xOld,y0+y-1,x0+x,y0+y);
    }
    xOld = x;
  }
}

/*********************************************************************
*
*       GUI_DrawEllipse
*/
void GUI_DrawEllipse(int x0, int y0, int rx, int ry) {
  #if (GUI_WINSUPPORT)
    GUI_RECT r;
  #endif
  GUI_LOCK();
  #if (GUI_WINSUPPORT)
    WM_ADDORG(x0,y0);
  /* Calc rectangle in order to avoid unnecessary drawing ops. */
    r.x0 = x0-rx; r.x1 = x0+rx; r.y0 = y0-ry; r.y1 = y0+ry;
    WM_ITERATE_START(&r); {
  #endif
  GL_DrawEllipse(x0, y0, rx, ry);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  GUI_UNLOCK();
}

/*************************** End of file ****************************/
