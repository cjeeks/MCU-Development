#ifndef _MACRO_H
#define _MACRO_H

#include <intrinsics.h>
#define EXT_CLK_32768 1
#if EXT_CLK_32768
#define   XTAL   18
#else
#define   XTAL   16   //可定义为所用的晶振频率（单位Mhz）
#endif

#define   delay(x)      __delay_cycles ( (unsigned long )x )
#define   delay_us(x)   __delay_cycles ( (unsigned long )x * XTAL) 
#define   delay_ms(x)   __delay_cycles ( (unsigned long )x * XTAL*1000) 
#define   delay_s(x)    __delay_cycles ( (unsigned long )x * XTAL*500000)
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
#define	u8 unsigned char
#define	u16 unsigned int
#define	u32 unsigned long

#endif