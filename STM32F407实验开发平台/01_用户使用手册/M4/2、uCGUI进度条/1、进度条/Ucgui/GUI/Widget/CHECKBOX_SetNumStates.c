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
File        : CHECKBOX_SetNumStates.c
Purpose     : Routines and bitmaps used for third state of checkbox
---------------------------END-OF-HEADER------------------------------
*/

#include "CHECKBOX_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Static const data
*
**********************************************************************
*/
/* Colors */
static const GUI_COLOR _aColorDisabled[] = {CHECKBOX_FGCOLOR0_DEFAULT, CHECKBOX_BKCOLOR0_DEFAULT};
static const GUI_COLOR _aColorEnabled[]  = {CHECKBOX_FGCOLOR1_DEFAULT, CHECKBOX_BKCOLOR1_DEFAULT};

/* Palettes */
static const GUI_LOGPALETTE _PalCheckDisabled = {
  2,	/* number of entries */
  0, 	/* No transparency */
  _aColorDisabled
};

static const GUI_LOGPALETTE _PalCheckEnabled = {
  2,	/* number of entries */
  0, 	/* No transparency */
  _aColorEnabled
};

/* Pixel data */
static const unsigned char _acCheck[] = {
  XXXXXXXX, XXX_____,
  XXXXXXXX, XXX_____,
  XXXXXXXX, _XX_____,
  XXXXXXX_, XXX_____,
  XX_XXX_X, _XX_____,
  XXX_X_X_, XXX_____,
  XX_X_X_X, XXX_____,
  XXX_X_XX, XXX_____,
  XXXX_XXX, XXX_____,
  XXXXXXXX, XXX_____,
  XXXXXXXX, XXX_____
};

/* Bitmaps */
static const GUI_BITMAP _abmCheck[2] = {
  { 11, 11, 2, 1, _acCheck,  &_PalCheckDisabled},
  { 11, 11, 2, 1, _acCheck,  &_PalCheckEnabled }
};

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       CHECKBOX_SetNumStates
*/
void CHECKBOX_SetNumStates(CHECKBOX_Handle hObj, unsigned NumStates) {
  CHECKBOX_Obj * pObj;
  if (!CHECKBOX__DefaultProps.apBm[2]) {
    CHECKBOX_SetDefaultImage(&_abmCheck[0], 2);
  }
  if (!CHECKBOX__DefaultProps.apBm[3]) {
    CHECKBOX_SetDefaultImage(&_abmCheck[1], 3);
  }
  if (hObj && ((NumStates == 2) || (NumStates == 3))) {
    WM_LOCK();
    pObj = CHECKBOX_H2P(hObj);
    pObj->Props.apBm[2] = CHECKBOX__DefaultProps.apBm[2];
    pObj->Props.apBm[3] = CHECKBOX__DefaultProps.apBm[3];
    pObj->NumStates = NumStates;
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_SetNumStates_C(void);
  void CHECKBOX_SetNumStates_C(void) {}
#endif
