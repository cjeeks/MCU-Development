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
File        : WM_TimerExternal.c
Purpose     : Implementetion of WM_CreateTimer, WM_DeleteTimer
              for systems with external one shot timers.
              (--> Philips, 2003)

              This module requires 2 macros in order to work and
              generate code:
              GUI_X_CREATE_TIMER(Period, void (*cb)(int))
              GUI_X_DELETE_TIMER(ID)

              Note that the delete macro is optional, since
              one-shot-timers are expected to delete themselves.
----------------------------------------------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "WM_Intern.h"


/* Typical configuration: */

#if 0
int MyApp_CreateTimer(int Period, void (*cb)(int)) {
  int r = 0;
  /* Alloc a one-shot timer from the kernel & start it etc ... */
  return r;
}
#define GUI_X_CREATE_TIMER(Period, cb) MyApp_CreateTimer(Period, cb)
#define GUI_X_DELETE_TIMER(ID)

#endif


#if GUI_WINSUPPORT && defined(GUI_X_CREATE_TIMER)   /* If 0, WM will not generate any code */


/*********************************************************************
*
*       Required data structures
*
**********************************************************************
*/
typedef struct TIMER_LINK {
  int      UserId;
  int      TimerId;
  WM_HWIN  hWin;
  GUI_HMEM hNext;
} TIMER_LINK;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static GUI_HMEM _hFirst;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

/*********************************************************************
*
*       _DeleteLinkItem
*
* Purpose:
* Returns:
*
*/
static void _DeleteLinkItem(GUI_HMEM hLinkToDelete) {
  GUI_HMEM hLink;
  TIMER_LINK* pLink;
  TIMER_LINK* pLinkToDelete;
  if (hLinkToDelete) {
    pLinkToDelete = (TIMER_LINK*)GUI_ALLOC_h2p(hLinkToDelete);
    if (_hFirst == hLinkToDelete) {
      _hFirst = pLinkToDelete->hNext;
      GUI_ALLOC_Free(hLinkToDelete);
    } else {
      for (hLink = _hFirst; hLink; hLink = pLink->hNext) {
        pLink = (TIMER_LINK*)GUI_ALLOC_h2p(hLink);
        if (pLink->hNext == hLinkToDelete) {
          pLink->hNext = pLinkToDelete->hNext;
          GUI_ALLOC_Free(hLinkToDelete);
          break;                         /* We found it ! */
        }
      }
    }
  }
}

/*********************************************************************
*
*       _FindTimerByTimerId
*
* Purpose:
*  Find the link item for this timer.
* Returns:  pointer to the link if the TimerId is valid, else NULL
*
*/
static GUI_HMEM _FindTimerByTimerId(int TimerId) {
  GUI_HMEM hLink;
  TIMER_LINK* pLink;
  for (hLink = _hFirst; hLink; hLink = pLink->hNext) {
    pLink = (TIMER_LINK*)GUI_ALLOC_h2p(hLink);
    if (pLink->TimerId == TimerId) {
      break;                         /* We found it ! */
    }
  }
  return hLink;
}

/*********************************************************************
*
*       _FindTimerByUserId
*
* Purpose:
*  Find the link item for this timer.
*  Returns:  pointer to the link if the Window handle & UserId are valid, else NULL
*
*/
static GUI_HMEM _FindTimerByUserId(WM_HWIN hWin, int UserId) {
  GUI_HMEM hLink;
  TIMER_LINK* pLink;
  for (hLink = _hFirst; hLink; hLink = pLink->hNext) {
    pLink = (TIMER_LINK*)GUI_ALLOC_h2p(hLink);
    if ((pLink->hWin == hWin) && (pLink->UserId == UserId)) {
      break;                         /* We found it ! */
    }
  }
  return hLink;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       _OnTimer
*
*   This routine is called when a timer is expired. Its function is to
*   find out which window needs to receive a WM_TIMER message.
*/
static void _OnTimer(int TimerId) {
  TIMER_LINK* pLink;
  GUI_HMEM hLink;
  WM_LOCK();
  hLink = _FindTimerByTimerId(TimerId);
  if (hLink) {
    WM_MESSAGE Msg;
    /* Send Message */
    pLink = GUI_ALLOC_h2p(hLink);
    Msg.MsgId   = WM_TIMER;
    Msg.Data.v  = pLink->UserId;
    Msg.hWinSrc = 0;
    WM_SendMessage(pLink->hWin, &Msg);
    /* Since these timers are one shot, we need to delete the link item. */
    _DeleteLinkItem(hLink);
  }
  WM_UNLOCK();
}

/*********************************************************************
*
*       WM_DeleteTimer
*
* Purpose:
*   API function (optional).
*   Allows the application to delete a timer. 
*/
void WM_DeleteTimer    (WM_HWIN hWin, int UserId) {
  GUI_HMEM hLink;
  WM_LOCK();
  hLink = _FindTimerByUserId(hWin, UserId);
  if (hLink) {
    TIMER_LINK* pLink;
    pLink = GUI_ALLOC_h2p(hLink);
    GUI_X_DELETE_TIMER(pLink->TimerId);
    _DeleteLinkItem(hLink);
  }
  WM_UNLOCK();
}


/*********************************************************************
*
*       WM_CreateTimer
*
*  Returns:    0 if failed, else != 0
*  Parameters:
*                hWin        Window handle of the window to receive the WM_TIMER message
*                UserId      User defined Id. If not needed, use 0.
*                Period      Number of time units (ticks)
*                Mode        0: one-shot
*
*/
int WM_CreateTimer               (WM_HWIN hWin, int UserId, int Period, int Mode) {
  int r = 0;
  int TimerId;
  GUI_HMEM hTimerLink;
  TIMER_LINK* pLink;
  WM_LOCK();
  TimerId = GUI_X_CREATE_TIMER(Period, _OnTimer);
  if (TimerId) {
    hTimerLink = GUI_ALLOC_AllocZero(sizeof(TIMER_LINK));
    if (hTimerLink) {
      pLink = (TIMER_LINK*) GUI_ALLOC_h2p(hTimerLink);
      /* Put new timer at beginning of the linked list */
      pLink->hNext = _hFirst;
      if (_hFirst) {
        TIMER_LINK* pNext;
        pNext = (TIMER_LINK*) GUI_ALLOC_h2p(_hFirst);
      }
      _hFirst = hTimerLink;
      /* Fill in link data */
      pLink->hWin    = hWin;
      pLink->TimerId = TimerId;
      pLink->UserId  = UserId;
      r = 1;            /* All right, we have successfully created a new timer */
    }
  }
  /* Cleanup in case of problem */
  if (r == 0) {
    if (TimerId) {
      GUI_X_DELETE_TIMER(TimerId);
    }
  }
  WM_UNLOCK();
  return r;
}





#else
  void WM_TimerExternal_c(void);
  void WM_TimerExternal_c(void) {} /* avoid empty object files */
#endif   /* GUI_WINSUPPORT */

/*************************** End of file ****************************/
