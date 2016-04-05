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
File        : F10S_ASCII.C
Purpose     : Proportional small font
Height      : 10
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_32[10] = { /* code 32 */
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

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_33[10] = { /* code 33 */
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  ________,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_34[10] = { /* code 34 */
  ________,
  ________,
  _X_X____,
  _X_X____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_35[10] = { /* code 35 */
  ________,
  ________,
  __X_X___,
  _XXXXX__,
  __X_X___,
  __X_X___,
  _XXXXX__,
  __X_X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_36[10] = { /* code 36 */
  ________,
  ________,
  __X_____,
  _XXX____,
  _XX_____,
  __X_____,
  __XX____,
  _XXX____,
  __X_____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_37[10] = { /* code 37 */
  ________,
  ________,
  _XX_____,
  _XX_X___,
  ___X____,
  __X_____,
  _X_XX___,
  ___XX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_38[10] = { /* code 38 */
  ________,
  ________,
  __X_____,
  _X_X____,
  __X_____,
  _X_XX___,
  _X_X____,
  __X_X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_39[10] = { /* code 39 */
  ________,
  ________,
  _X______,
  _X______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_40[10] = { /* code 40 */
  ________,
  ________,
  __X_____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_41[10] = { /* code 41 */
  ________,
  ________,
  _X______,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  _X______};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_42[10] = { /* code 42 */
  ________,
  ________,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_43[10] = { /* code 43 */
  ________,
  ________,
  ________,
  ________,
  __X_____,
  _XXX____,
  __X_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_44[10] = { /* code 44 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _X______,
  _X______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_45[10] = { /* code 45 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_____,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_46[10] = { /* code 46 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_47[10] = { /* code 47 */
  ________,
  ________,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_48[10] = { /* code 48 */
  ________,
  ________,
  __XX____,
  _X__X___,
  _X__X___,
  _X__X___,
  _X__X___,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_49[10] = { /* code 49 */
  ________,
  ________,
  __X_____,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_50[10] = { /* code 50 */
  ________,
  ________,
  __XX____,
  _X__X___,
  ____X___,
  __XX____,
  _X______,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_51[10] = { /* code 51 */
  ________,
  ________,
  __XX____,
  _X__X___,
  ___X____,
  ____X___,
  _X__X___,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_52[10] = { /* code 52 */
  ________,
  ________,
  ___X____,
  __XX____,
  __XX____,
  _X_X____,
  _XXXX___,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_53[10] = { /* code 53 */
  ________,
  ________,
  _XXX____,
  _X______,
  _XX_____,
  ___X____,
  ___X____,
  _XX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_54[10] = { /* code 54 */
  ________,
  ________,
  __XX____,
  _X______,
  _XXX____,
  _X__X___,
  _X__X___,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_55[10] = { /* code 55 */
  ________,
  ________,
  _XXX____,
  ___X____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_56[10] = { /* code 56 */
  ________,
  ________,
  __XX____,
  _X__X___,
  __XX____,
  _X__X___,
  _X__X___,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_57[10] = { /* code 57 */
  ________,
  ________,
  __XX____,
  _X__X___,
  __XXX___,
  ____X___,
  _X__X___,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_58[10] = { /* code 58 */
  ________,
  ________,
  ________,
  ________,
  _X______,
  ________,
  ________,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_59[10] = { /* code 59 */
  ________,
  ________,
  ________,
  ________,
  _X______,
  ________,
  ________,
  _X______,
  _X______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_60[10] = { /* code 60 */
  ________,
  ________,
  ________,
  ___X____,
  __X_____,
  _X______,
  __X_____,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_61[10] = { /* code 61 */
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  ________,
  _XXX____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_62[10] = { /* code 62 */
  ________,
  ________,
  ________,
  _X______,
  __X_____,
  ___X____,
  __X_____,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_63[10] = { /* code 63 */
  ________,
  ________,
  __XX____,
  _X__X___,
  ___X____,
  __X_____,
  ________,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_64[10] = { /* code 64 */
  ________,
  ________,
  ___XXX__,
  __X___X_,
  _X__X__X,
  _X_X_X_X,
  _X__XXX_,
  __X_____,
  ___XXX__,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_65[10] = { /* code 65 */
  ________,
  ________,
  ___X____,
  ___X____,
  __X_X___,
  __XXX___,
  _X___X__,
  _X___X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_66[10] = { /* code 66 */
  ________,
  ________,
  _XXXX___,
  _X___X__,
  _XXXX___,
  _X___X__,
  _X___X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_67[10] = { /* code 67 */
  ________,
  ________,
  __XXX___,
  _X___X__,
  _X______,
  _X______,
  _X___X__,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_68[10] = { /* code 68 */
  ________,
  ________,
  _XXXX___,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_69[10] = { /* code 69 */
  ________,
  ________,
  _XXXX___,
  _X______,
  _XXX____,
  _X______,
  _X______,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_70[10] = { /* code 70 */
  ________,
  ________,
  _XXXX___,
  _X______,
  _XXX____,
  _X______,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_71[10] = { /* code 71 */
  ________,
  ________,
  __XXX___,
  _X___X__,
  _X______,
  _X__XX__,
  _X___X__,
  __XXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_72[10] = { /* code 72 */
  ________,
  ________,
  _X__X___,
  _X__X___,
  _XXXX___,
  _X__X___,
  _X__X___,
  _X__X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_73[10] = { /* code 73 */
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_74[10] = { /* code 74 */
  ________,
  ________,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  _X_X____,
  _XX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_75[10] = { /* code 75 */
  ________,
  ________,
  _X__X___,
  _X_X____,
  _XX_____,
  _XX_____,
  _X_X____,
  _X__X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_76[10] = { /* code 76 */
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_77[10] = { /* code 77 */
  ________,
  ________,
  _XX___XX,
  _XX___XX,
  _X_X_X_X,
  _X_X_X_X,
  _X__X__X,
  _X__X__X,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_78[10] = { /* code 78 */
  ________,
  ________,
  _XX__X__,
  _XX__X__,
  _X_X_X__,
  _X_X_X__,
  _X__XX__,
  _X__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_79[10] = { /* code 79 */
  ________,
  ________,
  __XXX___,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_80[10] = { /* code 80 */
  ________,
  ________,
  _XXX____,
  _X__X___,
  _X__X___,
  _XXX____,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_81[10] = { /* code 81 */
  ________,
  ________,
  __XXX___,
  _X___X__,
  _X___X__,
  _X_X_X__,
  _X__X___,
  __XX_X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_82[10] = { /* code 82 */
  ________,
  ________,
  _XXXX___,
  _X___X__,
  _X___X__,
  _XXXX___,
  _X___X__,
  _X___X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_83[10] = { /* code 83 */
  ________,
  ________,
  __XX____,
  _X__X___,
  __X_____,
  ___X____,
  _X__X___,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_84[10] = { /* code 84 */
  ________,
  ________,
  XXXXX___,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_85[10] = { /* code 85 */
  ________,
  ________,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  _X___X__,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_86[10] = { /* code 86 */
  ________,
  ________,
  _X___X__,
  _X___X__,
  __X_X___,
  __X_X___,
  ___X____,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_87[10] = { /* code 87 */
  ________,
  ________,
  _X_____X,
  _X_____X,
  __X_X_X_,
  __X_X_X_,
  ___X_X__,
  ___X_X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_88[10] = { /* code 88 */
  ________,
  ________,
  _X___X__,
  __X_X___,
  ___X____,
  ___X____,
  __X_X___,
  _X___X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_89[10] = { /* code 89 */
  ________,
  ________,
  _X___X__,
  __X_X___,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_90[10] = { /* code 90 */
  ________,
  ________,
  _XXXX___,
  ____X___,
  ___X____,
  __X_____,
  _X______,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_91[10] = { /* code 91 */
  ________,
  ________,
  _XX_____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _XX_____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_92[10] = { /* code 92 */
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_93[10] = { /* code 93 */
  ________,
  ________,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  _XX_____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_94[10] = { /* code 94 */
  ________,
  ________,
  __X_____,
  _X_X____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_95[10] = { /* code 95 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_96[10] = { /* code 96 */
  ________,
  _X______,
  __X_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_97[10] = { /* code 97 */
  ________,
  ________,
  ________,
  ________,
  _XX_____,
  ___X____,
  _X_X____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_98[10] = { /* code 98 */
  ________,
  ________,
  _X______,
  _X______,
  _XXX____,
  _X__X___,
  _X__X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_99[10] = { /* code 99 */
  ________,
  ________,
  ________,
  ________,
  __XX____,
  _X______,
  _X______,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_100[10] = { /* code 100 */
  ________,
  ________,
  ____X___,
  ____X___,
  __XXX___,
  _X__X___,
  _X__X___,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_101[10] = { /* code 101 */
  ________,
  ________,
  ________,
  ________,
  __X_____,
  _X_X____,
  _X______,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_102[10] = { /* code 102 */
  ________,
  ________,
  __X_____,
  _X______,
  _XX_____,
  _X______,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_103[10] = { /* code 103 */
  ________,
  ________,
  ________,
  ________,
  __XXX___,
  _X__X___,
  _X__X___,
  __XXX___,
  ____X___,
  __XX____};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_104[10] = { /* code 104 */
  ________,
  ________,
  _X______,
  _X______,
  _XX_____,
  _X_X____,
  _X_X____,
  _X_X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_105[10] = { /* code 105 */
  ________,
  ________,
  _X______,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_106[10] = { /* code 106 */
  ________,
  ________,
  _X______,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_107[10] = { /* code 107 */
  ________,
  ________,
  _X______,
  _X______,
  _X_X____,
  _XX_____,
  _X_X____,
  _X_X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_108[10] = { /* code 108 */
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_109[10] = { /* code 109 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  _X_X_X__,
  _X_X_X__,
  _X_X_X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_110[10] = { /* code 110 */
  ________,
  ________,
  ________,
  ________,
  _XX_____,
  _X_X____,
  _X_X____,
  _X_X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_111[10] = { /* code 111 */
  ________,
  ________,
  ________,
  ________,
  __XX____,
  _X__X___,
  _X__X___,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_112[10] = { /* code 112 */
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  _X__X___,
  _X__X___,
  _XXX____,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_113[10] = { /* code 113 */
  ________,
  ________,
  ________,
  ________,
  __XXX___,
  _X__X___,
  _X__X___,
  __XXX___,
  ____X___,
  ____X___};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_114[10] = { /* code 114 */
  ________,
  ________,
  ________,
  ________,
  _XX_____,
  _X______,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_115[10] = { /* code 115 */
  ________,
  ________,
  ________,
  ________,
  __XX____,
  _X______,
  ___X____,
  _XX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_116[10] = { /* code 116 */
  ________,
  ________,
  ________,
  _X______,
  _XX_____,
  _X______,
  _X______,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_117[10] = { /* code 117 */
  ________,
  ________,
  ________,
  ________,
  _X_X____,
  _X_X____,
  _X_X____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_118[10] = { /* code 118 */
  ________,
  ________,
  ________,
  ________,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_119[10] = { /* code 119 */
  ________,
  ________,
  ________,
  ________,
  _X_X_X__,
  _X_X_X__,
  __X_X___,
  __X_X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_120[10] = { /* code 120 */
  ________,
  ________,
  ________,
  ________,
  _X_X____,
  __X_____,
  __X_____,
  _X_X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_121[10] = { /* code 121 */
  ________,
  ________,
  ________,
  ________,
  _X_X____,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  _X______};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_122[10] = { /* code 122 */
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  ___X____,
  _X______,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_123[10] = { /* code 123 */
  ________,
  ________,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  __X_____,
  __X_____,
  __X_____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_124[10] = { /* code 124 */
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_125[10] = { /* code 125 */
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  __X_____,
  _X______,
  _X______,
  _X______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10S_ASCII_126[10] = { /* code 126 */
  ________,
  ________,
  _X_X____,
  X_X_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};



GUI_CONST_STORAGE GUI_CHARINFO GUI_Font10S_ASCII_CharInfo[96] = {
   {   2,   2,  1, acFont10S_ASCII_32 } /* code  32 */
  ,{   2,   2,  1, acFont10S_ASCII_33 } /* code  33 */
  ,{   4,   4,  1, acFont10S_ASCII_34 } /* code  34 */
  ,{   6,   6,  1, acFont10S_ASCII_35 } /* code  35 */
  ,{   4,   4,  1, acFont10S_ASCII_36 } /* code  36 */
  ,{   5,   5,  1, acFont10S_ASCII_37 } /* code  37 */
  ,{   5,   5,  1, acFont10S_ASCII_38 } /* code  38 */
  ,{   2,   2,  1, acFont10S_ASCII_39 } /* code  39 */
  ,{   3,   3,  1, acFont10S_ASCII_40 } /* code  40 */
  ,{   3,   3,  1, acFont10S_ASCII_41 } /* code  41 */
  ,{   3,   3,  1, acFont10S_ASCII_42 } /* code  42 */
  ,{   4,   4,  1, acFont10S_ASCII_43 } /* code  43 */
  ,{   2,   2,  1, acFont10S_ASCII_44 } /* code  44 */
  ,{   3,   3,  1, acFont10S_ASCII_45 } /* code  45 */
  ,{   2,   2,  1, acFont10S_ASCII_46 } /* code  46 */
  ,{   3,   3,  1, acFont10S_ASCII_47 } /* code  47 */
  ,{   5,   5,  1, acFont10S_ASCII_48 } /* code  48 */
  ,{   3,   3,  1, acFont10S_ASCII_49 } /* code  49 */
  ,{   5,   5,  1, acFont10S_ASCII_50 } /* code  50 */
  ,{   5,   5,  1, acFont10S_ASCII_51 } /* code  51 */
  ,{   5,   5,  1, acFont10S_ASCII_52 } /* code  52 */
  ,{   4,   4,  1, acFont10S_ASCII_53 } /* code  53 */
  ,{   5,   5,  1, acFont10S_ASCII_54 } /* code  54 */
  ,{   4,   4,  1, acFont10S_ASCII_55 } /* code  55 */
  ,{   5,   5,  1, acFont10S_ASCII_56 } /* code  56 */
  ,{   5,   5,  1, acFont10S_ASCII_57 } /* code  57 */
  ,{   2,   2,  1, acFont10S_ASCII_58 } /* code  58 */
  ,{   2,   2,  1, acFont10S_ASCII_59 } /* code  59 */
  ,{   4,   4,  1, acFont10S_ASCII_60 } /* code  60 */
  ,{   4,   4,  1, acFont10S_ASCII_61 } /* code  61 */
  ,{   4,   4,  1, acFont10S_ASCII_62 } /* code  62 */
  ,{   5,   5,  1, acFont10S_ASCII_63 } /* code  63 */
  ,{   8,   8,  1, acFont10S_ASCII_64 } /* code  64 */
  ,{   6,   6,  1, acFont10S_ASCII_65 } /* code  65 */
  ,{   6,   6,  1, acFont10S_ASCII_66 } /* code  66 */
  ,{   6,   6,  1, acFont10S_ASCII_67 } /* code  67 */
  ,{   6,   6,  1, acFont10S_ASCII_68 } /* code  68 */
  ,{   5,   5,  1, acFont10S_ASCII_69 } /* code  69 */
  ,{   5,   5,  1, acFont10S_ASCII_70 } /* code  70 */
  ,{   6,   6,  1, acFont10S_ASCII_71 } /* code  71 */
  ,{   5,   5,  1, acFont10S_ASCII_72 } /* code  72 */
  ,{   2,   2,  1, acFont10S_ASCII_73 } /* code  73 */
  ,{   4,   4,  1, acFont10S_ASCII_74 } /* code  74 */
  ,{   5,   5,  1, acFont10S_ASCII_75 } /* code  75 */
  ,{   4,   4,  1, acFont10S_ASCII_76 } /* code  76 */
  ,{   8,   8,  1, acFont10S_ASCII_77 } /* code  77 */
  ,{   6,   6,  1, acFont10S_ASCII_78 } /* code  78 */
  ,{   6,   6,  1, acFont10S_ASCII_79 } /* code  79 */
  ,{   5,   5,  1, acFont10S_ASCII_80 } /* code  80 */
  ,{   6,   6,  1, acFont10S_ASCII_81 } /* code  81 */
  ,{   6,   6,  1, acFont10S_ASCII_82 } /* code  82 */
  ,{   5,   5,  1, acFont10S_ASCII_83 } /* code  83 */
  ,{   5,   5,  1, acFont10S_ASCII_84 } /* code  84 */
  ,{   6,   6,  1, acFont10S_ASCII_85 } /* code  85 */
  ,{   6,   6,  1, acFont10S_ASCII_86 } /* code  86 */
  ,{   8,   8,  1, acFont10S_ASCII_87 } /* code  87 */
  ,{   6,   6,  1, acFont10S_ASCII_88 } /* code  88 */
  ,{   6,   6,  1, acFont10S_ASCII_89 } /* code  89 */
  ,{   5,   5,  1, acFont10S_ASCII_90 } /* code  90 */
  ,{   3,   3,  1, acFont10S_ASCII_91 } /* code  91 */
  ,{   3,   3,  1, acFont10S_ASCII_92 } /* code  92 */
  ,{   3,   3,  1, acFont10S_ASCII_93 } /* code  93 */
  ,{   4,   4,  1, acFont10S_ASCII_94 } /* code  94 */
  ,{   5,   5,  1, acFont10S_ASCII_95 } /* code  95 */
  ,{   3,   3,  1, acFont10S_ASCII_96 } /* code  96 */
  ,{   4,   4,  1, acFont10S_ASCII_97 } /* code  97 */
  ,{   5,   5,  1, acFont10S_ASCII_98 } /* code  98 */
  ,{   4,   4,  1, acFont10S_ASCII_99 } /* code  99 */
  ,{   5,   5,  1, acFont10S_ASCII_100 } /* code 100 */
  ,{   4,   4,  1, acFont10S_ASCII_101 } /* code 101 */
  ,{   3,   3,  1, acFont10S_ASCII_102 } /* code 102 */
  ,{   5,   5,  1, acFont10S_ASCII_103 } /* code 103 */
  ,{   4,   4,  1, acFont10S_ASCII_104 } /* code 104 */
  ,{   2,   2,  1, acFont10S_ASCII_105 } /* code 105 */
  ,{   2,   2,  1, acFont10S_ASCII_106 } /* code 106 */
  ,{   4,   4,  1, acFont10S_ASCII_107 } /* code 107 */
  ,{   2,   2,  1, acFont10S_ASCII_108 } /* code 108 */
  ,{   6,   6,  1, acFont10S_ASCII_109 } /* code 109 */
  ,{   4,   4,  1, acFont10S_ASCII_110 } /* code 110 */
  ,{   5,   5,  1, acFont10S_ASCII_111 } /* code 111 */
  ,{   5,   5,  1, acFont10S_ASCII_112 } /* code 112 */
  ,{   5,   5,  1, acFont10S_ASCII_113 } /* code 113 */
  ,{   3,   3,  1, acFont10S_ASCII_114 } /* code 114 */
  ,{   4,   4,  1, acFont10S_ASCII_115 } /* code 115 */
  ,{   3,   3,  1, acFont10S_ASCII_116 } /* code 116 */
  ,{   4,   4,  1, acFont10S_ASCII_117 } /* code 117 */
  ,{   4,   4,  1, acFont10S_ASCII_118 } /* code 118 */
  ,{   6,   6,  1, acFont10S_ASCII_119 } /* code 119 */
  ,{   4,   4,  1, acFont10S_ASCII_120 } /* code 120 */
  ,{   4,   4,  1, acFont10S_ASCII_121 } /* code 121 */
  ,{   4,   4,  1, acFont10S_ASCII_122 } /* code 122 */
  ,{   3,   3,  1, acFont10S_ASCII_123 } /* code 123 */
  ,{   2,   2,  1, acFont10S_ASCII_124 } /* code 124 */
  ,{   3,   3,  1, acFont10S_ASCII_125 } /* code 125 */
  ,{   4,   4,  1, acFont10S_ASCII_126 } /* code 126 */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font10S_ASCII_FontProp1 = {
   32                             /* first character               */
  ,126                            /* last character                */
  ,&GUI_Font10S_ASCII_CharInfo[0] /* address of first character    */
  ,(const GUI_FONT_PROP*)0        /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font10S_ASCII = {
   GUI_FONTTYPE_PROP /* type of font    */
  ,10                /* height of font  */
  ,10                /* space of font y */
  ,1                 /* magnification x */
  ,1                 /* magnification y */
  ,{&GUI_Font10S_ASCII_FontProp1}
  , 8, 4, 6 
};

/*************************** End of file ****************************/
