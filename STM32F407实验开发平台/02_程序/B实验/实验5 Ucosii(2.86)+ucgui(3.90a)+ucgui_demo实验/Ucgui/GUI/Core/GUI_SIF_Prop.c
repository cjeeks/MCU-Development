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
File        : GUI_SIF_Prop.c
Purpose     : Implementation of system independend fonts
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_Private.h"

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _GetNumCharAreas
*/
static int _GetNumCharAreas(const GUI_FONT GUI_UNI_PTR * pFont) {
  U16 NumCharAreas;
  const U8 * pData;
  pData = (const U8 *)pFont->p.pFontData + 14 /* Skip ID, YSize, YDist, Baseline, LHeight and CHeight */;
  NumCharAreas = GUI__Read16(&pData);
  return NumCharAreas;
}

/*********************************************************************
*
*       _GetpCharInfo
*/
static const U8 * _GetpCharInfo(const GUI_FONT GUI_UNI_PTR * pFont, U16P c) {
  const U8 * pCharArea, * pCharInfo;
  int NumCharAreas;
  NumCharAreas = _GetNumCharAreas(pFont);                 /* Get # of char areas */
  pCharArea = (const U8 *)pFont->p.pFontData 
              + sizeof(GUI_SI_FONT);                      /* Set char area pointer to first char area */
  pCharInfo = pCharArea
              + sizeof(GUI_SIF_CHAR_AREA) * NumCharAreas; /* Set char info pointer to first character info */
  do {
    GUI_SIF_CHAR_AREA CharArea;
    CharArea.First    = GUI__Read16(&pCharArea);
    CharArea.Last     = GUI__Read16(&pCharArea);
    if ((c >= CharArea.First) && (c <= CharArea.Last)) {
      pCharInfo += sizeof(GUI_SIF_CHARINFO) * (c - CharArea.First);
      return pCharInfo;
    }
    pCharInfo += sizeof(GUI_SIF_CHARINFO) * (CharArea.Last - CharArea.First + 1);
  } while(--NumCharAreas);
  return 0;
}

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/

/*********************************************************************
*
*       GUI_SIF_DispChar
*/
static void _GUI_SIF_DispChar(U16P c) {
  const U8 * pCharInfo, * pData;
  pCharInfo = _GetpCharInfo(GUI_Context.pAFont, c);
  if (pCharInfo) {
    GUI_DRAWMODE DrawMode, OldDrawMode;
    GUI_SIF_CHARINFO CharInfo;
    CharInfo.XSize        = GUI__Read16(&pCharInfo);
    CharInfo.XDist        = GUI__Read16(&pCharInfo);
    CharInfo.BytesPerLine = GUI__Read16(&pCharInfo);
                            GUI__Read16(&pCharInfo); /* Dummy */
    CharInfo.OffData      = GUI__Read32(&pCharInfo);
    pData = (const U8 *)GUI_Context.pAFont->p.pFontData + CharInfo.OffData;
    DrawMode = GUI_Context.TextMode;
    OldDrawMode  = LCD_SetDrawMode(DrawMode);
    LCD_DrawBitmap(GUI_Context.DispPosX, GUI_Context.DispPosY,
                   CharInfo.XSize,
									 GUI_Context.pAFont->YSize,
                   GUI_Context.pAFont->XMag,
									 GUI_Context.pAFont->YMag,
                   1,
                   CharInfo.BytesPerLine,
                   pData,
                   &LCD_BKCOLORINDEX);
    /* Fill empty pixel lines */
    if (GUI_Context.pAFont->YDist > GUI_Context.pAFont->YSize) {
      int YMag = GUI_Context.pAFont->YMag;
      int YDist = GUI_Context.pAFont->YDist * YMag;
      int YSize = GUI_Context.pAFont->YSize * YMag;
      if (DrawMode != LCD_DRAWMODE_TRANS) {
        LCD_COLOR OldColor = GUI_GetColor();
        GUI_SetColor(GUI_GetBkColor());
        LCD_FillRect(GUI_Context.DispPosX, 
                     GUI_Context.DispPosY + YSize, 
                     GUI_Context.DispPosX + CharInfo.XSize, 
                     GUI_Context.DispPosY + YDist);
        GUI_SetColor(OldColor);
      }
    }
    LCD_SetDrawMode(OldDrawMode); /* Restore draw mode */
    GUI_Context.DispPosX += CharInfo.XDist;
  }
}

/*********************************************************************
*
*       GUI_SIF_GetCharDistX
*/
static int _GUI_SIF_GetCharDistX(U16P c) {
  const U8 * pCharInfo;
  U16 DistX = 0;
  pCharInfo = _GetpCharInfo(GUI_Context.pAFont, c); /* Get pointer to char info data */
  if (pCharInfo) {
    pCharInfo += 2 /* Skip XSize */;
    DistX = GUI__Read16(&pCharInfo);
  }
  return DistX;
}

/*********************************************************************
*
*       GUI_SIF_GetFontInfo
*/
static void _GUI_SIF_GetFontInfo(const GUI_FONT GUI_UNI_PTR * pFont, GUI_FONTINFO * pfi) {
  const U8 * pData;
  pData = (const U8 *)pFont->p.pFontData + 4 /* Skip XSize and XDist */;
  pfi->Baseline = GUI__Read16(&pData);
  pfi->LHeight  = GUI__Read16(&pData);
  pfi->CHeight  = GUI__Read16(&pData);
  pfi->Flags    = GUI_FONTINFO_FLAG_PROP;
}

/*********************************************************************
*
*       GUI_SIF_IsInFont
*/
static char _GUI_SIF_IsInFont(const GUI_FONT GUI_UNI_PTR * pFont, U16 c) {
  const U8 * pCharInfo;
  GUI_USE_PARA(pFont);
  pCharInfo = _GetpCharInfo(GUI_Context.pAFont, c);
  return (pCharInfo) ? 1 : 0;
}

/*********************************************************************
*
*       GUI_SIF_TYPE_PROP
*/
const tGUI_SIF_APIList GUI_SIF_APIList_Prop = {
  _GUI_SIF_DispChar,
  _GUI_SIF_GetCharDistX,
  _GUI_SIF_GetFontInfo,
  _GUI_SIF_IsInFont
};
