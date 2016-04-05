#include "msp430f5438a.h"
#include "macro.h"
#include "dth11.h"
//#include "gpio.h"
#include "RS232.h"
#include <stdlib.h>


//typedef unsigned char  u8;       //defined for unsigned 8-bits integer variable 	  无符号8位整型变量  
//typedef unsigned int   U16;      // defined for unsigned 16-bits integer variable 	  无符号16位整型变量 
unsigned char  u8FLAG,k;
unsigned char  u8count,u8temp;
unsigned char  u8T_data_H=1,u8T_data_L=2,u8RH_data_H=3,u8RH_data_L=4,u8checkdata=5;
unsigned char  u8T_data_H_temp,u8T_data_L_temp,u8RH_data_H_temp,u8RH_data_L_temp,u8checkdata_temp;
unsigned char  u8comdata;
//unsigned char  outdata[5];  //定义发送的字节数	   
unsigned char  indata[5];
unsigned char  count, count_r=0;
/*unsigned*/ char  str[20]={"RS232"};
unsigned char  U16temp1,U16temp2;
uchar tdata[4]={0x00,0x00,0x00,0x00};
uchar sbuf;
////////////////////////////////////////////////////////////
void DTH11_OUT() //配置TM1638DIO引脚为推挽输出
{
  DTH11_DIROUT;
  /*
   GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
   GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz;
   GPIO_Init(GPIOF, &GPIO_InitStructure);
  */
}
////////////////////////////////////////////////////////////

void DTH11_IN()  //配置TM1638DIO引脚为上拉输入
{
  DTH11_DIRIN;
  DTH11_PULLUP;
  //DTH11_PULL_DOWN;
}

