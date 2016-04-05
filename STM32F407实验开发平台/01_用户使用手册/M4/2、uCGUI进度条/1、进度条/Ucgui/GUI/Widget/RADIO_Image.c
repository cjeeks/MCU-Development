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
File        : RADIO_Image.c
Purpose     : Implementation of radio widget
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"
#include "RADIO_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/* Define colors */
#ifndef RADIO_BKCOLOR0_DEFAULT
  #define RADIO_BKCOLOR0_DEFAULT 0xc0c0c0           /* Inactive color */
#endif

#ifndef RADIO_BKCOLOR1_DEFAULT
  #define RADIO_BKCOLOR1_DEFAULT GUI_WHITE          /* Active color */
#endif

/*********************************************************************
*
*       Static const data
*
**********************************************************************
*/

/* Colors */
static const GUI_COLOR _aColorDisabled[] = {0xC0C0C0, 0x808080, 0x000000, RADIO_BKCOLOR0_DEFAULT};
static const GUI_COLOR _aColorEnabled[]  = {0xC0C0C0, 0x808080, 0x000000, RADIO_BKCOLOR1_DEFAULT};
static const GUI_COLOR _ColorsCheck[]    = {0xFFFFFF, 0x000000};

/* Palettes */
static const GUI_LOGPALETTE _PalRadioDisabled = {
  4,	/* number of entries */
  1, 	/* Transparency */
  _aColorDisabled
};

static const GUI_LOGPALETTE _PalRadioEnabled = {
  4,	/* number of entries */
  1, 	/* Transparency */
  _aColorEnabled
};

static const GUI_LOGPALETTE _PalCheck = {
  2,	/* number of entries */
  1, 	/* Transparency */
  &_ColorsCheck[0]
};

/* Pixel data */
static const unsigned char _acRadio[] = {
  0x00, 0x55, 0x00,
  0x05, 0xAA, 0x50,
  0x1A, 0xFF, 0xAC,
  0x1B, 0xFF, 0xCC,
  0x6F, 0xFF, 0xF3,
  0x6F, 0xFF, 0xF3,
  0x6F, 0xFF, 0xF3,
  0x6F, 0xFF, 0xF3,
  0x1B, 0xFF, 0xCC,
  0x10, 0xFF, 0x0C,
  0x0F, 0x00, 0xF0,
  0x00, 0xFF, 0x00
};

static const unsigned char _acCheck[] = {
  _XX_____,
  XXXX____,
  XXXX____,
  _XX_____
};

/*********************************************************************
*
*       Exported const data
*
**********************************************************************
*/
/* Bitmaps */
const GUI_BITMAP RADIO__abmRadio[] = {
  { 12, 12, 3, 2, _acRadio, &_PalRadioDisabled},
  { 12, 12, 3, 2, _acRadio, &_PalRadioEnabled}
};

const GUI_BITMAP RADIO__bmCheck = {
  4, /* XSize */
  4, /* YSize */
  1, /* BytesPerLine */
  1, /* BitsPerPixel */
  _acCheck,  /* Pointer to picture data (indices) */
  &_PalCheck  /* Pointer to palette */
};

#else                            /* Avoid problems with empty object modules */
  void RADIO_Image_C(void);
  void RADIO_Image_C(void) {}
#endif

/************************* end of file ******************************/
