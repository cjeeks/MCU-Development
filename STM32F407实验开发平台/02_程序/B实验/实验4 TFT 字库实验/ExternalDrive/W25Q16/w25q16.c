#include "stm32f4xx.h"
#include "w25q16.h"

static void W25Q16_Configuration(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC , ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);
    
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_SPI2);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
        
    /*!< SPI SCK pin configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /*!< SPI MOSI pin configuration */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /*!< SPI MISO pin configuration */
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /*!< Configure sFLASH Card CS pin in output pushpull mode ********************/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    W25Q16_CS_HIGH();

    /*!< SPI configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);
    
    /*!< Enable the sFLASH_SPI  */
    SPI_Cmd(SPI2 , ENABLE);



//	/*-----------------端口配置-------------------*/
//	/* SPI1_SCK SPI1_MISO SPI1_MOSI*/
//    GPIO_InitStructure.GPIO_Pin = W25Q16_SCK_PIN | W25Q16_MISO_PIN | W25Q16_MOSI_PIN;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(W25Q16_PORT, &GPIO_InitStructure);
//
//	/* FLASH_CS */
//	GPIO_InitStructure.GPIO_Pin = W25Q16_CS_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(W25Q16_PORT, &GPIO_InitStructure);
//
//	/*-----------------SPI配置--------------------*/
//	/* 初始化 */
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	/*串行时钟稳定状态是高电平*/
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;/* 时钟活跃边沿？？？*/
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; /*SPI波特率预分频*/
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; /*高位在前*/ 
//	SPI_InitStructure.SPI_CRCPolynomial = 7; /*the polynomial used for the CRC calculation*/
//	SPI_Init(W25Q16_SPI, &SPI_InitStructure);
//
//	/* SPI使能 */
//	SPI_Cmd(W25Q16_SPI, ENABLE);
	   
}

/**	
	*名称：SPIx_ReadWriteByte
	*输入：TxData 要写入的字节
	*输出：
	*返回：读取到的字节
	*功能：读写一个字节
	*说明：
**/
u8 SPIx_ReadWriteByte(u8 TxData)
{		
	uint8_t RxData = 0;
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);	/*等待发送缓冲区空 */
	SPI_I2S_SendData(SPI2, TxData);	               /*发一个字节*/

    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);	 /*等待数据接收	 */
	RxData = SPI_I2S_ReceiveData(SPI2);	        /*返回接收到的数据*/

    return (uint8_t)RxData;				    
}

/**
	*名称：SPI_Flash_Read
	*输入：ReadAddr 开始读取的地址(24bit)
		   NumByteToRead 要读取的字节数(最大65535)
	*输出: pBuffer 指向的数组
	*返回：无
	*功能：在指定地址开始读取指定长度的数据		   
	*说明：
**/
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
 	u16 i;    												    
	W25Q16_CS_LOW();                            //使能器件   
    SPIx_ReadWriteByte(W25X_ReadData);         //发送读取命令   
    SPIx_ReadWriteByte((u8)((ReadAddr)>>16));  //发送24bit地址    
    SPIx_ReadWriteByte((u8)((ReadAddr)>>8));   
    SPIx_ReadWriteByte((u8)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
	{ 
        pBuffer[i]=SPIx_ReadWriteByte(0XFF);   //循环读数  
    }
	W25Q16_CS_HIGH();                            //取消片选     	      
}

//读取SPI_FLASH的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
u8 SPI_Flash_ReadSR(void)   
{  
	u8 byte=0;   
	W25Q16_CS_LOW();                            //使能器件   
	SPIx_ReadWriteByte(0x05);    //发送读取状态寄存器命令    
	byte=SPIx_ReadWriteByte(0Xff);             //读取一个字节  
	W25Q16_CS_HIGH();                            //取消片选     
	return byte;   
} 

//等待空闲
void SPI_Flash_Wait_Busy(void)   
{   
	while ((SPI_Flash_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}
 
//SPI_FLASH写使能	
//将WEL置位   
void SPI_FLASH_Write_Enable(void)   
{
	W25Q16_CS_LOW();                            //使能器件   
    SPIx_ReadWriteByte(W25X_WriteEnable);      //发送写使能  
	W25Q16_CS_HIGH();                            //取消片选     	      
} 

/**
	*名称：SPI_Flash_Erase_Chip
	*输入：无
	*输出：无
	*返回：无
	*功能：擦除整个芯片整片擦除时间:
		   W25X16:25s 
		   W25X32:40s 
		   W25X64:40s 
		   等待时间超长...
	*说明：擦除时间来源于手册，有待验证

**/
void SPI_Flash_Erase_Chip(void)   
{                                             
    SPI_FLASH_Write_Enable();                  //SET WEL 
    SPI_Flash_Wait_Busy();   
  	W25Q16_CS_LOW();                            //使能器件   
    SPIx_ReadWriteByte(W25X_ChipErase);        //发送片擦除命令  
	W25Q16_CS_HIGH();                            //取消片选     	      
	SPI_Flash_Wait_Busy();   				   //等待芯片擦除结束
} 


/**
	*名称：SPI_Flash_Write_Page
	*输入：WriteAddr 开始写入的地址
	       NumByteToWrite 要写入的字节数(最大256)，该数不应该超过该页的剩余字节数！！！
	*输出：pBuffer 数据存储区
	*返回：无
	*功能：在指定地址开始写入最大256字节的数据
	*说明：SPI在一页(0~65535)内写入少于256个字节的数据
**/	 					
void SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
 	u16 i;  
    SPI_FLASH_Write_Enable();                  //SET WEL 
	W25Q16_CS_LOW();                            //使能器件   
    SPIx_ReadWriteByte(W25X_PageProgram);      //发送写页命令   
    SPIx_ReadWriteByte((u8)((WriteAddr)>>16)); //发送24bit地址    
    SPIx_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPIx_ReadWriteByte((u8)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++) SPIx_ReadWriteByte(pBuffer[i]);//循环写数  
	W25Q16_CS_HIGH();                            //取消片选 
	SPI_Flash_Wait_Busy();					   //等待写入结束
} 

/**
	*名称：SPI_Flash_ReadID
	*功能：读取芯片ID  W25X16的ID:0XEF14
**/
u16 SPI_Flash_ReadID(void)
{
	u16 Temp = 0;	  
	W25Q16_CS_LOW();
	SPIx_ReadWriteByte(0x90);     /*发送读取ID命令*/	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	    
	SPIx_ReadWriteByte(0x00); 	 			   
	Temp|=SPIx_ReadWriteByte(0xFF)<<8;  
	Temp|=SPIx_ReadWriteByte(0xFF);	 
	W25Q16_CS_HIGH();				    
	return Temp;
}

uint8_t W25Q16_Init(void)
{
//	uint16_t temp;
	W25Q16_Configuration();		  /* SPI引脚配置及初始化 */
	if(SPI_Flash_ReadID()==W25Q16_ID)
	{
//		printf("\r\n W25Q16 ID is 0x%x \r\n", temp);
		return 0;
	}
	else
        return 1;
}
