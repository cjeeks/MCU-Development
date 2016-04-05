#ifndef _TP_H
#define _TP_H

#include "macro.h"


/* touch panel interface define */
#define  CMD_RDX  0xD0	 
#define  CMD_RDY  0x90

struct tp_pix_
{
	u16 x;
	u16 y;
};
/*struct tp_pixu32_
{
	u32 x;
	u32 y;
};*/
extern struct tp_pix_  tp_pixad,tp_pixlcd;	 //¦Ì¡À?¡ã¡ä£¤??¡Á?¡À¨º¦Ì?AD?¦Ì,?¡ã¡ä£¤??¡Á?¡À¨º¦Ì??????¦Ì   
extern u16 vx,vy;  //¡À¨¨¨¤y¨°¨°¡Á¨®¡ê?¡ä??¦Ì3y¨°?1000??o¨®¡À¨ª¨º??¨¤¨¦¨´??AD?¦Ì¡ä¨²¡À¨ª¨°???????¦Ì?
//extern u16 chx,chy;//??¨¨?????¦Ì?¡Á?¡À¨º?a0¨º¡À¦Ì?AD?e¨º??¦Ì
#endif

//TP_INT P1.3 T_IRQ
#define IRQ_INPUT do{P1DIR&=~BIT3;}while(0)
#define IRQ_OUTPUT do{P1DIR|=BIT3;}while(0)
#define IRQ_H do{P1DIR|=BIT3;P1OUT|=BIT3;}while(0)
#define IRQ_L do{P1DIR|=BIT3;P1OUT&=~BIT3;}while(0)
#define IRQ_STATE (P1IN&BIT3)

#if 1
  //PMISO P10.2 T_DO --to tp
  #define MISO_INPUT do{P10DIR&=~BIT2;}while(0)
  #define MISO_OUTPUT do{P10DIR|=BIT2;}while(0)
  #define MISO_H do{P10DIR|=BIT2;P10OUT|=BIT2;}while(0)
  #define MISO_L do{P10DIR|=BIT2;P10OUT&=~BIT2;}while(0)
  #define MISO_STATE (P10IN&BIT2)
  
  //PMOSI P10.1 T_DIN --from tp
  #define MOSI_INPUT do{P10DIR&=~BIT1;}while(0)
  #define MOSI_OUTPUT do{P10DIR|=BIT1;}while(0)
  #define MOSI_H do{P10DIR|=BIT1;P10OUT|=BIT1;}while(0)
  #define MOSI_L do{P10DIR|=BIT1;P10OUT&=~BIT1;}while(0)
  #define MOSI_STATE (P10IN&BIT1)

#else

  //PMISO P10.2 T_DO --to tp
  #define MOSI_INPUT do{P10DIR&=~BIT2;}while(0)
  #define MOSI_OUTPUT do{P10DIR|=BIT2;}while(0)
  #define MOSI_H do{P10DIR|=BIT2;P10OUT|=BIT2;}while(0)
  #define MOSI_L do{P10DIR|=BIT2;P10OUT&=~BIT2;}while(0)
  #define MOSI_STATE (P10IN&BIT2)
  
  //PMOSI P10.1 T_DIN --from tp
  #define MISO_INPUT do{P10DIR&=~BIT1;}while(0)
  #define MISO_OUTPUT do{P10DIR|=BIT1;}while(0)
  #define MISO_H do{P10DIR|=BIT1;P10OUT|=BIT1;}while(0)
  #define MISO_L do{P10DIR|=BIT1;P10OUT&=~BIT1;}while(0)
  #define MISO_STATE (P10IN&BIT1)

#endif
//TP_CSL P3.4 T_CS
#define CS_H do{P3DIR|=BIT4;P3OUT|=BIT4;}while(0)
#define CS_L do{P3DIR|=BIT4;P3OUT&=~BIT4;}while(0)

//PSCK P10.3 T_CLK
#define CLK_H do{P10DIR|=BIT3;P10OUT|=BIT3;}while(0)
#define CLK_L do{P10DIR|=BIT3;P10OUT&=~BIT3;}while(0)

extern void tp_spi_init();
extern uchar is_tp_press();
extern unsigned int get_tp_x();
extern unsigned int get_tp_y();
//u8 tpstate(void); //is_tp_press
//void spistar(void);  
void Touch_Adjust(void);
void point(void); //??¨ª?o¡¥¨ºy
u16 ReadFromCharFrom7843();         //SPI ?¨¢¨ºy?Y
u8 Convert_Pos(void);
