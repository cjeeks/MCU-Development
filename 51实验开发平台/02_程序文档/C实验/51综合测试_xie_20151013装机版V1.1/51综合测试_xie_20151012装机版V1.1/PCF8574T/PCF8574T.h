
/*---------------------------------------------------------------------*/
/* --- STC MCU International Limited ----------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.GXWMCU.com --------------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了宏晶科技的资料及程序   */
/*---------------------------------------------------------------------*/


#ifndef	__PCF8574T_H
#define	__PCF8574T_H
#include <sys\sys.h>
#include <reg51.h>
#include <intrins.h>
#include <PCF8574T\PCF8574T.h>

sbit	SDA	= P1^0;	//定义SDA  PIN5
sbit	SCL	= P1^1;	//定义SCL  PIN6

#define SLAW	0xA2
#define SLAR	0xA3

#define	UA_PCF8574_SlaveAddress	0x20	//CS3: ENC28J60_CS  
#define	UB_PCF8574_SlaveAddress	0x21
#define	UD_PCF8574_SlaveAddress	0x22   	//OUTC
#define	UE_PCF8574_SlaveAddress	0x23
#define	UF_PCF8574_SlaveAddress	0x24   	//OUTF
#define	UG_PCF8574_SlaveAddress	0x25	//OUTG


//***************************
void	I2C_Delay(void);
void I2C_Start(void);
void I2C_Stop(void)	;
void S_ACK(void);
void S_NoACK(void);
void I2C_Check_ACK(char ack);
void I2C_WriteAbyte(u8 dat);
u8 I2C_ReadAbyte(void);
 
void WriteNbyte(u8 addr, u8 *p, u8 number);
void ReadNbyte( u8 addr, u8 *p, u8 number);
unsigned char PCF8574_Single_ReadI2C(u8 REG_Address);
void PCF8574_Single_WriteI2C(u8 REG_Address,u8 REG_data);

#endif

