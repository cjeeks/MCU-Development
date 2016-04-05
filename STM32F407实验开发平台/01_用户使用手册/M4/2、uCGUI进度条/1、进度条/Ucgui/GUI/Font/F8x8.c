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
File        : F8x8.C
Purpose     : Implementation of 8x8 pixel font
Height      : 8
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"

/*      *********************************
        *                               *
        *   Special character codes     *
        *                               *
        *********************************
*/

/* No 95 to 125 for European character set  */

#define CODE_SACCAGUE     95     /*  small accent ague */
#define CODE_SACCGRAV     96
#define CODE_SACCCIRC     97
#define CODE_SUMLAUT      98
#define CODE_STILDE       99
#define CODE_I_NOPOINT    100

#define CODE_SHARPS       101
#define CODE_A_RING       102
#define CODE_SA_RING      103
#define CODE_AE           104
#define CODE_ETH          105
#define CODE_THORN        106
#define CODE_SMALLAE      107
#define CODE_SMALLETH     108
#define CODE_SMALLTHORN   109
#define CODE_OSLASH       110
#define CODE_SOSLASH      111
#define CODE_LITTLE_A     112
#define CODE_LITTLE_E     113
#define CODE_LITTLE_I     114
#define CODE_LITTLE_O     115
#define CODE_LITTLE_U     116
#define CODE_LITTLE_N     117

#define CODE_INVEXCLAM    118
#define CODE_INVQUEST     119

#define CODE_CACCAGUE     120    /* capital accent ague */
#define CODE_CACCGRAV     121
#define CODE_CACCCIRC     122
#define CODE_CUMLAUT      123
#define CODE_CTILDE       124
#define CODE_CEDILLA      125

/* No 126 to 156 for complete ISO 8859_1 western latin character set  */
#define CODE_NB_SPACE     126
#define CODE_CENT         127
#define CODE_POUND        128
#define CODE_CURRENCY     129
#define CODE_YEN          130
#define CODE_BROKEN_BAR   131
#define CODE_SECTION      132
#define CODE_DIERESIS     133
#define CODE_COPYRIGHT    134
#define CODE_FEMININE     135
#define CODE_LEFT_QUOTE   136
#define CODE_NOT          137
#define CODE_HYPHEN       138
#define CODE_TRADEMARK    139
#define CODE_MACRON       140
#define CODE_DEGREE       141
#define CODE_PLUS_MINUS   142
#define CODE_SUPER_TWO    143
#define CODE_SUPER_THREE  144
#define CODE_ACUTE        145
#define CODE_MICRO        146
#define CODE_PARAGRAPH    147
#define CODE_MIDDLE_DOT   148
#define CODE_SUPER_ONE    149
#define CODE_MASCULINE    150
#define CODE_RIGHT_QUOTE  151
#define CODE_ONE_FOURTH   152
#define CODE_ONE_HALF     153
#define CODE_THREE_FOURTH 154
#define CODE_MULTIPLY     155
#define CODE_DIVISION     156
/* The following are extensions to ISO 8859-1 in the area which is not
   defined by the standard.
*/
#define CODE_ARROW_LEFT   157
#define CODE_ARROW_RIGHT  158
#define CODE_ARROW_UP     159
#define CODE_ARROW_DOWN   160
#define CODE_ENTER        161
#define CODE_CHECKMARK    162





/*
    ****************************************************************
    *                                                              *
    *                      8 * 8  font                             *
    *                                                              *
    ****************************************************************
*/


