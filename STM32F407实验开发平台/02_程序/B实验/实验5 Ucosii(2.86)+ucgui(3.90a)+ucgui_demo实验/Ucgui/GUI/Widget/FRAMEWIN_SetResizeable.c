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
File        : FRAMEWIN_SetResizeable.c
Purpose     : 
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "FRAMEWIN_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*        Defines
*
**********************************************************************
*/

#ifndef   FRAMEWIN_REACT_BORDER
  #define FRAMEWIN_REACT_BORDER 3
#endif
#ifndef   FRAMEWIN_MINSIZE_X
  #define FRAMEWIN_MINSIZE_X    20
#endif
#ifndef   FRAMEWIN_MINSIZE_Y
  #define FRAMEWIN_MINSIZE_Y    20
#endif

#define FRAMEWIN_RESIZE_X     (1<<0)
#define FRAMEWIN_RESIZE_Y     (1<<1)
#define FRAMEWIN_REPOS_X      (1<<2)
#define FRAMEWIN_REPOS_Y      (1<<3)
#define FRAMEWIN_MOUSEOVER    (1<<4)
#define FRAMEWIN_RESIZE       (FRAMEWIN_RESIZE_X | FRAMEWIN_RESIZE_Y | FRAMEWIN_REPOS_X | FRAMEWIN_REPOS_Y)

/*********************************************************************
*
*        Static data
*
**********************************************************************
*/

static GUI_HOOK _HOOK_Resizeable;
static int      _CaptureX;
static int      _CaptureY;
static int      _CaptureFlags;

#if GUI_SUPPORT_CURSOR
  static const GUI_CURSOR GUI_UNI_PTR * _pOldCursor;
#endif

/*********************************************************************
*
*        Static data, cursors
*
**********************************************************************
*/
#if GUI_SUPPORT_CURSOR

