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
File        : WM.C
Purpose     : Windows manager core
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include <string.h>           /* required for memset */

#define WM_C
#include "WM_Intern_ConfDep.h"

#if GUI_WINSUPPORT    /* If 0, WM will not generate any code */

/*********************************************************************
*
*                 Macros for internal use
*
**********************************************************************
*/

#define ASSIGN_IF_LESS(v0,v1) if (v1<v0) v0=v1

/*********************************************************************
*
*              Local typedefs
*
**********************************************************************
*/

typedef struct {
  GUI_RECT ClientRect;
  GUI_RECT CurRect;
  int Cnt;
  int EntranceCnt;
} WM_IVR_CONTEXT;

/*********************************************************************
*
*              global data
*
**********************************************************************
*/

U8                     WM_IsActive;
U16                    WM__CreateFlags;
WM_HWIN                WM__hCapture;
WM_HWIN                WM__hWinFocus;
char                   WM__CaptureReleaseAuto;
WM_tfPollPID*          WM_pfPollPID;
U8                     WM__PaintCallbackCnt;      /* Public for assertions only */
GUI_PID_STATE          WM_PID__StateLast;

#if WM_SUPPORT_TRANSPARENCY
  int                    WM__TransWindowCnt;
  WM_HWIN                WM__hATransWindow;
#endif

#if WM_SUPPORT_DIAG
  void (*WM__pfShowInvalid)(WM_HWIN hWin);
#endif

/*********************************************************************
*
*              static data
*
**********************************************************************
*/

static WM_HWIN        NextDrawWin;
static WM_IVR_CONTEXT _ClipContext;
static char           _IsInited;

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _CheckCriticalHandles
*
* Purpose:
*   Checks the critical handles and resets the matching one
*/
static void _CheckCriticalHandles(WM_HWIN hWin) {
  WM_CRITICAL_HANDLE * pCH;
  for (pCH = WM__pFirstCriticalHandle; pCH; pCH = pCH->pNext) {
    if (pCH->hWin == hWin) {
      pCH->hWin = 0;
    }
  }
}

/*********************************************************************
*
*       _DesktopHandle2Index
*
* Function:
*   Convert the given desktop window into the display index.
*
* Return value:
*   Desktop index if window handle is valid.
*   else: -1
*/
static int _DesktopHandle2Index(WM_HWIN hDesktop) {
#if GUI_NUM_LAYERS > 1
  int i;
  for (i = 0; i < GUI_NUM_LAYERS; i++) {
    if (hDesktop == WM__ahDesktopWin[i]) {
      return i;
    }
  }
#else
  if (hDesktop == WM__ahDesktopWin[0]) {
    return 0;
  }
#endif
  return -1;
}

/*********************************************************************
*
*       _Invalidate1Abs
*
*  Invalidate given window, using absolute coordinates
*/
static void _Invalidate1Abs(WM_HWIN hWin, const GUI_RECT*pRect) {
  GUI_RECT r;
  WM_Obj* pWin;
  int Status;
  pWin = WM_H2P(hWin);
  Status = pWin->Status;
  if ((Status & WM_SF_ISVIS) == 0) {
    return;   /* Window is not visible... we are done */
  }
  if ((Status & (WM_SF_HASTRANS | WM_SF_CONST_OUTLINE)) == WM_SF_HASTRANS) {
    return;   /* Window is transparent; transparency may change... we are done, since background will be invalidated */
  }
  if (WM__RectIsNZ(pRect) == 0) {
    return;   /* Nothing to do ... */
  }
  /* Calc affected area */
  GUI__IntersectRects(&r, pRect, &pWin->Rect);
  if (WM__RectIsNZ(&r)) {
    #if WM_SUPPORT_NOTIFY_VIS_CHANGED
      WM__SendMsgNoData(hWin, WM_NOTIFY_VIS_CHANGED);             /* Notify window that visibility may have changed */
    #endif

    if (pWin->Status & WM_SF_INVALID) {
      GUI_MergeRect(&pWin->InvalidRect, &pWin->InvalidRect, &r);
    } else {
      pWin->InvalidRect = r;
      pWin->Status |= WM_SF_INVALID;
      WM__NumInvalidWindows++;
      /* Optional code: Call external routine to notify that drawing is required */
      #ifdef GUI_X_REDRAW
      {
        GUI_RECT r;
        r = pWin->Rect;
        if (WM__ClipAtParentBorders(&r,  hWin)) {
          GUI_X_REDRAW(); /* Call hook function to signal an invalidation */
        }
      }
      #endif
      GUI_X_SIGNAL_EVENT();
    }
    /* Debug code: shows invalid areas */
    #if (WM_SUPPORT_DIAG)
      if (WM__pfShowInvalid) {
        (WM__pfShowInvalid)(hWin);
      }
    #endif
  }
}

/*********************************************************************
*
*       _GetTopLevelWindow
*/
#if GUI_NUM_LAYERS > 1
static WM_HWIN _GetTopLevelWindow(WM_HWIN hWin) {
  WM_Obj* pWin;
  WM_HWIN hTop;
  while (hTop = hWin, pWin = WM_H2P(hWin), (hWin = pWin->hParent) != 0) {
  }
  return hTop;
}
#endif

/*********************************************************************
*
*       ResetNextDrawWin

  When drawing, we have to start at the bottom window !
*/
static void ResetNextDrawWin(void) {
  NextDrawWin = WM_HWIN_NULL;
}


/*********************************************************************
*
*       _GethDrawWin
*
* Return Window being drawn.
* Normally same as pAWin, except if overlaying transparent window is drawn
*
*/
static WM_HWIN _GethDrawWin(void) {
  WM_HWIN h;
  #if WM_SUPPORT_TRANSPARENCY
    if (WM__hATransWindow) {
      h = WM__hATransWindow;
    } else
  #endif
  {
    h = GUI_Context.hAWin;
  }
  return h;
}





/*********************************************************************
*
*       _SetClipRectUserIntersect
*/
static void _SetClipRectUserIntersect(const GUI_RECT* prSrc) {
  if (GUI_Context.WM__pUserClipRect == NULL) {
    LCD_SetClipRectEx(prSrc);
  } else {
    GUI_RECT r;
    r = *GUI_Context.WM__pUserClipRect;             
    WM__Client2Screen(WM_H2P(_GethDrawWin()), &r);     /* Convert User ClipRect into screen coordinates */
    /* Set intersection as clip rect */    
    GUI__IntersectRect(&r, prSrc);
    LCD_SetClipRectEx(&r);
  }
}


