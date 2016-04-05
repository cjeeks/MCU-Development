//===========================================================================//
//                                                                           //
// 文件：  ENC28J60.C                                                        //
// 说明：  BW-DK5438开发板以太网远程控制程序                                 //
//         由Microchip ENC28J60 Ethernet Interface Driver ATMEGA8版移植      //
// 编译：  IAR Embedded Workbench IDE for MSP430 v4.21                       //
// 版本：  v1.1                                                              //
// 编写：  JASON.ZHANG                                                       //
// 版权：  北京拓普博维电子技术有限公司                                      //
// 日期：  2010.09.25                                                        //
//                                                                           //
//===========================================================================//

#include "msp430x54x.h"
#include <stdlib.h>
#include <stdio.h>
#include "PIN_DEF.H"

#include "enc28j60.h"
#include "timeout.h"

static uint8_t Enc28j60Bank                   ;
static uint16_t NextPacketPtr                 ;


unsigned char SPI_RW_Char(unsigned char data)
{
  unsigned char temp,i,cRec=0                 ;
  temp = data                                 ;
  for(i=0;i<8;i++)
  {
    if(P10IN&PMISO)
      cRec    |= (1<<(7-i))                   ;        
    if(temp&0x80)
      P10OUT  |= PMOSI                        ;
    else             
      P10OUT  &=~PMOSI                        ;
    P10OUT    |= PSCK                         ;
    P10OUT    &=~PSCK                         ;
    temp     <<=  1                           ;
  }  
  return cRec                                 ;
}

uint8_t enc28j60ReadOp(uint8_t op, uint8_t address)
{
  unsigned char data                          ;  
  CLR_J60_CS                                  ;                         
  SPI_RW_Char(op | (address & ADDR_MASK))     ;
  data=SPI_RW_Char(0x00)                      ;
  if(address & 0x80)
  {
    data = SPI_RW_Char(0x00)                  ;
  }
  SET_J60_CS                                  ;                         
  return data                                 ;
}

void enc28j60WriteOp(uint8_t op, uint8_t address, uint8_t data)
{
  CLR_J60_CS                                  ;                         
  SPI_RW_Char(op | (address & ADDR_MASK))     ;
  SPI_RW_Char(data)                           ;
  SET_J60_CS                                  ;                         
}

void enc28j60ReadBuffer(uint16_t len, uint8_t* data)
{
  CLR_J60_CS                                  ;                         
  SPI_RW_Char(ENC28J60_READ_BUF_MEM)          ;
  while(len--)
  {
    *data++   = SPI_RW_Char(0x00)             ;
  }		
  *data  = 0                                  ;
  SET_J60_CS                                  ;                         
}

void enc28j60WriteBuffer(uint16_t len, uint8_t* data)
{
  CLR_J60_CS                                  ;                         
  SPI_RW_Char(ENC28J60_WRITE_BUF_MEM)         ;
  while(len--)
  {
    SPI_RW_Char(*data++)                      ;
  }
  SET_J60_CS                                  ;                         
}


void enc28j60SetBank(uint8_t address)
{
  if((address & BANK_MASK) != Enc28j60Bank)
  {
    enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, (ECON1_BSEL1|ECON1_BSEL0));
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, (address & BANK_MASK)>>5) ;
    Enc28j60Bank = (address & BANK_MASK)                                     ;
  }
}

uint8_t enc28j60Read(uint8_t address)
{
  enc28j60SetBank(address)                               ;
  return enc28j60ReadOp(ENC28J60_READ_CTRL_REG, address) ;
}

void enc28j60Write(uint8_t address, uint8_t data)
{
  enc28j60SetBank(address)                               ;
  enc28j60WriteOp(ENC28J60_WRITE_CTRL_REG, address, data);
}

void enc28j60PhyWrite(uint8_t address, uint16_t data)
{
   enc28j60Write(MIREGADR, address);
   enc28j60Write(MIWRL, data);
   enc28j60Write(MIWRH, data>>8);
   while(enc28j60Read(MISTAT) & MISTAT_BUSY)
   {
      __delay_cycles(3000)                               ;
   }
}


