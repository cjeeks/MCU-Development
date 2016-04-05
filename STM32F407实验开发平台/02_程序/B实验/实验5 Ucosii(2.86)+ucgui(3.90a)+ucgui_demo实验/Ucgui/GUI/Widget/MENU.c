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
File        : MENU.c
Purpose     : Implementation of menu widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include <string.h>

#define MENU_C       /* Required to generate intermodule data */

#include "MENU.h"
#include "MENU_Private.h"
#include "GUIDebug.h"
#include "GUI_Protected.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Private config defaults
*
**********************************************************************
*/

/* Define default font */
#ifndef MENU_FONT_DEFAULT
  #define MENU_FONT_DEFAULT         &GUI_Font13_1
#endif

/* Define default effect */
#ifndef MENU_EFFECT_DEFAULT
  #define MENU_EFFECT_DEFAULT       &WIDGET_Effect_3D1L
#endif

/* Define colors, index 0, enabled, not selected */
#ifndef MENU_TEXTCOLOR0_DEFAULT
  #define MENU_TEXTCOLOR0_DEFAULT   GUI_BLACK
#endif

#ifndef MENU_BKCOLOR0_DEFAULT
  #define MENU_BKCOLOR0_DEFAULT     GUI_LIGHTGRAY
#endif

/* Define colors, index 1, enabled, selected */
#ifndef MENU_TEXTCOLOR1_DEFAULT
  #define MENU_TEXTCOLOR1_DEFAULT   GUI_WHITE
#endif

#ifndef MENU_BKCOLOR1_DEFAULT
  #define MENU_BKCOLOR1_DEFAULT     0x980000
#endif

/* Define colors, index 2, disabled, not selected */
#ifndef MENU_TEXTCOLOR2_DEFAULT
  #define MENU_TEXTCOLOR2_DEFAULT   0x7C7C7C
#endif

#ifndef MENU_BKCOLOR2_DEFAULT
  #define MENU_BKCOLOR2_DEFAULT     GUI_LIGHTGRAY
#endif

/* Define colors, index 3, disabled, selected */
#ifndef MENU_TEXTCOLOR3_DEFAULT
  #define MENU_TEXTCOLOR3_DEFAULT   GUI_LIGHTGRAY
#endif

#ifndef MENU_BKCOLOR3_DEFAULT
  #define MENU_BKCOLOR3_DEFAULT     0x980000
#endif

/* Define colors, index 4, active submenu */
#ifndef MENU_TEXTCOLOR4_DEFAULT
  #define MENU_TEXTCOLOR4_DEFAULT   GUI_WHITE
#endif

#ifndef MENU_BKCOLOR4_DEFAULT
  #define MENU_BKCOLOR4_DEFAULT     0x7C7C7C
#endif

/* Define borders */
#ifndef MENU_BORDER_LEFT_DEFAULT
  #define MENU_BORDER_LEFT_DEFAULT    4
#endif

#ifndef MENU_BORDER_RIGHT_DEFAULT
  #define MENU_BORDER_RIGHT_DEFAULT   4
#endif

#ifndef MENU_BORDER_TOP_DEFAULT
  #define MENU_BORDER_TOP_DEFAULT     2
#endif

#ifndef MENU_BORDER_BOTTOM_DEFAULT
  #define MENU_BORDER_BOTTOM_DEFAULT  2
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

MENU_PROPS MENU__DefaultProps = {
  MENU_TEXTCOLOR0_DEFAULT,
  MENU_TEXTCOLOR1_DEFAULT,
  MENU_TEXTCOLOR2_DEFAULT,
  MENU_TEXTCOLOR3_DEFAULT,
  MENU_TEXTCOLOR4_DEFAULT,
  MENU_BKCOLOR0_DEFAULT,
  MENU_BKCOLOR1_DEFAULT,
  MENU_BKCOLOR2_DEFAULT,
  MENU_BKCOLOR3_DEFAULT,
  MENU_BKCOLOR4_DEFAULT,
  MENU_BORDER_LEFT_DEFAULT,
  MENU_BORDER_RIGHT_DEFAULT,
  MENU_BORDER_TOP_DEFAULT,
  MENU_BORDER_BOTTOM_DEFAULT,
  MENU_FONT_DEFAULT
};

const WIDGET_EFFECT* MENU__pDefaultEffect = MENU_EFFECT_DEFAULT;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define OBJECT_ID 0x7843   /* Magic nubmer, should be unique if possible */
  #define INIT_ID(p)   p->DebugId = OBJECT_ID
  #define DEINIT_ID(p) p->DebugId = 0
#else
  #define INIT_ID(p)
  #define DEINIT_ID(p)
#endif

