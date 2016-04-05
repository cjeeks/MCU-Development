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
File        : F13B_ASCII.c
Purpose     : Proportional Font, ASCII characters, bold
Height      : 13
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"


/* Start of unicode area <Basic Latin> */

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0020[ 13] = { /* code 0020 */
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

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0021[ 13] = { /* code 0021 */
  ________,
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0022[ 13] = { /* code 0022 */
  ________,
  ________,
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

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0023[ 26] = { /* code 0023 */
  ________,________,
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
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0024[ 13] = { /* code 0024 */
  ________,
  ________,
  ___X____,
  ___X____,
  _XXXX___,
  XX_X_X__,
  XX_X____,
  _XXXX___,
  __X_XX__,
  X_X_XX__,
  _XXXX___,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0025[ 26] = { /* code 0025 */
  ________,________,
  ________,________,
  ________,________,
  _XXX___X,________,
  XX_XX__X,________,
  XX_XX_X_,________,
  XX_XX_X_,XXX_____,
  _XXX_X_X,X_XX____,
  _____X_X,X_XX____,
  ____X__X,X_XX____,
  ____X___,XXX_____,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0026[ 26] = { /* code 0026 */
  ________,________,
  ________,________,
  ________,________,
  _XXX____,________,
  XX_XX___,________,
  XX_XX___,________,
  _XXX__XX,________,
  XX_XX_X_,________,
  XX__XX__,________,
  XX___XX_,________,
  _XXXX_XX,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0027[ 13] = { /* code 0027 */
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0028[ 13] = { /* code 0028 */
  ________,
  ________,
  __XX____,
  _XX_____,
  _XX_____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  _XX_____,
  _XX_____,
  __XX____};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0029[ 13] = { /* code 0029 */
  ________,
  ________,
  XX______,
  _XX_____,
  _XX_____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  _XX_____,
  _XX_____,
  XX______};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_002A[ 13] = { /* code 002A */
  ________,
  ________,
  __XX____,
  X_XX_X__,
  _XXXX___,
  X_XX_X__,
  __XX____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_002B[ 26] = { /* code 002B */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ____X___,________,
  ____X___,________,
  ____X___,________,
  _XXXXXXX,________,
  ____X___,________,
  ____X___,________,
  ____X___,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_002C[ 13] = { /* code 002C */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_002D[ 13] = { /* code 002D */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXX____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_002E[ 13] = { /* code 002E */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_002F[ 13] = { /* code 002F */
  ________,
  ________,
  ____X___,
  ____X___,
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0030[ 13] = { /* code 0030 */
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
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0031[ 13] = { /* code 0031 */
  ________,
  ________,
  ________,
  __XX____,
  _XXX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0032[ 13] = { /* code 0032 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  XX______,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0033[ 13] = { /* code 0033 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  ____XX__,
  __XXX___,
  ____XX__,
  ____XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0034[ 13] = { /* code 0034 */
  ________,
  ________,
  ________,
  ____X___,
  ___XX___,
  __XXX___,
  _X_XX___,
  X__XX___,
  XXXXXX__,
  ___XX___,
  ___XX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0035[ 13] = { /* code 0035 */
  ________,
  ________,
  ________,
  _XXXXX__,
  _XX_____,
  _XX_____,
  _XXXX___,
  ____XX__,
  ____XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0036[ 13] = { /* code 0036 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX______,
  XX______,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0037[ 13] = { /* code 0037 */
  ________,
  ________,
  ________,
  XXXXXX__,
  ____XX__,
  ___XX___,
  ___XX___,
  ___XX___,
  __XX____,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0038[ 13] = { /* code 0038 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0039[ 13] = { /* code 0039 */
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ____XX__,
  ____XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_003A[ 13] = { /* code 003A */
  ________,
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  ________,
  ________,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_003B[ 13] = { /* code 003B */
  ________,
  ________,
  ________,
  ________,
  ________,
  XX______,
  XX______,
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_003C[ 26] = { /* code 003C */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ______XX,________,
  ____XX__,________,
  __XX____,________,
  _X______,________,
  __XX____,________,
  ____XX__,________,
  ______XX,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_003D[ 26] = { /* code 003D */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  _XXXXXXX,________,
  ________,________,
  ________,________,
  _XXXXXXX,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_003E[ 26] = { /* code 003E */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  _XX_____,________,
  ___XX___,________,
  _____XX_,________,
  _______X,________,
  _____XX_,________,
  ___XX___,________,
  _XX_____,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_003F[ 13] = { /* code 003F */
  ________,
  ________,
  ________,
  _XXX____,
  X__XX___,
  ___XX___,
  __XX____,
  _XX_____,
  _XX_____,
  ________,
  _XX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0040[ 26] = { /* code 0040 */
  ________,________,
  ________,________,
  ________,________,
  __XXXXX_,________,
  _X_____X,________,
  X__XXXX_,X_______,
  X_XX_XX_,X_______,
  X_XX_XX_,X_______,
  X_XX_XX_,X_______,
  X__XX_XX,________,
  _X______,________,
  __XXXXX_,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0041[ 13] = { /* code 0041 */
  ________,
  ________,
  ________,
  __XXX___,
  __XXX___,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
  XXXXXXX_,
  XX___XX_,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0042[ 13] = { /* code 0042 */
  ________,
  ________,
  ________,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0043[ 13] = { /* code 0043 */
  ________,
  ________,
  ________,
  _XXXXX__,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0044[ 13] = { /* code 0044 */
  ________,
  ________,
  ________,
  XXXXX___,
  XX__XX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX__XX__,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0045[ 13] = { /* code 0045 */
  ________,
  ________,
  ________,
  XXXXX___,
  XX______,
  XX______,
  XXXXX___,
  XX______,
  XX______,
  XX______,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0046[ 13] = { /* code 0046 */
  ________,
  ________,
  ________,
  XXXXX___,
  XX______,
  XX______,
  XXXXX___,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0047[ 13] = { /* code 0047 */
  ________,
  ________,
  ________,
  _XXXXXX_,
  XX______,
  XX______,
  XX______,
  XX__XXX_,
  XX___XX_,
  XX___XX_,
  _XXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0048[ 13] = { /* code 0048 */
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XXXXXXX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0049[ 13] = { /* code 0049 */
  ________,
  ________,
  ________,
  XXXX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_004A[ 13] = { /* code 004A */
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
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_004B[ 13] = { /* code 004B */
  ________,
  ________,
  ________,
  XX__XX__,
  XX_XX___,
  XXXX____,
  XXX_____,
  XXX_____,
  XXXX____,
  XX_XX___,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_004C[ 13] = { /* code 004C */
  ________,
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_004D[ 26] = { /* code 004D */
  ________,________,
  ________,________,
  ________,________,
  XX_____X,X_______,
  XXX___XX,X_______,
  XXXX_XXX,X_______,
  X_XXXX_X,X_______,
  X__XX__X,X_______,
  X______X,X_______,
  X______X,X_______,
  X______X,X_______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_004E[ 13] = { /* code 004E */
  ________,
  ________,
  ________,
  XX___X__,
  XXX__X__,
  XXXX_X__,
  X_XXXX__,
  X__XXX__,
  X___XX__,
  X____X__,
  X____X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_004F[ 13] = { /* code 004F */
  ________,
  ________,
  ________,
  _XXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0050[ 13] = { /* code 0050 */
  ________,
  ________,
  ________,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XXXXX___,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0051[ 13] = { /* code 0051 */
  ________,
  ________,
  ________,
  _XXXXX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XXXXX__,
  ___XX___,
  ____XXX_};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0052[ 13] = { /* code 0052 */
  ________,
  ________,
  ________,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XXXXX___,
  XX_XX___,
  XX__XX__,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0053[ 13] = { /* code 0053 */
  ________,
  ________,
  ________,
  _XXXXX__,
  XX______,
  XX______,
  XXXXX___,
  _XXXXX__,
  ____XX__,
  ____XX__,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0054[ 13] = { /* code 0054 */
  ________,
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
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0055[ 13] = { /* code 0055 */
  ________,
  ________,
  ________,
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

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0056[ 13] = { /* code 0056 */
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  _XXXX___,
  _XXXX___,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0057[ 26] = { /* code 0057 */
  ________,________,
  ________,________,
  ________,________,
  XX__XX__,XX______,
  XX__XX__,XX______,
  XX__XX__,XX______,
  _XX_XX_X,X_______,
  _XXXXXXX,X_______,
  _XXX__XX,X_______,
  __XX__XX,________,
  __XX__XX,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0058[ 13] = { /* code 0058 */
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  __XX____,
  __XX____,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0059[ 13] = { /* code 0059 */
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  _XXXX___,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_005A[ 13] = { /* code 005A */
  ________,
  ________,
  ________,
  XXXXXX__,
  ____XX__,
  ___XXX__,
  __XXX___,
  _XXX____,
  XXX_____,
  XX______,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_005B[ 13] = { /* code 005B */
  ________,
  ________,
  XXXX____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XXXX____};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_005C[ 13] = { /* code 005C */
  ________,
  ________,
  X_______,
  X_______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  __X_____,
  ___X____,
  ___X____,
  ____X___,
  ____X___};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_005D[ 13] = { /* code 005D */
  ________,
  ________,
  XXXX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  XXXX____};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_005E[ 26] = { /* code 005E */
  ________,________,
  ________,________,
  ________,________,
  ___X____,________,
  __X_X___,________,
  _X___X__,________,
  X_____X_,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_005F[ 13] = { /* code 005F */
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

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0060[ 13] = { /* code 0060 */
  ________,
  ________,
  _XX_____,
  __XX____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0061[ 13] = { /* code 0061 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  ____XX__,
  _XXXXX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0062[ 13] = { /* code 0062 */
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0063[ 13] = { /* code 0063 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX______,
  XX______,
  XX______,
  XX______,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0064[ 13] = { /* code 0064 */
  ________,
  ________,
  ____XX__,
  ____XX__,
  ____XX__,
  _XXXXX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0065[ 13] = { /* code 0065 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XXXXXX__,
  XX______,
  XX______,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0066[ 13] = { /* code 0066 */
  ________,
  ________,
  _XXX____,
  XX______,
  XX______,
  XXX_____,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0067[ 13] = { /* code 0067 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ____XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0068[ 13] = { /* code 0068 */
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0069[ 13] = { /* code 0069 */
  ________,
  ________,
  ________,
  XX______,
  ________,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_006A[ 13] = { /* code 006A */
  ________,
  ________,
  ________,
  _XX_____,
  ________,
  XXX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  XX______};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_006B[ 13] = { /* code 006B */
  ________,
  ________,
  XX______,
  XX______,
  XX______,
  XX__XX__,
  XX_XX___,
  XXXX____,
  XXXX____,
  XX_XX___,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_006C[ 13] = { /* code 006C */
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
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_006D[ 26] = { /* code 006D */
  ________,________,
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
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_006E[ 13] = { /* code 006E */
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_006F[ 13] = { /* code 006F */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0070[ 13] = { /* code 0070 */
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XXXXX___,
  XX______,
  XX______};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0071[ 13] = { /* code 0071 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXXX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ____XX__,
  ____XX__};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0072[ 13] = { /* code 0072 */
  ________,
  ________,
  ________,
  ________,
  ________,
  XX_X____,
  XXXX____,
  XX______,
  XX______,
  XX______,
  XX______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0073[ 13] = { /* code 0073 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX______,
  XXXX____,
  _XXXX___,
  ___XX___,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0074[ 13] = { /* code 0074 */
  ________,
  ________,
  ________,
  XX______,
  XX______,
  XXXX____,
  XX______,
  XX______,
  XX______,
  XX______,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0075[ 13] = { /* code 0075 */
  ________,
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0076[ 13] = { /* code 0076 */
  ________,
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  _XXXX___,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0077[ 26] = { /* code 0077 */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  XX_XX_XX,________,
  XX_XX_XX,________,
  XX_XX_XX,________,
  XXXXXXXX,________,
  _XX__XX_,________,
  _XX__XX_,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0078[ 13] = { /* code 0078 */
  ________,
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_0079[ 13] = { /* code 0079 */
  ________,
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  _XXXX___,
  __XX____,
  __XX____,
  _XX_____,
  _XX_____};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_007A[ 13] = { /* code 007A */
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXX___,
  ___XX___,
  __XX____,
  _XX_____,
  XX______,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_007B[ 13] = { /* code 007B */
  ________,
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
  ___XXX__};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_007C[ 13] = { /* code 007C */
  ________,
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
  __XX____};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_007D[ 13] = { /* code 007D */
  ________,
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
  XXX_____};

GUI_CONST_STORAGE unsigned char acFont13B_ASCII_007E[ 26] = { /* code 007E */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  _XXX___X,________,
  X__XX__X,________,
  X___XXX_,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE GUI_CHARINFO GUI_Font13B_ASCII_CharInfo[95] = {
   {   3,   3,  1, acFont13B_ASCII_0020 } /* code 0020 */
  ,{   3,   3,  1, acFont13B_ASCII_0021 } /* code 0021 */
  ,{   6,   6,  1, acFont13B_ASCII_0022 } /* code 0022 */
  ,{   9,   9,  2, acFont13B_ASCII_0023 } /* code 0023 */
  ,{   7,   7,  1, acFont13B_ASCII_0024 } /* code 0024 */
  ,{  13,  13,  2, acFont13B_ASCII_0025 } /* code 0025 */
  ,{   9,   9,  2, acFont13B_ASCII_0026 } /* code 0026 */
  ,{   3,   3,  1, acFont13B_ASCII_0027 } /* code 0027 */
  ,{   5,   5,  1, acFont13B_ASCII_0028 } /* code 0028 */
  ,{   5,   5,  1, acFont13B_ASCII_0029 } /* code 0029 */
  ,{   7,   7,  1, acFont13B_ASCII_002A } /* code 002A */
  ,{   9,   9,  2, acFont13B_ASCII_002B } /* code 002B */
  ,{   3,   3,  1, acFont13B_ASCII_002C } /* code 002C */
  ,{   5,   5,  1, acFont13B_ASCII_002D } /* code 002D */
  ,{   3,   3,  1, acFont13B_ASCII_002E } /* code 002E */
  ,{   6,   6,  1, acFont13B_ASCII_002F } /* code 002F */
  ,{   7,   7,  1, acFont13B_ASCII_0030 } /* code 0030 */
  ,{   7,   7,  1, acFont13B_ASCII_0031 } /* code 0031 */
  ,{   7,   7,  1, acFont13B_ASCII_0032 } /* code 0032 */
  ,{   7,   7,  1, acFont13B_ASCII_0033 } /* code 0033 */
  ,{   7,   7,  1, acFont13B_ASCII_0034 } /* code 0034 */
  ,{   7,   7,  1, acFont13B_ASCII_0035 } /* code 0035 */
  ,{   7,   7,  1, acFont13B_ASCII_0036 } /* code 0036 */
  ,{   7,   7,  1, acFont13B_ASCII_0037 } /* code 0037 */
  ,{   7,   7,  1, acFont13B_ASCII_0038 } /* code 0038 */
  ,{   7,   7,  1, acFont13B_ASCII_0039 } /* code 0039 */
  ,{   3,   3,  1, acFont13B_ASCII_003A } /* code 003A */
  ,{   3,   3,  1, acFont13B_ASCII_003B } /* code 003B */
  ,{   9,   9,  2, acFont13B_ASCII_003C } /* code 003C */
  ,{   9,   9,  2, acFont13B_ASCII_003D } /* code 003D */
  ,{   9,   9,  2, acFont13B_ASCII_003E } /* code 003E */
  ,{   6,   6,  1, acFont13B_ASCII_003F } /* code 003F */
  ,{  10,  10,  2, acFont13B_ASCII_0040 } /* code 0040 */
  ,{   8,   8,  1, acFont13B_ASCII_0041 } /* code 0041 */
  ,{   7,   7,  1, acFont13B_ASCII_0042 } /* code 0042 */
  ,{   7,   7,  1, acFont13B_ASCII_0043 } /* code 0043 */
  ,{   8,   8,  1, acFont13B_ASCII_0044 } /* code 0044 */
  ,{   6,   6,  1, acFont13B_ASCII_0045 } /* code 0045 */
  ,{   6,   6,  1, acFont13B_ASCII_0046 } /* code 0046 */
  ,{   8,   8,  1, acFont13B_ASCII_0047 } /* code 0047 */
  ,{   8,   8,  1, acFont13B_ASCII_0048 } /* code 0048 */
  ,{   5,   5,  1, acFont13B_ASCII_0049 } /* code 0049 */
  ,{   6,   6,  1, acFont13B_ASCII_004A } /* code 004A */
  ,{   7,   7,  1, acFont13B_ASCII_004B } /* code 004B */
  ,{   6,   6,  1, acFont13B_ASCII_004C } /* code 004C */
  ,{  10,  10,  2, acFont13B_ASCII_004D } /* code 004D */
  ,{   7,   7,  1, acFont13B_ASCII_004E } /* code 004E */
  ,{   8,   8,  1, acFont13B_ASCII_004F } /* code 004F */
  ,{   7,   7,  1, acFont13B_ASCII_0050 } /* code 0050 */
  ,{   8,   8,  1, acFont13B_ASCII_0051 } /* code 0051 */
  ,{   8,   8,  1, acFont13B_ASCII_0052 } /* code 0052 */
  ,{   7,   7,  1, acFont13B_ASCII_0053 } /* code 0053 */
  ,{   7,   7,  1, acFont13B_ASCII_0054 } /* code 0054 */
  ,{   8,   8,  1, acFont13B_ASCII_0055 } /* code 0055 */
  ,{   7,   7,  1, acFont13B_ASCII_0056 } /* code 0056 */
  ,{  11,  11,  2, acFont13B_ASCII_0057 } /* code 0057 */
  ,{   7,   7,  1, acFont13B_ASCII_0058 } /* code 0058 */
  ,{   7,   7,  1, acFont13B_ASCII_0059 } /* code 0059 */
  ,{   7,   7,  1, acFont13B_ASCII_005A } /* code 005A */
  ,{   5,   5,  1, acFont13B_ASCII_005B } /* code 005B */
  ,{   6,   6,  1, acFont13B_ASCII_005C } /* code 005C */
  ,{   5,   5,  1, acFont13B_ASCII_005D } /* code 005D */
  ,{   9,   9,  2, acFont13B_ASCII_005E } /* code 005E */
  ,{   7,   7,  1, acFont13B_ASCII_005F } /* code 005F */
  ,{   6,   6,  1, acFont13B_ASCII_0060 } /* code 0060 */
  ,{   7,   7,  1, acFont13B_ASCII_0061 } /* code 0061 */
  ,{   7,   7,  1, acFont13B_ASCII_0062 } /* code 0062 */
  ,{   6,   6,  1, acFont13B_ASCII_0063 } /* code 0063 */
  ,{   7,   7,  1, acFont13B_ASCII_0064 } /* code 0064 */
  ,{   7,   7,  1, acFont13B_ASCII_0065 } /* code 0065 */
  ,{   4,   4,  1, acFont13B_ASCII_0066 } /* code 0066 */
  ,{   7,   7,  1, acFont13B_ASCII_0067 } /* code 0067 */
  ,{   7,   7,  1, acFont13B_ASCII_0068 } /* code 0068 */
  ,{   3,   3,  1, acFont13B_ASCII_0069 } /* code 0069 */
  ,{   4,   4,  1, acFont13B_ASCII_006A } /* code 006A */
  ,{   7,   7,  1, acFont13B_ASCII_006B } /* code 006B */
  ,{   3,   3,  1, acFont13B_ASCII_006C } /* code 006C */
  ,{  11,  11,  2, acFont13B_ASCII_006D } /* code 006D */
  ,{   7,   7,  1, acFont13B_ASCII_006E } /* code 006E */
  ,{   7,   7,  1, acFont13B_ASCII_006F } /* code 006F */
  ,{   7,   7,  1, acFont13B_ASCII_0070 } /* code 0070 */
  ,{   7,   7,  1, acFont13B_ASCII_0071 } /* code 0071 */
  ,{   5,   5,  1, acFont13B_ASCII_0072 } /* code 0072 */
  ,{   6,   6,  1, acFont13B_ASCII_0073 } /* code 0073 */
  ,{   5,   5,  1, acFont13B_ASCII_0074 } /* code 0074 */
  ,{   7,   7,  1, acFont13B_ASCII_0075 } /* code 0075 */
  ,{   7,   7,  1, acFont13B_ASCII_0076 } /* code 0076 */
  ,{   9,   9,  2, acFont13B_ASCII_0077 } /* code 0077 */
  ,{   7,   7,  1, acFont13B_ASCII_0078 } /* code 0078 */
  ,{   7,   7,  1, acFont13B_ASCII_0079 } /* code 0079 */
  ,{   6,   6,  1, acFont13B_ASCII_007A } /* code 007A */
  ,{   7,   7,  1, acFont13B_ASCII_007B } /* code 007B */
  ,{   7,   7,  1, acFont13B_ASCII_007C } /* code 007C */
  ,{   7,   7,  1, acFont13B_ASCII_007D } /* code 007D */
  ,{   9,   9,  2, acFont13B_ASCII_007E } /* code 007E */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font13B_ASCII_Prop1 = {
   0x0020                           /* first character */
  ,0x007E                           /* last character  */
  ,&GUI_Font13B_ASCII_CharInfo[  0] /* address of first character */
  ,(const GUI_FONT_PROP*)0          /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font13B_ASCII = {
   GUI_FONTTYPE_PROP        /* type of font    */
  ,13                       /* height of font  */
  ,13                       /* space of font y */
  ,1                        /* magnification x */
  ,1                        /* magnification y */
  ,{&GUI_Font13B_ASCII_Prop1}
  ,11 ,6 ,8
};

