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
File        : MULTIPAGE_Private.h
Purpose     : Private MULTIPAGE include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef MULTIPAGE_PRIVATE_H

#include "GUIDebug.h"
#include "MULTIPAGE.h"

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#define MULTIPAGE_STATE_ENABLED     (1<<0)
#define MULTIPAGE_STATE_SCROLLMODE  WIDGET_STATE_USER0

#define MULTIPAGE_ID 0x4544   /* Magic number, should be unique if possible */

#define MULTIPAGE_H2P(h) (MULTIPAGE_Obj*) WM_H2P(h)

#if GUI_DEBUG_LEVEL > 1
  #define MULTIPAGE_ASSERT_IS_VALID_PTR(p) GUI_DEBUG_ERROROUT_IF(p->DebugId != MULTIPAGE_ID, "MULTIPAGE.c: Wrong handle type or Object not init'ed")
  #define MULTIPAGE_INIT_ID(p)   p->DebugId = MULTIPAGE_ID
  #define MULTIPAGE_DEINIT_ID(p) p->DebugId = MULTIPAGE_ID+1
#else
  #define MULTIPAGE_ASSERT_IS_VALID_PTR(p)
  #define MULTIPAGE_INIT_ID(p)
  #define MULTIPAGE_DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Externals
*
**********************************************************************
*/

extern const GUI_FONT GUI_UNI_PTR * MULTIPAGE__pDefaultFont;
extern unsigned                     MULTIPAGE__DefaultAlign;
extern GUI_COLOR                    MULTIPAGE__DefaultBkColor[2];
extern GUI_COLOR                    MULTIPAGE__DefaultTextColor[2];

#endif /* MULTIPAGE_PRIVATE_H */
