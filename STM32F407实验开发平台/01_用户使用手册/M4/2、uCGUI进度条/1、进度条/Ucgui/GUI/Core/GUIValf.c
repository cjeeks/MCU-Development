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
File        : GUIValF.C
Purpose     : Displaying floating point values
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"
#include "math.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DispFloatFix
*/
static void _DispFloatFix(float f, char Len, char Decs, int DrawPlusSign) {
  f *= GUI_Pow10[(unsigned)Decs];
  f += 0.5;
  f = (float) floor (f);
  if (DrawPlusSign) {
    GUI_DispSDecShift((long)f, Len, Decs);
  } else {
    GUI_DispDecShift((long)f, Len, Decs);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DispFloatFix
*/
void GUI_DispFloatFix(float f, char Len, char Decs) {
  _DispFloatFix(f, Len, Decs, 0);
}

/*********************************************************************
*
*       GUI_DispFloatMin
*/
void GUI_DispFloatMin(float f, char Fract) {
  char Len;
  Len = GUI_Long2Len((long)f);
  if ((f < 0) && (f > -1)) { /* If value < 0 and > -1 (e.g. -0.123) increment length by 1 */
    Len++;
  }
  _DispFloatFix(f, (char)(Len + Fract + (Fract ? 1 : 0)), (char)Fract, 0);
}

/*********************************************************************
*
*       GUI_DispFloat
*/
void GUI_DispFloat(float f, char Len) {
  int Decs;
  Decs =  Len - GUI_Long2Len((long)f)-1;
  if ((f < 0) && (f > -1)) { /* If value < 0 and > -1 (e.g. -0.123) decrement Decs */
    Decs--;
  }
  if (Decs<0)
    Decs =0;
  _DispFloatFix(f, Len, (char)Decs, 0);
}

/*********************************************************************
*
*       GUI_DispSFloatFix
*/
void GUI_DispSFloatFix(float f, char Len, char Fract) {
  _DispFloatFix (f, Len, Fract, 1);
}

/*********************************************************************
*
*       GUI_DispSFloatMin
*/
void GUI_DispSFloatMin(float f, char Fract) {
  char Len;
  Len = GUI_Long2Len((long)f);
  if ((f < 0) && (f > -1)) { /* If value < 0 and > -1 (e.g. -0.123) increment length by 1 */
    Len++;
  }
  if (f>0) {
    Len++;
  }
  _DispFloatFix(f, (char)(Len + Fract + (Fract ? 1 : 0)), (char)Fract, 1);
}

/*************************** End of file ****************************/
