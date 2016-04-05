#include "msp430f5438a.h"
#include "macro.h"
#include "TP.h"

u16 vx_tp=7724,vy_tp=12970;  
u16 chx_tp=3872,chy_tp=3763;

struct tp_pix_  tp_pixad,tp_pixlcd;	

#define SPI_DELAY() delay(1)

void tp_spi_init()
{
  IRQ_H;
  MISO_H;
  MOSI_H;
  CS_H;
  CLK_H;
  IRQ_INPUT;
  MISO_INPUT;//DIN_INPUT

}

uchar is_tp_press()
{
  if(IRQ_STATE == 0)
    return 1;
  else
    return 0;
}

uint get_tp_x()
 {
   return 0;
 }

 uint get_tp_y()
 {
   return 0;
 }

//**********************************************************
void WriteCharTo7843(unsigned char num)          //SPID write
{
  unsigned char count=0;
  CLK_L;//DCLK=0;
  for(count=0;count<8;count++)
  {
    //num<<=1;
   //DIN=CY;
   //DCLK=0; _nop_();_nop_();_nop_();                //rising egde
    //DCLK=1; _nop_();_nop_();_nop_();
    if(num & 0x80)
      MOSI_H;//DIN_H;
    else
      MOSI_L;//DIN_L;
    num<<=1;
    CLK_L;
    SPI_DELAY();
    CLK_H;
    SPI_DELAY();
  }
}
//**********************************************************
u16 ReadFromCharFrom7843()             //SPI read
{
	u8 count=0;
	u16 Num=0;
	for(count=0;count<12;count++)
	{
		Num<<=1;		
		CLK_H;//DCLK=1; _nop_();_nop_();_nop_();                //falling egde
                SPI_DELAY();
		CLK_L;//DCLK=0; _nop_();_nop_();_nop_();
                SPI_DELAY();
		if(MISO_STATE)//DIN_STATE DOUT
		{
			Num|=1;
		}
		
	}

return(Num);
}	
//read adc value 
u16 ADS_Read_AD(unsigned char CMD)          
{
  u16 l;
  CS_L;//CS=0;
  WriteCharTo7843(CMD);        
  CLK_H;//DCLK=1; _nop_();_nop_();_nop_();_nop_();
  SPI_DELAY();
  CLK_L;//DCLK=0; _nop_();_nop_();_nop_();_nop_();
  SPI_DELAY();
  l=ReadFromCharFrom7843();
  CS_H;//CS=1;
  return l;
}		   
//read one position READ_TIMES ,and sort it , discard max & min ,dan do average
#define READ_TIMES 15 //
#define LOST_VAL 5	  //
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
	for(i=0;i<READ_TIMES-1; i++)//sort
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//up sequence
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
//read with flitration
//min must > 100.
u8 Read_ADS(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);	 									   
	if(xtemp<100||ytemp<100)return 0;//fail
	*x=xtemp;
	*y=ytemp;
	return 1;//success
}
//read two AD value, deviation must < 50
#define ERR_RANGE 20 //deviation
u8 Read_ADS2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);	
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)>>1;
        *y=(y1+y2)>>1;		
        return 1;
    }else return 0;	  
} 
//read position for calibration   
u8 Read_TP_Once(void)
{
	u8 re=0;
	u16 x1,y1;
	while(re==0)
	{
		while(!Read_ADS2(&tp_pixad.x,&tp_pixad.y));
		delay_ms(10);//delayms(10);
		while(!Read_ADS2(&x1,&y1));
		if(tp_pixad.x==x1&&tp_pixad.y==y1)
		{
			re=1; 
		}
	} 
	return re;
}

