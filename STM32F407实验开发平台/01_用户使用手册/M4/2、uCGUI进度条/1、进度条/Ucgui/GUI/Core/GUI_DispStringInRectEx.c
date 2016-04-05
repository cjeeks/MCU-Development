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
File        : GUI_DispStringInRectEx.c
Purpose     : Implementation of GUI_DispStringInRectEx
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include "GUI_Private.h"
#if GUI_WINSUPPORT
  #include "WM.h"
#endif

#if GUI_SUPPORT_ROTATION

/*********************************************************************
*
*       Global data
*
**********************************************************************
*/

GUI_RECT GUI_RectDispString; /* Used by LCD_Rotate... */

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static const GUI_ROTATION * _SetRotation(const GUI_ROTATION* pLCD_Api) {
  const GUI_ROTATION * pLCD_ApiOld;
  GUI_LOCK();
  pLCD_ApiOld = GUI_pLCD_APIList;
  if (pLCD_Api) {
    GUI_Context.pClipRect_HL = NULL;           /* Do not perform high level clipping in rotated mode */
  } else {
    GUI_Context.pClipRect_HL = &GUI_Context.ClipRect;
  }
  GUI_pLCD_APIList = pLCD_Api;
  GUI_UNLOCK();
  return pLCD_ApiOld;
}

/*********************************************************************
*
*       Exported code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DispStringInRectEx
*/
void GUI_DispStringInRectEx(const char GUI_UNI_PTR *s, GUI_RECT* pRect, int TextAlign, int MaxLen, const GUI_ROTATION * pLCD_Api) {
  const GUI_ROTATION * pLCD_ApiOld;
  if (pLCD_Api == GUI_ROTATE_0) {
    /* Do nothing else but calling GUI_DispStringInRectMax if pLCD_Api == GUI_ROTATE_0 */
    GUI_DispStringInRectMax(s, pRect, TextAlign, MaxLen);
  } else {
    #if (!GUI_WINSUPPORT)
      GUI_RECT Rect_Old;
    #else
      const GUI_RECT * pOldClipRect = NULL;
    #endif
    GUI_RECT rClip, rText = {0};
    GUI_LOCK();
    /* Set the clip rectangle */
    if (pRect) {
      rText = *pRect;
      GUI_RectDispString = rText;
      #if (GUI_WINSUPPORT)
        pOldClipRect = WM_SetUserClipRect(pRect);
        if (pOldClipRect) {
          GUI__IntersectRects(&rClip, pRect, pOldClipRect);
          WM_SetUserClipRect(&rClip);
        }
      #else
        Rect_Old = GUI_Context.ClipRect;
        GUI__IntersectRects(&rClip, pRect, &Rect_Old);
        LCD_SetClipRectEx(&rClip);
      #endif
    }
    pLCD_ApiOld = _SetRotation(pLCD_Api);                /* Set the new function pointer for rotating text */
    pLCD_Api->pfRect2TextRect(&rText);                   /* Calculate the text rectangle */
    GUI__DispStringInRect(s, &rText, TextAlign, MaxLen); /* Display the string */
    /* Restore old clipping rectangle */
    #if (GUI_WINSUPPORT)
      WM_SetUserClipRect(pOldClipRect);
    #else
      LCD_SetClipRectEx(&Rect_Old);
    #endif
    _SetRotation(pLCD_ApiOld);
    GUI_UNLOCK();
  }
}

#else                                 /* Avoid empty object files */
void GUI_DispStringInRectEx_C(void);
void GUI_DispStringInRectEx_C(void) {}
#endif

/*************************** End of file ****************************/
