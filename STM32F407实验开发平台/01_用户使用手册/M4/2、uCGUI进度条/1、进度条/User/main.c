/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "ucos_ii.h"
#include <stdio.h>
#include "Gpio.h"
#include "gui.h"
#include "Systick.h"
#include "LedTest.h"
#include "WM.h"
#include "BUTTON.h"

#define STARTUP_TASK_PRIO              1
#define STARTUP_TASK_STK_SIZE          80
#define TOUCHTASK_PRIO                 10
#define TOUCHTASK_STK_SIZE             1000
#define LED_TASK_PRIO                  5
#define LED_TASK_STK_SIZE              5000

static void LedTask(void *p_arg);
static void TouchTask(void *p_arg);

static OS_STK starup_task_stk[STARTUP_TASK_STK_SIZE];
static OS_STK ledtask_stk[LED_TASK_STK_SIZE];
static OS_STK touchtask_stk[TOUCHTASK_STK_SIZE];

static void startup_task(void *p_arg)
{
    systick_init();
//#if(OS_TASK_STAT_EN > 0)
//    OSStatInit();
//#endif
//    
    OSTaskCreate(LedTask,(void*)0,&ledtask_stk[LED_TASK_STK_SIZE - 1],LED_TASK_PRIO);
    OSTaskCreate(TouchTask,(void*)0,&touchtask_stk[TOUCHTASK_STK_SIZE - 1],TOUCHTASK_PRIO);

    OSTaskDel(OS_PRIO_SELF);
}


int main(void)
{
    OSInit();
    OSTaskCreate(startup_task,(void*)0,&starup_task_stk[STARTUP_TASK_STK_SIZE - 1],STARTUP_TASK_PRIO);
    OSStart();
    return 0;
}


static void LedTask(void *p_arg)
{
  (void)p_arg;
	
	LEDGpio_Init();
	
	GUI_Init();
	GUI_SetBkColor(GUI_GREEN);   //设置背景颜色
	GUI_SetColor(GUI_RED);      //设置前景颜色，及字体和绘图的颜色
	GUI_Clear();                 //按指定颜色清屏

	GUI_DispStringAt("UCGUI OK!",10,10);        //显示字符
	GUI_SetFont(&GUI_Font4x6);
	GUI_DispStringAt("www.openmcu.com",10,100); //显示字符
	GUI_SetFont(&GUI_Font6x8);
	GUI_DispStringAt("www.openmcu.com",10,130); //显示字符
	GUI_SetFont(&GUI_Font8x16);
	GUI_DispStringAt("www.openmcu.com",10,160); //显示字符

	Panel();                             //显示面板
}

static void TouchTask(void *p_arg)
{
	u8 tick=0;
	(void)p_arg;

	GUI_CURSOR_Show();      //打开“鼠标显示”
	
	while(1) 
	{
		tick++;
		OSTimeDly(20); 
		GUI_TOUCH_Exec();
    GUI_Exec();         //界面绘制检测		
		if(tick&0x10)
		{
			LED1_ONOFF(Bit_RESET);
		}
		else
		{
			LED1_ONOFF(Bit_SET);
		}
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
