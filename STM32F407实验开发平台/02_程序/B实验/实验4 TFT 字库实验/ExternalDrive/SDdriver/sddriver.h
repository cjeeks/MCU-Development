#ifndef __SDDRIVER_H
#define __SDDRIVER_H
#include "stm32f4xx.h"
 
#define SD_CS_ENABLE()      GPIO_ResetBits(GPIOF,GPIO_Pin_6);GPIO_SetBits(GPIOG,GPIO_Pin_15);GPIO_SetBits(GPIOC,GPIO_Pin_13)   /*使能SD卡*/
#define SD_CS_DISABLE()     GPIO_SetBits(GPIOF,GPIO_Pin_6);GPIO_SetBits(GPIOG,GPIO_Pin_15);GPIO_SetBits(GPIOC,GPIO_Pin_13)    /*失能SD卡*/

#define SPI_SPEED_LOW     0
#define SPI_SPEED_HIGH	  1

/* Private define ------------------------------------------------------------*/
/* SD卡类型定义 */
#define SD_TYPE_MMC     0
#define SD_TYPE_V1      1
#define SD_TYPE_V2      2
#define SD_TYPE_V2HC    4

/* SD传输数据结束后是否释放总线宏定义 */
#define NO_RELEASE      0
#define RELEASE         1

/* SD卡指令表 */
#define CMD0    0       //卡复位
#define CMD9    9       //命令9 ，读CSD数据
#define CMD10   10      //命令10，读CID数据
#define CMD12   12      //命令12，停止数据传输
#define CMD16   16      //命令16，设置SectorSize 应返回0x00
#define CMD17   17      //命令17，读sector
#define CMD18   18      //命令18，读Multi sector
#define ACMD23  23      //命令23，设置多sector写入前预先擦除N个block
#define CMD24   24      //命令24，写sector
#define CMD25   25      //命令25，写Multi sector
#define ACMD41  41      //命令41，应返回0x00
#define CMD55   55      //命令55，应返回0x01
#define CMD58   58      //命令58，读OCR信息
#define CMD59   59      //命令59，使能/禁止CRC，应返回0x00

/* SPI波特率设置 低速256分频 */
uint8_t SD_Init(void);
void SPI_Configuration(void);
void SPI_SetSpeed(u8 SpeedSet);
u8 SPI_ReadWriteByte(u8 TxData);
u8 SD_SendCommand(u8 cmd, u32 arg, u8 crc);
u8 SD_SendCommand_NoDeassert(u8 cmd, u32 arg, u8 crc);

u8 SD_ReadSingleBlock(u32 sector, u8 *buffer);
u8 SD_ReadMultiBlock(u32 sector, u8 *buffer, u8 count);
u8 SD_WriteSingleBlock(u32 sector, const u8 *data);
u8 SD_WriteMultiBlock(u32 sector, const u8 *data, u8 count);

u8 SD_WaitReady(void);
u32 SD_GetCapacity(void);
u8 SD_GetCSD(u8 *csd_data);
u8 SD_ReceiveData(u8 *data, u16 len, u8 release);



#endif