////////////////////////////////////////////////////////////
/*  void DTH11_Delay(U16 j)
    {     
			u8 i;
	    for(;j>0;j--)
	  { 	
		//for(i=0;i<27;i++);
			for(i=0;i<250;i++);

	  }
    } 
*/
////////////////////////////////////////////////////////////
	/*	
void  Delay_10us(void)
      {
        unsigned char i;
        i--;
        i--;
        i--;
        i--;
        i--;
        i--;
       }
*/
////////////////////////////////////////////////////////////
void  DTH11_COM(void)
{    
  unsigned char i;
  /*		u8comdata=0;
  for(i=8;i>0;i--)	   
        {
                            u8comdata<<=1;
                            count=0;
                            DTH11_IN();	
                      while((GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)==0)&&count++<20);
                            if(count>=20) return ;
                      DTH11_Delay(4);
                            if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)!=0)
                            {
                                    u8comdata++;
                                    while((GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)!=0)&&count++<20)
                                    {
                                            DTH11_OUT();	
                                            GPIO_SetBits(GPIOF,GPIO_Pin_6);
                                    }
                                    if(count>=20)
                                    {
                                            return ;
                                    }
                            
                            }
                            
                    }*/
  u8comdata=0;
  for(i=0;i<8;i++)	   
        {            
              u8FLAG=2;
             // DTH11_IN();	
              //while((!GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6))&&u8FLAG++);
            //while((!P2_0)&&u8FLAG++);
            while((!IS_DTH11_HIGH) &&u8FLAG++);//        while(!GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6));
            delay_us(40);//        DTH11_Delay(4);
            u8temp=0;
            if(IS_DTH11_HIGH)u8temp=1;// if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6))u8temp=1;
        // if(P2_0)u8temp=1;
                u8FLAG=2;
                            //while((GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6))&&u8FLAG++);
            delay_us(2);//clay
              while(IS_DTH11_HIGH &&u8FLAG++)  delay_us(2);//      while(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6));
            // while((P2_0)&&u8FLAG++);
            //超时则跳出for循环		
               //LCD_ShowString(140,100, "  get .... ");	
       	// if(u8FLAG==1)break;
                if(u8FLAG > 200)break;
          //LCD_ShowString(140,100, "  get  not time out.. ");	
            //判断数据位是0还是1	 
               
            // 如果高电平高过预定0高电平值则数据位为 1 
             
               u8comdata<<=1;
               u8comdata|=u8temp;        //0
         }//rof
       //u8comdata=9;
 
}
////////////////////////////////////////////////////////////
/*
First time must 1s after power on
between two read time must longer than 100ms
*/
void DTH11_RH(void)
{
  //主机拉低18ms 
  DTH11_OUT();
  DTH11_LOW;// GPIO_ResetBits(GPIOF,GPIO_Pin_6);
  delay_ms(20);//DTH11_Delay(2600);
  DTH11_HIGH;//GPIO_SetBits(GPIOF,GPIO_Pin_6);

  //总线由上拉电阻拉高 主机延时20us
  delay_us(40);//      DTH11_Delay(3);
  //主机设为输入 判断从机响应信号 
   DTH11_HIGH;// DTH11_DIRIN;//      GPIO_SetBits(GPIOF,GPIO_Pin_6);
  //判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	
  DTH11_IN();
  delay_us(1);//CLAY ADD test 10->1
  if(IS_DTH11_LOW)//if(!GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)) 
    {
//      LCD_ShowString(150, 40, "--low--");	
       u8FLAG=2;
     //判断从机是否发出 80us 的低电平响应信号是否结束	 
       //              while((!GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6))&&u8FLAG++);
       //while((!P2_0)&&u8FLAG++);
       while((IS_DTH11_HIGH)&&u8FLAG++);
//       LCD_ShowString(150, 40, "--low--222");	
       u8FLAG=2;
     //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态

     // while((GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6))&&u8FLAG++);		
      //while((P2_0)&&u8FLAG++);
       while((IS_DTH11_HIGH)&&u8FLAG++);
//       LCD_ShowString(150, 40, "--low--333");	
     //数据接收状态		 
       DTH11_COM();
       u8RH_data_H_temp=u8comdata;
       DTH11_COM();
       u8RH_data_L_temp=u8comdata;
       DTH11_COM();
       u8T_data_H_temp=u8comdata;
       DTH11_COM();
       u8T_data_L_temp=u8comdata;
       DTH11_COM();
       u8checkdata_temp=u8comdata;
       DTH11_OUT();
      DTH11_HIGH;// GPIO_SetBits(GPIOF,GPIO_Pin_6);
      // P2_0=1;
     //数据校验 
//      LCD_ShowString(150, 40, "--low--444444444");	
       u8temp=(u8T_data_H_temp+u8T_data_L_temp+u8RH_data_H_temp+u8RH_data_L_temp);
       if(u8temp==u8checkdata_temp)
          {
              u8RH_data_H=u8RH_data_H_temp;
              u8RH_data_L=u8RH_data_L_temp;
              u8T_data_H=u8T_data_H_temp;
              u8T_data_L=u8T_data_L_temp;
              u8checkdata=u8checkdata_temp;
          }//fi
       }//fi
//       LCD_ShowString(150, 40, "--low--5555");	
}

	
void Send_DTH11(void)
{

  DTH11_RH();
  
 /*
            str[0]=u8RH_data_H;
	   str[1]=u8RH_data_L;
	   str[2]=u8T_data_H;
	   str[3]=u8T_data_L;
	   str[4]=u8checkdata;

	//	printf("Temperature=%d%d%d%d%d",str[0],str[1],str[2],str[3],str[4]);
	//	LCD_ShowString(150, 100, "温度值为：", Red, Black);
	//	LCD_ShowString(150, 100, "温度值为：", Red, Black);

		printf("humi_value =%d %%RH \r\n",str[0]);
		printf("temp_value =%d C \r\n",str[2]);
     */           

  }
/*void conversion(long temp_data)  
{     
    shiwan=temp_data/100000+0x30 ;
    temp_data=temp_data%100000;   //取余运算 
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 	
}*/

