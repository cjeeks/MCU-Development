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
File        : F8x13.C
Purpose     : Monospaced Font similar to courier
Height      : 13
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_32[13] = { /* code 32 */
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

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_33[13] = { /* code 33 */
  ________,
  ________,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ________,
  ____X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_34[13] = { /* code 34 */
  ________,
  ________,
  ___X_X__,
  ___X_X__,
  ___X_X__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_35[13] = { /* code 35 */
  ________,
  ________,
  ____X_X_,
  ____X_X_,
  __XXXXXX,
  ___X_X__,
  ___X_X__,
  ___X_X__,
  _XXXXXX_,
  __X_X___,
  __X_X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_36[13] = { /* code 36 */
  ________,
  ________,
  ____X___,
  ___XXX__,
  __X___X_,
  __X_____,
  ___XXX__,
  ______X_,
  __X___X_,
  ___XXX__,
  ____X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_37[13] = { /* code 37 */
  ________,
  ________,
  __X_____,
  _X_X___X,
  __X___X_,
  _____X__,
  ____X___,
  ___X____,
  __X___X_,
  _X___X_X,
  ______X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_38[13] = { /* code 38 */
  ________,
  ________,
  ___XX___,
  __X_____,
  __X_____,
  ___X____,
  __XX____,
  _X__X__X,
  _X__X_X_,
  _X___X__,
  __XXX_XX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_39[13] = { /* code 39 */
  ________,
  ________,
  ____X___,
  ____X___,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_40[13] = { /* code 40 */
  ________,
  ________,
  _____X__,
  ____X___,
  ____X___,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ____X___,
  ____X___,
  _____X__};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_41[13] = { /* code 41 */
  ________,
  ________,
  ___X____,
  ____X___,
  ____X___,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  ____X___,
  ____X___,
  ___X____};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_42[13] = { /* code 42 */
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
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_43[13] = { /* code 43 */
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ____X___,
  ____X___,
  _XXXXXXX,
  ____X___,
  ____X___,
  ____X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_44[13] = { /* code 44 */
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
  ____X___,
  ___X____,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_45[13] = { /* code 45 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXXX,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_46[13] = { /* code 46 */
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
  ____X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_47[13] = { /* code 47 */
  ________,
  ________,
  ________,
  _______X,
  ______X_,
  _____X__,
  ____X___,
  ___X____,
  __X_____,
  _X______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_48[13] = { /* code 48 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_49[13] = { /* code 49 */
  ________,
  ________,
  ____X___,
  __XXX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_50[13] = { /* code 50 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  ______X_,
  ______X_,
  _____X__,
  ____X___,
  ___X____,
  __X_____,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_51[13] = { /* code 51 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  ______X_,
  ______X_,
  ____XX__,
  ______X_,
  ______X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_52[13] = { /* code 52 */
  ________,
  ________,
  _____X__,
  ____XX__,
  ____XX__,
  ___X_X__,
  ___X_X__,
  __X__X__,
  __XXXXX_,
  _____X__,
  ____XXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_53[13] = { /* code 53 */
  ________,
  ________,
  __XXXXX_,
  __X_____,
  __X_____,
  __X_____,
  __XXXX__,
  ______X_,
  ______X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_54[13] = { /* code 54 */
  ________,
  ________,
  ____XX__,
  ___X____,
  __X_____,
  __X_____,
  __XXXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_55[13] = { /* code 55 */
  ________,
  ________,
  __XXXXX_,
  __X___X_,
  ______X_,
  _____X__,
  _____X__,
  ____X___,
  ____X___,
  ___X____,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_56[13] = { /* code 56 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_57[13] = { /* code 57 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXXX_,
  ______X_,
  ______X_,
  _____X__,
  ___XX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_58[13] = { /* code 58 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_59[13] = { /* code 59 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ____X___,
  ___X____,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_60[13] = { /* code 60 */
  ________,
  ________,
  ________,
  ________,
  _____X__,
  ____X___,
  ___X____,
  __X_____,
  ___X____,
  ____X___,
  _____X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_61[13] = { /* code 61 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  ________,
  __XXXXX_,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_62[13] = { /* code 62 */
  ________,
  ________,
  ________,
  ________,
  ___X____,
  ____X___,
  _____X__,
  ______X_,
  _____X__,
  ____X___,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_63[13] = { /* code 63 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  ______X_,
  ______X_,
  _____X__,
  ____X___,
  ____X___,
  ________,
  ____X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_64[13] = { /* code 64 */
  ________,
  ________,
  ___XXXX_,
  __X____X,
  _X__XX_X,
  _X_X_X_X,
  _X_X_X_X,
  _X_X_X_X,
  _X__XXX_,
  __X_____,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_65[13] = { /* code 65 */
  ________,
  ________,
  ___XX___,
  ____X___,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  __XXXXX_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_66[13] = { /* code 66 */
  ________,
  ________,
  _XXXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X____X,
  __X____X,
  __X____X,
  _XXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_67[13] = { /* code 67 */
  ________,
  ________,
  ___XXXX_,
  __X____X,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  __X____X,
  ___XXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_68[13] = { /* code 68 */
  ________,
  ________,
  _XXXXX__,
  __X___X_,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  __X___X_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_69[13] = { /* code 69 */
  ________,
  ________,
  _XXXXXXX,
  __X____X,
  __X_____,
  __X__X__,
  __XXXX__,
  __X__X__,
  __X_____,
  __X____X,
  _XXXXXXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_70[13] = { /* code 70 */
  ________,
  ________,
  _XXXXXXX,
  __X____X,
  __X_____,
  __X__X__,
  __XXXX__,
  __X__X__,
  __X_____,
  __X_____,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_71[13] = { /* code 71 */
  ________,
  ________,
  ___XXXX_,
  __X____X,
  _X______,
  _X______,
  _X______,
  _X___XXX,
  _X_____X,
  __X____X,
  ___XXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_72[13] = { /* code 72 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __XXXXX_,
  __X___X_,
  __X___X_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_73[13] = { /* code 73 */
  ________,
  ________,
  __XXXXX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_74[13] = { /* code 74 */
  ________,
  ________,
  ___XXXX_,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _X___X__,
  _X___X__,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_75[13] = { /* code 75 */
  ________,
  ________,
  _XXX__XX,
  __X___X_,
  __X__X__,
  __X__X__,
  __X_X___,
  __XXX___,
  __X__X__,
  __X___X_,
  _XXX__XX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_76[13] = { /* code 76 */
  ________,
  ________,
  _XXXXX__,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X___X,
  _XXXXXXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_77[13] = { /* code 77 */
  ________,
  ________,
  _XX___XX,
  __X___X_,
  __XX_XX_,
  __XX_XX_,
  __X_X_X_,
  __X_X_X_,
  __X___X_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_78[13] = { /* code 78 */
  ________,
  ________,
  _XX__XXX,
  __X___X_,
  __XX__X_,
  __XX__X_,
  __X_X_X_,
  __X__XX_,
  __X__XX_,
  __X___X_,
  _XXX__X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_79[13] = { /* code 79 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_80[13] = { /* code 80 */
  ________,
  ________,
  _XXXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X_____,
  __X_____,
  __X_____,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_81[13] = { /* code 81 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __X___X_,
  ___XXX__,
  ___XX_XX,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_82[13] = { /* code 82 */
  ________,
  ________,
  _XXXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X__X__,
  __X__X__,
  __X___X_,
  _XXX__XX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_83[13] = { /* code 83 */
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _X______,
  _X______,
  __XXXXX_,
  _______X,
  _______X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_84[13] = { /* code 84 */
  ________,
  ________,
  _XXXXXXX,
  _X__X__X,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_85[13] = { /* code 85 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X___X_,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_86[13] = { /* code 86 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ___X_X__,
  ____X___,
  ____X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_87[13] = { /* code 87 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  __X___X_,
  __X_X_X_,
  __X_X_X_,
  __X_X_X_,
  ___X_X__,
  ___X_X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_88[13] = { /* code 88 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ___X_X__,
  ___X_X__,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_89[13] = { /* code 89 */
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ____X___,
  ____X___,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_90[13] = { /* code 90 */
  ________,
  ________,
  _XXXXXXX,
  _X____X_,
  _____X__,
  _____X__,
  ____X___,
  ___X____,
  ___X____,
  __X____X,
  _XXXXXXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_91[13] = { /* code 91 */
  ________,
  ________,
  ___XXX__,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___XXX__};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_92[13] = { /* code 92 */
  ________,
  ________,
  ________,
  _X______,
  __X_____,
  ___X____,
  ____X___,
  _____X__,
  ______X_,
  _______X,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_93[13] = { /* code 93 */
  ________,
  ________,
  ___XXX__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  ___XXX__};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_94[13] = { /* code 94 */
  ________,
  ____X___,
  ___X_X__,
  __X___X_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_95[13] = { /* code 95 */
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

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_96[13] = { /* code 96 */
  ________,
  ________,
  ___X____,
  ____X___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_97[13] = { /* code 97 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXX__,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  __XXXX_X,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_98[13] = { /* code 98 */
  ________,
  ________,
  _XX_____,
  __X_____,
  __X_____,
  __XXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  _XXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_99[13] = { /* code 99 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _X______,
  _X______,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_100[13] = { /* code 100 */
  ________,
  ________,
  _____XX_,
  ______X_,
  ______X_,
  __XXXXX_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  __XXXXXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_101[13] = { /* code 101 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _XXXXXXX,
  _X______,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_102[13] = { /* code 102 */
  ________,
  ________,
  ____XX__,
  ___X____,
  ___X____,
  __XXXX__,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  __XXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_103[13] = { /* code 103 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXXX,
  _X____X_,
  _X____X_,
  _X____X_,
  __XXXXX_,
  ______X_,
  ______X_,
  __XXXX__};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_104[13] = { /* code 104 */
  ________,
  ________,
  _XX_____,
  __X_____,
  __X_____,
  __X_XX__,
  __XX__X_,
  __X___X_,
  __X___X_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_105[13] = { /* code 105 */
  ________,
  ________,
  ____X___,
  ________,
  ________,
  __XXX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_106[13] = { /* code 106 */
  ________,
  ________,
  _____X__,
  ________,
  ________,
  __XXXX__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  _____X__,
  __XXX___};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_107[13] = { /* code 107 */
  ________,
  ________,
  _XX_____,
  __X_____,
  __X_____,
  __X__XX_,
  __X__X__,
  __X_X___,
  __XXX___,
  __X__X__,
  _XX___XX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_108[13] = { /* code 108 */
  ________,
  ________,
  ___XX___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_109[13] = { /* code 109 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_X__,
  __X_X_X_,
  __X_X_X_,
  __X_X_X_,
  __X_X_X_,
  _XX_X_XX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_110[13] = { /* code 110 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_XX__,
  __XX__X_,
  __X___X_,
  __X___X_,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_111[13] = { /* code 111 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  _X_____X,
  _X_____X,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_112[13] = { /* code 112 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  __X____X,
  __X____X,
  __X____X,
  __X____X,
  __XXXXX_,
  __X_____,
  _XXX____};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_113[13] = { /* code 113 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXXX,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  __XXXXX_,
  ______X_,
  _____XXX};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_114[13] = { /* code 114 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XX_,
  ___XX__X,
  ___X____,
  ___X____,
  ___X____,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_115[13] = { /* code 115 */
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXXX_,
  _X_____X,
  __XXX___,
  _____XX_,
  _X_____X,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_116[13] = { /* code 116 */
  ________,
  ________,
  ________,
  ___X____,
  ___X____,
  __XXXX__,
  ___X____,
  ___X____,
  ___X____,
  ___X__X_,
  ____XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_117[13] = { /* code 117 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX__XX_,
  __X___X_,
  __X___X_,
  __X___X_,
  __X__XX_,
  ___XX_XX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_118[13] = { /* code 118 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_119[13] = { /* code 119 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X_X_X_,
  __X_X_X_,
  ___X_X__,
  ___X_X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_120[13] = { /* code 120 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  ___XXX__,
  ___XXX__,
  __X___X_,
  _XXX_XXX,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_121[13] = { /* code 121 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX_XXX,
  __X___X_,
  __X___X_,
  ___X_X__,
  ___X_X__,
  ____X___,
  ____X___,
  __XX____};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_122[13] = { /* code 122 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  _X___X__,
  ____X___,
  ___X____,
  __X___X_,
  _XXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_123[13] = { /* code 123 */
  ________,
  ________,
  _____XX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XX____,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  _____XX_};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_124[13] = { /* code 124 */
  ________,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  ____X___};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_125[13] = { /* code 125 */
  ________,
  ________,
  __XX____,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  _____XX_,
  ____X___,
  ____X___,
  ____X___,
  ____X___,
  __XX____};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_126[13] = { /* code 126 */
  ________,
  ________,
  ________,
  __XX___X,
  _X__X__X,
  _X___XX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acF8x13_ASCII_127[13] = { /* code 127 */
  ________,
  ________,
  ________,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ___XXX__,
  ________};


GUI_CONST_STORAGE GUI_CHARINFO GUI_CharInfoF8x13_ASCII[96] = {
   {   8,   8,  1, acF8x13_ASCII_32 } /* code  32 */
  ,{   8,   8,  1, acF8x13_ASCII_33 } /* code  33 */
  ,{   8,   8,  1, acF8x13_ASCII_34 } /* code  34 */
  ,{   8,   8,  1, acF8x13_ASCII_35 } /* code  35 */
  ,{   8,   8,  1, acF8x13_ASCII_36 } /* code  36 */
  ,{   8,   8,  1, acF8x13_ASCII_37 } /* code  37 */
  ,{   8,   8,  1, acF8x13_ASCII_38 } /* code  38 */
  ,{   8,   8,  1, acF8x13_ASCII_39 } /* code  39 */
  ,{   8,   8,  1, acF8x13_ASCII_40 } /* code  40 */
  ,{   8,   8,  1, acF8x13_ASCII_41 } /* code  41 */
  ,{   8,   8,  1, acF8x13_ASCII_42 } /* code  42 */
  ,{   8,   8,  1, acF8x13_ASCII_43 } /* code  43 */
  ,{   8,   8,  1, acF8x13_ASCII_44 } /* code  44 */
  ,{   8,   8,  1, acF8x13_ASCII_45 } /* code  45 */
  ,{   8,   8,  1, acF8x13_ASCII_46 } /* code  46 */
  ,{   8,   8,  1, acF8x13_ASCII_47 } /* code  47 */
  ,{   8,   8,  1, acF8x13_ASCII_48 } /* code  48 */
  ,{   8,   8,  1, acF8x13_ASCII_49 } /* code  49 */
  ,{   8,   8,  1, acF8x13_ASCII_50 } /* code  50 */
  ,{   8,   8,  1, acF8x13_ASCII_51 } /* code  51 */
  ,{   8,   8,  1, acF8x13_ASCII_52 } /* code  52 */
  ,{   8,   8,  1, acF8x13_ASCII_53 } /* code  53 */
  ,{   8,   8,  1, acF8x13_ASCII_54 } /* code  54 */
  ,{   8,   8,  1, acF8x13_ASCII_55 } /* code  55 */
  ,{   8,   8,  1, acF8x13_ASCII_56 } /* code  56 */
  ,{   8,   8,  1, acF8x13_ASCII_57 } /* code  57 */
  ,{   8,   8,  1, acF8x13_ASCII_58 } /* code  58 */
  ,{   8,   8,  1, acF8x13_ASCII_59 } /* code  59 */
  ,{   8,   8,  1, acF8x13_ASCII_60 } /* code  60 */
  ,{   8,   8,  1, acF8x13_ASCII_61 } /* code  61 */
  ,{   8,   8,  1, acF8x13_ASCII_62 } /* code  62 */
  ,{   8,   8,  1, acF8x13_ASCII_63 } /* code  63 */
  ,{   8,   8,  1, acF8x13_ASCII_64 } /* code  64 */
  ,{   8,   8,  1, acF8x13_ASCII_65 } /* code  65 */
  ,{   8,   8,  1, acF8x13_ASCII_66 } /* code  66 */
  ,{   8,   8,  1, acF8x13_ASCII_67 } /* code  67 */
  ,{   8,   8,  1, acF8x13_ASCII_68 } /* code  68 */
  ,{   8,   8,  1, acF8x13_ASCII_69 } /* code  69 */
  ,{   8,   8,  1, acF8x13_ASCII_70 } /* code  70 */
  ,{   8,   8,  1, acF8x13_ASCII_71 } /* code  71 */
  ,{   8,   8,  1, acF8x13_ASCII_72 } /* code  72 */
  ,{   8,   8,  1, acF8x13_ASCII_73 } /* code  73 */
  ,{   8,   8,  1, acF8x13_ASCII_74 } /* code  74 */
  ,{   8,   8,  1, acF8x13_ASCII_75 } /* code  75 */
  ,{   8,   8,  1, acF8x13_ASCII_76 } /* code  76 */
  ,{   8,   8,  1, acF8x13_ASCII_77 } /* code  77 */
  ,{   8,   8,  1, acF8x13_ASCII_78 } /* code  78 */
  ,{   8,   8,  1, acF8x13_ASCII_79 } /* code  79 */
  ,{   8,   8,  1, acF8x13_ASCII_80 } /* code  80 */
  ,{   8,   8,  1, acF8x13_ASCII_81 } /* code  81 */
  ,{   8,   8,  1, acF8x13_ASCII_82 } /* code  82 */
  ,{   8,   8,  1, acF8x13_ASCII_83 } /* code  83 */
  ,{   8,   8,  1, acF8x13_ASCII_84 } /* code  84 */
  ,{   8,   8,  1, acF8x13_ASCII_85 } /* code  85 */
  ,{   8,   8,  1, acF8x13_ASCII_86 } /* code  86 */
  ,{   8,   8,  1, acF8x13_ASCII_87 } /* code  87 */
  ,{   8,   8,  1, acF8x13_ASCII_88 } /* code  88 */
  ,{   8,   8,  1, acF8x13_ASCII_89 } /* code  89 */
  ,{   8,   8,  1, acF8x13_ASCII_90 } /* code  90 */
  ,{   8,   8,  1, acF8x13_ASCII_91 } /* code  91 */
  ,{   8,   8,  1, acF8x13_ASCII_92 } /* code  92 */
  ,{   8,   8,  1, acF8x13_ASCII_93 } /* code  93 */
  ,{   8,   8,  1, acF8x13_ASCII_94 } /* code  94 */
  ,{   8,   8,  1, acF8x13_ASCII_95 } /* code  95 */
  ,{   8,   8,  1, acF8x13_ASCII_96 } /* code  96 */
  ,{   8,   8,  1, acF8x13_ASCII_97 } /* code  97 */
  ,{   8,   8,  1, acF8x13_ASCII_98 } /* code  98 */
  ,{   8,   8,  1, acF8x13_ASCII_99 } /* code  99 */
  ,{   8,   8,  1, acF8x13_ASCII_100 } /* code 100 */
  ,{   8,   8,  1, acF8x13_ASCII_101 } /* code 101 */
  ,{   8,   8,  1, acF8x13_ASCII_102 } /* code 102 */
  ,{   8,   8,  1, acF8x13_ASCII_103 } /* code 103 */
  ,{   8,   8,  1, acF8x13_ASCII_104 } /* code 104 */
  ,{   8,   8,  1, acF8x13_ASCII_105 } /* code 105 */
  ,{   8,   8,  1, acF8x13_ASCII_106 } /* code 106 */
  ,{   8,   8,  1, acF8x13_ASCII_107 } /* code 107 */
  ,{   8,   8,  1, acF8x13_ASCII_108 } /* code 108 */
  ,{   8,   8,  1, acF8x13_ASCII_109 } /* code 109 */
  ,{   8,   8,  1, acF8x13_ASCII_110 } /* code 110 */
  ,{   8,   8,  1, acF8x13_ASCII_111 } /* code 111 */
  ,{   8,   8,  1, acF8x13_ASCII_112 } /* code 112 */
  ,{   8,   8,  1, acF8x13_ASCII_113 } /* code 113 */
  ,{   8,   8,  1, acF8x13_ASCII_114 } /* code 114 */
  ,{   8,   8,  1, acF8x13_ASCII_115 } /* code 115 */
  ,{   8,   8,  1, acF8x13_ASCII_116 } /* code 116 */
  ,{   8,   8,  1, acF8x13_ASCII_117 } /* code 117 */
  ,{   8,   8,  1, acF8x13_ASCII_118 } /* code 118 */
  ,{   8,   8,  1, acF8x13_ASCII_119 } /* code 119 */
  ,{   8,   8,  1, acF8x13_ASCII_120 } /* code 120 */
  ,{   8,   8,  1, acF8x13_ASCII_121 } /* code 121 */
  ,{   8,   8,  1, acF8x13_ASCII_122 } /* code 122 */
  ,{   8,   8,  1, acF8x13_ASCII_123 } /* code 123 */
  ,{   8,   8,  1, acF8x13_ASCII_124 } /* code 124 */
  ,{   8,   8,  1, acF8x13_ASCII_125 } /* code 125 */
  ,{   8,   8,  1, acF8x13_ASCII_126 } /* code 126 */
  ,{   8,   8,  1, acF8x13_ASCII_127 } /* code 127 */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontPropF8x13_ASCII_1 = {
   32                       /* first character               */
  ,127                      /* last character                */
  ,GUI_CharInfoF8x13_ASCII  /* address of first character    */
  ,(const GUI_FONT_PROP*)0  /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font8x13_ASCII = {
   GUI_FONTTYPE_PROP   /* type of font    */
  ,13                  /* height of font  */
  ,13                  /* space of font y */
  ,1                   /* magnification x */
  ,1                   /* magnification y */
  ,{&GUI_FontPropF8x13_ASCII_1}
  , 11, 6, 9
};

