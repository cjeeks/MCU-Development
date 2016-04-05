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
File        : GUI_CursorCrossLI.c
Purpose     : Defines the cross cursor, large
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "GUI_Protected.h"

GUI_CONST_STORAGE GUI_BITMAP GUI_BitmapCrossLI = {
 31,                   /* XSize */
 31,                   /* YSize */
 8,                    /* BytesPerLine */
 2,                    /* BitsPerPixel */
 GUI_Pixels_CrossL,    /* Pointer to picture data (indices) */
 &GUI_CursorPalI       /* Pointer to palette */
};


GUI_CONST_STORAGE GUI_CURSOR GUI_CursorCrossLI = {
  &GUI_BitmapCrossLI, 15, 15
};


/*************************** End of file ****************************/