GUI_CONST_STORAGE unsigned char GUI_F8x8_acFont[][8] = {

  {
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}  /* char ' '  */

 ,{
   ___XX___,
   __XXXX__,
   __XXXX__,
   ___XX___,
   ___XX___,
   ________,
   ___XX___,
   ________}  /* char '!'  */

 ,{
   _XX__XX_,
   _XX__XX_,
   __X__X__,
   ________,
   ________,
   ________,
   ________,
   ________}  /* char '"'  */

 ,{
   _XX_XX__,
   _XX_XX__,
   XXXXXXX_,
   _XX_XX__,
   XXXXXXX_,
   _XX_XX__,
   _XX_XX__,
   ________}  /* char '#'  */

 ,{
   ___XX___,
   __XXXXX_,
   _XX_____,
   __XXXX__,
   _____XX_,
   _XXXXX__,
   ___XX___,
   ________}  /* char '$'  */

 ,{
   ________,
   XX___XX_,
   XX__XX__,
   ___XX___,
   __XX____,
   _XX__XX_,
   XX___XX_,
   ________}  /* char '%'  */

 ,{
   __XXX___,
   _XX_XX__,
   __XXX___,
   _XXX_XX_,
   XX_XXX__,
   XX__XX__,
   _XXX_XX_,
   ________}  /* char '&'  */

 ,{
   ___XX___,
   ___XX___,
   __XX____,
   ________,
   ________,
   ________,
   ________,
   ________}  /* char '''  */

 ,{
   ____XX__,
   ___XX___,
   __XX____,
   __XX____,
   __XX____,
   ___XX___,
   ____XX__,
   ________}  /* char '('  */

 ,{
   __XX____,
   ___XX___,
   ____XX__,
   ____XX__,
   ____XX__,
   ___XX___,
   __XX____,
   ________}  /* char ')'  */

 ,{
   ________,
   _XX__XX_,
   __XXXX__,
   XXXXXXXX,
   __XXXX__,
   _XX__XX_,
   ________,
   ________}  /* char '*'  */

 ,{
   ________,
   ___XX___,
   ___XX___,
   _XXXXXX_,
   ___XX___,
   ___XX___,
   ________,
   ________}  /* char '+'  */

 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   ___XX___,
   ___XX___,
   __XX____}  /* char ','  */

 ,{
   ________,
   ________,
   ________,
   _XXXXXX_,
   ________,
   ________,
   ________,
   ________}  /* char '-'  */

 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   ___XX___,
   ___XX___,
   ________}  /* char '.'  */

 ,{
   _____XX_,
   ____XX__,
   ___XX___,
   __XX____,
   _XX_____,
   XX______,
   X_______,
   ________}  /* char '/'  */

 ,{
   __XXX___,
   _XX_XX__,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   ________}  /* char '0'  */

 ,{
   ___XX___,
   __XXX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   _XXXXXX_,
   ________}  /* char '1'  */

 ,{
   _XXXXX__,
   XX___XX_,
   _____XX_,
   ___XXX__,
   __XX____,
   _XX__XX_,
   XXXXXXX_,
   ________}  /* char '2'  */

 ,{
   _XXXXX__,
   XX___XX_,
   _____XX_,
   __XXXX__,
   _____XX_,
   XX___XX_,
   _XXXXX__,
   ________}  /* char '3'  */

 ,{
   ___XXX__,
   __XXXX__,
   _XX_XX__,
   XX__XX__,
   XXXXXXX_,
   ____XX__,
   ___XXXX_,
   ________}  /* char '4'  */

 ,{
   XXXXXXX_,
   XX______,
   XX______,
   XXXXXX__,
   _____XX_,
   XX___XX_,
   _XXXXX__,
   ________}  /* char '5'  */

 ,{
   __XXX___,
   _XX_____,
   XX______,
   XXXXXX__,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}  /* char '6'  */

 ,{
   XXXXXXX_,
   XX___XX_,
   ____XX__,
   ___XX___,
   __XX____,
   __XX____,
   __XX____,
   ________}  /* char '7'  */

 ,{
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}  /* char '8'  */

 ,{
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   _XXXXXX_,
   _____XX_,
   ____XX__,
   _XXXX___,
   ________}  /* char '9'  */

 ,{
   ________,
   ___XX___,
   ___XX___,
   ________,
   ________,
   ___XX___,
   ___XX___,
   ________}  /* char ':'  */

 ,{
   ________,
   ___XX___,
   ___XX___,
   ________,
   ________,
   ___XX___,
   ___XX___,
   __XX____}  /* char ';'  */

 ,{
   _____XX_,
   ____XX__,
   ___XX___,
   __XX____,
   ___XX___,
   ____XX__,
   _____XX_,
   ________}  /* char '<'  */

 ,{
   ________,
   ________,
   _XXXXXX_,
   ________,
   ________,
   _XXXXXX_,
   ________,
   ________}  /* char '='  */

 ,{
   _XX_____,
   __XX____,
   ___XX___,
   ____XX__,
   ___XX___,
   __XX____,
   _XX_____,
   ________}  /* char '>'  */

 ,{
   _XXXXX__,
   XX___XX_,
   ____XX__,
   ___XX___,
   ___XX___,
   ________,
   ___XX___,
   ________}  /* char '?'  */

 ,{
   _XXXXX__,
   XX___XX_,
   XX_XXXX_,
   XX_XXXX_,
   XX_XXXX_,
   XX______,
   _XXXX___,
   ________}  /* char '@'  */

 ,{
   __XXX___,
   _XX_XX__,
   XX___XX_,
   XXXXXXX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   ________}  /* char 'A'  */

 ,{
   XXXXXX__,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   _XX__XX_,
   _XX__XX_,
   XXXXXX__,
   ________}  /* char 'B'  */

 ,{
   __XXXX__,
   _XX__XX_,
   XX______,
   XX______,
   XX______,
   _XX__XX_,
   __XXXX__,
   ________}  /* char 'C'  */

 ,{
   XXXXX___,
   _XX_XX__,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   _XX_XX__,
   XXXXX___,
   ________}  /* char 'D'  */

 ,{
   XXXXXXX_,
   _XX___X_,
   _XX_X___,
   _XXXX___,
   _XX_X___,
   _XX___X_,
   XXXXXXX_,
   ________}  /* char 'E'  */

 ,{
   XXXXXXX_,
   _XX___X_,
   _XX_X___,
   _XXXX___,
   _XX_X___,
   _XX_____,
   XXXX____,
   ________}  /* char 'F'  */

 ,{
   __XXXX__,
   _XX__XX_,
   XX______,
   XX______,
   XX__XXX_,
   _XX__XX_,
   __XXX_X_,
   ________}  /* char 'G'  */

 ,{
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XXXXXXX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   ________}  /* char 'H'  */

 ,{
   __XXXX__,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}  /* char 'I'  */

 ,{
   ___XXXX_,
   ____XX__,
   ____XX__,
   ____XX__,
   XX__XX__,
   XX__XX__,
   _XXXX___,
   ________}  /* char 'J'  */

 ,{
   XXX__XX_,
   _XX__XX_,
   _XX_XX__,
   _XXXX___,
   _XX_XX__,
   _XX__XX_,
   XXX__XX_,
   ________}  /* char 'K'  */

 ,{
   XXXX____,
   _XX_____,
   _XX_____,
   _XX_____,
   _XX___X_,
   _XX__XX_,
   XXXXXXX_,
   ________}  /* char 'L'  */

 ,{
   XX___XX_,
   XXX_XXX_,
   XXXXXXX_,
   XXXXXXX_,
   XX_X_XX_,
   XX___XX_,
   XX___XX_,
   ________}  /* char 'M'  */

 ,{
   XX___XX_,
   XXX__XX_,
   XXXX_XX_,
   XX_XXXX_,
   XX__XXX_,
   XX___XX_,
   XX___XX_,
   ________}  /* char 'N'  */

 ,{
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}  /* char 'O'  */

 ,{
   XXXXXX__,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   _XX_____,
   _XX_____,
   XXXX____,
   ________}  /* char 'P'  */

 ,{
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX__XXX_,
   _XXXXX__,
   ____XXX_}  /* char 'Q'  */

 ,{
   XXXXXX__,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   _XX_XX__,
   _XX__XX_,
   XXX__XX_,
   ________}  /* char 'R'  */

 ,{
   __XXXX__,
   _XX__XX_,
   __XX____,
   ___XX___,
   ____XX__,
   _XX__XX_,
   __XXXX__,
   ________}  /* char 'S'  */

 ,{
   _XXXXXX_,
   _XXXXXX_,
   _X_XX_X_,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}  /* char 'T'  */

 ,{
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}  /* char 'U'  */

 ,{
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   ________}  /* char 'V'  */

 ,{
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX_X_XX_,
   XX_X_XX_,
   XXXXXXX_,
   _XX_XX__,
   ________}  /* char 'W'  */

 ,{
   XX___XX_,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   _XX_XX__,
   XX___XX_,
   XX___XX_,
   ________}  /* char 'X'  */

 ,{
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   __XXXX__,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}  /* char 'Y'  */

 ,{
   XXXXXXX_,
   XX___XX_,
   X___XX__,
   ___XX___,
   __XX__X_,
   _XX__XX_,
   XXXXXXX_,
   ________}  /* char 'Z'  */

 ,{
   __XXXX__,
   __XX____,
   __XX____,
   __XX____,
   __XX____,
   __XX____,
   __XXXX__,
   ________}  /* char '['  */

 ,{
   XX______,
   _XX_____,
   __XX____,
   ___XX___,
   ____XX__,
   _____XX_,
   ______X_,
   ________}  /* char '\'  */

 ,{
   __XXXX__,
   ____XX__,
   ____XX__,
   ____XX__,
   ____XX__,
   ____XX__,
   __XXXX__,
   ________}  /* char ']'  */

 ,{
   ___X____,
   __XXX___,
   _XX_XX__,
   XX___XX_,
   ________,
   ________,
   ________,
   ________}  /* char '^'  */

 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   XXXXXXXX}  /* char '_'  */

 ,{
   __XX____,
   ___XX___,
   ____XX__,
   ________,
   ________,
   ________,
   ________,
   ________}  /* char '`'  */

 ,{
   ________,
   ________,
   _XXXX___,
   ____XX__,
   _XXXXX__,
   XX__XX__,
   _XXX_XX_,
   ________}  /* char 'a'  */

 ,{
   XXX_____,
   _XX_____,
   _XXXXX__,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   XX_XXX__,
   ________}  /* char 'b'  */

 ,{
   ________,
   ________,
   _XXXXX__,
   XX___XX_,
   XX______,
   XX___XX_,
   _XXXXX__,
   ________}  /* char 'c'  */

 ,{
   ___XXX__,
   ____XX__,
   _XXXXX__,
   XX__XX__,
   XX__XX__,
   XX__XX__,
   _XXX_XX_,
   ________}  /* char 'd'  */

 ,{
   ________,
   ________,
   _XXXXX__,
   XX___XX_,
   XXXXXXX_,
   XX______,
   _XXXXX__,
   ________}  /* char 'e'  */

 ,{
   __XXXX__,
   _XX__XX_,
   _XX_____,
   XXXXX___,
   _XX_____,
   _XX_____,
   XXXX____,
   ________}  /* char 'f'  */

 ,{
   ________,
   ________,
   _XXX_XX_,
   XX__XX__,
   XX__XX__,
   _XXXXX__,
   ____XX__,
   XXXXX___}  /* char 'g'  */

 ,{
   XXX_____,
   _XX_____,
   _XX_XX__,
   _XXX_XX_,
   _XX__XX_,
   _XX__XX_,
   XXX__XX_,
   ________}  /* char 'h'  */

 ,{
   ___XX___,
   ________,
   __XXX___,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}  /* char 'i'  */

 ,{
   _____XX_,
   ________,
   _____XX_,
   _____XX_,
   _____XX_,
   _XX__XX_,
   _XX__XX_,
   __XXXX__}  /* char 'j'  */

 ,{
   XXX_____,
   _XX_____,
   _XX__XX_,
   _XX_XX__,
   _XXXX___,
   _XX_XX__,
   XXX__XX_,
   ________}  /* char 'k'  */

 ,{
   __XXX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}  /* char 'l'  */

 ,{
   ________,
   ________,
   XXX_XX__,
   XXXXXXX_,
   XX_X_XX_,
   XX_X_XX_,
   XX_X_XX_,
   ________}  /* char 'm'  */

 ,{
   ________,
   ________,
   XX_XXX__,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   ________}  /* char 'n'  */

 ,{
   ________,
   ________,
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}  /* char 'o'  */

 ,{
   ________,
   ________,
   XX_XXX__,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   _XX_____,
   XXXX____}  /* char 'p'  */

 ,{
   ________,
   ________,
   _XXX_XX_,
   XX__XX__,
   XX__XX__,
   _XXXXX__,
   ____XX__,
   ___XXXX_}  /* char 'q'  */

 ,{
   ________,
   ________,
   XX_XXX__,
   _XXX_XX_,
   _XX_____,
   _XX_____,
   XXXX____,
   ________}  /* char 'r'  */

 ,{
   ________,
   ________,
   _XXXXXX_,
   XX______,
   _XXXXX__,
   _____XX_,
   XXXXXX__,
   ________}  /* char 's'  */

 ,{
   __XX____,
   __XX____,
   XXXXXX__,
   __XX____,
   __XX____,
   __XX_XX_,
   ___XXX__,
   ________}  /* char 't'  */

 ,{
   ________,
   ________,
   XX__XX__,
   XX__XX__,
   XX__XX__,
   XX__XX__,
   _XXX_XX_,
   ________}  /* char 'u'  */

 ,{
   ________,
   ________,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   ________}  /* char 'v'  */

 ,{
   ________,
   ________,
   XX___XX_,
   XX_X_XX_,
   XX_X_XX_,
   XXXXXXX_,
   _XX_XX__,
   ________}  /* char 'w'  */

 ,{
   ________,
   ________,
   XX___XX_,
   _XX_XX__,
   __XXX___,
   _XX_XX__,
   XX___XX_,
   ________}  /* char 'x'  */

 ,{
   ________,
   ________,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXXX_,
   _____XX_,
   XXXXXX__}  /* char 'y'  */

 ,{
   ________,
   ________,
   _XXXXXX_,
   _X__XX__,
   ___XX___,
   __XX__X_,
   _XXXXXX_,
   ________}  /* char 'z'  */

 ,{
   ____XXX_,
   ___XX___,
   ___XX___,
   _XXX____,
   ___XX___,
   ___XX___,
   ____XXX_,
   ________}  /* char '{'  */

 ,{
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ___XX___,
   ________}  /* char '|'  */

 ,{
   _XXX____,
   ___XX___,
   ___XX___,
   ____XXX_,
   ___XX___,
   ___XX___,
   _XXX____,
   ________}  /* char '}'  */

 ,{
   _XXX_XX_,
   XX_XXX__,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}   /* char '~'  */