/*********************************************************************
*
*       Static routines, for higher debug level only
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU_h2p
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
MENU_Obj* MENU_h2p(MENU_Handle h) {
  MENU_Obj* p = (MENU_Obj*)GUI_ALLOC_h2p(h);
  if (p) {
    if (p->DebugId != OBJECT_ID) {
      GUI_DEBUG_ERROROUT("MENU.c: Wrong handle type or Object not init'ed");
      return 0;
    }
  }
  return p;
}
#endif

/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/
/*********************************************************************
*
*       _IsTopLevelMenu
*/
static char _IsTopLevelMenu(MENU_Handle hObj, const MENU_Obj* pObj) {
  if (MENU__SendMenuMessage(hObj, pObj->hOwner, MENU_IS_MENU, 0) == 0) {
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       _HasEffect
*/
static int _HasEffect(MENU_Handle hObj, MENU_Obj* pObj) {
  if (!(pObj->Flags & MENU_SF_POPUP)) {
    if (_IsTopLevelMenu(hObj, pObj)) {
      return 0;
    }
  }
  return 1;
}

/*********************************************************************
*
*       _GetEffectSize
*/
static int _GetEffectSize(MENU_Handle hObj, MENU_Obj* pObj) {
  int r = 0;
  if (_HasEffect(hObj, pObj)) { 
    r = pObj->Widget.pEffect->EffectSize;
  }
  return r;
}

/*********************************************************************
*
*       _CalcTextWidth
*/
static int _CalcTextWidth(MENU_Obj* pObj, const char GUI_UNI_PTR* sText) {
  int TextWidth = 0;
  if (sText) {
    const GUI_FONT GUI_UNI_PTR* pOldFont;
    pOldFont  = GUI_SetFont(pObj->Props.pFont);
    TextWidth = GUI_GetStringDistX(sText);
    GUI_SetFont(pOldFont);
  }
  return TextWidth;
}

/*********************************************************************
*
*       _GetItemWidth
*/
static int _GetItemWidth(MENU_Handle hObj, MENU_Obj* pObj, unsigned Index) {
  int ItemWidth;
  if (pObj->Width && (pObj->Flags & MENU_SF_VERTICAL)) {
    ItemWidth = pObj->Width - (_GetEffectSize(hObj, pObj) << 1);
  } else {
    MENU_ITEM* pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
    if ((pObj->Flags & MENU_SF_VERTICAL) || !(pItem->Flags & MENU_IF_SEPARATOR)) {
      ItemWidth = pItem->TextWidth;
    } else {
      ItemWidth = 3;
   }
    ItemWidth += pObj->Props.aBorder[MENU_BI_LEFT] + pObj->Props.aBorder[MENU_BI_RIGHT];
  }
  return ItemWidth;
}

/*********************************************************************
*
*       _GetItemHeight
*/
static int _GetItemHeight(MENU_Handle hObj, MENU_Obj* pObj, unsigned Index) {
  int ItemHeight;
  if (pObj->Height && !(pObj->Flags & MENU_SF_VERTICAL)) {
    ItemHeight = pObj->Height - (_GetEffectSize(hObj, pObj) << 1);
  } else {
    ItemHeight = GUI_GetYDistOfFont(pObj->Props.pFont);
    if (pObj->Flags & MENU_SF_VERTICAL) {
      MENU_ITEM* pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
      if (pItem->Flags & MENU_IF_SEPARATOR) {
        ItemHeight = 3;
      }
    }
    ItemHeight += pObj->Props.aBorder[MENU_BI_TOP] + pObj->Props.aBorder[MENU_BI_BOTTOM];
  }
  return ItemHeight;
}

/*********************************************************************
*
*       _CalcMenuSizeX
*/
static int _CalcMenuSizeX(MENU_Handle hObj, MENU_Obj* pObj) {
  unsigned i, NumItems = MENU__GetNumItems(pObj);
  int xSize = 0;
  if (pObj->Flags & MENU_SF_VERTICAL) {
    int ItemWidth;
    for (i = 0; i < NumItems; i++) {
      ItemWidth = _GetItemWidth(hObj, pObj, i);
      if (ItemWidth > xSize) {
        xSize = ItemWidth;
      }
    }
  } else {
    for (i = 0; i < NumItems; i++) {
      xSize += _GetItemWidth(hObj, pObj, i);
    }
  }
  xSize += (_GetEffectSize(hObj, pObj) << 1);
  return xSize;
}

/*********************************************************************
*
*       _CalcMenuSizeY
*/
static int _CalcMenuSizeY(MENU_Handle hObj, MENU_Obj* pObj) {
  unsigned i, NumItems = MENU__GetNumItems(pObj);
  int ySize = 0;
  if (pObj->Flags & MENU_SF_VERTICAL) {
    for (i = 0; i < NumItems; i++) {
      ySize += _GetItemHeight(hObj, pObj, i);
    }
  } else {
    int ItemHeight;
    for (i = 0; i < NumItems; i++) {
      ItemHeight = _GetItemHeight(hObj, pObj, i);
      if (ItemHeight > ySize) {
        ySize = ItemHeight;
      }
    }
  }
  ySize += (_GetEffectSize(hObj, pObj) << 1);
  return ySize;
}

/*********************************************************************
*
*       _CalcWindowSizeX
*/
static int _CalcWindowSizeX(MENU_Handle hObj, MENU_Obj* pObj) {
  int xSize = pObj->Width;
  if (xSize == 0) {
    xSize = _CalcMenuSizeX(hObj, pObj);
  }
  return xSize;
}

/*********************************************************************
*
*       _CalcWindowSizeY
*/
static int _CalcWindowSizeY(MENU_Handle hObj, MENU_Obj* pObj) {
  int ySize = pObj->Height;
  if (ySize == 0) {
    ySize = _CalcMenuSizeY(hObj, pObj);
  }
  return ySize;
}

/*********************************************************************
*
*       _GetItemFromPos
*
* Return value:
*   Zero based index of item at given position or -1.
*
* NOTE:
*   This function has to ensure that index is always less than the
*   maximum number of items.
*/
static int _GetItemFromPos(MENU_Handle hObj, MENU_Obj* pObj, int x, int y) {
  int xSize, ySize, EffectSize, r = -1;
  ySize = _CalcMenuSizeY(hObj, pObj);
  if ((pObj->Height) && (pObj->Height < ySize)) {
    ySize = pObj->Height;
  }
  xSize = _CalcMenuSizeX(hObj, pObj);
  if ((pObj->Width) && (pObj->Width < xSize)) {
    xSize = pObj->Width;
  }
  EffectSize = _GetEffectSize(hObj, pObj);
  x     -= EffectSize;
  y     -= EffectSize;
  xSize -= (EffectSize << 1);
  ySize -= (EffectSize << 1);
  if ((x >= 0) && (y >= 0) && (x < xSize) && (y < ySize)) {
    unsigned i, NumItems = MENU__GetNumItems(pObj);
    if (pObj->Flags & MENU_SF_VERTICAL) {
      int yPos = 0;
      for (i = 0; i < NumItems; i++) {
        yPos += _GetItemHeight(hObj, pObj, i);
        if (y < yPos) {
          r = i;
          break;
        }
      }
    } else {
      int xPos = 0;
      for (i = 0; i < NumItems; i++) {
        xPos += _GetItemWidth(hObj, pObj, i);
        if (x < xPos) {
          r = i;
          break;
        }
      }
    }
  }
  return r;
}

/*********************************************************************
*
*       _GetItemPos
*/
static void _GetItemPos(MENU_Handle hObj, MENU_Obj* pObj, unsigned Index, int* px, int* py) {
  int i, EffectSize;
  EffectSize = _GetEffectSize(hObj, pObj);
  if (pObj->Flags & MENU_SF_VERTICAL) {
    int yPos = 0;
    for (i = 0; i < (int)Index; i++) {
      yPos += _GetItemHeight(hObj, pObj, i);
    }
    *px = EffectSize;
    *py = EffectSize + yPos;
  } else {
    int xPos = 0;
    for (i = 0; i < (int)Index; i++) {
      xPos += _GetItemWidth(hObj, pObj, i);
    }
    *px = EffectSize + xPos;
    *py = EffectSize;
  }
}

/*********************************************************************
*
*       _SetCapture
*/
static void _SetCapture(MENU_Handle hObj, const MENU_Obj* pObj) {
  if (pObj->IsSubmenuActive == 0) {
    if (WM_HasCaptured(hObj) == 0) {
      WM_SetCapture(hObj, 0);
    }
  }
}

/*********************************************************************
*
*       _ReleaseCapture
*/
static void _ReleaseCapture(MENU_Handle hObj, const MENU_Obj* pObj) {
  if (WM_HasCaptured(hObj)) {
    if (_IsTopLevelMenu(hObj, pObj) && !(pObj->Flags & MENU_SF_POPUP)) {
      WM_ReleaseCapture();
    }
  }
}

/*********************************************************************
*
*       _CloseSubmenu
*/
static void _CloseSubmenu(MENU_Handle hObj, MENU_Obj* pObj) {
  if (pObj->Flags & MENU_SF_ACTIVE) {
    if (pObj->IsSubmenuActive) {
      MENU_ITEM* pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, pObj->Sel);
      /* Inform submenu about its deactivation and detach it */
      MENU__SendMenuMessage(hObj, pItem->hSubmenu, MENU_ON_CLOSE, 0);
      WM_DetachWindow(pItem->hSubmenu);
      pObj->IsSubmenuActive = 0;
      /*
       * Keep capture in menu widget. The capture may only released
       * by clicking outside the menu or when mouse moved out.
       * And it may only released from a top level menu.
       */
      _SetCapture(hObj, pObj);
      /* Invalidate menu item. This is needed because the appearance may have changed */
      MENU__InvalidateItem(hObj, pObj, pObj->Sel);
    }
  }
}

/*********************************************************************
*
*       _OpenSubmenu
*/
static void _OpenSubmenu(MENU_Handle hObj, MENU_Obj* pObj, unsigned Index) {
  if (pObj->Flags & MENU_SF_ACTIVE) {
    MENU_ITEM* pItem;
    char PrevActiveSubmenu;
    PrevActiveSubmenu = pObj->IsSubmenuActive;
    /* Close previous submenu (if needed) */
    _CloseSubmenu(hObj, pObj);
    pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
    if (pItem->hSubmenu) {
      if ((pItem->Flags & MENU_IF_DISABLED) == 0) {
        int x, y, EffectSize;
        /* Calculate position of submenu */
        EffectSize = _GetEffectSize(hObj, pObj);
        _GetItemPos(hObj, pObj, Index, &x, &y);
        if (pObj->Flags & MENU_SF_VERTICAL) {
          x += _CalcMenuSizeX(hObj, pObj) - (_GetEffectSize(hObj, pObj) << 1);
          y -= EffectSize;
        } else {
          y += _CalcMenuSizeY(hObj, pObj) - (_GetEffectSize(hObj, pObj) << 1);
          x -= EffectSize;
        }
        x += WM_GetWindowOrgX(hObj);
        y += WM_GetWindowOrgY(hObj);
        /*
         * Notify owner window when for the first time open a menu (when no
         * other submenu was open), so it can initialize the menu items.
         */
        if (PrevActiveSubmenu == 0) {
          if (_IsTopLevelMenu(hObj, pObj)) {
            MENU__SendMenuMessage(hObj, pObj->hOwner, MENU_ON_INITMENU, 0);
          }
        }
        /* Notify owner window when a submenu opens, so it can initialize the menu items. */
        MENU__SendMenuMessage(hObj, pObj->hOwner, MENU_ON_INITSUBMENU, pItem->Id);
        /* Set active menu as owner of submenu. */
        MENU_SetOwner(pItem->hSubmenu, hObj);
        /* Attach submenu and inform it about its activation. */
        WM_AttachWindowAt(pItem->hSubmenu, WM_HBKWIN, x, y);
        MENU__SendMenuMessage(hObj, pItem->hSubmenu, MENU_ON_OPEN, 0);
        pObj->IsSubmenuActive = 1;
        /* Invalidate menu item. This is needed because the appearance may have changed. */
        MENU__InvalidateItem(hObj, pObj, Index);
      }
    }
  }
}

/*********************************************************************
*
*       _ClosePopup
*/
static void _ClosePopup(MENU_Handle hObj, MENU_Obj* pObj) {
  if (pObj->Flags & MENU_SF_POPUP) {
    pObj->Flags &= ~(MENU_SF_POPUP);
    WM_DetachWindow(hObj);
    WM_ReleaseCapture();
  }
}

/*********************************************************************
*
*       _SetSelection
*/
static void _SetSelection(MENU_Handle hObj, MENU_Obj* pObj, int Index) {
  if (Index != pObj->Sel) {
    MENU__InvalidateItem(hObj, pObj, pObj->Sel); /* Invalidate previous selection */
    MENU__InvalidateItem(hObj, pObj, Index);     /* Invalidate new selection */
    pObj->Sel = Index;
  }
}

/*********************************************************************
*
*       _SelectItem
*/
static void _SelectItem(MENU_Handle hObj, MENU_Obj* pObj, unsigned Index) {
  if (pObj->Sel != (int)Index) {
    _SetCapture(hObj, pObj);
    _OpenSubmenu(hObj, pObj, Index);
    _SetSelection(hObj, pObj, Index);
  }
}

/*********************************************************************
*
*       _DeselectItem
*/
static void _DeselectItem(MENU_Handle hObj, MENU_Obj* pObj) {
  if (pObj->IsSubmenuActive == 0) {
    _SetSelection(hObj, pObj, -1);
    _ReleaseCapture(hObj, pObj);
  }
}

/*********************************************************************
*
*       _ActivateItem
*/
static void _ActivateItem(MENU_Handle hObj, MENU_Obj* pObj, unsigned Index) {
  MENU_ITEM* pItem;
  pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
  if (pItem->hSubmenu == 0) {
    if ((pItem->Flags & (MENU_IF_DISABLED | MENU_IF_SEPARATOR)) == 0) {
      _ClosePopup(hObj, pObj);
      /* Send item select message to owner. */
      MENU__SendMenuMessage(hObj, pObj->hOwner, MENU_ON_ITEMSELECT, pItem->Id);
    }
  }
}

/*********************************************************************
*
*       _ActivateMenu
*/
static void _ActivateMenu(MENU_Handle hObj, MENU_Obj* pObj, unsigned Index) {
  if ((pObj->Flags & MENU_SF_OPEN_ON_POINTEROVER) == 0) {
    MENU_ITEM* pItem;
    pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
    if (pItem->hSubmenu) {
      if ((pItem->Flags & MENU_IF_DISABLED) == 0) {
        if ((pObj->Flags & MENU_SF_ACTIVE) == 0) {
          pObj->Flags |= MENU_SF_ACTIVE;
          _OpenSubmenu(hObj, pObj, Index);
          _SetSelection(hObj, pObj, Index);
        } else if (pObj->Flags & MENU_SF_CLOSE_ON_SECOND_CLICK) {
          if ((int)Index == pObj->Sel) {
            _CloseSubmenu(hObj, pObj);
            pObj->Flags &= ~MENU_SF_ACTIVE;
          }
        }
      }
    }
  }
}

/*********************************************************************
*
*       _DeactivateMenu
*/
static void _DeactivateMenu(MENU_Handle hObj, MENU_Obj* pObj) {
  _CloseSubmenu(hObj, pObj);
  if ((pObj->Flags & MENU_SF_OPEN_ON_POINTEROVER) == 0) {
    pObj->Flags &= ~MENU_SF_ACTIVE;
  }
}

/*******************************************************************
*
*       _ForwardMouseOverMsg
*/
static int _ForwardMouseOverMsg(MENU_Handle hObj, MENU_Obj* pObj, int x, int y) {
#if (GUI_SUPPORT_MOUSE)
  if ((pObj->IsSubmenuActive == 0) && !(pObj->Flags & MENU_SF_POPUP)) {
    if (_IsTopLevelMenu(hObj, pObj)) {
      WM_HWIN hBelow;
      x += WM_GetWindowOrgX(hObj);
      y += WM_GetWindowOrgY(hObj);
      hBelow = WM_Screen2hWin(x, y);
      if (hBelow && (hBelow != hObj)) {
        WM_MESSAGE Msg;
        GUI_PID_STATE State;
        x -= WM_GetWindowOrgX(hBelow);
        y -= WM_GetWindowOrgY(hBelow);
        State.Pressed = 0;
        State.x = x;
        State.y = y;
        Msg.Data.p = &State;
        Msg.MsgId = WM_MOUSEOVER;
        WM__SendMessage(hBelow, &Msg);
        return 1;
      }
    }
  }
#endif
  return 0;
}

/*********************************************************************
*
*       _HandlePID
*
* Return values:
*   1 = We need to forward PID message to owner.
*   0 = We do not need to inform owner.
*/
static char _HandlePID(MENU_Handle hObj, MENU_Obj* pObj, int x, int y, int Pressed) {
  GUI_PID_STATE PrevState;
  char XYInWidget = 0;
  WM_PID__GetPrevState(&PrevState);
  /*
   * Check if coordinates are inside the widget.
   */
  if ((x >= 0) && (y >= 0)) {
    GUI_RECT r;
    WM__GetClientRectWin(&pObj->Widget.Win, &r);
    if ((x <= r.x1) && (y <= r.y1)) {
      XYInWidget = 1;
    }
  }

  if (XYInWidget) {
    int ItemIndex;
    ItemIndex = _GetItemFromPos(hObj, pObj, x, y);
    /* 
     * Handle PID when coordinates are inside the widget.
     */
    if (ItemIndex >= 0) {
      /* 
       * Coordinates are inside the menu.
       */
      if (Pressed == 1) {
        if (PrevState.Pressed == 0) {  /* Clicked */
          _ActivateMenu(hObj, pObj, ItemIndex);
        }
        _SelectItem(hObj, pObj, ItemIndex);
      } else if ((Pressed == 0) && (PrevState.Pressed == 1)) {  /* Released */
        _ActivateItem(hObj, pObj, ItemIndex);
      } else if (Pressed < 0) {  /* Mouse moved */
        if (_ForwardMouseOverMsg(hObj, pObj, x, y) == 0) {
          _SelectItem(hObj, pObj, ItemIndex);
        } else {
          _DeselectItem(hObj, pObj);
        }
      }
    } else {
      /* 
       * Coordinates are outside the menu but inside the widget.
       */
      if (Pressed == 1) {
        if (PrevState.Pressed == 0) {  /* Clicked */
          /* 
           * User has clicked outside the menu. Close the active submenu.
           * The widget itself must be closed (if needed) by the owner.
           */
          _DeactivateMenu(hObj, pObj);
        }
        _DeselectItem(hObj, pObj);
      } else if (Pressed < 0) {  /* Moved out or mouse moved */
        _DeselectItem(hObj, pObj);
      }
    }
    return 0;
  } else {
    /* 
     * Handle PID when coordinates are outside the widget.
     */
    if ((Pressed == 1) && (PrevState.Pressed == 0)) {
      /* 
       * User has clicked outside the menu. Close the active submenu.
       * The widget itself must be closed (if needed) by the owner.
       */
      _DeactivateMenu(hObj, pObj);
      _ClosePopup(hObj, pObj);
    }
    _DeselectItem(hObj, pObj);
    _ForwardMouseOverMsg(hObj, pObj, x, y);
  }
  return 1;   /* Coordinates are not in widget, we need to forward PID message to owner */
}

/*********************************************************************
*
*       _ForwardPIDMsgToOwner
*/
static void _ForwardPIDMsgToOwner(MENU_Handle hObj, MENU_Obj* pObj, WM_MESSAGE* pMsg) {
  if (_IsTopLevelMenu(hObj, pObj) == 0) {
    WM_HWIN hOwner;
    hOwner = pObj->hOwner ? pObj->hOwner : WM_GetParent(hObj);
    if (hOwner) {
      if (pMsg->Data.p) {
        GUI_PID_STATE* pState;
        pState = (GUI_PID_STATE*)pMsg->Data.p;
        pState->x += WM_GetWindowOrgX(hObj) - WM_GetWindowOrgX(hOwner);
        pState->y += WM_GetWindowOrgY(hObj) - WM_GetWindowOrgY(hOwner);
      }
      WM__SendMessage(hOwner, pMsg);
    }
  }
}

/*********************************************************************
*
*       Static routines, callback
*
**********************************************************************
*/
/*********************************************************************
*
*       _OnMenu
*/
static void _OnMenu(MENU_Handle hObj, MENU_Obj* pObj, WM_MESSAGE* pMsg) {
  const MENU_MSG_DATA* pData = (const MENU_MSG_DATA*)pMsg->Data.p;
  if (pData) {
    switch (pData->MsgType) {
    case MENU_ON_ITEMSELECT:
      _DeactivateMenu(hObj, pObj);
      _DeselectItem(hObj, pObj);
      _ClosePopup(hObj, pObj);
      /* No break here. We need to forward message to owner. */
    case MENU_ON_INITMENU:
    case MENU_ON_INITSUBMENU:
      /* Forward message to owner. */
      {
        WM_HWIN hOwner;
        hOwner = pObj->hOwner ? pObj->hOwner : WM_GetParent(hObj);
        if (hOwner) {
          pMsg->hWinSrc = hObj;
          WM__SendMessage(hOwner, pMsg);
        }
      }
      break;
    case MENU_ON_OPEN:
      pObj->Sel = -1;
      pObj->IsSubmenuActive = 0;
      pObj->Flags |= MENU_SF_ACTIVE | MENU_SF_OPEN_ON_POINTEROVER;
      _SetCapture(hObj, pObj);
      MENU__ResizeMenu(hObj, pObj);
      break;
    case MENU_ON_CLOSE:
      _CloseSubmenu(hObj, pObj);
      break;
    case MENU_IS_MENU:
      pMsg->Data.v = 1;
      break;
    }
  }
}

/*********************************************************************
*
*       _OnTouch
*/
static char _OnTouch(MENU_Handle hObj, MENU_Obj* pObj, WM_MESSAGE* pMsg) {
  const GUI_PID_STATE* pState = (const GUI_PID_STATE*)pMsg->Data.p;
  if (pState) {  /* Something happened in our area (pressed or released) */
    return _HandlePID(hObj, pObj, pState->x, pState->y, pState->Pressed);
  }
  return _HandlePID(hObj, pObj, -1, -1, -1); /* Moved out */
}

/*********************************************************************
*
*       _OnMouseOver
*/
#if (GUI_SUPPORT_MOUSE)
static char _OnMouseOver(MENU_Handle hObj, MENU_Obj* pObj, WM_MESSAGE* pMsg) {
  const GUI_PID_STATE* pState = (const GUI_PID_STATE *)pMsg->Data.p;
  if (pState) {
    return _HandlePID(hObj, pObj, pState->x, pState->y, -1);
  }
  return 0;
}
#endif

/*********************************************************************
*
*       _SetPaintColors
*/
static void _SetPaintColors(const MENU_Obj* pObj, const MENU_ITEM* pItem, int ItemIndex) {
  char Selected;
  unsigned ColorIndex;
  Selected = (ItemIndex == pObj->Sel) ? 1 : 0;
  if (pObj->IsSubmenuActive && Selected) {
    ColorIndex = MENU_CI_ACTIVE_SUBMENU;
  } else if (pItem->Flags & MENU_IF_SEPARATOR) {
    ColorIndex = MENU_CI_ENABLED;
  } else {
    ColorIndex = (Selected) ? MENU_CI_SELECTED : MENU_CI_ENABLED;
    if (pItem->Flags & MENU_IF_DISABLED) {
      if (pObj->Flags & MENU_CF_HIDE_DISABLED_SEL) {
        ColorIndex = MENU_CI_DISABLED;
      } else {
        ColorIndex += MENU_CI_DISABLED;
      }
    }
  }
  GUI_SetBkColor(pObj->Props.aBkColor[ColorIndex]);
  GUI_SetColor(pObj->Props.aTextColor[ColorIndex]);
}

/*********************************************************************
*
*       _OnPaint
*/
static void _OnPaint(MENU_Handle hObj, MENU_Obj* pObj) {
  GUI_RECT FillRect, TextRect;
  MENU_ITEM* pItem;
  unsigned TextWidth, NumItems, i;
  U8 BorderLeft   = pObj->Props.aBorder[MENU_BI_LEFT];
  U8 BorderTop    = pObj->Props.aBorder[MENU_BI_TOP];
  int FontHeight  = GUI_GetYDistOfFont(pObj->Props.pFont);
  int EffectSize  = _GetEffectSize(hObj, pObj);
  NumItems = MENU__GetNumItems(pObj);
  WM__GetClientRectWin(&pObj->Widget.Win, &FillRect);
  GUI__ReduceRect(&FillRect, &FillRect, EffectSize);
  GUI_SetFont(pObj->Props.pFont);
  if (pObj->Flags & MENU_SF_VERTICAL) {
    int ItemHeight, xSize;
    xSize = _CalcMenuSizeX(hObj, pObj);
    FillRect.x1 = xSize - EffectSize - 1;
    TextRect.x0 = FillRect.x0 + BorderLeft;
    for (i = 0; i < NumItems; i++) {
      pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, i);
      ItemHeight = _GetItemHeight(hObj, pObj, i);
      _SetPaintColors(pObj, pItem, i);
      FillRect.y1 = FillRect.y0 + ItemHeight - 1;
      if (pItem->Flags & MENU_IF_SEPARATOR) {
        GUI_ClearRectEx(&FillRect);
        GUI_SetColor(0x7C7C7C);
        GUI_DrawHLine(FillRect.y0 + BorderTop + 1, FillRect.x0 + 2, FillRect.x1 - 2);
      } else {
        TextWidth = pItem->TextWidth;
        TextRect.x1 = TextRect.x0 + TextWidth - 1;
        TextRect.y0 = FillRect.y0 + BorderTop;
        TextRect.y1 = TextRect.y0 + FontHeight - 1;
        WIDGET__FillStringInRect(pItem->acText, &FillRect, &TextRect, &TextRect);
      }
      FillRect.y0 += ItemHeight;
    }
  } else {
    int ItemWidth, ySize;
    ySize = _CalcMenuSizeY(hObj, pObj);
    FillRect.y1 = ySize - EffectSize - 1;
    TextRect.y0 = FillRect.y0 + BorderTop;
    TextRect.y1 = TextRect.y0 + FontHeight - 1;
    for (i = 0; i < NumItems; i++) {
      pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, i);
      ItemWidth = _GetItemWidth(hObj, pObj, i);
      _SetPaintColors(pObj, pItem, i);
      FillRect.x1 = FillRect.x0 + ItemWidth - 1;
      if (pItem->Flags & MENU_IF_SEPARATOR) {
        GUI_ClearRectEx(&FillRect);
        GUI_SetColor(0x7C7C7C);
        GUI_DrawVLine(FillRect.x0 + BorderLeft + 1, FillRect.y0 + 2, FillRect.y1 - 2);
      } else {
        TextWidth = pItem->TextWidth;
        TextRect.x0 = FillRect.x0 + BorderLeft;
        TextRect.x1 = TextRect.x0 + TextWidth - 1;
        WIDGET__FillStringInRect(pItem->acText, &FillRect, &TextRect, &TextRect);
      }
      FillRect.x0 += ItemWidth;
    }
  }
  if (pObj->Width || pObj->Height) {
    GUI_RECT r;
    WM__GetClientRectWin(&pObj->Widget.Win, &r);
    GUI__ReduceRect(&r, &r, EffectSize);
    GUI_SetBkColor(pObj->Props.aBkColor[MENU_CI_ENABLED]);
    GUI_ClearRect(FillRect.x1 + 1, EffectSize, r.x1, FillRect.y1);
    GUI_ClearRect(EffectSize, FillRect.y1 + 1, r.x1, r.y1);
  }
  /* Draw 3D effect (if configured) */
  if (_HasEffect(hObj, pObj)) {
    pObj->Widget.pEffect->pfDrawUp();
  }
}

