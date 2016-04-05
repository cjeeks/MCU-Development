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
File        : GUI_SIF.c
Purpose     : Implementation of system independend fonts
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/

/*********************************************************************
*
*       GUI_SIF_CreateFont
*/
void GUI_SIF_CreateFont(void * pFontData, GUI_FONT * pFont, const GUI_SIF_TYPE * pFontType) {
  const U8 * pSrc = (const U8 *)pFontData;
  U32 ID;
  /* Set pFontData of GUI_FONT structure to the first byte */
  pFont->p.pFontData = pFontData;
  /* Check ID */
  ID = GUI__Read32(&pSrc);
  if (ID != 0x50495547) { /* 'GUIP' */
    GUI_DEBUG_ERROROUT("ID of downloaded font wrong!");
    return;
  }
  /* Read properties of the font */
  pFont->YSize    = GUI__Read16(&pSrc);
  pFont->YDist    = GUI__Read16(&pSrc);
  pFont->Baseline = GUI__Read16(&pSrc);
  pFont->LHeight  = GUI__Read16(&pSrc);
  pFont->CHeight  = GUI__Read16(&pSrc);
  /* Magnification is always 1 */
  pFont->XMag = 1;
  pFont->YMag = 1;
  /* Set function pointers */
  pFont->pfDispChar     = pFontType->pDispChar;
  pFont->pfGetCharDistX = pFontType->pGetCharDistX;
  pFont->pfGetFontInfo  = pFontType->pGetFontInfo;
  pFont->pfIsInFont     = pFontType->pIsInFont;
  pFont->pafEncode      = 0;
  /* Use the new font */
  GUI_SetFont(pFont);
}

/*********************************************************************
*
*       GUI_SIF_DeleteFont
*/
void GUI_SIF_DeleteFont(GUI_FONT * pFont) {
  GUI_USE_PARA(pFont);
}