/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__ClipAtParentBorders
*
* Function:
*   Iterates over the window itself and all its ancestors.
*   Intersects all rectangles to
*   find out which part is actually visible.
*   Reduces the rectangle to the visible area.
*   This routines takes into account both the rectangles of the
*   ancestors as well as the WM_SF_ISVIS flag.
*
* Parameters
*   hWin    Obvious
*   pRect   Pointer to the rectangle to be clipped. May not be NULL.
*           The parameter is IN/OUT.
*           Note that the rectangle is clipped only if the return
*           value indicates a valid rectangle remains.
*
* Return value:
*   1: Something is or may be visible.
*   0: Nothing is visible (outside of ancestors, no desktop, hidden)
*/
int WM__ClipAtParentBorders(GUI_RECT* pRect, WM_HWIN hWin) {
  WM_Obj* pWin;

  /* Iterate up the window hierarchy.
     If the window is invisible, we are done.
     Clip at parent boarders.
     We are done with iterating if hWin has no parent.
  */
  do {
    pWin = WM_H2P(hWin);
    if ((pWin->Status & WM_SF_ISVIS) == 0) {
      return 0;                     /* Invisible */
    }
    GUI__IntersectRect(pRect, &pWin->Rect);  /* And clip on borders */
    if (pWin->hParent == 0) {
      break;   /* hWin is now the top level window which has no parent */
    }
    hWin = pWin->hParent;                    /* Go one level up (parent)*/
  } while (1);                               /* Only way out is in the loop. Required for efficiency, no bug, even though some compilers may complain. */
  
  /* Now check if the top level window is a desktop window. If it is not,
    then the window is not visible.
  */
  if (_DesktopHandle2Index(hWin) < 0) {
    return 0;           /* No desktop - (unattached) - Nothing to draw */
  }
  return 1;               /* Something may be visible */
}

/*********************************************************************
*
*       WM__ActivateClipRect
*/
void  WM__ActivateClipRect(void) {
  if (WM_IsActive) {
    _SetClipRectUserIntersect(&_ClipContext.CurRect);
  } else {    /* Window manager disabled, typically because meory device is active */
    GUI_RECT r;
    WM_Obj *pAWin;
    pAWin = WM_H2P(GUI_Context.hAWin);
    r = pAWin->Rect;
    #if WM_SUPPORT_TRANSPARENCY
      if (WM__hATransWindow) {
        WM__ClipAtParentBorders(&r, WM__hATransWindow);
      }
    #endif
    /* Take UserClipRect into account */
    _SetClipRectUserIntersect(&r);
  }
}




/*********************************************************************
*
*       WM__InsertWindowIntoList
*
* Routine describtion
*   This routine inserts the window in the list of child windows for
*   a particular parent window.
*   The window is placed on top of all siblings with the same level.
*/
void WM__InsertWindowIntoList(WM_HWIN hWin, WM_HWIN hParent) {
  int OnTop;
  WM_HWIN hi;
  WM_Obj * pWin;
  WM_Obj * pParent;
  WM_Obj * pi;

  if (hParent) {
    pWin = WM_H2P(hWin);
    pWin->hNext = 0;
    pWin->hParent = hParent;
    pParent = WM_H2P(hParent);
    OnTop   = pWin->Status & WM_CF_STAYONTOP;
    hi = pParent->hFirstChild;
    /* Put it at beginning of the list if there is no child */
    if (hi == 0) {   /* No child yet ... Makes things easy ! */
      pParent->hFirstChild = hWin;
      return;                         /* Early out ... We are done */
    }
    /* Put it at beginning of the list if first child is a TOP window and new one is not */
    pi = WM_H2P(hi);
    if (!OnTop) {
      if (pi->Status & WM_SF_STAYONTOP) {
        pWin->hNext = hi;
        pParent->hFirstChild = hWin;
        return;                         /* Early out ... We are done */
      }
    }
    /* Put it at the end of the list or before the last non "STAY-ON-TOP" child */
    do {
      WM_Obj* pNext;
      WM_HWIN hNext;
      if ((hNext = pi->hNext) == 0) {   /* End of sibling list ? */
        pi->hNext = hWin;             /* Then modify this last element to point to new one and we are done */
        break;
      }
      pNext = WM_H2P(hNext);
      if (!OnTop) {
        if (pNext->Status & WM_SF_STAYONTOP) {
          pi->hNext = hWin;
          pWin->hNext = hNext;
          break;
        }
      }
      pi = pNext;
    }  while (1);
    #if WM_SUPPORT_NOTIFY_VIS_CHANGED
      WM__NotifyVisChanged(hWin, &pWin->Rect);
    #endif
  }
}

/*********************************************************************
*
*       WM__RemoveWindowFromList
*/
void WM__RemoveWindowFromList(WM_HWIN hWin) {
  WM_HWIN hi, hParent;
  WM_Obj * pWin, * pParent, * pi;
  
  pWin = WM_H2P(hWin);
  hParent = pWin->hParent;
  if (hParent) {
    pParent = WM_H2P(hParent);
    hi = pParent->hFirstChild;
    if (hi == hWin) {
      pi = WM_H2P(hi);
      pParent->hFirstChild = pi->hNext;
    } else {
      while (hi) {
        pi = WM_H2P(hi);
        if (pi->hNext == hWin) {
          pi->hNext = pWin->hNext;
          break;
        }
        hi = pi->hNext;
      }
    }
  }
}

/*********************************************************************
*
*       WM__DetachWindow
*
* Detaches the given window. The window still exists, it keeps all
* children, but it is no longer visible since it is taken out of
* the tree of the desktop window.
*/
void WM__DetachWindow(WM_HWIN hWin) {
  WM_Obj* pWin;
  WM_HWIN hParent;
  pWin = WM_H2P(hWin);
  hParent = pWin->hParent;
  if (hParent) {
    WM__RemoveWindowFromList(hWin);
    /* Clear area used by this window */
    WM_InvalidateArea(&pWin->Rect);
    pWin->hParent = 0;
  }
}


/*********************************************************************
*
*       _DeleteAllChildren
*/
static void _DeleteAllChildren(WM_HWIN hChild) {
  while (hChild) {
    WM_Obj* pChild = WM_H2P(hChild);
    WM_HWIN hNext = pChild->hNext;
    WM_DeleteWindow(hChild);
    hChild = hNext;
  }
}

/*********************************************************************
*
*             Module internal routines
*
**********************************************************************
*/
/*********************************************************************
*
*       WM__Client2Screen
*/
void WM__Client2Screen(const WM_Obj* pWin, GUI_RECT *pRect) {
  GUI_MoveRect(pRect, pWin->Rect.x0, pWin->Rect.y0);
}

/*********************************************************************
*
*       WM__IsWindow
*/
int WM__IsWindow(WM_HWIN hWin) {
  WM_HWIN iWin;
  for (iWin = WM__FirstWin; iWin; iWin = WM_H2P(iWin)->hNextLin) {
    if (iWin == hWin) {
      return 1;
    }
  }
  return 0;
}

/*********************************************************************
*
*         WM__InvalidateAreaBelow

  Params: pRect  Rectangle in Absolute coordinates
*/
void WM__InvalidateAreaBelow(const GUI_RECT* pRect, WM_HWIN StopWin) {
  GUI_USE_PARA(StopWin);
  WM_InvalidateArea(pRect);      /* Can be optimized to spare windows above */
}

