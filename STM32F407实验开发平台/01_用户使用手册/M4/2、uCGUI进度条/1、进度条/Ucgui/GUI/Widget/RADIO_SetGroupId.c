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
File        : RADIO_SetGroupId.c
Purpose     : Implementation of RADIO widget
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>
#include "RADIO.h"
#include "RADIO_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetValue
*/
static void _SetValue(RADIO_Handle hObj, int v) {
  RADIO_Obj* pObj;
  pObj = RADIO_H2P(hObj);
  RADIO__SetValue(hObj, pObj, v);
}

/*********************************************************************
*
*       _IsInGroup
*/
static int _IsInGroup(WM_HWIN hWin, U8 GroupId) {
  if (GroupId) {
    WM_MESSAGE Msg;
    Msg.MsgId = WM_GET_RADIOGROUP;
    WM_SendMessage(hWin, &Msg);
    return (Msg.Data.v == GroupId);
  }
  return 0;
}

/*********************************************************************
*
*       _GetPrevInGroup
*/
static WM_HWIN _GetPrevInGroup(WM_HWIN hWin, U8 GroupId) {
  for (hWin = WM__GetPrevSibling(hWin); hWin; hWin = WM__GetPrevSibling(hWin)) {
    if (_IsInGroup(hWin, GroupId)) {
      return hWin;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _GetNextInGroup
*/
static WM_HWIN _GetNextInGroup(WM_HWIN hWin, U8 GroupId) {
  for (; hWin; hWin = WM_GetNextSibling(hWin)) {
    if (_IsInGroup(hWin, GroupId)) {
      return hWin;
    }
  }
  return 0;
}

/*********************************************************************
*
*       _ClearSelection
*/
static void _ClearSelection(RADIO_Handle hObj, U8 GroupId) {
  WM_HWIN hWin;
  WM_Obj* pWin;
  for (hWin = WM__GetFirstSibling(hObj); hWin; hWin = pWin->hNext) {
    pWin = WM_H2P(hWin);
    if (hWin != hObj) {
      if (_IsInGroup(hWin, GroupId)) {
        RADIO__SetValue(hWin, (RADIO_Obj*)pWin, -1);
      }
    }
  }
}

/*********************************************************************
*
*       _HandleSetValue
*/
static void _HandleSetValue(RADIO_Handle hObj, RADIO_Obj* pObj, int v) {
  if (v < 0) {
    WM_HWIN hWin = _GetPrevInGroup(hObj, pObj->GroupId);
    if (hWin) {
      WM_SetFocus(hWin);
      _SetValue(hWin, 0x7FFF);
      RADIO__SetValue(hObj, pObj, -1);
    }
  } else if (v >= pObj->NumItems) {
    WM_HWIN hWin = _GetNextInGroup(pObj->Widget.Win.hNext, pObj->GroupId);
    if (hWin) {
      WM_SetFocus(hWin);
      _SetValue(hWin, 0);
      RADIO__SetValue(hObj, pObj, -1);
    }
  } else {
    if (pObj->Sel != v) {
      _ClearSelection(hObj, pObj->GroupId);
      RADIO__SetValue(hObj, pObj, v);
    }
  }
}

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/
/*********************************************************************
*
*       RADIO_SetGroupId
*/
void RADIO_SetGroupId(RADIO_Handle hObj, U8 NewGroupId) {
  if (hObj) {
    RADIO_Obj* pObj;
    U8 OldGroupId;
    WM_LOCK();
    pObj = RADIO_H2P(hObj);
    OldGroupId = pObj->GroupId;
    if (NewGroupId != OldGroupId) {
      WM_HWIN hFirst;
      hFirst = WM__GetFirstSibling(hObj);
      /* Set function pointer if necessary */
      if (NewGroupId && (RADIO__pfHandleSetValue == NULL)) {
        RADIO__pfHandleSetValue = _HandleSetValue;
      }
      /* Pass our selection, if we have one, to another radio button in */
      /* our old group. So the group have a valid selection when we leave it. */
      if (OldGroupId && (pObj->Sel >= 0)) {
        WM_HWIN hWin;
        pObj->GroupId = 0; /* Leave group first, so _GetNextInGroup() could */
                           /* not find a handle to our own window. */
        hWin = _GetNextInGroup(hFirst, OldGroupId);
        if (hWin) {
          _SetValue(hWin, 0);
        }
      }
      /* Make sure we have a valid selection according to our new group */
      if (_GetNextInGroup(hFirst, NewGroupId) != 0) {
        /* Join an existing group with an already valid selection, so clear our own one */
        RADIO__SetValue(hObj, pObj, -1);
      } else if (pObj->Sel < 0) {
        /* We are the first window in group, so we must have a valid selection at our own. */
        RADIO__SetValue(hObj, pObj, 0);
      }
      /* Change the group */
      pObj->GroupId = NewGroupId;
    }
    WM_UNLOCK();
  }
}

#else                            /* Avoid problems with empty object modules */
  void RADIO_SetGroupId_C(void);
  void RADIO_SetGroupId_C(void) {}
#endif

/************************* end of file ******************************/
