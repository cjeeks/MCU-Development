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
File        : CHECKBOX.h
Purpose     : CHECKBOX include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "WM.h"
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*           defines
*
**********************************************************************
*/

/*********************************************************************
*
*       Bitmap indices
*/
#define CHECKBOX_BI_INACTIV        0
#define CHECKBOX_BI_ACTIV          1
#define CHECKBOX_BI_INACTIV_3STATE 2
#define CHECKBOX_BI_ACTIV_3STATE   3

/*********************************************************************
*
*                         Public Types
*
**********************************************************************

*/
typedef WM_HMEM CHECKBOX_Handle;

/*********************************************************************
*
*                 Create functions
*
**********************************************************************
*/

CHECKBOX_Handle CHECKBOX_Create        (int x0, int y0, int xsize, int ysize, WM_HWIN hParent, int Id, int Flags);
CHECKBOX_Handle CHECKBOX_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
CHECKBOX_Handle CHECKBOX_CreateEx      (int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                        int WinFlags, int ExFlags, int Id);

/*********************************************************************
*
*       Standard member functions
*
**********************************************************************
*/

int                          CHECKBOX_GetDefaultAlign    (void);
GUI_COLOR                    CHECKBOX_GetDefaultBkColor  (void);
const GUI_FONT GUI_UNI_PTR * CHECKBOX_GetDefaultFont     (void);
int                          CHECKBOX_GetDefaultSpacing  (void);
int                          CHECKBOX_GetDefaultTextAlign(void);
GUI_COLOR                    CHECKBOX_GetDefaultTextColor(void);
void                         CHECKBOX_SetDefaultAlign    (int Align);
void                         CHECKBOX_SetDefaultBkColor  (GUI_COLOR Color);
void                         CHECKBOX_SetDefaultFont     (const GUI_FONT GUI_UNI_PTR * pFont);
void                         CHECKBOX_SetDefaultImage    (const GUI_BITMAP * pBitmap, unsigned int Index);
void                         CHECKBOX_SetDefaultSpacing  (int Spacing);
void                         CHECKBOX_SetDefaultTextAlign(int Align);
void                         CHECKBOX_SetDefaultTextColor(GUI_COLOR Color);

/*********************************************************************
*
*                 Member functions
*
**********************************************************************
*/

int  CHECKBOX_GetState    (CHECKBOX_Handle hObj);
int  CHECKBOX_IsChecked   (CHECKBOX_Handle hObj);
void CHECKBOX_SetBkColor  (CHECKBOX_Handle hObj, GUI_COLOR Color);
void CHECKBOX_SetFont     (CHECKBOX_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont);
void CHECKBOX_SetImage    (CHECKBOX_Handle hObj, const GUI_BITMAP * pBitmap, unsigned int Index);
void CHECKBOX_SetNumStates(CHECKBOX_Handle hObj, unsigned NumStates);
void CHECKBOX_SetSpacing  (CHECKBOX_Handle hObj, unsigned Spacing);
void CHECKBOX_SetState    (CHECKBOX_Handle hObj, unsigned State);
void CHECKBOX_SetText     (CHECKBOX_Handle hObj, const char * pText);
void CHECKBOX_SetTextAlign(CHECKBOX_Handle hObj, int Align);
void CHECKBOX_SetTextColor(CHECKBOX_Handle hObj, GUI_COLOR Color);

/*********************************************************************
*
*       Macros for compatibility
*
**********************************************************************
*/

#define CHECKBOX_Check(hObj)   CHECKBOX_SetState(hObj, 1)
#define CHECKBOX_Uncheck(hObj) CHECKBOX_SetState(hObj, 0)

#if defined(__cplusplus)
  }
#endif

#endif   /* if GUI_WINSUPPORT */
#endif   /* CHECKBOX_H */
