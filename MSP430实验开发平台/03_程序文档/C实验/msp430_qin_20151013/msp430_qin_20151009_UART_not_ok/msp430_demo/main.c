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
unsigned char  MP3_Play[]={0x7E, 0x02, 0x0D, 0xEF};
void Init_CLK(void)
{
  /*
  WDTCTL     = WDTPW + WDTHOLD;  // 关看门狗 
  P5SEL|=BIT2+BIT3;//P5.2.3口选择连接XT2
  P7SEL|=BIT0+BIT1;//P7.0.1口选择连接XT1
  __bis_SR_register(SCG0)                                 ; // 关闭FLL控制回路
  UCSCTL0=0x0000;//方便自带调节
   UCSCTL1    = DCORSEL_7                                  ; // 设置DCO振荡范围
  UCSCTL2    = FLLD__1 + FLL_FACTOR                       ; // Fdco = ( FLL_FACTOR + 1)×FLLRef = (649 + 1) * 32768 = 21.2992MHz 4Mhz
 //   __bic_SR_register(SCG0)                                 ; // 打开FLL控制回路                                                            
 // __delay_cycles(1024000)                                 ; 
  
  UCSCTL3|=FLLREFDIV_1;//选择DCO参考频率为n=2,?
  UCSCTL6&=~(XT1OFF+XT2OFF);//开XT1，XT2
  UCSCTL6|=XCAP_3;//配置XT1内部电容12Pf
  UCSCTL6|=XT2DRIVE_2;//增大XT2的驱动能力
 
  
 // UCSCTL4=SELA_0+SELS_5+SELM_5;//ACLK选择XT1=32768Hz,SMCLK=XT2,MCLK=XT2 为16MHz
 UCSCTL4   |= SELA_0                                     ; // ACLK   = XT1 
  
  __bic_SR_register(SCG0)                                 ; // 打开FLL控制回路                                                            
  __delay_cycles(1024000)                                 ; 
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 错误标志                                                            
    SFRIFG1 &= ~OFIFG                                     ; 
  }while(SFRIFG1&OFIFG);   
    UCSCTL6   |= XT2DRIVE0 + XT2DRIVE1                      ; // XT2 驱动模式 24~32MHz     -----------????
  */

 // #if  EXT_CLK_32768
  #if  0
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  P7SEL     |= 0x03                                       ; // 端口选择外部低频晶振XT1
  UCSCTL6   &=~XT1OFF                                     ; // 使能外部晶振 
  UCSCTL6   |= XCAP_3                                     ; // 设置内部负载电容
  UCSCTL3   |= SELREF_2                                   ; // DCOref = REFO
  UCSCTL4   |= SELA_0                                     ; // ACLK   = XT1  
 // UCSCTL6|=XT1DRIVE_0;//增大XT2的驱动能力
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

unsigned char DHT11_data[2] = {0, 0};
  uint key_count =0;
  uchar read_val =0;
  uchar key_temp=0;
  
void main()
{
    
  unsigned char timer=0;
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  __disable_interrupt();
//  Init_CLK();//初始化系统时钟
/////// SET clk 32768
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  P7SEL     |= 0x03                                       ; // 端口选择外部低频晶振XT1
  UCSCTL6   &=~XT1OFF                                     ; // 使能外部晶振 
  UCSCTL6   |= XCAP_3                                     ; // 设置内部负载电容
  UCSCTL3   |= SELREF_2                                   ; // DCOref = REFO
  UCSCTL4   |= SELA_0                                     ; // ACLK   = XT1  
 // UCSCTL6|=XT1DRIVE_0;//增大XT2的驱动能力
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

///////
 // Init_USB();//UART2

  Init_RS232_0();    //RS232->UART1
  Init_RS232_1();   //GSM
 // Init_RS232_2();   //RFID
  Init_RS232_3();  //MP3 +RS232
   delay_ms(1000);
   RS232_3_TX(MP3_Play);
  //RS232_1_TX("AT\n\r");
  //RS232_1_TX("this is RS232_1");
  //while(1)
 // RS232_2_TX("this is RS232_2");
   RS232_0_TX("this is RS232_0");
   RS232_3_TX("this is RS232_3");
   
  //USB_TX("this is USB uart\n\r");     //会导致屏幕显示的内容不全
 Init_CLK();//初始化系统时钟
  __enable_interrupt();
  WDTCTL     = WDTPW + WDTHOLD                            ; // 关看门狗
  init_keypad();

  LCD_Init();  

   delay_ms(1000);  delay_ms(1000);
    LCD_Clear(BLACK);
////////////STEP 1 KEY
    LCD_DrawRectangle(0,0, 479, 271);
    LCD_DrawRectangle(5,5, 474, 266);
    LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
    delay_ms(100);
    LCD_ShowString(100,90, " Step 1 : KEY and GSM test");	//item
    LCD_ShowString(100,130, "Note   : Press K1-K4");
    delay_ms(100);
   // testing 
    PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0xFF);
  key_temp=0;
  while(key_temp!=0x0F)
  {
    if(IS_KEY1_DOWN==1) 
    {   
      delay_ms(20);
     if(IS_KEY1_DOWN==1) 
      {   
       // RS232_1_TX("AT\r\n");   //GSM TEST
        PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0xEF);
        key_temp |=0x01;
      }
    } 
     read_val = PCF8574_Single_ReadI2C(PCF8574_SlaveAddress);
      if((read_val & 0x80)==0)
      {
        PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0xEE);//
        key_temp |=0x02;
      }
      if((read_val & 0x40)==0)
        {
        PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0xEC);//
        key_temp |=0x04;
      }
        if((read_val & 0x20)==0)
      {
        PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0xE8);//
        key_temp |=0x08;
      }
  }  
    delay_ms(1000);
    key_count =0;
    PCF8574_Single_WriteI2C(PCF8574_SlaveAddress, 0xFF);
