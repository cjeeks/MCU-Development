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
File        : RADIO_SetDefaultImage.c
Purpose     : Implementation of radio widget
---------------------------END-OF-HEADER------------------------------
*/

#include "RADIO.h"
#include "RADIO_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/
/*********************************************************************
*
*       RADIO_SetDefaultImage
*/
void RADIO_SetDefaultImage(const GUI_BITMAP * pBitmap, unsigned int Index) {
  switch (Index) {
  case RADIO_BI_INACTIV:
  case RADIO_BI_ACTIV:
    RADIO__apDefaultImage[Index] = pBitmap;
    break;
  case RADIO_BI_CHECK:
    RADIO__pDefaultImageCheck = pBitmap;
    break;
  }
}

#else                            /* Avoid problems with empty object modules */
  void RADIO_SetDefaultImage_C(void);
  void RADIO_SetDefaultImage_C(void) {}
#endif

/************************* end of file ******************************/
