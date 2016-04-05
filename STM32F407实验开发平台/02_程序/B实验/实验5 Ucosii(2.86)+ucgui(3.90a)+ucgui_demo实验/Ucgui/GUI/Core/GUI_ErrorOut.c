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
File        : GUI_ErrorOut.C
Purpose     : Logging (used only at higher debug levels)
---------------------------END-OF-HEADER------------------------------
*/

#include <stdio.h>
#include <string.h>
#include "GUI_Protected.h"
#include "GUI_X.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define MAXLEN 50

/*********************************************************************
*
*      Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _CopyString
*/
static void _CopyString(char*d, const char*s, int MaxLen) {
  while ((MaxLen > 0) && *s) {
    *d++ = *s++;
    MaxLen--;
  }
  *d = 0;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_ErrorOut
*/
void GUI_ErrorOut(const char *s) { GUI_X_ErrorOut(s); }

/*********************************************************************
*
*       GUI_ErrorOut1
*/
void GUI_ErrorOut1(const char *s, int p0) {
  char ac[MAXLEN + 10];
  char* sOut = ac;
  GUI_MEMSET((U8*)ac, 0, sizeof(ac));
  _CopyString(ac, s, MAXLEN);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI_ErrorOut(ac);
}

/*********************************************************************
*
*       GUI_ErrorOut2
*/
void GUI_ErrorOut2(const char *s, int p0, int p1) {
  char ac[MAXLEN + 20];
  char* sOut = ac;
  GUI_MEMSET((U8*)ac, 0, sizeof(ac));
  _CopyString(ac, s, MAXLEN);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI__AddSpaceHex(p1, 8, &sOut);
  GUI_ErrorOut(ac);
}

/*********************************************************************
*
*       GUI_ErrorOut3
*/
void GUI_ErrorOut3(const char *s, int p0, int p1, int p2) {
  char ac[MAXLEN + 30];
  char* sOut = ac;
  GUI_MEMSET((U8*)ac, 0, sizeof(ac));
  _CopyString(ac, s, MAXLEN);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI__AddSpaceHex(p1, 8, &sOut);
  GUI__AddSpaceHex(p2, 8, &sOut);
  GUI_ErrorOut(ac);
}

/*********************************************************************
*
*       GUI_ErrorOut4
*/
void GUI_ErrorOut4(const char *s, int p0, int p1, int p2, int p3) {
  char ac[MAXLEN + 40] = {0};
  char* sOut = ac;
  GUI_MEMSET((U8*)ac, 0, sizeof(ac));
  _CopyString(ac, s, MAXLEN);
  sOut += strlen(sOut);
  GUI__AddSpaceHex(p0, 8, &sOut);
  GUI__AddSpaceHex(p1, 8, &sOut);
  GUI__AddSpaceHex(p2, 8, &sOut);
  GUI__AddSpaceHex(p3, 8, &sOut);
  GUI_ErrorOut(ac);
}

/*************************** End of file ****************************/
