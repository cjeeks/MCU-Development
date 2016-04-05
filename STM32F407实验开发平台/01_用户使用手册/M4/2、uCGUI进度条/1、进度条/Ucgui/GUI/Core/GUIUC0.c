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
File        : GUIUC0.C
Purpose     : Implementation of character and string services
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI.h"
 
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_UC2DB
*
* Purpose:
*   Convert Convert UNICODE 16-bit value into double byte version
*   - Byte0: First byte, msb
*   - Byte1: Last  byte, lsb
*/
void GUI_UC2DB(U16 Code, U8* pOut) {
/* move regular ASCII to (unused) 0xE000-0xE0ff area */
  if (Code < 0x100) {
    if (Code !=0)  /* end marker ? */
      Code += 0xe000;
  } else {
/* If Low byte 0: Move to (unused) 0xE100-0xE1ff area */
    if ((Code&0xff) == 0) {
      Code = (Code>>8) +0xe100;
    }
  }
/* Convert into double byte, putting msb first*/
  *pOut++ = Code >> 8;     /* Save msb first */
  *pOut   = Code & 0xff;
}

/*********************************************************************
*
*       GUI_DB2UC
*
* Purpose:
*   Convert Unicode double byte into UNICODE.
*   - Byte0: First byte, msb
*   - Byte1: Last  byte, lsb
*/
U16 GUI_DB2UC(U8 Byte0, U8 Byte1) {
  if (Byte0==0)
    return 0;
  if ((Byte0&0xfe) == 0xe0) {
    if (Byte0 == 0xe0)        /* ASCII */
      return Byte1;
    return ((U16)Byte1)<<8;   /* low byte was zero */
  }
  return Byte1 | (((U16)Byte0)<<8);
}

/*************************** End of file ****************************/
