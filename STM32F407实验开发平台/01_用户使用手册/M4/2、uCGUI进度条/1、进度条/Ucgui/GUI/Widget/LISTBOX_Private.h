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
File        : LISTBOX_Private.h
Purpose     : Private LISTBOX include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef LISTBOX_PRIVATE_H
#define LISTBOX_PRIVATE_H

#include "LISTBOX.h"
#include "WM.h"
#include "GUI_ARRAY.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define LISTBOX_H2P(h) (LISTBOX_Obj*) GUI_ALLOC_h2p(h)

#if GUI_DEBUG_LEVEL >1
  #define OBJECT_ID 0x4C69   /* Magic numer, should be unique if possible */
  #define ASSERT_IS_VALID_PTR(p) GUI_DEBUG_ERROROUT_IF(p->DebugId != OBJECT_ID, "EDIT.C: Wrong handle type or Object not init'ed")
  #define INIT_ID(p)   p->DebugId = OBJECT_ID
  #define DEINIT_ID(p) p->DebugId = 0
#else
  #define ASSERT_IS_VALID_PTR(p)
  #define INIT_ID(p)
  #define DEINIT_ID(p)
#endif

#define LISTBOX_ITEM_SELECTED (1 << 0)
#define LISTBOX_ITEM_DISABLED (1 << 1)

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  U16  xSize, ySize;
  U8   Status;
  char acText[1];
} LISTBOX_ITEM;

typedef struct {
  const GUI_FONT GUI_UNI_PTR* pFont;
  U16                         ScrollStepH;
  GUI_COLOR aBackColor[4];
  GUI_COLOR aTextColor[4];
} LISTBOX_PROPS;

typedef struct {
  WIDGET Widget;
  GUI_ARRAY ItemArray;
  WIDGET_DRAW_ITEM_FUNC* pfDrawItem;
  WM_SCROLL_STATE ScrollStateV;
  WM_SCROLL_STATE ScrollStateH;
  LISTBOX_PROPS Props;
  WM_HWIN hOwner;
  #if GUI_DEBUG_LEVEL >1
    int DebugId;
  #endif  
  I16 Sel;                        /* current selection */
  U8 Flags;
  U8  ScrollbarWidth;
  U16 ItemSpacing;
} LISTBOX_Obj;

/*********************************************************************
*
*       Private (module internal) data
*
**********************************************************************
*/

extern LISTBOX_PROPS LISTBOX_DefaultProps;

/*********************************************************************
*
*       Private (module internal) functions
*
**********************************************************************
*/
unsigned    LISTBOX__GetNumItems           (const LISTBOX_Obj* pObj);
const char* LISTBOX__GetpString            (const LISTBOX_Obj* pObj, int Index);
void        LISTBOX__InvalidateInsideArea  (LISTBOX_Handle hObj);
void        LISTBOX__InvalidateItem        (LISTBOX_Handle hObj, const LISTBOX_Obj* pObj, int Sel);
void        LISTBOX__InvalidateItemAndBelow(LISTBOX_Handle hObj, const LISTBOX_Obj* pObj, int Sel);
void        LISTBOX__InvalidateItemSize    (const LISTBOX_Obj* pObj, unsigned Index);
void        LISTBOX__SetScrollbarWidth     (LISTBOX_Handle hObj, const LISTBOX_Obj* pObj);

#endif /* GUI_WINSUPPORT */

#else                            /* Avoid problems with empty object modules */
  void LISTBOX_C(void) {}
#endif

/*************************** End of file ****************************/
