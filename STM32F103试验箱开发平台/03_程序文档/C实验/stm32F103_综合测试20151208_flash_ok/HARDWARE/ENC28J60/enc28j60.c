#include "enc28j60.h"
#include "spi.h"
#include <stdio.h>

static unsigned char Enc28j60Bank;
static unsigned int NextPacketPtr;


unsigned char enc28j60ReadOp(unsigned char op, unsigned char address)
{
	unsigned char dat = 0;
	
	ENC28J60_CSL();
	
	dat = op | (address & ADDR_MASK);
	SPI1_ReadWrite(dat);
	dat = SPI1_ReadWrite(0xFF);
	// do dummy read if needed (for mac and mii, see datasheet page 29)
	if(address & 0x80)
	    {
		dat = SPI1_ReadWrite(0xFF);
	    }
	// release CS
	ENC28J60_CSH();
	return dat;
}

void enc28j60WriteOp(unsigned char op, unsigned char address, unsigned char data)
{
	unsigned char dat = 0;
	  
	ENC28J60_CSL();
	// issue write command
	dat = op | (address & ADDR_MASK);
	SPI1_ReadWrite(dat);
	// write data
	dat = data;
	SPI1_ReadWrite(dat);
	ENC28J60_CSH();
}

void enc28j60ReadBuffer(unsigned int len, unsigned char* data)
{
	ENC28J60_CSL();
	// issue read command
	SPI1_ReadWrite(ENC28J60_READ_BUF_MEM);
	while(len)
		{
        len--;
        // read data
        *data = (unsigned char)SPI1_ReadWrite(0);
        data++;
		}
	*data='\0';
	ENC28J60_CSH();
}

void enc28j60WriteBuffer(unsigned int len, unsigned char* data)
{
	ENC28J60_CSL();
	// issue write command
	SPI1_ReadWrite(ENC28J60_WRITE_BUF_MEM);
	
	while(len)
		{
		len--;
		SPI1_ReadWrite(*data);
		data++;
		}
	ENC28J60_CSH();
}

void enc28j60SetBank(unsigned char address)
{
	// set the bank (if needed)
	if((address & BANK_MASK) != Enc28j60Bank)
	{
        // set the bank
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, (ECON1_BSEL1|ECON1_BSEL0));
        enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, (address & BANK_MASK)>>5);
        Enc28j60Bank = (address & BANK_MASK);
	}
}

unsigned char enc28j60Read(unsigned char address)
{
	// set the bank
	enc28j60SetBank(address);
	// do the read
	return enc28j60ReadOp(ENC28J60_READ_CTRL_REG, address);
}

void enc28j60Write(unsigned char address, unsigned char data)
{
	// set the bank
	enc28j60SetBank(address);
	// do the write
	enc28j60WriteOp(ENC28J60_WRITE_CTRL_REG, address, data);
}

void enc28j60PhyWrite(unsigned char address, unsigned int data)
{
	// set the PHY register address
	enc28j60Write(MIREGADR, address);
	// write the PHY data
	enc28j60Write(MIWRL, data);
	enc28j60Write(MIWRH, data>>8);
	// wait until the PHY write completes
	while(enc28j60Read(MISTAT) & MISTAT_BUSY)
	{
		//_nop_();
	}
}

void enc28j60clkout(unsigned char clk)
{
    //setup clkout: 2 is 12.5MHz:
	enc28j60Write(ECOCON, clk & 0x7);
}

