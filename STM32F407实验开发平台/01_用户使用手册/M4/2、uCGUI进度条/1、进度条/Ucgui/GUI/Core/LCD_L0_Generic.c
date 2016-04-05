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
File        : LCD_L0_Generic.c
Purpose     : Color conversion routines for LCD-drivers
              This file may not be compiled by itself, but needs
              to be included in every LCD driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef LCD_INCLUDEDRIVER_H     /* includes only for stand-alone compilation, not as included file */
  #include <stddef.h>           /* needed for definition of NULL */
  #include "LCD_Private.h"      /* private modul definitions & config */
  #include "GUI_Private.h"
  #include "GUIDebug.h"
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define FIXEDPALETTE LCD_FIXEDPALETTE

#if   FIXEDPALETTE == -1     /* User defined color conversion routines */
  #define COLOR2INDEX(Color) LCD_Color2Index_User(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_User(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_User()
#elif FIXEDPALETTE == 0      /* User defined colors (LCD_PHYSCOLORS) */
  #define COLOR2INDEX(Color) LCD_Color2Index_0(Color, &LCD_PhysPal)
  #define INDEX2COLOR(Index) LCD_Index2Color_0(Index, &LCD_PhysPal)
  #define GETINDEXMASK()     LCD_GetIndexMask_0()
#elif FIXEDPALETTE == 1
  #define COLOR2INDEX(Color) LCD_Color2Index_1(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_1(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_1()
#elif FIXEDPALETTE == 2
  #define COLOR2INDEX(Color) LCD_Color2Index_2(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_2(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_2()
#elif FIXEDPALETTE == 4
  #define COLOR2INDEX(Color) LCD_Color2Index_4(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_4(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_4()
#elif (FIXEDPALETTE == 111) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_111(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_111(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_111()
#elif (FIXEDPALETTE == 111) && (LCD_SWAP_RB)
  #define COLOR2INDEX(Color) LCD_Color2Index_M111(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M111(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M111()
#elif (FIXEDPALETTE == 222) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_222(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_222(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_222()
#elif (FIXEDPALETTE == 222) && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M222(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M222(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M222()
#elif (FIXEDPALETTE == 233) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_233(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_233(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_233()
#elif (FIXEDPALETTE == 233) && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M233(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M233(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M233()
#elif (FIXEDPALETTE == 323) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_323(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_323(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_323()
#elif (FIXEDPALETTE == 323) && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M323(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M323(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M323()
#elif (FIXEDPALETTE == 332) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_332(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_332(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_332()
#elif (FIXEDPALETTE == 332) && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M332(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M332(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M332()
#elif (FIXEDPALETTE == 444121)
  #define COLOR2INDEX(Color) LCD_Color2Index_444_12_1(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_444_12_1(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_444_12_1()
#elif (FIXEDPALETTE == 44412) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_444_12(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_444_12(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_444_12()
#elif (FIXEDPALETTE == 44416)  && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_444_16(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_444_16(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_444_16()
#elif (FIXEDPALETTE == 44412)  && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M444_12(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M444_12(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M444_12()
#elif (FIXEDPALETTE == 44416)  && (LCD_SWAP_RB==1)
  #define COLOR2INDEX(Color) LCD_Color2Index_M444_16(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M444_16(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M444_16()
#elif (FIXEDPALETTE == 555)  && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_555(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_555(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_555()
#elif (FIXEDPALETTE == 555)  && (LCD_SWAP_RB)
  #define COLOR2INDEX(Color) LCD_Color2Index_M555(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M555(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M555()
#elif (FIXEDPALETTE == 556) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_556(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_556(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_556()
#elif (FIXEDPALETTE == 556) && (LCD_SWAP_RB)
  #define COLOR2INDEX(Color) LCD_Color2Index_M556(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M556(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M556()
#elif (FIXEDPALETTE == 565) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_565(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_565(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_565()
#elif (FIXEDPALETTE == 565) && (LCD_SWAP_RB)
  #define COLOR2INDEX(Color) LCD_Color2Index_M565(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M565(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M565()
#elif (FIXEDPALETTE == 655) && (LCD_SWAP_RB==0)
  #define COLOR2INDEX(Color) LCD_Color2Index_655(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_655(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_655()
#elif (FIXEDPALETTE == 655) && (LCD_SWAP_RB)
  #define COLOR2INDEX(Color) LCD_Color2Index_M655(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_M655(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_M655()
#elif FIXEDPALETTE == 8666
  #define COLOR2INDEX(Color) LCD_Color2Index_8666(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_8666(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_8666()
#elif FIXEDPALETTE == 86661
  #define COLOR2INDEX(Color) LCD_Color2Index_8666_1(Color)
  #define INDEX2COLOR(Index) LCD_Index2Color_8666_1(Index)
  #define GETINDEXMASK()     LCD_GetIndexMask_8666_1()
#else
  #error Unsupported color mode
#endif

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

#if (LCD_FIXEDPALETTE==0)
  #if !LCD_PHYSCOLORS_IN_RAM
    const
  #endif
  LCD_COLOR       LCD_PhysColors[]   = { LCD_PHYSCOLORS };
  const LCD_PHYSPALETTE LCD_PhysPal  = { LCD_NUM_COLORS, &LCD_PhysColors[0] };
#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*           LCD_L0_Color2Index
*/
unsigned int LCD_L0_Color2Index(LCD_COLOR Color) {
  unsigned int Index;
  Index = COLOR2INDEX(Color);
  #if LCD_REVERSE
    Index ^= ((1<<LCD_BITSPERPIXEL)-1);
  #endif
  return Index;
}

/*********************************************************************
*
*       LCD_L0_Index2Color
*/
LCD_COLOR LCD_L0_Index2Color(int Index) {
  #if LCD_REVERSE
    Index ^= ((1<<LCD_BITSPERPIXEL)-1);
  #endif
  return INDEX2COLOR(Index);
}

/*********************************************************************
*
*       LCD_L0_GetIndexMask
*/
unsigned int LCD_L0_GetIndexMask(void) {
  return GETINDEXMASK();
}

/*********************************************************************
*
*       LCD_L0_GetRect
*/
void LCD_L0_GetRect(LCD_RECT *pRect) {
  pRect->x0 = 0;
  pRect->y0 = 0;
  pRect->x1 = LCD_XSIZE - 1;
  pRect->y1 = LCD_YSIZE - 1;
}

/*************************** End of file ****************************/
