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
File        : GUI__memset.c
Purpose     : Implementation of said function
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <string.h>           /* needed for definition of NULL */
#include "GUI_Protected.h"

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI__memset
*
* Purpose:
*  Replacement for the memset function. The advantage is high speed
*  on all systems (sometime up to 10 times as fast as the one
*  in the library)
*  Main idea is to write int-wise.
*/
void GUI__memset(U8* p, U8 Fill, int NumBytes) {
  int NumInts;
  /* Write bytes until we are done or have reached an int boundary */
  while (NumBytes && ((sizeof(int) - 1) & (U32)p)) {
    *p++ = Fill;
    NumBytes--;
  }
  /* Write Ints */
  NumInts = (unsigned)NumBytes / sizeof(int);
  if (NumInts) {
    int FillInt;
    int *pInt;
    NumBytes &= (sizeof(int) - 1);
    if (sizeof(int) == 2) {        /* May some compilers generate a warning at this line: Condition is alwaws true/false */
      FillInt = Fill * 0x101;      /* May some compilers generate a warning at this line: Unreachable code */
    } else if (sizeof(int) == 4) { /* May some compilers generate a warning at this line: Condition is alwaws true/false */
      FillInt = Fill * 0x1010101;  /* May some compilers generate a warning at this line: Unreachable code */
    }
    pInt = (int*)p;
    /* Fill large amount of data at a time */
    while (NumInts >= 4) { 
      *pInt++ = FillInt;
      *pInt++ = FillInt;
      *pInt++ = FillInt;
      *pInt++ = FillInt;
      NumInts -= 4;
    }
    /* Fill one int at a time */
    while (NumInts) {
      *pInt++ = FillInt;
      NumInts--;
    }
    p = (U8*)pInt;
  }
  /* Fill the remainder byte wise */
  while (NumBytes) {
    *p++ = Fill;
    NumBytes--;
  }
}

/*************************** End of file ****************************/
