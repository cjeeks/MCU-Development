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
File        : F13HB_ASCII.C
Purpose     : ASCII character set, bold, high
Height      : 13
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"

/* Start of unicode area <Basic Latin> */
GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0020[ 13] = { /* code 0020 */
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

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0021[ 13] = { /* code 0021 */
  ________,
  ________,
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
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0022[ 13] = { /* code 0022 */
  ________,
  XX_XX___,
  XX_XX___,
  XX_XX___,
  XX_XX___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0023[ 26] = { /* code 0023 */
  ________,________,
  ________,________,
  ___X__X_,________,
  ___X__X_,________,
  _XXXXXXX,________,
  _XXXXXXX,________,
  __X__X__,________,
  XXXXXXX_,________,
  XXXXXXX_,________,
  _X__X___,________,
  _X__X___,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0024[ 13] = { /* code 0024 */
  ___X____,
  ___X____,
  _XXXXX__,
  XX_X__X_,
  XX_X____,
  XX_X____,
  _XXXXX__,
  ___X_XX_,
  ___X_XX_,
  X__X_XX_,
  _XXXXX__,
  ___X____,
  ___X____};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0025[ 26] = { /* code 0025 */
  ________,________,
  ________,________,
  _XXXX___,________,
  XX__XX__,_X______,
  XX__XX__,X_______,
  XX__XX_X,________,
  _XXXX_X_,XXXX____,
  _____X_X,X__XX___,
  ____X__X,X__XX___,
  ___X___X,X__XX___,
  ________,XXXX____,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0026[ 26] = { /* code 0026 */
  ________,________,
  ________,________,
  __XXXX__,________,
  _XX__XX_,________,
  _XX__XX_,________,
  _XX__XX_,________,
  __XXXX__,XX______,
  _XX__XX_,XX______,
  _XX___XX,X_______,
  _XX___XX,________,
  __XXXX_X,XX______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0027[ 13] = { /* code 0027 */
  ________,
  _XX_____,
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
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0028[ 13] = { /* code 0028 */
  ________,
  ___XX___,
  __XX____,
  __XX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  __XX____,
  __XX____,
  ___XX___};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0029[ 13] = { /* code 0029 */
  ________,
  _XX_____,
  __XX____,
  __XX____,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  _XX_____};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_002A[ 13] = { /* code 002A */
  ________,
  ___XX___,
  _X_XX_X_,
  __XXXX__,
  _X_XX_X_,
  ___XX___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_002B[ 26] = { /* code 002B */
  ________,________,
  ________,________,
  ________,________,
  _____X__,________,
  _____X__,________,
  _____X__,________,
  __XXXXXX,X_______,
  _____X__,________,
  _____X__,________,
  _____X__,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_002C[ 13] = { /* code 002C */
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
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_002D[ 13] = { /* code 002D */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXX___,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_002E[ 13] = { /* code 002E */
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
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_002F[ 13] = { /* code 002F */
  ________,
  _____X__,
  _____X__,
  ____X___,
  ____X___,
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0030[ 13] = { /* code 0030 */
  ________,
  ________,
  _XXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0031[ 13] = { /* code 0031 */
  ________,
  ________,
  ___XX___,
  _XXXX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  _XXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0032[ 13] = { /* code 0032 */
  ________,
  ________,
  _XXXXX__,
  X____XX_,
  X____XX_,
  _____XX_,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  XXXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0033[ 13] = { /* code 0033 */
  ________,
  ________,
  _XXXXX__,
  X____XX_,
  _____XX_,
  _____XX_,
  __XXXX__,
  _____XX_,
  _____XX_,
  X____XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0034[ 13] = { /* code 0034 */
  ________,
  ________,
  ____XX__,
  ___XXX__,
  __X_XX__,
  _X__XX__,
  X___XX__,
  XXXXXXX_,
  ____XX__,
  ____XX__,
  ____XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0035[ 13] = { /* code 0035 */
  ________,
  ________,
  _XXXXXX_,
  _XX_____,
  _XX_____,
  _XXXXX__,
  _____XX_,
  _____XX_,
  _____XX_,
  X____XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0036[ 13] = { /* code 0036 */
  ________,
  ________,
  __XXXX__,
  _XX_____,
  XX______,
  XXXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0037[ 13] = { /* code 0037 */
  ________,
  ________,
  XXXXXXX_,
  _____XX_,
  ____XX__,
  ____XX__,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0038[ 13] = { /* code 0038 */
  ________,
  ________,
  _XXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0039[ 13] = { /* code 0039 */
  ________,
  ________,
  _XXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXXX_,
  _____XX_,
  ____XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_003A[ 13] = { /* code 003A */
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
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_003B[ 13] = { /* code 003B */
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
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_003C[ 26] = { /* code 003C */
  ________,________,
  ________,________,
  ________,________,
  _______X,X_______,
  _____XX_,________,
  ___XX___,________,
  _XX_____,________,
  _XX_____,________,
  ___XX___,________,
  _____XX_,________,
  _______X,X_______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_003D[ 26] = { /* code 003D */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  _XXXXXXX,X_______,
  ________,________,
  ________,________,
  _XXXXXXX,X_______,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_003E[ 26] = { /* code 003E */
  ________,________,
  ________,________,
  ________,________,
  _XX_____,________,
  ___XX___,________,
  _____XX_,________,
  _______X,X_______,
  _______X,X_______,
  _____XX_,________,
  ___XX___,________,
  _XX_____,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_003F[ 13] = { /* code 003F */
  ________,
  ________,
  _XXXX___,
  X___XX__,
  ____XX__,
  ___XX___,
  __XX____,
  __XX____,
  ________,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0040[ 26] = { /* code 0040 */
  ________,________,
  ________,________,
  __XXXXX_,________,
  _X_____X,________,
  X__XXXX_,X_______,
  X_XX_XX_,X_______,
  X_XX_XX_,X_______,
  X_XX_XX_,X_______,
  X_XX_XX_,X_______,
  X__XX_XX,________,
  _X______,________,
  __XXXXXX,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0041[ 26] = { /* code 0041 */
  ________,________,
  ________,________,
  ___XXX__,________,
  ___XXX__,________,
  __XX_XX_,________,
  __XX_XX_,________,
  _XX___XX,________,
  _XXXXXXX,________,
  _XX___XX,________,
  XX_____X,X_______,
  XX_____X,X_______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0042[ 13] = { /* code 0042 */
  ________,
  ________,
  XXXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0043[ 13] = { /* code 0043 */
  ________,
  ________,
  _XXXXX__,
  XX____X_,
  XX____X_,
  XX______,
  XX______,
  XX______,
  XX____X_,
  XX____X_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0044[ 26] = { /* code 0044 */
  ________,________,
  ________,________,
  XXXXXX__,________,
  XX___XX_,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX___XX_,________,
  XXXXXX__,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0045[ 13] = { /* code 0045 */
  ________,
  ________,
  XXXXXX__,
  XX______,
  XX______,
  XX______,
  XXXXX___,
  XX______,
  XX______,
  XX______,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0046[ 13] = { /* code 0046 */
  ________,
  ________,
  XXXXXX__,
  XX______,
  XX______,
  XX______,
  XXXXX___,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0047[ 13] = { /* code 0047 */
  ________,
  ________,
  _XXXXX__,
  XX____X_,
  XX____X_,
  XX______,
  XX__XXX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0048[ 26] = { /* code 0048 */
  ________,________,
  ________,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XXXXXXXX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0049[ 13] = { /* code 0049 */
  ________,
  ________,
  XXXX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_004A[ 13] = { /* code 004A */
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
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_004B[ 13] = { /* code 004B */
  ________,
  ________,
  XX___XX_,
  XX__XX__,
  XX_XX___,
  XXXX____,
  XXX_____,
  XXXX____,
  XX_XX___,
  XX__XX__,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_004C[ 13] = { /* code 004C */
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_004D[ 26] = { /* code 004D */
  ________,________,
  ________,________,
  XXX____X,XX______,
  XXX____X,XX______,
  X_XX__X_,XX______,
  X_XX__X_,XX______,
  X__XXX__,XX______,
  X__XXX__,XX______,
  X___X___,XX______,
  X___X___,XX______,
  X_______,XX______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_004E[ 13] = { /* code 004E */
  ________,
  ________,
  XXX___X_,
  XXX___X_,
  X_XX__X_,
  X_XX__X_,
  X__XX_X_,
  X__XX_X_,
  X___XXX_,
  X___XXX_,
  X____XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_004F[ 26] = { /* code 004F */
  ________,________,
  ________,________,
  _XXXXXX_,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  _XXXXXX_,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0050[ 13] = { /* code 0050 */
  ________,
  ________,
  XXXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXX__,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0051[ 26] = { /* code 0051 */
  ________,________,
  ________,________,
  _XXXXXX_,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  _XXXXXX_,________,
  _____XX_,________,
  ______XX,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0052[ 26] = { /* code 0052 */
  ________,________,
  ________,________,
  XXXXXX__,________,
  XX___XX_,________,
  XX___XX_,________,
  XX___XX_,________,
  XXXXXX__,________,
  XX_XX___,________,
  XX__XX__,________,
  XX___XX_,________,
  XX____XX,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0053[ 13] = { /* code 0053 */
  ________,
  ________,
  _XXXXX__,
  XX____X_,
  XX____X_,
  XX______,
  _XXXXX__,
  _____XX_,
  X____XX_,
  X____XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0054[ 13] = { /* code 0054 */
  ________,
  ________,
  XXXXXX__,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0055[ 13] = { /* code 0055 */
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0056[ 26] = { /* code 0056 */
  ________,________,
  ________,________,
  XX____XX,________,
  XX____XX,________,
  XX____XX,________,
  _XX__XX_,________,
  _XX__XX_,________,
  __XXXX__,________,
  __XXXX__,________,
  ___XX___,________,
  ___XX___,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0057[ 26] = { /* code 0057 */
  ________,________,
  ________,________,
  XX___XX_,__XX____,
  XX___XX_,__XX____,
  XX___XX_,__XX____,
  XX__XXXX,__XX____,
  _XX_XXXX,_XX_____,
  _XXXX__X,XXX_____,
  _XXXX__X,XXX_____,
  __XX____,XX______,
  __XX____,XX______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0058[ 26] = { /* code 0058 */
  ________,________,
  ________,________,
  XX____XX,________,
  XX____XX,________,
  _XX__XX_,________,
  __XXXX__,________,
  ___XX___,________,
  __XXXX__,________,
  _XX__XX_,________,
  XX____XX,________,
  XX____XX,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0059[ 26] = { /* code 0059 */
  ________,________,
  ________,________,
  XX____XX,________,
  XX____XX,________,
  _XX__XX_,________,
  _XX__XX_,________,
  __XXXX__,________,
  ___XX___,________,
  ___XX___,________,
  ___XX___,________,
  ___XX___,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_005A[ 13] = { /* code 005A */
  ________,
  ________,
  XXXXXX__,
  ____XX__,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  XX______,
  XX______,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_005B[ 13] = { /* code 005B */
  ________,
  _XXXX___,
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
  _XXXX___};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_005C[ 13] = { /* code 005C */
  ________,
  X_______,
  X_______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  ___X____,
  ___X____,
  ____X___,
  ____X___,
  _____X__,
  _____X__};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_005D[ 13] = { /* code 005D */
  ________,
  _XXXX___,
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
  _XXXX___};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_005E[ 26] = { /* code 005E */
  ________,________,
  ________,________,
  ____XX__,________,
  ___X__X_,________,
  __X____X,________,
  _X______,X_______,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_005F[ 13] = { /* code 005F */
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

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0060[ 13] = { /* code 0060 */
  ________,
  __XX____,
  ___XX___,
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

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0061[ 13] = { /* code 0061 */
  ________,
  ________,
  ________,
  ________,
  __XXXX__,
  _X___XX_,
  _____XX_,
  _XXXXXX_,
  XX___XX_,
  XX___XX_,
  _XXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0062[ 13] = { /* code 0062 */
  ________,
  XX______,
  XX______,
  XX______,
  XX_XXX__,
  XXX__XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0063[ 13] = { /* code 0063 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX___X__,
  XX______,
  XX______,
  XX______,
  XX___X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0064[ 13] = { /* code 0064 */
  ________,
  _____XX_,
  _____XX_,
  _____XX_,
  _XXXXXX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX__XXX_,
  _XXX_XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0065[ 13] = { /* code 0065 */
  ________,
  ________,
  ________,
  ________,
  _XXXXX__,
  XX___XX_,
  XX___XX_,
  XXXXXXX_,
  XX______,
  XX____X_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0066[ 13] = { /* code 0066 */
  ________,
  __XXX___,
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
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0067[ 13] = { /* code 0067 */
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX__XXX_,
  _XXX_XX_,
  _____XX_,
  _XXXXX__};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0068[ 13] = { /* code 0068 */
  ________,
  XX______,
  XX______,
  XX______,
  XX_XXX__,
  XXX__XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0069[ 13] = { /* code 0069 */
  ________,
  XX______,
  XX______,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_006A[ 13] = { /* code 006A */
  ________,
  _XX_____,
  _XX_____,
  ________,
  XXX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XX______};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_006B[ 13] = { /* code 006B */
  ________,
  XX______,
  XX______,
  XX______,
  XX__XX__,
  XX_XX___,
  XXXX____,
  XXX_____,
  XXXX____,
  XX_XX___,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_006C[ 13] = { /* code 006C */
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_006D[ 26] = { /* code 006D */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  XXXXX_XX,X_______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_006E[ 13] = { /* code 006E */
  ________,
  ________,
  ________,
  ________,
  XX_XXX__,
  XXX__XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_006F[ 13] = { /* code 006F */
  ________,
  ________,
  ________,
  ________,
  _XXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0070[ 13] = { /* code 0070 */
  ________,
  ________,
  ________,
  ________,
  XX_XXX__,
  XXX__XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXX__,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0071[ 13] = { /* code 0071 */
  ________,
  ________,
  ________,
  ________,
  _XXXXXX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX__XXX_,
  _XXX_XX_,
  _____XX_,
  _____XX_};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0072[ 13] = { /* code 0072 */
  ________,
  ________,
  ________,
  ________,
  XX_XX___,
  XXXXX___,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0073[ 13] = { /* code 0073 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX___X__,
  XXX_____,
  _XXXX___,
  ___XXX__,
  X___XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0074[ 13] = { /* code 0074 */
  ________,
  ________,
  _XX_____,
  _XX_____,
  XXXXX___,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0075[ 13] = { /* code 0075 */
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX__XXX_,
  _XXX_XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0076[ 13] = { /* code 0076 */
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XX_XX__,
  _XX_XX__,
  __XXX___,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0077[ 26] = { /* code 0077 */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  XX__XX__,XX______,
  XX__XX__,XX______,
  _XX_XX_X,X_______,
  _XX_XX_X,X_______,
  _XXX__XX,X_______,
  __XX__XX,________,
  __XX__XX,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0078[ 13] = { /* code 0078 */
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  __XX____,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_0079[ 13] = { /* code 0079 */
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XX_XX__,
  _XX_XX__,
  __XXX___,
  __XXX___,
  ___XX___,
  __XX____};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_007A[ 13] = { /* code 007A */
  ________,
  ________,
  ________,
  ________,
  XXXXXX__,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  XX______,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_007B[ 13] = { /* code 007B */
  ________,
  ___XXX__,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  XXX_____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  ___XXX__};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_007C[ 13] = { /* code 007C */
  ________,
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
  __XX____,
  __XX____};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_007D[ 13] = { /* code 007D */
  ________,
  XXX_____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  ___XXX__,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  XXX_____};

GUI_CONST_STORAGE unsigned char acFont13HB_ASCII_007E[ 26] = { /* code 007E */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  _XXXX___,_X______,
  XXXXXX__,_X______,
  X___XXXX,XX______,
  X____XXX,X_______,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE GUI_CHARINFO GUI_Font13HB_ASCII_CharInfo[95] = {
   {   4,   4,  1, acFont13HB_ASCII_0020 } /* code 0020 */
  ,{   5,   5,  1, acFont13HB_ASCII_0021 } /* code 0021 */
  ,{   6,   6,  1, acFont13HB_ASCII_0022 } /* code 0022 */
  ,{   9,   9,  2, acFont13HB_ASCII_0023 } /* code 0023 */
  ,{   8,   8,  1, acFont13HB_ASCII_0024 } /* code 0024 */
  ,{  14,  14,  2, acFont13HB_ASCII_0025 } /* code 0025 */
  ,{  11,  11,  2, acFont13HB_ASCII_0026 } /* code 0026 */
  ,{   4,   4,  1, acFont13HB_ASCII_0027 } /* code 0027 */
  ,{   6,   6,  1, acFont13HB_ASCII_0028 } /* code 0028 */
  ,{   6,   6,  1, acFont13HB_ASCII_0029 } /* code 0029 */
  ,{   8,   8,  1, acFont13HB_ASCII_002A } /* code 002A */
  ,{  11,  11,  2, acFont13HB_ASCII_002B } /* code 002B */
  ,{   4,   4,  1, acFont13HB_ASCII_002C } /* code 002C */
  ,{   6,   6,  1, acFont13HB_ASCII_002D } /* code 002D */
  ,{   4,   4,  1, acFont13HB_ASCII_002E } /* code 002E */
  ,{   8,   8,  1, acFont13HB_ASCII_002F } /* code 002F */
  ,{   8,   8,  1, acFont13HB_ASCII_0030 } /* code 0030 */
  ,{   8,   8,  1, acFont13HB_ASCII_0031 } /* code 0031 */
  ,{   8,   8,  1, acFont13HB_ASCII_0032 } /* code 0032 */
  ,{   8,   8,  1, acFont13HB_ASCII_0033 } /* code 0033 */
  ,{   8,   8,  1, acFont13HB_ASCII_0034 } /* code 0034 */
  ,{   8,   8,  1, acFont13HB_ASCII_0035 } /* code 0035 */
  ,{   8,   8,  1, acFont13HB_ASCII_0036 } /* code 0036 */
  ,{   8,   8,  1, acFont13HB_ASCII_0037 } /* code 0037 */
  ,{   8,   8,  1, acFont13HB_ASCII_0038 } /* code 0038 */
  ,{   8,   8,  1, acFont13HB_ASCII_0039 } /* code 0039 */
  ,{   5,   5,  1, acFont13HB_ASCII_003A } /* code 003A */
  ,{   5,   5,  1, acFont13HB_ASCII_003B } /* code 003B */
  ,{  11,  11,  2, acFont13HB_ASCII_003C } /* code 003C */
  ,{  11,  11,  2, acFont13HB_ASCII_003D } /* code 003D */
  ,{  11,  11,  2, acFont13HB_ASCII_003E } /* code 003E */
  ,{   7,   7,  1, acFont13HB_ASCII_003F } /* code 003F */
  ,{  10,  10,  2, acFont13HB_ASCII_0040 } /* code 0040 */
  ,{  10,  10,  2, acFont13HB_ASCII_0041 } /* code 0041 */
  ,{   8,   8,  1, acFont13HB_ASCII_0042 } /* code 0042 */
  ,{   8,   8,  1, acFont13HB_ASCII_0043 } /* code 0043 */
  ,{   9,   9,  2, acFont13HB_ASCII_0044 } /* code 0044 */
  ,{   7,   7,  1, acFont13HB_ASCII_0045 } /* code 0045 */
  ,{   6,   6,  1, acFont13HB_ASCII_0046 } /* code 0046 */
  ,{   8,   8,  1, acFont13HB_ASCII_0047 } /* code 0047 */
  ,{   9,   9,  2, acFont13HB_ASCII_0048 } /* code 0048 */
  ,{   5,   5,  1, acFont13HB_ASCII_0049 } /* code 0049 */
  ,{   6,   6,  1, acFont13HB_ASCII_004A } /* code 004A */
  ,{   8,   8,  1, acFont13HB_ASCII_004B } /* code 004B */
  ,{   7,   7,  1, acFont13HB_ASCII_004C } /* code 004C */
  ,{  11,  11,  2, acFont13HB_ASCII_004D } /* code 004D */
  ,{   8,   8,  1, acFont13HB_ASCII_004E } /* code 004E */
  ,{   9,   9,  2, acFont13HB_ASCII_004F } /* code 004F */
  ,{   8,   8,  1, acFont13HB_ASCII_0050 } /* code 0050 */
  ,{   9,   9,  2, acFont13HB_ASCII_0051 } /* code 0051 */
  ,{   9,   9,  2, acFont13HB_ASCII_0052 } /* code 0052 */
  ,{   8,   8,  1, acFont13HB_ASCII_0053 } /* code 0053 */
  ,{   7,   7,  1, acFont13HB_ASCII_0054 } /* code 0054 */
  ,{   8,   8,  1, acFont13HB_ASCII_0055 } /* code 0055 */
  ,{   9,   9,  2, acFont13HB_ASCII_0056 } /* code 0056 */
  ,{  13,  13,  2, acFont13HB_ASCII_0057 } /* code 0057 */
  ,{   9,   9,  2, acFont13HB_ASCII_0058 } /* code 0058 */
  ,{   9,   9,  2, acFont13HB_ASCII_0059 } /* code 0059 */
  ,{   7,   7,  1, acFont13HB_ASCII_005A } /* code 005A */
  ,{   6,   6,  1, acFont13HB_ASCII_005B } /* code 005B */
  ,{   8,   8,  1, acFont13HB_ASCII_005C } /* code 005C */
  ,{   6,   6,  1, acFont13HB_ASCII_005D } /* code 005D */
  ,{  11,  11,  2, acFont13HB_ASCII_005E } /* code 005E */
  ,{   8,   8,  1, acFont13HB_ASCII_005F } /* code 005F */
  ,{   7,   7,  1, acFont13HB_ASCII_0060 } /* code 0060 */
  ,{   8,   8,  1, acFont13HB_ASCII_0061 } /* code 0061 */
  ,{   8,   8,  1, acFont13HB_ASCII_0062 } /* code 0062 */
  ,{   7,   7,  1, acFont13HB_ASCII_0063 } /* code 0063 */
  ,{   8,   8,  1, acFont13HB_ASCII_0064 } /* code 0064 */
  ,{   8,   8,  1, acFont13HB_ASCII_0065 } /* code 0065 */
  ,{   5,   5,  1, acFont13HB_ASCII_0066 } /* code 0066 */
  ,{   8,   8,  1, acFont13HB_ASCII_0067 } /* code 0067 */
  ,{   8,   8,  1, acFont13HB_ASCII_0068 } /* code 0068 */
  ,{   3,   3,  1, acFont13HB_ASCII_0069 } /* code 0069 */
  ,{   4,   4,  1, acFont13HB_ASCII_006A } /* code 006A */
  ,{   7,   7,  1, acFont13HB_ASCII_006B } /* code 006B */
  ,{   3,   3,  1, acFont13HB_ASCII_006C } /* code 006C */
  ,{  11,  11,  2, acFont13HB_ASCII_006D } /* code 006D */
  ,{   8,   8,  1, acFont13HB_ASCII_006E } /* code 006E */
  ,{   8,   8,  1, acFont13HB_ASCII_006F } /* code 006F */
  ,{   8,   8,  1, acFont13HB_ASCII_0070 } /* code 0070 */
  ,{   8,   8,  1, acFont13HB_ASCII_0071 } /* code 0071 */
  ,{   6,   6,  1, acFont13HB_ASCII_0072 } /* code 0072 */
  ,{   7,   7,  1, acFont13HB_ASCII_0073 } /* code 0073 */
  ,{   6,   6,  1, acFont13HB_ASCII_0074 } /* code 0074 */
  ,{   8,   8,  1, acFont13HB_ASCII_0075 } /* code 0075 */
  ,{   8,   8,  1, acFont13HB_ASCII_0076 } /* code 0076 */
  ,{  11,  11,  2, acFont13HB_ASCII_0077 } /* code 0077 */
  ,{   7,   7,  1, acFont13HB_ASCII_0078 } /* code 0078 */
  ,{   8,   8,  1, acFont13HB_ASCII_0079 } /* code 0079 */
  ,{   7,   7,  1, acFont13HB_ASCII_007A } /* code 007A */
  ,{   7,   7,  1, acFont13HB_ASCII_007B } /* code 007B */
  ,{   7,   7,  1, acFont13HB_ASCII_007C } /* code 007C */
  ,{   7,   7,  1, acFont13HB_ASCII_007D } /* code 007D */
  ,{  11,  11,  2, acFont13HB_ASCII_007E } /* code 007E */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font13HB_ASCII_Prop1 = {
   0x0020                           /* first character */
  ,0x007E                           /* last character  */
  ,&GUI_Font13HB_ASCII_CharInfo[0]  /* address of first character */
  ,(const GUI_FONT_PROP*)0          /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font13HB_ASCII = {
   GUI_FONTTYPE_PROP          /* type of font    */
  ,13                         /* height of font  */
  ,13                         /* space of font y */
  ,1                          /* magnification x */
  ,1                          /* magnification y */
  ,{&GUI_Font13HB_ASCII_Prop1}
  , 11, 7, 9
};

