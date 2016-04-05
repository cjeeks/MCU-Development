#ifndef __FLASH_H
#define __FLASH_H			    
#include "sys.h" 

#define SPI_FLASH_ANALOG  /*SPI_FLASH_HAL*/

#include "stm32f10x.h"

// SPI_SCK
#define SPI_FLASH_SCK_S        GPIOC, GPIO_Pin_1
#define SPI_FLASH_SCK_PORT_S   GPIOC
#define SPI_FLASH_SCK_PIN_S    GPIO_Pin_1

// SPI_MISO
#define SPI_FLASH_MISO_S       GPIOC, GPIO_Pin_2
#define SPI_FLASH_MISO_PORY_S  GPIOC
#define SPI_FLASH_MISO_PIN_S   GPIO_Pin_2

// SPI_MOSI
#define SPI_FLASH_MOSI_S       GPIOC, GPIO_Pin_3
#define SPI_FLASH_MOSI_PORY_S  GPIOC
#define SPI_FLASH_MOSI_PIN_S   GPIO_Pin_3

// io ctrl
#define SPI_FLASH_SCK_S_1      {GPIOC->BSRR = GPIO_Pin_1;}
#define SPI_FLASH_SCK_S_0      {GPIOC->BRR  = GPIO_Pin_1;}

#define SPI_FLASH_MISO_S_G     (GPIOC->IDR & GPIO_Pin_2)
#define SPI_FLASH_MISO_S_1     {GPIOC->BSRR = GPIO_Pin_2;}
#define SPI_FLASH_MISO_S_0     {GPIOC->BRR  = GPIO_Pin_2;}

#define SPI_FLASH_MOSI_S_1     {GPIOC->BSRR = GPIO_Pin_3;}
#define SPI_FLASH_MOSI_S_0     {GPIOC->BRR  = GPIO_Pin_3;}

#define SPI_FLASH_NSS_S_1     {GPIOB->BSRR = GPIO_Pin_12;}
#define SPI_FLASH_NSS_S_0     {GPIOB->BRR  = GPIO_Pin_12;}


// NSS
#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOB, GPIO_Pin_12)

void SPI_FLASH_Write_Enable(void);
void SPI_Flash_Init(void);
void SPI_FLASH_SectorErase(u32 SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(const u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_Flash_Write(const u8* pBuffer, u32 WriteAddr, u32 NumByteToWrite);
void SPI_Flash_Read(u8* pBuffer, u32 ReadAddr, u32 NumByteToRead);
u32 SPI_FLASH_ReadID(void);
u32 SPI_FLASH_ReadDeviceID(void);
void SPI_FLASH_StartReadSequence(u32 ReadAddr);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);

#ifdef SPI_FLASH_ANALOG
void SPI_FLASH_SendByte(u8 byte);
#else
u8 SPI_FLASH_SendByte(u8 byte);
#endif

u8 SPI_FLASH_ReadByte(void);
u16 SPI_FLASH_SendHalfWord(u16 HalfWord);
void SPI_FLASH_Write_Enable(void);
void SPI_FLASH_WaitForWriteEnd(void);


/*	  
//W25X系列/Q系列芯片列表	   
//W25Q80 ID  0XEF13
//W25Q16 ID  0XEF14
//W25Q32 ID  0XEF15
//W25Q32 ID  0XEF16	
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16

extern u16 SPI_FLASH_TYPE;//定义我们使用的flash芯片型号

#define	SPI_FLASH_CS PBout(12)  //选中FLASH	
				 
////////////////////////////////////////////////////////////////////////////
 
//指令表
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

void SPI_Flash_Init(void);
u16  SPI_Flash_ReadID(void);  	    //读取FLASH ID
u8	 SPI_Flash_ReadSR(void);        //读取状态寄存器 
void SPI_FLASH_Write_SR(u8 sr);  	//写状态寄存器
void SPI_FLASH_Write_Enable(void);  //写使能 
void SPI_FLASH_Write_Disable(void);	//写保护
void SPI_FLASH_PageWrite(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u32 NumByteToRead);   //读取flash
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u32 NumByteToWrite);//写入flash
void SPI_Flash_Erase_Chip(void);    	  //整片擦除
void SPI_Flash_Erase_Sector(u32 Dst_Addr);//扇区擦除
void SPI_Flash_Wait_Busy(void);           //等待空闲
void SPI_Flash_PowerDown(void);           //进入掉电模式
void SPI_Flash_WAKEUP(void);			  //唤醒
*/
#endif
