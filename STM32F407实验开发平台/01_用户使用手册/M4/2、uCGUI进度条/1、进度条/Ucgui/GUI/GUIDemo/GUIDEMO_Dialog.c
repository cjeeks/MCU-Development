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
File        : GUIDEMO_Dialog.c
Purpose     : Automotive samples
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "GUI.h"
#include "GUIDEMO.h"
#include "LCD_ConfDefaults.h"

#if GUI_SUPPORT_MEMDEV && GUI_WINSUPPORT

#include "WM.h"
#include "DIALOG.h"
#include "LISTBOX.h"
#include "EDIT.h"
#include "SLIDER.h"
#include "FRAMEWIN.h"

/*********************************************************************
*
*       types
*
**********************************************************************
*/

typedef struct {
  unsigned char Id;
  int Time;
} KEYSIM;

/*********************************************************************
*
*       static data
*
**********************************************************************
*/

#if GUIDEMO_LARGE

static const GUI_WIDGET_CREATE_INFO aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Dialog", 0,               10,   10, 162, 214, FRAMEWIN_CF_MOVEABLE},
  { BUTTON_CreateIndirect,   "OK",     GUI_ID_OK,       90,    5,  60,  20 },
  { BUTTON_CreateIndirect,   "Cancel", GUI_ID_CANCEL,   90,   30,  60,  20 },
  { TEXT_CreateIndirect,     "LText",  0,                5,   59,  43,  15, TEXT_CF_LEFT  },
  { TEXT_CreateIndirect,     "RText",  0,                5,   79,  43,  15, TEXT_CF_RIGHT },
  { TEXT_CreateIndirect,     "Hex",    0,                5,   99,  48,  15, TEXT_CF_LEFT  },
  { TEXT_CreateIndirect,     "Bin",    0,                5,  119,  48,  15, TEXT_CF_LEFT  },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT0,    50,   59, 100,  15, EDIT_CF_LEFT,  50 },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT1,    50,   79, 100,  15, EDIT_CF_RIGHT, 50 },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT2,    50,   99, 100,  15, EDIT_CF_RIGHT, 6  },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT3,    50,  119, 100,  15, EDIT_CF_LEFT,  0  },
  { LISTBOX_CreateIndirect,  "",       GUI_ID_LISTBOX0,  5,    5,  75,  45, 0, 0 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER1,   5,  140, 100,  20, 0, 0 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER0,   5,  165, 145,  26, 0, 0 }
};

static const KEYSIM _aID[] = {
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_DOWN, 250 },
  { GUI_KEY_DOWN, 250 },
  { GUI_KEY_DOWN, 250 },
  { GUI_KEY_DOWN, 250 },
  { GUI_KEY_UP,   250 },
  { GUI_KEY_UP,   250 }
};

static const GUI_ConstString _apListBox[] = {
  "English", "Deutsch", "Français", "Japanese", "Italiano", NULL
};

#elif !(GUIDEMO_TINY)

static const GUI_WIDGET_CREATE_INFO aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Dialog", 0,               10,   10, 132, 113, FRAMEWIN_CF_MOVEABLE},
  { BUTTON_CreateIndirect,   "OK",     GUI_ID_OK,        5,    5,  55,  20 },
  { BUTTON_CreateIndirect,   "Cancel", GUI_ID_CANCEL,   65,    5,  55,  20 },
  { TEXT_CreateIndirect,     "LText",  0,                5,   32,  33,  15, TEXT_CF_LEFT  },
  { TEXT_CreateIndirect,     "RText",  0,                5,   52,  33,  15, TEXT_CF_RIGHT },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT0,    40,   32,  80,  15, EDIT_CF_LEFT,  50 },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT1,    40,   52,  80,  15, EDIT_CF_RIGHT, 50 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER0,   5,   74, 116,  20, 0, 0 },
};

static const KEYSIM _aID[] = {
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_TAB,  400 },
};

#else

static const GUI_WIDGET_CREATE_INFO aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Dialog", 0,                0,    0,  110,  84, FRAMEWIN_CF_MOVEABLE},
  { BUTTON_CreateIndirect,   "OK",     GUI_ID_OK,        4,    3,  95,  18 },
  { TEXT_CreateIndirect,     "Text",   0,                5,   25,  28,  15, TEXT_CF_LEFT  },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT0,    30,   25,  69,  15, EDIT_CF_LEFT,  50 },
};

static const KEYSIM _aID[] = {
  { GUI_KEY_TAB,  400 },
  { GUI_KEY_TAB,  400 },
};

