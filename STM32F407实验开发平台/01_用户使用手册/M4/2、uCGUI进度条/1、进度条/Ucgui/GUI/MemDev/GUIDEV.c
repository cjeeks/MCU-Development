/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIDEV.c
Purpose     : Implementation of memory devices
---------------------------END-OF-HEADER------------------------------
*/


#include <string.h>
#include "GUI_Private.h"
#include "GUIDebug.h"
#if GUI_WINSUPPORT
  #include "WM.h"
#endif

/* Memory device capabilities are compiled only if support for them is enabled.*/ 
#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       internal routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MEMDEV__GetRect
*/
void GUI_MEMDEV__GetRect(GUI_RECT* pRect) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  pRect->x0 = pDev->x0;
  pRect->y0 = pDev->y0;
  pRect->x1 = pDev->x0 + pDev->XSize-1;
  pRect->y1 = pDev->y0 + pDev->YSize-1;
}

/*********************************************************************
*
*       GUI_MEMDEV__Color2Index
*/
unsigned int GUI_MEMDEV__Color2Index(LCD_COLOR Color) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  return pDev->pfColor2Index(Color);
}

/*********************************************************************
*
*       GUI_MEMDEV__Index2Color
*/
LCD_COLOR GUI_MEMDEV__Index2Color(int Index) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  return pDev->pfIndex2Color(Index);
}

/*********************************************************************
*
*       GUI_MEMDEV__GetIndexMask
*/
unsigned int GUI_MEMDEV__GetIndexMask(void) {
  GUI_MEMDEV * pDev = GUI_MEMDEV_H2P(GUI_Context.hDevData);
  return pDev->pfGetIndexMask();
}

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_MEMDEV_Delete
*/
void GUI_MEMDEV_Delete(GUI_MEMDEV_Handle hMemDev) {
/* Make sure memory device is not used */
  GUI_LOCK();
  if (hMemDev) {
    GUI_MEMDEV* pDev;
    if (GUI_Context.hDevData == hMemDev) {
	    GUI_SelectLCD();
    }
    pDev = GUI_MEMDEV_H2P(hMemDev);
    /* Delete the associated usage device */
    if (pDev->hUsage)
      GUI_USAGE_DecUseCnt(pDev->hUsage);
    GUI_ALLOC_Free(hMemDev);
  }
  GUI_UNLOCK();
}

/*********************************************************************
*
*       GUI_MEMDEV__CreateFixed
*/
GUI_MEMDEV_Handle GUI_MEMDEV__CreateFixed(int x0, int y0, int xsize, int ysize, int Flags
                                        ,const tLCDDEV_APIList * pMemDevAPI
                                        ,tLCDDEV_Color2Index*        pfColor2Index
                                        ,tLCDDEV_Index2Color*        pfIndex2Color
                                        ,tLCDDEV_GetIndexMask*       pfGetIndexMask) {
  I32 MemSize;
  GUI_USAGE_Handle hUsage = 0;
  unsigned int BitsPerPixel, BytesPerLine;
  GUI_MEMDEV_Handle hMemDev;
  BitsPerPixel = pMemDevAPI->BitsPerPixel;
  BytesPerLine = (xsize * BitsPerPixel + 7) >> 3;     /* Note: This code works with 8 and 16 bit memory devices. If other BPPs are introduced for MemDevs, it needs to be changed */
  /* Calc available MemSize */
  MemSize = GUI_ALLOC_GetMaxSize();
  if (!(Flags & GUI_MEMDEV_NOTRANS)) {
    MemSize = (MemSize / 4) * 3;   /* We need to reserve some memory for usage object ... TBD: This can be optimized as we do not use memory perfectly. */
  }
  if (ysize<=0) {
    int MaxLines = (MemSize - sizeof(GUI_MEMDEV)) / BytesPerLine;
    ysize = (MaxLines > -ysize) ? -ysize : MaxLines;
  }
  if (!(Flags & GUI_MEMDEV_NOTRANS)) {
    /* Create the usage map */
    hUsage = GUI_USAGE_BM_Create(x0, y0, xsize, ysize, 0);
  }
  /* Check if we can alloc sufficient memory */
  if (ysize <= 0) {
    GUI_DEBUG_WARN("GUI_MEMDEV_Create: Too little memory");
    GUI_UNLOCK();
    return 0;    
  }
  MemSize = ysize * BytesPerLine + sizeof(GUI_MEMDEV);
  if (Flags & GUI_MEMDEV_NOTRANS) {
    hMemDev = GUI_ALLOC_AllocNoInit(MemSize);
  } else {
    hMemDev = GUI_ALLOC_AllocZero(MemSize);
  }
  if (hMemDev) {
    GUI_MEMDEV* pDevData;
    pDevData = GUI_MEMDEV_H2P(hMemDev);
    pDevData->x0            = x0;
    pDevData->y0            = y0;
    pDevData->XSize         = xsize;
    pDevData->YSize         = ysize;
    pDevData->NumColors     = 
    #if GUI_NUM_LAYERS == 1
      LCD_GET_NUMCOLORS();
    #else
      LCD_GetNumColorsEx(GUI_Context.SelLayer);
    #endif
    pDevData->BytesPerLine  = BytesPerLine;
    pDevData->hUsage        = hUsage;
    /* Set color conversion routine pointers */
    pDevData->pfColor2Index = pfColor2Index;    /* LCD_L0_Color2Index; */
    pDevData->pfIndex2Color = pfIndex2Color;    /* LCD_L0_Index2Color; */
    pDevData->pfGetIndexMask= pfGetIndexMask;   /* LCD_L0_GetIndexMask */

    pDevData->pAPIList      = pMemDevAPI;
    pDevData->BitsPerPixel  = BitsPerPixel;
    #if (GUI_NUM_LAYERS > 1)   /* Size opt., preprocessor not required */
      pDevData->LayerIndex  = GUI_Context.SelLayer;
    #else
      pDevData->LayerIndex  = 0;
    #endif
  } else {
    if (hUsage) {
      GUI_ALLOC_Free(hUsage);
    }
    GUI_DEBUG_WARN("GUI_MEMDEV_Create: Alloc failed");
  }
  return hMemDev;
}