u8 Convert_Pos(void)
{		 	 
	u8 l=0; 
	if(Read_ADS2(&tp_pixad.x,&tp_pixad.y))
	{
		l=1;
		tp_pixlcd.x=tp_pixad.x>chx_tp?((u32)tp_pixad.x-(u32)chx_tp)*1000/vx_tp:((u32)chx_tp-(u32)tp_pixad.x)*1000/vx_tp;
		tp_pixlcd.y=tp_pixad.y>chy_tp?((u32)tp_pixad.y-(u32)chy_tp)*1000/vy_tp:((u32)chy_tp-(u32)tp_pixad.y)*1000/vy_tp;
	}
	return l;
}	   
#if 0
#if 0
void Drow_Touch_Point(u16 x,u16 y)
{
	LCD_DrawLine(x-12,y,x+13,y);//o¨¢??
	LCD_DrawLine(x,y-12,x,y+13);//¨º¨²??
	LCD_DrawPoint(x+1,y+1);
	LCD_DrawPoint(x-1,y+1);
	LCD_DrawPoint(x+1,y-1);
	LCD_DrawPoint(x-1,y-1);
//	Draw_Circle(x,y,6);//?-?DD?¨¨|
}	  
#endif
//caculater
#define tp_pianyi 50   //calibration offset
#define tp_xiaozhun 1000   //calibration acccuracy
void Touch_Adjust(void)
{	
	float vx_tp1,vx_tp2,vy_tp1,vy_tp2;  //¡À¨¨¨¤y¨°¨°¡Á¨®¡ê?¡ä??¦Ì3y¨°?1000??o¨®¡À¨ª¨º??¨¤¨¦¨´??AD?¦Ì¡ä¨²¡À¨ª¨°???????¦Ì?
	u16 chx_tp1,chx_tp2,chy_tp1,chy_tp2;//??¨¨?????¦Ì?¡Á?¡À¨º?a0¨º¡À¦Ì?AD?e¨º??¦Ì
	u16 lx,ly;				 
	struct tp_pixu32_ p[4];
	u8  cnt=0;	 
	cnt=0;				
	POINT_COLOR=BLUE;
	BACK_COLOR =WHITE;
	LCD_Clear(WHITE);//???¨¢   
	POINT_COLOR=RED;//o¨¬¨¦? 
	LCD_Clear(WHITE);//???¨¢ 
	Drow_Touch_Point(tp_pianyi,tp_pianyi);//?-¦Ì?1 
	while(1)
	{
		if(Penirq==0)//¡ã¡ä?¨¹¡ã¡ä??¨¢?
		{
			if(Read_TP_Once())//¦Ì?¦Ì?¦Ì£¤¡ä?¡ã¡ä?¨¹?¦Ì
			{  								   
				p[cnt].x=tp_pixad.x;
				p[cnt].y=tp_pixad.y;
				cnt++; 
			}			 
			switch(cnt)
			{			   
				case 1:
					LCD_Clear(WHITE);//???¨¢ 
					while(!Penirq)  //¦Ì¨¨¡äy?¨¦¨º?
					{
					}
					Drow_Touch_Point(LCD_W-tp_pianyi-1,tp_pianyi);//?-¦Ì?2
					break;
				case 2:
					LCD_Clear(WHITE);//???¨¢ 
					while(!Penirq)  //¦Ì¨¨¡äy?¨¦¨º?
					{
					}
					Drow_Touch_Point(tp_pianyi,LCD_H-tp_pianyi-1);//?-¦Ì?3
					break;
				case 3:
					LCD_Clear(WHITE);//???¨¢ 
					while(!Penirq)  //¦Ì¨¨¡äy?¨¦¨º?
					{
					}
					Drow_Touch_Point(LCD_W-tp_pianyi-1,LCD_H-tp_pianyi-1);//?-¦Ì?4
					break;
				case 4:	 //¨¨?2?????¦Ì?¨°??-¦Ì?¦Ì?
	    		   	LCD_Clear(WHITE);//???¨¢ 
				   	while(!Penirq)  //¦Ì¨¨¡äy?¨¦¨º?
					{
					}
			   		vx_tp1=p[1].x>p[0].x?(p[1].x-p[0].x+1)*1000/(LCD_W-tp_pianyi-tp_pianyi):(p[0].x-p[1].x-1)*1000/(LCD_W-tp_pianyi-tp_pianyi);
				 	chx_tp1=p[1].x>p[0].x?p[0].x-(vx_tp1*tp_pianyi)/1000:p[0].x+(vx_tp1*tp_pianyi)/1000;
				   	vy_tp1=p[2].y>p[0].y?(p[2].y-p[0].y-1)*1000/(LCD_H-tp_pianyi-tp_pianyi):(p[0].y-p[2].y-1)*1000/(LCD_H-tp_pianyi-tp_pianyi);
					chy_tp1=p[2].y>p[0].y?p[0].y-(vy_tp1*tp_pianyi)/1000:p[0].y+(vy_tp1*tp_pianyi)/1000; 
					
					vx_tp2=p[3].x>p[2].x?(p[3].x-p[2].x+1)*1000/(LCD_W-tp_pianyi-tp_pianyi):(p[2].x-p[3].x-1)*1000/(LCD_W-tp_pianyi-tp_pianyi);
					chx_tp2=p[3].x>p[2].x?p[2].x-(vx_tp2*tp_pianyi)/1000:p[2].x+(vx_tp2*tp_pianyi)/1000;
				   	vy_tp2=p[3].y>p[1].y?(p[3].y-p[1].y-1)*1000/(LCD_H-tp_pianyi-tp_pianyi):(p[1].y-p[3].y-1)*1000/(LCD_H-tp_pianyi-tp_pianyi);
					chy_tp2=p[3].y>p[1].y?p[1].y-(vy_tp2*tp_pianyi)/1000:p[1].y+(vy_tp2*tp_pianyi)/1000; 


					if((vx_tp1>vx_tp2&&vx_tp1>vx_tp2+tp_xiaozhun)||(vx_tp1<vx_tp2&&vx_tp1<vx_tp2-tp_xiaozhun)||(vy_tp1>vy_tp2&&vy_tp1>vy_tp2+tp_xiaozhun)||(vy_tp1<vy_tp2&&vy_tp1<vy_tp2-tp_xiaozhun))
					{
						cnt=0;
						LCD_Clear(WHITE);//???¨¢ 
						Drow_Touch_Point(tp_pianyi,tp_pianyi);//?-¦Ì?1 
						continue;
					}
					vx_tp=(vx_tp1+vx_tp2)/2;vy_tp=(vy_tp1+vy_tp2)/2;
					chx_tp=(chx_tp1+chx_tp2)/2;chy_tp=(chy_tp1+chy_tp2)/2;	
																
					//??¨º?D¡ê¡Á?D??¡é
					LCD_Clear(WHITE);//???¨¢ 
					POINT_COLOR=BLACK;
					BACK_COLOR=BLUE;	
			
					lx=0;ly=50;			
					LCD_ShowString(lx,ly,"vx_tp1:");lx+=40;LCD_ShowNum(lx,ly,vx_tp1,4);					
					lx=0;ly+=20;
					LCD_ShowString(lx,ly,"vy_tp1:");lx+=40;LCD_ShowNum(lx,ly,vy_tp1,4);					
					lx=0;ly+=20; 
					LCD_ShowString(lx,ly,"chx_tp1:");lx+=40;LCD_ShowNum(lx,ly,chx_tp1,4);					
				    lx=0;ly+=20; 
					LCD_ShowString(lx,ly,"chy_tp1:");lx+=40;LCD_ShowNum(lx,ly,chy_tp1,4);

					lx=100;ly=50;			
					LCD_ShowString(lx,ly,"vx_tp2:");lx+=40;LCD_ShowNum(lx,ly,vx_tp2,4);					
					lx=100;ly+=20;
					LCD_ShowString(lx,ly,"vy_tp2:");lx+=40;LCD_ShowNum(lx,ly,vy_tp2,4);					
					lx=100;ly+=20; 
					LCD_ShowString(lx,ly,"chx_tp2:");lx+=40;LCD_ShowNum(lx,ly,chx_tp2,4);					
				    lx=100;ly+=20; 
					LCD_ShowString(lx,ly,"chy_tp2:");lx+=40;LCD_ShowNum(lx,ly,chy_tp2,4);
				
					lx=50;ly=150;			
					LCD_ShowString(lx,ly,"vx_tp:");lx+=40;LCD_ShowNum(lx,ly,vx_tp,4);					
					lx=50;ly+=20;
					LCD_ShowString(lx,ly,"vy_tp:");lx+=40;LCD_ShowNum(lx,ly,vy_tp,4);					
					lx=50;ly+=20; 
					LCD_ShowString(lx,ly,"chx_tp:");lx+=40;LCD_ShowNum(lx,ly,chx_tp,4);					
				    lx=50;ly+=20; 
					LCD_ShowString(lx,ly,"chy_tp:");lx+=40;LCD_ShowNum(lx,ly,chy_tp,4);

					lx=30;ly+=30;
					LCD_ShowString(lx,ly,"Adjust OK!  Touch Anywhere To Continue");										  
					Read_TP_Once(); //¦Ì¨¨¡äy¨¨?¨°a?¨¹o¨®?¨¬D?

					LCD_Clear(WHITE);//???¨¢
					return;//D¡ê?y¨ª¨º3¨¦				 
			}
		}
	} 
}
#endif	    	