void enc28j60Init(unsigned char* macaddr)
{
    /*将ENC28J60的SPI NSS信号置高*/
    ENC28J60_CSH();	    
    
	/*软件复位ENC28J60*/
	enc28j60WriteOp(ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);

	//设置接收缓冲区地址  8K字节容量
	NextPacketPtr = RXSTART_INIT;

	//接收缓冲器由一个硬件管理的循环FIFO 缓冲器构成。寄存器对ERXSTH:ERXSTL 和ERXNDH:ERXNDL 作为指针，定义
	//缓冲器的容量和其在存储器中的位置。ERXST和ERXND指向的字节均包含在FIFO缓冲器内。当从以太网接口接收数据
	//字节时，这些字节被顺序写入接收缓冲器。 但是当写入由ERXND 指向的存储单元后，硬件会自动将接收的下一
	//字节写入由ERXST 指向的存储单元。 因此接收硬件将不会写入FIFO 以外的单元。

	enc28j60Write(ERXSTL, RXSTART_INIT&0xFF);	 
	enc28j60Write(ERXSTH, RXSTART_INIT>>8);

    // set receive pointer address
    //ERXWRPTH:ERXWRPTL 寄存器定义硬件向FIFO 中的哪个位置写入其接收到的字节。 指针是只读的，在成
    //功接收到一个数据包后，硬件会自动更新指针。 指针可用于判断FIFO 内剩余空间的大小  8K-1500。 
	enc28j60Write(ERXRDPTL, RXSTART_INIT&0xFF);
	enc28j60Write(ERXRDPTH, RXSTART_INIT>>8);
	// RX end
	enc28j60Write(ERXNDL, RXSTOP_INIT&0xFF);
	enc28j60Write(ERXNDH, RXSTOP_INIT>>8);
	// TX start	  1500
	enc28j60Write(ETXSTL, TXSTART_INIT&0xFF);
	enc28j60Write(ETXSTH, TXSTART_INIT>>8);
	// TX end
	enc28j60Write(ETXNDL, TXSTOP_INIT&0xFF);
	enc28j60Write(ETXNDH, TXSTOP_INIT>>8);
	// do bank 1 stuff, packet filter:
        // For broadcast packets we allow only ARP packtets
        // All other packets should be unicast only for our mac (MAADR)
        //
        // The pattern to match on is therefore
        // Type     ETH.DST
        // ARP      BROADCAST
        // 06 08 -- ff ff ff ff ff ff -> ip checksum for theses bytes=f7f9
        // in binary these poitions are:11 0000 0011 1111
        // This is hex 303F->EPMM0=0x3f,EPMM1=0x30
    //接收过滤器
	//UCEN：单播过滤器使能位
    // 当ANDOR = 1 时：
	// 1= 目标地址与本地MAC 地址不匹配的数据包将被丢弃
	// 0= 禁止过滤器
	// 当ANDOR = 0 时：
	// 1= 目标地址与本地MAC 地址匹配的数据包会被接受
	// 0 = 禁止过滤器

    //CRCEN：后过滤器CRC 校验使能位
	// 1 = 所有CRC 无效的数据包都将被丢弃
	// 0 = 不考虑CRC 是否有效
	
	// PMEN：格式匹配过滤器使能位
	// 当ANDOR = 1 时：
	// 1 = 数据包必须符合格式匹配条件，否则将被丢弃
	// 0 = 禁止过滤器
	// 当ANDOR = 0 时：
	// 1 = 符合格式匹配条件的数据包将被接受
	// 0 = 禁止过滤器
	enc28j60Write(ERXFCON, ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_PMEN);
	enc28j60Write(EPMM0, 0x3f);
	enc28j60Write(EPMM1, 0x30);
	enc28j60Write(EPMCSL, 0xf9);
	enc28j60Write(EPMCSH, 0xf7);
	// do bank 2 stuff
	// enable MAC receive
	//bit 0 MARXEN：MAC 接收使能位
		// 1= 允许MAC 接收数据包
		// 0 = 禁止数据包接收
	//bit  3 TXPAUS：暂停控制帧发送使能位
		// 1= 允许MAC 发送暂停控制帧（用于全双工模式下的流量控制）
		//0 = 禁止暂停帧发送
	//bit 2 RXPAUS：暂停控制帧接收使能位
		// 1 = 当接收到暂停控制帧时，禁止发送（正常操作）
		// 0 = 忽略接收到的暂停控制帧
	enc28j60Write(MACON1, MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
	// bring MAC out of reset
	//将MACON2 中的MARST 位清零，使MAC 退出复位状态。
	enc28j60Write(MACON2, 0x00);
	// enable automatic padding to 60bytes and CRC operations
	//bit 7-5 PADCFG2:PACDFG0：自动填充和CRC 配置位
		//111 = 用0 填充所有短帧至64 字节长，并追加一个有效的CRC
		//110 = 不自动填充短帧
		//101 = MAC 自动检测具有8100h 类型字段的VLAN 协议帧，并自动填充到64 字节长。如果不
		//是VLAN 帧，则填充至60 字节长。填充后还要追加一个有效的CRC
		//100 = 不自动填充短帧
		//011 = 用0 填充所有短帧至64 字节长，并追加一个有效的CRC
		//010 = 不自动填充短帧
		//001 = 用0 填充所有短帧至60 字节长，并追加一个有效的CRC
		//000 = 不自动填充短帧
	//bit 4 TXCRCEN：发送CRC 使能位
	  	// 1= 不管PADCFG如何，MAC都会在发送帧的末尾追加一个有效的CRC。 如果PADCFG规定要
		//追加有效的CRC，则必须将TXCRCEN 置1。
		// 0 = MAC不会追加CRC。 检查最后4 个字节，如果不是有效的CRC 则报告给发送状态向量。
	//bit 0 FULDPX：MAC 全双工使能位
		// 1= MAC工作在全双工模式下。 PHCON1.PDPXMD 位必须置1。
		// 0 = MAC工作在半双工模式下。 PHCON1.PDPXMD 位必须清零。
		
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN|MACON3_FULDPX);
	// set inter-frame gap (non-back-to-back)
	//配置非背对背包间间隔寄存器的低字节MAIPGL。 大多数应用使用12h 编程该寄存器。
	//如果使用半双工模式，应编程非背对背包间间隔寄存器的高字节MAIPGH。 大多数应用使用0Ch
	//编程该寄存器。
	enc28j60Write(MAIPGL, 0x12);
	enc28j60Write(MAIPGH, 0x0C);
	// set inter-frame gap (back-to-back)
	//配置背对背包间间隔寄存器MABBIPG。当使用全双工模式时，大多数应用使用15h 编程该寄存
	//器，而使用半双工模式时则使用12h 进行编程。
	enc28j60Write(MABBIPG, 0x15);
    
	// Set the maximum packet size which the controller will accept
    // Do not send packets longer than MAX_FRAMELEN:
	// 最大帧长度  1500
	enc28j60Write(MAMXFLL, MAX_FRAMELEN&0xFF);	
	enc28j60Write(MAMXFLH, MAX_FRAMELEN>>8);

	// write MAC address
	// NOTE: MAC address in ENC28J60 is byte-backward
	enc28j60Write(MAADR5, macaddr[0]);	
	enc28j60Write(MAADR4, macaddr[1]);
	enc28j60Write(MAADR3, macaddr[2]);
	enc28j60Write(MAADR2, macaddr[3]);
	enc28j60Write(MAADR1, macaddr[4]);
	enc28j60Write(MAADR0, macaddr[5]);
    
	//配置PHY为全双工  LEDB为拉电流
	enc28j60PhyWrite(PHCON1, PHCON1_PDPXMD);

	// no loopback of transmitted frames	 禁止环回
    //HDLDIS：PHY 半双工环回禁止位
		//当PHCON1.PDPXMD = 1 或PHCON1.PLOOPBK = 1 时：
		//此位可被忽略。
		//当PHCON1.PDPXMD = 0 且PHCON1.PLOOPBK = 0 时：
	    // 1 =  要发送的数据仅通过双绞线接口发出
		// 0 = 要发送的数据会环回到MAC 并通过双绞线接口发出
		
	enc28j60PhyWrite(PHCON2, PHCON2_HDLDIS);
	// switch to bank 0
	//ECON1 寄存器
		//寄存器3-1 所示为ECON1 寄存器，它用于控制
		//ENC28J60 的主要功能。 ECON1 中包含接收使能、发
		//送请求、DMA 控制和存储区选择位。
	enc28j60SetBank(ECON1);
	// enable interrutps
	//EIE： 以太网中断允许寄存器
	//bit 7 INTIE： 全局INT 中断允许位
		// 1 =  允许中断事件驱动INT 引脚
		// 0 = 禁止所有INT 引脚的活动（引脚始终被驱动为高电平）
	//bit 6 PKTIE： 接收数据包待处理中断允许位
		// 1  =  允许接收数据包待处理中断
		// 0 = 禁止接收数据包待处理中断
		
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE|EIE_PKTIE);
	// enable packet reception
	//bit 2 RXEN：接收使能位
	    // 1  = 通过当前过滤器的数据包将被写入接收缓冲器
		//0 = 忽略所有接收的数据包
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);

    //指示灯状态:0x476 is PHLCON LEDA(绿)=links status, LEDB(红)=receive/transmit
    //enc28j60PhyWrite(PHLCON,0x7a4);
	//PHLCON：PHY 模块LED 控制寄存器	
	enc28j60PhyWrite(PHLCON,0x0476);	
    
	enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
}

