#ifndef	__UART_H
#define	__UART_H
#include <reg51.h>
#include <PCF8574T\PCF8574T.h>

#include <sys\sys.h>
#include "intrins.h"
//#include "utility.h"

#define GSM_length 10	

#define UART_RATE48  	 0xF4		/*定义波特率9600bps*/
#define UART_RATE96    0xFA		/*定义波特率9600bps*/
#define UART_RATE192   0xFD		/*定义波特率9600bps*/
#define UART_RATE576   0xFF		/*定义波特率9600bps*/
#define UART_RATE1152	 0x00		/*定义波特率9600bps*/

extern unsigned char uart_flag ;
extern char gsm_ch[GSM_length];

#define SPEEDUP
extern unsigned char uart_flag;
extern unsigned char RFID_count;
extern idata unsigned char gsm_temp[10];
extern unsigned char BufferA[50];

void Uart1_SendData(unsigned char dat);
void Uart1_SendString(char *s);
void Init_Uart1(u32 baud);
void Uart2_SendData(unsigned char  dat);
void Uart2_SendString(char *s);
void Init_Uart2();

#endif