void enc28j60Init(uint8_t* macaddr)
{
  enc28j60WriteOp(ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET); 
  delay_ms(50)                                                ;
  NextPacketPtr = RXSTART_INIT                                ;      
  enc28j60Write(ERXSTL, RXSTART_INIT&0xFF)                    ; 
  enc28j60Write(ERXSTH, RXSTART_INIT>>8)                      ;	
  enc28j60Write(ERXRDPTL, RXSTART_INIT&0xFF)                  ;
  enc28j60Write(ERXRDPTH, RXSTART_INIT>>8)                    ;
  enc28j60Write(ERXNDL, RXSTOP_INIT&0xFF)                     ;
  enc28j60Write(ERXNDH, RXSTOP_INIT>>8)                       ;	
  enc28j60Write(ETXSTL, TXSTART_INIT&0xFF)                    ;
  enc28j60Write(ETXSTH, TXSTART_INIT>>8)                      ;
  enc28j60Write(ETXNDL, TXSTOP_INIT&0xFF)                     ;
  enc28j60Write(ETXNDH, TXSTOP_INIT>>8)                       ;
  enc28j60Write(ERXFCON, ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_PMEN) ;
  enc28j60Write(EPMM0, 0x3f)                                      ;
  enc28j60Write(EPMM1, 0x30)                                      ;
  enc28j60Write(EPMCSL, 0xf9)                                     ;
  enc28j60Write(EPMCSH, 0xf7)                                     ;
  enc28j60Write(MACON1, MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
  enc28j60Write(MACON2, 0x00)                                     ;
  enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN);
  enc28j60Write(MAIPGL, 0x12)                                      ;
  enc28j60Write(MAIPGH, 0x0C)                                      ;
  enc28j60Write(MABBIPG, 0x12)                                     ;
  enc28j60Write(MAMXFLL, MAX_FRAMELEN&0xFF)                        ;	
  enc28j60Write(MAMXFLH, MAX_FRAMELEN>>8)                          ;
  enc28j60Write(MAADR5, macaddr[0])                                ;
  enc28j60Write(MAADR4, macaddr[1])                                ;
  enc28j60Write(MAADR3, macaddr[2])                                ;
  enc28j60Write(MAADR2, macaddr[3])                                ;
  enc28j60Write(MAADR1, macaddr[4])                                ;
  enc28j60Write(MAADR0, macaddr[5])                                ;
  enc28j60PhyWrite(PHCON2, PHCON2_HDLDIS)                          ;
  enc28j60SetBank(ECON1)                                           ;
  enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE|EIE_PKTIE);
  enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN)       ;
}

uint8_t enc28j60getrev(void)
{
  return(enc28j60Read(EREVID))                                     ;
}

void enc28j60PacketSend(uint16_t len, uint8_t* packet)
{
  enc28j60Write(EWRPTL, TXSTART_INIT&0xFF)                         ;
  enc28j60Write(EWRPTH, TXSTART_INIT>>8)                           ;
  enc28j60Write(ETXNDL, (TXSTART_INIT+len)&0xFF)                   ;
  enc28j60Write(ETXNDH, (TXSTART_INIT+len)>>8)                     ;
  enc28j60WriteOp(ENC28J60_WRITE_BUF_MEM, 0, 0x00)                 ;
  enc28j60WriteBuffer(len, packet);
  enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS)      ;
  if( (enc28j60Read(EIR) & EIR_TXERIF) )
  {
    enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS)    ;
  }
}

uint16_t enc28j60PacketReceive(uint16_t maxlen, uint8_t* packet)
{
  uint16_t rxstat                                                  ;
  uint16_t len                                                     ;
  if( enc28j60Read(EPKTCNT) ==0 )		return(0)          ;
  enc28j60Write(ERDPTL, (NextPacketPtr))                           ;
  enc28j60Write(ERDPTH, (NextPacketPtr)>>8)                        ;
  NextPacketPtr  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)        ;
  NextPacketPtr |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8     ;
  len  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)                  ;
  len |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8               ;
  len -=4                                                          ; 
  rxstat  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)               ;
  rxstat |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8            ;
  if (len>maxlen-1)            len=maxlen-1                        ;
  if ((rxstat & 0x80)==0)      len=0                               ;
  else                         enc28j60ReadBuffer(len, packet)     ;
  enc28j60Write(ERXRDPTL, (NextPacketPtr))                         ;
  enc28j60Write(ERXRDPTH, (NextPacketPtr)>>8)                      ;
  enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PKTDEC)     ;
  return(len)                                                      ;
}

void ENC_SLEEP(void)
{
  enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_RXEN) ;
  enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_VRPS) ;
  enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PWRSV);  
}

void ENC_WAKEUP(void)
{
  enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON2, ECON2_PWRSV);
  delay_ms(1)                                                ;  
  enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN) ;  
}
