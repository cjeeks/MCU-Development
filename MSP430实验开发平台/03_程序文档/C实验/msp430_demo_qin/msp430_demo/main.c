#include "msp430f5438a.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RS232.h"
#include "macro.h"
//#include "GPIO.h"
#include "dth11.h"
#include "LED_ARRAY.h"
#include "LCD.h"
#include "Relay.h"
#include "DDPLAY.h"
#include "DCMoto.h"
#include "SteperMoto.h"
#include "tm1638.h"
#include "gas.h"
#include "body.h"
#include "adc.h"
#include "bmp085.h"
#include "TP.h"
extern int net_main(void);

#define  FLL_FACTOR     549                                          // FLL_FACTOR: DCO倍频系数    
void Init_CLK(void)
{
#if  EXT_CLK_32768
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  P7SEL     |= 0x03                                       ; // 端口选择外部低频晶振XT1
  UCSCTL6   &=~XT1OFF                                     ; // 使能外部晶振 
  UCSCTL6   |= XCAP_3                                     ; // 设置内部负载电容
  UCSCTL3   |= SELREF_2                                   ; // DCOref = REFO
  UCSCTL4   |= SELA_0                                     ; // ACLK   = XT1  
  __bis_SR_register(SCG0)                                 ; // 关闭FLL控制回路
  UCSCTL0    = 0x0000                                     ; // 设置DCOx, MODx
  UCSCTL1    = DCORSEL_7                                  ; // 设置DCO振荡范围
  UCSCTL2    = FLLD__1 + FLL_FACTOR                       ; // Fdco = ( FLL_FACTOR + 1)×FLLRef = (649 + 1) * 32768 = 21.2992MHz 4Mhz
  __bic_SR_register(SCG0)                                 ; // 打开FLL控制回路                                                            
  __delay_cycles(1024000)                                 ; 
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 错误标志                                                            
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // 检测振荡器错误标志 

#else
  
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  P5SEL     |= 0x0C                                       ; // 端口功能选择振荡器
  UCSCTL6   &= ~XT2OFF                                    ; // 振荡器使能
  UCSCTL3   |= SELREF_2                                   ; // FLLref = REFO
  UCSCTL4   |= SELA__REFOCLK                                     ; // ACLK=REFO,SMCLK=DCO,MCLK=DCO
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 错误标志                                                          
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG)                                   ; // 检测振荡器错误标志
  UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 驱动模式 24~32MHz     -----------????
  UCSCTL4  = UCSCTL4-SELA__REFOCLK                     ;
  UCSCTL4   |= SELS_5 + SELM_5  + SELA__XT2CLK         ; // ACLK = SMCLK = MCLK = XT2
#endif
}