// read the revision of the chip:
unsigned char enc28j60getrev(void)
{
	//在EREVID 内也存储了版本信息。 EREVID 是一个只读控
	//制寄存器，包含一个5 位标识符，用来标识器件特定硅片
	//的版本号
	return(enc28j60Read(EREVID));
}

void enc28j60PacketSend(unsigned int len, unsigned char* packet)
{
	// Set the write pointer to start of transmit buffer area
	enc28j60Write(EWRPTL, TXSTART_INIT&0xFF);
	enc28j60Write(EWRPTH, TXSTART_INIT>>8);

	// Set the TXND pointer to correspond to the packet size given
	enc28j60Write(ETXNDL, (TXSTART_INIT+len)&0xFF);
	enc28j60Write(ETXNDH, (TXSTART_INIT+len)>>8);

	// write per-packet control byte (0x00 means use macon3 settings)
	enc28j60WriteOp(ENC28J60_WRITE_BUF_MEM, 0, 0x00);

	// copy the packet into the transmit buffer
	enc28j60WriteBuffer(len, packet);

	// send the contents of the transmit buffer onto the network
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);

    // Reset the transmit logic problem. See Rev. B4 Silicon Errata point 12.
	if( (enc28j60Read(EIR) & EIR_TXERIF) )
	{
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS);
    }
}