/*********************************************************************
*
*       _MENU_Callback
*/
static void _MENU_Callback(WM_MESSAGE* pMsg) {
  MENU_Handle hObj;
  MENU_Obj* pObj;
  hObj = pMsg->hWin;
  if (pMsg->MsgId != WM_PID_STATE_CHANGED) {
    /* Let widget handle the standard messages */
    if (WIDGET_HandleActive(hObj, pMsg) == 0) {
      return;
    }
  }
  pObj = (MENU_Obj*) GUI_ALLOC_h2p(hObj);
  switch (pMsg->MsgId) {
  case WM_MENU:
    _OnMenu(hObj, pObj, pMsg);
    return;     /* Message handled, do not call WM_DefaultProc() here. */
  case WM_TOUCH:
    if (_OnTouch(hObj, pObj, pMsg)) {
      _ForwardPIDMsgToOwner(hObj, pObj, pMsg);
    }
    break;
#if (GUI_SUPPORT_MOUSE)
  case WM_MOUSEOVER:
    if (_OnMouseOver(hObj, pObj, pMsg)) {
      _ForwardPIDMsgToOwner(hObj, pObj, pMsg);
    }
    break;
#endif
  case WM_PAINT:
    _OnPaint(hObj, pObj);
    break;
  case WM_DELETE:
    GUI_ARRAY_Delete(&pObj->ItemArray);
    break;      /* No return here ... WM_DefaultProc needs to be called */
  }
  WM_DefaultProc(pMsg);
}