///////////////STEP 2 RELAY
    LCD_Clear(BLACK);
    LCD_DrawRectangle(0,0, 479, 271);
    LCD_DrawRectangle(5,5, 474, 266);
    LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
    LCD_ShowString(140,100, " Step 2 :Relay test ");	//item
    Init_GPIO();//small board key led
    Relay_test();
    delay_ms(500);//delay_s(1);     
      
//////////// STEP 3 DTH11 AND HUM
    LCD_Clear(BLACK);
    LCD_DrawRectangle(0,0, 479, 271);
    LCD_DrawRectangle(5,5, 474, 266);
    LCD_ShowString(150, 40, "-- Temperature TEST--");	//title
    LCD_ShowString(100,100, " Step 3 : you will see temp & hum");	//item	
    key_count =0;
     for(timer=25;timer>0;timer--)
    {
      Send_DTH11();
     // LCD_Clear(BLACK);
      LCD_ShowString(160,200,"DTH11 temp is:");
      //LCD_ShowString(250,200, DHT11_data);
      DHT11_data[0] = u8T_data_H/10;
      DHT11_data[1] = u8T_data_H%10;     
      LCD_ShowNum(272,200,DHT11_data[0],1);
      LCD_ShowNum(280,200,DHT11_data[1],1); 
      delay_ms(300);
     }    
#if 1
////////// STEP 4 RFID
  delay_ms(1000); 
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "-- RFID TEST--");	//title
  LCD_ShowString(100,100, " Step 4 : RFID test");	//item  
  LCD_ShowString(100,140, " RFID :");	//item
  LCD_ShowString(100, 180, "DATA :"); 	
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266); 
   while(!IS_KEY1_DOWN)
   {
      //delay_ms(100);
      if(parse_RFID_info())//
      {
         LCD_Fill(180, 140, LCD_W- 80-180, 16 +140 ,BLACK );
         LCD_ShowString(180, 140, get_RFID_ID());
         LCD_Fill(50, 220, LCD_W- 320-100, 16 +220 ,BLACK );
         LCD_ShowString(50, 220, get_RFID_DATA());
      } 
   } 
  delay_ms(2000);
  
 #endif
  #if 1
////////// STEP 5 DC motor test 
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
  LCD_ShowString(150,100, " Step 5 : DC Moto test ");	//item 
  Dc_Moto_test();
  delay_ms(2000);
