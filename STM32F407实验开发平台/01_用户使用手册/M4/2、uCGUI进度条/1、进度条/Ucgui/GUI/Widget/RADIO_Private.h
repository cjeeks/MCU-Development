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
File        : RADIO_Private.h
Purpose     : RADIO private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef RADIO_PRIVATE_H
#define RADIO_PRIVATE_H

#include "WM.h"

#if GUI_WINSUPPORT

#include "RADIO.h"
#include "WIDGET.h"
#include "GUI_ARRAY.h"

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  WIDGET Widget;
  const GUI_BITMAP* apBmRadio[2];
  const GUI_BITMAP* pBmCheck;
  GUI_ARRAY TextArray;
  I16 Sel;                   /* current selection */
  U16 Spacing;
  U16 Height;
  U16 NumItems;
  U8  GroupId;
  GUI_COLOR BkColor;
  GUI_COLOR TextColor;
  const GUI_FONT GUI_UNI_PTR* pFont;
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
} RADIO_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define RADIO_H2P(h) (RADIO_Obj*) GUI_ALLOC_h2p(h)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef void tRADIO_SetValue(RADIO_Handle hObj, RADIO_Obj* pObj, int v);

/*********************************************************************
*
*       Extern data
*
**********************************************************************
*/

extern const GUI_BITMAP             RADIO__abmRadio[2];
extern const GUI_BITMAP             RADIO__bmCheck;
extern const GUI_BITMAP*            RADIO__apDefaultImage[2];
extern const GUI_BITMAP*            RADIO__pDefaultImageCheck;
extern const GUI_FONT GUI_UNI_PTR*  RADIO__pDefaultFont;
extern       GUI_COLOR              RADIO__DefaultTextColor;
extern       tRADIO_SetValue*       RADIO__pfHandleSetValue;

/*********************************************************************
*
*       public functions (internal)
*
**********************************************************************
*/

void RADIO__SetValue(RADIO_Handle hObj, RADIO_Obj* pObj, int v);

#endif   /* GUI_WINSUPPORT */
#endif   /* RADIO_PRIVATE_H */

/************************* end of file ******************************/