/*********************************************************************
*
*       Public code, Create
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU_CreateEx
*/
MENU_Handle MENU_CreateEx(int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id) {
  MENU_Handle hObj;
  /* Create the window */
  hObj = WM_CreateWindowAsChild(x0, y0, xSize, ySize, hParent, WM_CF_SHOW | WM_CF_STAYONTOP | WinFlags, &_MENU_Callback,
                                sizeof(MENU_Obj) - sizeof(WM_Obj));
  if (hObj) {
    MENU_Obj* pObj;
    WM_LOCK();
    pObj = (MENU_Obj*)GUI_ALLOC_h2p(hObj);
     /* Init sub-classes */
    GUI_ARRAY_CREATE(&pObj->ItemArray);
    /* init widget specific variables */
    WIDGET__Init(&pObj->Widget, Id, WIDGET_STATE_FOCUSSABLE);
    /* init member variables */
    if (ExFlags & MENU_SF_OPEN_ON_POINTEROVER) {
      ExFlags |= MENU_SF_ACTIVE;
    } else {
      ExFlags &= ~(MENU_SF_ACTIVE);
    }
    pObj->Props           = MENU__DefaultProps;
    pObj->Flags           = ExFlags;
    pObj->Width           = ((xSize > 0) ? xSize : 0);
    pObj->Height          = ((ySize > 0) ? ySize : 0);
    pObj->Sel             = -1;
    pObj->hOwner          = 0;
    pObj->IsSubmenuActive = 0;
    WIDGET_SetEffect(hObj, MENU__pDefaultEffect);
    INIT_ID(pObj);
    WM_UNLOCK();
  } else {
    GUI_DEBUG_ERROROUT_IF(hObj==0, "MENU_CreateEx failed")
  }
  return hObj;
}

