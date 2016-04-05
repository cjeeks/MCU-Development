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
File        : LCD_2.C
Purpose     : Glue code for second display in a multi-controller
              environment
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Private.h"      /* private modul definitions & config */

#define LCD_2_C

#if GUI_NUM_LAYERS > 2


/*********************************************************************
*
*      Map the defines for this controller
*
*      #define LCD_<xxx> LCD_<xxx>_2
*
**********************************************************************
*/

#undef  LCD_CONTROLLER
#define LCD_CONTROLLER     LCD_CONTROLLER_2

#undef  LCD_XSIZE
#define LCD_XSIZE          LCD_XSIZE_2

#undef  LCD_YSIZE
#define LCD_YSIZE          LCD_YSIZE_2

#undef  LCD_BITSPERPIXEL
#define LCD_BITSPERPIXEL   LCD_BITSPERPIXEL_2

#undef  LCD_VYSIZE
#define LCD_VYSIZE         LCD_VYSIZE_2

#undef  LCD_MIRROR_X
#define LCD_MIRROR_X       LCD_MIRROR_X_2

#undef  LCD_MIRROR_Y
#define LCD_MIRROR_Y       LCD_MIRROR_Y_2

#undef  LCD_SWAP_XY
#define LCD_SWAP_XY        LCD_SWAP_XY_2

#undef  LCD_BITSPERPIXEL
#define LCD_BITSPERPIXEL LCD_BITSPERPIXEL_2

/* Optional defines */

#ifdef LCD_CACHE_2
  #ifdef  LCD_CACHE
    #undef  LCD_CACHE
  #endif
  #define LCD_CACHE LCD_CACHE_2
#endif

#ifdef LCD_CACHE_CONTROL_2
  #ifdef LCD_CACHE_CONTROL
    #undef  LCD_CACHE_CONTROL
  #endif
  #define LCD_CACHE_CONTROL LCD_CACHE_CONTROL_2
#endif

#ifdef LCD_CHECKBUSY_2
  #ifdef LCD_CHECKBUSY
    #undef  LCD_CHECKBUSY
  #endif
  #define LCD_CHECKBUSY   LCD_CHECKBUSY_2
#endif

#ifdef LCD_FIRSTSEG0_2
  #undef  LCD_FIRSTSEG0
  #define LCD_FIRSTSEG0   LCD_FIRSTSEG0_2
#endif

#ifdef LCD_LASTSEG0_2
  #undef  LCD_LASTSEG0
  #define LCD_LASTSEG0    LCD_LASTSEG0_2
#endif

#ifdef LCD_FIRSTCOM0_2
  #undef  LCD_FIRSTCOM0
  #define LCD_FIRSTCOM0   LCD_FIRSTCOM0_2
#endif

#ifdef LCD_LASTCOM0_2
  #undef  LCD_LASTCOM0
  #define LCD_LASTCOM0    LCD_LASTCOM0_2
#endif

#ifdef LCD_XORG0_2
  #undef  LCD_XORG0
  #define LCD_XORG0       LCD_XORG0_2
#endif

#ifdef LCD_YORG0_2
  #undef  LCD_YORG0
  #define LCD_YORG0       LCD_YORG0_2
#endif

#ifdef LCD_SWAP_RB_2
  #undef  LCD_SWAP_RB
  #define LCD_SWAP_RB     LCD_SWAP_RB_2
#endif

#ifdef LCD_FIXEDPALETTE_2
  #undef  LCD_FIXEDPALETTE
  #define LCD_FIXEDPALETTE LCD_FIXEDPALETTE_2
#endif

#ifdef LCD_DELTA_MODE_2
  #undef  LCD_DELTA_MODE
  #define LCD_DELTA_MODE LCD_DELTA_MODE_2
#endif

#ifdef LCD_BITSPERPIXEL_L0_2
  #undef  LCD_BITSPERPIXEL_L0
  #define LCD_BITSPERPIXEL_L0 LCD_BITSPERPIXEL_2
#endif

/*********************************************************************
*
*      Rename identifiers
*
**********************************************************************
*/
#define LCD_L0_Color2Index   LCD_L0_2_Color2Index
#define LCD_L0_ControlCache  LCD_L0_2_ControlCache
#define LCD_L0_DrawBitmap    LCD_L0_2_DrawBitmap
#define LCD_L0_DrawHLine     LCD_L0_2_DrawHLine
#define LCD_L0_DrawVLine     LCD_L0_2_DrawVLine
#define LCD_L0_DrawPixel     LCD_L0_2_DrawPixel
#define LCD_L0_FillRect      LCD_L0_2_FillRect
#define LCD_L0_GetPixelIndex LCD_L0_2_GetPixelIndex
#define LCD_L0_GetRect       LCD_L0_2_GetRect
#define LCD_L0_Index2Color   LCD_L0_2_Index2Color
#define LCD_L0_Init          LCD_L0_2_Init
#define LCD_L0_Off           LCD_L0_2_Off
#define LCD_L0_On            LCD_L0_2_On
#define LCD_L0_ReInit        LCD_L0_2_ReInit
#define LCD_L0_Refresh       LCD_L0_2_Refresh
#define LCD_L0_SetLUTEntry   LCD_L0_2_SetLUTEntry
#define LCD_L0_SetOrg        LCD_L0_2_SetOrg
#define LCD_L0_SetPixelIndex LCD_L0_2_SetPixelIndex
#define LCD_L0_XorPixel      LCD_L0_2_XorPixel
#define LCD_L0_CheckInit     LCD_L0_2_CheckInit
#define LCD_L0_GetIndexMask  LCD_L0_2_GetIndexMask

#define LCD_PhysColors       LCD_PhysColors_2
#define LCD_PhysPal          LCD_PhysPal_2

/*********************************************************************
*
*      Include the generic part & driver
*
**********************************************************************
*/

#define LCD_DISPLAY_INDEX 2
#include "LCD_IncludeDriver.h"

#else
  void LCD_2_c(void);
  void LCD_2_c(void) {} /* avoid empty object files */
#endif

