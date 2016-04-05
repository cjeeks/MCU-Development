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
File        : LCD_1.C
Purpose     : Glue code for second display in a multi-controller
              environment
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>           /* needed for definition of NULL */
#include "LCD_Private.h"      /* private modul definitions & config */

#define LCD_1_C

#if GUI_NUM_LAYERS > 1


/*********************************************************************
*
*      Map the defines for this controller
*
*      #define LCD_<xxx> LCD_<xxx>_1
*
**********************************************************************
*/

#undef  LCD_CONTROLLER
#define LCD_CONTROLLER     LCD_CONTROLLER_1

#undef  LCD_XSIZE
#define LCD_XSIZE          LCD_XSIZE_1

#undef  LCD_YSIZE
#define LCD_YSIZE          LCD_YSIZE_1

#undef  LCD_BITSPERPIXEL
#define LCD_BITSPERPIXEL   LCD_BITSPERPIXEL_1

#undef  LCD_VYSIZE
#define LCD_VYSIZE         LCD_VYSIZE_1

#undef  LCD_MIRROR_X
#define LCD_MIRROR_X       LCD_MIRROR_X_1

#undef  LCD_MIRROR_Y
#define LCD_MIRROR_Y       LCD_MIRROR_Y_1

#undef  LCD_SWAP_XY
#define LCD_SWAP_XY        LCD_SWAP_XY_1

#undef  LCD_BITSPERPIXEL
#define LCD_BITSPERPIXEL   LCD_BITSPERPIXEL_1

/* Optional defines */

#ifdef LCD_CACHE_1
  #ifdef  LCD_CACHE
    #undef  LCD_CACHE
  #endif
  #define LCD_CACHE LCD_CACHE_1
#endif

#ifdef LCD_CACHE_CONTROL_1
  #ifdef LCD_CACHE_CONTROL
    #undef  LCD_CACHE_CONTROL
  #endif
  #define LCD_CACHE_CONTROL LCD_CACHE_CONTROL_1
#endif

#ifdef LCD_CHECKBUSY_1
  #ifdef LCD_CHECKBUSY
    #undef  LCD_CHECKBUSY
  #endif
  #define LCD_CHECKBUSY   LCD_CHECKBUSY_1
#endif

#ifdef LCD_FIRSTSEG0_1
  #undef  LCD_FIRSTSEG0
  #define LCD_FIRSTSEG0   LCD_FIRSTSEG0_1
#endif

#ifdef LCD_LASTSEG0_1
  #undef  LCD_LASTSEG0
  #define LCD_LASTSEG0    LCD_LASTSEG0_1
#endif

#ifdef LCD_FIRSTCOM0_1
  #undef  LCD_FIRSTCOM0
  #define LCD_FIRSTCOM0   LCD_FIRSTCOM0_1
#endif

#ifdef LCD_LASTCOM0_1
  #undef  LCD_LASTCOM0
  #define LCD_LASTCOM0    LCD_LASTCOM0_1
#endif

#ifdef LCD_XORG0_1
  #undef  LCD_XORG0
  #define LCD_XORG0       LCD_XORG0_1
#endif

#ifdef LCD_YORG0_1
  #undef  LCD_YORG0
  #define LCD_YORG0       LCD_YORG0_1
#endif

#ifdef LCD_SWAP_RB_1
  #undef  LCD_SWAP_RB
  #define LCD_SWAP_RB     LCD_SWAP_RB_1
#endif

#ifdef LCD_FIXEDPALETTE_1
  #undef  LCD_FIXEDPALETTE
  #define LCD_FIXEDPALETTE LCD_FIXEDPALETTE_1
#endif

#ifdef LCD_DELTA_MODE_1
  #undef  LCD_DELTA_MODE
  #define LCD_DELTA_MODE LCD_DELTA_MODE_1
#endif

#ifdef LCD_BITSPERPIXEL_L0_1
  #undef  LCD_BITSPERPIXEL_L0
  #define LCD_BITSPERPIXEL_L0 LCD_BITSPERPIXEL_1
#endif

/*********************************************************************
*
*      Rename identifiers
*
**********************************************************************
*/
#define LCD_L0_Color2Index   LCD_L0_1_Color2Index
#define LCD_L0_ControlCache  LCD_L0_1_ControlCache
#define LCD_L0_DrawBitmap    LCD_L0_1_DrawBitmap
#define LCD_L0_DrawHLine     LCD_L0_1_DrawHLine
#define LCD_L0_DrawVLine     LCD_L0_1_DrawVLine
#define LCD_L0_DrawPixel     LCD_L0_1_DrawPixel
#define LCD_L0_FillRect      LCD_L0_1_FillRect
#define LCD_L0_GetPixelIndex LCD_L0_1_GetPixelIndex
#define LCD_L0_GetRect       LCD_L0_1_GetRect
#define LCD_L0_Index2Color   LCD_L0_1_Index2Color
#define LCD_L0_Init          LCD_L0_1_Init
#define LCD_L0_Off           LCD_L0_1_Off
#define LCD_L0_On            LCD_L0_1_On
#define LCD_L0_ReInit        LCD_L0_1_ReInit
#define LCD_L0_Refresh       LCD_L0_1_Refresh
#define LCD_L0_SetLUTEntry   LCD_L0_1_SetLUTEntry
#define LCD_L0_SetOrg        LCD_L0_1_SetOrg
#define LCD_L0_SetPixelIndex LCD_L0_1_SetPixelIndex
#define LCD_L0_XorPixel      LCD_L0_1_XorPixel
#define LCD_L0_CheckInit     LCD_L0_1_CheckInit
#define LCD_L0_GetIndexMask  LCD_L0_1_GetIndexMask

#define LCD_PhysColors       LCD_PhysColors_1
#define LCD_PhysPal          LCD_PhysPal_1

/*********************************************************************
*
*      Include the generic part & driver
*
**********************************************************************
*/

#define LCD_DISPLAY_INDEX 1
#include "LCD_IncludeDriver.h"

#else
  void LCD_1_c(void);
  void LCD_1_c(void) {} /* avoid empty object files */
#endif