/*********************************************************************
*
*       Public code, modul internal functions
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU__GetNumItems
*/
unsigned MENU__GetNumItems(MENU_Obj* pObj) {
  return GUI_ARRAY_GetNumItems(&pObj->ItemArray);
}

/*********************************************************************
*
*       MENU__InvalidateItem
*/
void MENU__InvalidateItem(MENU_Handle hObj, const MENU_Obj* pObj, unsigned Index) {
  GUI_USE_PARA(pObj);
  GUI_USE_PARA(Index);
  WM_InvalidateWindow(hObj);  /* Can be optimized, no need to invalidate all items */
}

/*********************************************************************
*
*       MENU__RecalcTextWidthOfItems
*/
void MENU__RecalcTextWidthOfItems(MENU_Obj* pObj) {
  const GUI_FONT GUI_UNI_PTR* pOldFont;
  MENU_ITEM* pItem;
  unsigned i, NumItems;
  NumItems = MENU__GetNumItems(pObj);
  pOldFont  = GUI_SetFont(pObj->Props.pFont);
  for (i = 0; i < NumItems; i++) {
    pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, i);
    pItem->TextWidth = GUI_GetStringDistX(pItem->acText);
  }
  GUI_SetFont(pOldFont);
}

/*********************************************************************
*
*       MENU__ResizeMenu
*/
void MENU__ResizeMenu(MENU_Handle hObj, MENU_Obj* pObj) {
  int xSize, ySize;
  xSize = _CalcWindowSizeX(hObj, pObj);
  ySize = _CalcWindowSizeY(hObj, pObj);
  WM_SetSize(hObj, xSize, ySize);
  WM_InvalidateWindow(hObj);
}

