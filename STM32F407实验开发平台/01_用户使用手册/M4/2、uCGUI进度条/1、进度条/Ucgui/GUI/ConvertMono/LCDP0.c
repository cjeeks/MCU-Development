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
File        : LCDP0.C
Purpose     : Color conversion routines for LCD-drivers
---------------------------END-OF-HEADER------------------------------
*/

#include "LCD_Private.h"    /* inter modul definitions */
#include "GUI.h"

/*********************************************************************
*
*       Public code, 1/2/4/8 bpp color, LUT
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_Color2Index_0
*/
unsigned LCD_Color2Index_0(LCD_COLOR Color, const LCD_PHYSPALETTE* pPhysPal) {
  int i;
  int NumEntries = pPhysPal->NumEntries;
  int BestIndex = 0;
  U32 BestDiff = 0xffffff; /* Initialize to worst match */
  const LCD_COLOR* pPalEntry;
/* Try to find perfect match */
  i=0; pPalEntry = &pPhysPal->pPalEntries[0];
  do {
	  if (Color==*(pPalEntry+i))
	    return i;
  } while (++i<NumEntries);
/* Find best match */
  i=0; pPalEntry = &pPhysPal->pPalEntries[0];
  do {
    U32 Diff = GUI_CalcColorDist (Color, *(pPalEntry+i));
    if (Diff < BestDiff) {
      BestDiff  = Diff;
      BestIndex = i;
    }
  } while (++i<NumEntries);
  return BestIndex;
}

/*********************************************************************
*
*       LCD_Index2Color_0
*/
LCD_COLOR LCD_Index2Color_0(int Index, const LCD_PHYSPALETTE* pPhysPal) {
  if ((unsigned)Index >= (unsigned) pPhysPal->NumEntries) {
    return 0;     /* Illegal index */
  }
  return *(pPhysPal->pPalEntries+Index);
}

/*********************************************************************
*
*       LCD_GetIndexMask_0
*/
unsigned LCD_GetIndexMask_0(void) {
  return ((1 << LCD_BITSPERPIXEL) - 1);
}

/*************************** End of file ****************************/
