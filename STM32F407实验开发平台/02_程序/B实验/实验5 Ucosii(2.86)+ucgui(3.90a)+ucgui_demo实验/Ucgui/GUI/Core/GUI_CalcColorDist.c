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
File        : GUI_CalcColorDist
Purpose     : Color conversion routines
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "GUI.h"

/*********************************************************************
*
*       defines
*
**********************************************************************
*/

#if 1  /* Normaly calculate square values */

  #define  SQUARE(Dist) ((U16)Dist) * ((U16)Dist)

#else

  #define S(x) ((x)*(x))
  #define SQUARES(Base)  S(Base+0),  S(Base+1),  S(Base+2),  S(Base+3), S(Base+4),  S(Base+5),  \
                         S(Base+6),  S(Base+7),  S(Base+8),  S(Base+9), S(Base+10), S(Base+11), \
                         S(Base+12), S(Base+13), S(Base+14), S(Base+15)

  static const U16 aSquare[] = {
    SQUARES(0*16)
    ,SQUARES(1*16), SQUARES(2*16), SQUARES(3*16)
    ,SQUARES(4*16) ,SQUARES(5*16), SQUARES(6*16), SQUARES(7*16)
    ,SQUARES(8*16) ,SQUARES(9*16), SQUARES(10*16),SQUARES(11*16)
    ,SQUARES(12*16),SQUARES(13*16),SQUARES(14*16),SQUARES(15*16)
  };

  #define  SQUARE(Dist) aSquare[Dist]

#endif

/*********************************************************************
*
*       public code, color conversions for palette based displays
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_CalcColorDist
*/
U32 GUI_CalcColorDist (LCD_COLOR PalColor, LCD_COLOR  Color) {
/* This routine does not use abs() because we are optimizing for speed ! */
  I16 Dist;
  U32 Sum;
  Dist  = (PalColor&0xff) - (Color&0xff);
  if (Dist < 0)
	  Dist = -Dist;
  Sum = SQUARE(Dist);
  Dist  = ((PalColor>>8)&0xff) -  ((Color>>8)&0xff);
  if (Dist < 0)
	  Dist = -Dist;
  Sum += SQUARE(Dist);
  Dist  = (PalColor>>16) - (Color>>16);
  if (Dist < 0)
	  Dist = -Dist;
  return Sum + SQUARE(Dist);
}

/*************************** End of file ****************************/
