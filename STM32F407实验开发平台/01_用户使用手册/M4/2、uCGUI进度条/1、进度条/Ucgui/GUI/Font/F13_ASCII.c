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
File        : F13_ASCII.c
Purpose     : ASCII character set
Height      : 13
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"

/* Start of unicode area <Basic Latin> */

GUI_CONST_STORAGE unsigned char acFont13ASCII_0020[13] = { /* code 0020 */
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

GUI_CONST_STORAGE unsigned char acFont13ASCII_0021[13] = { /* code 0021 */
  ________,
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  ________,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0022[13] = { /* code 0022 */
  ________,
  ________,
  X_X_____,
  X_X_____,
  X_X_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0023[13] = { /* code 0023 */
  ________,
  ________,
  ________,
  ___X_X__,
  ___X_X__,
  _XXXXXX_,
  __X_X___,
  __X_X___,
  XXXXXX__,
  _X_X____,
  _X_X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0024[13] = { /* code 0024 */
  ________,
  ________,
  __X_____,
  __X_____,
  _XXXX___,
  X_X_____,
  X_X_____,
  _XXX____,
  __X_X___,
  __X_X___,
  XXXX____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0025[26] = { /* code 0025 */
  ________,________,
  ________,________,
  ________,________,
  _XX___X_,________,
  X__X__X_,________,
  X__X_X__,________,
  _XX__X__,________,
  ____X__X,X_______,
  ____X_X_,_X______,
  ___X__X_,_X______,
  ___X___X,X_______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0026[13] = { /* code 0026 */
  ________,
  ________,
  ________,
  _XX_____,
  X__X____,
  X__X____,
  _XX__X__,
  X__X_X__,
  X___X___,
  X___XX__,
  _XXX__X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0027[13] = { /* code 0027 */
  ________,
  ________,
  X_______,
  X_______,
  X_______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0028[13] = { /* code 0028 */
  ________,
  ________,
  __X_____,
  _X______,
  _X______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  _X______,
  _X______,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0029[13] = { /* code 0029 */
  ________,
  ________,
  X_______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13ASCII_002A[13] = { /* code 002A */
  ________,
  ________,
  __X_____,
  X_X_X___,
  _XXX____,
  X_X_X___,
  __X_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_002B[13] = { /* code 002B */
  ________,
  ________,
  ________,
  ________,
  ___X____,
  ___X____,
  ___X____,
  XXXXXXX_,
  ___X____,
  ___X____,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_002C[13] = { /* code 002C */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13ASCII_002D[13] = { /* code 002D */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXX_____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_002E[13] = { /* code 002E */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_002F[13] = { /* code 002F */
  ________,
  ________,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0030[13] = { /* code 0030 */
  ________,
  ________,
  ________,
  _XXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0031[13] = { /* code 0031 */
  ________,
  ________,
  ________,
  __X_____,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0032[13] = { /* code 0032 */
  ________,
  ________,
  ________,
  _XXX____,
  X___X___,
  ____X___,
  ___X____,
  __X_____,
  _X______,
  X_______,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0033[13] = { /* code 0033 */
  ________,
  ________,
  ________,
  _XXX____,
  X___X___,
  ____X___,
  __XX____,
  ____X___,
  ____X___,
  X___X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0034[13] = { /* code 0034 */
  ________,
  ________,
  ________,
  ___X____,
  __XX____,
  _X_X____,
  X__X____,
  XXXXX___,
  ___X____,
  ___X____,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0035[13] = { /* code 0035 */
  ________,
  ________,
  ________,
  XXXXX___,
  X_______,
  X_______,
  XXXX____,
  ____X___,
  ____X___,
  X___X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0036[13] = { /* code 0036 */
  ________,
  ________,
  ________,
  __XX____,
  _X______,
  X_______,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0037[13] = { /* code 0037 */
  ________,
  ________,
  ________,
  XXXXX___,
  ____X___,
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0038[13] = { /* code 0038 */
  ________,
  ________,
  ________,
  _XXX____,
  X___X___,
  X___X___,
  _XXX____,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0039[13] = { /* code 0039 */
  ________,
  ________,
  ________,
  _XXX____,
  X___X___,
  X___X___,
  X___X___,
  _XXXX___,
  ____X___,
  ___X____,
  _XX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_003A[13] = { /* code 003A */
  ________,
  ________,
  ________,
  ________,
  ________,
  _X______,
  _X______,
  ________,
  ________,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_003B[13] = { /* code 003B */
  ________,
  ________,
  ________,
  ________,
  ________,
  _X______,
  _X______,
  ________,
  ________,
  _X______,
  _X______,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13ASCII_003C[13] = { /* code 003C */
  ________,
  ________,
  ________,
  ________,
  ______X_,
  ____XX__,
  __XX____,
  _X______,
  __XX____,
  ____XX__,
  ______X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_003D[13] = { /* code 003D */
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
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_003E[13] = { /* code 003E */
  ________,
  ________,
  ________,
  ________,
  _X______,
  __XX____,
  ____XX__,
  ______X_,
  ____XX__,
  __XX____,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_003F[13] = { /* code 003F */
  ________,
  ________,
  ________,
  XXX_____,
  ___X____,
  ___X____,
  __X_____,
  _X______,
  _X______,
  ________,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0040[26] = { /* code 0040 */
  ________,________,
  ________,________,
  ________,________,
  __XXXXX_,________,
  _X_____X,________,
  X__XXX__,X_______,
  X_X__X__,X_______,
  X_X__X__,X_______,
  X_X__X__,X_______,
  X__XXXXX,________,
  _X______,________,
  __XXXX__,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0041[13] = { /* code 0041 */
  ________,
  ________,
  ________,
  __XX____,
  __XX____,
  _X__X___,
  _X__X___,
  _X__X___,
  XXXXXX__,
  X____X__,
  X____X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0042[13] = { /* code 0042 */
  ________,
  ________,
  ________,
  XXXX____,
  X___X___,
  X___X___,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0043[13] = { /* code 0043 */
  ________,
  ________,
  ________,
  __XXXX__,
  _X______,
  X_______,
  X_______,
  X_______,
  X_______,
  _X______,
  __XXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0044[13] = { /* code 0044 */
  ________,
  ________,
  ________,
  XXXX____,
  X___X___,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X___X___,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0045[13] = { /* code 0045 */
  ________,
  ________,
  ________,
  XXXXX___,
  X_______,
  X_______,
  XXXX____,
  X_______,
  X_______,
  X_______,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0046[13] = { /* code 0046 */
  ________,
  ________,
  ________,
  XXXXX___,
  X_______,
  X_______,
  XXXXX___,
  X_______,
  X_______,
  X_______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0047[13] = { /* code 0047 */
  ________,
  ________,
  ________,
  __XXXX__,
  _X______,
  X_______,
  X_______,
  X__XXX__,
  X____X__,
  _X___X__,
  __XXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0048[13] = { /* code 0048 */
  ________,
  ________,
  ________,
  X____X__,
  X____X__,
  X____X__,
  XXXXXX__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0049[13] = { /* code 0049 */
  ________,
  ________,
  ________,
  XXX_____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  XXX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_004A[13] = { /* code 004A */
  ________,
  ________,
  ________,
  _XXX____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  XXX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_004B[13] = { /* code 004B */
  ________,
  ________,
  ________,
  X___X___,
  X__X____,
  X_X_____,
  XX______,
  XX______,
  X_X_____,
  X__X____,
  X___X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_004C[13] = { /* code 004C */
  ________,
  ________,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_004D[13] = { /* code 004D */
  ________,
  ________,
  ________,
  XX___XX_,
  XX___XX_,
  X_X_X_X_,
  X_X_X_X_,
  X__X__X_,
  X__X__X_,
  X_____X_,
  X_____X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_004E[13] = { /* code 004E */
  ________,
  ________,
  ________,
  XX___X__,
  XX___X__,
  X_X__X__,
  X_X__X__,
  X__X_X__,
  X__X_X__,
  X___XX__,
  X___XX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_004F[13] = { /* code 004F */
  ________,
  ________,
  ________,
  __XXX___,
  _X___X__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___X__,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0050[13] = { /* code 0050 */
  ________,
  ________,
  ________,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  XXXX____,
  X_______,
  X_______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0051[13] = { /* code 0051 */
  ________,
  ________,
  ________,
  __XXX___,
  _X___X__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___X__,
  __XXX___,
  ____X___,
  _____XX_};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0052[13] = { /* code 0052 */
  ________,
  ________,
  ________,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  XXXX____,
  X__X____,
  X___X___,
  X____X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0053[13] = { /* code 0053 */
  ________,
  ________,
  ________,
  _XXXX___,
  X_______,
  X_______,
  _XXX____,
  ____X___,
  ____X___,
  ____X___,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0054[13] = { /* code 0054 */
  ________,
  ________,
  ________,
  XXXXX___,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0055[13] = { /* code 0055 */
  ________,
  ________,
  ________,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0056[13] = { /* code 0056 */
  ________,
  ________,
  ________,
  X___X___,
  X___X___,
  X___X___,
  _X_X____,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0057[26] = { /* code 0057 */
  ________,________,
  ________,________,
  ________,________,
  X___X___,X_______,
  X___X___,X_______,
  X___X___,X_______,
  _X_X_X_X,________,
  _X_X_X_X,________,
  _X_X_X_X,________,
  __X___X_,________,
  __X___X_,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0058[13] = { /* code 0058 */
  ________,
  ________,
  ________,
  X___X___,
  X___X___,
  _X_X____,
  __X_____,
  __X_____,
  _X_X____,
  X___X___,
  X___X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0059[13] = { /* code 0059 */
  ________,
  ________,
  ________,
  X___X___,
  X___X___,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_005A[13] = { /* code 005A */
  ________,
  ________,
  ________,
  XXXXX___,
  ____X___,
  ___X____,
  __X_____,
  __X_____,
  _X______,
  X_______,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_005B[13] = { /* code 005B */
  ________,
  ________,
  XXX_____,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  XXX_____};

GUI_CONST_STORAGE unsigned char acFont13ASCII_005C[13] = { /* code 005C */
  ________,
  ________,
  X_______,
  X_______,
  X_______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont13ASCII_005D[13] = { /* code 005D */
  ________,
  ________,
  XXX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  XXX_____};

GUI_CONST_STORAGE unsigned char acFont13ASCII_005E[13] = { /* code 005E */
  ________,
  ________,
  ________,
  ___X____,
  __X_X___,
  _X___X__,
  X_____X_,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_005F[13] = { /* code 005F */
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
  XXXXXX__};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0060[13] = { /* code 0060 */
  ________,
  ________,
  _X______,
  __X_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0061[13] = { /* code 0061 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  ____X___,
  _XXXX___,
  X___X___,
  X___X___,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0062[13] = { /* code 0062 */
  ________,
  ________,
  X_______,
  X_______,
  X_______,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0063[13] = { /* code 0063 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  X_______,
  X_______,
  X_______,
  X_______,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0064[13] = { /* code 0064 */
  ________,
  ________,
  ____X___,
  ____X___,
  ____X___,
  _XXXX___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0065[13] = { /* code 0065 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  X___X___,
  XXXXX___,
  X_______,
  X___X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0066[13] = { /* code 0066 */
  ________,
  ________,
  _XX_____,
  X_______,
  X_______,
  XXX_____,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0067[13] = { /* code 0067 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXXX___,
  ____X___,
  _XXX____};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0068[13] = { /* code 0068 */
  ________,
  ________,
  X_______,
  X_______,
  X_______,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0069[13] = { /* code 0069 */
  ________,
  ________,
  ________,
  X_______,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_006A[13] = { /* code 006A */
  ________,
  ________,
  ________,
  _X______,
  ________,
  XX______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13ASCII_006B[13] = { /* code 006B */
  ________,
  ________,
  X_______,
  X_______,
  X_______,
  X__X____,
  X_X_____,
  XX______,
  X_X_____,
  X__X____,
  X___X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_006C[13] = { /* code 006C */
  ________,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_006D[13] = { /* code 006D */
  ________,
  ________,
  ________,
  ________,
  ________,
  XXX_XX__,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  X__X__X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_006E[13] = { /* code 006E */
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_006F[13] = { /* code 006F */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0070[13] = { /* code 0070 */
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  XXXX____,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0071[13] = { /* code 0071 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXXX___,
  ____X___,
  ____X___};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0072[13] = { /* code 0072 */
  ________,
  ________,
  ________,
  ________,
  ________,
  X_X_____,
  XX______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0073[13] = { /* code 0073 */
  ________,
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  X_______,
  XX______,
  __XX____,
  ___X____,
  XXX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0074[13] = { /* code 0074 */
  ________,
  ________,
  ________,
  X_______,
  X_______,
  XXX_____,
  X_______,
  X_______,
  X_______,
  X_______,
  _XX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0075[13] = { /* code 0075 */
  ________,
  ________,
  ________,
  ________,
  ________,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0076[13] = { /* code 0076 */
  ________,
  ________,
  ________,
  ________,
  ________,
  X___X___,
  X___X___,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0077[13] = { /* code 0077 */
  ________,
  ________,
  ________,
  ________,
  ________,
  X__X__X_,
  X__X__X_,
  X_X_X_X_,
  X_X_X_X_,
  _X___X__,
  _X___X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0078[13] = { /* code 0078 */
  ________,
  ________,
  ________,
  ________,
  ________,
  X___X___,
  _X_X____,
  __X_____,
  __X_____,
  _X_X____,
  X___X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_0079[13] = { /* code 0079 */
  ________,
  ________,
  ________,
  ________,
  ________,
  X___X___,
  X___X___,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  _X______,
  _X______};

GUI_CONST_STORAGE unsigned char acFont13ASCII_007A[13] = { /* code 007A */
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXX____,
  ___X____,
  __X_____,
  _X______,
  X_______,
  XXXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13ASCII_007B[13] = { /* code 007B */
  ________,
  ________,
  ___X____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  XX______,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ___X____};

GUI_CONST_STORAGE unsigned char acFont13ASCII_007C[13] = { /* code 007C */
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
  _X______};

GUI_CONST_STORAGE unsigned char acFont13ASCII_007D[13] = { /* code 007D */
  ________,
  ________,
  X_______,
  _X______,
  _X______,
  _X______,
  _X______,
  __XX____,
  _X______,
  _X______,
  _X______,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13ASCII_007E[13] = { /* code 007E */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _XX___X_,
  X__X__X_,
  X___XX__,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE GUI_CHARINFO GUI_Font13ASCII_CharInfo[95] = {
   {   3,   3,  1, acFont13ASCII_0020 } /* code 0020 */
  ,{   4,   4,  1, acFont13ASCII_0021 } /* code 0021 */
  ,{   4,   4,  1, acFont13ASCII_0022 } /* code 0022 */
  ,{   8,   8,  1, acFont13ASCII_0023 } /* code 0023 */
  ,{   6,   6,  1, acFont13ASCII_0024 } /* code 0024 */
  ,{  11,  11,  2, acFont13ASCII_0025 } /* code 0025 */
  ,{   7,   7,  1, acFont13ASCII_0026 } /* code 0026 */
  ,{   2,   2,  1, acFont13ASCII_0027 } /* code 0027 */
  ,{   4,   4,  1, acFont13ASCII_0028 } /* code 0028 */
  ,{   4,   4,  1, acFont13ASCII_0029 } /* code 0029 */
  ,{   6,   6,  1, acFont13ASCII_002A } /* code 002A */
  ,{   8,   8,  1, acFont13ASCII_002B } /* code 002B */
  ,{   4,   4,  1, acFont13ASCII_002C } /* code 002C */
  ,{   4,   4,  1, acFont13ASCII_002D } /* code 002D */
  ,{   4,   4,  1, acFont13ASCII_002E } /* code 002E */
  ,{   4,   4,  1, acFont13ASCII_002F } /* code 002F */
  ,{   6,   6,  1, acFont13ASCII_0030 } /* code 0030 */
  ,{   6,   6,  1, acFont13ASCII_0031 } /* code 0031 */
  ,{   6,   6,  1, acFont13ASCII_0032 } /* code 0032 */
  ,{   6,   6,  1, acFont13ASCII_0033 } /* code 0033 */
  ,{   6,   6,  1, acFont13ASCII_0034 } /* code 0034 */
  ,{   6,   6,  1, acFont13ASCII_0035 } /* code 0035 */
  ,{   6,   6,  1, acFont13ASCII_0036 } /* code 0036 */
  ,{   6,   6,  1, acFont13ASCII_0037 } /* code 0037 */
  ,{   6,   6,  1, acFont13ASCII_0038 } /* code 0038 */
  ,{   6,   6,  1, acFont13ASCII_0039 } /* code 0039 */
  ,{   4,   4,  1, acFont13ASCII_003A } /* code 003A */
  ,{   4,   4,  1, acFont13ASCII_003B } /* code 003B */
  ,{   8,   8,  1, acFont13ASCII_003C } /* code 003C */
  ,{   8,   8,  1, acFont13ASCII_003D } /* code 003D */
  ,{   8,   8,  1, acFont13ASCII_003E } /* code 003E */
  ,{   5,   5,  1, acFont13ASCII_003F } /* code 003F */
  ,{  10,  10,  2, acFont13ASCII_0040 } /* code 0040 */
  ,{   7,   7,  1, acFont13ASCII_0041 } /* code 0041 */
  ,{   6,   6,  1, acFont13ASCII_0042 } /* code 0042 */
  ,{   7,   7,  1, acFont13ASCII_0043 } /* code 0043 */
  ,{   7,   7,  1, acFont13ASCII_0044 } /* code 0044 */
  ,{   6,   6,  1, acFont13ASCII_0045 } /* code 0045 */
  ,{   6,   6,  1, acFont13ASCII_0046 } /* code 0046 */
  ,{   7,   7,  1, acFont13ASCII_0047 } /* code 0047 */
  ,{   7,   7,  1, acFont13ASCII_0048 } /* code 0048 */
  ,{   4,   4,  1, acFont13ASCII_0049 } /* code 0049 */
  ,{   5,   5,  1, acFont13ASCII_004A } /* code 004A */
  ,{   6,   6,  1, acFont13ASCII_004B } /* code 004B */
  ,{   5,   5,  1, acFont13ASCII_004C } /* code 004C */
  ,{   8,   8,  1, acFont13ASCII_004D } /* code 004D */
  ,{   7,   7,  1, acFont13ASCII_004E } /* code 004E */
  ,{   8,   8,  1, acFont13ASCII_004F } /* code 004F */
  ,{   6,   6,  1, acFont13ASCII_0050 } /* code 0050 */
  ,{   8,   8,  1, acFont13ASCII_0051 } /* code 0051 */
  ,{   7,   7,  1, acFont13ASCII_0052 } /* code 0052 */
  ,{   6,   6,  1, acFont13ASCII_0053 } /* code 0053 */
  ,{   6,   6,  1, acFont13ASCII_0054 } /* code 0054 */
  ,{   7,   7,  1, acFont13ASCII_0055 } /* code 0055 */
  ,{   6,   6,  1, acFont13ASCII_0056 } /* code 0056 */
  ,{  10,  10,  2, acFont13ASCII_0057 } /* code 0057 */
  ,{   6,   6,  1, acFont13ASCII_0058 } /* code 0058 */
  ,{   6,   6,  1, acFont13ASCII_0059 } /* code 0059 */
  ,{   6,   6,  1, acFont13ASCII_005A } /* code 005A */
  ,{   4,   4,  1, acFont13ASCII_005B } /* code 005B */
  ,{   4,   4,  1, acFont13ASCII_005C } /* code 005C */
  ,{   4,   4,  1, acFont13ASCII_005D } /* code 005D */
  ,{   8,   8,  1, acFont13ASCII_005E } /* code 005E */
  ,{   6,   6,  1, acFont13ASCII_005F } /* code 005F */
  ,{   6,   6,  1, acFont13ASCII_0060 } /* code 0060 */
  ,{   6,   6,  1, acFont13ASCII_0061 } /* code 0061 */
  ,{   6,   6,  1, acFont13ASCII_0062 } /* code 0062 */
  ,{   5,   5,  1, acFont13ASCII_0063 } /* code 0063 */
  ,{   6,   6,  1, acFont13ASCII_0064 } /* code 0064 */
  ,{   6,   6,  1, acFont13ASCII_0065 } /* code 0065 */
  ,{   4,   4,  1, acFont13ASCII_0066 } /* code 0066 */
  ,{   6,   6,  1, acFont13ASCII_0067 } /* code 0067 */
  ,{   6,   6,  1, acFont13ASCII_0068 } /* code 0068 */
  ,{   2,   2,  1, acFont13ASCII_0069 } /* code 0069 */
  ,{   3,   3,  1, acFont13ASCII_006A } /* code 006A */
  ,{   5,   5,  1, acFont13ASCII_006B } /* code 006B */
  ,{   2,   2,  1, acFont13ASCII_006C } /* code 006C */
  ,{   8,   8,  1, acFont13ASCII_006D } /* code 006D */
  ,{   6,   6,  1, acFont13ASCII_006E } /* code 006E */
  ,{   6,   6,  1, acFont13ASCII_006F } /* code 006F */
  ,{   6,   6,  1, acFont13ASCII_0070 } /* code 0070 */
  ,{   6,   6,  1, acFont13ASCII_0071 } /* code 0071 */
  ,{   4,   4,  1, acFont13ASCII_0072 } /* code 0072 */
  ,{   5,   5,  1, acFont13ASCII_0073 } /* code 0073 */
  ,{   4,   4,  1, acFont13ASCII_0074 } /* code 0074 */
  ,{   6,   6,  1, acFont13ASCII_0075 } /* code 0075 */
  ,{   6,   6,  1, acFont13ASCII_0076 } /* code 0076 */
  ,{   8,   8,  1, acFont13ASCII_0077 } /* code 0077 */
  ,{   6,   6,  1, acFont13ASCII_0078 } /* code 0078 */
  ,{   6,   6,  1, acFont13ASCII_0079 } /* code 0079 */
  ,{   5,   5,  1, acFont13ASCII_007A } /* code 007A */
  ,{   5,   5,  1, acFont13ASCII_007B } /* code 007B */
  ,{   4,   4,  1, acFont13ASCII_007C } /* code 007C */
  ,{   5,   5,  1, acFont13ASCII_007D } /* code 007D */
  ,{   8,   8,  1, acFont13ASCII_007E } /* code 007E */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font13ASCII_Prop1 = {
   32                           /* first character               */
  ,126                          /* last character                */
  ,&GUI_Font13ASCII_CharInfo[0] /* address of first character    */
  ,(const GUI_FONT_PROP*)0      /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font13_ASCII = {
   GUI_FONTTYPE_PROP /* type of font    */
  ,13                /* height of font  */
  ,13                /* space of font y */
  ,1                 /* magnification x */
  ,1                 /* magnification y */
  ,{&GUI_Font13ASCII_Prop1}
  , 11, 6, 8
};


