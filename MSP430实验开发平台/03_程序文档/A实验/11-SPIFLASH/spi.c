#include "msp430f5438a.h"
#include <stdio.h>
#include "delay.h"
#include "spi.h"

/*******************MSP430的SPI Master部分基本函数*********************/
/*******UCB2作为SPI FLASH口********/
void SPI_Init(void)
{
  P9OUT|=BIT0;
  P9DIR|=BIT0;
  P9SEL&=0xF0;
  P9SEL|=0x0e; // P9.1/2/3功能选择为SPI
  UCB2_SPI_RESET;//Enabled. USCI logic held in reset state.
  UCB2CTL0=(BIT6+BIT5+BIT3+BIT0);//MSB first,8bit data,Master mode,3-pin SPI with UCxSTE active low,Synchronous mode
  UCB2CTL1=(BIT7+BIT6+BIT0);//SMCLK
  UCB2BR0=4;//Bit clock prescaler low byte.The 16-bit value of (UCBxBR0 + UCBxBR1 × 256) forms the prescaler value UCBRx.
  UCB2BR1=0x00;//Bit clock prescaler high byte.
  UCB2_SPI_UNRESET; //Disabled. USCI reset released for operation.
  UCB2_SPI_SET_CS;
  delay_ms(50);
}

unsigned char SPI_SendReceiveByte(unsigned char data)
{
  UCB2TXBUF=data;
  while(!(UCB2IFG&UCRXIFG));
  return UCB2RXBUF;
}

/*****************SPI FLASH部分函数*******************/

/*****************command*******************/
unsigned char SPIFLASH_RD_Status1(void) //0x05 Read Status Register-1
{
  unsigned char data=0;
  UCB2_SPI_RESET_CS;
  SPI_SendReceiveByte(0x05);
  data=SPI_SendReceiveByte(0xff);//必须发送0xFF
  UCB2_SPI_SET_CS;
  return data;
}

unsigned char SPIFLASH_RD_Status2(void) //0x35 Read Status Register-2
{
  unsigned char data=0;
  UCB2_SPI_RESET_CS;
  SPI_SendReceiveByte(0x35);
  data=SPI_SendReceiveByte(0xff);//必须发送0xFF
  UCB2_SPI_SET_CS;
  return data;
}

void SPIFLASH_WR_Status(unsigned int data) //0x01 Write Status Register
{
  UCB2_SPI_RESET_CS;
  SPI_SendReceiveByte(0x01);
  SPI_SendReceiveByte(data);
  SPI_SendReceiveByte(data>>8);
  UCB2_SPI_SET_CS;
}

void SPIFLASH_PPro(unsigned long addrs,unsigned char *data,unsigned char length) //0x02 Page Program
{
  unsigned char i=0;
  UCB2_SPI_RESET_CS;
  SPI_SendReceiveByte(0x02);
  SPI_SendReceiveByte(addrs>>16);
  SPI_SendReceiveByte(addrs>>8);
  SPI_SendReceiveByte(addrs);
  for(;i<length;i++)
  {
    SPI_SendReceiveByte(data[i]);
  }
  UCB2_SPI_SET_CS;
}

#define  SPIFLASH_Quad_PPro 0x032 //Quad Page Program
#define  SPIFLASH_BlockErase_64 0xD8 //Block Erase (64KB)
#define  SPIFLASH_BlockErase_32 0x52 //Block Erase (32KB)
#define  SPIFLASH_SectorErase 0x020 //Sector Erase (4KB)
#define  SPIFLASH_HP_MODE 0xA3 //High Performance Mode
#define  SPIFLASH_MB_RST 0xFF //Mode Bit Reset
unsigned char SPIFLASH_RELEASE_PW(void) //0xAB Release Power down or HPM / Device ID
{
  unsigned char data=0;
  UCB2_SPI_RESET_CS;
  SPI_SendReceiveByte(0xAB);
  SPI_SendReceiveByte(0x00);
  SPI_SendReceiveByte(0x00);
  SPI_SendReceiveByte(0x00);
  data=SPI_SendReceiveByte(0xff);//必须发送0xFF
  UCB2_SPI_SET_CS;
  return data;
}
#define  SPIFLASH_MANUDVC_ID 0x90 //Manufacturer/Device ID
unsigned char MFID=0,DeviceID=0;

void SPIFLASH_RD_ID(void) //0x4B Read Unique ID
{
  UCB2_SPI_RESET_CS;
  SPI_SendReceiveByte(0x90);
  SPI_SendReceiveByte(0x00);
  SPI_SendReceiveByte(0x00);
  SPI_SendReceiveByte(0x00);
  MFID=SPI_SendReceiveByte(0xff);//必须发送0xFF
  DeviceID=SPI_SendReceiveByte(0xff);//必须发送0xFF
  UCB2_SPI_SET_CS;
}

#define  SPIFLASH_JEDEC_ID 0x9F //JEDEC ID
void SPIFLASH_RD_DATA(unsigned long addrs,unsigned char *data,unsigned char length)//0x03 Read Data
{
  unsigned char i=0;
  UCB2_SPI_RESET_CS;
  SPI_SendReceiveByte(0x03);
  SPI_SendReceiveByte(addrs>>16);
  SPI_SendReceiveByte(addrs>>8);
  SPI_SendReceiveByte(addrs);
  for(;i<length;i++)
  {
    data[i]=SPI_SendReceiveByte(0xff);//必须发送0xFF
  }
  UCB2_SPI_SET_CS;
}
#define  SPIFLASH_RD_FAST 0x0B //Fast Read
#define  SPIFLASH_RD_FAST_DUALOUT0 0x3B //Fast Read Dual Output
#define  SPIFLASH_RD_FAST_DUALIO_0 0xBB //Fast Read Dual I/O
#define  SPIFLASH_RD_FAST_DUALOUT1 0x6B //Fast Read Quad Output
#define  SPIFLASH_RD_FAST_DUALIO_1 0xEB //Fast Read Quad I/O


