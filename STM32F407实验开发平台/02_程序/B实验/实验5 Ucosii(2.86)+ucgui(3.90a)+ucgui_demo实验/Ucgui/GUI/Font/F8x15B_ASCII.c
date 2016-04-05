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
File        : F8x15B.C
Purpose     : Monospaced Bold Font similar to the fixed system font
Height      : 15
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_32[15] = { /* code 32 */
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

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_33[15] = { /* code 33 */
  ________,
  ________,
  ________,
  ___XX___,
  __XXXX__,
  __XXXX__,
  __XXXX__,
  ___XX___,
  ___XX___,
  ________,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_34[15] = { /* code 34 */
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_35[15] = { /* code 35 */
  ________,
  ________,
  ________,
  __XX_XX_,
  __XX_XX_,
  _XXXXXXX,
  __XX_XX_,
  __XX_XX_,
  __XX_XX_,
  _XXXXXXX,
  __XX_XX_,
  __XX_XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_36[15] = { /* code 36 */
  ________,
  ___XX___,
  ___XX___,
  __XXXX__,
  _XX__XX_,
  _XX_____,
  __XX____,
  ___XX___,
  ____XX__,
  _____XX_,
  _XX__XX_,
  __XXXX__,
  ___XX___,
  ___XX___,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_37[15] = { /* code 37 */
  ________,
  ________,
  _XXX____,
  XX_XX___,
  XX_XX_X_,
  _XXX_XX_,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_XXX_,
  _X_XX_XX,
  ___XX_XX,
  ____XXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_38[15] = { /* code 38 */
  ________,
  ________,
  ________,
  __XXX___,
  _XX_XX__,
  _XX_XX__,
  __XXX___,
  _XX_____,
  _XX_XXXX,
  _XX__XX_,
  _XX__XX_,
  __XXX_XX,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_39[15] = { /* code 39 */
  ________,
  ________,
  ________,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_40[15] = { /* code 40 */
  ________,
  ________,
  ________,
  ____XX__,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  ___XX___,
  ___XX___,
  ____XX__,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_41[15] = { /* code 41 */
  ________,
  ________,
  ________,
  __XX____,
  ___XX___,
  ___XX___,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ___XX___,
  ___XX___,
  __XX____,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_42[15] = { /* code 42 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XX_XX_,
  ___XXX__,
  _XXXXXXX,
  ___XXX__,
  __XX_XX_,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_43[15] = { /* code 43 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ___XX___,
  ___XX___,
  _XXXXXX_,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_44[15] = { /* code 44 */
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
  ___XXX__,
  ___XXX__,
  ____XX__,
  ___XX___,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_45[15] = { /* code 45 */
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
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_46[15] = { /* code 46 */
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
  ___XXX__,
  ___XXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_47[15] = { /* code 47 */
  ________,
  ________,
  ________,
  _____XX_,
  _____XX_,
  ____XX__,
  ____XX__,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  _XX_____,
  _XX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_48[15] = { /* code 48 */
  ________,
  ________,
  ________,
  ___XXXX_,
  __XX__XX,
  __XX_XXX,
  __XX_XXX,
  __XX__XX,
  __XXX_XX,
  __XXX_XX,
  __XX__XX,
  ___XXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_49[15] = { /* code 49 */
  ________,
  ________,
  ________,
  ____XX__,
  ___XXX__,
  _XXXXX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_50[15] = { /* code 50 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _____XX_,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_51[15] = { /* code 51 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _____XX_,
  ___XXX__,
  _____XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_52[15] = { /* code 52 */
  ________,
  ________,
  ________,
  __XX____,
  __XX____,
  __XX_XX_,
  __XX_XX_,
  __XX_XX_,
  _XX__XX_,
  _XXXXXXX,
  _____XX_,
  _____XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_53[15] = { /* code 53 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXXXX__,
  _____XX_,
  _____XX_,
  ____XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_54[15] = { /* code 54 */
  ________,
  ________,
  ________,
  ___XXX__,
  ___XX___,
  __XX____,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_55[15] = { /* code 55 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  _____XX_,
  ____XX__,
  ____XX__,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  __XX____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_56[15] = { /* code 56 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XXX_XX_,
  __XXXX__,
  _XX_XXX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_57[15] = { /* code 57 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXXX_,
  ____XX__,
  ___XX___,
  __XXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_58[15] = { /* code 58 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ___XXX__,
  ___XXX__,
  ________,
  ________,
  ________,
  ___XXX__,
  ___XXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_59[15] = { /* code 59 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ___XXX__,
  ___XXX__,
  ________,
  ________,
  ________,
  ___XXX__,
  ___XXX__,
  ____XX__,
  ___XX___,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_60[15] = { /* code 60 */
  ________,
  ________,
  ________,
  _____XX_,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  __XX____,
  ___XX___,
  ____XX__,
  _____XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_61[15] = { /* code 61 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  ________,
  _XXXXXX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_62[15] = { /* code 62 */
  ________,
  ________,
  ________,
  _XX_____,
  __XX____,
  ___XX___,
  ____XX__,
  _____XX_,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_63[15] = { /* code 63 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  ____XX__,
  ___XX___,
  ___XX___,
  ________,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_64[15] = { /* code 64 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  XX____XX,
  XX____XX,
  XX__XXXX,
  XX_XX_XX,
  XX_XX_XX,
  XX__XXXX,
  XX______,
  _XXXXXXX,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_65[15] = { /* code 65 */
  ________,
  ________,
  ________,
  ___XX___,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXXX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_66[15] = { /* code 66 */
  ________,
  ________,
  ________,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_67[15] = { /* code 67 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_68[15] = { /* code 68 */
  ________,
  ________,
  ________,
  _XXXX___,
  _XX_XX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX_XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_69[15] = { /* code 69 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXXXX__,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_70[15] = { /* code 70 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXXXX__,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_71[15] = { /* code 71 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX_____,
  _XX_____,
  _XX_XXX_,
  _XX__XX_,
  _XX__XX_,
  __XXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_72[15] = { /* code 72 */
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXXX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_73[15] = { /* code 73 */
  ________,
  ________,
  ________,
  __XXXX__,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_74[15] = { /* code 74 */
  ________,
  ________,
  ________,
  _____XX_,
  _____XX_,
  _____XX_,
  _____XX_,
  _____XX_,
  _____XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_75[15] = { /* code 75 */
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX_XX__,
  _XX_XX__,
  _XXXX___,
  _XX_XX__,
  _XX_XX__,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_76[15] = { /* code 76 */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_77[15] = { /* code 77 */
  ________,
  ________,
  ________,
  _XX___XX,
  _XX___XX,
  _XXX_XXX,
  _XX_X_XX,
  _XX_X_XX,
  _XX_X_XX,
  _XX___XX,
  _XX___XX,
  _XX___XX,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_78[15] = { /* code 78 */
  ________,
  ________,
  ________,
  _XX___XX,
  _XX___XX,
  _XXX__XX,
  _XXXX_XX,
  _XX_XXXX,
  _XX__XXX,
  _XX___XX,
  _XX___XX,
  _XX___XX,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_79[15] = { /* code 79 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_80[15] = { /* code 80 */
  ________,
  ________,
  ________,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_81[15] = { /* code 81 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ____XX__,
  _____XX_,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_82[15] = { /* code 82 */
  ________,
  ________,
  ________,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  _XX_XX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_83[15] = { /* code 83 */
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX_____,
  __XX____,
  ___XX___,
  ____XX__,
  _____XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_84[15] = { /* code 84 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_85[15] = { /* code 85 */
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_86[15] = { /* code 86 */
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_87[15] = { /* code 87 */
  ________,
  ________,
  ________,
  _XX___XX,
  _XX___XX,
  _XX___XX,
  _XX_X_XX,
  _XX_X_XX,
  _XX_X_XX,
  __XX_XX_,
  __XX_XX_,
  __XX_XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_88[15] = { /* code 88 */
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  __XX_X__,
  ___XX___,
  ___XX___,
  __X_XX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_89[15] = { /* code 89 */
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_90[15] = { /* code 90 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  _____XX_,
  _____XX_,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  _XX_____,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_91[15] = { /* code 91 */
  ________,
  ________,
  ________,
  __XXXX__,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XXXX__};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_92[15] = { /* code 92 */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  __XX____,
  __XX____,
  ___XX___,
  ___XX___,
  ____XX__,
  ____XX__,
  _____XX_,
  _____XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_93[15] = { /* code 93 */
  ________,
  ________,
  ________,
  __XXXX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  __XXXX__};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_94[15] = { /* code 94 */
  ________,
  ___XX___,
  __XXXX__,
  _XX__XX_,
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

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_95[15] = { /* code 95 */
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
  XXXXXXXX};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_96[15] = { /* code 96 */
  ________,
  __XXX___,
  ___XX___,
  ____XX__,
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

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_97[15] = { /* code 97 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXX__,
  _____XX_,
  _____XX_,
  __XXXXX_,
  _XX__XX_,
  _XX__XX_,
  __XXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_98[15] = { /* code 98 */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_99[15] = { /* code 99 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_100[15] = { /* code 100 */
  ________,
  ________,
  ________,
  _____XX_,
  _____XX_,
  __XXXXX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_101[15] = { /* code 101 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XXXXXX_,
  _XX_____,
  _XX_____,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_102[15] = { /* code 102 */
  ________,
  ________,
  ________,
  ___XXXX_,
  __XX____,
  __XX____,
  __XX____,
  _XXXXXX_,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_103[15] = { /* code 103 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXXX_,
  _____XX_,
  _____XX_,
  _XXXXX__};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_104[15] = { /* code 104 */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_105[15] = { /* code 105 */
  ________,
  ________,
  ___XX___,
  ___XX___,
  ________,
  _XXXX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_106[15] = { /* code 106 */
  ________,
  ________,
  ____XX__,
  ____XX__,
  ________,
  __XXXX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_107[15] = { /* code 107 */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  _XX__XX_,
  _XX__XX_,
  _XX_XX__,
  _XXXX___,
  _XX_XX__,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_108[15] = { /* code 108 */
  ________,
  ________,
  ________,
  _XXXX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_109[15] = { /* code 109 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  _XX_X_XX,
  _XX_X_XX,
  _XX_X_XX,
  _XX_X_XX,
  _XX_X_XX,
  _XX___XX,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_110[15] = { /* code 110 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_111[15] = { /* code 111 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_112[15] = { /* code 112 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  _XX_____,
  _XX_____,
  _XX_____};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_113[15] = { /* code 113 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXXX_,
  _____XX_,
  _____XX_,
  _____XX_};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_114[15] = { /* code 114 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX_XXX_,
  _XXX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_115[15] = { /* code 115 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _XX_____,
  _XX_____,
  __XXXX__,
  _____XX_,
  _____XX_,
  _XXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_116[15] = { /* code 116 */
  ________,
  ________,
  ________,
  __XX____,
  __XX____,
  _XXXXXX_,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  ___XXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_117[15] = { /* code 117 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_118[15] = { /* code 118 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_119[15] = { /* code 119 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX___XX,
  _XX_X_XX,
  _XX_X_XX,
  _XX_X_XX,
  _XX_X_XX,
  __XX_XX_,
  __XX_XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_120[15] = { /* code 120 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ___XX___,
  __XXXX__,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_121[15] = { /* code 121 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ____XX__,
  ___XX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_122[15] = { /* code 122 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  _____XX_,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_123[15] = { /* code 123 */
  ________,
  ________,
  ________,
  ____XX__,
  ___XX___,
  ___XX___,
  ___XX___,
  __XX____,
  _XX_____,
  __XX____,
  ___XX___,
  ___XX___,
  ___XX___,
  ____XX__,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_124[15] = { /* code 124 */
  ________,
  ________,
  ________,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_125[15] = { /* code 125 */
  ________,
  ________,
  ________,
  __XX____,
  ___XX___,
  ___XX___,
  ___XX___,
  ____XX__,
  _____XX_,
  ____XX__,
  ___XX___,
  ___XX___,
  ___XX___,
  __XX____,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_126[15] = { /* code 126 */
  ________,
  ________,
  ________,
  _XXX___X,
  XX_XX_XX,
  X___XXX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x15B_ASCII_127[15] = { /* code 127 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  _XXXXXX_,
  _XXXXXX_,
  _XXXXXX_,
  _XXXXXX_,
  _XXXXXX_,
  _XXXXXX_,
  _XXXXXX_,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE GUI_CHARINFO GUI_CharInfoF8x15B_ASCII[96] = {
   {   8,   8,  1, acF8x15B_ASCII_32 } /* code  32 */
  ,{   8,   8,  1, acF8x15B_ASCII_33 } /* code  33 */
  ,{   8,   8,  1, acF8x15B_ASCII_34 } /* code  34 */
  ,{   8,   8,  1, acF8x15B_ASCII_35 } /* code  35 */
  ,{   8,   8,  1, acF8x15B_ASCII_36 } /* code  36 */
  ,{   8,   8,  1, acF8x15B_ASCII_37 } /* code  37 */
  ,{   8,   8,  1, acF8x15B_ASCII_38 } /* code  38 */
  ,{   8,   8,  1, acF8x15B_ASCII_39 } /* code  39 */
  ,{   8,   8,  1, acF8x15B_ASCII_40 } /* code  40 */
  ,{   8,   8,  1, acF8x15B_ASCII_41 } /* code  41 */
  ,{   8,   8,  1, acF8x15B_ASCII_42 } /* code  42 */
  ,{   8,   8,  1, acF8x15B_ASCII_43 } /* code  43 */
  ,{   8,   8,  1, acF8x15B_ASCII_44 } /* code  44 */
  ,{   8,   8,  1, acF8x15B_ASCII_45 } /* code  45 */
  ,{   8,   8,  1, acF8x15B_ASCII_46 } /* code  46 */
  ,{   8,   8,  1, acF8x15B_ASCII_47 } /* code  47 */
  ,{   8,   8,  1, acF8x15B_ASCII_48 } /* code  48 */
  ,{   8,   8,  1, acF8x15B_ASCII_49 } /* code  49 */
  ,{   8,   8,  1, acF8x15B_ASCII_50 } /* code  50 */
  ,{   8,   8,  1, acF8x15B_ASCII_51 } /* code  51 */
  ,{   8,   8,  1, acF8x15B_ASCII_52 } /* code  52 */
  ,{   8,   8,  1, acF8x15B_ASCII_53 } /* code  53 */
  ,{   8,   8,  1, acF8x15B_ASCII_54 } /* code  54 */
  ,{   8,   8,  1, acF8x15B_ASCII_55 } /* code  55 */
  ,{   8,   8,  1, acF8x15B_ASCII_56 } /* code  56 */
  ,{   8,   8,  1, acF8x15B_ASCII_57 } /* code  57 */
  ,{   8,   8,  1, acF8x15B_ASCII_58 } /* code  58 */
  ,{   8,   8,  1, acF8x15B_ASCII_59 } /* code  59 */
  ,{   8,   8,  1, acF8x15B_ASCII_60 } /* code  60 */
  ,{   8,   8,  1, acF8x15B_ASCII_61 } /* code  61 */
  ,{   8,   8,  1, acF8x15B_ASCII_62 } /* code  62 */
  ,{   8,   8,  1, acF8x15B_ASCII_63 } /* code  63 */
  ,{   8,   8,  1, acF8x15B_ASCII_64 } /* code  64 */
  ,{   8,   8,  1, acF8x15B_ASCII_65 } /* code  65 */
  ,{   8,   8,  1, acF8x15B_ASCII_66 } /* code  66 */
  ,{   8,   8,  1, acF8x15B_ASCII_67 } /* code  67 */
  ,{   8,   8,  1, acF8x15B_ASCII_68 } /* code  68 */
  ,{   8,   8,  1, acF8x15B_ASCII_69 } /* code  69 */
  ,{   8,   8,  1, acF8x15B_ASCII_70 } /* code  70 */
  ,{   8,   8,  1, acF8x15B_ASCII_71 } /* code  71 */
  ,{   8,   8,  1, acF8x15B_ASCII_72 } /* code  72 */
  ,{   8,   8,  1, acF8x15B_ASCII_73 } /* code  73 */
  ,{   8,   8,  1, acF8x15B_ASCII_74 } /* code  74 */
  ,{   8,   8,  1, acF8x15B_ASCII_75 } /* code  75 */
  ,{   8,   8,  1, acF8x15B_ASCII_76 } /* code  76 */
  ,{   8,   8,  1, acF8x15B_ASCII_77 } /* code  77 */
  ,{   8,   8,  1, acF8x15B_ASCII_78 } /* code  78 */
  ,{   8,   8,  1, acF8x15B_ASCII_79 } /* code  79 */
  ,{   8,   8,  1, acF8x15B_ASCII_80 } /* code  80 */
  ,{   8,   8,  1, acF8x15B_ASCII_81 } /* code  81 */
  ,{   8,   8,  1, acF8x15B_ASCII_82 } /* code  82 */
  ,{   8,   8,  1, acF8x15B_ASCII_83 } /* code  83 */
  ,{   8,   8,  1, acF8x15B_ASCII_84 } /* code  84 */
  ,{   8,   8,  1, acF8x15B_ASCII_85 } /* code  85 */
  ,{   8,   8,  1, acF8x15B_ASCII_86 } /* code  86 */
  ,{   8,   8,  1, acF8x15B_ASCII_87 } /* code  87 */
  ,{   8,   8,  1, acF8x15B_ASCII_88 } /* code  88 */
  ,{   8,   8,  1, acF8x15B_ASCII_89 } /* code  89 */
  ,{   8,   8,  1, acF8x15B_ASCII_90 } /* code  90 */
  ,{   8,   8,  1, acF8x15B_ASCII_91 } /* code  91 */
  ,{   8,   8,  1, acF8x15B_ASCII_92 } /* code  92 */
  ,{   8,   8,  1, acF8x15B_ASCII_93 } /* code  93 */
  ,{   8,   8,  1, acF8x15B_ASCII_94 } /* code  94 */
  ,{   8,   8,  1, acF8x15B_ASCII_95 } /* code  95 */
  ,{   8,   8,  1, acF8x15B_ASCII_96 } /* code  96 */
  ,{   8,   8,  1, acF8x15B_ASCII_97 } /* code  97 */
  ,{   8,   8,  1, acF8x15B_ASCII_98 } /* code  98 */
  ,{   8,   8,  1, acF8x15B_ASCII_99 } /* code  99 */
  ,{   8,   8,  1, acF8x15B_ASCII_100 } /* code 100 */
  ,{   8,   8,  1, acF8x15B_ASCII_101 } /* code 101 */
  ,{   8,   8,  1, acF8x15B_ASCII_102 } /* code 102 */
  ,{   8,   8,  1, acF8x15B_ASCII_103 } /* code 103 */
  ,{   8,   8,  1, acF8x15B_ASCII_104 } /* code 104 */
  ,{   8,   8,  1, acF8x15B_ASCII_105 } /* code 105 */
  ,{   8,   8,  1, acF8x15B_ASCII_106 } /* code 106 */
  ,{   8,   8,  1, acF8x15B_ASCII_107 } /* code 107 */
  ,{   8,   8,  1, acF8x15B_ASCII_108 } /* code 108 */
  ,{   8,   8,  1, acF8x15B_ASCII_109 } /* code 109 */
  ,{   8,   8,  1, acF8x15B_ASCII_110 } /* code 110 */
  ,{   8,   8,  1, acF8x15B_ASCII_111 } /* code 111 */
  ,{   8,   8,  1, acF8x15B_ASCII_112 } /* code 112 */
  ,{   8,   8,  1, acF8x15B_ASCII_113 } /* code 113 */
  ,{   8,   8,  1, acF8x15B_ASCII_114 } /* code 114 */
  ,{   8,   8,  1, acF8x15B_ASCII_115 } /* code 115 */
  ,{   8,   8,  1, acF8x15B_ASCII_116 } /* code 116 */
  ,{   8,   8,  1, acF8x15B_ASCII_117 } /* code 117 */
  ,{   8,   8,  1, acF8x15B_ASCII_118 } /* code 118 */
  ,{   8,   8,  1, acF8x15B_ASCII_119 } /* code 119 */
  ,{   8,   8,  1, acF8x15B_ASCII_120 } /* code 120 */
  ,{   8,   8,  1, acF8x15B_ASCII_121 } /* code 121 */
  ,{   8,   8,  1, acF8x15B_ASCII_122 } /* code 122 */
  ,{   8,   8,  1, acF8x15B_ASCII_123 } /* code 123 */
  ,{   8,   8,  1, acF8x15B_ASCII_124 } /* code 124 */
  ,{   8,   8,  1, acF8x15B_ASCII_125 } /* code 125 */
  ,{   8,   8,  1, acF8x15B_ASCII_126 } /* code 126 */
  ,{   8,   8,  1, acF8x15B_ASCII_127 } /* code 127 */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontPropF8x15B_ASCII_1 = {
   32                         /* first character               */
  ,127                        /* last character                */
  ,GUI_CharInfoF8x15B_ASCII   /* address of first character    */
  ,(GUI_CONST_STORAGE GUI_FONT_PROP*)0    /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font8x15B_ASCII = {
   GUI_FONTTYPE_PROP  /* type of font    */
  ,15                 /* height of font  */
  ,15                 /* space of font y */
  ,1                  /* magnification x */
  ,1                  /* magnification y */
  ,{&GUI_FontPropF8x15B_ASCII_1}
  , 12, 7, 9
};

