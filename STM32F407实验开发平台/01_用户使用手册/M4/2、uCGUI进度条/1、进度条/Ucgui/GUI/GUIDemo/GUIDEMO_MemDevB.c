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
File        : GUIDEMO_MemDevB.c
Purpose     : Memory device demo
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.h"
#if GUI_WINSUPPORT
#include "WM.h"
#endif
#include "stdio.h"

#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const GUI_POINT _aArrow[] = {
  {  0, 0   +85},
  {-40, -35 +85},
  {-10, -25 +85},
  {-10, -85 +85},
  { 10, -85 +85},
  { 10, -25 +85},
  { 40, -35 +85}
};

/* Define the callback structure. The structure should contain all the data
   required by the callback drawing funtion
*/
typedef struct {
  int Angle;
  int DoClear;
  GUI_COLOR BkColor;
} tDrawContext;

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

/* The user defined callback routine */
static void _Draw(void * p) {
  int XSize = LCD_GetXSize();
  int YSize = LCD_GetYSize();
  tDrawContext * pContext = (tDrawContext *)p;
  int i = pContext->Angle;
  static int iLast = -1;
  static GUI_POINT aPoint[7];
  if (pContext->DoClear) {
    GUI_SetBkColor(pContext->BkColor);
    GUI_Clear();
  }
  GUI_SetFont(&GUI_FontD24x32);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetColor(GUI_GRAY);
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_DispStringHCenterAt("Below arrow", XSize / 2, YSize / 2 - 20);
  if (iLast != i) {
    float Angle = 0.02 * (float)i;
    iLast = i;
    GUI_RotatePolygon(aPoint, _aArrow, 7, Angle);
  }
  GUI_SetColor(GUI_WHITE);
  GUI_FillPolygon(&aPoint[0], 7, XSize / 2, YSize / 2 + 30);
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetColor(GUI_DARKGRAY);
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_DispStringHCenterAt("Above arrow", XSize / 2, YSize / 2);
}

/*********************************************************************
*
*       GUIDEMO_ShowMemoryDevice
*
**********************************************************************
*/

void GUIDEMO_ShowMemoryDevice(void) {
  int i;
  U32 tDiff, t0;
  tDrawContext DrawContext;
  GUI_RECT rView, rPrev, rTemp;
  GUIDEMO_ShowIntro("Memory devices",
                    "\nFor flicker free animation"
                    "\nand other purposes");
  GUIDEMO_NotifyStartNext();
  GUI_SetBkColor(GUI_GREEN); 
  GUI_Clear();
  /* Use banding memory device  */
  GUI_GetClientRect(&rView);  
  DrawContext.BkColor = GUI_ColorIsAvailable(GUI_RED) ? GUI_RED : GUI_BLACK;
  GUI_SetBkColor(DrawContext.BkColor);
  GUI_Clear();
  t0 = GUI_GetTime();
  for (i = 0; tDiff = GUI_GetTime() - t0, (tDiff < 8000) && !GUIDEMO_CheckCancel(); i++) {
    U32 t = GUI_GetTime();
    DrawContext.Angle = 90 + tDiff / 50;
    /* Calculate required size */
    {
      GUI_HMEM hMem = GUI_MEASDEV_Create();
      GUI_MEASDEV_Select(hMem);
      DrawContext.DoClear = 0;
      _Draw(&DrawContext);
      GUI_MEASDEV_GetRect(hMem, &rView);
      GUI_MEASDEV_Delete(hMem);
      rTemp = rView;
      if (i)
        GUI_MergeRect(&rView, &rView, &rPrev);
      rPrev = rTemp;
    }
    DrawContext.DoClear = 1;
    GUI_MEMDEV_Draw(&rView, _Draw, &DrawContext, 0, GUI_MEMDEV_NOTRANS);
    t = (GUI_GetTime() - t);
    if (t < 20) {
      GUI_Delay(20 -t);
    }
  }
  GUI_SetFont(&GUI_FontComic24B_ASCII);
  GUI_SetColor(GUI_WHITE);
  GUI_SetBkColor(DrawContext.BkColor);
  GUI_DispStringAt("ms/Update: ", 10 , 200);
  if (i) {
    GUI_DispDecMin(tDiff / i);
  }
  GUIDEMO_Delay(1000);
  GUI_Clear();
}

#else

  void GUIDEMO_ShowMemoryDevice(void) {}

#endif /* GUI_SUPPORT_MEMDEV */



