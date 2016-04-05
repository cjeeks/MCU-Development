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
File        : EditDec
Purpose     : Edit decimal values
---------------------------END-OF-HEADER------------------------------
*/

#include <math.h>

#include "EDIT.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"
#include "EDIT_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*             Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       EDIT_SetFloatMode
*/
void EDIT_SetFloatMode(EDIT_Handle hEdit, float Value, float Min, float Max, int Shift, U8 Flags) {
  I32 _Value, _Min, _Max;
  float Scale;
  if (hEdit) {
    WM_LOCK();
    Scale  =(float)GUI_Pow10[Shift];
    _Value = floor(Scale * Value + 0.5);
    _Min   = floor(Scale * Min + 0.5);
    _Max   = floor(Scale * Max + 0.5);
    EDIT_SetDecMode(hEdit, _Value, _Min, _Max, Shift, Flags);
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       EDIT_GetFloatValue
*/
float EDIT_GetFloatValue(EDIT_Handle hObj) {
  float Value = 0;
  if (hObj) {
    float Scale;
    EDIT_Obj * pObj;
    WM_LOCK();
    pObj  = EDIT_H2P(hObj);
    Scale = (float)GUI_Pow10[pObj->NumDecs];
    Value = (float)(I32)pObj->CurrentValue / Scale;
    WM_UNLOCK();
  }
  return Value;
}

/*********************************************************************
*
*       EDIT_SetFloatValue
*/
void EDIT_SetFloatValue(EDIT_Handle hObj, float Value) {
  if (hObj) {
    float Scale;
    EDIT_Obj * pObj;
    WM_LOCK();
    pObj  = EDIT_H2P(hObj);
    Scale = (float)GUI_Pow10[pObj->NumDecs];
    Value *= Scale;
    EDIT_SetValue(hObj, (I32)(Value + (Value >= 0 ? 0.5 : -0.5)));
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */

void EditFloat_C(void);
void EditFloat_C(void){}

#endif /* GUI_WINSUPPORT */
