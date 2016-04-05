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
File        : F16_1HK.C
Purpose     : ASCII, West European, Hiragana & Katakana
Height      : 16
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"


GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font16_1HK_Prop2 = {
   0x30A1                                         /* first character               */
  ,0x30F6                                         /* last character                */
  ,&GUI_Font16_HK_CharInfo[83]                    /* address of first character    */
  ,(const GUI_FONT_PROP GUI_UNI_PTR *)&GUI_Font16_1_FontProp1  /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font16_1HK_Prop1 = {
   0x3041                                       /* first character               */
  ,0x3093                                       /* last character                */
  ,&GUI_Font16_HK_CharInfo[0]                   /* address of first character    */
  ,(const GUI_FONT_PROP GUI_UNI_PTR *)&GUI_Font16_1HK_Prop2  /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font16_1HK = {
   GUI_FONTTYPE_PROP  /* type of font    */
  ,16                 /* height of font  */
  ,16                 /* space of font y */
  ,1                  /* magnification x */
  ,1                  /* magnification y */
  ,{(const GUI_FONT_PROP GUI_UNI_PTR *)&GUI_Font16_1HK_Prop1}
  , 13, 7, 10
};

