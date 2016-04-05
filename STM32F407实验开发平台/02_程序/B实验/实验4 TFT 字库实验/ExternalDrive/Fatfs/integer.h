/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef __INTEGER_H_
#define __INTEGER_H_

//#include "stm32f10x_type.h" 
//#if 0
//#include <windows.h>
//#else

/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef signed char		CHAR;
typedef unsigned char	UCHAR;
typedef unsigned char	BYTE;

/* These types must be 16-bit integer */
typedef short			SHORT;
typedef unsigned short	USHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types must be 32-bit integer */
typedef long			LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

typedef unsigned char   INT8U;        // 无符号8位整型变量                     
typedef signed   char   INT8S;        // 有符号8位整型变量                        
typedef unsigned int    INT16U;       // 无符号16位整型变量                       
typedef signed   int    INT16S;       // 有符号16位整型变量                       
typedef unsigned long   INT32U;       // 无符号32位整型变量                       
typedef signed long     INT32S;       // 有符号32位整型变量                       
/* Boolean type */
#ifndef __STM32F10x_TYPE_H    
/*这个文件包含定义typedef enum {FALSE = 0, TRUE = !FALSE} bool;将造成命名冲突 */
typedef enum { FALSE = 0, TRUE } BOOL;
#else
typedef bool BOOL;
#endif

#define _INTEGER
#endif
