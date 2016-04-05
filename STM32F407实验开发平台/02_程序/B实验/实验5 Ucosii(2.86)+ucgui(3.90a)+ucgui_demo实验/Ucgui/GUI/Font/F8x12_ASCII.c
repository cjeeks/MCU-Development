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
File        : F8x12_ASCII.C
Purpose     : Monospaced Font similar to Terminal
Height      : 12
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0020[12] = { /* code 0020 */
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

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0021[12] = { /* code 0021 */
  ________,
  __XX____,
  _XXXX___,
  _XXXX___,
  _XXXX___,
  __XX____,
  __XX____,
  ________,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0022[12] = { /* code 0022 */
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __X__X__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0023[12] = { /* code 0023 */
  ________,
  _XX_XX__,
  _XX_XX__,
  XXXXXXX_,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
  XXXXXXX_,
  _XX_XX__,
  _XX_XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0024[12] = { /* code 0024 */
  __XX____,
  __XX____,
  _XXXXX__,
  XX______,
  XX______,
  _XXXX___,
  ____XX__,
  ____XX__,
  XXXXX___,
  __XX____,
  __XX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0025[12] = { /* code 0025 */
  ________,
  ________,
  ________,
  XX___X__,
  XX__XX__,
  ___XX___,
  __XX____,
  _XX_____,
  XX__XX__,
  X___XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0026[12] = { /* code 0026 */
  ________,
  _XXX____,
  XX_XX___,
  XX_XX___,
  _XXX____,
  XXXXX_X_,
  XX_XXXX_,
  XX__XX__,
  XX_XXX__,
  _XXX_XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0027[12] = { /* code 0027 */
  ________,
  __XX____,
  __XX____,
  __XX____,
  _XX_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0028[12] = { /* code 0028 */
  ________,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  _XX_____,
  _XX_____,
  __XX____,
  ___XX___,
  ____XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0029[12] = { /* code 0029 */
  ________,
  _XX_____,
  __XX____,
  ___XX___,
  ____XX__,
  ____XX__,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_002A[12] = { /* code 002A */
  ________,
  ________,
  ________,
  _XX__XX_,
  __XXXX__,
  XXXXXXXX,
  __XXXX__,
  _XX__XX_,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_002B[12] = { /* code 002B */
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

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_002C[12] = { /* code 002C */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXX___,
  __XXX___,
  _XX_____,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_002D[12] = { /* code 002D */
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXXXX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_002E[12] = { /* code 002E */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  __XXX___,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_002F[12] = { /* code 002F */
  ________,
  ________,
  ______X_,
  _____XX_,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  XX______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0030[12] = { /* code 0030 */
  ________,
  _XXXXX__,
  XX___XX_,
  XX__XXX_,
  XX_XXXX_,
  XX_X_XX_,
  XXXX_XX_,
  XXX__XX_,
  XX___XX_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0031[12] = { /* code 0031 */
  ________,
  ___X____,
  __XX____,
  XXXX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0032[12] = { /* code 0032 */
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  XX__XX__,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0033[12] = { /* code 0033 */
  ________,
  _XXXX___,
  XX__XX__,
  ____XX__,
  ____XX__,
  __XXX___,
  ____XX__,
  ____XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0034[12] = { /* code 0034 */
  ________,
  ____XX__,
  ___XXX__,
  __XXXX__,
  _XX_XX__,
  XX__XX__,
  XXXXXXX_,
  ____XX__,
  ____XX__,
  ___XXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0035[12] = { /* code 0035 */
  ________,
  XXXXXX__,
  XX______,
  XX______,
  XX______,
  XXXXX___,
  ____XX__,
  ____XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0036[12] = { /* code 0036 */
  ________,
  __XXX___,
  _XX_____,
  XX______,
  XX______,
  XXXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0037[12] = { /* code 0037 */
  ________,
  XXXXXXX_,
  XX___XX_,
  XX___XX_,
  _____XX_,
  ____XX__,
  ___XX___,
  __XX____,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0038[12] = { /* code 0038 */
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XXX_XX__,
  _XXXX___,
  XX_XXX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0039[12] = { /* code 0039 */
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ___XX___,
  ___XX___,
  __XX____,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_003A[12] = { /* code 003A */
  ________,
  ________,
  ________,
  __XXX___,
  __XXX___,
  ________,
  ________,
  __XXX___,
  __XXX___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_003B[12] = { /* code 003B */
  ________,
  ________,
  ________,
  __XXX___,
  __XXX___,
  ________,
  ________,
  __XXX___,
  __XXX___,
  ___XX___,
  __XX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_003C[12] = { /* code 003C */
  ________,
  ____XX__,
  ___XX___,
  __XX____,
  _XX_____,
  XX______,
  _XX_____,
  __XX____,
  ___XX___,
  ____XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_003D[12] = { /* code 003D */
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
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_003E[12] = { /* code 003E */
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
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_003F[12] = { /* code 003F */
  ________,
  _XXXX___,
  XX__XX__,
  ____XX__,
  ___XX___,
  __XX____,
  __XX____,
  ________,
  __XX____,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0040[12] = { /* code 0040 */
  ________,
  _XXXXX__,
  XX___XX_,
  XX___XX_,
  XX_XXXX_,
  XX_XXXX_,
  XX_XXXX_,
  XX______,
  XX______,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0041[12] = { /* code 0041 */
  ________,
  __XX____,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XXXXXX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0042[12] = { /* code 0042 */
  ________,
  XXXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0043[12] = { /* code 0043 */
  ________,
  __XXXX__,
  _XX__XX_,
  XX___XX_,
  XX______,
  XX______,
  XX______,
  XX___XX_,
  _XX__XX_,
  __XXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0044[12] = { /* code 0044 */
  ________,
  XXXXX___,
  _XX_XX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX_XX__,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0045[12] = { /* code 0045 */
  ________,
  XXXXXXX_,
  _XX___X_,
  _XX_____,
  _XX__X__,
  _XXXXX__,
  _XX__X__,
  _XX_____,
  _XX___X_,
  XXXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0046[12] = { /* code 0046 */
  ________,
  XXXXXXX_,
  _XX__XX_,
  _XX___X_,
  _XX__X__,
  _XXXXX__,
  _XX__X__,
  _XX_____,
  _XX_____,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0047[12] = { /* code 0047 */
  ________,
  __XXXX__,
  _XX__XX_,
  XX___XX_,
  XX______,
  XX______,
  XX__XXX_,
  XX___XX_,
  _XX__XX_,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0048[12] = { /* code 0048 */
  ________,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XXXXXX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0049[12] = { /* code 0049 */
  ________,
  _XXXX___,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_004A[12] = { /* code 004A */
  ________,
  ___XXXX_,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_004B[12] = { /* code 004B */
  ________,
  XXX__XX_,
  _XX__XX_,
  _XX_XX__,
  _XX_XX__,
  _XXXX___,
  _XX_XX__,
  _XX_XX__,
  _XX__XX_,
  XXX__XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_004C[12] = { /* code 004C */
  ________,
  XXXX____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX___X_,
  _XX__XX_,
  _XX__XX_,
  XXXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_004D[12] = { /* code 004D */
  ________,
  XX___XX_,
  XXX_XXX_,
  XXXXXXX_,
  XXXXXXX_,
  XX_X_XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_004E[12] = { /* code 004E */
  ________,
  XX___XX_,
  XX___XX_,
  XXX__XX_,
  XXXX_XX_,
  XXXXXXX_,
  XX_XXXX_,
  XX__XXX_,
  XX___XX_,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_004F[12] = { /* code 004F */
  ________,
  __XXX___,
  _XX_XX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  _XX_XX__,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0050[12] = { /* code 0050 */
  ________,
  XXXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  _XX_____,
  _XX_____,
  _XX_____,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0051[12] = { /* code 0051 */
  ________,
  __XXX___,
  _XX_XX__,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX__XXX_,
  XX_XXXX_,
  _XXXXX__,
  ____XX__,
  ___XXXX_,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0052[12] = { /* code 0052 */
  ________,
  XXXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  _XX_XX__,
  _XX__XX_,
  _XX__XX_,
  XXX__XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0053[12] = { /* code 0053 */
  ________,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX______,
  _XXX____,
  ___XX___,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0054[12] = { /* code 0054 */
  ________,
  XXXXXX__,
  X_XX_X__,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0055[12] = { /* code 0055 */
  ________,
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
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0056[12] = { /* code 0056 */
  ________,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0057[12] = { /* code 0057 */
  ________,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX___XX_,
  XX_X_XX_,
  XX_X_XX_,
  _XX_XX__,
  _XX_XX__,
  _XX_XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0058[12] = { /* code 0058 */
  ________,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  __XX____,
  _XXXX___,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0059[12] = { /* code 0059 */
  ________,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  __XX____,
  __XX____,
  __XX____,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_005A[12] = { /* code 005A */
  ________,
  XXXXXXX_,
  XX__XXX_,
  X__XX___,
  ___XX___,
  __XX____,
  _XX_____,
  _XX___X_,
  XX___XX_,
  XXXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_005B[12] = { /* code 005B */
  ________,
  __XXXX__,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XX____,
  __XXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_005C[12] = { /* code 005C */
  ________,
  ________,
  X_______,
  XX______,
  _XX_____,
  __XX____,
  ___XX___,
  ____XX__,
  _____XX_,
  ______X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_005D[12] = { /* code 005D */
  ________,
  __XXXX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  __XXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_005E[12] = { /* code 005E */
  ___X____,
  __XXX___,
  _XX_XX__,
  XX___XX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_005F[12] = { /* code 005F */
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
  XXXXXXXX,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0060[12] = { /* code 0060 */
  __XX____,
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
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0061[12] = { /* code 0061 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  ____XX__,
  _XXXXX__,
  XX__XX__,
  XX__XX__,
  _XXX_XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0062[12] = { /* code 0062 */
  ________,
  XXX_____,
  _XX_____,
  _XX_____,
  _XXXXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  XX_XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0063[12] = { /* code 0063 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XX______,
  XX______,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0064[12] = { /* code 0064 */
  ________,
  ___XXX__,
  ____XX__,
  ____XX__,
  _XXXXX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXX_XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0065[12] = { /* code 0065 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  XXXXXX__,
  XX______,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0066[12] = { /* code 0066 */
  ________,
  __XXX___,
  _XX_XX__,
  _XX_____,
  _XX_____,
  XXXXX___,
  _XX_____,
  _XX_____,
  _XX_____,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0067[12] = { /* code 0067 */
  ________,
  ________,
  ________,
  ________,
  _XXX_XX_,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ____XX__,
  XX__XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0068[12] = { /* code 0068 */
  ________,
  XXX_____,
  _XX_____,
  _XX_____,
  _XX_XX__,
  _XXX_XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  XXX__XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0069[12] = { /* code 0069 */
  ________,
  ___XX___,
  ___XX___,
  ________,
  _XXXX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  _XXXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_006A[12] = { /* code 006A */
  ________,
  ____XX__,
  ____XX__,
  ________,
  __XXXX__,
  ____XX__,
  ____XX__,
  ____XX__,
  ____XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_006B[12] = { /* code 006B */
  ________,
  XXX_____,
  _XX_____,
  _XX_____,
  _XX__XX_,
  _XX_XX__,
  _XXXX___,
  _XX_XX__,
  _XX__XX_,
  XXX__XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_006C[12] = { /* code 006C */
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
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_006D[12] = { /* code 006D */
  ________,
  ________,
  ________,
  ________,
  XXXXXX__,
  XX_X_XX_,
  XX_X_XX_,
  XX_X_XX_,
  XX_X_XX_,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_006E[12] = { /* code 006E */
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

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_006F[12] = { /* code 006F */
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

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0070[12] = { /* code 0070 */
  ________,
  ________,
  ________,
  ________,
  XX_XXX__,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XXXXX__,
  _XX_____,
  XXXX____};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0071[12] = { /* code 0071 */
  ________,
  ________,
  ________,
  ________,
  _XXX_XX_,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXXX__,
  ____XX__,
  ___XXXX_};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0072[12] = { /* code 0072 */
  ________,
  ________,
  ________,
  ________,
  XXX_XX__,
  _XX_XXX_,
  _XXX_XX_,
  _XX_____,
  _XX_____,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0073[12] = { /* code 0073 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  XX__XX__,
  _XX_____,
  ___XX___,
  XX__XX__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0074[12] = { /* code 0074 */
  ________,
  ________,
  __X_____,
  _XX_____,
  XXXXXX__,
  _XX_____,
  _XX_____,
  _XX_____,
  _XX_XX__,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0075[12] = { /* code 0075 */
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXX_XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0076[12] = { /* code 0076 */
  ________,
  ________,
  ________,
  ________,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  XX__XX__,
  _XXXX___,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0077[12] = { /* code 0077 */
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  XX_X_XX_,
  XX_X_XX_,
  _XX_XX__,
  _XX_XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0078[12] = { /* code 0078 */
  ________,
  ________,
  ________,
  ________,
  XX___XX_,
  _XX_XX__,
  __XXX___,
  __XXX___,
  _XX_XX__,
  XX___XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_0079[12] = { /* code 0079 */
  ________,
  ________,
  ________,
  ________,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  _XX__XX_,
  __XXXX__,
  ____XX__,
  ___XX___,
  XXXX____};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_007A[12] = { /* code 007A */
  ________,
  ________,
  ________,
  ________,
  XXXXXX__,
  X___XX__,
  ___XX___,
  _XX_____,
  XX___X__,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_007B[12] = { /* code 007B */
  ________,
  ___XXX__,
  __XX____,
  __XX____,
  _XX_____,
  XX______,
  _XX_____,
  __XX____,
  __XX____,
  ___XXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_007C[12] = { /* code 007C */
  ________,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ___XX___,
  ___XX___,
  ___XX___,
  ___XX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_007D[12] = { /* code 007D */
  ________,
  XXX_____,
  __XX____,
  __XX____,
  ___XX___,
  ____XX__,
  ___XX___,
  __XX____,
  __XX____,
  XXX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_007E[12] = { /* code 007E */
  ________,
  _XXX__XX,
  XX_XX_X_,
  XX__XXX_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont8x12ASCII_007F[12] = { /* code 007F */
  ________,
  ________,
  ________,
  ___X____,
  __XXX___,
  _XX_XX__,
  XX___XX_,
  XX___XX_,
  XXXXXXX_,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE GUI_CHARINFO GUI_Font8x12ASCII_CharInfo[96] = {
   {   8,   8,  1, acFont8x12ASCII_0020 } /* code 0020 */
  ,{   8,   8,  1, acFont8x12ASCII_0021 } /* code 0021 */
  ,{   8,   8,  1, acFont8x12ASCII_0022 } /* code 0022 */
  ,{   8,   8,  1, acFont8x12ASCII_0023 } /* code 0023 */
  ,{   8,   8,  1, acFont8x12ASCII_0024 } /* code 0024 */
  ,{   8,   8,  1, acFont8x12ASCII_0025 } /* code 0025 */
  ,{   8,   8,  1, acFont8x12ASCII_0026 } /* code 0026 */
  ,{   8,   8,  1, acFont8x12ASCII_0027 } /* code 0027 */
  ,{   8,   8,  1, acFont8x12ASCII_0028 } /* code 0028 */
  ,{   8,   8,  1, acFont8x12ASCII_0029 } /* code 0029 */
  ,{   8,   8,  1, acFont8x12ASCII_002A } /* code 002A */
  ,{   8,   8,  1, acFont8x12ASCII_002B } /* code 002B */
  ,{   8,   8,  1, acFont8x12ASCII_002C } /* code 002C */
  ,{   8,   8,  1, acFont8x12ASCII_002D } /* code 002D */
  ,{   8,   8,  1, acFont8x12ASCII_002E } /* code 002E */
  ,{   8,   8,  1, acFont8x12ASCII_002F } /* code 002F */
  ,{   8,   8,  1, acFont8x12ASCII_0030 } /* code 0030 */
  ,{   8,   8,  1, acFont8x12ASCII_0031 } /* code 0031 */
  ,{   8,   8,  1, acFont8x12ASCII_0032 } /* code 0032 */
  ,{   8,   8,  1, acFont8x12ASCII_0033 } /* code 0033 */
  ,{   8,   8,  1, acFont8x12ASCII_0034 } /* code 0034 */
  ,{   8,   8,  1, acFont8x12ASCII_0035 } /* code 0035 */
  ,{   8,   8,  1, acFont8x12ASCII_0036 } /* code 0036 */
  ,{   8,   8,  1, acFont8x12ASCII_0037 } /* code 0037 */
  ,{   8,   8,  1, acFont8x12ASCII_0038 } /* code 0038 */
  ,{   8,   8,  1, acFont8x12ASCII_0039 } /* code 0039 */
  ,{   8,   8,  1, acFont8x12ASCII_003A } /* code 003A */
  ,{   8,   8,  1, acFont8x12ASCII_003B } /* code 003B */
  ,{   8,   8,  1, acFont8x12ASCII_003C } /* code 003C */
  ,{   8,   8,  1, acFont8x12ASCII_003D } /* code 003D */
  ,{   8,   8,  1, acFont8x12ASCII_003E } /* code 003E */
  ,{   8,   8,  1, acFont8x12ASCII_003F } /* code 003F */
  ,{   8,   8,  1, acFont8x12ASCII_0040 } /* code 0040 */
  ,{   8,   8,  1, acFont8x12ASCII_0041 } /* code 0041 */
  ,{   8,   8,  1, acFont8x12ASCII_0042 } /* code 0042 */
  ,{   8,   8,  1, acFont8x12ASCII_0043 } /* code 0043 */
  ,{   8,   8,  1, acFont8x12ASCII_0044 } /* code 0044 */
  ,{   8,   8,  1, acFont8x12ASCII_0045 } /* code 0045 */
  ,{   8,   8,  1, acFont8x12ASCII_0046 } /* code 0046 */
  ,{   8,   8,  1, acFont8x12ASCII_0047 } /* code 0047 */
  ,{   8,   8,  1, acFont8x12ASCII_0048 } /* code 0048 */
  ,{   8,   8,  1, acFont8x12ASCII_0049 } /* code 0049 */
  ,{   8,   8,  1, acFont8x12ASCII_004A } /* code 004A */
  ,{   8,   8,  1, acFont8x12ASCII_004B } /* code 004B */
  ,{   8,   8,  1, acFont8x12ASCII_004C } /* code 004C */
  ,{   8,   8,  1, acFont8x12ASCII_004D } /* code 004D */
  ,{   8,   8,  1, acFont8x12ASCII_004E } /* code 004E */
  ,{   8,   8,  1, acFont8x12ASCII_004F } /* code 004F */
  ,{   8,   8,  1, acFont8x12ASCII_0050 } /* code 0050 */
  ,{   8,   8,  1, acFont8x12ASCII_0051 } /* code 0051 */
  ,{   8,   8,  1, acFont8x12ASCII_0052 } /* code 0052 */
  ,{   8,   8,  1, acFont8x12ASCII_0053 } /* code 0053 */
  ,{   8,   8,  1, acFont8x12ASCII_0054 } /* code 0054 */
  ,{   8,   8,  1, acFont8x12ASCII_0055 } /* code 0055 */
  ,{   8,   8,  1, acFont8x12ASCII_0056 } /* code 0056 */
  ,{   8,   8,  1, acFont8x12ASCII_0057 } /* code 0057 */
  ,{   8,   8,  1, acFont8x12ASCII_0058 } /* code 0058 */
  ,{   8,   8,  1, acFont8x12ASCII_0059 } /* code 0059 */
  ,{   8,   8,  1, acFont8x12ASCII_005A } /* code 005A */
  ,{   8,   8,  1, acFont8x12ASCII_005B } /* code 005B */
  ,{   8,   8,  1, acFont8x12ASCII_005C } /* code 005C */
  ,{   8,   8,  1, acFont8x12ASCII_005D } /* code 005D */
  ,{   8,   8,  1, acFont8x12ASCII_005E } /* code 005E */
  ,{   8,   8,  1, acFont8x12ASCII_005F } /* code 005F */
  ,{   8,   8,  1, acFont8x12ASCII_0060 } /* code 0060 */
  ,{   8,   8,  1, acFont8x12ASCII_0061 } /* code 0061 */
  ,{   8,   8,  1, acFont8x12ASCII_0062 } /* code 0062 */
  ,{   8,   8,  1, acFont8x12ASCII_0063 } /* code 0063 */
  ,{   8,   8,  1, acFont8x12ASCII_0064 } /* code 0064 */
  ,{   8,   8,  1, acFont8x12ASCII_0065 } /* code 0065 */
  ,{   8,   8,  1, acFont8x12ASCII_0066 } /* code 0066 */
  ,{   8,   8,  1, acFont8x12ASCII_0067 } /* code 0067 */
  ,{   8,   8,  1, acFont8x12ASCII_0068 } /* code 0068 */
  ,{   8,   8,  1, acFont8x12ASCII_0069 } /* code 0069 */
  ,{   8,   8,  1, acFont8x12ASCII_006A } /* code 006A */
  ,{   8,   8,  1, acFont8x12ASCII_006B } /* code 006B */
  ,{   8,   8,  1, acFont8x12ASCII_006C } /* code 006C */
  ,{   8,   8,  1, acFont8x12ASCII_006D } /* code 006D */
  ,{   8,   8,  1, acFont8x12ASCII_006E } /* code 006E */
  ,{   8,   8,  1, acFont8x12ASCII_006F } /* code 006F */
  ,{   8,   8,  1, acFont8x12ASCII_0070 } /* code 0070 */
  ,{   8,   8,  1, acFont8x12ASCII_0071 } /* code 0071 */
  ,{   8,   8,  1, acFont8x12ASCII_0072 } /* code 0072 */
  ,{   8,   8,  1, acFont8x12ASCII_0073 } /* code 0073 */
  ,{   8,   8,  1, acFont8x12ASCII_0074 } /* code 0074 */
  ,{   8,   8,  1, acFont8x12ASCII_0075 } /* code 0075 */
  ,{   8,   8,  1, acFont8x12ASCII_0076 } /* code 0076 */
  ,{   8,   8,  1, acFont8x12ASCII_0077 } /* code 0077 */
  ,{   8,   8,  1, acFont8x12ASCII_0078 } /* code 0078 */
  ,{   8,   8,  1, acFont8x12ASCII_0079 } /* code 0079 */
  ,{   8,   8,  1, acFont8x12ASCII_007A } /* code 007A */
  ,{   8,   8,  1, acFont8x12ASCII_007B } /* code 007B */
  ,{   8,   8,  1, acFont8x12ASCII_007C } /* code 007C */
  ,{   8,   8,  1, acFont8x12ASCII_007D } /* code 007D */
  ,{   8,   8,  1, acFont8x12ASCII_007E } /* code 007E */
  ,{   8,   8,  1, acFont8x12ASCII_007F } /* code 007F */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font8x12ASCII_Prop1 = {
   32                             /* first character               */
  ,127                            /* last character                */
  ,&GUI_Font8x12ASCII_CharInfo[0] /* address of first character    */
  ,(const GUI_FONT_PROP*)0        /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font8x12_ASCII = {
   GUI_FONTTYPE_PROP /* type of font    */
  ,12                /* height of font  */
  ,12                /* space of font y */
  ,1                 /* magnification x */
  ,1                 /* magnification y */
  ,{&GUI_Font8x12ASCII_Prop1}
  ,10, 6, 9
};