#endif

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbCallback
*/
static void _cbCallback(WM_MESSAGE * pMsg) {
  WM_HWIN hWin = pMsg->hWin;
  #if GUIDEMO_LARGE
    int NCode, Id;
  #endif
  switch (pMsg->MsgId) {
    case WM_INIT_DIALOG:
      /* Initialize all widgets */
      #if GUIDEMO_TINY
        EDIT_SetText(WM_GetDialogItem(hWin, GUI_ID_EDIT0), "EDIT");
      #else
        EDIT_SetText(WM_GetDialogItem(hWin, GUI_ID_EDIT0), "EDIT widget 0");
        EDIT_SetText(WM_GetDialogItem(hWin, GUI_ID_EDIT1), "EDIT widget 1");
      #endif
      {
        #if GUIDEMO_LARGE
          WM_HWIN hListBox;
          EDIT_SetHexMode(WM_GetDialogItem(hWin, GUI_ID_EDIT2), 0x1234, 0, 0xffffff);
          EDIT_SetBinMode(WM_GetDialogItem(hWin, GUI_ID_EDIT3), 0x1234, 0, 0xffff);
          hListBox = WM_GetDialogItem(hWin, GUI_ID_LISTBOX0);
          LISTBOX_SetText(hListBox, _apListBox);
          SCROLLBAR_CreateAttached(hListBox, SCROLLBAR_CF_VERTICAL);
        #else
          GUI_RECT Rect;
          int x, y, ySize;
          ySize = LCD_GetYSize();
          if (ySize < 120) {
            WM_ResizeWindow(hWin, 0, -24);
          }
          WM_GetWindowRectEx(hWin, &Rect);
          x = (LCD_GetXSize() - (Rect.x1 - Rect.x0 + 1)) >> 1;
          y = (ySize          - (Rect.y1 - Rect.y0 + 1)) >> 1;
          #if GUIDEMO_TINY
            WM_MoveTo(hWin, x, y);
          #else
            WM_MoveTo(hWin, x, y - 4);
          #endif
        #endif
      }
      break;
    case WM_KEY:
      switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) {
      case GUI_KEY_ESCAPE:
        GUI_EndDialog(hWin, 1);
        break;
      case GUI_KEY_ENTER:
        GUI_EndDialog(hWin, 0);
        break;
      }
      break;
  #if GUIDEMO_LARGE
    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);    /* Id of widget */
      NCode = pMsg->Data.v;               /* Notification code */
      switch (NCode) {
        case WM_NOTIFICATION_RELEASED:    /* React only if released */
          if (Id == GUI_ID_OK) {          /* OK Button */
            GUI_EndDialog(hWin, 0);
          }
          if (Id == GUI_ID_CANCEL) {      /* Cancel Button */
            GUI_EndDialog(hWin, 1);
          }
          break;
        case WM_NOTIFICATION_SEL_CHANGED: /* Selection changed */
          FRAMEWIN_SetText(hWin, "Dialog - sel changed");
          break;
        default:
          FRAMEWIN_SetText(hWin, "Dialog - notification received");
      }
      break;
  #endif
    default:
      WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIDEMO_Dialog
*/
void GUIDEMO_Dialog(void) {
  int i;
  WM_HWIN hWin;
  GUI_COLOR DesktopColorOld;
  GUIDEMO_ShowIntro("Dialog boxes", "\nDialog boxes\ncan easily be created");
  GUIDEMO_HideInfoWin();
  DesktopColorOld = GUIDEMO_SetBkColor(GUI_RED);
  DesktopColorOld = WM_SetDesktopColor(DesktopColorOld);  /* Automatically update desktop window */
  hWin = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), _cbCallback, 0, 0, 0);
  for (i = 0; i < GUI_COUNTOF(_aID); i++) {
    GUIDEMO_Delay(_aID[i].Time);
    GUI_SendKeyMsg(_aID[i].Id, 1);
  }
  #if !(GUIDEMO_TINY)
    #if !(GUIDEMO_LARGE)
      if (LCD_GetYSize() < 120) {
      } else
    #endif
    {
      GUIDEMO_Delay(1000);
      for (i = 0; i <= 100; i += 10) {
        if (WM_IsWindow(hWin)) {
          SLIDER_SetValue(WM_GetDialogItem(hWin, GUI_ID_SLIDER0), i);
        }
        GUIDEMO_Delay(100);
      }
    }
  #endif
  GUIDEMO_Delay(800);
  if (WM_IsWindow(hWin)) {
    WM_MoveTo(hWin, 20, 20);
    GUIDEMO_Delay(500);
  }
  if (WM_IsWindow(hWin)) {
    WM_MoveTo(hWin, 60, 20);
    GUIDEMO_Delay(800);
  }
  /* Cleanup ... */
  if (WM_IsWindow(hWin)) {
    WM_DeleteWindow(hWin);
  }
  GUIDEMO_NotifyStartNext();
  WM_SetDesktopColor(DesktopColorOld);   /* Restore old settings */
}

#else

void GUIDEMO_Dialog(void) {}

#endif /* GUI_SUPPORT_MEMDEV */
