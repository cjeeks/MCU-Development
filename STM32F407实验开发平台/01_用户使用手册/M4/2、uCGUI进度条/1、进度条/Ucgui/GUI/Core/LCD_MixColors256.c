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
File        : LCD_MixColors256.c
Purpose     : Implementation of LCD_MixColors256
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD.h"
#include "GUI_Private.h"
#include "LCD_Private.h"

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_MixColors256
*
* Purpose:
*   Mix 2 colors.
*
* Parameters:
*   Intens:    Intensity of first color in 257 steps, from 0 to 256, where 256 equals 100%
*/
LCD_COLOR LCD_MixColors256(LCD_COLOR Color, LCD_COLOR BkColor, unsigned Intens) {
  /* Calc Color seperations for FgColor first */
  U32 R = (Color & 0xff)    * Intens;
  U32 G = (Color & 0xff00)  * Intens;
  U32 B = (Color & 0xff0000)* Intens;
  /* Add Color seperations for BkColor */
  Intens = 256 - Intens;
  R += (BkColor & 0xff)     * Intens;
  G += (BkColor & 0xff00)   * Intens;
  B += (BkColor & 0xff0000) * Intens;
  R = (R >> 8);
  G = (G >> 8) & 0xff00;
  B = (B >> 8) & 0xff0000;
  return R + G + B;
}

/*************************** End of file ****************************/