/*********************************************************************
*
*       WM_RemoveFromLinList
*/
void WM__RemoveFromLinList(WM_HWIN hWin) {
  WM_Obj* piWin;
  WM_HWIN hiWin;
  WM_HWIN hNext;
  for (hiWin = WM__FirstWin; hiWin; ) {
    piWin = WM_H2P(hiWin);
    hNext = piWin->hNextLin;
    if (hNext == hWin) {
      piWin->hNextLin = WM_H2P(hWin)->hNextLin;
      break;
    }
    hiWin = hNext;
  }
}

/*********************************************************************
*
*       _AddToLinList
*/
static void _AddToLinList(WM_HWIN hNew) {
  WM_Obj* pFirst;
  WM_Obj* pNew;
  if (WM__FirstWin) {
    pFirst = WM_H2P(WM__FirstWin);
    pNew   = WM_H2P(hNew);
    pNew->hNextLin = pFirst->hNextLin;
    pFirst->hNextLin = hNew;
  } else {
    WM__FirstWin = hNew;
  }
}

/*********************************************************************
*
*       WM__RectIsNZ
*
   Check if the rectangle has some content (is non-zero)
   Returns 0 if the Rectangle has no content, else 1.
*/
int WM__RectIsNZ(const GUI_RECT* pr) {
  if (pr->x0 > pr->x1)
    return 0;
  if (pr->y0 > pr->y1)
    return 0;
  return 1;
}

/*********************************************************************
*
*        _Findy1
*
*/
static void _Findy1(WM_HWIN iWin, GUI_RECT* pRect, GUI_RECT* pParentRect) {
  WM_Obj* pWin;
  for (; iWin; iWin = pWin->hNext) { 
    int Status = (pWin = WM_H2P(iWin))->Status;
    /* Check if this window affects us at all */    
    if (Status & WM_SF_ISVIS) {
      GUI_RECT rWinClipped;               /* Window rect, clipped to part inside of ancestors */
      if (pParentRect) {
        GUI__IntersectRects(&rWinClipped, &pWin->Rect, pParentRect);
      } else {
        rWinClipped = pWin->Rect;
      }
      /* Check if this window affects us at all */    
      if (GUI_RectsIntersect(pRect, &rWinClipped)) {
        if ((Status & WM_SF_HASTRANS) == 0) {
          if (pWin->Rect.y0 > pRect->y0) {
            ASSIGN_IF_LESS(pRect->y1, rWinClipped.y0 - 1);      /* Check upper border of window */
          } else {
            ASSIGN_IF_LESS(pRect->y1, rWinClipped.y1);        /* Check lower border of window */
          }
        } else {
          /* Check all children*/ 
          WM_HWIN hChild;
          WM_Obj* pChild;
          for (hChild = pWin->hFirstChild; hChild; hChild = pChild->hNext) {
            pChild = WM_H2P(hChild);
            _Findy1(hChild, pRect, &rWinClipped);
          }
        }
      }
    }
  }
}

/*********************************************************************
*
*        _Findx0
*/
static int _Findx0(WM_HWIN hWin, GUI_RECT* pRect, GUI_RECT* pParentRect) {
  WM_Obj* pWin;
  int r = 0;
  for (; hWin; hWin = pWin->hNext) { 
    int Status = (pWin = WM_H2P(hWin))->Status;
    if (Status & WM_SF_ISVIS) {           /* If window is not visible, it can be safely ignored */
      GUI_RECT rWinClipped;               /* Window rect, clipped to part inside of ancestors */
      if (pParentRect) {
        GUI__IntersectRects(&rWinClipped, &pWin->Rect, pParentRect);
      } else {
        rWinClipped = pWin->Rect;
      }
      /* Check if this window affects us at all */    
      if (GUI_RectsIntersect(pRect, &rWinClipped)) {
        if ((Status & WM_SF_HASTRANS) == 0) {
          pRect->x0 = rWinClipped.x1+1;
          r = 1;
        } else {
          /* Check all children */
          WM_HWIN hChild;
          WM_Obj* pChild;
          for (hChild = pWin->hFirstChild; hChild; hChild = pChild->hNext) {
            pChild = WM_H2P(hChild);
            if (_Findx0(hChild, pRect, &rWinClipped)) {
              r = 1;
            }
          }
        }
      }
    }
  }
  return r;
}

/*********************************************************************
*
*        _Findx1
*/
static void _Findx1(WM_HWIN hWin, GUI_RECT* pRect, GUI_RECT* pParentRect) {
  WM_Obj* pWin;
  for (; hWin; hWin = pWin->hNext) { 
    int Status = (pWin = WM_H2P(hWin))->Status;
    if (Status & WM_SF_ISVIS) {           /* If window is not visible, it can be safely ignored */
      GUI_RECT rWinClipped;               /* Window rect, clipped to part inside of ancestors */
      if (pParentRect) {
        GUI__IntersectRects(&rWinClipped, &pWin->Rect, pParentRect);
      } else {
        rWinClipped = pWin->Rect;
      }
      /* Check if this window affects us at all */    
      if (GUI_RectsIntersect(pRect, &rWinClipped)) {
        if ((Status & WM_SF_HASTRANS) == 0) {
          pRect->x1 = rWinClipped.x0-1;
        } else {
          /* Check all children */
          WM_HWIN hChild;
          WM_Obj* pChild;
          for (hChild = pWin->hFirstChild; hChild; hChild = pChild->hNext) {
            pChild = WM_H2P(hChild);
            _Findx1(hChild, pRect, &rWinClipped);
          }
        }
      }
    }
  }
}

