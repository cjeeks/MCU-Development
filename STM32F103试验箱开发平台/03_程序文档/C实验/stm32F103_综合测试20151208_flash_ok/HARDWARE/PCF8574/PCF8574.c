#include "PCF8574.h"
#include  <math.h>    //Keil library

//PA0(23) - SCL
//PA1(24) - SDA

/*******************************************************************************
* Function Name  : I2C_GPIO_Config
* Description    : Configration Simulation IIC GPIO
* Input          : None 
* Output         : None
* Return         : None
****************************************************************************** */
void PCF8574_I2C_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	PCF8574_I2C_Stop();
}

void PCF8574_i2c_SDA_input(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
   //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	
	 //GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
   //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void PCF8574_i2c_SDA_output(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*******************************************************************************
* Function Name  : PCF8574_I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void PCF8574_I2C_delay(void)
{
		
   u16 i=5000; //’‚¿Ôø…“‘”≈ªØÀŸ∂»	£¨æ≠≤‚ ‘◊ÓµÕµΩ5ªπƒ‹–¥»Î
   while(i) 
   { 
     i--; 
   }  
}

void PCF8574_delay5ms(void)
{
		
   int i=50000;  
   while(i) 
   { 
     i--; 
   }  
}

void PCF8574_delay50us(void)
{
		
   int i=500;  
   while(i) 
   { 
     i--; 
   }  
}
//*************************************************************************************************
//I2C∆ º–≈∫≈
//*************************************************************************************************
void PCF8574_I2C_Start(void)
{
    SDA_H;                    //¿≠∏ﬂ ˝æ›œﬂ
    SCL_H;                    //¿≠∏ﬂ ±÷”œﬂ
    PCF8574_I2C_delay();                 //—” ±
    SDA_L;                    //≤˙…˙œ¬Ωµ—ÿ
    PCF8574_I2C_delay();                 //—” ±
    SCL_L;                    //¿≠µÕ ±÷”œﬂ
    PCF8574_I2C_delay();                 //—” 	
}
//*************************************************************************************************
//I2CÕ£÷π–≈∫≈
//*************************************************************************************************
void PCF8574_I2C_Stop(void)
{
	  SCL_L;                    //¿≠∏ﬂ ±÷”œﬂ
    SDA_L;                    //¿≠µÕ ˝æ›œﬂ
    PCF8574_I2C_delay();                 //—” ±	
    SCL_H;                    //¿≠∏ﬂ ±÷”œﬂ
    PCF8574_I2C_delay();                 //—” ±
    SDA_H;                    //≤˙…˙…œ…˝—ÿ
    PCF8574_I2C_delay();                 //—” ±
}
//**************************************************************************************************
//I2C∑¢ÀÕ”¶¥–≈∫≈
//»Îø⁄≤Œ ˝:ack (0:ACK 1:NAK)
//**************************************************************************************************
void PCF8574_I2C_SendACK(char ack)
{
	if(ack == 1)
	  SDA_H;
	else
    SDA_L;                  //–¥”¶¥–≈∫≈
	SCL_H;                    //¿≠∏ﬂ ±÷”œﬂ
	PCF8574_I2C_delay();                 //—” ±
	SCL_L;                    //¿≠µÕ ±÷”œﬂ
	PCF8574_I2C_delay();                 //—” ±
}
//****************************************************************************************************
//I2CΩ” ’”¶¥–≈∫≈
//****************************************************************************************************
char PCF8574_I2C_RecvACK(void)
{
	char CY;
	PCF8574_i2c_SDA_input();
	PCF8574_I2C_delay();                 //—” ±	
	SCL_H;                    //¿≠∏ﬂ ±÷”œﬂ
	PCF8574_I2C_delay();                 //—” ±
	if(SDA_read)
    CY = 1;                   //∂¡”¶¥–≈∫≈
	else
		CY = 0;
	SCL_L;                    //¿≠µÕ ±÷”œﬂ
	PCF8574_i2c_SDA_output();
	PCF8574_I2C_delay();                 //—” ±
	return CY;
}
//*****************************************************************************************************
//œÚI2C◊‹œﬂ∑¢ÀÕ“ª∏ˆ◊÷Ω⁄ ˝æ›
//*****************************************************************************************************
void PCF8574_I2C_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8Œªº∆ ˝∆˜
    {
			  if(dat&0x80)
          SDA_H;               //ÀÕ ˝æ›ø⁄
			  else
					SDA_L;
				
        dat <<= 1;              //“∆≥ˆ ˝æ›µƒ◊Ó∏ﬂŒª			
        SCL_H;                //¿≠∏ﬂ ±÷”œﬂ
        PCF8574_I2C_delay();             //—” ±
        SCL_L;                //¿≠µÕ ±÷”œﬂ
        PCF8574_I2C_delay();             //—” ±
    }
    PCF8574_I2C_RecvACK();
}
//*****************************************************************************************************
//¥”I2C◊‹œﬂΩ” ’“ª∏ˆ◊÷Ω⁄ ˝æ›
//******************************************************************************************************
uchar PCF8574_I2C_RecvByte(void)
{
    uchar i;
    uchar dat = 0;
		PCF8574_i2c_SDA_input();
    for (i=0; i<8; i++)         //8Œªº∆ ˝∆˜
    {
        SCL_L;                //¿≠µÕ ±÷”œﬂ
        PCF8574_I2C_delay();             //—” ± 
        SCL_H;                //¿≠∏ﬂ ±÷”œﬂ
        PCF8574_I2C_delay();             //—” ±
  			dat <<= 1;			
			  if(SDA_read)
					dat |= 1;             //∂¡ ˝æ›               

    }
	  PCF8574_i2c_SDA_output();		
    return dat;
}

//*****************************************************************************************************
//œÚI2C…Ë±∏–¥»Î“ª∏ˆ◊÷Ω⁄ ˝æ›
//*****************************************************************************************************

//REG_Address : SALVE ADDRESS
//REG_data    : data
void PCF8574_Single_WriteI2C(uchar REG_Address,uchar REG_data)
{  uchar t;
	 t=(REG_Address<<1);
	
    PCF8574_I2C_Start();       //∆ º–≈∫≈
	  PCF8574_I2C_SendByte(t);   //∑¢ÀÕ…Ë±∏µÿ÷∑+–¥–≈∫≈
    PCF8574_I2C_SendByte(REG_data);   //ƒ⁄≤øºƒ¥Ê∆˜µÿ÷∑
    PCF8574_I2C_Stop();        //∑¢ÀÕÕ£÷π–≈∫≈
}

//*******************************************************************************************************
//¥”I2C…Ë±∏∂¡»°“ª∏ˆ◊÷Ω⁄ ˝æ›
//*******************************************************************************************************
uchar PCF8574_Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	 uchar t;
	t=((REG_Address<<1)|0x01);	
	
	PCF8574_I2C_Start();                   //∆ º–≈∫≈
	PCF8574_I2C_SendByte(t);  //∑¢ÀÕ…Ë±∏µÿ÷∑+∂¡–≈∫≈
	REG_data=PCF8574_I2C_RecvByte();       //∂¡≥ˆºƒ¥Ê∆˜ ˝æ›
	PCF8574_I2C_SendACK(1);                //Ω” ’”¶¥–≈∫≈
	PCF8574_I2C_Stop();                    //Õ£÷π–≈∫≈
	return REG_data;
}					      