////////// STEP 6 STEPPER MOTO TEST
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
  LCD_ShowString(150,100, " Step 6 : Stepper Moto test ");	//item
  StepperMoto_IO_init();
  StepperMoto_run_clockwise(); 
  delay_ms(2000);
 ////////// STEP 7 GAS AND BODY TEST 
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
  LCD_ShowString(150,100, " Step 7 : GAS and body test");	//item
  LCD_ShowString(100, 160, " Note  : Press key 5 to Break"); 	//value 
  gas_init();
  BODY_init();
  init_keypad();
  key_count =  0;
  while(!IS_KEY1_DOWN)
  {
    if(is_gas_alarm())  LCD_ShowString(140,100, "  gas low ");
                  else  LCD_ShowString(140,100, " gas  high ");
    if(is_BODY_alarm()) LCD_ShowString(140,140, "  body high ");
                  else  LCD_ShowString(140,140, "  body low ");
  }  
 
///////// STEP 8 LED ARRAY TEST
  LCD_Clear(BLACK);
  LCD_DrawRectangle(0,0, 479, 271);
  LCD_DrawRectangle(5,5, 474, 266);
  LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
  LCD_ShowString(100,100, " Step 8 : LED array test");	//item
  LCD_ShowString(100, 160, "Note   : Press key 5 to break "); 	
  init_keypad();
  key_count=0;
  Init_LED_array_GPIO();
  while(!IS_KEY1_DOWN)
  {
    LED_array_show_font();  
  }
  delay_ms(2000);
////////// STEP 9 ACC AND AIR TEST 
    LCD_Clear(BLACK);
    LCD_DrawRectangle(0,0, 479, 271);
    LCD_DrawRectangle(5,5, 474, 266);
    LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
    LCD_ShowString(100,90, " Step 9 : Acceleration & Air pressure");	//item
    LCD_ShowString(100,140, " acceleration :");	//item
    LCD_ShowString(100, 180, "air pressure :"); 	
    LCD_ShowString(100, 220, " temperature :"); 	
    init_keypad();
    InitBMP085();  
    while(!IS_KEY1_DOWN){
   {
      bmp085Convert();
      LCD_Fill(280, 180, LCD_W- 40-280, 16 +180 ,BLACK );
      LCD_ShowString(280,180,get_pressure());         
      LCD_Fill(280, 220, LCD_W- 40-280, 16 +220 ,BLACK );
      LCD_ShowString(280,220,get_temperature());       
      LCD_Fill(280, 140, LCD_W- 40-280, 16 +140 ,BLACK );
      LCD_ShowNum(280,140,self_test7455(),3); 
      if(IS_KEY1_DOWN)
      {
         break;
      } 
    }
 #endif  
    
//**********如下为备用代码******************   
    
#if 0
//over
  Init_LED_array_GPIO();//初始化按键，LED
  LCD_Init(); 
  init_keypad();

    // LED & KEY pad
    LCD_Clear(BLACK);
    LCD_DrawRectangle(0,0, 479, 271);
    LCD_DrawRectangle(5,5, 474, 266);
    LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
    LCD_ShowString(150,100, " Step 10 : LED key pad test");	//item
    LCD_ShowString(100, 160, " Note: Press ALL key to test "); 	//value 
   // LCD_ShowString(100, 200, " and then  press all key and see led  "); 	//value
    TM1638Test();
   
    #if 0
    //net 
      LCD_Clear(BLACK);
      LCD_DrawRectangle(0,0, 479, 271);
      LCD_DrawRectangle(5,5, 474, 266);
      LCD_ShowString(150, 40, "--MSP430F5438A TEST--");	//title
      LCD_ShowString(100,90, " Step 11 : NET test");	//item
      init_keypad();
        
      while(1){
        net_main();
        delay_ms(100);
        if(IS_KEY5_DOWN){
           break;
        } 
      }
    #endif 
    
    #if 0
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
    key_count =0;
    while(1){
      if(is_tp_press())
      {
        //key_count++;
        // LCD_ShowString(50 + 10*key_count, 140, "press --");	
        if(Convert_Pos())
        {
          LCD_DrawPoint_big(tp_pixlcd.x,tp_pixlcd.y);
          //LCD_ShowString(50 + 10*key_count, 240, "press --");	
          LCD_Fill(200, 140, LCD_W- 40-200, 16 +140 ,BLACK );
          LCD_Fill(200, 180, LCD_W- 40-200, 16 +180 ,BLACK );
          LCD_ShowNum(200,140,tp_pixlcd.x,4);
          LCD_ShowNum(200,180,tp_pixlcd.y,4);
        }

      }
      
     // delay_ms(100);
      if(IS_KEY5_DOWN){
         break;
      } 
    }
    #endif  
#endif    
}
}