/*********************************************************************
*
*       MENU__SetItem
*/
char MENU__SetItem(MENU_Handle hObj, MENU_Obj* pObj, unsigned Index, const MENU_ITEM_DATA* pItemData) {
  MENU_ITEM Item = {0};
  const char* pText;
  pText = pItemData->pText;
  if (!pText) {
    pText = "";
  }
  Item.Id        = pItemData->Id;
  Item.Flags     = pItemData->Flags;
  Item.hSubmenu  = pItemData->hSubmenu;
  Item.TextWidth = _CalcTextWidth(pObj, pText);
  if (Item.Flags & MENU_IF_SEPARATOR) {
    Item.hSubmenu = 0;   /* Ensures that no separator is a submenu */
  }
  if (GUI_ARRAY_SetItem(&pObj->ItemArray, Index, &Item, sizeof(MENU_ITEM) + strlen(pText)) != 0) {
    MENU_ITEM* pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
    strcpy(pItem->acText, pText);
    MENU_SetOwner(Item.hSubmenu, hObj);
    return 1;
  }
  return 0;
}

/*********************************************************************
*
*       MENU__SetItemFlags
*/
void MENU__SetItemFlags(MENU_Obj* pObj, unsigned Index, U16 Mask, U16 Flags) {
  MENU_ITEM* pItem = (MENU_ITEM*)GUI_ARRAY_GetpItem(&pObj->ItemArray, Index);
  pItem->Flags &= ~Mask;
  pItem->Flags |= Flags;
}

