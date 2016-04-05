#define MAIN_Fosc		22118400UL	//
#include <UART\UART.h>
#include "lcd/lcd.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;



#define FOSC 22118400L      //System frequency
//set uart baud
unsigned char BAUD1 = UART_RATE1152;
#define 			BAUD2 9600           //UART baudrate
/*Define UART parity mode*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity

#define PARITYBIT NONE_PARITY   //Testing even parity
//bit busy;
bit busy1;
bit busy2;
/*Declare SFR associated with the UART2 */
sfr AUXR  = 0x8e;           //Auxiliary register
sfr S2CON = 0x9a;           //UART2 control register
sfr S2BUF = 0x9b;           //UART2 data buffer
sfr BRT   = 0x9c;           //Baudrate generator
sfr IE2   = 0xaf;           //Interrupt control 2

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3
#define SETBIT(u8Val, u8Offset)    		u8Val |= 1 << u8Offset
#define RESETBIT(u8Val, u8Offset)  	u8Val &= ~(1 << u8Offset)

unsigned char BufferA[50];
unsigned char BufferCount = 0;
unsigned char DBufferFlag=0;

unsigned char uart_flag = 0;

void Uart1_SendData(unsigned char dat);
void Uart1_SendString(char *s);
void Init_Uart1();
void Uart2_SendData(BYTE dat);
void Uart2_SendString(char *s);
void Init_Uart2();

void Init_Uart1(u32 baud)
{
	ES = 0;			/*关串行口中断*/	

#ifdef SPEEDUP			/*串口速度加倍*/
	RESETBIT(PCON, 7);
#else
	SETBIT(PCON, 7);
#endif

	if(baud == UART_RATE1152)
	{
		baud = UART_RATE576;
		SETBIT(PCON, 7);
	}

	TMOD &= 0x0F;
	TMOD |= 0x20;
	ET1 = 0;				/*中断无效*/
	TH1 = baud;
	TL1 = baud;
	TR1 = 1;				/*定时器开启*/
	SCON = 0x50;

	RI = 0;
	
	ES = 1;				/*串行口中断printf需要串口关闭*/         //Open master interrupt switch
}

/*----------------------------
UART interrupt service routine
----------------------------*/
void Uart1_Isr() interrupt 4 using 1		//RFID
{	

	unsigned char ch;
		
    if (RI)
    {	
			
			uart_flag ++;  
			
	    RI = 0;             //Clear receive interrupt flag
			ch = SBUF;  
			
			BufferA[BufferCount++] = ch;
			if(BufferCount > 48)
			{
						DBufferFlag=1;
				BufferCount=0;
				}
			else
			{
				DBufferFlag=0;
			}
		
		//PCF8574_Single_WriteI2C(UD_PCF8574_SlaveAddress ,0);
        //P0 = SBUF;          //P0 show UART data
        //bit9 = RB8;         //P2.2 show parity bit
    }
 
    if (TI)
    {	 
        TI = 0;             //Clear transmit interrupt flag
        busy1 = 0;           //Clear transmit busy flag
    }
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void Uart1_SendData(unsigned char dat)
{
    while (busy1);           //Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    if (P)                  //Set the parity bit according to P
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;            //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;            //Set parity bit to 1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;            //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;            //Set parity bit to 0
#endif
    }
    busy1 = 1;
    SBUF = ACC;             //Send data to UART buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void Uart1_SendString(char *s)
{
    while (*s)              //Check the end of the string
    {
        Uart1_SendData(*s++);     //Send current char and increment string ptr
    }
}

void Init_Uart2()
{
#if (PARITYBIT == NONE_PARITY)
    S2CON = 0x50;           //8-bit variable UART
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    S2CON = 0xda;           //9-bit variable UART, parity bit initial to 1
#elif (PARITYBIT == SPACE_PARITY)
    S2CON = 0xd2;           //9-bit variable UART, parity bit initial to 0
#endif

    BRT = -(FOSC/32/BAUD2);  //Set auto-reload vaule of baudrate generator
    AUXR = 0x14;            //Baudrate generator work in 1T mode
    IE2 = 0x01;             //Enable UART2 interrupt
    EA = 1;                 //Open master interrupt switch
}

char gsm_ch[GSM_length] = {0};



/*----------------------------
UART2 interrupt service routine
----------------------------*/
void Uart2() interrupt 8 using 1
{
		u8 ch;
	
	static u8 gsm_count = 0;
	
    if (S2CON & S2RI)
    {        
			ch = S2BUF; 
			
			gsm_ch[gsm_count] = ch;
			gsm_count ++; 
			
			if(gsm_count  > GSM_length)
				gsm_count = 0;	
			
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			S2CON &= ~S2RI;     //Clear receive interrupt flag				

			//while (busy2);			
			
			/*
		gsm_temp[gsm_count] = ch;
		if(gsm_temp[gsm_count] == 0x0D)
		{				
			gsm_temp[gsm_count] = ' ';
			//LCD_ShowString(142, 160,a);
			//LCD_ShowString(150, 160,gsm_temp);
			gsm_count = 0;				
		}
		if(gsm_temp[gsm_count] == 0x0A)
			gsm_temp[gsm_count] = ' ';
				
		gsm_count ++;
			
			*/
	
    }
    if (S2CON & S2TI)
    {	//uart_flag = 1;
        S2CON &= ~S2TI;     //Clear transmit interrupt flag
        busy2 = 0;           //Clear transmit busy flag
    }
		
}



/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void Uart2_SendData(unsigned char  dat)
{
    while (busy2);           //Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    if (P)                  //Set the parity bit according to P
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON &= ~S2TB8;    //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
        S2CON |= S2TB8;     //Set parity bit to 1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        S2CON |= S2TB8;     //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
        S2CON &= ~S2TB8;    //Set parity bit to 0
#endif
    }
    busy2 = 1;
    S2BUF = ACC;            //Send data to UART2 buffer
}

/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void Uart2_SendString(char *s)
{
    while (*s)              //Check the end of the string
    {
        Uart2_SendData(*s++);     //Send current char and increment string ptr
    }
}

void Send_Com()
{

	u8 i;	
	u8 Rfid_Id[9];
	idata u8 Rfid_Value[35];

		LCD_ShowNum(150, 80,uart_flag, 1);
		LCD_ShowNum(180, 80,DBufferFlag, 1);	
	
	while(BufferCount<45);
 
		for(i=0;i<9;i++)
			Rfid_Id[i]=BufferA[i+1];
		LCD_ShowString(50, 180, "RFID_ID:");
		LCD_ShowString(114, 180, Rfid_Id);
	
		Uart1_SendString("G1");
	
		for(i=0;i<35;i++)
			Rfid_Value[i]=BufferA[i+12];
		LCD_ShowString(50, 200, "RFID_Value:");
		LCD_ShowString(138, 200, Rfid_Value);
	for(i=0;i<BufferCount;i++)
			BufferA[i]=0x00;
			 BufferCount=0;
			 DBufferFlag=0;
			 
		Uart1_SendString("G2");	 
}

void RFID_Test(void)
{  
		Send_Com();	
}