/*********************************************************************
*
*       GUI_MEMDEV_CreateEx
*/
GUI_MEMDEV_Handle GUI_MEMDEV_CreateEx(int x0, int y0, int xSize, int ySize, int Flags) {
  GUI_MEMDEV_Handle hMemDev;
  const tLCDDEV_APIList * pDeviceAPI;
  tLCDDEV_Color2Index   * pfColor2Index;
  tLCDDEV_Index2Color   * pfIndex2Color;
  tLCDDEV_GetIndexMask  * pfGetIndexMask;
  GUI_LOCK();
  #if (GUI_NUM_LAYERS > 1)   /* Size opt., preprocessor not required */
    pDeviceAPI = LCD_aAPI[GUI_Context.SelLayer];
  #else
    pDeviceAPI = LCD_aAPI[0];
  #endif
  if (GUI_Context.hDevData == 0) {
    pfColor2Index = GUI_Context.pDeviceAPI->pfColor2Index;    /* LCD_L0_Color2Index; */
    pfIndex2Color = GUI_Context.pDeviceAPI->pfIndex2Color;    /* LCD_L0_Index2Color; */
    pfGetIndexMask= GUI_Context.pDeviceAPI->pfGetIndexMask;   /* LCD_L0_GetIndexMask */
  } else {
    /* If a memory device is already selected, we create a compatible one by copying its data */
    GUI_MEMDEV* pDevSel;
    pDevSel = GUI_MEMDEV_H2P(GUI_Context.hDevData);
    pfColor2Index = pDevSel->pfColor2Index;
    pfIndex2Color = pDevSel->pfIndex2Color;
    pfGetIndexMask= pDevSel->pfGetIndexMask;
  }
  hMemDev = GUI_MEMDEV__CreateFixed(x0, y0, xSize, ySize, Flags, pDeviceAPI->pMemDevAPI, 
                                    pfColor2Index, pfIndex2Color ,pfGetIndexMask);
  GUI_UNLOCK();
  return hMemDev;
}
/*********************************************************************
*
*       GUI_MEMDEV_Create
*/
GUI_MEMDEV_Handle GUI_MEMDEV_Create(int x0, int y0, int xsize, int ysize) {
  return GUI_MEMDEV_CreateEx(x0, y0, xsize, ysize, GUI_MEMDEV_HASTRANS);
}

/*********************************************************************
*
*       GUI_MEMDEV_Select
*/
GUI_MEMDEV_Handle GUI_MEMDEV_Select(GUI_MEMDEV_Handle hMem) {
  GUI_MEMDEV_Handle r;
  GUI_LOCK();
  r = GUI_Context.hDevData;
  if (hMem == 0) {
    GUI_SelectLCD();
  } else {
    GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(hMem);
    #if GUI_WINSUPPORT
      WM_Deactivate();
    #endif
    /* If LCD was selected Save cliprect */
    if (GUI_Context.hDevData == 0) {
      GUI_Context.ClipRectPrev = GUI_Context.ClipRect;
    }
    GUI_Context.hDevData = hMem;
    GUI_Context.pDeviceAPI = pDev->pAPIList;
    LCD_SetClipRectMax();
  }
  GUI_UNLOCK();
  return r;
}