void main()
{
  uint count =0;
  //char value ;

  __disable_interrupt();
  Init_CLK();//初始化系统时钟
  Init_USB();
  Init_RS232_1();
  Init_RS232_2();
  RS232_1_TX("\r\r");
  RS232_1_TX("this is RS232_1");
  RS232_2_TX("this is RS232_2");
  USB_TX("this is USB uart\n\r");
  __enable_interrupt();
  
  Init_LED_array_GPIO();//初始化按键，LED
  LCD_Init(); 
  init_keypad();
  

 /*StepperMoto_IO_init();
  while(1){
 StepperMoto_run_clockwise();
  }*/
  
  //save power 
  MOTO_3L_OUT_L;
  MOTO_2L_OUT_L;
  MOTO_1L_OUT_L;
  MOTO_0L_OUT_L;
 
  // motor test 
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
  LCD_ShowString(140,100, " First : Beep & Relay test ");	//item
  LCD_ShowString(100, 160, " You will hear sound of switch & beep "); 	//value 
//  LCD_ShowString(100, 200, " You will hear sound of switch & beep "); 	//value
  //  LCD_Fill(150, 100, LCD_W-5-150, 16 +100 ,BLACK ); //clear area
  Init_GPIO();//small board key led
  Relay_test();
  delay_ms(500);//delay_s(1);
  

  // motor test 
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
  LCD_ShowString(150,100, " Second : DC Moto test ");	//item
  LCD_ShowString(100, 160, " You will see  DC Moto Runing "); 	//value 
  Dc_Moto_test();
   
    // Steer & Stepper moto test 
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
  LCD_ShowString(150,100, " Third : Stepper Moto test ");	//item
//  LCD_ShowString(100, 160, " You will see  Steer Moto  Runing "); 	//value 
  LCD_ShowString(100, 200, " and then  Stepper Motor Runing  "); 	//value
  StepperMoto_IO_init();
  StepperMoto_run_clockwise();
   
  // LED & KEY pad
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
  LCD_ShowString(150,100, " Fourth : LED key pad test");	//item
  LCD_ShowString(100, 160, " You will see LED num show , led light "); 	//value 
  LCD_ShowString(100, 200, " and then  press all key and see led  "); 	//value
  TM1638Test();
 
  // gas & BODY pad
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
  LCD_ShowString(150,100, " Fifth : GAS and body test");	//item
  LCD_ShowString(100, 160, " if test  press key 5 to jump next chapter  "); 	//value 
//  LCD_ShowString(100, 200, " and then  press all key and see led  "); 	//value  
  gas_init();
  BODY_init();
  init_keypad();
  count =  0;
  while(1){
    if(is_gas_alarm()){
      LCD_ShowString(140,100, "  gas low ");
    }else{
      LCD_ShowString(140,100, " gas  high ");
    }
    if(is_BODY_alarm()){
       LCD_ShowString(140,140, "  body high ");
    }else{
      LCD_ShowString(140,140, "  body low ");
    }
    if(IS_KEY5_DOWN){
       LCD_ShowString(200,240, "  IS_KEY5_DOWN ");
       break;
    } 
    count++;
    if(count > 1000) break;
  }
  
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "-- LED ARRAY TEST--");	//title
  LCD_ShowString(100,100, " Sixth : you will see led array show");	//item
  LCD_ShowString(100, 160, " chinese fone & press key 5 to next item "); 	
  init_keypad();
  //count=0;
  while(1){
    LED_array_show_font();
    if(IS_KEY5_DOWN){
      // LCD_ShowString(200,240, "  IS_KEY5_DOWN ");
       break;
    } 
    //count++;
    //if(count > 1000) break;
   
  }
 
  // RFID 
    LCD_Clear(BLACK);
    LCD_DrawRectangle(0,0, 479, 271);
    LCD_DrawRectangle(5,5, 474, 266);
    LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
    LCD_ShowString(100,90, " Seventh : RFID test , READ Card");	//item
    LCD_ShowString(100,140, " RFID :");	//item
    LCD_ShowString(100, 180, "DATA :"); 	
    init_keypad();
    count =0;
    LED2_DIROUT;
             
    while(1){
      
    #if 1
      delay_ms(100);
      if(parse_RFID_info())//
      {
         LCD_Fill(180, 140, LCD_W- 80-180, 16 +140 ,BLACK );
         LCD_ShowString(180, 140, get_RFID_ID());
         LCD_Fill(50, 220, LCD_W- 320-100, 16 +220 ,BLACK );
         LCD_ShowString(50, 220, get_RFID_DATA());
      } 
    #else        
     if(Is_RS232_1_data())
     {
        if(count > 50){
          count = 0;
          LCD_Fill(100, 160, LCD_W-320-100, 16 +160 ,BLACK );
        }else{
        LCD_ShowChar(100+count*8, 160, get_RS232_1_byte(), 0);
        //LCD_ShowChar(100+count*8, 200, get_RS232_1_byte(), 1);
        count++;
        }
     }
    #endif
      if(IS_KEY5_DOWN){
         break;
      } 
    }
  
  //temperature 
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "-- Temperature TEST--");	//title
  LCD_ShowString(100,100, " Eighth : you will see temp & hum");	//item
  LCD_ShowString(80, 160, "wait a few seconds & press key 5 to next item"); 	
  
  while(1)
  {
   
    Send_DTH11();
    
    //LCD_Clear(WHITE);
    LCD_ShowString(160,200,"get temp = ");
    LCD_Fill(250, 200, LCD_W-5-250, 16 +200 ,BLACK );
    LCD_ShowNum(250,200,u8T_data_H,4);
    LCD_Fill(330, 200, LCD_W-5-330, 16 +200 ,BLACK );
    LCD_ShowNum(330,200,u8T_data_L,4);
    LCD_ShowString(160,240,"get hum  = ");
    LCD_Fill(250, 240, LCD_W-5-250, 16 +240 ,BLACK );
    LCD_ShowNum(250,240,u8RH_data_H,4);
    LCD_Fill(330, 240, LCD_W-5-330, 16 +240 ,BLACK );
    LCD_ShowNum(330,240,u8RH_data_L,4);
    
    //delay_s(2);
    
    if(IS_KEY5_DOWN){
      // LCD_ShowString(200,240, "  IS_KEY5_DOWN ");
       break;
    } 
  }

    #if 1 
    LCD_Clear(BLACK);
    LCD_DrawRectangle(0,0, 479, 271);
    LCD_DrawRectangle(5,5, 474, 266);
    LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
    LCD_ShowString(100,90, " ninth : acceleration & air pressure");	//item
    LCD_ShowString(100,140, " acceleration :");	//item
    LCD_ShowString(100, 180, "air pressure :"); 	
    LCD_ShowString(100, 220, " temperature :"); 	
    init_keypad();
    InitBMP085();
    
    while(1){
      bmp085Convert();
      LCD_Fill(280, 180, LCD_W- 40-280, 16 +180 ,BLACK );
      LCD_ShowString(280,180,get_pressure());         
      LCD_Fill(280, 220, LCD_W- 40-280, 16 +220 ,BLACK );
      LCD_ShowString(280,220,get_temperature());       
       
      delay_ms(100);
      LCD_Fill(280, 140, LCD_W- 40-280, 16 +140 ,BLACK );
      LCD_ShowNum(280,140,self_test7455(),3); 
      
      delay_ms(100);
      if(IS_KEY5_DOWN){
         break;
      } 
    }
  #endif  
    
  #if 0
  //net 
    LCD_Clear(BLACK);
    LCD_DrawRectangle(0,0, 479, 271);
    LCD_DrawRectangle(5,5, 474, 266);
    LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
    LCD_ShowString(100,90, " Twelfth : NET test");	//item
    init_keypad();
      
    while(1){
      net_main();
      delay_ms(100);
      if(IS_KEY5_DOWN){
         break;
      } 
    }
  #endif 
    
    #if 1
    //tp 
    LCD_Clear(BLACK);
    LCD_DrawRectangle(0,0, 479, 271);
    LCD_DrawRectangle(5,5, 474, 266);
    LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
    LCD_ShowString(100,90, " Eleventh : touch test");	//item
    LCD_ShowString(150 , 140, "X : ");
    LCD_ShowString(150 , 180, "Y : ");
    init_keypad();   
    tp_spi_init();
    //MISO_INPUT;
    count =0;
    while(1){

      if(is_tp_press())
      {
        //count++;
        // LCD_ShowString(50 + 10*count, 140, "press --");	
        if(Convert_Pos())
        {
          LCD_DrawPoint_big(tp_pixlcd.x,tp_pixlcd.y);
          //LCD_ShowString(50 + 10*count, 240, "press --");	
          LCD_Fill(200, 140, LCD_W- 40-200, 16 +140 ,BLACK );
          LCD_Fill(200, 180, LCD_W- 40-200, 16 +180 ,BLACK );
          LCD_ShowNum(200,140,tp_pixlcd.x,4);
          LCD_ShowNum(200,180,tp_pixlcd.y,4);
        }
        /*  count++;
          if(count > 30)
          {
            count = 0;
            LCD_Fill(50, 140, LCD_W- 40-50, 16 +140 ,BLACK );
          }
         LCD_ShowString(50 + 10*count, 140, "press --");	
         */
      }
      
     // delay_ms(100);
      if(IS_KEY5_DOWN){
         break;
      } 
    }
  #endif      
}
