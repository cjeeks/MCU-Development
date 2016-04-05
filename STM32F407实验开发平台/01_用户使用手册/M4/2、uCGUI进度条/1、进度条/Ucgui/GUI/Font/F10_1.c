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
File        : F10_1.C
Purpose     : ISO 8859-1 West European Character Set similar to Swiss
Height      : 10
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI_FontIntern.h"


/* The character codes 0x80 - 0x9f are not part of the
   ISO 8859 extensions. If needed them you can include them
   by using a modifyed copy of this file.
*/

#if 0

GUI_CONST_STORAGE unsigned char acFont10_1_128[10] = { /* code 128 */
  ________,
  __XXXX__,
  _X______,
  XXXXXX__,
  _X______,
  XXXXXX__,
  _X______,
  __X_____,
  ___XXX__,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_129[10] = { /* code 129 */
  ________,
  _XXXXXX_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _XXXXXX_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_130[10] = { /* code 130 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont10_1_131[10] = { /* code 131 */
  ________,
  ___XX___,
  __X_____,
  _XXX____,
  __X_____,
  __X_____,
  __X_____,
  _X______,
  _X______,
  XX______};

GUI_CONST_STORAGE unsigned char acFont10_1_132[10] = { /* code 132 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  X_X_____,
  X_X_____};

GUI_CONST_STORAGE unsigned char acFont10_1_133[20] = { /* code 133 */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  _X__X__X,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_134[10] = { /* code 134 */
  ________,
  __X_____,
  __X_____,
  XXXXX___,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont10_1_135[10] = { /* code 135 */
  ________,
  __X_____,
  __X_____,
  XXXXX___,
  __X_____,
  __X_____,
  __X_____,
  __X_____,
  XXXXX___,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont10_1_136[10] = { /* code 136 */
  ________,
  __X_____,
  _X_X____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_137[20] = { /* code 137 */
  ________,________,
  _X__X___,________,
  X_X_X___,________,
  X_X_X___,________,
  _X_X____,________,
  ___X_X__,_X______,
  __X_X_X_,X_X_____,
  __X_X_X_,X_X_____,
  __X__X__,_X______,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_138[10] = { /* code 138 */
  _X_X____,
  __X_____,
  _XXXXX__,
  X____X__,
  X_______,
  _XXXX___,
  _____X__,
  X____X__,
  _XXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_139[10] = { /* code 139 */
  ________,
  ________,
  ________,
  ________,
  __X_____,
  _X______,
  X_______,
  _X______,
  __X_____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_140[20] = { /* code 140 */
  ________,________,
  _XXX_XXX,XX______,
  X___XX__,________,
  X____X__,________,
  X____XXX,XX______,
  X____X__,________,
  X____X__,________,
  X___XX__,________,
  _XXX_XXX,XX______,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_141[10] = { /* code 141 */
  ________,
  _XXXXXX_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _XXXXXX_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_142[10] = { /* code 142 */
  __X_X___,
  ___X____,
  XXXXXX__,
  _____X__,
  ___XX___,
  __X_____,
  _X______,
  X_______,
  XXXXXX__,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_143[10] = { /* code 143 */
  ________,
  _XXXXXX_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _XXXXXX_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_144[10] = { /* code 144 */
  ________,
  _XXXXXX_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _XXXXXX_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_145[10] = { /* code 145 */
  ________,
  X_______,
  X_______,
  X_______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_146[10] = { /* code 146 */
  ________,
  X_______,
  X_______,
  X_______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_147[10] = { /* code 147 */
  ________,
  X_X_____,
  X_X_____,
  X_X_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_148[10] = { /* code 148 */
  ________,
  X_X_____,
  X_X_____,
  X_X_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_149[10] = { /* code 149 */
  ________,
  ________,
  ________,
  XXX_____,
  XXX_____,
  XXX_____,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_150[10] = { /* code 150 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXXXXX__,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_151[20] = { /* code 151 */
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  XXXXXXXX,XXX_____,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_152[10] = { /* code 152 */
  ________,
  _X_X____,
  X_X_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_153[20] = { /* code 153 */
  ________,________,
  XXX_X___,X_______,
  _X__XX_X,X_______,
  _X__XX_X,X_______,
  _X__X_X_,X_______,
  ________,________,
  ________,________,
  ________,________,
  ________,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_154[10] = { /* code 154 */
  _X_X____,
  __X_____,
  ________,
  _XXX____,
  X___X___,
  _XX_____,
  ___X____,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_155[10] = { /* code 155 */
  ________,
  ________,
  ________,
  ________,
  X_______,
  _X______,
  __X_____,
  _X______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_156[20] = { /* code 156 */
  ________,________,
  ________,________,
  ________,________,
  _XXX_XXX,________,
  X___X___,X_______,
  X___XXXX,X_______,
  X___X___,________,
  X___X___,X_______,
  _XXX_XXX,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_157[10] = { /* code 157 */
  ________,
  _XXXXXX_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _X____X_,
  _XXXXXX_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_158[10] = { /* code 158 */
  _X_X____,
  __X_____,
  ________,
  XXXXX___,
  ___X____,
  __X_____,
  __X_____,
  _X______,
  XXXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_159[10] = { /* code 159 */
  __X_X___,
  X_____X_,
  _X___X__,
  _X___X__,
  __X_X___,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ________};

#endif

GUI_CONST_STORAGE unsigned char acFont10_1_160[10] = { /* code 160 */
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

GUI_CONST_STORAGE unsigned char acFont10_1_161[10] = { /* code 161 */
  ________,
  ________,
  ________,
  X_______,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont10_1_162[10] = { /* code 162 */
  ________,
  ___X____,
  ___X____,
  _XXX____,
  X_X_X___,
  X_X_____,
  X_X_____,
  X_X_X___,
  _XXX____,
  _X______};

GUI_CONST_STORAGE unsigned char acFont10_1_163[10] = { /* code 163 */
  ________,
  __XX____,
  _X__X___,
  _X______,
  _X______,
  XXX_____,
  _X______,
  _XX_____,
  X__XX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_164[10] = { /* code 164 */
  ________,
  ________,
  X____X__,
  _XXXX___,
  _X__X___,
  _X__X___,
  _XXXX___,
  X____X__,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_165[10] = { /* code 165 */
  ________,
  X___X___,
  X___X___,
  _X_X____,
  _X_X____,
  XXXXX___,
  __X_____,
  XXXXX___,
  __X_____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_166[10] = { /* code 166 */
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  ________,
  ________,
  X_______,
  X_______,
  X_______};

GUI_CONST_STORAGE unsigned char acFont10_1_167[10] = { /* code 167 */
  ________,
  _XXX____,
  X___X___,
  _X______,
  XXX_____,
  X__X____,
  _X__X___,
  __X_X___,
  ___X____,
  X___X___};

GUI_CONST_STORAGE unsigned char acFont10_1_168[10] = { /* code 168 */
  ________,
  X_X_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_169[10] = { /* code 169 */
  ________,
  __XXXX__,
  _X____X_,
  X__XXX_X,
  X_X____X,
  X_X____X,
  X__XXX_X,
  _X____X_,
  __XXXX__,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_170[10] = { /* code 170 */
  ________,
  XXX_____,
  __X_____,
  XXX_____,
  XXX_____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_171[10] = { /* code 171 */
  ________,
  ________,
  ________,
  ________,
  __X_X___,
  _X_X____,
  X_X_____,
  _X_X____,
  __X_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_172[10] = { /* code 172 */
  ________,
  ________,
  ________,
  ________,
  XXXXX___,
  ____X___,
  ____X___,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_173[10] = { /* code 173 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  XXX_____,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_174[10] = { /* code 174 */
  ________,
  __XXXX__,
  _X____X_,
  X_XXX__X,
  X_X__X_X,
  X_XXX__X,
  X_X__X_X,
  _X____X_,
  __XXXX__,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_175[10] = { /* code 175 */
  XXXXXX__,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_176[10] = { /* code 176 */
  ________,
  XXX_____,
  X_X_____,
  XXX_____,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_177[10] = { /* code 177 */
  ________,
  ________,
  __X_____,
  __X_____,
  XXXXX___,
  __X_____,
  __X_____,
  ________,
  XXXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_178[10] = { /* code 178 */
  ________,
  XXX_____,
  __X_____,
  _X______,
  XXX_____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_179[10] = { /* code 179 */
  ________,
  XXX_____,
  _X______,
  __X_____,
  XXX_____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_180[10] = { /* code 180 */
  ________,
  __X_____,
  _X______,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_181[10] = { /* code 181 */
  ________,
  ________,
  ________,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  XXXXX___,
  X_______};

GUI_CONST_STORAGE unsigned char acFont10_1_182[10] = { /* code 182 */
  ________,
  _XXXXX__,
  XXX_X___,
  XXX_X___,
  _XX_X___,
  __X_X___,
  __X_X___,
  __X_X___,
  __X_X___,
  __X_X___};

GUI_CONST_STORAGE unsigned char acFont10_1_183[10] = { /* code 183 */
  ________,
  ________,
  ________,
  ________,
  ________,
  X_______,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_184[10] = { /* code 184 */
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  ________,
  _X______,
  __X_____};

GUI_CONST_STORAGE unsigned char acFont10_1_185[10] = { /* code 185 */
  ________,
  __X_____,
  _XX_____,
  __X_____,
  __X_____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_186[10] = { /* code 186 */
  ________,
  _XX_____,
  X__X____,
  X__X____,
  _XX_____,
  ________,
  ________,
  ________,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_187[10] = { /* code 187 */
  ________,
  ________,
  ________,
  ________,
  X_X_____,
  _X_X____,
  __X_X___,
  _X_X____,
  X_X_____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_188[20] = { /* code 188 */
  ________,________,
  _X____X_,________,
  XX___X__,________,
  _X__X___,________,
  _X__X___,________,
  ___X__X_,________,
  ___X_XX_,________,
  __X_XXXX,________,
  _X____X_,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_189[20] = { /* code 189 */
  ________,________,
  __X____X,________,
  _XX___X_,________,
  __X__X__,________,
  __X_X___,________,
  ____X_XX,X_______,
  ___X____,X_______,
  __X____X,________,
  __X___XX,X_______,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_190[20] = { /* code 190 */
  ________,________,
  XXX____X,________,
  _X____X_,________,
  __X__X__,________,
  XXX__X__,________,
  ____X__X,________,
  ___X__XX,________,
  __X__XXX,X_______,
  __X____X,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_191[10] = { /* code 191 */
  ________,
  ________,
  __X_____,
  ________,
  __X_____,
  __X_____,
  _X______,
  X_______,
  X___X___,
  _XXX____};

GUI_CONST_STORAGE unsigned char acFont10_1_192[10] = { /* code 192 */
  __X_____,
  ___X____,
  __XXX___,
  __X_X___,
  __X_X___,
  _X___X__,
  _XXXXX__,
  X_____X_,
  X_____X_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_193[10] = { /* code 193 */
  ____X___,
  ___X____,
  __XXX___,
  __X_X___,
  __X_X___,
  _X___X__,
  _XXXXX__,
  X_____X_,
  X_____X_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_194[10] = { /* code 194 */
  ___X____,
  __X_X___,
  __XXX___,
  __X_X___,
  __X_X___,
  _X___X__,
  _XXXXX__,
  X_____X_,
  X_____X_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_195[10] = { /* code 195 */
  ___X_X__,
  __X_X___,
  __XXX___,
  __X_X___,
  __X_X___,
  _X___X__,
  _XXXXX__,
  X_____X_,
  X_____X_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_196[10] = { /* code 196 */
  __X_X___,
  ________,
  __XXX___,
  __X_X___,
  __X_X___,
  _X___X__,
  _XXXXX__,
  X_____X_,
  X_____X_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_197[10] = { /* code 197 */
  __XXX___,
  __X_X___,
  __XXX___,
  __X_X___,
  __X_X___,
  _X___X__,
  _XXXXX__,
  X_____X_,
  X_____X_,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_198[20] = { /* code 198 */
  ________,________,
  ___XXXXX,XX______,
  ___X_X__,________,
  __X__X__,________,
  __X__XXX,XX______,
  _X___X__,________,
  _XXXXX__,________,
  X____X__,________,
  X____XXX,XX______,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_199[10] = { /* code 199 */
  ________,
  __XXX___,
  _X___X__,
  X_______,
  X_______,
  X_______,
  _X___X__,
  __XXXX__,
  ___X____,
  ____X___};

GUI_CONST_STORAGE unsigned char acFont10_1_200[10] = { /* code 200 */
  _X______,
  __X_____,
  XXXXX___,
  X_______,
  X_______,
  XXXXX___,
  X_______,
  X_______,
  XXXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_201[10] = { /* code 201 */
  ___X____,
  __X_____,
  XXXXX___,
  X_______,
  X_______,
  XXXXX___,
  X_______,
  X_______,
  XXXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_202[10] = { /* code 202 */
  __X_____,
  _X_X____,
  XXXXX___,
  X_______,
  X_______,
  XXXXX___,
  X_______,
  X_______,
  XXXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_203[10] = { /* code 203 */
  _X_X____,
  ________,
  XXXXX___,
  X_______,
  X_______,
  XXXXX___,
  X_______,
  X_______,
  XXXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_204[10] = { /* code 204 */
  X_______,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_205[10] = { /* code 205 */
  _X______,
  X_______,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_206[10] = { /* code 206 */
  X_______,
  _X______,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_207[10] = { /* code 207 */
  _X______,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_208[10] = { /* code 208 */
  ________,
  _XXXX___,
  _X___X__,
  _X____X_,
  XXXX__X_,
  _X____X_,
  _X____X_,
  _X___X__,
  _XXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_209[10] = { /* code 209 */
  _X_X____,
  X____X__,
  XX___X__,
  X_X__X__,
  X_X__X__,
  X__X_X__,
  X__X_X__,
  X___XX__,
  X____X__,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_210[10] = { /* code 210 */
  __X_____,
  ___X____,
  __XXX___,
  _X___X__,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___X__,
  __XXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_211[10] = { /* code 211 */
  ____X___,
  ___X____,
  __XXX___,
  _X___X__,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___X__,
  __XXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_212[10] = { /* code 212 */
  ___X____,
  __X_X___,
  __XXX___,
  _X___X__,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___X__,
  __XXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_213[10] = { /* code 213 */
  ___X_X__,
  __X_X___,
  __XXX___,
  _X___X__,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___X__,
  __XXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_214[10] = { /* code 214 */
  __X_X___,
  ________,
  __XXX___,
  _X___X__,
  X_____X_,
  X_____X_,
  X_____X_,
  _X___X__,
  __XXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_215[10] = { /* code 215 */
  ________,
  ________,
  ________,
  X___X___,
  _X_X____,
  __X_____,
  _X_X____,
  X___X___,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_216[10] = { /* code 216 */
  ________,
  __XXX_X_,
  _X___XX_,
  X___X_X_,
  X__X__X_,
  X__X__X_,
  X_X___X_,
  _X___X__,
  X_XXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_217[10] = { /* code 217 */
  __X_____,
  ___X____,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_218[10] = { /* code 218 */
  ___X____,
  __X_____,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_219[10] = { /* code 219 */
  __X_____,
  _X_X____,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_220[10] = { /* code 220 */
  __X_X___,
  ________,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  X____X__,
  _XXXX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_221[10] = { /* code 221 */
  ____X___,
  X__X__X_,
  _X___X__,
  _X___X__,
  __X_X___,
  ___X____,
  ___X____,
  ___X____,
  ___X____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_222[10] = { /* code 222 */
  ________,
  X_______,
  X_______,
  XXXXX___,
  X____X__,
  X____X__,
  XXXXX___,
  X_______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_223[10] = { /* code 223 */
  ________,
  _XXX____,
  X___X___,
  X___X___,
  X__X____,
  X__XX___,
  X____X__,
  X_X__X__,
  X__XX___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_224[10] = { /* code 224 */
  __X_____,
  ___X____,
  ________,
  _XXX____,
  X___X___,
  _XXXX___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_225[10] = { /* code 225 */
  ___X____,
  __X_____,
  ________,
  _XXX____,
  X___X___,
  _XXXX___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_226[10] = { /* code 226 */
  __X_____,
  _X_X____,
  ________,
  _XXX____,
  X___X___,
  _XXXX___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_227[10] = { /* code 227 */
  __X_X___,
  _X_X____,
  ________,
  _XXX____,
  X___X___,
  _XXXX___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_228[10] = { /* code 228 */
  ________,
  _X_X____,
  ________,
  _XXX____,
  X___X___,
  _XXXX___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_229[10] = { /* code 229 */
  _XXX____,
  _X_X____,
  _XXX____,
  _XXX____,
  X___X___,
  _XXXX___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_230[20] = { /* code 230 */
  ________,________,
  ________,________,
  ________,________,
  _XXX_XXX,________,
  X___X___,X_______,
  _XXXXXXX,X_______,
  X___X___,________,
  X___X___,X_______,
  _XXX_XXX,________,
  ________,________};

GUI_CONST_STORAGE unsigned char acFont10_1_231[10] = { /* code 231 */
  ________,
  ________,
  ________,
  _XXX____,
  X___X___,
  X_______,
  X___X___,
  _XXX____,
  __X_____,
  ___X____};

GUI_CONST_STORAGE unsigned char acFont10_1_232[10] = { /* code 232 */
  _X______,
  __X_____,
  ________,
  _XXX____,
  X___X___,
  XXXXX___,
  X_______,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_233[10] = { /* code 233 */
  ___X____,
  __X_____,
  ________,
  _XXX____,
  X___X___,
  XXXXX___,
  X_______,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_234[10] = { /* code 234 */
  __X_____,
  _X_X____,
  ________,
  _XXX____,
  X___X___,
  XXXXX___,
  X_______,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_235[10] = { /* code 235 */
  ________,
  _X_X____,
  ________,
  _XXX____,
  X___X___,
  XXXXX___,
  X_______,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_236[10] = { /* code 236 */
  X_______,
  _X______,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_237[10] = { /* code 237 */
  _X______,
  X_______,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_238[10] = { /* code 238 */
  _X______,
  X_X_____,
  ________,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  _X______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_239[10] = { /* code 239 */
  ________,
  _X______,
  ________,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  X_______,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_240[10] = { /* code 240 */
  ________,
  __XXX___,
  _X_X____,
  ___X____,
  _XXXX___,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_241[10] = { /* code 241 */
  __X_X___,
  _X_X____,
  ________,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_242[10] = { /* code 242 */
  _X______,
  __X_____,
  ________,
  _XXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_243[10] = { /* code 243 */
  ___X____,
  __X_____,
  ________,
  _XXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_244[10] = { /* code 244 */
  __X_____,
  _X_X____,
  ________,
  _XXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_245[10] = { /* code 245 */
  __X_X___,
  _X_X____,
  ________,
  _XXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_246[10] = { /* code 246 */
  ________,
  _X_X____,
  ________,
  _XXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  _XXX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_247[10] = { /* code 247 */
  ________,
  ________,
  ________,
  __X_____,
  ________,
  XXXXX___,
  ________,
  __X_____,
  ________,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_248[10] = { /* code 248 */
  ________,
  ________,
  ________,
  _XX_X___,
  X__XX___,
  X_X_X___,
  X_X_X___,
  XX__X___,
  X_XX____,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_249[10] = { /* code 249 */
  _X______,
  __X_____,
  ________,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_250[10] = { /* code 250 */
  ___X____,
  __X_____,
  ________,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_251[10] = { /* code 251 */
  __X_____,
  _X_X____,
  ________,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_252[10] = { /* code 252 */
  ________,
  _X_X____,
  ________,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  X__XX___,
  _XX_X___,
  ________};

GUI_CONST_STORAGE unsigned char acFont10_1_253[10] = { /* code 253 */
  ___X____,
  __X_____,
  ________,
  X___X___,
  X___X___,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  _X______};

GUI_CONST_STORAGE unsigned char acFont10_1_254[10] = { /* code 254 */
  ________,
  X_______,
  X_______,
  XXXX____,
  X___X___,
  X___X___,
  X___X___,
  X___X___,
  XXXX____,
  X_______};

GUI_CONST_STORAGE unsigned char acFont10_1_255[10] = { /* code 255 */
  ________,
  _X_X____,
  ________,
  X___X___,
  X___X___,
  _X_X____,
  _X_X____,
  __X_____,
  __X_____,
  _X______};



GUI_CONST_STORAGE GUI_CHARINFO Font10_1_CharInfo[96] = {
   {   3,   3,  1, acFont10_1_160 } /* code 160 */
  ,{   2,   2,  1, acFont10_1_161 } /* code 161 */
  ,{   6,   6,  1, acFont10_1_162 } /* code 162 */
  ,{   6,   6,  1, acFont10_1_163 } /* code 163 */
  ,{   7,   7,  1, acFont10_1_164 } /* code 164 */
  ,{   6,   6,  1, acFont10_1_165 } /* code 165 */
  ,{   2,   2,  1, acFont10_1_166 } /* code 166 */
  ,{   6,   6,  1, acFont10_1_167 } /* code 167 */
  ,{   4,   4,  1, acFont10_1_168 } /* code 168 */
  ,{   8,   8,  1, acFont10_1_169 } /* code 169 */
  ,{   4,   4,  1, acFont10_1_170 } /* code 170 */
  ,{   6,   6,  1, acFont10_1_171 } /* code 171 */
  ,{   6,   6,  1, acFont10_1_172 } /* code 172 */
  ,{   4,   4,  1, acFont10_1_173 } /* code 173 */
  ,{   8,   8,  1, acFont10_1_174 } /* code 174 */
  ,{   6,   6,  1, acFont10_1_175 } /* code 175 */
  ,{   4,   4,  1, acFont10_1_176 } /* code 176 */
  ,{   6,   6,  1, acFont10_1_177 } /* code 177 */
  ,{   4,   4,  1, acFont10_1_178 } /* code 178 */
  ,{   4,   4,  1, acFont10_1_179 } /* code 179 */
  ,{   4,   4,  1, acFont10_1_180 } /* code 180 */
  ,{   6,   6,  1, acFont10_1_181 } /* code 181 */
  ,{   6,   6,  1, acFont10_1_182 } /* code 182 */
  ,{   3,   3,  1, acFont10_1_183 } /* code 183 */
  ,{   4,   4,  1, acFont10_1_184 } /* code 184 */
  ,{   4,   4,  1, acFont10_1_185 } /* code 185 */
  ,{   5,   5,  1, acFont10_1_186 } /* code 186 */
  ,{   6,   6,  1, acFont10_1_187 } /* code 187 */
  ,{   9,   9,  2, acFont10_1_188 } /* code 188 */
  ,{  10,  10,  2, acFont10_1_189 } /* code 189 */
  ,{  10,  10,  2, acFont10_1_190 } /* code 190 */
  ,{   6,   6,  1, acFont10_1_191 } /* code 191 */
  ,{   8,   8,  1, acFont10_1_192 } /* code 192 */
  ,{   8,   8,  1, acFont10_1_193 } /* code 193 */
  ,{   8,   8,  1, acFont10_1_194 } /* code 194 */
  ,{   8,   8,  1, acFont10_1_195 } /* code 195 */
  ,{   8,   8,  1, acFont10_1_196 } /* code 196 */
  ,{   8,   8,  1, acFont10_1_197 } /* code 197 */
  ,{  11,  11,  2, acFont10_1_198 } /* code 198 */
  ,{   7,   7,  1, acFont10_1_199 } /* code 199 */
  ,{   6,   6,  1, acFont10_1_200 } /* code 200 */
  ,{   6,   6,  1, acFont10_1_201 } /* code 201 */
  ,{   6,   6,  1, acFont10_1_202 } /* code 202 */
  ,{   6,   6,  1, acFont10_1_203 } /* code 203 */
  ,{   2,   2,  1, acFont10_1_204 } /* code 204 */
  ,{   2,   2,  1, acFont10_1_205 } /* code 205 */
  ,{   2,   2,  1, acFont10_1_206 } /* code 206 */
  ,{   2,   2,  1, acFont10_1_207 } /* code 207 */
  ,{   8,   8,  1, acFont10_1_208 } /* code 208 */
  ,{   7,   7,  1, acFont10_1_209 } /* code 209 */
  ,{   8,   8,  1, acFont10_1_210 } /* code 210 */
  ,{   8,   8,  1, acFont10_1_211 } /* code 211 */
  ,{   8,   8,  1, acFont10_1_212 } /* code 212 */
  ,{   8,   8,  1, acFont10_1_213 } /* code 213 */
  ,{   8,   8,  1, acFont10_1_214 } /* code 214 */
  ,{   6,   6,  1, acFont10_1_215 } /* code 215 */
  ,{   8,   8,  1, acFont10_1_216 } /* code 216 */
  ,{   7,   7,  1, acFont10_1_217 } /* code 217 */
  ,{   7,   7,  1, acFont10_1_218 } /* code 218 */
  ,{   7,   7,  1, acFont10_1_219 } /* code 219 */
  ,{   7,   7,  1, acFont10_1_220 } /* code 220 */
  ,{   8,   8,  1, acFont10_1_221 } /* code 221 */
  ,{   7,   7,  1, acFont10_1_222 } /* code 222 */
  ,{   7,   7,  1, acFont10_1_223 } /* code 223 */
  ,{   6,   6,  1, acFont10_1_224 } /* code 224 */
  ,{   6,   6,  1, acFont10_1_225 } /* code 225 */
  ,{   6,   6,  1, acFont10_1_226 } /* code 226 */
  ,{   6,   6,  1, acFont10_1_227 } /* code 227 */
  ,{   6,   6,  1, acFont10_1_228 } /* code 228 */
  ,{   6,   6,  1, acFont10_1_229 } /* code 229 */
  ,{  10,  10,  2, acFont10_1_230 } /* code 230 */
  ,{   6,   6,  1, acFont10_1_231 } /* code 231 */
  ,{   6,   6,  1, acFont10_1_232 } /* code 232 */
  ,{   6,   6,  1, acFont10_1_233 } /* code 233 */
  ,{   6,   6,  1, acFont10_1_234 } /* code 234 */
  ,{   6,   6,  1, acFont10_1_235 } /* code 235 */
  ,{   2,   2,  1, acFont10_1_236 } /* code 236 */
  ,{   2,   2,  1, acFont10_1_237 } /* code 237 */
  ,{   2,   2,  1, acFont10_1_238 } /* code 238 */
  ,{   2,   2,  1, acFont10_1_239 } /* code 239 */
  ,{   6,   6,  1, acFont10_1_240 } /* code 240 */
  ,{   6,   6,  1, acFont10_1_241 } /* code 241 */
  ,{   6,   6,  1, acFont10_1_242 } /* code 242 */
  ,{   6,   6,  1, acFont10_1_243 } /* code 243 */
  ,{   6,   6,  1, acFont10_1_244 } /* code 244 */
  ,{   6,   6,  1, acFont10_1_245 } /* code 245 */
  ,{   6,   6,  1, acFont10_1_246 } /* code 246 */
  ,{   6,   6,  1, acFont10_1_247 } /* code 247 */
  ,{   6,   6,  1, acFont10_1_248 } /* code 248 */
  ,{   6,   6,  1, acFont10_1_249 } /* code 249 */
  ,{   6,   6,  1, acFont10_1_250 } /* code 250 */
  ,{   6,   6,  1, acFont10_1_251 } /* code 251 */
  ,{   6,   6,  1, acFont10_1_252 } /* code 252 */
  ,{   6,   6,  1, acFont10_1_253 } /* code 253 */
  ,{   6,   6,  1, acFont10_1_254 } /* code 254 */
  ,{   6,   6,  1, acFont10_1_255 } /* code 255 */
};

GUI_CONST_STORAGE GUI_FONT_PROP Font10_1Prop1 = {
   160                            /* first character               */
  ,255                            /* last character                */
  ,&Font10_1_CharInfo[0]          /* address of first character    */
  ,&GUI_Font10ASCIIProp1          /* pointer to next GUI_FONT_PROP */
};

GUI_CONST_STORAGE GUI_FONT GUI_Font10_1 = {
   GUI_FONTTYPE_PROP              /* type of font    */
  ,10                             /* height of font  */
  ,10                             /* space of font y */
  ,1                              /* magnification x */
  ,1                              /* magnification y */
  ,{&Font10_1Prop1}
  ,9, 6, 8 
};

/*************************** End of file ****************************/
