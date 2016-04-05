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
File        : LISTVIEW_Private.h
Purpose     : Private LISTVIEW include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef LISTVIEW_PRIVATE_H
#define LISTVIEW_PRIVATE_H

#include "WM.h"
#include "LISTVIEW.h"
#include "GUI_ARRAY.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define LISTVIEW_ID 0x4567   /* Magic numer, should be unique if possible */

#define LISTVIEW_H2P(h) (LISTVIEW_Obj*) WM_H2P(h)

#if GUI_DEBUG_LEVEL > 1
  #define LISTVIEW_ASSERT_IS_VALID_PTR(p) DEBUG_ERROROUT_IF(p->DebugId != LISTVIEW_ID, "xxx.c: Wrong handle type or Object not init'ed")
  #define LISTVIEW_INIT_ID(p)   p->DebugId = LISTVIEW_ID
  #define LISTVIEW_DEINIT_ID(p) p->DebugId = LISTVIEW_ID+1
#else
  #define LISTVIEW_ASSERT_IS_VALID_PTR(p)
  #define LISTVIEW_INIT_ID(p)
  #define LISTVIEW_DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/

typedef struct {
  GUI_COLOR aBkColor[3];
  GUI_COLOR aTextColor[3];
} LISTVIEW_ITEM_INFO;

typedef struct {
  WM_HMEM hItemInfo;
  char acText[1];
} LISTVIEW_ITEM;

typedef struct {
  GUI_COLOR                    aBkColor[3];
  GUI_COLOR                    aTextColor[3];
  GUI_COLOR                    GridColor;
  const GUI_FONT GUI_UNI_PTR * pFont;
} LISTVIEW_PROPS;

typedef struct {
  WIDGET          Widget;
  HEADER_Handle   hHeader;
  GUI_ARRAY       RowArray;         /* One entry per line. Every entry is a handle of GUI_ARRAY of strings */
  GUI_ARRAY       AlignArray;       /* One entry per column */
  LISTVIEW_PROPS  Props;
  int             Sel;
  int             ShowGrid;
  unsigned        RowDistY;
  unsigned        LBorder;
  unsigned        RBorder;
  WM_SCROLL_STATE ScrollStateV;
  WM_SCROLL_STATE ScrollStateH;
  WM_HWIN         hOwner;
  #if GUI_DEBUG_LEVEL > 1
    int DebugId;
  #endif  
} LISTVIEW_Obj;

/*********************************************************************
*
*       Private (module internal) data
*
**********************************************************************
*/

extern LISTVIEW_PROPS LISTVIEW_DefaultProps;

/*********************************************************************
*
*       Private (module internal) functions
*
**********************************************************************
*/
int      LISTVIEW__UpdateScrollParas   (LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj);
void     LISTVIEW__InvalidateInsideArea(LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj);
unsigned LISTVIEW__GetRowDistY         (const LISTVIEW_Obj* pObj);
void     LISTVIEW__InvalidateRow       (LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj, int Sel);
int      LISTVIEW__UpdateScrollPos     (LISTVIEW_Handle hObj, LISTVIEW_Obj* pObj);

#endif /* GUI_WINSUPPORT */

#else                            /* Avoid problems with empty object modules */
  void LISTVIEW_C(void) {}
#endif

/*************************** End of file ****************************/
