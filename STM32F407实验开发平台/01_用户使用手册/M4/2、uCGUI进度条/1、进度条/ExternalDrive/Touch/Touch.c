#include "stm32f4xx.h"
#include "ssd1963_lcd.h"
#include "Touch.h"
//#include "Nvic.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "Systick.h"


Pen_Holder Pen_Point;	/* 定义笔实体 */

static void Delay(uint16_t counter)
{
    unsigned int i,j;
    for(i=0;i<counter;i++)
        for(j=0;j<10000;j++);
}

//触摸IO口初始化
static void Touch_Gpio_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);
    
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

    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF , ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG , ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//    GPIO_Init(GPIOG, &GPIO_InitStructure);

    //SD_CS_DISABLE();
    NotSelect_TOUCH_CS();
    NotSelect_FLASH_CS();
    NotSelect_SD_CS();

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	/*串行时钟稳定状态是高电平*/
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;/* 时钟活跃边沿？？？*/
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; /*SPI波特率预分频*/
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; /*高位在前*/ 
	SPI_InitStructure.SPI_CRCPolynomial = 7; /*the polynomial used for the CRC calculation*/
	SPI_Init(SPI2, &SPI_InitStructure);

	/* SPI2使能 */
	SPI_Cmd(SPI2, ENABLE);     
}

///*SPIX初始化*/
//static void  TouchSPIx_Init(void)
//{  
//	SPI_InitTypeDef  SPI_InitStructure;
//	
//	NotSelect_TOUCH_CS();
//	
//	/* SPI1 configuration */
//	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
//	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
//	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;//	 SPI_BaudRatePrescaler_32
//	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_InitStructure.SPI_CRCPolynomial = 7;
//	SPI_Init(TOUCH_SPI, &SPI_InitStructure);
//	
//	/* Enable SPI1  */
//	SPI_Cmd(TOUCH_SPI, ENABLE);
//}
//触摸中断实始化
static void TOUCH_EXTI_Configuration(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); //使能IO时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;          //模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;          //设置上接
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;             //IO口为0
  GPIO_Init(GPIOG, &GPIO_InitStructure);                //如上配置gpio

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource8);//实始化中断线0

  EXTI_InitStructure.EXTI_Line = EXTI_Line8;                   //配置中断线为中断线0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;          //配置中断模式
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;      //配置为下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                    //配置中断线使能
  EXTI_Init(&EXTI_InitStructure);                              

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;             
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  EXTI_GenerateSWInterrupt(EXTI_Line8);   //用软中断 试一下配置
}

/*SPI读写一字节*/
uchar SPI_SendByte(unsigned char byte)
{
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(TOUCH_SPI, SPI_I2S_FLAG_TXE) == RESET);
	
	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(TOUCH_SPI, byte);
	
	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(TOUCH_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(TOUCH_SPI);
}

