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
File        : GUITOUCH.C
Purpose     : Touch screen manager
----------------------------------------------------------------------
This module handles the touch screen. It is configured in the file
GUITouch.conf.h (Should be located in the Config\ directory).
----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LCD_Private.h"      /* private modul definitions & config */
#include "GUI_Protected.h"

/* Generate code only if configuration says so ! */
#if GUI_SUPPORT_TOUCH

#include "GUITouchConf.h"    /* Located in GUIx, will include GUITouchConf.h */

/*********************************************************************
*
*       Defines, config defaults
*
**********************************************************************
*/

#ifndef GUI_TOUCH_AD_LEFT         /* max value returned by AD-converter */
  #define GUI_TOUCH_AD_LEFT 30   
#endif

#ifndef GUI_TOUCH_AD_RIGHT        /* min value returned by AD-converter */
  #define GUI_TOUCH_AD_RIGHT 220    
#endif

#ifndef GUI_TOUCH_AD_TOP          /* max value returned by AD-converter */
  #define GUI_TOUCH_AD_TOP 30
#endif

#ifndef GUI_TOUCH_AD_BOTTOM       /* min value returned by AD-converter */
  #define GUI_TOUCH_AD_BOTTOM 220
#endif

#ifndef GUI_TOUCH_SWAP_XY         /* Is XY of touch swapped ? */
  #define GUI_TOUCH_SWAP_XY 0
#endif

#ifndef GUI_TOUCH_MIRROR_X
  #define GUI_TOUCH_MIRROR_X 0
#endif

#ifndef GUI_TOUCH_MIRROR_Y
  #define GUI_TOUCH_MIRROR_Y 0
#endif

#ifndef GUI_TOUCH_YSIZE
  #define GUI_TOUCH_YSIZE LCD_YSIZE
#endif

#ifndef GUI_TOUCH_XSIZE
  #define GUI_TOUCH_XSIZE LCD_XSIZE
#endif

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef struct {int Min; int Max; } tMinMax;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static int xPhys, yPhys;

static tMinMax xyMinMax[2] = {
#if ((GUI_TOUCH_SWAP_XY==0) && (GUI_TOUCH_MIRROR_X==0)) || ((GUI_TOUCH_SWAP_XY) && (GUI_TOUCH_MIRROR_Y==0))
  { GUI_TOUCH_AD_LEFT, GUI_TOUCH_AD_RIGHT },
#else
  { GUI_TOUCH_AD_RIGHT, GUI_TOUCH_AD_LEFT },
#endif
#if ((GUI_TOUCH_SWAP_XY==0) && (GUI_TOUCH_MIRROR_Y==0)) || ((GUI_TOUCH_SWAP_XY) && (GUI_TOUCH_MIRROR_X==0))
  { GUI_TOUCH_AD_TOP,  GUI_TOUCH_AD_BOTTOM }
#else
  { GUI_TOUCH_AD_BOTTOM,  GUI_TOUCH_AD_TOP }
#endif
};

#ifndef WIN32
static int xMin;
static int xMax;
static int yMin;
static int yMax;
#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _AD2X
*
* Purpose:
*   Convert physical value into (logical) coordinates.
*/
#ifndef WIN32
static int _AD2X(int adx) {
  I32 r = adx - xyMinMax[GUI_COORD_X].Min;
  r *= GUI_TOUCH_XSIZE - 1;
  return r / (xyMinMax[GUI_COORD_X].Max - xyMinMax[GUI_COORD_X].Min);    
}

/*********************************************************************
*
*       _AD2Y
*
* Purpose:
*   Convert physical value into (logical) coordinates.
*/
static int _AD2Y(int ady) {
  I32 r = ady - xyMinMax[GUI_COORD_Y].Min;
  r *= GUI_TOUCH_YSIZE - 1;
  return r/(xyMinMax[GUI_COORD_Y].Max - xyMinMax[GUI_COORD_Y].Min);    
}
#endif

/*********************************************************************
*
*       _Log2Phys
*/
static int _Log2Phys(int l, I32 l0, I32 l1, I32 p0, I32 p1) {
  return p0+ ((p1 - p0) * (l - l0)) / (l1 - l0);
}