/*********************************************************************
*
*       MENU__SendMenuMessage
*/
int MENU__SendMenuMessage(MENU_Handle hObj, WM_HWIN hDestWin, U16 MsgType, U16 ItemId) {
  MENU_MSG_DATA MsgData;
  WM_MESSAGE    Msg = {0};
  MsgData.MsgType   = MsgType;
  MsgData.ItemId    = ItemId;
  Msg.MsgId         = WM_MENU;
  Msg.Data.p        = &MsgData;
  Msg.hWinSrc       = hObj;
  if (!hDestWin) {
    hDestWin = WM_GetParent(hObj);
  }
  if (hDestWin) {
    WM__SendMessage(hDestWin, &Msg);
    return Msg.Data.v;
  }
  return 0;
}

/*********************************************************************
*
*       Public code, member functions
*
**********************************************************************
*/
/*********************************************************************
*
*       MENU_AddItem
*/
void MENU_AddItem(MENU_Handle hObj, const MENU_ITEM_DATA* pItemData) {
  if (hObj && pItemData) {
    MENU_Obj* pObj;
    WM_LOCK();
    pObj = MENU_H2P(hObj);
    if (pObj) {
      if (GUI_ARRAY_AddItem(&pObj->ItemArray, NULL, 0) == 0) {
        unsigned Index;
        Index = MENU__GetNumItems(pObj) - 1;
        if (MENU__SetItem(hObj, pObj, Index, pItemData) == 0) {
          GUI_ARRAY_DeleteItem(&pObj->ItemArray, Index);
        } else {
          MENU__ResizeMenu(hObj, pObj);
        }
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       MENU_SetOwner
*/
void MENU_SetOwner(MENU_Handle hObj, WM_HWIN hOwner) {
  if (hObj) {
    MENU_Obj* pObj;
    WM_LOCK();
    pObj = MENU_H2P(hObj);
    if (pObj) {
      pObj->hOwner = hOwner;
    }
    WM_UNLOCK();
  }
}

#else  /* avoid empty object files */
  void Menu_C(void);
  void Menu_C(void) {}
#endif

/*************************** End of file ****************************/