//2次读取ADS7846,连续读取2次有效的AD值,且这两次的偏差不能超过
//50,满足条件,则认为读数正确,否则读数错误.	   
//该函数能大大提高准确度
#define ERR_RANGE 50 //误差范围 
u8 Read_ADS2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
} 
/*****************************************************************************
** 函数名称: Pen_Int_Set
** 功能描述: PEN中断设置
				EN=1：开启中断
					EN=0: 关闭中断
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/	 
void Pen_Int_Set(u8 en)
{
	if(en)EXTI->IMR|=1<<8;   //开启line13上的中断	  	
	else EXTI->IMR&=~(1<<8); //关闭line13上的中断	   
}
//读取一次坐标值	
//仅仅读取一次,知道PEN松开才返回!					   
u8 Read_TP_Once(void)
{
//	u8 t=0;	    
	Pen_Int_Set(0);//关闭中断


	Pen_Point.Key_Sta=Key_Up;

    Delay(2);

	if(Read_ADS2(&Pen_Point.X,&Pen_Point.Y))
	{
	    Delay(500);
		Pen_Int_Set(1);//开启中断
	    return 1;
	}
	else
	{ 
		Pen_Int_Set(1);//开启中断
	    return 0;
	}


//	while(t<=150)	 // PEN==0&&t<=250
//	{
//		t++;
//		Delay(1);
//	};
//	Pen_Int_Set(1);//开启中断		 
//	if(t>=50)		//250
//	    return 0;//按下2.5s 认为无效
//	else 
//    	return 1;


//	if(Read_ADS2(&Pen_Point.X,&Pen_Point.Y) == 1)
//	    return 1;
//	else
//	    return 0;	
}
//////////////////////////////////////////////////
//与LCD部分有关的函数  
//画一个触摸点
//用来校准用的
void Drow_Touch_Point(u8 x,u16 y)
{
	Draw_Circle(x,y,6,Red);//画中心圈
}
//触摸屏校准代码
//得到四个校准参数
void Touch_Adjust(void)
{								 
	u16 pos_temp[4][2];//坐标缓存值
	u8  cnt=0;	
	u16 d1,d2;
	u32 tem1,tem2;
	double fac; 	   
	cnt=0;				 
	lcd_clear(White);//清屏 
	Drow_Touch_Point(20,20);//画点1 
	Pen_Point.Key_Sta=Key_Up;//消除触发信号 
	Pen_Point.xfac=0;//xfac用来标记是否校准过,所以校准之前必须清掉!以免错误	 
	while(1)
	{
		if(Pen_Point.Key_Sta==Key_Down)//按键按下了
		{
			if(Read_TP_Once())//得到单次按键值
			{  								   
				pos_temp[cnt][0]=Pen_Point.X;
				pos_temp[cnt][1]=Pen_Point.Y;

                printf(" \r %d ",Pen_Point.X);
                printf(" %d \n",Pen_Point.Y);

				cnt++;
			}			 
			switch(cnt)
			{			   
				case 1:
					lcd_clear(White);//清屏 
					Drow_Touch_Point(220,20);//画点2
					break;
				case 2:
					lcd_clear(White);//清屏 
					Drow_Touch_Point(20,300);//画点3
					break;
				case 3:
					lcd_clear(White);//清屏 
					Drow_Touch_Point(220,300);//画点4
					break;
				case 4:	 //全部四个点已经得到
	    		    	//对边相等
					tem1=abs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
					tem2=abs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1,2的距离
					
					tem1=abs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
					tem2=abs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到3,4的距离
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05||d1==0||d2==0)//不合格
					{
						cnt=0;
						lcd_clear(White);//清屏 
						Drow_Touch_Point(20,20);
						continue;
					}
					tem1=abs(pos_temp[0][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[0][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1,3的距离
					
					tem1=abs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到2,4的距离
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//不合格
					{
						cnt=0;
						lcd_clear(White);//清屏 
						Drow_Touch_Point(20,20);
						continue;
					}//正确了
								   
					//对角线相等
					tem1=abs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//得到1,4的距离
	
					tem1=abs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//得到2,3的距离
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//不合格
					{
						cnt=0;
						lcd_clear(White);//清屏 
						Drow_Touch_Point(20,20);
						continue;
					}//正确了
					//计算结果
					Pen_Point.xfac=(float)200/(pos_temp[1][0]-pos_temp[0][0]);//得到xfac		 
					Pen_Point.xoff=(240-Pen_Point.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;//得到xoff
						  
					Pen_Point.yfac=(float)280/(pos_temp[2][1]-pos_temp[0][1]);//得到yfac
					Pen_Point.yoff=(320-Pen_Point.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//得到yoff  
//					POINT_COLOR=BLUE;
					lcd_clear(White);//清屏
                    LCD_ShowString(60, 18, "Touch Screen Adjust OK!", Red, Black); //校正完成
					Delay(20);
					lcd_clear(Magenta);//清屏   
					return;//校正完成				 
			}
		}
	} 
}
//触摸屏初始化
void Touch_Init(void)
{
    Touch_Gpio_Init();
	//TouchSPIx_Init();
//	NVIC_Configuration();
	//TOUCH_EXTI_Configuration();

	//Touch_Adjust();
}
/*****************************************************************************
** 函数名称: void Touch_IRQ(void)
** 功能描述: 触摸中断函数
** 作  　者: 
** 日　  期: 
*****************************************************************************/
void Touch_IRQ(void)
{
	//u16 i;
  	if(EXTI_GetITStatus(TOUCH_IRQ_GPIO_Pin) != RESET)
	{
		//if(Read_TP_Once() == 1)
		Pen_Point.Key_Sta=Key_Down;//按键按下 
	
        EXTI_ClearITPendingBit(TOUCH_IRQ_LINE);			 		  				 
	}
}






//SPI读数据 
//从7846/7843/XPT2046/UH7843/UH7846读取adc值	   
u16 ADS_Read_AD(u8 CMD)	  
{ 	 
//	u8 i;	  
	u16 Num,Date; 

    NotSelect_SD_CS(); 
    NotSelect_FLASH_CS();
	Select_TOUCH_CS();

    SPI_SendByte(CMD); 
	//for(i=100;i>0;i--); 
	Num=0;
	Date=0;
	Num = SPI_SendByte(0x00);
	Date = Num << 8;
	Num = SPI_SendByte(0x00);

	Date |= Num; 

    Date >>=4;
    Date &=0XFFF;

	NotSelect_TOUCH_CS();
	return(Date); 
}

//读取一个坐标值
//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值 
#define READ_TIMES 20 //读取次数
#define LOST_VAL 1	  //丢弃值
u16 ADS_Read_XY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)
	{				 
		buf[i]=ADS_Read_AD(xy);	    
	}				    
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 

//带滤波的坐标读取
//最小值不能少于100.
u8 Read_ADS(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);
//	xtemp=ADS_Read_AD(CMD_RDX);
//	ytemp=ADS_Read_AD(CMD_RDY);
	  												   
	if(xtemp<10||ytemp<10)return 0;//读数失败
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}

//转换结果
//根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
void Convert_Pos(void)
{		 	  
	if(Read_ADS2(&Pen_Point.X,&Pen_Point.Y))
	{
		Pen_Point.X0=Pen_Point.xfac*Pen_Point.X+Pen_Point.xoff;
		Pen_Point.Y0=Pen_Point.yfac*Pen_Point.Y+Pen_Point.yoff;  
	}
}

/*****************************************************************************
** 函数名称: Refreshes_Screen
** 功能描述: 刷新屏幕				
** 作  　者: Dream
** 日　  期: 2010年12月06日
*****************************************************************************/
void Refreshes_Screen(void)
{
	lcd_clear(White);//清屏  
	LCD_ShowString(216,0,"RST",Red,Black);
//  	POINT_COLOR=BLUE;//设置画笔蓝色 
}

//画一个大点
//2*2的点			   
void Draw_Big_Point(u8 x,u16 y)
{	    
	LCD_DrawPoint(x,y,Red);//中心点 
	LCD_DrawPoint(x+1,y,Red);
	LCD_DrawPoint(x,y+1,Red);
	LCD_DrawPoint(x+1,y+1,Red);	 	  	
}
