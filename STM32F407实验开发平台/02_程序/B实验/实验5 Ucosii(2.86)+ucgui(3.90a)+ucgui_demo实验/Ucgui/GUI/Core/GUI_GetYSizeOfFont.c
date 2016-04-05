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
File        : GUI_GetYSizeOfFont.c
Purpose     : Implementation of optional routines
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_GetYSizeOfFont
*/
int GUI_GetYSizeOfFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  return pFont->YSize * pFont->YMag;
}

/*********************************************************************
*
*       GUI_GetYDistOfFont
*/
int GUI_GetYDistOfFont(const GUI_FONT GUI_UNI_PTR * pFont) {
  return pFont->YDist * pFont->YMag;
}

/*************************** End of file ****************************/
