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
File        : GUIDEV_UsageBM.C
Purpose     : Implementation of memory devices
---------------------------END-OF-HEADER------------------------------
*/


#include <string.h>
#include "GUI_Protected.h"
#include "GUIDebug.h"

/* Memory device capabilities are compiled only if support for them is enabled.*/ 
#if GUI_SUPPORT_MEMDEV

/*********************************************************************
*
*       GUI_USAGE_BM structure
*
**********************************************************************
*/

typedef struct {
  GUI_USAGE Public;
  struct {
    int BytesPerLine;
  } Private;
} GUI_USAGE_BM;

/*********************************************************************
*
*       static code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_USAGE_BM_AddPixel
*/
static void GUI_USAGE_BM_AddPixel(GUI_USAGE* p, int x, int y) {
  U8* pData;
  GUI_USAGE_BM * pThis = (GUI_USAGE_BM*)p;
  #if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
    if ((x >= pThis->Public.x0 + pThis->Public.XSize) | (x < pThis->Public.x0)
      | (y >= pThis->Public.y0 + pThis->Public.YSize) | (y < pThis->Public.y0))
    {
      GUI_DEBUG_ERROROUT2("GUI_USAGE_BM_AddPixel: parameters out of bounds",x,y);
    }
  #endif
  x -= pThis->Public.x0;
  pData =  (U8*)(pThis+1); 
  pData += (y-pThis->Public.y0) * pThis->Private.BytesPerLine;
  pData += x>>3;
  *pData|= 0x80>>(x&7);
}

/*********************************************************************
*
*       GUI_USAGE_BM_AddHLine
*/
static void GUI_USAGE_BM_AddHLine(GUI_USAGE* p, int x, int y, int len) {
#if 0   /* Enable for the slower, but smaller version ... xxx*/
  while (len-- >0)
    GUI_USAGE_BM_AddPixel(h, x++,y);
#else
  U8* pData;
  GUI_USAGE_BM * pThis = (GUI_USAGE_BM*)p;
  /* Asserts */
  GUI_DEBUG_ERROROUT3_IF( x<pThis->Public.x0, "GUIDEV.c: MarkPixels: negative x offset, Act= %d, Border= %d, Clip= %d"
                    ,x, pThis->Public.x0, GUI_Context.ClipRect.x0);
  /* Calculate pointers */
  x -= pThis->Public.x0;
  pData =  (U8*)(pThis+1); 
  pData += (y-pThis->Public.y0) * pThis->Private.BytesPerLine;
  pData += x>>3;
  /* Set bits */
  {  
    int x1 = x+len-1;   /* last pixel */
    int NumBytes = (x1>>3) - (x>>3);
    U8 Mask0 = 0xff >> (x&7);
    U8 Mask1 = 0xff << (7-(x1&7));
    if (NumBytes ==0) {
      *pData |= (Mask0&Mask1);
    } else {
      *pData++ |= Mask0;               /* Mark first byte */
      /* Mark middle bytes */
      if (--NumBytes > 0) {
        memset (pData, 0xff, NumBytes);
        pData += NumBytes;
      }
      *pData |= Mask1;                 /* Mark last bytes */
    }
  }
#endif
}

/*********************************************************************
*
*       GUI_USAGE_BM_Clear
*/
static void GUI_USAGE_BM_Clear(GUI_USAGE* p) {
  GUI_USAGE_BM * pThis = (GUI_USAGE_BM*) p;
  memset (pThis+1, 0, pThis->Public.YSize * pThis->Private.BytesPerLine);
}

/*********************************************************************
*
*       GUI_USAGE_BM_GetNextDirty
*/
static int GUI_USAGE_BM_GetNextDirty(GUI_USAGE* p, int *pxOff, int yOff) {
  int x = *pxOff;
  int xEnd;
  GUI_USAGE_BM * pThis = (GUI_USAGE_BM*)p;
  int xSize = pThis->Public.XSize;
  U8* pData = (U8*)(pThis+1);
  if (yOff >= pThis->Public.YSize) {
    return 0;
  }
  pData += yOff * pThis->Private.BytesPerLine;
  pData += (x>>3);
  if (x>=xSize)
    return 0;
  {
/* Find first bit */
    int BytesLeft = ((xSize-1) >>3) - (x>>3);
    /* Check first byte */
    U8 Data = (*pData++) << (x&7);
    while (Data == 0) {
      if (BytesLeft ==0)
        return 0;
      Data = *pData++;
      BytesLeft--;
      x= (x+8) & ~7;
    }
    while ((Data&0x80) ==0) {
      Data<<=1;
      x++;
    }
/* Find last cleared byte */
    if (Data != 0xff) {   /* This line is simply a speed-opt and may be eliminated */
      xEnd =x;
      while (Data&0x40) {
        Data<<=1;
        xEnd++;
      }
    } else {
      xEnd =x+7;
    }
    if ((xEnd&7) ==7) {
      while (--BytesLeft >= 0) {
        if ((Data = *pData++) == 0xff) {
          xEnd+=8;
        } else {
          while (Data&0x80) {
            Data<<=1;
            xEnd++;
          }
          break;
        }
      }
    }

  }
  *pxOff =x;
  return xEnd-x+1;
}

/*********************************************************************
*
*       Delete
*/
static void _GUI_USAGE_BM_Delete(GUI_MEMDEV_Handle hDevUsage) {
  GUI_ALLOC_Free(hDevUsage);
}

/*********************************************************************
*
*       API List
*/
static const tUSAGE_APIList API = {
  GUI_USAGE_BM_AddPixel,     /* tUSAGE_AddPixel*         */
  GUI_USAGE_BM_AddHLine,     /* tUSAGE_AddHLine*         */
  GUI_USAGE_BM_Clear,        /* tUSAGE_Clear*            */
  0,                         /* tUSAGE_CreateCompatible* */
  _GUI_USAGE_BM_Delete,       /* tUSAGE_Delete*           */
  GUI_USAGE_BM_GetNextDirty  /* tUSAGE_GetNextDirty*     */

};

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_USAGE_BM_Create
*/
GUI_USAGE_Handle GUI_USAGE_BM_Create(int x0, int y0, int xsize, int ysize, int Flags) {
  int MemSize;
  int BytesPerLine;
  GUI_USAGE_Handle hMem;
  GUI_USE_PARA(Flags);
  BytesPerLine = ((xsize+15) >>4)<<1;  /* 2 byte alignment */
  MemSize = ysize*BytesPerLine +sizeof(GUI_USAGE_BM);
  hMem = GUI_ALLOC_AllocZero(MemSize);
  /* Check if we can alloc sufficient memory */
  if (!hMem) {
    GUI_DEBUG_ERROROUT("GUI_USAGE_BM_Create: Too little memory");
    return 0;    
  }
  {
    GUI_USAGE_BM * pUsage;
    GUI_LOCK();
    pUsage = (GUI_USAGE_BM*)GUI_ALLOC_h2p(hMem);
    pUsage->Public.x0    = x0;
    pUsage->Public.y0    = y0;
    pUsage->Public.XSize = xsize;
    pUsage->Public.YSize = ysize;
    pUsage->Public.pAPI  = &API;
    pUsage->Public.UseCnt= 1;
    pUsage->Private.BytesPerLine= BytesPerLine;
    GUI_UNLOCK();
  }
  return hMem;
}

#else

void GUIDEV_UsageBM(void) {} /* avoid empty object files */

#endif /* GUI_SUPPORT_MEMDEV */

/*************************** end of file ****************************/