/*********************************************************************
*
*       _StoreUnstable
*/
static void _StoreUnstable(int x, int y) {
  static int _xLast = -1;
  static int _yLast = -1;
  int xOut, yOut;

  if ((x != -1) && (y != -1) && (_xLast != -1) && (_yLast != -1)) {
    xOut = _xLast;    
    yOut = _yLast;    
  } else {
    xOut = -1;
    yOut = -1;    
  }
  _xLast = x;
  _yLast = y;
  GUI_TOUCH_StoreUnstable(xOut, yOut);
}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_TOUCH_GetxPhys
*/
int  GUI_TOUCH_GetxPhys(void) {
  return xPhys;
}

/*********************************************************************
*
*       GUI_TOUCH_GetyPhys
*/
int  GUI_TOUCH_GetyPhys(void) {
  return yPhys;
}

/*********************************************************************
*
*       GUI_TOUCH_SetDefaultCalibration
*/
void GUI_TOUCH_SetDefaultCalibration(void) {
  xyMinMax[0].Min = GUI_TOUCH_AD_LEFT;
  xyMinMax[0].Max = GUI_TOUCH_AD_RIGHT;
  xyMinMax[1].Min = GUI_TOUCH_AD_TOP;
  xyMinMax[1].Max = GUI_TOUCH_AD_BOTTOM;
}

/*********************************************************************
*
*       GUI_TOUCH_Calibrate
*/
int GUI_TOUCH_Calibrate(int Coord, int Log0, int Log1, int Phys0, int Phys1) {
  int l0 = 0;
  int l1 = (Coord == GUI_COORD_X) ? LCD_XSIZE - 1 : LCD_YSIZE - 1;
  if (labs(Phys0 - Phys1) < 20) {
    return 1;
  }
  if (labs(Log0 - Log1) < 20) {
    return 1;
  }
  xyMinMax[Coord].Min = _Log2Phys(l0, Log0, Log1, Phys0, Phys1);  
  xyMinMax[Coord].Max = _Log2Phys(l1, Log0, Log1, Phys0, Phys1);
  return 0;
}

/*********************************************************************
*
*       GUI_TOUCH_GetCalData
*/
void GUI_TOUCH_GetCalData(int Coord, int* pMin,int* pMax) {
  *pMin = xyMinMax[Coord].Min;
  *pMax = xyMinMax[Coord].Max; 
}
  
/*********************************************************************
*
*       GUI_TOUCH_Exec
*/
void GUI_TOUCH_Exec(void) {
  #ifndef WIN32
  static U8 ReadState;
  int x,y;
  /* calculate Min / Max values */
  if (xyMinMax[GUI_COORD_X].Min < xyMinMax[GUI_COORD_X].Max) {
    xMin = xyMinMax[GUI_COORD_X].Min;
    xMax = xyMinMax[GUI_COORD_X].Max;
  } else {
    xMax = xyMinMax[GUI_COORD_X].Min;
    xMin = xyMinMax[GUI_COORD_X].Max;
  }
  if (xyMinMax[GUI_COORD_Y].Min < xyMinMax[GUI_COORD_Y].Max) {
    yMin = xyMinMax[GUI_COORD_Y].Min;
    yMax = xyMinMax[GUI_COORD_Y].Max;
  } else {
    yMax = xyMinMax[GUI_COORD_Y].Min;
    yMin = xyMinMax[GUI_COORD_Y].Max;
  }
  /* Execute the state machine which reads the touch */
  switch (ReadState) {
  case 0:
    yPhys = TOUCH_X_MeasureY();
    TOUCH_X_ActivateY();  /* Prepare X- measurement */
    ReadState++;
    break;
  default:
    xPhys = TOUCH_X_MeasureX();
    TOUCH_X_ActivateX();  /* Prepare Y- measurement */
    /* Convert values into logical values */
    #if !GUI_TOUCH_SWAP_XY   /* Is X/Y swapped ? */
      x = xPhys;
      y = yPhys;
    #else
      x = yPhys;
      y = xPhys;
    #endif
    if ((x < xMin) || (x > xMax)  || (y < yMin) || (y > yMax)) {
      _StoreUnstable(-1, -1);
    } else {
      x = _AD2X(x);
      y = _AD2Y(y);
      _StoreUnstable(x, y);
    }
    /* Reset state machine */
    ReadState = 0;
    break;
  }
  #endif /* WIN32 */
}

#else

void GUI_TOUCH_DriverAnalog_C(void);  /* Avoid "no prototype" warnings */
void GUI_TOUCH_DriverAnalog_C(void) {}

#endif    /* defined(GUI_SUPPORT_TOUCH) && GUI_SUPPORT_TOUCH */

/*************************** End of file ****************************/
