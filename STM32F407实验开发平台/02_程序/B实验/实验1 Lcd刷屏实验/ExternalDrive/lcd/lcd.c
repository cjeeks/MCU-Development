
#include "lcd.h"

#define LCD_RAM    *(__IO uint16_t *) (0x6C000002)    	//地址寄存器
#define LCD_REG    *(__IO uint16_t *) (0x6C000000)	 	//指令寄存器

#define rw_data_prepare()               write_cmd(34)


void write_cmd(unsigned short cmd);
unsigned short read_data(void);
unsigned short DeviceCode;





static void delay(int cnt)
{
	volatile unsigned int dl;
	while(cnt--)
	{
		for(dl=0; dl<500; dl++);
	}
}

/*
 *	
 */
void write_cmd(unsigned short cmd)
{	
	LCD_REG = cmd;	
}

unsigned short read_data(void)
{
	unsigned short temp;	
	temp = LCD_RAM;
	temp = LCD_RAM;
	return temp;
}

void write_data(unsigned short data_code )
{	
	LCD_RAM = data_code;
}

void write_reg(unsigned char reg_addr,unsigned short reg_val)
{
	write_cmd(reg_addr);
	write_data(reg_val);
}

unsigned short read_reg(unsigned char reg_addr)
{
	unsigned short val=0;
	write_cmd(reg_addr);
	val = read_data();
	return (val);
}


void lcd_SetCursor(unsigned int x,unsigned int y)
{
	write_reg(0x004e,x);    /* 0-239 */
	write_reg(0x004f,y);    /* 0-319 */
}
/* 读取指定地址的GRAM */
static unsigned short lcd_read_gram(unsigned int x,unsigned int y)
{
	unsigned short temp;
	lcd_SetCursor(x,y);
	rw_data_prepare();
	/* dummy read */
	temp = read_data();
	temp = read_data();
	return temp;
}
static void lcd_data_bus_test(void)
{
	unsigned short temp1;
	unsigned short temp2;
	/* wirte */
	lcd_SetCursor(0,0);
	rw_data_prepare();
	write_data(0x5555);

	lcd_SetCursor(1,0);
	rw_data_prepare();
	write_data(0xAAAA);

	/* read */
	lcd_SetCursor(0,0);
	temp1 = lcd_read_gram(0,0);
	temp2 = lcd_read_gram(1,0);

	if( (temp1 == 0x5555) && (temp2 == 0xAAAA) )
	{
		//printf(" data bus test pass!\r\n");
	}
	else
	{
		//printf(" data bus test error: %04X %04X\r\n",temp1,temp2);
	}
}

void lcd_clear(unsigned short Color)
{
    unsigned int count;

	write_cmd(0x002a);	
	write_data(0);	    
	write_data(0);
	write_data(HDP>>8);	    
	write_data(HDP&0x00ff);
    write_cmd(0x002b);	
	write_data(0);	    
	write_data(0);
	write_data(VDP>>8);	    
	write_data(VDP&0x00ff);
	write_cmd(0x002c);	
	write_cmd(0x002c);


	for(count=0;count<130560;count++){
		
		write_data(Color);
	}
}

