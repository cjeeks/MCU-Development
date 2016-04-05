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
File        : F16B_ASCII.C
Purpose     : ASCII Character Set similar to Swiss, bold
Height      : 16
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"

/* Start of unicode area <Basic Latin> */
GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0020[ 16] = { /* code 0020 */
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

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0021[ 16] = { /* code 0021 */
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
  ________,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0022[ 16] = { /* code 0022 */
  ________,
  ________,
  ________,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
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

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0023[ 16] = { /* code 0023 */
  ________,
  ________,
  ________,
  __X__X__,
  __X__X__,
  __X__X__,
  XXXXXX__,
  _X__X___,
  _X__X___,
  XXXXXX__,
  X__X____,
  X__X____,
  X__X____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0024[ 16] = { /* code 0024 */
  ________,
  ________,
  ___X____,
  __XXX___,
  _X_X_X__,
  _X_X____,
  _XXX____,
  _XXXX___,
  __XXXX__,
  ___XXX__,
  ___X_X__,
  _X_X_X__,
  __XXX___,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0025[ 32] = { /* code 0025 */
  ________,________,
  ________,________,
  ________,________,
  _XXX__X_,________,
  _X_X__X_,________,
  _X_X__X_,________,
  _X_X_X__,________,
  _XXX_X__,________,
  ____X_XX,X_______,
  ____X_X_,X_______,
  ____X_X_,X_______,
  ___X__X_,X_______,
  ___X__XX,X_______,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0026[ 32] = { /* code 0026 */
  ________,________,
  ________,________,
  ________,________,
  ___XXX__,________,
  __XX_XX_,________,
  __XX_XX_,________,
  ___XXXX_,________,
  ___XX___,________,
  __XXXX_X,________,
  _XX_XX_X,________,
  _XX__XXX,________,
  _XX__XXX,________,
  __XXXX_X,X_______,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0027[ 16] = { /* code 0027 */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  _XX_____,
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

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0028[ 16] = { /* code 0028 */
  ________,
  ________,
  ________,
  ___X____,
  __XX____,
  __X_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  __X_____,
  __XX____,
  ___X____};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0029[ 16] = { /* code 0029 */
  ________,
  ________,
  ________,
  X_______,
  XX______,
  _X______,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _X______,
  XX______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_002A[ 16] = { /* code 002A */
  ________,
  ________,
  ________,
  __X_____,
  XXXXX___,
  __X_____,
  XX_XX___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_002B[ 16] = { /* code 002B */
  ________,
  ________,
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
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_002C[ 16] = { /* code 002C */
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
  _XX_____,
  _XX_____,
  __X_____,
  _X______,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_002D[ 16] = { /* code 002D */
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
  _XXX____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_002E[ 16] = { /* code 002E */
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
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_002F[ 16] = { /* code 002F */
  ________,
  ________,
  ________,
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  _X______,
  X_______,
  X_______,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0030[ 16] = { /* code 0030 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0031[ 16] = { /* code 0031 */
  ________,
  ________,
  ________,
  ___XX___,
  __XXX___,
  _XXXX___,
  _X_XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0032[ 16] = { /* code 0032 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  ____XX__,
  ____XX__,
  ___XX___,
  __XXX___,
  __XX____,
  _XX_____,
  XX______,
  XXXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0033[ 16] = { /* code 0033 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  ____XX__,
  ____XX__,
  __XXX___,
  ____XX__,
  ____XX__,
  ____XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0034[ 16] = { /* code 0034 */
  ________,
  ________,
  ________,
  ___XX___,
  ___XX___,
  __XXX___,
  __XXX___,
  _X_XX___,
  _X_XX___,
  X__XX___,
  XXXXXX__,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0035[ 16] = { /* code 0035 */
  ________,
  ________,
  ________,
  _XXXXX__,
  _XX_____,
  XX______,
  XXXXX___,
  XX__XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0036[ 16] = { /* code 0036 */
  ________,
  ________,
  ________,
  __XXX___,
  _X__XX__,
  XX______,
  XX______,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0037[ 16] = { /* code 0037 */
  ________,
  ________,
  ________,
  XXXXXX__,
  ____XX__,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  __XX____,
  _XX_____,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0038[ 16] = { /* code 0038 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0039[ 16] = { /* code 0039 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ____XX__,
  ____XX__,
  XX__X___,
  _XXX____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_003A[ 16] = { /* code 003A */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_003B[ 16] = { /* code 003B */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  __X_____,
  _X______,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_003C[ 16] = { /* code 003C */
  ________,
  ________,
  ________,
  ________,
  ________,
  _____X__,
  ___XXX__,
  _XXX____,
  XX______,
  _XXX____,
  ___XXX__,
  _____X__,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_003D[ 16] = { /* code 003D */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXXXX_,
  ________,
  XXXXXXX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_003E[ 16] = { /* code 003E */
  ________,
  ________,
  ________,
  ________,
  ________,
  _X______,
  _XXX____,
  ___XXX__,
  _____XX_,
  ___XXX__,
  _XXX____,
  _X______,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_003F[ 16] = { /* code 003F */
  ________,
  ________,
  ________,
  _XXXXX__,
  XX___XX_,
  _____XX_,
  _____XX_,
  ____XX__,
  ___XX___,
  __XX____,
  ________,
  __XX____,
  __XX____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0040[ 32] = { /* code 0040 */
  ________,________,
  ________,________,
  ________,________,
  ____XXXX,XX______,
  __XX____,__X_____,
  _XX_____,___X____,
  _X__XXX_,XX__X___,
  X__XXXXX,XX__X___,
  X_XXX__X,XX__X___,
  X_XX___X,X___X___,
  X_XX__XX,X__X____,
  X_XXXXXX,X_XX____,
  _X_XXX_X,XX______,
  _X______,____X___,
  __XX____,__XX____,
  ____XXXX,XX______};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0041[ 32] = { /* code 0041 */
  ________,________,
  ________,________,
  ________,________,
  ___XXX__,________,
  ___XXX__,________,
  __XX_XX_,________,
  __XX_XX_,________,
  __XX_XX_,________,
  _XX___XX,________,
  _XX___XX,________,
  _XXXXXXX,________,
  XX_____X,X_______,
  XX_____X,X_______,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0042[ 32] = { /* code 0042 */
  ________,________,
  ________,________,
  ________,________,
  _XXXXXX_,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XXXXXX_,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XXXXXX_,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0043[ 32] = { /* code 0043 */
  ________,________,
  ________,________,
  ________,________,
  ___XXXXX,________,
  __XX___X,X_______,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________,
  __XX___X,X_______,
  ___XXXXX,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0044[ 32] = { /* code 0044 */
  ________,________,
  ________,________,
  ________,________,
  _XXXXX__,________,
  _XX__XX_,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX__XX_,________,
  _XXXXX__,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0045[ 16] = { /* code 0045 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXXXXX_,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0046[ 16] = { /* code 0046 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXXXXX_,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0047[ 32] = { /* code 0047 */
  ________,________,
  ________,________,
  ________,________,
  ___XXXXX,________,
  __XX___X,X_______,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________,
  _XX__XXX,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  __XX___X,X_______,
  ___XXXXX,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0048[ 32] = { /* code 0048 */
  ________,________,
  ________,________,
  ________,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XXXXXXX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0049[ 16] = { /* code 0049 */
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
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_004A[ 16] = { /* code 004A */
  ________,
  ________,
  ________,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_004B[ 32] = { /* code 004B */
  ________,________,
  ________,________,
  ________,________,
  _XX___XX,________,
  _XX__XX_,________,
  _XX_XX__,________,
  _XX_XX__,________,
  _XXXXX__,________,
  _XXX_XX_,________,
  _XX__XX_,________,
  _XX__XX_,________,
  _XX___XX,________,
  _XX___XX,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_004C[ 16] = { /* code 004C */
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
  _XX_____,
  _XXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_004D[ 32] = { /* code 004D */
  ________,________,
  ________,________,
  ________,________,
  _XXX___X,XX______,
  _XXX___X,XX______,
  _XXXX_XX,XX______,
  _XXXX_XX,XX______,
  _XX_X_X_,XX______,
  _XX_X_X_,XX______,
  _XX_X_X_,XX______,
  _XX_XXX_,XX______,
  _XX_XXX_,XX______,
  _XX__X__,XX______,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_004E[ 32] = { /* code 004E */
  ________,________,
  ________,________,
  ________,________,
  _XX___XX,________,
  _XXX__XX,________,
  _XXX__XX,________,
  _XXXX_XX,________,
  _XX_X_XX,________,
  _XX_XXXX,________,
  _XX__XXX,________,
  _XX__XXX,________,
  _XX___XX,________,
  _XX___XX,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_004F[ 32] = { /* code 004F */
  ________,________,
  ________,________,
  ________,________,
  ___XXXX_,________,
  __XX__XX,________,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  __XX__XX,________,
  ___XXXX_,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0050[ 32] = { /* code 0050 */
  ________,________,
  ________,________,
  ________,________,
  _XXXXXX_,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XXXXXX_,________,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________,
  _XX_____,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0051[ 32] = { /* code 0051 */
  ________,________,
  ________,________,
  ________,________,
  ___XXXX_,________,
  __XX__XX,________,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX____X,X_______,
  _XX__X_X,X_______,
  __XX__XX,________,
  ___XXXXX,________,
  ________,X_______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0052[ 32] = { /* code 0052 */
  ________,________,
  ________,________,
  ________,________,
  _XXXXXX_,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XXXXXX_,________,
  _XX__XX_,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX____X,X_______,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0053[ 32] = { /* code 0053 */
  ________,________,
  ________,________,
  ________,________,
  __XXXXX_,________,
  _XX___XX,________,
  _XX_____,________,
  _XXX____,________,
  __XXXX__,________,
  ___XXXX_,________,
  _____XXX,________,
  ______XX,________,
  _XX___XX,________,
  __XXXXX_,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0054[ 16] = { /* code 0054 */
  ________,
  ________,
  ________,
  XXXXXXXX,
  ___XX___,
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

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0055[ 32] = { /* code 0055 */
  ________,________,
  ________,________,
  ________,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  __XXXXX_,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0056[ 32] = { /* code 0056 */
  ________,________,
  ________,________,
  ________,________,
  XX_____X,X_______,
  XX_____X,X_______,
  _XX___XX,________,
  _XX___XX,________,
  _XX___XX,________,
  __XX_XX_,________,
  __XX_XX_,________,
  __XX_XX_,________,
  ___XXX__,________,
  ___XXX__,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0057[ 32] = { /* code 0057 */
  ________,________,
  ________,________,
  ________,________,
  XX___XXX,___XX___,
  XX___XXX,___XX___,
  _XX__XXX,__XX____,
  _XX_XX_X,X_XX____,
  _XX_XX_X,X_XX____,
  _XX_XX_X,X_XX____,
  _XX_XX_X,X_XX____,
  __XXX___,XXX_____,
  __XXX___,XXX_____,
  __XXX___,XXX_____,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0058[ 32] = { /* code 0058 */
  ________,________,
  ________,________,
  ________,________,
  _XX___XX,________,
  _XX___XX,________,
  __XX_XX_,________,
  ___XXX__,________,
  ___XXX__,________,
  ___XXX__,________,
  ___XXX__,________,
  __XX_XX_,________,
  _XX___XX,________,
  _XX___XX,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0059[ 16] = { /* code 0059 */
  ________,
  ________,
  ________,
  XX____XX,
  XX____XX,
  _XX__XX_,
  __XXXX__,
  __XXXX__,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_005A[ 16] = { /* code 005A */
  ________,
  ________,
  ________,
  XXXXXXX_,
  _____XX_,
  ____XX__,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  _XX_____,
  XX______,
  XXXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_005B[ 16] = { /* code 005B */
  ________,
  ________,
  ________,
  _XXX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XXX____};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_005C[ 16] = { /* code 005C */
  ________,
  ________,
  ________,
  X_______,
  X_______,
  _X______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  __X_____,
  ___X____,
  ___X____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_005D[ 16] = { /* code 005D */
  ________,
  ________,
  ________,
  XXX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XXX_____};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_005E[ 16] = { /* code 005E */
  ________,
  ________,
  ________,
  ________,
  __XX____,
  __XX____,
  _XXXX___,
  _X__X___,
  XX__XX__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_005F[ 16] = { /* code 005F */
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
  XXXXXXX_};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0060[ 16] = { /* code 0060 */
  ________,
  ________,
  ________,
  XX______,
  _XX_____,
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

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0061[ 16] = { /* code 0061 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXXX__,
  _X___XX_,
  ___XXXX_,
  __XX_XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0062[ 16] = { /* code 0062 */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_XX__,
  _XXX_XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXX_XX_,
  _XX_XX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0063[ 16] = { /* code 0063 */
  ________,
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

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0064[ 16] = { /* code 0064 */
  ________,
  ________,
  ________,
  _____XX_,
  _____XX_,
  _____XX_,
  __XX_XX_,
  _XX_XXX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX_XXX_,
  __XX_XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0065[ 16] = { /* code 0065 */
  ________,
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
  _XX__XX_,
  __XXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0066[ 16] = { /* code 0066 */
  ________,
  ________,
  ________,
  __XX____,
  _XX_____,
  _XX_____,
  XXXX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0067[ 16] = { /* code 0067 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  __XX_XX_,
  _XX_XXX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX_XXX_,
  __XX_XX_,
  _____XX_,
  _X___XX_,
  __XXXX__};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0068[ 16] = { /* code 0068 */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_XX__,
  _XXX_XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0069[ 16] = { /* code 0069 */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  ________,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_006A[ 16] = { /* code 006A */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  ________,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XX______};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_006B[ 16] = { /* code 006B */
  ________,
  ________,
  ________,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX__XX_,
  _XX_XX__,
  _XXXX___,
  _XXXX___,
  _XX_XX__,
  _XX_XX__,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_006C[ 16] = { /* code 006C */
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
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_006D[ 32] = { /* code 006D */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  _XX_XXX_,XX______,
  _XXX_XXX,_XX_____,
  _XX__XX_,_XX_____,
  _XX__XX_,_XX_____,
  _XX__XX_,_XX_____,
  _XX__XX_,_XX_____,
  _XX__XX_,_XX_____,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_006E[ 16] = { /* code 006E */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_XX__,
  _XXX_XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_006F[ 16] = { /* code 006F */
  ________,
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

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0070[ 16] = { /* code 0070 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX_XX__,
  _XXX_XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXX_XX_,
  _XX_XX__,
  _XX_____,
  _XX_____,
  _XX_____};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0071[ 16] = { /* code 0071 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  __XX_XX_,
  _XX_XXX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX_XXX_,
  __XX_XX_,
  _____XX_,
  _____XX_,
  _____XX_};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0072[ 16] = { /* code 0072 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0073[ 16] = { /* code 0073 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XXX_____,
  _XXXX___,
  ___XXX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0074[ 16] = { /* code 0074 */
  ________,
  ________,
  ________,
  ________,
  __X_____,
  _XX_____,
  XXXX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  __XX____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0075[ 16] = { /* code 0075 */
  ________,
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
  _XX_XXX_,
  __XX_XX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0076[ 16] = { /* code 0076 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
  __XXX___,
  __XXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0077[ 32] = { /* code 0077 */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  XX___X__,_XX_____,
  XX__XXX_,_XX_____,
  _XX_XXX_,XX______,
  _XX_X_X_,XX______,
  _XXXX_XX,XX______,
  __XXX_XX,X_______,
  __XX___X,X_______,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0078[ 16] = { /* code 0078 */
  ________,
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

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_0079[ 16] = { /* code 0079 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
  __XXX___,
  __XXX___,
  __XXX___,
  __XX____,
  XXXX____};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_007A[ 16] = { /* code 007A */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXX__,
  ____XX__,
  ___XX___,
  __XX____,
  __XX____,
  _XX_____,
  _XXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_007B[ 16] = { /* code 007B */
  ________,
  ________,
  ________,
  __XXX___,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XX______,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  __XXX___};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_007C[ 16] = { /* code 007C */
  ________,
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  ________};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_007D[ 16] = { /* code 007D */
  ________,
  ________,
  ________,
  XXX_____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  ___XX___,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  XXX_____};

GUI_CONST_STORAGE unsigned char acFont16B_ASCII_007E[ 16] = { /* code 007E */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX__X_,
  X__XXX__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE GUI_CHARINFO GUI_Font16B_ASCII_CharInfo[95] = {
   {   4,   4,  1, acFont16B_ASCII_0020 } /* code 0020 */
  ,{   4,   4,  1, acFont16B_ASCII_0021 } /* code 0021 */
  ,{   6,   6,  1, acFont16B_ASCII_0022 } /* code 0022 */
  ,{   7,   7,  1, acFont16B_ASCII_0023 } /* code 0023 */
  ,{   7,   7,  1, acFont16B_ASCII_0024 } /* code 0024 */
  ,{  10,  10,  2, acFont16B_ASCII_0025 } /* code 0025 */
  ,{   9,   9,  2, acFont16B_ASCII_0026 } /* code 0026 */
  ,{   3,   3,  1, acFont16B_ASCII_0027 } /* code 0027 */
  ,{   4,   4,  1, acFont16B_ASCII_0028 } /* code 0028 */
  ,{   4,   4,  1, acFont16B_ASCII_0029 } /* code 0029 */
  ,{   5,   5,  1, acFont16B_ASCII_002A } /* code 002A */
  ,{   8,   8,  1, acFont16B_ASCII_002B } /* code 002B */
  ,{   4,   4,  1, acFont16B_ASCII_002C } /* code 002C */
  ,{   4,   4,  1, acFont16B_ASCII_002D } /* code 002D */
  ,{   4,   4,  1, acFont16B_ASCII_002E } /* code 002E */
  ,{   4,   4,  1, acFont16B_ASCII_002F } /* code 002F */
  ,{   7,   7,  1, acFont16B_ASCII_0030 } /* code 0030 */
  ,{   7,   7,  1, acFont16B_ASCII_0031 } /* code 0031 */
  ,{   7,   7,  1, acFont16B_ASCII_0032 } /* code 0032 */
  ,{   7,   7,  1, acFont16B_ASCII_0033 } /* code 0033 */
  ,{   7,   7,  1, acFont16B_ASCII_0034 } /* code 0034 */
  ,{   7,   7,  1, acFont16B_ASCII_0035 } /* code 0035 */
  ,{   7,   7,  1, acFont16B_ASCII_0036 } /* code 0036 */
  ,{   7,   7,  1, acFont16B_ASCII_0037 } /* code 0037 */
  ,{   7,   7,  1, acFont16B_ASCII_0038 } /* code 0038 */
  ,{   7,   7,  1, acFont16B_ASCII_0039 } /* code 0039 */
  ,{   4,   4,  1, acFont16B_ASCII_003A } /* code 003A */
  ,{   4,   4,  1, acFont16B_ASCII_003B } /* code 003B */
  ,{   8,   8,  1, acFont16B_ASCII_003C } /* code 003C */
  ,{   8,   8,  1, acFont16B_ASCII_003D } /* code 003D */
  ,{   8,   8,  1, acFont16B_ASCII_003E } /* code 003E */
  ,{   8,   8,  1, acFont16B_ASCII_003F } /* code 003F */
  ,{  13,  13,  2, acFont16B_ASCII_0040 } /* code 0040 */
  ,{   9,   9,  2, acFont16B_ASCII_0041 } /* code 0041 */
  ,{   9,   9,  2, acFont16B_ASCII_0042 } /* code 0042 */
  ,{   9,   9,  2, acFont16B_ASCII_0043 } /* code 0043 */
  ,{   9,   9,  2, acFont16B_ASCII_0044 } /* code 0044 */
  ,{   8,   8,  1, acFont16B_ASCII_0045 } /* code 0045 */
  ,{   8,   8,  1, acFont16B_ASCII_0046 } /* code 0046 */
  ,{  10,  10,  2, acFont16B_ASCII_0047 } /* code 0047 */
  ,{   9,   9,  2, acFont16B_ASCII_0048 } /* code 0048 */
  ,{   4,   4,  1, acFont16B_ASCII_0049 } /* code 0049 */
  ,{   7,   7,  1, acFont16B_ASCII_004A } /* code 004A */
  ,{   9,   9,  2, acFont16B_ASCII_004B } /* code 004B */
  ,{   8,   8,  1, acFont16B_ASCII_004C } /* code 004C */
  ,{  11,  11,  2, acFont16B_ASCII_004D } /* code 004D */
  ,{   9,   9,  2, acFont16B_ASCII_004E } /* code 004E */
  ,{  10,  10,  2, acFont16B_ASCII_004F } /* code 004F */
  ,{   9,   9,  2, acFont16B_ASCII_0050 } /* code 0050 */
  ,{  10,  10,  2, acFont16B_ASCII_0051 } /* code 0051 */
  ,{   9,   9,  2, acFont16B_ASCII_0052 } /* code 0052 */
  ,{   9,   9,  2, acFont16B_ASCII_0053 } /* code 0053 */
  ,{   8,   8,  1, acFont16B_ASCII_0054 } /* code 0054 */
  ,{   9,   9,  2, acFont16B_ASCII_0055 } /* code 0055 */
  ,{   9,   9,  2, acFont16B_ASCII_0056 } /* code 0056 */
  ,{  13,  13,  2, acFont16B_ASCII_0057 } /* code 0057 */
  ,{   9,   9,  2, acFont16B_ASCII_0058 } /* code 0058 */
  ,{   8,   8,  1, acFont16B_ASCII_0059 } /* code 0059 */
  ,{   7,   7,  1, acFont16B_ASCII_005A } /* code 005A */
  ,{   4,   4,  1, acFont16B_ASCII_005B } /* code 005B */
  ,{   4,   4,  1, acFont16B_ASCII_005C } /* code 005C */
  ,{   4,   4,  1, acFont16B_ASCII_005D } /* code 005D */
  ,{   8,   8,  1, acFont16B_ASCII_005E } /* code 005E */
  ,{   7,   7,  1, acFont16B_ASCII_005F } /* code 005F */
  ,{   4,   4,  1, acFont16B_ASCII_0060 } /* code 0060 */
  ,{   8,   8,  1, acFont16B_ASCII_0061 } /* code 0061 */
  ,{   8,   8,  1, acFont16B_ASCII_0062 } /* code 0062 */
  ,{   7,   7,  1, acFont16B_ASCII_0063 } /* code 0063 */
  ,{   8,   8,  1, acFont16B_ASCII_0064 } /* code 0064 */
  ,{   8,   8,  1, acFont16B_ASCII_0065 } /* code 0065 */
  ,{   4,   4,  1, acFont16B_ASCII_0066 } /* code 0066 */
  ,{   8,   8,  1, acFont16B_ASCII_0067 } /* code 0067 */
  ,{   8,   8,  1, acFont16B_ASCII_0068 } /* code 0068 */
  ,{   4,   4,  1, acFont16B_ASCII_0069 } /* code 0069 */
  ,{   4,   4,  1, acFont16B_ASCII_006A } /* code 006A */
  ,{   7,   7,  1, acFont16B_ASCII_006B } /* code 006B */
  ,{   4,   4,  1, acFont16B_ASCII_006C } /* code 006C */
  ,{  12,  12,  2, acFont16B_ASCII_006D } /* code 006D */
  ,{   8,   8,  1, acFont16B_ASCII_006E } /* code 006E */
  ,{   8,   8,  1, acFont16B_ASCII_006F } /* code 006F */
  ,{   8,   8,  1, acFont16B_ASCII_0070 } /* code 0070 */
  ,{   8,   8,  1, acFont16B_ASCII_0071 } /* code 0071 */
  ,{   5,   5,  1, acFont16B_ASCII_0072 } /* code 0072 */
  ,{   6,   6,  1, acFont16B_ASCII_0073 } /* code 0073 */
  ,{   4,   4,  1, acFont16B_ASCII_0074 } /* code 0074 */
  ,{   8,   8,  1, acFont16B_ASCII_0075 } /* code 0075 */
  ,{   7,   7,  1, acFont16B_ASCII_0076 } /* code 0076 */
  ,{  11,  11,  2, acFont16B_ASCII_0077 } /* code 0077 */
  ,{   8,   8,  1, acFont16B_ASCII_0078 } /* code 0078 */
  ,{   7,   7,  1, acFont16B_ASCII_0079 } /* code 0079 */
  ,{   7,   7,  1, acFont16B_ASCII_007A } /* code 007A */
  ,{   5,   5,  1, acFont16B_ASCII_007B } /* code 007B */
  ,{   3,   3,  1, acFont16B_ASCII_007C } /* code 007C */
  ,{   5,   5,  1, acFont16B_ASCII_007D } /* code 007D */
  ,{   8,   8,  1, acFont16B_ASCII_007E } /* code 007E */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font16B_ASCII_Prop1 = {
   0x0020                         /* first character */
  ,0x007E                         /* last character  */
  ,&GUI_Font16B_ASCII_CharInfo[0] /* address of first character */
  ,(GUI_CONST_STORAGE GUI_FONT_PROP*)0        /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font16B_ASCII = {
   GUI_FONTTYPE_PROP        /* type of font    */
  ,16                       /* height of font  */
  ,16                       /* space of font y */
  ,1                        /* magnification x */
  ,1                        /* magnification y */
  ,{&GUI_Font16B_ASCII_Prop1}
  ,13, 7, 10
};

