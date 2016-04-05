/**
  ******************************************************************************
  * @file    uart.c 
  * @author  Wangbao Dev Team
  * @version V1.0.0
  * @date    07-10-2012
  * @brief   uart program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 
#include "uart.h"
#include "string.h"
#include "lcd.h"
#include "stdio.h"
//typedef struct _FILE FILE;

char Date_Buf[10];
char BufferA[50];
uint8_t DBufferFlag=0;
uint8_t mark = 0;
	static unsigned char BufferCount=0;
void uart6_init(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 开启GPIO_D的时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	/* 开启串口3的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);


	USART_InitStructure.USART_BaudRate   = 115200; //115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;
	USART_InitStructure.USART_Parity     = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART6, &USART_InitStructure);

	/* 使能串口6*/
	USART_Cmd(USART6, ENABLE);
	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
}


void uart3_init(void)	//usart3
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
                                                           
	/* 开启GPIO_D的时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	/* 开启串口3的时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);


	USART_InitStructure.USART_BaudRate   = 9600;//115200;//;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;
	USART_InitStructure.USART_Parity     = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART3, &USART_InitStructure);

	/* 使能串口3 */
	USART_Cmd(USART3, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	USART_ClearFlag(USART3, USART_FLAG_TC);     /* 清发送外城标志，Transmission Complete flag */
}


void uart1_init(void)	//usart1
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
                                                           
	/* 开启GPIO_A的时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	/* 开启串口1的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1);

	USART_InitStructure.USART_BaudRate   = 9600;//9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;
	USART_InitStructure.USART_Parity     = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART1, &USART_InitStructure);

	/* 使能串口1*/
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

//debug uart中断
void USART3_IRQ(void)
{
  uint8_t ch;

	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(USART3);  //取出串口得到的数据
		USART_SendData(USART1, ch);
	}	
}

//GSM uart中断
void USART1_IRQ(void)
{
  uint8_t ch;
	static uint8_t count = 0, temp[] = {0};
	uint8_t a[1] = {'A'};

	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(USART1);  //取出串口得到的数据
	  USART_SendData(USART3, ch);
		
		temp[count] = ch;

		if(temp[count] == 0x0D)
		{
			temp[count] = ' ';
			LCD_ShowString(142, 160,a, White, Black);
			LCD_ShowString(150, 160,temp, White, Black);
			count = 0;	
		}
		if(temp[count] == 0x0A)
			temp[count] = ' ';
		
			
		count ++;
	}
}

void uart2_init(void)	//usart2
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
                                                           
	/* 开启GPIO_D的时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	/* 开启串口2的时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);


	USART_InitStructure.USART_BaudRate   = 115200;//9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;
	USART_InitStructure.USART_Parity     = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART2, &USART_InitStructure);

	/* 使能串口2*/
	USART_Cmd(USART2, ENABLE);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}


//中断
void USART2_IRQ(void)
{
  uint8_t ch;

	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(USART2);  //取出串口得到的数据
	//	USART_SendData(USART3, ch);
		Date_Buf[mark] = ch;
		if(mark++ >= 10)
		  mark = 0;
	}	
}


//RFID uart中断6
void USART6_IRQ(void)
{
	uint8_t ch;
	if(USART_GetFlagStatus(USART6,USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(USART6);  //取出串口得到的数据
	//	USART_SendData(USART6, ch);
		BufferA[BufferCount++]=ch;
		if(BufferCount>48)
		{
      DBufferFlag=1;
			BufferCount=0;
    }
		else
		{
			DBufferFlag=0;
		}
	}
}

void Send_Com()
{
	unsigned char i;	
	char Rfid_Id[9];
	char Rfid_Value[35];
	while(BufferCount<48);
	//if((BufferCount>48)||(BufferCount==48))
	//{
		////////////////////////////
		for(i=0;i<9;i++)
			Rfid_Id[i]=BufferA[i+1];
		LCD_ShowString(50, 180, "RFID_ID:", Red, Black);
		LCD_ShowString(114, 180, Rfid_Id, Red, Black);
		////////////////////////////
		for(i=0;i<35;i++)
			Rfid_Value[i]=BufferA[i+12];
		LCD_ShowString(50, 200, "RFID_Value:", Red, Black);
		LCD_ShowString(138, 200, Rfid_Value, Red, Black);
		
		//USART3_Send(BufferA,BufferCount);
	for(i=0;i<BufferCount;i++)
					 BufferA[i]=0x00;
			 BufferCount=0;
			 DBufferFlag=0;
//	}
}

int fputc(int ch, FILE *f)
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART3, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
	{}

	return ch;
}
void USART6_Send(uint8_t *str,uint32_t num)
{
	while(num!=0)
	{
    USART6->DR = (*str++ & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
		num--;
	}
}
void USART3_Send(uint8_t *str,uint32_t num)
{
	while(num!=0)
	{
    USART3->DR = (*str++ & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
		num--;
	}
}

void USART1_Send(uint8_t *str,uint8_t num)
{
	while(num!=0)
	{
		USART1->DR = (*str++ & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		num--;
	}
}

/*
int fputc6(int ch, FILE *f)
{
	// Place your implementation of fputc here 
	// e.g. write a character to the USART 
	USART_SendData(USART6, (uint8_t) ch);

	// Loop until the end of transmission 
	while (USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET)
	{}

	return ch;
}*/

