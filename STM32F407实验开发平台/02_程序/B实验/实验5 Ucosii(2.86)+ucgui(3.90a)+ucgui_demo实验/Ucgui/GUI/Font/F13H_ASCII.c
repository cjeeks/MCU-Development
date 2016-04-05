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
File        : F13H_ASCII.C
Purpose     : Proportional 13 pixel high font, ASCII character set
Height      : 13
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"


/* Start of unicode area <Basic Latin> */
GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0020[ 13] = { /* code 0020 */
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

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0021[ 13] = { /* code 0021 */
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
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0022[ 13] = { /* code 0022 */
  ________,
  _X_X____,
  _X_X____,
  _X_X____,
  _X_X____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0023[ 26] = { /* code 0023 */
  ________,________,
  ________,________,
  ____X_X_,________,
  ____X_X_,________,
  __XXXXXX,________,
  ___X_X__,________,
  ___X_X__,________,
  _XXXXXX_,________,
  ___X_X__,________,
  __X_X___,________,
  __X_X___,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0024[ 13] = { /* code 0024 */
  ________,
  __X_____,
  __X_____,
  _XXXXX__,
  X_X_____,
  X_X_____,
  _XX_____,
  __XXX___,
  __X__X__,
  __X__X__,
  XXXXX___,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0025[ 26] = { /* code 0025 */
  ________,________,
  ________,________,
  __XX____,X_______,
  _X__X__X,________,
  _X__X__X,________,
  _X__X_X_,________,
  __XX_X__,XX______,
  _____X_X,__X_____,
  ____X__X,__X_____,
  ____X__X,__X_____,
  ___X____,XX______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0026[ 26] = { /* code 0026 */
  ________,________,
  ________,________,
  _XXXX___,________,
  X____X__,________,
  X____X__,________,
  _X__X___,________,
  _XXX__X_,________,
  X___X_X_,________,
  X____XX_,________,
  X____XX_,________,
  _XXXX__X,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0027[ 13] = { /* code 0027 */
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0028[ 13] = { /* code 0028 */
  ________,
  ____X___,
  ___X____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  ___X____,
  ____X___};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0029[ 13] = { /* code 0029 */
  ________,
  X_______,
  _X______,
  __X_____,
  __X_____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  _X______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_002A[ 13] = { /* code 002A */
  ________,
  ___X____,
  _X_X_X__,
  __XXX___,
  _X_X_X__,
  ___X____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_002B[ 13] = { /* code 002B */
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
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_002C[ 13] = { /* code 002C */
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

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_002D[ 13] = { /* code 002D */
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
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_002E[ 13] = { /* code 002E */
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

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_002F[ 13] = { /* code 002F */
  ________,
  ____X___,
  ____X___,
  ___X____,
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  _X______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0030[ 13] = { /* code 0030 */
  ________,
  ________,
  _XXXX___,
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

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0031[ 13] = { /* code 0031 */
  ________,
  ________,
  ___X____,
  _XXX____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0032[ 13] = { /* code 0032 */
  ________,
  ________,
  _XXXX___,
  X____X__,
  _____X__,
  _____X__,
  ____X___,
  __XX____,
  _X______,
  X_______,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0033[ 13] = { /* code 0033 */
  ________,
  ________,
  _XXXX___,
  X____X__,
  _____X__,
  _____X__,
  __XXX___,
  _____X__,
  _____X__,
  X____X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0034[ 13] = { /* code 0034 */
  ________,
  ________,
  ____X___,
  ___XX___,
  __X_X___,
  _X__X___,
  X___X___,
  XXXXXX__,
  ____X___,
  ____X___,
  ____X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0035[ 13] = { /* code 0035 */
  ________,
  ________,
  XXXXXX__,
  X_______,
  X_______,
  XXXXX___,
  _____X__,
  _____X__,
  _____X__,
  X____X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0036[ 13] = { /* code 0036 */
  ________,
  ________,
  __XXX___,
  _X______,
  X_______,
  XXXXX___,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0037[ 13] = { /* code 0037 */
  ________,
  ________,
  XXXXXX__,
  _____X__,
  ____X___,
  ____X___,
  ___X____,
  ___X____,
  __X_____,
  __X_____,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0038[ 13] = { /* code 0038 */
  ________,
  ________,
  _XXXX___,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0039[ 13] = { /* code 0039 */
  ________,
  ________,
  _XXXX___,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _XXXXX__,
  _____X__,
  ____X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_003A[ 13] = { /* code 003A */
  ________,
  ________,
  ________,
  ________,
  __X_____,
  __X_____,
  ________,
  ________,
  ________,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_003B[ 13] = { /* code 003B */
  ________,
  ________,
  ________,
  ________,
  __X_____,
  __X_____,
  ________,
  ________,
  ________,
  __X_____,
  __X_____,
  __X_____,
  _X______};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_003C[ 26] = { /* code 003C */
  ________,________,
  ________,________,
  ________,________,
  _______X,________,
  _____XX_,________,
  ___XX___,________,
  _XX_____,________,
  ___XX___,________,
  _____XX_,________,
  _______X,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_003D[ 26] = { /* code 003D */
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

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_003E[ 26] = { /* code 003E */
  ________,________,
  ________,________,
  ________,________,
  _X______,________,
  __XX____,________,
  ____XX__,________,
  ______XX,________,
  ____XX__,________,
  __XX____,________,
  _X______,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_003F[ 13] = { /* code 003F */
  ________,
  ________,
  _XXX____,
  X___X___,
  ____X___,
  ___X____,
  __X_____,
  _X______,
  ________,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0040[ 26] = { /* code 0040 */
  ________,________,
  ________,________,
  ___XXXXX,________,
  _XX_____,XX______,
  _X__XXXX,_X______,
  X__X___X,__X_____,
  X__X___X,__X_____,
  X__X___X,__X_____,
  X__X___X,__X_____,
  _X__XXXX,XX______,
  _XX_____,________,
  ___XXXXX,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0041[ 13] = { /* code 0041 */
  ________,
  ________,
  ___X____,
  ___X____,
  __X_X___,
  __X_X___,
  _X___X__,
  _X___X__,
  _XXXXX__,
  X_____X_,
  X_____X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0042[ 13] = { /* code 0042 */
  ________,
  ________,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  XXXXX___,
  X____X__,
  X____X__,
  X____X__,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0043[ 13] = { /* code 0043 */
  ________,
  ________,
  __XXXX__,
  _X____X_,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  _X____X_,
  __XXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0044[ 13] = { /* code 0044 */
  ________,
  ________,
  XXXXX___,
  X____X__,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  X____X__,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0045[ 13] = { /* code 0045 */
  ________,
  ________,
  XXXXXX__,
  X_______,
  X_______,
  X_______,
  XXXXXX__,
  X_______,
  X_______,
  X_______,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0046[ 13] = { /* code 0046 */
  ________,
  ________,
  XXXXXX__,
  X_______,
  X_______,
  X_______,
  XXXXXX__,
  X_______,
  X_______,
  X_______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0047[ 13] = { /* code 0047 */
  ________,
  ________,
  __XXXX__,
  _X____X_,
  X_______,
  X_______,
  X_______,
  X___XXX_,
  X_____X_,
  _X____X_,
  __XXXXX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0048[ 13] = { /* code 0048 */
  ________,
  ________,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  XXXXXXX_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0049[ 13] = { /* code 0049 */
  ________,
  ________,
  XXX_____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  XXX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_004A[ 13] = { /* code 004A */
  ________,
  ________,
  _XXX____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  XXX_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_004B[ 13] = { /* code 004B */
  ________,
  ________,
  X____X__,
  X___X___,
  X__X____,
  X_X_____,
  XX______,
  X_X_____,
  X__X____,
  X___X___,
  X____X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_004C[ 13] = { /* code 004C */
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
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_004D[ 26] = { /* code 004D */
  ________,________,
  ________,________,
  XX_____X,X_______,
  XX_____X,X_______,
  X_X___X_,X_______,
  X_X___X_,X_______,
  X__X_X__,X_______,
  X__X_X__,X_______,
  X___X___,X_______,
  X___X___,X_______,
  X_______,X_______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_004E[ 13] = { /* code 004E */
  ________,
  ________,
  XX____X_,
  XX____X_,
  X_X___X_,
  X_X___X_,
  X__X__X_,
  X___X_X_,
  X___X_X_,
  X____XX_,
  X____XX_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_004F[ 26] = { /* code 004F */
  ________,________,
  ________,________,
  __XXXX__,________,
  _X____X_,________,
  X______X,________,
  X______X,________,
  X______X,________,
  X______X,________,
  X______X,________,
  _X____X_,________,
  __XXXX__,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0050[ 13] = { /* code 0050 */
  ________,
  ________,
  XXXXX___,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  XXXXX___,
  X_______,
  X_______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0051[ 26] = { /* code 0051 */
  ________,________,
  ________,________,
  __XXXX__,________,
  _X____X_,________,
  X______X,________,
  X______X,________,
  X______X,________,
  X______X,________,
  X______X,________,
  _X____X_,________,
  __XXXX__,________,
  ____X___,________,
  _____XXX,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0052[ 13] = { /* code 0052 */
  ________,
  ________,
  XXXXX___,
  X____X__,
  X____X__,
  X____X__,
  X___X___,
  XXXX____,
  X___X___,
  X____X__,
  X_____X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0053[ 13] = { /* code 0053 */
  ________,
  ________,
  _XXXXX__,
  X_____X_,
  X_______,
  X_______,
  _XXXXX__,
  ______X_,
  ______X_,
  X_____X_,
  _XXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0054[ 13] = { /* code 0054 */
  ________,
  ________,
  XXXXXXX_,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0055[ 13] = { /* code 0055 */
  ________,
  ________,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___X__,
  __XXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0056[ 13] = { /* code 0056 */
  ________,
  ________,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___X__,
  _X___X__,
  __X_X___,
  __X_X___,
  ___X____,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0057[ 26] = { /* code 0057 */
  ________,________,
  ________,________,
  X____X__,__X_____,
  X____X__,__X_____,
  X___X_X_,__X_____,
  X___X_X_,__X_____,
  _X__X_X_,_X______,
  _X_X___X,_X______,
  _X_X___X,_X______,
  _X_X___X,_X______,
  __X_____,X_______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0058[ 13] = { /* code 0058 */
  ________,
  ________,
  X_____X_,
  _X___X__,
  __X_X___,
  __X_X___,
  ___X____,
  __X_X___,
  __X_X___,
  _X___X__,
  X_____X_,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0059[ 13] = { /* code 0059 */
  ________,
  ________,
  X_____X_,
  _X___X__,
  _X___X__,
  __X_X___,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_005A[ 13] = { /* code 005A */
  ________,
  ________,
  XXXXXX__,
  _____X__,
  ____X___,
  ___X____,
  __X_____,
  __X_____,
  _X______,
  X_______,
  XXXXXX__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_005B[ 13] = { /* code 005B */
  ________,
  _XXX____,
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
  _XXX____};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_005C[ 13] = { /* code 005C */
  ________,
  X_______,
  X_______,
  _X______,
  _X______,
  _X______,
  __X_____,
  __X_____,
  ___X____,
  ___X____,
  ___X____,
  ____X___,
  ____X___};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_005D[ 13] = { /* code 005D */
  ________,
  _XXX____,
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
  _XXX____};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_005E[ 26] = { /* code 005E */
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

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_005F[ 13] = { /* code 005F */
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

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0060[ 13] = { /* code 0060 */
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
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0061[ 13] = { /* code 0061 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  _____X__,
  _____X__,
  _XXXXX__,
  X____X__,
  X___XX__,
  _XXX_X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0062[ 13] = { /* code 0062 */
  ________,
  X_______,
  X_______,
  X_______,
  X_XXX___,
  XX___X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0063[ 13] = { /* code 0063 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0064[ 13] = { /* code 0064 */
  ________,
  _____X__,
  _____X__,
  _____X__,
  _XXXXX__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X___XX__,
  _XXX_X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0065[ 13] = { /* code 0065 */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  X____X__,
  X____X__,
  XXXXXX__,
  X_______,
  X____X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0066[ 13] = { /* code 0066 */
  ________,
  __XX____,
  _X______,
  _X______,
  XXXX____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0067[ 13] = { /* code 0067 */
  ________,
  ________,
  ________,
  ________,
  _XXXXX__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X___XX__,
  _XXX_X__,
  _____X__,
  _XXXX___};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0068[ 13] = { /* code 0068 */
  ________,
  X_______,
  X_______,
  X_______,
  X_XXX___,
  XX___X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0069[ 13] = { /* code 0069 */
  ________,
  ________,
  _X______,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_006A[ 13] = { /* code 006A */
  ________,
  ________,
  __X_____,
  ________,
  _XX_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  XX______};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_006B[ 13] = { /* code 006B */
  ________,
  X_______,
  X_______,
  X_______,
  X___X___,
  X__X____,
  X_X_____,
  XX______,
  X_X_____,
  X__X____,
  X___X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_006C[ 13] = { /* code 006C */
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
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_006D[ 26] = { /* code 006D */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  _X_XX__X,X_______,
  _XX__XX_,_X______,
  _X___X__,_X______,
  _X___X__,_X______,
  _X___X__,_X______,
  _X___X__,_X______,
  _X___X__,_X______,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_006E[ 13] = { /* code 006E */
  ________,
  ________,
  ________,
  ________,
  X_XXX___,
  XX___X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_006F[ 13] = { /* code 006F */
  ________,
  ________,
  ________,
  ________,
  _XXXX___,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0070[ 13] = { /* code 0070 */
  ________,
  ________,
  ________,
  ________,
  X_XXX___,
  XX___X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  XXXXX___,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0071[ 13] = { /* code 0071 */
  ________,
  ________,
  ________,
  ________,
  _XXXXX__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X___XX__,
  _XXX_X__,
  _____X__,
  _____X__};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0072[ 13] = { /* code 0072 */
  ________,
  ________,
  ________,
  ________,
  X_XX____,
  XX______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0073[ 13] = { /* code 0073 */
  ________,
  ________,
  ________,
  ________,
  _XXX____,
  X___X___,
  X_______,
  _XXX____,
  ____X___,
  X___X___,
  _XXX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0074[ 13] = { /* code 0074 */
  ________,
  ________,
  _X______,
  _X______,
  XXXX____,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  __XX____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0075[ 13] = { /* code 0075 */
  ________,
  ________,
  ________,
  ________,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X___XX__,
  _XXX_X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0076[ 13] = { /* code 0076 */
  ________,
  ________,
  ________,
  ________,
  X___X___,
  X___X___,
  _X_X____,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0077[ 26] = { /* code 0077 */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  X___X___,X_______,
  X___X___,X_______,
  _X_X_X_X,________,
  _X_X_X_X,________,
  _X_X_X_X,________,
  __X___X_,________,
  __X___X_,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0078[ 13] = { /* code 0078 */
  ________,
  ________,
  ________,
  ________,
  X___X___,
  _X_X____,
  _X_X____,
  __X_____,
  _X_X____,
  _X_X____,
  X___X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_0079[ 13] = { /* code 0079 */
  ________,
  ________,
  ________,
  ________,
  X___X___,
  X___X___,
  _X_X____,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  __X_____,
  _X______};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_007A[ 13] = { /* code 007A */
  ________,
  ________,
  ________,
  ________,
  XXXXX___,
  ____X___,
  ___X____,
  __X_____,
  _X______,
  X_______,
  XXXXX___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_007B[ 13] = { /* code 007B */
  ________,
  ___XX___,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  XX______,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ___XX___};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_007C[ 13] = { /* code 007C */
  ________,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_007D[ 13] = { /* code 007D */
  ________,
  XX______,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  ___XX___,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  XX______};

GUI_CONST_STORAGE unsigned char acFont13H_ASCII_007E[ 26] = { /* code 007E */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  __XX___X,________,
  _X__X__X,________,
  _X___XX_,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};


GUI_CONST_STORAGE GUI_CHARINFO GUI_Font13H_ASCII_CharInfo[95] = {
   {   4,   4,  1, acFont13H_ASCII_0020 } /* code 0020 */
  ,{   4,   4,  1, acFont13H_ASCII_0021 } /* code 0021 */
  ,{   5,   5,  1, acFont13H_ASCII_0022 } /* code 0022 */
  ,{   9,   9,  2, acFont13H_ASCII_0023 } /* code 0023 */
  ,{   7,   7,  1, acFont13H_ASCII_0024 } /* code 0024 */
  ,{  12,  12,  2, acFont13H_ASCII_0025 } /* code 0025 */
  ,{   9,   9,  2, acFont13H_ASCII_0026 } /* code 0026 */
  ,{   3,   3,  1, acFont13H_ASCII_0027 } /* code 0027 */
  ,{   5,   5,  1, acFont13H_ASCII_0028 } /* code 0028 */
  ,{   5,   5,  1, acFont13H_ASCII_0029 } /* code 0029 */
  ,{   8,   8,  1, acFont13H_ASCII_002A } /* code 002A */
  ,{   8,   8,  1, acFont13H_ASCII_002B } /* code 002B */
  ,{   4,   4,  1, acFont13H_ASCII_002C } /* code 002C */
  ,{   5,   5,  1, acFont13H_ASCII_002D } /* code 002D */
  ,{   4,   4,  1, acFont13H_ASCII_002E } /* code 002E */
  ,{   5,   5,  1, acFont13H_ASCII_002F } /* code 002F */
  ,{   7,   7,  1, acFont13H_ASCII_0030 } /* code 0030 */
  ,{   7,   7,  1, acFont13H_ASCII_0031 } /* code 0031 */
  ,{   7,   7,  1, acFont13H_ASCII_0032 } /* code 0032 */
  ,{   7,   7,  1, acFont13H_ASCII_0033 } /* code 0033 */
  ,{   7,   7,  1, acFont13H_ASCII_0034 } /* code 0034 */
  ,{   7,   7,  1, acFont13H_ASCII_0035 } /* code 0035 */
  ,{   7,   7,  1, acFont13H_ASCII_0036 } /* code 0036 */
  ,{   7,   7,  1, acFont13H_ASCII_0037 } /* code 0037 */
  ,{   7,   7,  1, acFont13H_ASCII_0038 } /* code 0038 */
  ,{   7,   7,  1, acFont13H_ASCII_0039 } /* code 0039 */
  ,{   5,   5,  1, acFont13H_ASCII_003A } /* code 003A */
  ,{   5,   5,  1, acFont13H_ASCII_003B } /* code 003B */
  ,{   9,   9,  2, acFont13H_ASCII_003C } /* code 003C */
  ,{   9,   9,  2, acFont13H_ASCII_003D } /* code 003D */
  ,{   9,   9,  2, acFont13H_ASCII_003E } /* code 003E */
  ,{   6,   6,  1, acFont13H_ASCII_003F } /* code 003F */
  ,{  12,  12,  2, acFont13H_ASCII_0040 } /* code 0040 */
  ,{   8,   8,  1, acFont13H_ASCII_0041 } /* code 0041 */
  ,{   7,   7,  1, acFont13H_ASCII_0042 } /* code 0042 */
  ,{   8,   8,  1, acFont13H_ASCII_0043 } /* code 0043 */
  ,{   8,   8,  1, acFont13H_ASCII_0044 } /* code 0044 */
  ,{   7,   7,  1, acFont13H_ASCII_0045 } /* code 0045 */
  ,{   7,   7,  1, acFont13H_ASCII_0046 } /* code 0046 */
  ,{   8,   8,  1, acFont13H_ASCII_0047 } /* code 0047 */
  ,{   8,   8,  1, acFont13H_ASCII_0048 } /* code 0048 */
  ,{   4,   4,  1, acFont13H_ASCII_0049 } /* code 0049 */
  ,{   5,   5,  1, acFont13H_ASCII_004A } /* code 004A */
  ,{   7,   7,  1, acFont13H_ASCII_004B } /* code 004B */
  ,{   6,   6,  1, acFont13H_ASCII_004C } /* code 004C */
  ,{  10,  10,  2, acFont13H_ASCII_004D } /* code 004D */
  ,{   8,   8,  1, acFont13H_ASCII_004E } /* code 004E */
  ,{   9,   9,  2, acFont13H_ASCII_004F } /* code 004F */
  ,{   7,   7,  1, acFont13H_ASCII_0050 } /* code 0050 */
  ,{   9,   9,  2, acFont13H_ASCII_0051 } /* code 0051 */
  ,{   8,   8,  1, acFont13H_ASCII_0052 } /* code 0052 */
  ,{   8,   8,  1, acFont13H_ASCII_0053 } /* code 0053 */
  ,{   8,   8,  1, acFont13H_ASCII_0054 } /* code 0054 */
  ,{   8,   8,  1, acFont13H_ASCII_0055 } /* code 0055 */
  ,{   8,   8,  1, acFont13H_ASCII_0056 } /* code 0056 */
  ,{  12,  12,  2, acFont13H_ASCII_0057 } /* code 0057 */
  ,{   8,   8,  1, acFont13H_ASCII_0058 } /* code 0058 */
  ,{   7,   7,  1, acFont13H_ASCII_0059 } /* code 0059 */
  ,{   7,   7,  1, acFont13H_ASCII_005A } /* code 005A */
  ,{   5,   5,  1, acFont13H_ASCII_005B } /* code 005B */
  ,{   5,   5,  1, acFont13H_ASCII_005C } /* code 005C */
  ,{   5,   5,  1, acFont13H_ASCII_005D } /* code 005D */
  ,{   9,   9,  2, acFont13H_ASCII_005E } /* code 005E */
  ,{   7,   7,  1, acFont13H_ASCII_005F } /* code 005F */
  ,{   7,   7,  1, acFont13H_ASCII_0060 } /* code 0060 */
  ,{   7,   7,  1, acFont13H_ASCII_0061 } /* code 0061 */
  ,{   7,   7,  1, acFont13H_ASCII_0062 } /* code 0062 */
  ,{   6,   6,  1, acFont13H_ASCII_0063 } /* code 0063 */
  ,{   7,   7,  1, acFont13H_ASCII_0064 } /* code 0064 */
  ,{   7,   7,  1, acFont13H_ASCII_0065 } /* code 0065 */
  ,{   4,   4,  1, acFont13H_ASCII_0066 } /* code 0066 */
  ,{   7,   7,  1, acFont13H_ASCII_0067 } /* code 0067 */
  ,{   7,   7,  1, acFont13H_ASCII_0068 } /* code 0068 */
  ,{   3,   3,  1, acFont13H_ASCII_0069 } /* code 0069 */
  ,{   4,   4,  1, acFont13H_ASCII_006A } /* code 006A */
  ,{   6,   6,  1, acFont13H_ASCII_006B } /* code 006B */
  ,{   3,   3,  1, acFont13H_ASCII_006C } /* code 006C */
  ,{  11,  11,  2, acFont13H_ASCII_006D } /* code 006D */
  ,{   7,   7,  1, acFont13H_ASCII_006E } /* code 006E */
  ,{   7,   7,  1, acFont13H_ASCII_006F } /* code 006F */
  ,{   7,   7,  1, acFont13H_ASCII_0070 } /* code 0070 */
  ,{   7,   7,  1, acFont13H_ASCII_0071 } /* code 0071 */
  ,{   5,   5,  1, acFont13H_ASCII_0072 } /* code 0072 */
  ,{   6,   6,  1, acFont13H_ASCII_0073 } /* code 0073 */
  ,{   4,   4,  1, acFont13H_ASCII_0074 } /* code 0074 */
  ,{   7,   7,  1, acFont13H_ASCII_0075 } /* code 0075 */
  ,{   6,   6,  1, acFont13H_ASCII_0076 } /* code 0076 */
  ,{  10,  10,  2, acFont13H_ASCII_0077 } /* code 0077 */
  ,{   6,   6,  1, acFont13H_ASCII_0078 } /* code 0078 */
  ,{   6,   6,  1, acFont13H_ASCII_0079 } /* code 0079 */
  ,{   6,   6,  1, acFont13H_ASCII_007A } /* code 007A */
  ,{   6,   6,  1, acFont13H_ASCII_007B } /* code 007B */
  ,{   6,   6,  1, acFont13H_ASCII_007C } /* code 007C */
  ,{   6,   6,  1, acFont13H_ASCII_007D } /* code 007D */
  ,{   9,   9,  2, acFont13H_ASCII_007E } /* code 007E */
};

GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font13H_ASCII_Prop1 = {
   0x0020                         /* first character */
  ,0x007E                         /* last character  */
  ,&GUI_Font13H_ASCII_CharInfo[0] /* address of first character */
  ,(const GUI_FONT_PROP*)0        /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font13H_ASCII = {
   GUI_FONTTYPE_PROP        /* type of font    */
  ,13                       /* height of font  */
  ,13                       /* space of font y */
  ,1                        /* magnification x */
  ,1                        /* magnification y */
  ,{&GUI_Font13H_ASCII_Prop1}
  , 11, 7, 9
};

