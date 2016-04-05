#ifndef _SPI_H
#define _SPI_H
#include "delay.h"

#define UCB2_SPI_RESET  do{UCB2CTL1|=BIT0;}while(0) //Enabled. USCI logic held in reset state.
#define UCB2_SPI_UNRESET  do{UCB2CTL1&=~BIT0;}while(0)//Disabled. USCI reset released for operation.
#define UCB2_SPI_SET_CS do{P9OUT|=0x01;}while(0)
#define UCB2_SPI_RESET_CS do{P9OUT&=~0x01;}while(0)
//extern unsigned char RXsign,SPIdata;
extern unsigned char SPI_SendReceiveByte(unsigned char);
extern unsigned char MFID,DeviceID;
/*****************command*******************/
#define  SPIFLASH_WR_Enable   do{UCB2_SPI_RESET_CS;SPI_SendReceiveByte(0x06);UCB2_SPI_SET_CS;}while(0)//Write Enable
#define  SPIFLASH_WR_Disable   do{UCB2_SPI_RESET_CS;SPI_SendReceiveByte(0x04);UCB2_SPI_SET_CS;}while(0) //Write Disable
#define  SPIFLASH_ChipErase0  do{UCB2_SPI_RESET_CS;SPI_SendReceiveByte(0xC7);UCB2_SPI_SET_CS;}while(0)//Chip Erase
#define  SPIFLASH_ChipErase1  do{UCB2_SPI_RESET_CS;SPI_SendReceiveByte(0x60);UCB2_SPI_SET_CS;}while(0)//Chip Erase
#define  SPIFLASH_EraseSuspend  do{UCB2_SPI_RESET_CS;SPI_SendReceiveByte(0x75);UCB2_SPI_SET_CS;}while(0) //Erase Suspend
#define  SPIFLASH_EraseResume  do{UCB2_SPI_RESET_CS;SPI_SendReceiveByte(0x7A);UCB2_SPI_SET_CS;}while(0) //Erase Resume
#define  SPIFLASH_PowerDown  do{UCB2_SPI_RESET_CS;SPI_SendReceiveByte(0xB9);UCB2_SPI_SET_CS;}while(0) //Power-down
extern void SPI_Init(void);
extern unsigned char SPIFLASH_RD_Status1(void);
extern unsigned char SPIFLASH_RD_Status2(void);
extern void SPIFLASH_WR_Status(unsigned int);
extern unsigned char SPIFLASH_RELEASE_PW(void);
extern void SPIFLASH_RD_ID(void);
extern void SPIFLASH_RD_DATA(unsigned long,unsigned char*,unsigned char);
extern void SPIFLASH_PPro(unsigned long,unsigned char *,unsigned char);
#endif