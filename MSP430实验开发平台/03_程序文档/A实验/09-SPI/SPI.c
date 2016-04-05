#include "msp430f5438a.h"
#include <stdio.h>
#include <stdbool.h>
#include "delay.h"
#include "SPI.h"

/*******************MSP430的SPI Master部分基本函数*********************/
void SPI_Init(void)
{
  SSN_HIGH;
  SSN_DIROUT;
  P9SEL&=0xF0;
  P9SEL|=0x0e; // P9.1/2/3功能选择为SPI
  UCB2_SPI_RESET;//Enabled. USCI logic held in reset state.
  UCB2CTL0=(BIT5+BIT3+BIT0);//MSB first,8bit data,Master mode,3-pin SPI with UCxSTE active low,Synchronous mode
  UCB2CTL1=(BIT7+BIT6+BIT0);//SMCLK
  UCB2BR0=16;//Bit clock prescaler low byte.The 16-bit value of (UCBxBR0 + UCBxBR1 × 256) forms the prescaler value UCBRx.
  UCB2BR1=0x00;//Bit clock prescaler high byte.
  UCB2IFG=0x00;
  UCB2_SPI_UNRESET; //Disabled. USCI reset released for operation.
  SSN_HIGH;
  delay_ms(50);
}

/*static unsigned char SPI_SendReceiveByte(unsigned char data)
{
  UCB2TXBUF=data;
  while(!(UCB2IFG&UCRXIFG));
  return UCB2TXBUF;
}*/

static unsigned char SPI_SendRecieveByte(unsigned char sendbyte)
{
  unsigned char data;
  UCB2TXBUF=sendbyte; 
  while(!(UCB2IFG&UCRXIFG));
  data=UCB2RXBUF;
  return data;
}

static unsigned char SPI_RecieveByte(void)
{
  unsigned char data;
  UCB2TXBUF=0xff; // U1ACTIVE is asserted
  while(!(UCB2IFG&UCRXIFG));
  data=UCB2RXBUF;
  return data;
}

static uchar SD_Write_CMD(unsigned char cmd,unsigned long int arg,unsigned char crc)
{
  uchar retry=0,response=0xff;
  SPI_SendRecieveByte(0xff);
  SSN_LOW;
  SPI_SendRecieveByte(0x40|cmd);
  SPI_SendRecieveByte((uchar)(arg>>24));
  SPI_SendRecieveByte((uchar)(arg>>16));
  SPI_SendRecieveByte((uchar)(arg>>8));
  SPI_SendRecieveByte((uchar)(arg));
  SPI_SendRecieveByte(crc);
  do
  {
    response=SPI_SendRecieveByte(0xFF);
    retry++;
  }while(((response&0x80)!=0)&&(retry < 200));
  SSN_HIGH;
  SPI_SendRecieveByte(0xff);
  return response;
}


bool SD_Init(void)
{
  unsigned char i=0,retry=0;
  static uchar temp=0;
  /*   发送74CLK   */
  SSN_HIGH;
  for(i=0;i<0x10;i++)SPI_SendRecieveByte(0x00);
  
  /*   发送CMD0    */
  do
  {
    temp=SD_Write_CMD(0x00,0x00,0x95);
    retry++;
    if(200==retry)
    {
      return false;
    }
  }while(temp!=0x01); //回应01h，停止写入
  
  /*   发送CMD1    */
  retry=0;
  do
  {
    temp=SD_Write_CMD(0x01,0x00,0xff);
    retry++;
    if(200==retry)
    {
      return false;
    }
  }while(temp!=0x00); //回应00h，停止写入
  
  return true;
}

bool SD_Block_W(unsigned char * Block, unsigned long address)
{
  uchar retry=0;
  uchar temp=0;
  uint i=0;
  /*    发送CMD24    */
  do
  {
    temp=SD_Write_CMD(0x18,address,0xff);
    retry++;
    if(200==retry)
    {
      return false;
    }
  }while(temp!=0x00); //回应00h，停止写入
  
  SSN_LOW;
  /*    发送4字节0xff    */
  SPI_SendRecieveByte(0xff);
  SPI_SendRecieveByte(0xff);
  SPI_SendRecieveByte(0xff);
  SPI_SendRecieveByte(0xff);
  
  /*    发送数据帧    */
  SPI_SendRecieveByte(0xfe); //’Start Block’ token (one byte)
  for(i=0;i<512;i++)SPI_SendRecieveByte(Block[i]);
  SPI_SendRecieveByte(0xff); //两字节CRC校验码
  SPI_SendRecieveByte(0xff);
  
  do  //等待返回0x05
  {
    temp=SPI_RecieveByte()&0x0f;
    retry++;
    if(200==retry)return false;
  }while(temp!=0x05);
  
  while(SPI_RecieveByte()!=0xff);
  
  SSN_HIGH;
  
  SPI_SendRecieveByte(0xff);
  return true;
}

bool SD_Block_R( unsigned char * buffer , unsigned long address )
{
  uint i=0;
  uchar retry=0,temp=0;
  /*    发送CMD17    */
  do
  {
    temp=SD_Write_CMD(0x11,address,0xff);
    retry++;
    if(200==retry)
    {
      return false;
    }
  }while(temp!=0x00); //回应00h，停止写入
  
  SSN_LOW;
  do  //等待返回0xfe
  {
    temp=SPI_SendRecieveByte(0xFF);
    retry++;
    if(retry==200)return false;
  }while((temp!=0xfe)); ////0xFE为块读出的头，后面紧跟512字节的块数据+2字节的CRC码
  
  for(i=0;i<512;i++)
  {
    *(buffer+i)=SPI_SendRecieveByte(0xFF);
  }
  SPI_SendRecieveByte(0xFF);  //两字节CRC码，丢弃
  SPI_SendRecieveByte(0xFF);
  
  SSN_HIGH;
  
  SPI_SendRecieveByte(0xff);
  return true;
}