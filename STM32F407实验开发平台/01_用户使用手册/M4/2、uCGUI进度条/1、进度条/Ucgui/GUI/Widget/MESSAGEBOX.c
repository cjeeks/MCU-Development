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
File        : MESSAGEBOX.c
Purpose     : Implementation of Mesagebox
---------------------------END-OF-HEADER------------------------------
*/


#include <string.h>             /* for memset */
#include "GUI.h"
#include "BUTTON.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "DIALOG.h"
#include "MESSAGEBOX.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Defaults
*
**********************************************************************
*/

#ifndef MESSAGEBOX_BORDER
  #define MESSAGEBOX_BORDER 4
#endif

#ifndef MESSAGEBOX_XSIZEOK
  #define MESSAGEBOX_XSIZEOK 50
#endif

#ifndef MESSAGEBOX_YSIZEOK
  #define MESSAGEBOX_YSIZEOK 20
#endif

#ifndef MESSAGEBOX_BKCOLOR
  #define MESSAGEBOX_BKCOLOR GUI_WHITE
#endif

#define ID_FRAME 100

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/
/*********************************************************************
*
*       _MESSAGEBOX_cbCallback
*/
static void _MESSAGEBOX_cbCallback(WM_MESSAGE * pMsg) {
  WM_HWIN hWin = pMsg->hWin;
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      FRAMEWIN_SetClientColor(hWin, MESSAGEBOX_BKCOLOR);
      break;
    case WM_KEY:
      {
        int Key = ((const WM_KEY_INFO*)(pMsg->Data.p))->Key;
        if (((const WM_KEY_INFO*)(pMsg->Data.p))->PressedCnt) {
          switch (Key) {
          case GUI_KEY_ESCAPE:
            GUI_EndDialog(hWin, 1);             /* End dialog with return value 1 if <ESC> is pressed */
            break;
          case GUI_KEY_ENTER:
            GUI_EndDialog(hWin, 0);             /* End dialog with return value 0 if <ENTER> is pressed */
            break;
          }
        }
      }
      break;
    case WM_NOTIFY_PARENT:
      {
        int NCode = pMsg->Data.v;             /* Get notification code */
        int Id    = WM_GetId(pMsg->hWinSrc);  /* Get control ID */
        switch (NCode) {
          case WM_NOTIFICATION_RELEASED:      /* React only if released */
            if (Id == GUI_ID_OK) {
              GUI_EndDialog(hWin, 0);         /* End dialog with return value 0 if OK */
            }
            break;
        }
      }
      break;
    default:
      WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       MESSAGEBOX_Create
*/
WM_HWIN MESSAGEBOX_Create(const char * sMessage, const char * sCaption, int Flags) {
  GUI_WIDGET_CREATE_INFO _aDialogCreate[3];                                     /* 0: FrameWin, 1: Text, 2: Button */
  int BorderSize = FRAMEWIN_GetDefaultBorderSize();                             /* Default border size of frame window */
  int xSizeFrame = MESSAGEBOX_XSIZEOK + 2 * BorderSize + MESSAGEBOX_BORDER * 2; /* XSize of frame window */
  int ySizeFrame;                                                               /* YSize of frame window */
  int x0, y0;                                                                   /* Position of frame window */
  int xSizeMessage;                                                             /* Length in pixels of message */
  int xSizeCaption;                                                             /* Length in pixels of caption */
  int ySizeCaption;                                                             /* YSize of caption */
  int ySizeMessage;                                                             /* YSize of message */
  GUI_RECT Rect;
  const GUI_FONT GUI_UNI_PTR * pOldFont;
  /* Zeroinit variables */
  memset(_aDialogCreate, 0, sizeof(_aDialogCreate));
  /* Get dimension of message */
  pOldFont = GUI_SetFont(TEXT_GetDefaultFont());
  GUI_GetTextExtend(&Rect, sMessage, 255);
  xSizeMessage = Rect.x1 - Rect.x0 + MESSAGEBOX_BORDER * 2;
  ySizeMessage = Rect.y1 - Rect.y0 + 1;
  if (xSizeFrame < (xSizeMessage + 4 + MESSAGEBOX_BORDER * 2)) {
    xSizeFrame = xSizeMessage + 4 + MESSAGEBOX_BORDER * 2;
  }
  ySizeCaption = GUI_GetYSizeOfFont(FRAMEWIN_GetDefaultFont());
  ySizeFrame = ySizeMessage +            /* size of message */
               MESSAGEBOX_YSIZEOK +      /* size of button */
               ySizeCaption +            /* caption size */
               MESSAGEBOX_BORDER * 3 +   /* inner border - text, text - button, button - bottom */
               BorderSize * 2 +          /* top & bottom border */
               1;                        /* inner border */
  /* Get xsize of caption */
  xSizeCaption = GUI_GetStringDistX(sCaption);
  if (xSizeFrame < xSizeCaption + BorderSize * 2) {
    xSizeFrame = xSizeCaption + BorderSize * 2;
  }
  /* Check maximum */
  if (xSizeFrame > LCD_GET_XSIZE()) {
    xSizeFrame = LCD_GET_XSIZE();
  }
  if (ySizeFrame > LCD_GET_YSIZE()) {
    ySizeFrame = LCD_GET_YSIZE();
  }
  /* Calculate position of framewin */
  x0 = (LCD_GET_XSIZE() - xSizeFrame) / 2;
  y0 = (LCD_GET_YSIZE() - ySizeFrame) / 2;
  /* restore modified Context */
  GUI_SetFont(pOldFont);
  /* Fill frame win resource */
  _aDialogCreate[0].pfCreateIndirect = FRAMEWIN_CreateIndirect;
  _aDialogCreate[0].pName            = sCaption;
  _aDialogCreate[0].x0               = x0;
  _aDialogCreate[0].y0               = y0;
  _aDialogCreate[0].xSize            = xSizeFrame;
  _aDialogCreate[0].ySize            = ySizeFrame;
  if (Flags & GUI_MESSAGEBOX_CF_MOVEABLE) {
    _aDialogCreate[0].Flags          = FRAMEWIN_CF_MOVEABLE;
  }
  /* Fill text resource */
  _aDialogCreate[1].pfCreateIndirect = TEXT_CreateIndirect;
  _aDialogCreate[1].pName            = sMessage;
  _aDialogCreate[1].x0               = (xSizeFrame - xSizeMessage - BorderSize * 2) / 2;
  _aDialogCreate[1].y0               = MESSAGEBOX_BORDER;
  _aDialogCreate[1].xSize            = xSizeMessage;
  _aDialogCreate[1].ySize            = ySizeMessage;
  _aDialogCreate[1].Para             = GUI_TA_TOP | GUI_TA_HCENTER;
  /* Fill button resource */
  _aDialogCreate[2].pfCreateIndirect = BUTTON_CreateIndirect;
  _aDialogCreate[2].pName            = "OK";
  _aDialogCreate[2].Id               = GUI_ID_OK;
  _aDialogCreate[2].x0               = (xSizeFrame - MESSAGEBOX_XSIZEOK - BorderSize * 2) / 2;
  _aDialogCreate[2].y0               = MESSAGEBOX_BORDER * 2 + ySizeMessage;
  _aDialogCreate[2].xSize            = MESSAGEBOX_XSIZEOK;
  _aDialogCreate[2].ySize            = MESSAGEBOX_YSIZEOK;
  /* Create dialog */
  return GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _MESSAGEBOX_cbCallback, 0, 0, 0);
}

/*********************************************************************
*
*       GUI_MessageBox
*/
int GUI_MessageBox(const char * sMessage, const char * sCaption, int Flags) {
  WM_HWIN hWin;
  hWin = MESSAGEBOX_Create(sMessage, sCaption, Flags);
  /* Exec dialog */
  return GUI_ExecCreatedDialog(hWin);
}

#else

void GUI_MessageBox_C(void) {} /* avoid empty object files */

#endif /* GUI_WINSUPPORT */
