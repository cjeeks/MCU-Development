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
File        : GUICharAA.C
Purpose     : Display antialiased
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

#if GUI_SUPPORT_AA

#include <stdio.h>
#include <string.h>

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       Draw
*/
static void Draw(int x0, int y0, int XSize, int YSize, int BytesPerLine, const U8*pData) {
  int x, y;
  tLCD_SetPixelAA* pfSetPixelAA;
  pfSetPixelAA = (GUI_Context.TextMode && GUI_TM_TRANS) ?
                 LCD_SetPixelAA : LCD_SetPixelAA_NoTrans;
  for (y=0; y<YSize; y++) {
    const U8*pData0 = pData;
    for (x=0; x<XSize-1; x+=2) {
      (*pfSetPixelAA)(x+x0,y0+y,   (*pData0)>>4); /* x0+x changed -> x+x0 to avoid problems with IAR's ICCMC80 */
      (*pfSetPixelAA)(x0+x+1,y0+y, (*pData0++)&15);
  	}
    if (XSize&1) {
      (*pfSetPixelAA)(x0+x,y0+y, (*pData0)&15);
    }
    pData+=BytesPerLine;
  }
}

/*********************************************************************
*
*       GUIPROP_FindChar
*/
static const GUI_FONT_PROP* GUIPROP_FindChar(const GUI_FONT_PROP* pProp, U16P c) {
  for (pProp = GUI_Context.pAFont->p.pProp; pProp; pProp=(const GUI_FONT_PROP*) pProp->pNext) {
    if ((c>=pProp->First) && (c<=pProp->Last))
      break;
  }
  return pProp;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIPROP_AA4_DispChar
*/
void GUIPROP_AA4_DispChar(U16P c) {
  int BytesPerLine;
  GUI_DRAWMODE DrawMode = GUI_Context.TextMode;
  const GUI_FONT_PROP* pProp = GUIPROP_FindChar(GUI_Context.pAFont->p.pProp, c);
  if (pProp) {
    GUI_DRAWMODE OldDrawMode;
    const GUI_CHARINFO* pCharInfo = pProp->paCharInfo+(c-pProp->First);
    BytesPerLine = pCharInfo->BytesPerLine;
    OldDrawMode  = LCD_SetDrawMode(DrawMode);
    Draw  ( GUI_Context.DispPosX, GUI_Context.DispPosY,
                       pCharInfo->XSize,
                       GUI_Context.pAFont->YSize,
                       BytesPerLine,
                       (U8 const*)pCharInfo->pData
                       );
    LCD_SetDrawMode(OldDrawMode); /* Restore draw mode */
    GUI_Context.DispPosX += pCharInfo->XDist;
  }
}

/*********************************************************************
*
*       GUIPROP_AA4_GetCharDistX
*/
int GUIPROP_AA4_GetCharDistX(U16P c) {
  const GUI_FONT_PROP* pProp = GUIPROP_FindChar(GUI_Context.pAFont->p.pProp, c);
  return (pProp) ? (pProp->paCharInfo+(c-pProp->First))->XSize : 0;
}

/*********************************************************************
*
*       GUIPROP_AA4_GetFontInfo
*/
void GUIPROP_AA4_GetFontInfo(const GUI_FONT * pFont, GUI_FONTINFO* pfi) {
  GUI_USE_PARA(pFont);
  pfi->Flags = GUI_FONTINFO_FLAG_PROP | GUI_FONTINFO_FLAG_AA4;
}

/*********************************************************************
*
*       GUIPROP_AA4_IsInFont
*/
char GUIPROP_AA4_IsInFont(const GUI_FONT * pFont, U16 c) {
  const GUI_FONT_PROP* pProp = GUIPROP_FindChar(pFont->p.pProp, c);
  return (pProp==NULL) ? 0 : 1;
}

#else                            /* Avoid problems with empty object modules */
  void GUIAAChar4_C(void);
  void GUIAAChar4_C(void) {}
#endif /* GUI_SUPPORT_AA */

/*************************** End of file ****************************/
