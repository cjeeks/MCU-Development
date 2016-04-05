/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   IAR STM32-SK Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  APP_CFG_PROBE_OS_PLUGIN_EN      DEF_ENABLED            /* DEF_ENABLED = Present, DEF_DISABLED = Not Present        */
#define  APP_CFG_PROBE_COM_EN            DEF_ENABLED
#define  APP_CFG_LCD_EN                  DEF_ENABLED
#define  APP_CFG_KSD_EN                  DEF_ENABLED

/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO               3
#define  APP_CFG_TASK_PB_PRIO                  4
#define  APP_CFG_TASK_JOY_PRIO                 5

#define  OS_PROBE_TASK_PRIO                    9
#define  OS_PROBE_TASK_ID                      9

#define  KSD_CFG_TASK_LED_PRIO                10
#define  KSD_CFG_TASK_LED_ID                  10

#define  APP_CFG_TASK_LCD_PRIO                11

#define  OS_TASK_TMR_PRIO              (OS_LOWEST_PRIO - 2)

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE         128
#define  APP_CFG_TASK_PB_STK_SIZE            128
#define  APP_CFG_TASK_LCD_STK_SIZE           512
#define  APP_CFG_TASK_JOY_STK_SIZE           128
#define  APP_CFG_TASK_PROBE_STR_STK_SIZE     128

#define  OS_PROBE_TASK_STK_SIZE              128

#define  KSD_CFG_TASK_LED_STK_SIZE           128

/*
*********************************************************************************************************
*                               uC/Probe plug-in for uC/OS-II CONFIGURATION
*********************************************************************************************************
*/

#define  OS_PROBE_TASK                         1                /* Task will be created for uC/Probe OS Plug-In             */
#define  OS_PROBE_TMR_32_BITS                  1                /* uC/Probe OS Plug-In timer is a 32-bit timer              */
#define  OS_PROBE_TIMER_SEL                    2
#define  OS_PROBE_HOOKS_EN                     1

/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#define  TRACE_LEVEL_OFF                       0
#define  TRACE_LEVEL_INFO                      1
#define  TRACE_LEVEL_DBG                       2

#define  APP_CFG_TRACE_LEVEL             TRACE_LEVEL_INFO
#define  APP_CFG_TRACE                   pritnf           

#define  BSP_CFG_TRACE_LEVEL             TRACE_LEVEL_INFO
#define  BSP_CFG_TRACE                   printf               

#define  APP_TRACE_INFO(x)               ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_CFG_TRACE x) : (void)0)

#define  BSP_TRACE_INFO(x)               ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_INFO) ? (void)(BSP_CFG_TRACE x) : (void)0)
#define  BSP_TRACE_DBG(x)                ((BSP_CFG_TRACE_LEVEL  >= TRACE_LEVEL_DBG)  ? (void)(BSP_CFG_TRACE x) : (void)0)

#endif
