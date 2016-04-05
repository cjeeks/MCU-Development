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
File        : GUIDEMO_Font.c
Purpose     : GUIDEMO font routines
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "GUI.h"
#include "GUIDEMO.h"

/*********************************************************************
*
*       Japanese SJIS font
*
**********************************************************************
*/

/* SPACE */
static const unsigned char _acFontSJIS16_0020[ 16] = { /* code 0020 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

/* HYPHEN-MINUS */
static const unsigned char _acFontSJIS16_002D[ 16] = { /* code 002D */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

/* QUESTION MARK */
static const unsigned char _acFontSJIS16_003F[ 16] = { /* code 003F */
  ________,
  ___XX___,
  __X__X__,
  _XX___X_,
  _XX___X_,
  ______X_,
  _____X__,
  ____X___,
  ___X____,
  ___X____,
  ________,
  ________,
  ___X____,
  __XXX___,
  ___X____,
  ________};

/* LATIN CAPITAL LETTER H */
static const unsigned char _acFontSJIS16_0048[ 16] = { /* code 0048 */
  ________,
  XXX_XXX_,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _XXXXX__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  XXX_XXX_,
  ________,
  ________};

/* LATIN CAPITAL LETTER L */
static const unsigned char _acFontSJIS16_004C[ 16] = { /* code 004C */
  ________,
  XXX_____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X____X_,
  _X____X_,
  XXXXXXX_,
  ________,
  ________};

/* LATIN SMALL LETTER A */
static const unsigned char _acFontSJIS16_0061[ 16] = { /* code 0061 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  X____X__,
  X____X__,
  __XXXX__,
  _X___X__,
  X____X__,
  X___XX__,
  _XXX_XX_,
  ________,
  ________};

/* LATIN SMALL LETTER E */
static const unsigned char _acFontSJIS16_0065[ 16] = { /* code 0065 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ___XX___,
  __X__X__,
  _X____X_,
  _XXXXXX_,
  _X______,
  _X______,
  __X___X_,
  ___XXX__,
  ________,
  ________};

/* LATIN SMALL LETTER L */
static const unsigned char _acFontSJIS16_006C[ 16] = { /* code 006C */
  ________,
  __XX____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  __XXX___,
  ________,
  ________};

/* LATIN SMALL LETTER N */
static const unsigned char _acFontSJIS16_006E[ 16] = { /* code 006E */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX_XX___,
  _XX__X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  XXX_XXX_,
  ________,
  ________};

/* LATIN SMALL LETTER O */
static const unsigned char _acFontSJIS16_006F[ 16] = { /* code 006F */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ___XX___,
  __X__X__,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  __X__X__,
  ___XX___,
  ________,
  ________};

/* LATIN SMALL LETTER R */
static const unsigned char _acFontSJIS16_0072[ 16] = { /* code 0072 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_XX__,
  __XX__X_,
  __X___X_,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  _XXX____,
  ________,
  ________};

/* LATIN SMALL LETTER S */
static const unsigned char _acFontSJIS16_0073[ 16] = { /* code 0073 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX_X_,
  X____XX_,
  X_____X_,
  _XX_____,
  ___XXX__,
  X_____X_,
  XX____X_,
  X_XXXX__,
  ________,
  ________};

/* LATIN SMALL LETTER U */
static const unsigned char _acFontSJIS16_0075[ 16] = { /* code 0075 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X__XX__,
  __XX_XX_,
  ________,
  ________};

/* LATIN SMALL LETTER W */
static const unsigned char _acFontSJIS16_0077[ 16] = { /* code 0077 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX_X_XX_,
  X__X__X_,
  X__X__X_,
  X_X_X_X_,
  X_X_X_X_,
  _X___X__,
  _X___X__,
  _X___X__,
  ________,
  ________};

/* LATIN SMALL LETTER X */
static const unsigned char _acFontSJIS16_0078[ 16] = { /* code 0078 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  _X___X__,
  __X_X___,
  ___X____,
  ___X____,
  __X_X___,
  _X___X__,
  XX___XX_,
  ________,
  ________};

/* LATIN SMALL LETTER Y */
static const unsigned char _acFontSJIS16_0079[ 16] = { /* code 0079 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXX_XXX_,
  _X___X__,
  _X___X__,
  __X_X___,
  __X_X___,
  __XX____,
  ___X____,
  X_X_____,
  XX______,
  ________};

/* IDEOGRAPHIC SPACE */
static const unsigned char _acFontSJIS16_8140[ 32] = { /* code 8140 */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

/* FULLWIDTH QUESTION MARK */
static const unsigned char _acFontSJIS16_8148[ 32] = { /* code 8148 */
  ________,________,
  ______XX,X_______,
  _____X__,_X______,
  ____X___,__X_____,
  ____XX__,__X_____,
  ________,_X______,
  ________,X_______,
  _______X,________,
  _______X,________,
  _______X,________,
  ________,________,
  ________,________,
  _______X,________,
  _______X,________,
  ________,________,
  ________,________};

/* HIRAGANA LETTER O */
static const unsigned char _acFontSJIS16_82A8[ 32] = { /* code 82A8 */
  ____XX__,________,
  _____XX_,________,
  _____X__,X__XX___,
  _X___XXX,_____X__,
  __XXXX__,______X_,
  _____X__,______X_,
  _____X_X,XXXX____,
  _____XX_,____X___,
  ____XX__,_____X__,
  ___X_X__,_____X__,
  _XX__X__,_____X__,
  ___X_X__,X___X___,
  ____XX__,_XXX____,
  _____X__,________,
  ________,________,
  ________,________};

/* HIRAGANA LETTER KA */
static const unsigned char _acFontSJIS16_82A9[ 32] = { /* code 82A9 */
  ________,________,
  ____XX__,________,
  _____XX_,________,
  _____X__,________,
  _X___XXX,X__XX___,
  _XXXXX__,_X___X__,
  ____X___,_X____X_,
  ____X___,_X____X_,
  ____X___,_X__XXX_,
  ___X____,_X____X_,
  ___X_X__,_X______,
  __X___X_,X_______,
  _XX____X,X_______,
  _X_____X,________,
  ________,________,
  ________,________};

/* HIRAGANA LETTER KO */
static const unsigned char _acFontSJIS16_82B1[ 32] = { /* code 82B1 */
  ________,________,
  ________,________,
  ____X___,________,
  _____XXX,XXXX____,
  ________,XX______,
  _______X,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  __X_____,________,
  ___X____,________,
  ___XX___,________,
  _____XXX,XXXXX___,
  ________,________,
  ________,________};

/* HIRAGANA LETTER SA */
static const unsigned char _acFontSJIS16_82B3[ 32] = { /* code 82B3 */
  _______X,X_______,
  ________,X_______,
  ________,X_______,
  __X_____,_X_XX___,
  ___XXXXX,XXX_____,
  ________,_X______,
  ________,__X_____,
  ____XXXX,X_X_____,
  ___X____,_XXX____,
  __X_____,___X____,
  __X_____,________,
  __X_____,________,
  ___XX___,________,
  _____XXX,XX______,
  ________,________,
  ________,________};

/* HIRAGANA LETTER SU */
static const unsigned char _acFontSJIS16_82B7[ 32] = { /* code 82B7 */
  _______X,X_______,
  ________,XX______,
  ________,X___X___,
  XX__XXXX,XXXXXX__,
  _XXX____,X_______,
  _____XX_,X_______,
  ____X__X,X_______,
  ____X___,X_______,
  ____X___,X_______,
  ____X__X,X_______,
  _____XX_,X_______,
  _______X,________,
  _______X,________,
  ______X_,________,
  _____X__,________,
  ________,________};

/* HIRAGANA LETTER TI */
static const unsigned char _acFontSJIS16_82BF[ 32] = { /* code 82BF */
  ________,________,
  ____XX__,________,
  _____X__,_XX_____,
  _X___XXX,X_______,
  __XXXX__,________,
  ____X___,________,
  ____X___,________,
  ____X__X,XXX_____,
  ___XXXX_,___X____,
  ___XX___,____X___,
  ___X____,____X___,
  ________,____X___,
  ________,___X____,
  ________,__XX____,
  _____XXX,XX______,
  ________,________};

/* HIRAGANA LETTER DE */
static const unsigned char _acFontSJIS16_82C5[ 32] = { /* code 82C5 */
  ________,________,
  ________,________,
  _X____XX,XXXXXX__,
  __XXXX__,_XX_____,
  ________,X____X__,
  _______X,___X__X_,
  ______X_,____X___,
  ______X_,________,
  _____X__,________,
  _____X__,________,
  _____X__,________,
  ______X_,________,
  ______XX,__X_____,
  ________,XXXX____,
  ________,________,
  ________,________};

/* HIRAGANA LETTER NI */
static const unsigned char _acFontSJIS16_82C9[ 32] = { /* code 82C9 */
  ________,________,
  _XX_____,________,
  __XX____,________,
  __X_____,_XXXX___,
  __X____X,X_______,
  _X______,________,
  _X______,________,
  _X______,________,
  _X__X___,________,
  _X__X_X_,________,
  _X_X__X_,________,
  _X_X___X,X_______,
  __XX____,_XXXXX__,
  ___XX___,________,
  ________,________,
  ________,________};

/* HIRAGANA LETTER HA */
static const unsigned char _acFontSJIS16_82CD[ 32] = { /* code 82CD */
  ________,________,
  _XX_____,__XX____,
  __XX____,___X____,
  __X___X_,___XXX__,
  __X____X,XXXX____,
  _X______,___X____,
  _X______,___X____,
  _X______,___X____,
  _X__X___,___X____,
  _X_X____,___X____,
  _X_X___X,XXXX____,
  _XXX__X_,___XX___,
  __X___X_,___X_X__,
  __X____X,XXX_____,
  ________,________,
  ________,________};

/* HIRAGANA LETTER N */
static const unsigned char _acFontSJIS16_82F1[ 32] = { /* code 82F1 */
  ________,________,
  _____XX_,________,
  ______XX,________,
  ______X_,________,
  _____X__,________,
  _____X__,________,
  ____X___,________,
  ____XXX_,________,
  ___XX__X,________,
  ___X___X,_____X__,
  __XX____,X____X__,
  __X_____,X____X__,
  _XX_____,X___X___,
  _X______,_XXX____,
  ________,________,
  ________,________};

/* KATAKANA LETTER KU */
static const unsigned char _acFontSJIS16_834E[ 32] = { /* code 834E */
  ________,________,
  _____XX_,________,
  ______XX,________,
  ______X_,___X____,
  _____XXX,XXXXX___,
  _____X__,___X____,
  ____X___,___X____,
  ___X____,__X_____,
  __X_____,__X_____,
  ________,_X______,
  ________,X_______,
  _______X,________,
  _____XX_,________,
  ___XX___,________,
  ________,________,
  ________,________};

/* KATAKANA LETTER SU */
static const unsigned char _acFontSJIS16_8358[ 32] = { /* code 8358 */
  ________,________,
  ________,________,
  ________,________,
  ________,__X_____,
  __XXXXXX,XXXX____,
  ___X____,__X_____,
  ________,_X______,
  ________,X_______,
  ________,X_______,
  _______X,_X______,
  ______X_,__X_____,
  _____X__,___X____,
  ___XX___,___XX___,
  _XX_____,____X___,
  ________,________,
  ________,________};

/* KATAKANA LETTER SMALL TU */
static const unsigned char _acFontSJIS16_8362[ 32] = { /* code 8362 */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ______X_,__XX____,
  ___X___X,___XX___,
  ____X__X,___X____,
  ____X___,__X_____,
  ________,__X_____,
  ________,_X______,
  ________,X_______,
  ______XX,________,
  ____XX__,________,
  ________,________,
  ________,________};

/* KATAKANA LETTER RA */
static const unsigned char _acFontSJIS16_8389[ 32] = { /* code 8389 */
  ________,________,
  ________,__X_____,
  ___XXXXX,XXXX____,
  ____X___,________,
  ________,____X___,
  __XXXXXX,XXXXXX__,
  ___X____,____X___,
  ________,____X___,
  ________,___X____,
  ________,___X____,
  ________,__X_____,
  ________,_X______,
  _______X,X_______,
  ____XXX_,________,
  ________,________,
  ________,________};

/* <CJK> */
static const unsigned char _acFontSJIS16_8B43[ 32] = { /* code 8B43 */
  ___XX___,________,
  ___X____,___X____,
  __XXXXXX,XXXXX___,
  _X______,________,
  X__XXXXX,XXX_____,
  ________,________,
  _XXXXXXX,XXXX____,
  ________,___X____,
  _______X,X__X____,
  __XX___X,___X____,
  ____XXX_,___X____,
  ______X_,___X__X_,
  _____X_X,____X_X_,
  ___XX___,X___XX__,
  _XX_____,_____XX_,
  ________,________};

/* <CJK> */
static const unsigned char _acFontSJIS16_8CB3[ 32] = { /* code 8CB3 */
  ________,__X_____,
  __XXXXXX,XXXX____,
  ________,________,
  ________,________,
  ________,________,
  ________,____X___,
  XXXXXXXX,XXXXXX__,
  ____X___,X_______,
  ____X___,X_______,
  ____X___,X_______,
  ____X___,X_______,
  ___X____,X____X__,
  ___X____,X____X__,
  __X_____,X____XX_,
  XX______,_XXXXX__,
  ________,________};

static const GUI_CHARINFO _FontSJIS16_CharInfo[34] = {
   {   8,   8,  1, _acFontSJIS16_0020 } /* code 0020 */
  ,{   8,   8,  1, _acFontSJIS16_002D } /* code 002D */
  ,{   8,   8,  1, _acFontSJIS16_003F } /* code 003F */
  ,{   8,   8,  1, _acFontSJIS16_0048 } /* code 0048 */
  ,{   8,   8,  1, _acFontSJIS16_004C } /* code 004C */
  ,{   8,   8,  1, _acFontSJIS16_0061 } /* code 0061 */
  ,{   8,   8,  1, _acFontSJIS16_0065 } /* code 0065 */
  ,{   8,   8,  1, _acFontSJIS16_006C } /* code 006C */
  ,{   8,   8,  1, _acFontSJIS16_006E } /* code 006E */
  ,{   8,   8,  1, _acFontSJIS16_006F } /* code 006F */
  ,{   8,   8,  1, _acFontSJIS16_0072 } /* code 0072 */
  ,{   8,   8,  1, _acFontSJIS16_0073 } /* code 0073 */
  ,{   8,   8,  1, _acFontSJIS16_0075 } /* code 0075 */
  ,{   8,   8,  1, _acFontSJIS16_0077 } /* code 0077 */
  ,{   8,   8,  1, _acFontSJIS16_0078 } /* code 0078 */
  ,{   8,   8,  1, _acFontSJIS16_0079 } /* code 0079 */
  ,{  16,  16,  2, _acFontSJIS16_8140 } /* code 8140 */
  ,{  16,  16,  2, _acFontSJIS16_8148 } /* code 8148 */
  ,{  16,  16,  2, _acFontSJIS16_82A8 } /* code 82A8 */
  ,{  16,  16,  2, _acFontSJIS16_82A9 } /* code 82A9 */
  ,{  16,  16,  2, _acFontSJIS16_82B1 } /* code 82B1 */
  ,{  16,  16,  2, _acFontSJIS16_82B3 } /* code 82B3 */
  ,{  16,  16,  2, _acFontSJIS16_82B7 } /* code 82B7 */
  ,{  16,  16,  2, _acFontSJIS16_82BF } /* code 82BF */
  ,{  16,  16,  2, _acFontSJIS16_82C5 } /* code 82C5 */
  ,{  16,  16,  2, _acFontSJIS16_82C9 } /* code 82C9 */
  ,{  16,  16,  2, _acFontSJIS16_82CD } /* code 82CD */
  ,{  16,  16,  2, _acFontSJIS16_82F1 } /* code 82F1 */
  ,{  16,  16,  2, _acFontSJIS16_834E } /* code 834E */
  ,{  16,  16,  2, _acFontSJIS16_8358 } /* code 8358 */
  ,{  16,  16,  2, _acFontSJIS16_8362 } /* code 8362 */
  ,{  16,  16,  2, _acFontSJIS16_8389 } /* code 8389 */
  ,{  16,  16,  2, _acFontSJIS16_8B43 } /* code 8B43 */
  ,{  16,  16,  2, _acFontSJIS16_8CB3 } /* code 8CB3 */
};

static const GUI_FONT_PROP _FontSJIS16_Prop29 = {
   0x8CB3 /* first character */
  ,0x8CB3 /* last character  */
  ,&_FontSJIS16_CharInfo[ 33] /* address of first character */
  ,(const GUI_FONT_PROP*)0 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop28 = {
   0x8B43 /* first character */
  ,0x8B43 /* last character  */
  ,&_FontSJIS16_CharInfo[ 32] /* address of first character */
  ,&_FontSJIS16_Prop29 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop27 = {
   0x8389 /* first character */
  ,0x8389 /* last character  */
  ,&_FontSJIS16_CharInfo[ 31] /* address of first character */
  ,&_FontSJIS16_Prop28 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop26 = {
   0x8362 /* first character */
  ,0x8362 /* last character  */
  ,&_FontSJIS16_CharInfo[ 30] /* address of first character */
  ,&_FontSJIS16_Prop27 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop25 = {
   0x8358 /* first character */
  ,0x8358 /* last character  */
  ,&_FontSJIS16_CharInfo[ 29] /* address of first character */
  ,&_FontSJIS16_Prop26 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop24 = {
   0x834E /* first character */
  ,0x834E /* last character  */
  ,&_FontSJIS16_CharInfo[ 28] /* address of first character */
  ,&_FontSJIS16_Prop25 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop23 = {
   0x82F1 /* first character */
  ,0x82F1 /* last character  */
  ,&_FontSJIS16_CharInfo[ 27] /* address of first character */
  ,&_FontSJIS16_Prop24 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop22 = {
   0x82CD /* first character */
  ,0x82CD /* last character  */
  ,&_FontSJIS16_CharInfo[ 26] /* address of first character */
  ,&_FontSJIS16_Prop23 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop21 = {
   0x82C9 /* first character */
  ,0x82C9 /* last character  */
  ,&_FontSJIS16_CharInfo[ 25] /* address of first character */
  ,&_FontSJIS16_Prop22 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop20 = {
   0x82C5 /* first character */
  ,0x82C5 /* last character  */
  ,&_FontSJIS16_CharInfo[ 24] /* address of first character */
  ,&_FontSJIS16_Prop21 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop19 = {
   0x82BF /* first character */
  ,0x82BF /* last character  */
  ,&_FontSJIS16_CharInfo[ 23] /* address of first character */
  ,&_FontSJIS16_Prop20 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop18 = {
   0x82B7 /* first character */
  ,0x82B7 /* last character  */
  ,&_FontSJIS16_CharInfo[ 22] /* address of first character */
  ,&_FontSJIS16_Prop19 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop17 = {
   0x82B3 /* first character */
  ,0x82B3 /* last character  */
  ,&_FontSJIS16_CharInfo[ 21] /* address of first character */
  ,&_FontSJIS16_Prop18 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop16 = {
   0x82B1 /* first character */
  ,0x82B1 /* last character  */
  ,&_FontSJIS16_CharInfo[ 20] /* address of first character */
  ,&_FontSJIS16_Prop17 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop15 = {
   0x82A8 /* first character */
  ,0x82A9 /* last character  */
  ,&_FontSJIS16_CharInfo[ 18] /* address of first character */
  ,&_FontSJIS16_Prop16 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop14 = {
   0x8148 /* first character */
  ,0x8148 /* last character  */
  ,&_FontSJIS16_CharInfo[ 17] /* address of first character */
  ,&_FontSJIS16_Prop15 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop13 = {
   0x8140 /* first character */
  ,0x8140 /* last character  */
  ,&_FontSJIS16_CharInfo[ 16] /* address of first character */
  ,&_FontSJIS16_Prop14 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop12 = {
   0x0077 /* first character */
  ,0x0079 /* last character  */
  ,&_FontSJIS16_CharInfo[ 13] /* address of first character */
  ,&_FontSJIS16_Prop13 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop11 = {
   0x0075 /* first character */
  ,0x0075 /* last character  */
  ,&_FontSJIS16_CharInfo[ 12] /* address of first character */
  ,&_FontSJIS16_Prop12 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop10 = {
   0x0072 /* first character */
  ,0x0073 /* last character  */
  ,&_FontSJIS16_CharInfo[ 10] /* address of first character */
  ,&_FontSJIS16_Prop11 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop9 = {
   0x006E /* first character */
  ,0x006F /* last character  */
  ,&_FontSJIS16_CharInfo[  8] /* address of first character */
  ,&_FontSJIS16_Prop10 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop8 = {
   0x006C /* first character */
  ,0x006C /* last character  */
  ,&_FontSJIS16_CharInfo[  7] /* address of first character */
  ,&_FontSJIS16_Prop9 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop7 = {
   0x0065 /* first character */
  ,0x0065 /* last character  */
  ,&_FontSJIS16_CharInfo[  6] /* address of first character */
  ,&_FontSJIS16_Prop8 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop6 = {
   0x0061 /* first character */
  ,0x0061 /* last character  */
  ,&_FontSJIS16_CharInfo[  5] /* address of first character */
  ,&_FontSJIS16_Prop7 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop5 = {
   0x004C /* first character */
  ,0x004C /* last character  */
  ,&_FontSJIS16_CharInfo[  4] /* address of first character */
  ,&_FontSJIS16_Prop6 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop4 = {
   0x0048 /* first character */
  ,0x0048 /* last character  */
  ,&_FontSJIS16_CharInfo[  3] /* address of first character */
  ,&_FontSJIS16_Prop5 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop3 = {
   0x003F /* first character */
  ,0x003F /* last character  */
  ,&_FontSJIS16_CharInfo[  2] /* address of first character */
  ,&_FontSJIS16_Prop4 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop2 = {
   0x002D /* first character */
  ,0x002D /* last character  */
  ,&_FontSJIS16_CharInfo[  1] /* address of first character */
  ,&_FontSJIS16_Prop3 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT_PROP _FontSJIS16_Prop1 = {
   0x0020 /* first character */
  ,0x0020 /* last character  */
  ,&_FontSJIS16_CharInfo[  0] /* address of first character */
  ,&_FontSJIS16_Prop2 /* pointer to next GUI_FONT_PROP */
};

static const GUI_FONT _FontSJIS16 = {
   GUI_FONTTYPE_PROP_SJIS /* type of font    */
  ,16 /* height of font  */
  ,16 /* space of font y */
  ,1 /* magnification x */
  ,1 /* magnification y */
  ,{&_FontSJIS16_Prop1}
};

/*********************************************************************
*
*       Static variables
*
**********************************************************************
*/

static const GUI_FONT * _apPropFonts[] = {
  &GUI_Font10S_ASCII,
  &GUI_Font8_ASCII,
  &GUI_Font13_ASCII,
  &GUI_Font13H_ASCII,
  &GUI_Font16_ASCII,
  &GUI_Font13HB_ASCII,
  0
};

static const GUI_FONT * _apMonoFonts[] = {
  &GUI_Font4x6,
  &GUI_Font6x8,
  &GUI_Font8x13_ASCII,
  &GUI_Font8x8,
  &GUI_Font8x15B_ASCII,
  &GUI_Font8x16,
  0
};

static const GUI_FONT * _apDigitFonts[] = {
  &GUI_FontD32,
  0
};

static const char * _apSJIS[] = {
  "\x82\xa8\x8c\xb3\x8b\x43\x82\xc5\x82\xb7\x82\xa9\x81\x48\nHow are you?\x0",
};

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

static void _Label(const char * sText) {
  GUI_Clear();
  #if GUIDEMO_LARGE
    GUI_SetFont(&GUI_FontComic18B_ASCII);
    GUI_SetLBorder(5);
    GUI_DispStringAt(sText, 5, 5);
    GUI_SetLBorder(0);
  #else
    GUI_USE_PARA(sText);
  #endif
}

static int _GetYPos(void) {
  #if GUIDEMO_LARGE
    return 70;
  #else
    return 0;
  #endif
}

static void _ShowCharacters(const char*s, const GUI_FONT* pFont, int IncX) {
  int i;
  int ix=0, y;
  int FontSizeY;
  GUI_SetFont(pFont);
  FontSizeY = GUI_GetFontSizeY();
  _Label(s);
  GUI_SetFont(pFont);
  y = _GetYPos();
  for (i = 0; i < 20000; i++) {
    if (GUI_IsInFont(NULL, (U16)i)) {
      GUI_GotoXY(ix * IncX, y);
      if (ix++ > 20) {
        ix = 0;
        y += FontSizeY;
      }
    	GUI_DispChar((U16)i);
    }
  }
  GUIDEMO_Delay(2000);
  GUIDEMO_NotifyStartNext();
}

static void _ShowFonts(const char *s, const char *pMessage, const GUI_FONT **pPropFonts) {
  int i;
  _Label(s);
  GUI_GotoXY(0, _GetYPos());
  for (i=0;pPropFonts[i];i++) {
    GUI_SetFont(pPropFonts[i]);
    GUI_DispString(pMessage);
    GUI_DispNextLine();
  }
  GUIDEMO_Wait();
  GUIDEMO_NotifyStartNext();
}

static void _ShowJapaneseSample(void) {
  int i;
  _Label("Japanese text\nmixed with\nASCIItext");
  GUI_SetFont(&_FontSJIS16);
  for (i=0;i<sizeof(_apSJIS)/sizeof(_apSJIS[0]);i++) {
    GUI_DispStringHCenterAt(_apSJIS[i], LCD_GetXSize() / 2, _GetYPos() + 14);
    GUI_DispNextLine();
  }
  GUIDEMO_Delay(3000);
  GUIDEMO_NotifyStartNext();
}

/*********************************************************************
*
*       GUIDEMO_ShowInternationalFonts
*
**********************************************************************
*/

void GUIDEMO_ShowInternationalFonts(void) {
  GUIDEMO_ShowIntro("International fonts",
                    "emWin supports"
                    "\nUNICODE (all characters)"
                    "\nand Shift JIS (Japan)"
                    );
/* Show japanese text */
  _ShowJapaneseSample();
/* Show some character sets */
  _ShowCharacters("ASCII characters\n& European\nextensions", &GUI_Font13_1, 13);
  _ShowCharacters("Hiragana &\nKatakana", &GUI_Font16_HK, 16);
/* Show fonts */
  _ShowFonts("Proportional\nFonts", 
             "FontConverter available to create your own fonts...", 
             _apPropFonts);
  _ShowFonts("Monospaced\nFonts", 
             "Fonts with fixed character width...", 
             _apMonoFonts);
  #if !(GUIDEMO_TINY)
    _ShowFonts("Digits", "\n+- 0.1234", _apDigitFonts);
  #else
    _ShowFonts("Digits", "+-0.1234", _apDigitFonts);
  #endif
/* Show alignments */
  GUIDEMO_NotifyStartNext();
}