/*********************************************************************
*
*       GUI_MEMDEV__WriteToActiveAt
*/
void GUI_MEMDEV__WriteToActiveAt(GUI_MEMDEV_Handle hMem,int x, int y) {
  GUI_MEMDEV* pDev = GUI_MEMDEV_H2P(hMem);
  GUI_USAGE_h hUsage = pDev->hUsage; 
  GUI_USAGE*  pUsage;
  int YSize = pDev->YSize;
  int yi;
  unsigned int BytesPerLine = pDev->BytesPerLine;
  unsigned int BitsPerPixel = pDev->BitsPerPixel;
  int BytesPerPixel = BitsPerPixel >> 3;
  U8* pData = (U8*)(pDev+1);
  if (hUsage) {
    pUsage = GUI_USAGE_H2P(hUsage);
    for (yi = 0; yi < YSize; yi++) {
      int xOff = 0;
      int XSize;
      XSize = GUI_USAGE_GetNextDirty(pUsage, &xOff, yi);
      if (XSize == pDev->XSize) {
        /* If the entire line is affected, calculate the number of entire lines */
        int y0 = yi;
        while ((GUI_USAGE_GetNextDirty(pUsage, &xOff, yi + 1)) == XSize) {
          yi++;
        }
		    LCD_DrawBitmap(x, y + y0, pDev->XSize, yi - y0 + 1, 1, 1, BitsPerPixel, BytesPerLine, pData, NULL);
        pData += (yi - y0 + 1) * BytesPerLine;
      } else {
        /* Draw the partial line which needs to be drawn */
        for (; XSize; ) {
          LCD_DrawBitmap(x + xOff, y + yi, XSize, 1, 1, 1, BitsPerPixel, BytesPerLine, pData + xOff * BytesPerPixel, NULL);
          xOff += XSize;
          XSize = GUI_USAGE_GetNextDirty(pUsage, &xOff, yi);
        }
        pData += BytesPerLine;
      }
    }
  } else {
		LCD_DrawBitmap(x, y, pDev->XSize, YSize, 1, 1, BitsPerPixel, BytesPerLine, pData, NULL);
  }
}

/*********************************************************************
*
*       GUI_MEMDEV_CopyToLCDAt
*/
void GUI_MEMDEV_CopyToLCDAt(GUI_MEMDEV_Handle hMem, int x, int y) {
  if (hMem) {
    GUI_MEMDEV_Handle hMemPrev;
    GUI_MEMDEV* pDevData;
  #if (GUI_WINSUPPORT)
    GUI_RECT r;
  #endif
  #if GUI_NUM_LAYERS > 1
    int PrevLayer;
  #endif
    GUI_LOCK();
    hMemPrev = GUI_Context.hDevData;
    pDevData = (GUI_MEMDEV*) GUI_ALLOC_h2p(hMem);  /* Convert to pointer */
    /* Make sure LCD is selected as device */
  #if GUI_NUM_LAYERS > 1
    PrevLayer = GUI_SelectLayer(pDevData->LayerIndex);
  #else
    GUI_SelectLCD();  /* Activate LCD */
  #endif
    if (x == GUI_POS_AUTO) {
      x = pDevData->x0;
      y = pDevData->y0;
    }
  #if (GUI_WINSUPPORT)
    /* Calculate rectangle */
    r.x1 = (r.x0 = x) + pDevData->XSize-1;
    r.y1 = (r.y0 = y) + pDevData->YSize-1;;
    /* Do the drawing. Window manager has to be on */
    WM_Activate();
    WM_ITERATE_START(&r) {
  #endif
    GUI_MEMDEV__WriteToActiveAt(hMem, x, y);
  #if (GUI_WINSUPPORT)
    } WM_ITERATE_END();
  #endif
  #if GUI_NUM_LAYERS > 1
    GUI_SelectLayer(PrevLayer);
  #endif
    /* Reactivate previously used device */
    GUI_MEMDEV_Select(hMemPrev);
    GUI_UNLOCK();
  }
}

/*********************************************************************
*
*       GUI_MEMDEV_CopyToLCD
*/
void GUI_MEMDEV_CopyToLCD(GUI_MEMDEV_Handle hMem) {
  GUI_MEMDEV_CopyToLCDAt(hMem, GUI_POS_AUTO, GUI_POS_AUTO);
}

#else

void GUIDEV_C(void) {}

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
