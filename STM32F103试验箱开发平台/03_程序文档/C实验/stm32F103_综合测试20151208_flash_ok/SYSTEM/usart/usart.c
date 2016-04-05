#include "sys.h"
#include "usart.h"	
#include "lcd.h"

char Date_Buf[10];
char BufferA[50];
uint8_t DBufferFlag=0;
uint8_t mark = 0;
	static unsigned char BufferCount=0;
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)    

void _ttywrch(int ch)  			//为了使用malloc  xie 20150718
{ 
    while((USART1->SR&0X40)==0);//训话发送，直到发送完毕  
    USART1->DR = (u8) ch;  
}

//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  

//初始化IO 串口1 
//bound:波特率
void Uart1_init(u32 bound){
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
 	USART_DeInit(USART1);  //复位串口1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART1, ENABLE);                    //使能串口 

}


static u32 startadd = 0;
void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
			if(Res == ',')
				Res = 0;
			else
			{
				SPI_FLASH_Write_Enable();                  //SET WEL 
				SPI_FLASH_PageWrite(&Res, startadd++, 1);
			}
/*		if((USART_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART_RX_STA&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
				else USART_RX_STA|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}  	
			}  
*/				 
     } 

#ifdef OS_TICKS_PER_SEC	 	//如果时钟节拍数定义了,说明要使用ucosII了.
	OSIntExit();  											 
#endif
} 

//UART3 -> RFID
void Uart3_init(u32 bound)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	;
	/* 开启串口3的时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3，GPIOA时钟
//USART3_TX PB10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
//USART3_RX PB11
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入	
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate   = 115200; //115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits   = USART_StopBits_1;
	USART_InitStructure.USART_Parity     = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3, ENABLE);
}

void USART3_IRQHandler(void)    //RFID     
{
	uint8_t ch;
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(USART3);  //取出串口得到的数据
	//	USART_SendData(USART3, ch);
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

void Uart5_init(u32 bound)
{
GPIO_InitTypeDef GPIO_InitStructure; 
  	USART_InitTypeDef USART_InitStructure;   


   
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);  //??UART5??GPIOC???  
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);  //????5?? 

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	         	//USART5 TX 
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    	//?????? 
  	GPIO_Init(GPIOC, &GPIO_InitStructure);	    	 //c??  

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	         	 //USART5 RX 
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //?????? 
  	GPIO_Init(GPIOD, &GPIO_InitStructure);	         	 //D??  
   
  	USART_InitStructure.USART_BaudRate   = bound; 
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//???8? 
  	USART_InitStructure.USART_StopBits   = USART_StopBits_1;	//???1? 
  	USART_InitStructure.USART_Parity     = USART_Parity_No;	//???? 
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //????? 
  	USART_InitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;	//???? 
   
  	/* Configure USART3 */ 
  	USART_Init(UART5, &USART_InitStructure);	//????????  
   
  	/*USART3 receive data register is not empty */ 
  	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);   
  	/* Enable the USART3 */ 
  	USART_Cmd(UART5, ENABLE);		
	
/*	
		USART_InitTypeDef USART_InitStructure; 
		GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD , ENABLE);	
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
		USART_DeInit(UART5);
		USART_InitStructure.USART_BaudRate = bound;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(UART5,&USART_InitStructure);
		USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART5, ENABLE);
*/
}

uint8_t gsm_ch[GSM_length] = {0};

void UART5_IRQHandler(void)   	//GSM      
{	
  uint8_t ch;
	//static uint8_t count = 0, temp[5] = {0};
	//uint8_t a[1] = {'A'};
	
	static uint8_t gsm_count = 0;

	if(USART_GetFlagStatus(UART5,USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(UART5);  //取出串口得到的数据
		
		USART_SendData(UART4, ch);
		while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
		
			gsm_ch[gsm_count] = ch;
			gsm_count ++; 
			
			if(gsm_count  > GSM_length)
				gsm_count = 0;	
		
/*		
		temp[count] = ch;
		if(temp[count] == 0x0D)
		{
			temp[count] = ' ';
			LCD_ShowString(142, 160,a);
			LCD_ShowString(150, 160,temp);
			count = 0;	
		}
		if(temp[count] == 0x0A)
			temp[count] = ' ';
		
			
		count ++;
*/
		}	
} 

void UART5_Send(uint8_t *str,uint32_t num)
{
	while(num!=0)
	{
    UART5->DR = (*str++ & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
		num--;
	}
}

void Uart4_init(u32 bound)
{
   USART_InitTypeDef USART_InitStructure;
   GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);                                                                                
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);	

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
   GPIO_Init(GPIOC, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	USART_DeInit(UART4);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4,&USART_InitStructure);
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
  USART_Cmd(UART4, ENABLE);
}

void UART4_IRQHandler(void)         
{
	uint8_t ch;
	if(USART_GetFlagStatus(UART4, USART_FLAG_RXNE))
	{
		ch = USART_ReceiveData(UART4);  //取出串口得到的数据
		
		USART_SendData(UART5, ch);
		while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);		
		
	//	USART_SendData(USART3, ch);
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

void UART4_Send(uint8_t *str,uint32_t num)
{
	while(num!=0)
	{
    UART4->DR = (*str++ & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
		num--;
	}
}


void RFID_Test()
{
	unsigned char i;	
	char Rfid_Id[9];
	char Rfid_Value[35];
	
	while(BufferCount<48);
		for(i=0;i<9;i++)
			Rfid_Id[i]=BufferA[i+1];
		LCD_ShowString(50, 180, "RFID_ID:");
		LCD_ShowString(114, 180, Rfid_Id);

		for(i=0;i<35;i++)
			Rfid_Value[i]=BufferA[i+12];
		LCD_ShowString(50, 200, "RFID_Value:");
		LCD_ShowString(138, 200, Rfid_Value);

	for(i=0;i<BufferCount;i++)
					 BufferA[i]=0x00;
			 BufferCount=0;
			 DBufferFlag=0;
}