/*********************************************************************
*
*       Sending messages
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_SendMessage
*/
void WM_SendMessage(WM_HWIN hWin, WM_MESSAGE* pMsg) {
  if (hWin) {
    WM_Obj* pWin;
    WM_LOCK();
    pWin = WM_H2P(hWin);
    if (pWin->cb != NULL) {
      pMsg->hWin = hWin;
      (*pWin->cb)(pMsg);
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       WM__SendMsgNoData
*/
void WM__SendMsgNoData(WM_HWIN hWin, U8 MsgId) {
  WM_MESSAGE Msg;
  Msg.hWin  = hWin;
  Msg.MsgId = MsgId;
  WM_SendMessage(hWin, &Msg);
}

/*********************************************************************
*
*       WM__GetClientRectWin
*
  Get client rectangle in windows coordinates. This means that the
  upper left corner is always at (0,0). 
*/
void WM__GetClientRectWin(const WM_Obj* pWin, GUI_RECT* pRect) {
  pRect->x0 = pRect->y0 = 0;
  pRect->x1 = pWin->Rect.x1 - pWin->Rect.x0;
  pRect->y1 = pWin->Rect.y1 - pWin->Rect.y0;
}

/*********************************************************************
*
*       WM__GetInvalidRectAbs
*/
static void WM__GetInvalidRectAbs(WM_Obj* pWin, GUI_RECT* pRect) {
  *pRect = pWin->InvalidRect;
}

/*********************************************************************
*
*       Invalidation functions
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_InvalidateRect
*
*  Invalidate a section of the window. The optional rectangle
*  contains client coordinates, which are independent of the
*  position of the window on the logical desktop area.
*/
void WM_InvalidateRect(WM_HWIN hWin, const GUI_RECT*pRect) {
  GUI_RECT r;
  WM_Obj* pWin;
  int Status;
  if (hWin) {
    WM_LOCK();
    pWin = WM_H2P(hWin);
    Status = pWin->Status;
    if (Status & WM_SF_ISVIS) {
      r = pWin->Rect;
      if (pRect) {
        GUI_RECT rPara;
        rPara = *pRect;
        WM__Client2Screen(pWin, &rPara);
        GUI__IntersectRect(&r, &rPara);
      }
      if (WM__ClipAtParentBorders(&r, hWin)) {      /* Optimization that saves invalidation if window area is not visible ... Not required */
        if ((Status & (WM_SF_HASTRANS | WM_SF_CONST_OUTLINE)) == WM_SF_HASTRANS) {
          WM__InvalidateAreaBelow(&r, hWin);        /* Can be optimized to spare windows above */
        } else {
          _Invalidate1Abs(hWin, &r);
        }
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*        WM_InvalidateWindow
*
  Invalidates an entire window.
*/
void WM_InvalidateWindow(WM_HWIN hWin) {
  WM_InvalidateRect(hWin, NULL);
}

/*********************************************************************
*
*        WM_InvalidateArea

  Invalidate a certain section of the display. One main reason for this is
  that the top window has been moved or destroyed.
  The coordinates given are absolute coordinates (desktop coordinates)
*/
void WM_InvalidateArea(const GUI_RECT* pRect) {
  WM_HWIN   hWin;
  WM_LOCK();
  /* Iterate over all windows */
  for (hWin = WM__FirstWin; hWin; hWin = WM_H2P(hWin)->hNextLin) {
    _Invalidate1Abs(hWin, pRect);
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       manage windows stack
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_CreateWindowAsChild
*/
WM_HWIN WM_CreateWindowAsChild( int x0, int y0, int width, int height
                               ,WM_HWIN hParent, U16 Style, WM_CALLBACK* cb
                               ,int NumExtraBytes) {
  WM_Obj* pWin;
  WM_HWIN hWin;
  WM_ASSERT_NOT_IN_PAINT();
  WM_LOCK();
  Style |= WM__CreateFlags;
  /* Default parent is Desktop 0 */
  if (!hParent) {
    if (WM__NumWindows) {
    #if GUI_NUM_LAYERS == 1
      hParent = WM__ahDesktopWin[0];
    #else
      hParent = WM__ahDesktopWin[GUI_Context.SelLayer];
    #endif
    }
  }
  if (hParent == WM_UNATTACHED) {
    hParent = WM_HWIN_NULL;
  }  
  if (hParent) {
    WM_Obj* pParent = WM_H2P(hParent);
    x0 += pParent->Rect.x0;
    y0 += pParent->Rect.y0;
    if (width==0) {
      width = pParent->Rect.x1 - pParent->Rect.x0+1;
    }
    if (height==0) {
      height = pParent->Rect.y1 - pParent->Rect.y0+1;
    }
  }
  if ((hWin = (WM_HWIN) GUI_ALLOC_AllocZero(NumExtraBytes + sizeof(WM_Obj))) == 0) {
    GUI_DEBUG_ERROROUT("WM_CreateWindow: No memory to create window");
  } else {
    WM__NumWindows++;
    pWin = WM_H2P(hWin);
    pWin->Rect.x0 = x0;
    pWin->Rect.y0 = y0;
    pWin->Rect.x1 = x0 + width - 1;
    pWin->Rect.y1 = y0 + height - 1;
    pWin->cb = cb;
    /* Copy the flags which can simply be accepted */
    pWin->Status |= (Style & (WM_CF_SHOW |
                              WM_SF_MEMDEV |
                              WM_CF_MEMDEV_ON_REDRAW |
                              WM_SF_STAYONTOP |
                              WM_SF_CONST_OUTLINE |
                              WM_SF_HASTRANS |
                              WM_CF_ANCHOR_RIGHT |
                              WM_CF_ANCHOR_BOTTOM |
                              WM_CF_ANCHOR_LEFT |
                              WM_CF_ANCHOR_TOP |
                              WM_CF_LATE_CLIP));
    /* Add to linked lists */
    _AddToLinList(hWin);
    WM__InsertWindowIntoList(hWin, hParent);
    /* Activate window if WM_CF_ACTIVATE is specified */
    if (Style & WM_CF_ACTIVATE) {
      WM_SelectWindow(hWin);  /* This is not needed if callbacks are being used, but it does not cost a lot and makes life easier ... */
    }
    /* Handle the Style flags, one at a time */
    #if WM_SUPPORT_TRANSPARENCY
      if (Style & WM_SF_HASTRANS) {
        WM__TransWindowCnt++;          /* Increment counter for transparency windows */
      }
    #endif
    if (Style & WM_CF_BGND) {
      WM_BringToBottom(hWin);
    }
    if (Style & WM_CF_SHOW) {
      pWin->Status |= WM_SF_ISVIS;  /* Set Visibility flag */
      WM_InvalidateWindow(hWin);    /* Mark content as invalid */
    }
    WM__SendMsgNoData(hWin, WM_CREATE);
  }
  WM_UNLOCK();
  return hWin;
}

/*********************************************************************
*
*       WM_CreateWindow
*/
WM_HWIN WM_CreateWindow(int x0, int y0, int width, int height, U16 Style, WM_CALLBACK* cb, int NumExtraBytes) {
  return WM_CreateWindowAsChild(x0,y0,width,height, 0 /* No parent */,  Style, cb, NumExtraBytes);
}

/*********************************************************************
*
*       Delete window
*
**********************************************************************
*/
/*********************************************************************
*
*       WM_DeleteWindow
*/
void WM_DeleteWindow (WM_HWIN hWin) {
  WM_Obj* pWin;
  if (!hWin) {
    return;
  }
  WM_ASSERT_NOT_IN_PAINT();
  WM_LOCK();
  if (WM__IsWindow(hWin)) {
    pWin = WM_H2P(hWin);
    ResetNextDrawWin();              /* Make sure the window will no longer receive drawing messages */
  /* Make sure that focus is set to an existing window */
    if (WM__hWinFocus == hWin) {
      WM__hWinFocus = 0;
    }
    if (WM__hCapture == hWin) {
      WM__hCapture = 0;
    }
    /* check if critical handles are affected. If so, reset the window handle to 0 */
    _CheckCriticalHandles(hWin);
    /* Inform parent */
    WM_NotifyParent(hWin, WM_NOTIFICATION_CHILD_DELETED);
    /* Delete all children */
    _DeleteAllChildren(pWin->hFirstChild);
    #if WM_SUPPORT_NOTIFY_VIS_CHANGED
      WM__SendMsgNoData(hWin, WM_NOTIFY_VIS_CHANGED);             /* Notify window that visibility may have changed */
    #endif
    /* Send WM_DELETE message to window in order to inform window itself */
    WM__SendMsgNoData(hWin, WM_DELETE);     /* tell window about it */
    WM__DetachWindow(hWin);
    /* Remove window from window stack */
    WM__RemoveFromLinList(hWin);
    /* Handle transparency counter if necessary */
    #if WM_SUPPORT_TRANSPARENCY
      if (pWin->Status & WM_SF_HASTRANS) {
        WM__TransWindowCnt--;
      }
    #endif
    /* Make sure window is no longer counted as invalid */
    if (pWin->Status & WM_SF_INVALID) {
      WM__NumInvalidWindows--;
    }
  /* Free window memory */
    WM__NumWindows--;
    GUI_ALLOC_Free(hWin);
  /* Select a valid window */
    WM_SelectWindow(WM__FirstWin);
  } else {
    GUI_DEBUG_WARN("WM_DeleteWindow: Invalid handle");
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       WM_SelectWindow
*
*  Sets the active Window. The active Window is the one that is used for all
*  drawing (and text) operations.
*/
WM_HWIN WM_SelectWindow(WM_HWIN  hWin) {
  WM_HWIN hWinPrev;
  WM_Obj* pObj;

  WM_ASSERT_NOT_IN_PAINT();
  WM_LOCK();
  hWinPrev = GUI_Context.hAWin;
  if (hWin == 0) {
    hWin = WM__FirstWin;
  }
  /* Select new window */
  GUI_Context.hAWin = hWin;
  #if GUI_NUM_LAYERS > 1
  {
    WM_HWIN hTop;
    int LayerIndex;
    hTop = _GetTopLevelWindow(hWin);
    LayerIndex = _DesktopHandle2Index(hTop);
    if (LayerIndex >= 0) {
      GUI_SelectLayer(LayerIndex);
    }
  }
  #endif
  pObj = WM_H2P(hWin);
  LCD_SetClipRectMax();             /* Drawing operations will clip ... If WM is deactivated, allow all */
  GUI_Context.xOff = pObj->Rect.x0;
  GUI_Context.yOff = pObj->Rect.y0;
  WM_UNLOCK();
  return hWinPrev;
}

/*********************************************************************
*
*       WM_GetActiveWindow
*/
WM_HWIN WM_GetActiveWindow(void) {
  return GUI_Context.hAWin;
}


/*********************************************************************
*
*       IVR calculation
*
**********************************************************************

IVRs are invalid rectangles. When redrawing, only the portion of the
window which is
  a) within the window-rectangle
  b) not covered by an other window
  c) marked as invalid
  is actually redrawn. Unfortunately, this section is not always
  rectangular. If the window is partially covered by an other window,
  it consists of the sum of multiple rectangles. In all drawing
  operations, we have to iterate over every one of these rectangles in
  order to make sure the window is drawn completly.
Function works as follows:
  STEP 1: - Set upper left coordinates to next pixel. If end of line (right border), goto next line -> (r.x0, r.y0)
  STEP 2: - Check if we are done, return if we are.
  STEP 3: - If we are at the left border, find max. heigtht (r.y1) by iterating over windows above
  STEP 4: - Find x0 for the given y0, y1 by iterating over windows above
  STEP 5: - If r.x0 out of right border, this stripe is done. Set next stripe and goto STEP 2
  STEP 6: - Find r.x1. We have to Iterate over all windows which are above
*/

/*********************************************************************
*
*       _FindNext_IVR
*/
#if WM_SUPPORT_OBSTRUCT
static int _FindNext_IVR(void) {
  WM_HMEM hParent;
  GUI_RECT r;
  WM_Obj* pAWin;
  WM_Obj* pParent;
  r = _ClipContext.CurRect;  /* temps  so we do not have to work with pointers too much */
  /*
     STEP 1:
       Set the next position which could be part of the next IVR
       This will be the first unhandle pixel in reading order, i.e. next one to the right
       or next one down if we are at the right border.
  */
  if (_ClipContext.Cnt == 0) {       /* First IVR starts in upper left */
    r.x0 = _ClipContext.ClientRect.x0;
    r.y0 = _ClipContext.ClientRect.y0;
  } else {
    r.x0 = _ClipContext.CurRect.x1+1;
    r.y0 = _ClipContext.CurRect.y0;
    if (r.x0 > _ClipContext.ClientRect.x1) {
NextStripe:  /* go down to next stripe */
      r.x0 = _ClipContext.ClientRect.x0;
      r.y0 = _ClipContext.CurRect.y1+1;
    }
  }
  /*
     STEP 2:
       Check if we are done completely.
  */
  if (r.y0 >_ClipContext.ClientRect.y1) {
    return 0;
  }
  /* STEP 3:
       Find out the max. height (r.y1) if we are at the left border.
       Since we are using the same height for all IVRs at the same y0,
       we do this only for the leftmost one.
  */
  pAWin = WM_H2P(GUI_Context.hAWin);
  if (r.x0 == _ClipContext.ClientRect.x0) {
    r.y1 = _ClipContext.ClientRect.y1;
    r.x1 = _ClipContext.ClientRect.x1;
    /* Iterate over all windows which are above */
    /* Check all siblings above (Iterate over Parents and top siblings (hNext) */
    for (hParent = GUI_Context.hAWin; hParent; hParent = pParent->hParent) {
      pParent = WM_H2P(hParent);
      _Findy1(pParent->hNext, &r, NULL);
    }
    /* Check all children */
    _Findy1(pAWin->hFirstChild, &r, NULL);
  }
  /* 
    STEP 4
      Find out x0 for the given y0, y1 by iterating over windows above.
      if we find one that intersects, adjust x0 to the right.
  */
Find_x0:
  r.x1 = r.x0;
  /* Iterate over all windows which are above */
  /* Check all siblings above (siblings of window, siblings of parents, etc ...) */
  #if 0   /* This is a planned, but not yet released optimization */
    if (Status & WM_SF_DONT_CLIP_SIBLINGS)
    {
      hParent = pAWin->hParent;
    } else
  #endif
  {
    hParent = GUI_Context.hAWin;
  }
  for (; hParent; hParent = pParent->hParent) {
    pParent = WM_H2P(hParent);
    if (_Findx0(pParent->hNext, &r, NULL)) {
      goto Find_x0;
    }
  }
  /* Check all children */
  if (_Findx0(pAWin->hFirstChild, &r, NULL)) {
    goto Find_x0;
  }
  /* 
   STEP 5:
     If r.x0 out of right border, this stripe is done. Set next stripe and goto STEP 2
     Find out x1 for the given x0, y0, y1
  */
  r.x1 = _ClipContext.ClientRect.x1;
  if (r.x1 < r.x0) {/* horizontal border reached ? */
    _ClipContext.CurRect = r;
    goto NextStripe;
  }    
  /* 
   STEP 6:
     Find r.x1. We have to Iterate over all windows which are above
  */
  /* Check all siblings above (Iterate over Parents and top siblings (hNext) */
  #if 0   /* This is a planned, but not yet released optimization */
    if (Status & WM_SF_DONT_CLIP_SIBLINGS)
    {
      hParent = pAWin->hParent;
    } else
  #endif
  {
    hParent = GUI_Context.hAWin;
  }
  for (; hParent; hParent = pParent->hParent) {
    pParent = WM_H2P(hParent);
    _Findx1(pParent->hNext, &r, NULL);
  }
  /* Check all children */
  _Findx1(pAWin->hFirstChild, &r, NULL);
  /* We are done. Return the rectangle we found in the _ClipContext. */
  if (_ClipContext.Cnt >200) {
    return 0;  /* error !!! This should not happen !*/
  }
  _ClipContext.CurRect = r;
  return 1;  /* IVR is valid ! */
}

#else

static int _FindNext_IVR(void) {
  if (_ClipContext.Cnt ==0) {
    _ClipContext.CurRect = GUI_Context.pAWin->Rect;
    return 1;  /* IVR is valid ! */
  }
  return 0;  /* Nothing left to draw */
}
#endif

/*********************************************************************
*
*       WM_GetNextIVR

  Sets the next clipping rectangle. If a valid one has
  been found (and set), 1 is returned in order to indicate
  that the drawing operation needs to be executed.
  Returning 0 signals that we have iterated over all
  rectangles.

  Returns: 0 if no valid rectangle is found
           1 if rectangle has been found
*/
int  WM__GetNextIVR(void) {
  #if GUI_SUPPORT_CURSOR
    static char _CursorHidden;
  #endif
  /* If WM is not active, we have no rectangles to return */
  if (WM_IsActive==0) {
    return 0;
  }
  if (_ClipContext.EntranceCnt > 1) {
    _ClipContext.EntranceCnt--;
    return 0;
  }
  #if GUI_SUPPORT_CURSOR
    if (_CursorHidden) {
      _CursorHidden = 0;
      (*GUI_CURSOR_pfTempUnhide) ();
    }
  #endif
  ++_ClipContext.Cnt;
  /* Find next rectangle and use it as ClipRect */
  if (!_FindNext_IVR()) {
    _ClipContext.EntranceCnt--;  /* This search is over ! */
    return 0;        /* Could not find an other one ! */
  }
  WM__ActivateClipRect();
  /* Hide cursor if necessary */
  #if GUI_SUPPORT_CURSOR
    if (GUI_CURSOR_pfTempHide) {
      _CursorHidden = (*GUI_CURSOR_pfTempHide) ( &_ClipContext.CurRect);
    }
  #endif
  return 1;
}

/*********************************************************************
*
*       WM__InitIVRSearch

  This routine is called from the clipping level
  (the WM_ITERATE_START macro) when starting an iteration over the
  visible rectangles.

  Return value:
    0 : There is no valid rectangle (nothing to do ...)
    1 : There is a valid rectangle
*/
int WM__InitIVRSearch(const GUI_RECT* pMaxRect) {
  GUI_RECT r;
  WM_Obj* pAWin;
  GUI_ASSERT_LOCK();   /* GUI_LOCK must have been "called" before entering this (normally done indrawing routine) */
   /* If WM is not active -> nothing to do, leave cliprect alone */
  if (WM_IsActive==0) {
    WM__ActivateClipRect();
    return 1;
  }
  /* If we entered multiple times, leave Cliprect alone */
  if (++_ClipContext.EntranceCnt > 1)
    return 1;
  pAWin = WM_H2P(GUI_Context.hAWin);
  _ClipContext.Cnt        = -1;
 /* When using callback mechanism, it is legal to reduce drawing
    area to the invalid area ! */
  if (WM__PaintCallbackCnt) {
    WM__GetInvalidRectAbs(pAWin, &r);
  } else {  /* Not using callback mechanism, therefor allow entire rectangle */
    if (pAWin->Status & WM_SF_ISVIS) {
      r = pAWin->Rect;
    } else {
      --_ClipContext.EntranceCnt;
      return 0;  /* window is not even visible ! */
    }
  }
  /* If the drawing routine has specified a rectangle, use it to reduce the rectangle */
  if (pMaxRect) {
    GUI__IntersectRect(&r, pMaxRect);
  }
  /* If user has reduced the cliprect size, reduce the rectangle */
  if (GUI_Context.WM__pUserClipRect) {
    WM_Obj* pWin = pAWin;
    GUI_RECT rUser = *(GUI_Context.WM__pUserClipRect);
    #if WM_SUPPORT_TRANSPARENCY
      if (WM__hATransWindow) {
        pWin = WM_H2P(WM__hATransWindow);
      }   
    #endif
    WM__Client2Screen(pWin, &rUser);
    GUI__IntersectRect(&r, &rUser);
  }
  /* For transparent windows, we need to further reduce the rectangle */
  #if WM_SUPPORT_TRANSPARENCY
    if (WM__hATransWindow) {
      if (WM__ClipAtParentBorders(&r, WM__hATransWindow) == 0) {
        --_ClipContext.EntranceCnt;
        return 0;           /* Nothing to draw */
      }
    }
  #endif
  /* Iterate over all ancestors and clip at their borders. If there is no visible part, we are done */
  if (WM__ClipAtParentBorders(&r, GUI_Context.hAWin) == 0) {
    --_ClipContext.EntranceCnt;
    return 0;           /* Nothing to draw */
  }
  /* Store the rectangle and find the first rectangle of the area */
  _ClipContext.ClientRect = r;
  return WM__GetNextIVR();
}

/*********************************************************************
*
*       WM_SetDefault
*
  This routine sets the defaults for WM and the layers below.
  It is used before a drawing routine is called in order to
  make sure that defaults are set (in case the default settings
  had been altered before by the application)
*/
void WM_SetDefault(void) {
  GL_SetDefault();
  GUI_Context.WM__pUserClipRect = NULL;   /* No add. clipping */
}

/*********************************************************************
*
*       _Paint1
*/
static void _Paint1(WM_HWIN hWin, WM_Obj* pWin) {
  int Status = pWin->Status;
  /* Send WM_PAINT if window is visible and a callback is defined */
  if ((pWin->cb != NULL)  && (Status & WM_SF_ISVIS)) {
    WM_MESSAGE Msg;
    WM__PaintCallbackCnt++;
    if (Status & WM_SF_LATE_CLIP) {
      Msg.hWin   = hWin;
      Msg.MsgId  = WM_PAINT;
      Msg.Data.p = (GUI_RECT*)&pWin->InvalidRect;
      WM_SetDefault();
      WM_SendMessage(hWin, &Msg);
    } else {
      WM_ITERATE_START(&pWin->InvalidRect) {
        Msg.hWin   = hWin;
        Msg.MsgId  = WM_PAINT;
        Msg.Data.p = (GUI_RECT*)&pWin->InvalidRect;
        WM_SetDefault();
        WM_SendMessage(hWin, &Msg);
      } WM_ITERATE_END();
    }
    WM__PaintCallbackCnt--;
  }
}
/*********************************************************************
*
*       _Paint1Trans
*
* Purpose:
*   Draw a transparent window as part of an other one (the active window: pAWin).
*   This is required because transparent windows are drawn as part of their
*   non-transparent parents.
* Return value:
*   0 if nothing was drawn (no invalid rect)
*   1 if something was drawn (invalid rect exists)
* Add. info:
*   It is important to restore the modified settings, especially the invalid rectangle
*   of the window. The invalid rectangle needs to be set, as it is passed as add. info
*   to the callback on WM_PAINT.
*   On traditional transparent windows, the transparent window is never drawn on its own,
*   so there is no need to restore the invalid rectangle.
*   However, with WM_SF_CONST_OUTLINE, the window itself may need to be redrawn because it
*   can be invalid. Modifying the invalid rectangle would lead to not updating the window
*   in the worst case.
*/

#if WM_SUPPORT_TRANSPARENCY
static int _Paint1Trans(WM_HWIN hWin, WM_Obj* pWin) {
  int xPrev, yPrev;
  WM_Obj* pAWin = WM_H2P(GUI_Context.hAWin);
  /* Check if we need to do any drawing */
  if (GUI_RectsIntersect(&pAWin->InvalidRect, &pWin->Rect)) {
    /* Save old values */
    xPrev = GUI_Context.xOff;
    yPrev = GUI_Context.yOff;
    /* Set values for the current (transparent) window, rather than the one below */
    GUI__IntersectRects(&pWin->InvalidRect, &pWin->Rect, &pAWin->InvalidRect);
    WM__hATransWindow = hWin;
    GUI_Context.xOff = pWin->Rect.x0;
    GUI_Context.yOff = pWin->Rect.y0;
    /* Do the actual drawing ... */
    _Paint1(hWin, pWin);
    /* Restore settings */
    WM__hATransWindow = 0;
    GUI_Context.xOff = xPrev;
    GUI_Context.yOff = yPrev;
    return 1;                       /* Some drawing took place */
  }
  return 0;                         /* No invalid area, so nothing was drawn */
}
#endif

/*********************************************************************
*
*       _PaintTransChildren
*
* Purpose:
*   Paint transparent children. This function is obviously required
*   only if there are transparent windows.
* Function:  Obvious
* Parameter: Obvious
* Returns:   ---
*/
#if WM_SUPPORT_TRANSPARENCY
static void _PaintTransChildren(WM_Obj* pWin) {
  WM_HWIN hChild;
  WM_Obj* pChild;
  if (pWin->Status & WM_SF_ISVIS) {
    for (hChild = pWin->hFirstChild; hChild; hChild = pChild->hNext) {
      pChild = WM_H2P(hChild);
      if ((pChild->Status & (WM_SF_HASTRANS | WM_SF_ISVIS))   /* Transparent & visible ? */
		                ==  (WM_SF_HASTRANS | WM_SF_ISVIS)) {
        /* Set invalid area of the window to draw */
        if (GUI_RectsIntersect(&pChild->Rect, &pWin->InvalidRect)) {
          GUI_RECT InvalidRectPrev;
          InvalidRectPrev = pWin->InvalidRect;
          if(_Paint1Trans(hChild, pChild)) {
            _PaintTransChildren(pChild);
          }
          pWin->InvalidRect = InvalidRectPrev;
        }
      }
    }
  }
}
#endif

/*********************************************************************
*
*       _PaintTransTopSiblings
*
* Purpose:
*   Paint transparent top siblings. This function is obviously required
*   only if there are transparent windows.
* Function:  Obvious
* Parameter: Obvious
* Returns:   ---
*/
#if WM_SUPPORT_TRANSPARENCY
static void _PaintTransTopSiblings(WM_HWIN hWin, WM_Obj* pWin) {
  WM_HWIN hParent;
  WM_Obj* pParent;
  hParent = pWin->hParent;
  hWin = pWin->hNext;
  while (hParent) { /* Go hierarchy up to desktop window */
    for (; hWin; hWin = pWin->hNext) {
      pWin = WM_H2P(hWin);
      /* paint window if it is transparent & visible */
      if ((pWin->Status & (WM_SF_HASTRANS | WM_SF_ISVIS)) ==  (WM_SF_HASTRANS | WM_SF_ISVIS)) {
        _Paint1Trans(hWin, pWin);
      }
      /* paint transparent & visible children */
      _PaintTransChildren(pWin);
    }
    pParent = WM_H2P(hParent);
    hWin = pParent->hNext;
    hParent = pParent->hParent;
  }
}
#endif

/*********************************************************************
*
*       Callback for Paint message
*
* This callback is used by the window manger in conjunction with
* banding memory devices. A pointer to this routine is given to
* the banding memory device. This callback in turn will send the
* paint message to the window.
*
**********************************************************************
*/

/*********************************************************************
*
*       WM__PaintWinAndOverlays
*
* Purpose
*   Paint the given window and all overlaying windows
*   (transparent children and transparent top siblings)
*/
void WM__PaintWinAndOverlays(WM_PAINTINFO* pInfo) {
  WM_HWIN hWin;
  WM_Obj* pWin;
  hWin = pInfo->hWin;
  pWin = pInfo->pWin;
  #if WM_SUPPORT_TRANSPARENCY
    /* Transparent windows without const outline are drawn as part of the background and can be skipped. */
    if ((pWin->Status & (WM_SF_HASTRANS | WM_SF_CONST_OUTLINE)) != WM_SF_HASTRANS) {
  #endif
  _Paint1(hWin, pWin);    /* Draw the window itself */
  #if WM_SUPPORT_TRANSPARENCY
    }
    if (WM__TransWindowCnt != 0) {
      _PaintTransChildren(pWin);       /* Draw all transparent children */
      _PaintTransTopSiblings(hWin, pWin);    /* Draw all transparent top level siblings */
    }
  #endif
}

/*********************************************************************
*
*       _cbPaintMemDev
*
* Purpose:
*   This is the routine called by the banding memory device. It calls
*   the same _cbPaint Routine which is also used when drawing directly;
*   the only add. work done is adjustment of the invalid rectangle.
*   This way the invalid rectangle visible by the window callback function
*   is limited to the current band, allowing the callback to optimize
*   better.
*/
#if GUI_SUPPORT_MEMDEV
static void _cbPaintMemDev(void* p) {
  GUI_RECT Rect;
  WM_Obj* pWin = WM_H2P(GUI_Context.hAWin);
  Rect = pWin->InvalidRect;
  pWin->InvalidRect = GUI_Context.ClipRect;
  WM__PaintWinAndOverlays((WM_PAINTINFO*)p);
  pWin->InvalidRect = Rect;
}
#endif

/*********************************************************************
*
*       _Paint
  Returns:
    1: a window has been redrawn
    0: No window has been drawn  
*/
static int _Paint(WM_HWIN hWin, WM_Obj* pWin) {
  int Ret = 0;
  if (pWin->Status & WM_SF_INVALID) {
    if (pWin->cb) {
      if (WM__ClipAtParentBorders(&pWin->InvalidRect, hWin)) {
        WM_PAINTINFO Info;
        Info.hWin = hWin;
        Info.pWin = pWin;
        WM_SelectWindow(hWin);
        #if GUI_SUPPORT_MEMDEV
          if (pWin->Status & WM_SF_MEMDEV) {
            int Flags;
            GUI_RECT r = pWin->InvalidRect;
            Flags = (pWin->Status & WM_SF_HASTRANS) ? GUI_MEMDEV_HASTRANS : GUI_MEMDEV_NOTRANS;
            /*
             * Currently we treat a desktop window as transparent, because per default it does not repaint itself.
             */
            if (pWin->hParent == 0) {
              Flags = GUI_MEMDEV_HASTRANS;
            }
            GUI_MEMDEV_Draw(&r, _cbPaintMemDev, &Info, 0, Flags);
          } else
        #endif
        {
          WM__PaintWinAndOverlays(&Info);
          Ret = 1;    /* Something has been done */
        }
      }
    }
    /* We purposly clear the invalid flag after painting so we can still query the invalid rectangle while painting */
    pWin->Status &=  ~WM_SF_INVALID; /* Clear invalid flag */
    if (pWin->Status & WM_CF_MEMDEV_ON_REDRAW) {
      pWin->Status |= WM_CF_MEMDEV;
    }
    WM__NumInvalidWindows--;
  }
  return Ret;      /* Nothing done */
}

/*********************************************************************
*
*       _DrawNext
*/
static void _DrawNext(void) {
  int UpdateRem = 1;
  WM_HWIN iWin = (NextDrawWin == WM_HWIN_NULL) ? WM__FirstWin : NextDrawWin;
  GUI_CONTEXT ContextOld;
  GUI_SaveContext(&ContextOld);
  /* Make sure the next window to redraw is valid */
  for (; iWin && UpdateRem; ) {
    WM_Obj* pWin = WM_H2P(iWin);
    if (_Paint(iWin, pWin)) {
      UpdateRem--;  /* Only the given number of windows at a time ... */
    }
    iWin = pWin->hNextLin;
  }  
  NextDrawWin = iWin;   /* Remember the window */
  GUI_RestoreContext(&ContextOld);
}

/*********************************************************************
*
*       WM_Exec1
*/
int WM_Exec1(void) {
  /* Poll PID if necessary */
  if (WM_pfPollPID) {
    WM_pfPollPID();
  }
  if (WM_pfHandlePID) {
    if (WM_pfHandlePID())
      return 1;               /* We have done something ... */
  }
  if (GUI_PollKeyMsg()) {
    return 1;               /* We have done something ... */
  }
  if (WM_IsActive && WM__NumInvalidWindows) {
    WM_LOCK();
    _DrawNext();
    WM_UNLOCK();
    return 1;               /* We have done something ... */
  }
  return 0;                  /* There was nothing to do ... */
}

/*********************************************************************
*
*       WM_Exec
*/
int WM_Exec(void) {
  int r = 0;
  while (WM_Exec1()) {
    r = 1;                  /* We have done something */
  }
  return r;
}

/*********************************************************************
*
*       cbBackWin
*
* Purpose
*   Callback for background window
*
*/
static void cbBackWin( WM_MESSAGE* pMsg) {
  const WM_KEY_INFO* pKeyInfo;
  switch (pMsg->MsgId) {
  case WM_KEY:
    pKeyInfo = (const WM_KEY_INFO*)pMsg->Data.p;
    if (pKeyInfo->PressedCnt == 1) {
      GUI_StoreKey(pKeyInfo->Key);
    }
    break;
  case WM_PAINT:
    {
      int LayerIndex;
      #if GUI_NUM_LAYERS > 1
        LayerIndex = _DesktopHandle2Index(pMsg->hWin);
      #else
        LayerIndex = 0;
      #endif
      if (WM__aBkColor[LayerIndex] != GUI_INVALID_COLOR) {
        GUI_SetBkColor(WM__aBkColor[LayerIndex]);
        GUI_Clear();
      }
    }
  default:
    WM_DefaultProc(pMsg);
  }
}

/*********************************************************************
*
*       WM_Activate
*/
void WM_Activate(void) {
  WM_IsActive = 1;       /* Running */
}

/*********************************************************************
*
*       WM_Deactivate
*/
void WM_Deactivate(void) {
  WM_IsActive = 0;       /* No clipping performed by WM */
  WM_LOCK();
  LCD_SetClipRectMax();
  WM_UNLOCK();
}

/*********************************************************************
*
*       WM_DefaultProc
*
* Purpose
*   Default callback for windows
*   Any window should call this routine in the "default" part of the
*   its callback function for messages it does not handle itself.
*
*/
void WM_DefaultProc(WM_MESSAGE* pMsg) {
  WM_HWIN hWin = pMsg->hWin;
  const void *p = pMsg->Data.p;
  WM_Obj* pWin = WM_H2P(hWin);
  /* Exec message */
  switch (pMsg->MsgId) {
  case WM_GET_INSIDE_RECT:      /* return client window in absolute (screen) coordinates */
    WM__GetClientRectWin(pWin, (GUI_RECT*)p);
    break;
  case WM_GET_CLIENT_WINDOW:      /* return handle to client window. For most windows, there is no seperate client window, so it is the same handle */
    pMsg->Data.v = (int)hWin;
    return;                       /* Message handled */
  case WM_KEY:
    WM_SendToParent(hWin, pMsg);
    return;                       /* Message handled */
   case WM_GET_BKCOLOR:
    pMsg->Data.Color = GUI_INVALID_COLOR;
    return;                       /* Message handled */
  case WM_NOTIFY_ENABLE:
    WM_InvalidateWindow(hWin);    
    return;                       /* Message handled */
  }
  /* Message not handled. If it queries something, we return 0 to be on the safe side. */
  pMsg->Data.v = 0;
  pMsg->Data.p = 0;
}

/*********************************************************************
*
*       WM_Init
*/
void WM_Init(void) {
	if (!_IsInited) {
	  NextDrawWin = WM__FirstWin = WM_HWIN_NULL;
	  GUI_Context.WM__pUserClipRect = NULL;
	  WM__NumWindows = WM__NumInvalidWindows =0;
	  /* Make sure we have at least one window. This greatly simplifies the
		  drawing routines as they do not have to check if the window is valid.
	  */
    #if GUI_NUM_LAYERS == 1
      WM__ahDesktopWin[0] = WM_CreateWindow(0, 0, GUI_XMAX, GUI_YMAX, WM_CF_SHOW, cbBackWin, 0);
      WM__aBkColor[0] = GUI_INVALID_COLOR;
      WM_InvalidateWindow(WM__ahDesktopWin[0]); /* Required because a desktop window has no parent. */
    #else
    {
      int i;
      for (i = 0; i < GUI_NUM_LAYERS; i++) {
        WM__ahDesktopWin[i] = WM_CreateWindowAsChild(0, 0, GUI_XMAX, GUI_YMAX, WM_UNATTACHED, WM_CF_SHOW, cbBackWin, 0);
        WM__aBkColor[i] = GUI_INVALID_COLOR;
        WM_InvalidateWindow(WM__ahDesktopWin[i]); /* Required because a desktop window has no parent. */
      }
    }
    #endif
    /* Register the critical handles ... Note: This could be moved into the module setting the Window handle */
    WM__AddCriticalHandle(&WM__CHWinModal);
    WM__AddCriticalHandle(&WM__CHWinLast);

    WM_SelectWindow(WM__ahDesktopWin[0]);
	  WM_Activate();
    _IsInited =1;
	}
}


#else
  void WM(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/

