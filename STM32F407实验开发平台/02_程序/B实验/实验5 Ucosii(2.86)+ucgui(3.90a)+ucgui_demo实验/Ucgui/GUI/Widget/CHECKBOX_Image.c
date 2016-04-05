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
File        : CHECKBOX_Image.c
Purpose     : Contains the default bitmap used by the checkbox widget
---------------------------END-OF-HEADER------------------------------
*/

#include "CHECKBOX.h"
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
  XXXXXXX_, _XX_____,
  XX_XXX__, _XX_____,
  XX__X___, XXX_____,
  XX_____X, XXX_____,
  XXX___XX, XXX_____,
  XXXX_XXX, XXX_____,
  XXXXXXXX, XXX_____,
  XXXXXXXX, XXX_____
};

/*********************************************************************
*
*       Exported const data
*
**********************************************************************
*/
/* Bitmaps */
const GUI_BITMAP CHECKBOX__abmCheck[2] = {
  { 11, 11, 2, 1, _acCheck,  &_PalCheckDisabled},
  { 11, 11, 2, 1, _acCheck,  &_PalCheckEnabled }
};

#else                            /* Avoid problems with empty object modules */
  void CHECKBOX_Image_C(void);
  void CHECKBOX_Image_C(void) {}
#endif
