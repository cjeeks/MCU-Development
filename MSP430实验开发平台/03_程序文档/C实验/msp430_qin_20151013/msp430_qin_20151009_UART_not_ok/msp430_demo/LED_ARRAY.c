#include "msp430f5438a.h"
#include "macro.h"
#include "LED_ARRAY.h"

const unsigned char ziku_table[]={
0x7F,0xFF,0x7B,0xEF,0x7B,0xEF,0x03,0xE0,0xFF,0xFB,0xBB,0xFB,0xBB,0x83,0x00,0xBD,
0xBB,0xD6,0xBB,0xF7,0x83,0xF7,0xBB,0xF7,0xBB,0xEB,0x83,0xEB,0xBB,0xDD,0xFF,0xBE,/*"?",0*/
};


void Init_LED_array_GPIO(void)
{
 
  //LED ARRAY
  DATA_DIROUT;
  C_DIROUT;
  G_DIROUT;
  D_DIROUT;
  A_DIROUT;
  LATCH_DIROUT;
  B_DIROUT;
  CLK_DIROUT;
  
  A_HIGH;
  B_HIGH;
  C_HIGH;
  D_HIGH;
  G_HIGH;
  DATA_HIGH;
  CLK_HIGH;
  LATCH_HIGH;
}

/******************************************************************************************
*函数名称：void ABCD_port(u8 dat)
*
*入口参数：dat
*
*出口参数：无
*
*功能说明：修改ABCD的值
           选择显示哪一行//clay
*******************************************************************************************/
void LED_array_ABCD_port(uchar dat)
{
	if((dat&0x01)==0x00)
	    A_LOW;//A_ONOFF(Bit_RESET);
	else A_HIGH;//A_ONOFF(Bit_SET);
	
	if((dat&0x02)==0x00)
	    B_LOW;//B_ONOFF(Bit_RESET);
	else B_HIGH;//B_ONOFF(Bit_SET);
	
	if((dat&0x04)==0x00)
            C_LOW;//C_ONOFF(Bit_RESET);
	else C_HIGH;//C_ONOFF(Bit_SET);
	
	if((dat&0x08)==0x00)
            D_LOW;//D_ONOFF(Bit_RESET);
	else D_HIGH;//D_ONOFF(Bit_SET);
}

void LED_array_show_font(){
    uchar data_buff;
    uchar hanzi = 0;
    //	u8 han;
    uchar shift=1;
    uchar  i;
  //SHOW   
      for(shift=0;shift<16;shift++){	//一个字移位16位
      //HC595锁定输出,避免数据传输过程中，屏数据变化从而显示闪烁
         LATCH_LOW;// LAT_ONOFF(Bit_RESET);
         CLK_LOW;// CLK_ONOFF(Bit_RESET);
          //74HC595输出数据Hzk16
          data_buff = ziku_table[hanzi*32+shift*2+1];
            for(i=0;i<8;i++){
                  if((data_buff&0x80)!=0) DATA_HIGH;// DI_ONOFF(Bit_SET);//DA_in_port = 1;
                  else DATA_LOW;// DI_ONOFF(Bit_RESET);//DA_in_port = 0;
                 // DATA_HIGH;//CLAY TEST
                  CLK_HIGH;// CLK_ONOFF(Bit_SET);//CLK_port = 1;
                  CLK_LOW;//CLK_ONOFF(Bit_RESET);//CLK_port = 0;
                  data_buff <<= 1;
                  }
                  data_buff = ziku_table[hanzi*32+shift*2];
            for(i=0;i<8;i++){
                  if((data_buff&0x01)!=0) DATA_HIGH;//DI_ONOFF(Bit_SET);//DA_in_port = 1;
                  else DATA_LOW;//DI_ONOFF(Bit_RESET);//DA_in_port = 0;
                  //DATA_LOW;//CLAY TEST
                  CLK_HIGH;//CLK_ONOFF(Bit_SET);//CLK_port = 1;
                  CLK_LOW;//CLK_ONOFF(Bit_RESET);//CLK_port = 0;
                  data_buff >>= 1;
                  }
          //74HC138输出控制	 
          G_HIGH;// G_ONOFF(Bit_SET);//EN_port = 1;    //关屏显示，原理为使HC138输出全为1，从而三极管截止，点阵不显示
          LED_array_ABCD_port(shift);//ABCD_port = (ABCD_port & 0x0f)|(han<<4);  //HC138译码输出
         // ABCD_port(5);//ABCD_port = (ABCD_port & 0x0f)|(han<<4);  //HC138译码输出
          LATCH_HIGH;//LAT_ONOFF(Bit_SET);//Latch_port = 1; //允许HC595数据输出到Q1-Q8端口
          G_LOW;// G_ONOFF(Bit_RESET);//EN_port = 0;    //HC138输出有效，打开显示
          LATCH_LOW;//LAT_ONOFF(Bit_RESET);//Latch_port = 0;	//锁定HC595数据输出
      }     
}

void LED_array_hide(){
       G_HIGH;// high: ALL CLOSE
}