/*  additional characters for European character set  */

/* small accent ague, 95 */
 ,{
   ____XX__,
   ___X____,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}

 /* small accent grave, 96 */
 ,{
   _XX_____,
   ___X____,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


/* small accent circonflex, 97 */
 ,{
   _XXXXX__,
   X_____X_,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* small umlaut, 98 */
 ,{
   XX___XX_,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* small tilde, 99  */
 ,{
   _XXX__X_,
   X___XX__,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* i without dot, 100  */
 ,{
   ________,
   ________,
   __XXX___,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}


 /* sharps eg á, 101  */
 ,{
   __XXX___,
   _XX_XX__,
   _XX_XX__,
   _XXXX___,
   _XX__XX_,
   _XX__XX_,
   _XX_XX__,
   XX______}


 /* capital A with ring, 102  */
 ,{
   ___XX___,
   ________,
   __XXXX__,
   _XX__XX_,
   _XXXXXX_,
   _XX__XX_,
   _XX__XX_,
   ________}


 /* small a with ring, 103  */
 ,{
   __XX____,
   ________,
   _XXXX___,
   ____XX__,
   _XXXXX__,
   XX__XX__,
   _XXX_XX_,
   ________}



 /*  capital A diphtong, ligature, 104  */
 ,{
   ___XXXX_,
   _XXXX___,
   X__XX___,
   X__XXXX_,
   XXXXX___,
   X__XX___,
   X__XXXX_,
   ________}


 /*  Icelandic eth, 105  */
 ,{
   _XXXXX__,
   _XX__XX_,
   _XX__XX_,
   XXXX_XX_,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   ________}


 /*  Icelandic Thorn, 106  */
 ,{
   XXXX____,
   _XX_____,
   _XXXXX__,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   _XX_____,
   XXXX____}


 /*  small a diphtong, ligature, 107  */
 ,{
   ________,
   ________,
   XX__XX__,
   __XX__X_,
   _XXXXXX_,
   X_XX____,
   XXX_XX__,
   ________}


 /*  small Icelanic Eth, 108 */
 ,{
   _XX_X___,
   __XX____,
   _X_XX___,
   ____XX__,
   _XXXXXX_,
   XX___XX_,
   _XXXXX__,
   ________}


 /*  small Icelandic Thorn, 109 */
 ,{
   _XXX____,
   __XX____,
   __XXXX__,
   __XX_XX_,
   __XXXX__,
   __XX____,
   _XXXX___,
   ________}


 /*  capital O with slash, 110 */
 ,{
   __XXX_X_,
   _XX_XX__,
   XX__XXX_,
   XX_X_XX_,
   XXX__XX_,
   _XX_XX__,
   X_XXX___,
   ________}


 /*  small o with slash, 111 */
 ,{
   ________,
   ______X_,
   _XXXXX__,
   XX__XXX_,
   XX_X_XX_,
   XXX__XX_,
   _XXXXX__,
   X_______}


 /*  Little capital A, 112 */
 ,{
   ________,
   ________,
   _XXXXX__,
   XX___XX_,
   XXXXXXX_,
   XX___XX_,
   XX___XX_,
   ________}


 /*  Little capital E, 113 */
 ,{
   ________,
   ________,
   XXXXXXX_,
   _XX_____,
   _XXXXX__,
   _XX_____,
   XXXXXXX_,
   ________}


 /*  Little capital I, 114 */
 ,{
   ________,
   ________,
   __XXXX__,
   ___XX___,
   ___XX___,
   ___XX___,
   __XXXX__,
   ________}


 /*  Little capital O, 115 */
 ,{
   ________,
   ________,
   _XXXXX__,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}


 /*  Little capital U, 116 */
 ,{
   ________,
   ________,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   XX___XX_,
   _XXXXX__,
   ________}


 /*  Little capital N, 117 */
 ,{
   ________,
   ________,
   XXX__XX_,
   XXXX_XX_,
   XX_XXXX_,
   XX__XXX_,
   XX___XX_,
   ________}


 /*  inverted exclamation, 118 */

 ,{
   ___XX___,
   ________,
   ___XX___,
   ___XX___,
   __XXXX__,
   __XXXX__,
   ___XX___,
   ________}


 /*  inverted question mark, 119  */
 ,{
   __XX____,
   ________,
   __XX____,
   __XX____,
   _XX_____,
   XX___XX_,
   _XXXXX__,
   ________}


 /* capital accent ague, 120 */

 ,{
   ____XX__,
   ___X____,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* capital accent grave, 121 */
 ,{
   _XX_____,
   ___X____,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* capital accent circonflex, 122 */
 ,{
   __XXX___,
   _X___X__,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* capital umlaut, 123 */
 ,{
   XX___XX_,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* capital tilde, 124 */
 ,{
   _XXX__X_,
   X___XX__,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /*  cedilla, 125  */
 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ___X____}



/*  additional characters for complete ISO 8859-1 character set  */

/* Non breaking space, ISO-Code: 160, internal code: 126  */
 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* cent sign, ISO-Code: 162, internal code: 127  */
 ,{
   ________,
   ___X____,
   _XXXXX__,
   XX_X____,
   XX_X____,
   XX_X_XX_,
   _XXXXX__,
   ___X____}  /* char 'c'  */


 /* pound sterling, ISO-Code: 163, internal code: 128  */
 ,{
   ___XXX__,
   __XX____,
   __XX____,
   _XXXX___,
   __XX____,
   __XX__X_,
   _X_XXX__,
   ________}


 /* general currency sign, ISO-Code: 164, internal code: 129  */
 ,{
   ________,
   ________,
   _X___X__,
   __XXX___,
   __X_X___,
   __XXX___,
   _X___X__,
   ________}


 /* yen sign, ISO-Code: 165, internal code: 130  */
 ,{
   _X___X__,
   __X_X___,
   _XXXXX__,
   ___X____,
   _XXXXX__,
   ___X____,
   ___X____,
   ________}



 /* broken vertical bar, ISO-Code: 166, internal code: 131  */
 ,{
   __XX____,
   __XX____,
   __XX____,
   ________,
   __XX____,
   __XX____,
   __XX____,
   ________}


 /* section sign, ISO-Code: 167, internal code: 132  */
 ,{
   __XXX___,
   _X______,
   __XX____,
   _X__X___,
   __XX____,
   ____X___,
   _XXX____,
   ________}


 /* umlaut (dieresis), ISO-Code: 168, internal code: 133  */
 ,{
   XX___XX_,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* copyright, ISO-Code: 169, internal code: 134  */
 ,{
   _XXXXXX_,
   _X____X_,
   _X_XX_X_,
   _X_XXXX_,
   _X_XX_X_,
   _X____X_,
   _XXXXXX_,
   ________}


 /* feminine ordinal, ISO-Code: 170, internal code: 135  */
 ,{
   __XXX___,
   _____X__,
   __XXXX__,
   _X___X__,
   __XXX___,
   ________,
   ________,
   ________}


 /* left angle quote, ISO-Code: 172, internal code: 136  */
 ,{
   ________,
   __XX_XX_,
   _XX_XX__,
   XX_XX___,
   _XX_XX__,
   __XX_XX_,
   ________,
   ________}


 /* not sign, ISO-Code: 173, internal code: 137  */
 ,{
   ________,
   ________,
   ________,
   _XXXXX__,
   _____X__,
   _____X__,
   ________,
   ________}


 /* soft hyphen, ISO-Code: 173, internal code: 138  */
 ,{
   ________,
   ________,
   ________,
   _XXXXX__,
   ________,
   ________,
   ________,
   ________}


 /* rgistered trademark, ISO-Code: 174, internal code: 139  */
 ,{
   _XXXXX__,
   _X___X__,
   _X_X_X__,
   _X___X__,
   _X__XX__,
   _X_X_X__,
   _XXXXX__,
   ________}


 /* macron accent, ISO-Code: 175, internal code: 140  */
 ,{
   _XXXXX__,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* degree sign, ISO-Code: 176, internal code: 141  */
 ,{
   __XX____,
   _X__X___,
   __XX____,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* plus or minus, ISO-Code: 177, internal code: 142  */
 ,{
   ___X____,
   ___X____,
   _XXXXX__,
   ___X____,
   ___X____,
   ________,
   _XXXXX__,
   ________}


 /* superscript two, ISO-Code: 178, internal code: 143  */
 ,{
   _XX_____,
   X__X____,
   __X_____,
   _X______,
   XXXX____,
   ________,
   ________,
   ________}


 /* superscript three, ISO-Code: 179, internal code: 144  */
 ,{
   XXX_____,
   ___X____,
   _XX_____,
   ___X____,
   XXX_____,
   ________,
   ________,
   ________}


 /* acute accent, ISO-Code: 180, internal code: 145  */
 ,{
   ____XXX_,
   ___XX___,
   __X_____,
   ________,
   ________,
   ________,
   ________,
   ________}


 /* micro sign, ISO-Code: 181, internal code: 146  */
 ,{
   ________,
   ________,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   _XXXXX__,
   XX______}


 /* paragraph sign, ISO-Code: 182, internal code: 147  */
 ,{
   _XXXXXX_,
   XX_X_X__,
   XX_X_X__,
   _XXX_X__,
   ___X_X__,
   ___X_X__,
   __XXXXX_,
   ________}


 /* middle dot, ISO-Code: 183, internal code: 148  */
 ,{
   ________,
   ________,
   ________,
   ___XX___,
   ___XX___,
   ________,
   ________,
   ________}


 /* superscript one, ISO-Code: 185, internal code: 149  */
 ,{
   _X______,
   XX______,
   _X______,
   _X______,
   XXX_____,
   ________,
   ________,
   ________}


 /* masculine ordinal, ISO-Code: 186, internal code: 150  */
 ,{
   __XXXX__,
   _XX__XX_,
   _XX__XX_,
   _XX__XX_,
   __XXXX__,
   ________,
   ________,
   ________}


 /* right angle quote, ISO-Code: 187, internal code: 151  */
 ,{
   ________,
   XX_XX___,
   _XX_XX__,
   __XX_XX_,
   _XX_XX__,
   XX_XX___,
   ________,
   ________}


 /* fraction one-fourth, ISO-Code: 188, internal code: 152  */
 ,{
   X____X__,
   X___X___,
   X__X____,
   X_X__X__,
   _X__XX__,
   X__X_X__,
   ___XXXX_,
   _____X__}


 /* fraction one-half, ISO-Code: 189, internal code: 153  */
 ,{
   X____X__,
   X___X___,
   X__X____,
   X_X_XX__,
   _X_X__X_,
   X____X__,
   ____X___,
   ___XXXX_}


 /* fraction three-fourth, ISO-Code: 190, internal code: 154  */
 ,{
   XX______,
   __X_____,
   _X______,
   __X__X__,
   XX__XX__,
   ___X_X__,
   ___XXXX_,
   _____X__}


 /* multiply sign, ISO-Code: 215, internal code: 155  */
 ,{
   ________,
   _XX__XX_,
   __XXXX__,
   ___XX___,
   __XXXX__,
   _XX__XX_,
   ________,
   ________}


 /* division sign, ISO-Code: 247, internal code: 156  */
 ,{
   ________,
   ___XX___,
   ________,
   _XXXXXX_,
   ________,
   ___XX___,
   ________,
   ________}


 /* left arrow, ISO-Code: ---, internal code: 157  */
 ,{
   ___X____,
   __XX____,
   _XXX____,
   XXXXXX__,
   _XXX____,
   __XX____,
   ___X____,
   ________}

 /* right arrow, ISO-Code: ---, internal code: 158  */
 ,{
   __X_____,
   __XX____,
   __XXX___,
   XXXXXX__,
   __XXX___,
   __XX____,
   __X_____,
   ________}

 /* up arrow, ISO-Code: ---, internal code: 159 */
 ,{
   ________,
   __X_____,
   _XXX____,
   XXXXX___,
   __X_____,
   __X_____,
   ________,
   ________}

 /* down arrow, ISO-Code: ---, internal code: 160  */
 ,{
   ________,
   __X_____,
   __X_____,
   XXXXX___,
   _XXX____,
   __X_____,
   ________,
   ________}

 /* ENTER character, ISO-Code: ---, internal code: 162  */
 ,{
   ________,
   ____X___,
   __X_X___,
   _XX_X___,
   XXXXX___,
   _XX_____,
   __X_____,
   ________}

 /* ENTER character, ISO-Code: ---, internal code: 162  */
 ,{
   _____XX_,
   _____XX_,
   _____XX_,
   ____XX__,
   X___XX__,
   XX_XX___,
   _XXXX___,
   __XX____}


};


GUI_CONST_STORAGE GUI_FONT_TRANSLIST GUI_F8x8_TransList[] = {
/*
   The folowing are extensions to ISO 8859-1.
   Since ISO 8859-1 does not define any characters for the codes
   128 - 159, this area can be used by an application.
   The most commonly used symbols in embedded applications are
   therefor inserted here.
*/
  {CODE_ARROW_LEFT,-1},			/* 144, arrow left */
  {CODE_ARROW_RIGHT,-1},		/* 145, arrow right */
  {CODE_ARROW_UP,-1},			/* 146, arrow up */
  {CODE_ARROW_DOWN,-1},			/* 147, arrow down */
  {CODE_ENTER,-1},                      /* 148, enter symbol */
  {CODE_CHECKMARK,-1},			/* 149, checkmark symbol */
  {-1,-1},				/* 150, unused symbol */
  {-1,-1},				/* 151, unused symbol */
  {-1,-1},				/* 152, unused symbol */
  {-1,-1},				/* 153, unused symbol */
  {-1,-1},				/* 154, unused symbol */
  {-1,-1},				/* 155, unused symbol */
  {-1,-1},				/* 156, unused symbol */
  {-1,-1},				/* 157, unused symbol */
  {-1,-1},				/* 158, unused symbol */
  {-1,-1},				/* 159, unused symbol */
/* starting at character code 160 are the characters defined
   by ISO 8859-1
*/
  {CODE_NB_SPACE,-1},                   /* 160, non-breaking space */
  {CODE_INVEXCLAM,-1},                  /* 161, inverted exclamation sign */
  {CODE_CENT,-1},                       /* 162, cent sign */
  {CODE_POUND,-1},                      /* 163, pound sterling */
  {CODE_CURRENCY,-1},                   /* 164, general currency sign */
  {CODE_YEN,-1},                        /* 165, yen sign */
  {CODE_BROKEN_BAR,-1},                 /* 166, broken vertical bar */
  {CODE_SECTION,-1},                    /* 167, section sign */
  {CODE_DIERESIS,-1},                   /* 168, umlaut */
  {CODE_COPYRIGHT,-1},                  /* 169, copyright */
  {CODE_FEMININE,-1},                   /* 170,  */
  {CODE_LEFT_QUOTE,-1},                 /* 171,  */
  {CODE_NOT,-1},                        /* 172,  */
  {CODE_HYPHEN,-1},                     /* 173,  */
  {CODE_TRADEMARK,-1},                  /* 174,  */
  {CODE_MACRON,-1},                     /* 175,  */
  {CODE_DEGREE,-1},                     /* 176,  */
  {CODE_PLUS_MINUS,-1},                 /* 177,  */
  {CODE_SUPER_TWO,-1},                  /* 178,  */
  {CODE_SUPER_THREE,-1},                /* 179,  */
  {CODE_ACUTE,-1},                      /* 180,  */
  {CODE_MICRO,-1},                      /* 181,  */
  {CODE_PARAGRAPH,-1},                  /* 182,  */
  {CODE_MIDDLE_DOT,-1},                 /* 183,  */
  {CODE_CEDILLA,-1},                    /* 184,  */
  {CODE_SUPER_ONE,-1},                  /* 185,  */
  {CODE_MASCULINE,-1},                  /* 186,  */
  {CODE_RIGHT_QUOTE,-1},                /* 187,  */
  {CODE_ONE_FOURTH,-1},                 /* 188,  */
  {CODE_ONE_HALF,-1},                   /* 189,  */
  {CODE_THREE_FOURTH,-1},               /* 190,  */
  {CODE_INVQUEST,-1},                   /* 191,  */
  {CODE_LITTLE_A,CODE_CACCGRAV},        /* 192,  */
  {CODE_LITTLE_A,CODE_CACCAGUE},        /* 193,  */
  {CODE_LITTLE_A,CODE_CACCCIRC},        /* 194,  */
  {CODE_LITTLE_A,CODE_CTILDE},          /* 195,  */
  {CODE_LITTLE_A,CODE_CUMLAUT},         /* 196,  */
  {CODE_A_RING,-1},                     /* 197,  */
  {CODE_AE,-1},                         /* 198,  */
  {'C'-32,CODE_CEDILLA},                /* 199,  */
  {CODE_LITTLE_E,CODE_CACCGRAV},        /* 200,  */
  {CODE_LITTLE_E,CODE_CACCAGUE},        /* 201,  */
  {CODE_LITTLE_E,CODE_CACCCIRC},        /* 202,  */
  {CODE_LITTLE_E,CODE_CUMLAUT},         /* 203,  */
  {CODE_LITTLE_I,CODE_CACCGRAV},        /* 204,  */
  {CODE_LITTLE_I,CODE_CACCAGUE},        /* 205,  */
  {CODE_LITTLE_I,CODE_CACCCIRC},        /* 206,  */
  {CODE_LITTLE_I,CODE_CUMLAUT},         /* 207,  */
  {CODE_ETH,-1},                        /* 208,  */
  {CODE_LITTLE_N,CODE_CTILDE},          /* 209,  */
  {CODE_LITTLE_O,CODE_CACCGRAV},        /* 210,  */
  {CODE_LITTLE_O,CODE_CACCAGUE},        /* 211,  */
  {CODE_LITTLE_O,CODE_CACCCIRC},        /* 212,  */
  {CODE_LITTLE_O,CODE_CTILDE},          /* 213,  */
  {CODE_LITTLE_O,CODE_CUMLAUT},         /* 214,  */
  {CODE_MULTIPLY,-1},                   /* 215,  */
  {CODE_OSLASH,-1},                     /* 216,  */
  {CODE_LITTLE_U,CODE_CACCGRAV},        /* 217,  */
  {CODE_LITTLE_U,CODE_CACCAGUE},        /* 218,  */
  {CODE_LITTLE_U,CODE_CACCCIRC},        /* 219,  */
  {CODE_LITTLE_U,CODE_CUMLAUT},         /* 220,  */
  {'Y'-32,CODE_CACCAGUE},               /* 221,  */
  {CODE_THORN,-1},                      /* 222,  */
  {CODE_SHARPS,-1},                     /* 223,  */
  {'a'-32,CODE_SACCGRAV},               /* 224,  */
  {'a'-32,CODE_SACCAGUE},               /* 225,  */
  {'a'-32,CODE_SACCCIRC},               /* 226,  */
  {'a'-32,CODE_STILDE},                 /* 227,  */
  {'a'-32,CODE_SUMLAUT},                /* 228,  */
  {CODE_SA_RING,-1},                    /* 229,  */
  {CODE_SMALLAE,-1},                    /* 230,  */
  {'c'-32,CODE_CEDILLA},                /* 231,  */
  {'e'-32,CODE_SACCGRAV},               /* 232,  */
  {'e'-32,CODE_SACCAGUE},               /* 233,  */
  {'e'-32,CODE_SACCCIRC},               /* 234,  */
  {'e'-32,CODE_SUMLAUT},                /* 235,  */
  {CODE_I_NOPOINT,CODE_SACCGRAV},       /* 236,  */
  {CODE_I_NOPOINT,CODE_SACCAGUE},       /* 237,  */
  {CODE_I_NOPOINT,CODE_SACCCIRC},       /* 238,  */
  {CODE_I_NOPOINT,CODE_SUMLAUT},        /* 239,  */
  {CODE_SMALLETH,-1},                   /* 240, small eth, Icelandic */
  {'n'-32,CODE_STILDE},                 /* 241, small n, tilde */
  {'o'-32,CODE_SACCGRAV},               /* 242, small o, grave accent */
  {'o'-32,CODE_SACCAGUE},               /* 243, small o, acute accent */
  {'o'-32,CODE_SACCCIRC},               /* 244, small o, circumflex  */
  {'o'-32,CODE_STILDE},                 /* 245, small o, tilde  */
  {'o'-32,CODE_SUMLAUT},                /* 246, small o, umlaut  */
  {CODE_DIVISION,-1},                   /* 247, division sign */
  {CODE_SOSLASH,-1},                    /* 248, small o slash */
  {'u'-32,CODE_SACCAGUE},               /* 249,  */
  {'u'-32,CODE_SACCGRAV},               /* 250,  */
  {'u'-32,CODE_SACCCIRC},               /* 251,  */
  {'u'-32,CODE_SUMLAUT},                /* 252, small u, umlaut  */
  {'y'-32,CODE_SACCAGUE},               /* 253, small y, acute accent */
  {CODE_SMALLTHORN,-1},                 /* 254, small thorn, Icelandic  */
  {'y'-32,CODE_SUMLAUT},                /* 255, */
};

GUI_CONST_STORAGE GUI_FONT_TRANSINFO GUI_F8x8_TransInfo = {
  144                   /*  FirstChar  */
  ,255                  /*  LastChar   */
  ,GUI_F8x8_TransList   /*  const GUI_FONT_TRANSLIST* pList */
};

GUI_CONST_STORAGE GUI_FONT_MONO GUI_F8x8_Mono = {
 GUI_F8x8_acFont[0],
 GUI_F8x8_acFont[0],
 &GUI_F8x8_TransInfo,
 32,                    /* FirstChar */
 127,                   /* LastChar */
 8,                     /* XSize */
 8,                     /* XDist */
 1                      /* BytesPerLine */
};
  
GUI_CONST_STORAGE GUI_FONT GUI_Font8x8 = { 
  GUI_FONTTYPE_MONO
  ,8
  ,8
  ,1
  ,1
  ,{&GUI_F8x8_Mono}
  , 7, 5, 7
};

GUI_CONST_STORAGE GUI_FONT GUI_Font8x9 = { 
  GUI_FONTTYPE_MONO
  ,8
  ,9
  ,1
  ,1
  ,{&GUI_F8x8_Mono}
  , 7, 5, 7 };