/*********************************************************************
*
*        Cursor colors
*/
static GUI_CONST_STORAGE GUI_COLOR _ColorsCursor[] = {
     0x0000FF,0x000000,0xFFFFFF
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalCursor = {
  3,	/* number of entries */
  1, 	/* Has transparency */
  &_ColorsCursor[0]
};

/*********************************************************************
*
*        Cursor data, CursorH
*/
static GUI_CONST_STORAGE unsigned char _acResizeCursorH[] = {
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x40, 0x00, 0x40, 0x00,
  0x01, 0x40, 0x00, 0x50, 0x00,
  0x06, 0x40, 0x00, 0x64, 0x00,
  0x1A, 0x55, 0x55, 0x69, 0x00,
  0x6A, 0xAA, 0xAA, 0xAA, 0x40,
  0x1A, 0x55, 0x55, 0x69, 0x00,
  0x06, 0x40, 0x00, 0x64, 0x00,
  0x01, 0x40, 0x00, 0x50, 0x00,
  0x00, 0x40, 0x00, 0x40, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00
};

static GUI_CONST_STORAGE GUI_BITMAP _bmResizeCursorH = {
 17,  /* XSize */
 17,  /* YSize */
 5,   /* BytesPerLine */
 2,   /* BitsPerPixel */
 _acResizeCursorH,    /* Pointer to picture data (indices) */
 &_PalCursor          /* Pointer to palette */
};

static GUI_CONST_STORAGE GUI_CURSOR _ResizeCursorH = {
  &_bmResizeCursorH, 8, 8
};

/*********************************************************************
*
*        Cursor data, CursorV
*/
static GUI_CONST_STORAGE unsigned char _acResizeCursorV[] = {
  0x00, 0x00, 0x40, 0x00, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x06, 0xA4, 0x00, 0x00,
  0x00, 0x1A, 0xA9, 0x00, 0x00,
  0x00, 0x55, 0x95, 0x40, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x55, 0x95, 0x40, 0x00,
  0x00, 0x1A, 0xA9, 0x00, 0x00,
  0x00, 0x06, 0xA4, 0x00, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x00, 0x00
};

static GUI_CONST_STORAGE GUI_BITMAP _bmResizeCursorV = {
 17,  /* XSize */
 17,  /* YSize */
 5,   /* BytesPerLine */
 2,   /* BitsPerPixel */
 _acResizeCursorV,    /* Pointer to picture data (indices) */
 &_PalCursor          /* Pointer to palette */
};

static GUI_CONST_STORAGE GUI_CURSOR _ResizeCursorV = {
  &_bmResizeCursorV, 8, 8
};

/*********************************************************************
*
*        Cursor data, CursorDD
*/
static GUI_CONST_STORAGE unsigned char _acResizeCursorDD[] = {
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x05, 0x55, 0x00, 0x00, 0x00,
  0x06, 0xA4, 0x00, 0x00, 0x00,
  0x06, 0x90, 0x00, 0x00, 0x00,
  0x06, 0x64, 0x00, 0x00, 0x00,
  0x05, 0x19, 0x00, 0x00, 0x00,
  0x04, 0x06, 0x40, 0x00, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x00, 0x00, 0x64, 0x04, 0x00,
  0x00, 0x00, 0x19, 0x14, 0x00,
  0x00, 0x00, 0x06, 0x64, 0x00,
  0x00, 0x00, 0x01, 0xA4, 0x00,
  0x00, 0x00, 0x06, 0xA4, 0x00,
  0x00, 0x00, 0x15, 0x54, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00
};

static GUI_CONST_STORAGE GUI_BITMAP _bmResizeCursorDD = {
 17,  /* XSize */
 17,  /* YSize */
 5,   /* BytesPerLine */
 2,   /* BitsPerPixel */
 _acResizeCursorDD,   /* Pointer to picture data (indices) */
 &_PalCursor          /* Pointer to palette */
};

static GUI_CONST_STORAGE GUI_CURSOR _ResizeCursorDD = {
  &_bmResizeCursorDD, 8, 8
};

/*********************************************************************
*
*        Cursor data, CursorDU
*/
static GUI_CONST_STORAGE unsigned char _acResizeCursorDU[] = {
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x15, 0x54, 0x00,
  0x00, 0x00, 0x06, 0xA4, 0x00,
  0x00, 0x00, 0x01, 0xA4, 0x00,
  0x00, 0x00, 0x06, 0x64, 0x00,
  0x00, 0x00, 0x19, 0x14, 0x00,
  0x00, 0x00, 0x64, 0x04, 0x00,
  0x00, 0x01, 0x90, 0x00, 0x00,
  0x04, 0x06, 0x40, 0x00, 0x00,
  0x05, 0x19, 0x00, 0x00, 0x00,
  0x06, 0x64, 0x00, 0x00, 0x00,
  0x06, 0x90, 0x00, 0x00, 0x00,
  0x06, 0xA4, 0x00, 0x00, 0x00,
  0x05, 0x55, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00
};

static GUI_CONST_STORAGE GUI_BITMAP _bmResizeCursorDU = {
 17,  /* XSize */
 17,  /* YSize */
 5,   /* BytesPerLine */
 2,   /* BitsPerPixel */
 _acResizeCursorDU,   /* Pointer to picture data (indices) */
 &_PalCursor          /* Pointer to palette */
};

static GUI_CONST_STORAGE GUI_CURSOR _ResizeCursorDU = {
  &_bmResizeCursorDU, 8, 8
};

#endif

/*********************************************************************
*
*        Static code, helpers
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetResizeCursor
*/
#if GUI_SUPPORT_CURSOR
static void _SetResizeCursor(int Mode) {
  const GUI_CURSOR GUI_UNI_PTR * pNewCursor = NULL;
  if (Mode) {
    int Direction;
    Direction = Mode & (FRAMEWIN_RESIZE_X | FRAMEWIN_RESIZE_Y);
    if (Direction == FRAMEWIN_RESIZE_X) {
      pNewCursor = &_ResizeCursorH;
    } else if (Direction == FRAMEWIN_RESIZE_Y) {
      pNewCursor = &_ResizeCursorV;
    } else {
      Direction = Mode & (FRAMEWIN_REPOS_X | FRAMEWIN_REPOS_Y);
      if ((Direction == (FRAMEWIN_REPOS_X | FRAMEWIN_REPOS_Y)) || !Direction) {
        pNewCursor = &_ResizeCursorDD;
      } else {
        pNewCursor = &_ResizeCursorDU;
      }
    }
  }
  if (pNewCursor) {
    const GUI_CURSOR GUI_UNI_PTR * pOldCursor;
    pOldCursor = GUI_CURSOR_Select(pNewCursor);
    if (_pOldCursor == NULL) {
      _pOldCursor = pOldCursor;
    }
  } else if (_pOldCursor) {
    GUI_CURSOR_Select(_pOldCursor);
    _pOldCursor = NULL;
  }
}
#endif

/*********************************************************************
*
*       _SetCapture
*/
static void _SetCapture(FRAMEWIN_Handle hWin, int x, int y, int Mode) {
  if ((_CaptureFlags & FRAMEWIN_REPOS_X) == 0) {
    _CaptureX = x;
  }
  if ((_CaptureFlags & FRAMEWIN_REPOS_Y) == 0) {
    _CaptureY = y;
  }
  if (Mode) {
    if (WM_HasCaptured(hWin) == 0) {
      WM_SetCapture(hWin, 0);
    }
  #if GUI_SUPPORT_CURSOR
    _SetResizeCursor(Mode);
  #endif
    if (Mode & FRAMEWIN_MOUSEOVER) {
      Mode = 0;
    }
    _CaptureFlags = (Mode | FRAMEWIN_MOUSEOVER);
  }
}

/*********************************************************************
*
*       _ChangeWindowPosSize
*/
static void _ChangeWindowPosSize(FRAMEWIN_Handle hWin, int* px, int* py) {
  int dx = 0, dy = 0;
  GUI_RECT Rect;
  WM_GetClientRectEx(hWin, &Rect);
  /* Calculate new size of window */
  if (_CaptureFlags & FRAMEWIN_RESIZE_X) {
    dx = (_CaptureFlags & FRAMEWIN_REPOS_X) ? (_CaptureX - *px) : (*px - _CaptureX);
  }
  if (_CaptureFlags & FRAMEWIN_RESIZE_Y) {
    dy = (_CaptureFlags & FRAMEWIN_REPOS_Y) ? (_CaptureY - *py) : (*py - _CaptureY);
  }
  /* Check the minimal size of window */
  if ((Rect.x1 + dx + 1) < FRAMEWIN_MINSIZE_X) {
    dx = FRAMEWIN_MINSIZE_X - Rect.x1 - 1;
    *px = _CaptureX + dx;
  }
  if ((Rect.y1 + dy + 1) < FRAMEWIN_MINSIZE_Y) {
    dy = FRAMEWIN_MINSIZE_Y - Rect.y1 - 1;
    *py = _CaptureY + dy;
  }
  /* Set new window position */
  if (_CaptureFlags & FRAMEWIN_REPOS_X) {
    WM_MoveWindow(hWin, -dx, 0);
  }
  if (_CaptureFlags & FRAMEWIN_REPOS_Y) {
    WM_MoveWindow(hWin, 0, -dy);
  }
  /* Set new window size */
  WM_ResizeWindow(hWin, dx, dy);
}

/*********************************************************************
*
*       _CheckBorderX
*/
static int _CheckBorderX(int x, int x1, int Border) {
  int Mode = 0;
  if (x > (x1 - Border)) {
    Mode = FRAMEWIN_RESIZE_X;
  } else if (x < (Border)) {
    Mode = FRAMEWIN_RESIZE_X | FRAMEWIN_REPOS_X;
  }
  return Mode;
}

/*********************************************************************
*
*       _CheckBorderY
*/
static int _CheckBorderY(int y, int y1, int Border) {
  int Mode = 0;
  if (y > (y1 - Border)) {
    Mode = FRAMEWIN_RESIZE_Y;
  } else if (y < (Border)) {
    Mode = FRAMEWIN_RESIZE_Y | FRAMEWIN_REPOS_Y;
  }
  return Mode;
}

/*********************************************************************
*
*       _CheckReactBorder
*/
static int _CheckReactBorder(FRAMEWIN_Handle hWin, int x, int y) {
  int Mode = 0;
  GUI_RECT r;
  WM_GetClientRectEx(hWin, &r);
  if ((x >= 0) && (y >= 0) && (x <= r.x1) && (y <= r.y1)) {
    Mode |= _CheckBorderX(x, r.x1, FRAMEWIN_REACT_BORDER);
    if (Mode) {
      Mode |= _CheckBorderY(y, r.y1, 4 * FRAMEWIN_REACT_BORDER);
    } else {
      Mode |= _CheckBorderY(y, r.y1, FRAMEWIN_REACT_BORDER);
      if (Mode) {
        Mode |= _CheckBorderX(x, r.x1, 4 * FRAMEWIN_REACT_BORDER);
      }
    }
  }
  return Mode;
}

/*********************************************************************
*
*       _OnTouch
*/
static int _OnTouch(FRAMEWIN_Handle hWin, WM_MESSAGE* pMsg) {
  const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
  if (pState) {  /* Something happened in our area (pressed or released) */
    int x, y, Mode;
    x    = pState->x;
    y    = pState->y;
    Mode = _CheckReactBorder(hWin, x, y);
    if (pState->Pressed == 1) {
      if (_CaptureFlags & FRAMEWIN_RESIZE) {
        _ChangeWindowPosSize(hWin, &x, &y);
        _SetCapture(hWin, x, y, 0);
        return 1;
      } else if (Mode) {
        WM_SetFocus(hWin);
        WM_BringToTop(hWin);
        _SetCapture(hWin, x, y, Mode);
        return 1;
      }
      #if (GUI_SUPPORT_MOUSE & GUI_SUPPORT_CURSOR)
      else if (_CaptureFlags) {
        WM_ReleaseCapture();
        return 1;
      }
      #endif
    } else if (WM_HasCaptured(hWin)) {
      _CaptureFlags &= ~(FRAMEWIN_RESIZE);
      #if (GUI_SUPPORT_MOUSE & GUI_SUPPORT_CURSOR)
        if (!Mode)
      #endif
      {
        WM_ReleaseCapture();
      }
      return 1;
    }
  }
  return 0;
}

/*******************************************************************
*
*       _ForwardMouseOverMsg
*/
#if (GUI_SUPPORT_MOUSE & GUI_SUPPORT_CURSOR)
static int _ForwardMouseOverMsg(FRAMEWIN_Handle hWin, WM_MESSAGE* pMsg) {
  GUI_PID_STATE* pState = (GUI_PID_STATE *)pMsg->Data.p;
  WM_HWIN hBelow;
  pState->x += WM_GetWindowOrgX(hWin);
  pState->y += WM_GetWindowOrgY(hWin);
  hBelow = WM_Screen2hWin(pState->x, pState->y);
  if (hBelow && (hBelow != hWin)) {
    pState->x -= WM_GetWindowOrgX(hBelow);
    pState->y -= WM_GetWindowOrgY(hBelow);
    WM__SendMessage(hBelow, pMsg);
    return 1;
  }
  return 0;
}
#endif

/*********************************************************************
*
*       _OnMouseOver
*/
#if (GUI_SUPPORT_MOUSE & GUI_SUPPORT_CURSOR)
static int _OnMouseOver(FRAMEWIN_Handle hWin, WM_MESSAGE* pMsg) {
  const GUI_PID_STATE* pState = (const GUI_PID_STATE *)pMsg->Data.p;
  if (pState) {
    int x, y, Mode;
    x    = pState->x;
    y    = pState->y;
    Mode = _CheckReactBorder(hWin, x, y);
    if (Mode) {
      if (_ForwardMouseOverMsg(hWin, pMsg) == 0) {
        _SetCapture(hWin, x, y, Mode | FRAMEWIN_MOUSEOVER);
      }
      return 1;
    } else if (WM_HasCaptured(hWin)) {
      if ((_CaptureFlags & FRAMEWIN_RESIZE) == 0) {
        WM_ReleaseCapture();
        _ForwardMouseOverMsg(hWin, pMsg);
      }
      return 1;
    }
  }
  return 0;
}
#endif

/*********************************************************************
*
*       static code, hook function
*
**********************************************************************
*/
/*********************************************************************
*
*       _HOOKFUNC_Resizeable
*/
static int _HOOKFUNC_Resizeable(WM_MESSAGE* pMsg) {
  WM_HWIN hWin = pMsg->hWin;
  if (WM_HasCaptured(hWin) && (_CaptureFlags == 0)) {
    return 0;
  }
  if (FRAMEWIN_IsMinimized(hWin) || FRAMEWIN_IsMaximized(hWin)) {
    return 0;
  }
  switch(pMsg->MsgId) {
  case WM_TOUCH:
    return _OnTouch(hWin, pMsg);
#if (GUI_SUPPORT_MOUSE & GUI_SUPPORT_CURSOR)
  case WM_MOUSEOVER:
    return _OnMouseOver(hWin, pMsg);
#endif
  case WM_CAPTURE_RELEASED:
  #if GUI_SUPPORT_CURSOR
    _SetResizeCursor(0);
  #endif
    _CaptureFlags = 0;
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*        Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       FRAMEWIN_SetResizeable
*/
void FRAMEWIN_SetResizeable(FRAMEWIN_Handle hObj, int State) {
  if (hObj) {
    FRAMEWIN_Obj* pObj;
    WM_LOCK();
    pObj = FRAMEWIN_H2P(hObj);
    if (pObj) {
      if (State) {
        GUI_HOOK_Add(&pObj->pFirstHook, &_HOOK_Resizeable, &_HOOKFUNC_Resizeable);
      } else {
        GUI_HOOK_Remove(&pObj->pFirstHook, &_HOOK_Resizeable);
      }
    }
    WM_UNLOCK();
  }
}

#else
  void FRAMEWIN_SetResizeable_c(void) {} /* avoid empty object files */
#endif /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