// Gets a packet from the network receive buffer, if one is available.
// The packet will by headed by an ethernet header.
//      maxlen  The maximum acceptable length of a retrieved packet.
//      packet  Pointer where packet data should be stored.
// Returns: Packet length in bytes if a packet was retrieved, zero otherwise.
unsigned int enc28j60PacketReceive(unsigned int maxlen, unsigned char* packet)
{
	unsigned int rxstat;
	unsigned int len;

	// check if a packet has been received and buffered
        // The above does not work. See Rev. B4 Silicon Errata point 6.
	if( enc28j60Read(EPKTCNT) ==0 )  //收到的以太网数据包长度
	{
		return(0);
    }

	// Set the read pointer to the start of the received packet		 缓冲器读指针
	enc28j60Write(ERDPTL, (NextPacketPtr));
	enc28j60Write(ERDPTH, (NextPacketPtr)>>8);

	// read the next packet pointer
	NextPacketPtr  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
	NextPacketPtr |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8;

	// read the packet length (see datasheet page 43)
	len  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
	len |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8;

    len-=4; //remove the CRC count
    
	// read the receive status (see datasheet page 43)
	rxstat  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
	rxstat |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8;
    
	// limit retrieve length
    if (len>maxlen-1)
	{
        len=maxlen-1;
    }

    // check CRC and symbol errors (see datasheet page 44, table 7-3):
    // The ERXFCON.CRCEN is set by default. Normally we should not
    // need to check this.
    if ((rxstat & 0x80)==0)
	{
		// invalid
		len=0;
    }
	else
	{
        // copy the packet from the receive buffer
        enc28j60ReadBuffer(len, packet);
    }
    
	// Move the RX read pointer to the start of the next received packet
	// This frees the memory we just read out
	enc28j60Write(ERXRDPTL, (NextPacketPtr));
	enc28j60Write(ERXRDPTH, (NextPacketPtr)>>8);

	// decrement the packet counter indicate we are done with this packet
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PKTDEC);

    return(len);
}

unsigned char mymac[6] = {0x32,0x12,0x35,0x11,0x01,0x51};

//網口
//How to test
/*
3.3V供电
把模块插上网线，连上开发板的串口，波特率115200
打开串口工具可看到mac和模块IP
在电脑端ping 模块IP，可在串口工具上看到数据包信息
*/


//IO DEFINETION	20150727 xie
/*
CS	 --> PA4
MISO --> PA6
MOSI --> PA7
SCK  --> PA5
INT  --> 悬空
WOL  --> 悬空
CLK  --> 悬空
*/

void enc28j60_Test(void)
{
	/*SPI1接口初始化*/
  SPI1_Init();
	
  /*初始化ENC28J60*/
  enc28j60Init(mymac);	

  /*ENC28J60初始化以及Server程序*/
  simple_server();
}

