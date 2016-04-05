#include "stm32f4xx.h"
#include "MMA7455.h"
#include  <math.h>    //Keil library
#include "lcd.h"
#include "BMP085.h"

//    MMA7455
uchar table4[10]="0123456789";

uchar xposivalue;			//x正方向满格显示g值
uchar xnegavalue;			//x反方向满格显示g值
uchar yposivalue;			//y正方向满格显示g值
uchar ynegavalue;			//y反方向满格显示g值

void MMA7455_delay50us(void)
{
		
   int i=500;  
   while(i) 
   { 
     i--; 
   }  
}

//******************************************************************************************************
//初始化MMA7455
//******************************************************************************************************
void MMA7455_data_init(void)
{
	xposivalue=50;
	xnegavalue=50;
	yposivalue=50;
	ynegavalue=50;
}

uint8_t MMA7455_self_test7455(void)					 //函数功能：检测7455有没有插好
{										 											 //          如果没有插好，1602将会显示
	uchar j;							 								   //			 “No acceleration!"
	char t, status, name;

	MMA7455_delay50us();
  Single_WriteI2C(IIC_WRITE, 0x16,0x15);	
	status = Single_ReadI2C(IIC_READ, 0x09);
	name = Single_ReadI2C(IIC_READ, 0x0f); //whoami
	MMA7455_delay50us();
	t = Single_ReadI2C(IIC_READ, 0x16);

	Single_WriteI2C(IIC_WRITE, 0x10,0x15);
	Single_WriteI2C(IIC_WRITE, 0x12,0x25);	
	Single_WriteI2C(IIC_WRITE, 0x14,0x10);	
	
	if(t!=0x15)
	{
		printf("No acceleration!");
		return 0;
	}
	else
	{
		//printf("X= 0.00,Y= 0.00, Z= 0.00,t=%c\n",t);
		return 1;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
void MMA7455_sendxyz(void)				
{
	u16 x1,x2,x3,xsign;
	uchar x_data[4], status;
	u16 x,y,z;
	u8 X_Angle[] = {"X:000"}, Y_Angle[] = {"Y:000"}, Z_Angle[] = {"Z:000"}; 

	x =Single_ReadI2C(IIC_READ, 0x06);
	y =Single_ReadI2C(IIC_READ, 0x07);
	z =Single_ReadI2C(IIC_READ, 0x08);

	X_Angle[2]=(x/63)+'0';
	X_Angle[3]=((x*100/63)%100)/10+'0';
	X_Angle[4]=(x*100/63)%10+'0';		
	printf("X_angle %c%c%c ", X_Angle[2], X_Angle[3], X_Angle[4]);	
	LCD_ShowString(150, 160,X_Angle, White, Black);		

	Y_Angle[2]=(y/63)+'0';
	Y_Angle[3]=((y*100/63)%100)/10+'0';
	Y_Angle[4]=(y*100/63)%10+'0';		
	printf("Y_angle %c%c%c ", Y_Angle[2], Y_Angle[3], Y_Angle[4]);
	LCD_ShowString(200, 160,Y_Angle, White, Black);	
	
	Z_Angle[2] = (z/63)+'0';
	Z_Angle[3] = ((z*100/63)%100)/10+'0';
	Z_Angle[4] =( z*100/63)%10+'0';			
	printf("Z_angle %c%c%c\n", Z_Angle[2], Z_Angle[2], Z_Angle[2]);
	LCD_ShowString(250, 160,Z_Angle, White, Black);	
}

