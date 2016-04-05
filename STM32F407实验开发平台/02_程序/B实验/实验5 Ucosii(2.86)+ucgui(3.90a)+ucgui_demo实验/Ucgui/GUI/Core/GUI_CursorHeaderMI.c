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
File        : GUI_CursorHeaderMI.c
Purpose     : Defines the header cursor, medium size, invers
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Protected.h"

/*********************************************************************
*
*       static data, cursor bitmap
*
**********************************************************************
*/

static GUI_CONST_STORAGE GUI_BITMAP _Bitmap = {
 17,                  /* XSize */
 17,                  /* YSize */
 5,                   /* BytesPerLine */
 2,                   /* BitsPerPixel */
 GUI_PixelsHeaderM,   /* Pointer to picture data (indices) */
 &GUI_CursorPalI      /* Pointer to palette */
};


/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
GUI_CONST_STORAGE GUI_CURSOR GUI_CursorHeaderMI = {
  &_Bitmap, 8, 8
};

/*************************** End of file ****************************/