void port_fsmc_init(void)
{	
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	//FSMC_NORSRAMTimingInitTypeDef  p;
	GPIO_InitTypeDef GPIO_InitStructure;

	
	FSMC_NORSRAMTimingInitTypeDef  Timing_read,Timing_write;

	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &Timing_read;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &Timing_write;

	FSMC_NORSRAMStructInit(&FSMC_NORSRAMInitStructure);

	/*--------------------- read timings configuration ---------------------*/
	Timing_read.FSMC_AddressSetupTime = 0;  /* [3:0] F2/F4 1~15 HCLK */
	Timing_read.FSMC_AddressHoldTime = 0;   /* [7:4] keep 0x00 in SRAM mode */
	Timing_read.FSMC_DataSetupTime = 3;     /* [15:8] F2/F4 0~255 HCLK */
	/* [19:16] Time between NEx high to NEx low (BUSTURN HCLK) */
	Timing_read.FSMC_BusTurnAroundDuration = 0;
	Timing_read.FSMC_CLKDivision = 0; /* [24:20] keep 0x00 in SRAM mode  */
	Timing_read.FSMC_DataLatency = 0; /* [27:25] keep 0x00 in SRAM mode  */
	Timing_read.FSMC_AccessMode = FSMC_AccessMode_A;

	/*--------------------- write timings configuration ---------------------*/
	Timing_write.FSMC_AddressSetupTime = 0;  /* [3:0] F2/F4 1~15 HCLK */
	Timing_write.FSMC_AddressHoldTime = 0;   /* [7:4] keep 0x00 in SRAM mode */
	Timing_write.FSMC_DataSetupTime = 0;     /* [15:8] F2/F4 0~255 HCLK */
	/* [19:16] Time between NEx high to NEx low (BUSTURN HCLK) */
	Timing_write.FSMC_BusTurnAroundDuration = 0;
	Timing_write.FSMC_CLKDivision = 0; /* [24:20] keep 0x00 in SRAM mode  */
	Timing_write.FSMC_DataLatency = 0; /* [27:25] keep 0x00 in SRAM mode  */
	Timing_write.FSMC_AccessMode = FSMC_AccessMode_A;

	/* Enable GPIOs clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);
	/* Enable FSMC clock */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);	
	/* Configure the BL pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);	
	

	GPIO_ResetBits(GPIOF,GPIO_Pin_9);

	/*
	+-------------------+--------------------+------------------+------------------+
	+                       SRAM pins assignment                                  +
	+-------------------+--------------------+------------------+------------------+
	| PD0  <-> FSMC_D2  | PE0  <-> FSMC_NBL0 | PF0  <-> FSMC_A0 | PG0 <-> FSMC_A10 |
	| PD1  <-> FSMC_D3  | PE1  <-> FSMC_NBL1 | PF1  <-> FSMC_A1 | PG1 <-> FSMC_A11 |
	| PD4  <-> FSMC_NOE | PE7  <-> FSMC_D4   | PF2  <-> FSMC_A2 | PG2 <-> FSMC_A12 |
	| PD5  <-> FSMC_NWE | PE8  <-> FSMC_D5   | PF3  <-> FSMC_A3 | PG3 <-> FSMC_A13 |
	| PD8  <-> FSMC_D13 | PE9  <-> FSMC_D6   | PF4  <-> FSMC_A4 | PG4 <-> FSMC_A14 |
	| PD9  <-> FSMC_D14 | PE10 <-> FSMC_D7   | PF5  <-> FSMC_A5 | PG5 <-> FSMC_A15 |
	| PD10 <-> FSMC_D15 | PE11 <-> FSMC_D8   | PF12 <-> FSMC_A6 | PG9 <-> FSMC_NE2 |
	| PD11 <-> FSMC_A16 | PE12 <-> FSMC_D9   | PF13 <-> FSMC_A7 |------------------+
	| PD12 <-> FSMC_A17 | PE13 <-> FSMC_D10  | PF14 <-> FSMC_A8 | 
	| PD14 <-> FSMC_D0  | PE14 <-> FSMC_D11  | PF15 <-> FSMC_A9 | 
	| PD15 <-> FSMC_D1  | PE15 <-> FSMC_D12  |------------------+
	+-------------------+--------------------+
	*/
	/*
	+-------------------+--------------------+------------------+-------------------+
	+                       STM32 FSMC pins assignment                              +
	+-------------------+--------------------+------------------+-------------------+
	| PD0  <-> FSMC_D2  | PE0  <-> FSMC_NBL0 | PF0  <-> FSMC_A0 | PG0  <-> FSMC_A10 |
	| PD1  <-> FSMC_D3  | PE1  <-> FSMC_NBL1 | PF1  <-> FSMC_A1 | PG1  <-> FSMC_A11 |
	| PD4  <-> FSMC_NOE | PE3  <-> FSMC_A19  | PF2  <-> FSMC_A2 | PG2  <-> FSMC_A12 |
	| PD5  <-> FSMC_NWE | PE4  <-> FSMC_A20  | PF3  <-> FSMC_A3 | PG3  <-> FSMC_A13 |
	| PD8  <-> FSMC_D13 | PE7  <-> FSMC_D4   | PF4  <-> FSMC_A4 | PG4  <-> FSMC_A14 |
	| PD9  <-> FSMC_D14 | PE8  <-> FSMC_D5   | PF5  <-> FSMC_A5 | PG5  <-> FSMC_A15 |
	| PD10 <-> FSMC_D15 | PE9  <-> FSMC_D6   | PF12 <-> FSMC_A6 | PG9  <-> FSMC_NE2 |
	| PD11 <-> FSMC_A16 | PE10 <-> FSMC_D7   | PF13 <-> FSMC_A7 | PG12 <-> FSMC_NE4 |
	| PD12 <-> FSMC_A17 | PE11 <-> FSMC_D8   | PF14 <-> FSMC_A8 |-------------------+
	| PD13 <-> FSMC_A18 | PE12 <-> FSMC_D9   | PF15 <-> FSMC_A9 |
	| PD14 <-> FSMC_D0  | PE13 <-> FSMC_D10  |------------------+
	| PD15 <-> FSMC_D1  | PE14 <-> FSMC_D11  |
	| PD7  <-> FSMC_NE1 | PE15 <-> FSMC_D12  |
	+-------------------+--------------------+
	*/
	
	/* GPIOD configuration */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	//GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
	//GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_FSMC);
	//GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

	/* GPIOE configuration */
	//GPIO_PinAFConfig(GPIOE, GPIO_PinSource0 , GPIO_AF_FSMC);
	//GPIO_PinAFConfig(GPIOE, GPIO_PinSource1 , GPIO_AF_FSMC);
	//GPIO_PinAFConfig(GPIOE, GPIO_PinSource3 , GPIO_AF_FSMC);
	//GPIO_PinAFConfig(GPIOE, GPIO_PinSource4 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);

	/* GPIOF configuration */
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0 , GPIO_AF_FSMC);
	/*GPIO_PinAFConfig(GPIOF, GPIO_PinSource1 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource2 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource3 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource4 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource5 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource12 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource13 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource14 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource15 , GPIO_AF_FSMC);*/

	/* GPIOG configuration */
	/*GPIO_PinAFConfig(GPIOG, GPIO_PinSource0 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource1 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource2 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource3 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource4 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource5 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9 , GPIO_AF_FSMC);*/
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12 , GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4
		| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7
		| GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
		/*| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13*/
		| GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = /*GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_3 |*/
		GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
		GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
		GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  /*| GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3 |
		GPIO_Pin_4  | GPIO_Pin_5  |
		GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15*/;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =/* GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3 |
		GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_9 |*/ GPIO_Pin_12;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;  
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &Timing_read;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &Timing_write;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	/*!< Enable FSMC Bank1_SRAM1 Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);	
}

void lcd_init(void)
{
	port_fsmc_init();

	GPIO_SetBits(GPIOF,GPIO_Pin_9);
	delay(100);
	DeviceCode = read_reg(0x0000);
    //DeviceCode = 0x8999;
//	if (DeviceCode == 0x8999)
//	{
//		// power supply setting
//		// set R07h at 0021h (GON=1,DTE=0,D[1:0]=01)
//		write_reg(0x07,0x0021);
//		// set R00h at 0001h (OSCEN=1)
//		write_reg(0x00,0x0001);
//		// set R07h at 0023h (GON=1,DTE=0,D[1:0]=11)
//		write_reg(0x07,0x0023);
//		// set R10h at 0000h (Exit sleep mode)
//		write_reg(0x10,0x0000);
//		// Wait 30ms
//		delay(3000);
//		// set R07h at 0033h (GON=1,DTE=1,D[1:0]=11)
//		write_reg(0x07,0x0033);
//		// Entry mode setting (R11h)
//		// R11H Entry mode
//		// vsmode DFM1 DFM0 TRANS OEDef WMode DMode1 DMode0 TY1 TY0 ID1 ID0 AM LG2 LG2 LG0
//		//   0     1    1     0     0     0     0      0     0   1   1   1  *   0   0   0
//		write_reg(0x11,0x6070);
//		// LCD driver AC setting (R02h)
//		write_reg(0x02,0x0600);
//		// power control 1
//		// DCT3 DCT2 DCT1 DCT0 BT2 BT1 BT0 0 DC3 DC2 DC1 DC0 AP2 AP1 AP0 0
//		// 1     0    1    0    1   0   0  0  1   0   1   0   0   1   0  0
//		// DCT[3:0] fosc/4 BT[2:0]  DC{3:0] fosc/4
//		write_reg(0x03,0x0804);//0xA8A4
//		write_reg(0x0C,0x0000);//
//		write_reg(0x0D,0x080C);//
//		// power control 4
//		// 0 0 VCOMG VDV4 VDV3 VDV2 VDV1 VDV0 0 0 0 0 0 0 0 0
//		// 0 0   1    0    1    0    1    1   0 0 0 0 0 0 0 0
//		write_reg(0x0E,0x2900);
//		write_reg(0x1E,0x00B8);
//		write_reg(0x01,0x2B3F);//驱动输出控制320*240  0x6B3F
//		write_reg(0x10,0x0000);
//		write_reg(0x05,0x0000);
//		write_reg(0x06,0x0000);
//		write_reg(0x16,0xEF1C);
//		write_reg(0x17,0x0003);
//		write_reg(0x07,0x0233);//0x0233
//		write_reg(0x0B,0x0000|(3<<6));
//		write_reg(0x0F,0x0000);//扫描开始地址
//		write_reg(0x41,0x0000);
//		write_reg(0x42,0x0000);
//		write_reg(0x48,0x0000);
//		write_reg(0x49,0x013F);
//		write_reg(0x4A,0x0000);
//		write_reg(0x4B,0x0000);
//		write_reg(0x44,0xEF00);
//		write_reg(0x45,0x0000);
//		write_reg(0x46,0x013F);
//		write_reg(0x30,0x0707);
//		write_reg(0x31,0x0204);
//		write_reg(0x32,0x0204);
//		write_reg(0x33,0x0502);
//		write_reg(0x34,0x0507);
//		write_reg(0x35,0x0204);
//		write_reg(0x36,0x0204);
//		write_reg(0x37,0x0502);
//		write_reg(0x3A,0x0302);
//		write_reg(0x3B,0x0302);
//		write_reg(0x23,0x0000);
//		write_reg(0x24,0x0000);
//		write_reg(0x25,0x8000);   // 65hz
//		write_reg(0x4f,0);        // 行首址0
//		write_reg(0x4e,0);        // 列首址0	

//	}	
//	else
//	{
//		//printf("LCD model is not recognized,DeviceCode = 0x%x!\r\n",DeviceCode);
//		//return;
//	}
	//数据总线测试,用于测试硬件连接是否正常.

    
    write_cmd(0x002b);	
	write_data(0);

	Delay(5); // delay 50 ms 
	write_cmd(0x00E2);					//PLL multiplier, set PLL clock to 120M
	write_data(0x001D);					//N=0x36 for 6.5M, 0x23 for 10M crystal
	write_data(0x0002);
	write_data(0x0004);
	
	write_cmd(0x00E0);					//PLL enable
	write_data(0x0001);
	Delay(1);
	write_cmd(0x00E0);
	write_data(0x0003);
	Delay(5);
	write_cmd(0x0001);  					//software reset
	Delay(5);
	write_cmd(0x00E6);					//PLL setting for PCLK, depends on resolution
//	LCD_WriteRAM(0x0001);
//	LCD_WriteRAM(0x0033);
//	LCD_WriteRAM(0x0032);
	write_data(0x0000);
	write_data(0x00D9);
	write_data(0x0016);

	write_cmd(0x00B0);					//LCD SPECIFICATION
	write_data(0x0020);
	write_data(0x0000);
	write_data((HDP>>8)&0X00FF);			//Set HDP
	write_data(HDP&0X00FF);
    write_data((VDP>>8)&0X00FF);			//Set VDP
	write_data(VDP&0X00FF);
    write_data(0x0000);

	write_cmd(0x00B4);					//HSYNC
	write_data((HT>>8)&0X00FF); 			//Set HT
	write_data(HT&0X00FF);
	write_data((HPS>>8)&0X00FF);			//Set HPS
	write_data(HPS&0X00FF);
	write_data(HPW);						//Set HPW
	write_data((LPS>>8)&0X00FF); 			//Set HPS
	write_data(LPS&0X00FF);
	write_data(0x0000);

	write_cmd(0x00B6);					//VSYNC
	write_data((VT>>8)&0X00FF);   		//Set VT
	write_data(VT&0X00FF);
	write_data((VPS>>8)&0X00FF); 			//Set VPS
	write_data(VPS&0X00FF);
	write_data(VPW);						//Set VPW
	write_data((FPS>>8)&0X00FF);			//Set FPS
	write_data(FPS&0X00FF);

	//=============================================

	//=============================================
	write_cmd(0x00BA);
	write_data(0x0005);//0x000F);    //GPIO[3:0] out 1

	write_cmd(0x00B8);
	write_data(0x0007);    //GPIO3=input, GPIO[2:0]=output
	write_data(0x0001);    //GPIO0 normal

	write_cmd(0x0036); //rotation
	write_data(0x0000);

	Delay(50);

	write_cmd(0x00BE); //set PWM for B/L
	write_data(0x0006);
	write_data(0x0080);
	
	write_data(0x0001);
	write_data(0x00f0);
	write_data(0x0000);
	write_data(0x0000);

	write_cmd(0x00d0);//设置动态背光控制配置 
	write_data(0x000d);
   
	write_cmd(0x00F0); //pixel data interface
	write_data(0x0003); //03:16位   02:24位

	write_cmd(0x0029); //display on

	//lcd_data_bus_test();
	lcd_clear(Red);	
}
