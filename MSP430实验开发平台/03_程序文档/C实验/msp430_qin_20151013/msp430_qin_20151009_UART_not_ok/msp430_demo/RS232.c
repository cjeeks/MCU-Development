#include "msp430f5438a.h"
#include <string.h>
#include "RS232.h"
#include "macro.h"
#include "GPIO.h"
#include "LCD.h"


uchar uart1_buf[BUF_SIZE];
uchar read_index = 0;
uchar write_index = 0;

//void Init_USB(void)//UART_A2,BAUDRATE=38400 (16M/UCSRX=416/UCBRSX=6/UCBRFX=0)(UCOS16 = 0)
void Init_USB(void)  //UART_A2, (32768/UCSRX=3/UCBRSX=3/UCBRFX=0)
{ 
#if EXT_CLK_32768 
//9600  
  P9SEL |= BIT4+BIT5; // 选择引脚功能:P9.4=UCA2TXD,P9.5=UCA2RXD
  UCA2CTL1 = UCSWRST; // 状态机复位
  //UCA2CTL0 = ;//LSB,8BIT,one stop bit,UART mode,Asynchronous mode
  //UCA2CTL1 |= UCSSEL_0+UCSSEL_1; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  UCA2CTL1  |= UCSSEL_1  ;
  UCA2BR0 = 0x03; 
  UCA2BR1 = 0x00;
  UCA2MCTL = UCBRS_3 + UCBRF_0  ;//UCBRS_6 + UCBRF_0; // UCBRSx=6, UCBRFx=0
  UCA2IFG = 0;
  UCA2CTL1 &= ~UCSWRST; // 启动状态机
  UCA2IE = UCRXIE; // 允许接收中断
  
#else //38400
  P9SEL |= BIT4+BIT5; // 选择引脚功能:P9.4=UCA2TXD,P9.5=UCA2RXD
  UCA2CTL1 = UCSWRST; // 状态机复位
  //UCA2CTL0 = ;//LSB,8BIT,one stop bit,UART mode,Asynchronous mode
  UCA2CTL1 |= UCSSEL_0+UCSSEL_1; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  
  UCA2BR0 = 0xa0; 
  UCA2BR1 = 0x01;
  UCA2MCTL = UCBRS_6 + UCBRF_0; // UCBRSx=6, UCBRFx=0
  UCA2IFG = 0;
  UCA2CTL1 &= ~UCSWRST; // 启动状态机
  UCA2IE = UCRXIE; // 允许接收中断
#endif
}

//void Init_RS232_0(void)//UART_A3,BAUDRATE=9600 (16M/UCSRX=1666/UCBRSX=6/UCBRFX=0)(UCOS16 = 0)
void Init_RS232_0(void)  //UART_A3,BAUDRATE=115200 (32768/UCSRX=3/UCBRSX=3/UCBRFX=0)
{
  /*uchar i=0;
  uchar j=0;
  P3SEL = 0x30;                             // P3.4,5 = USCI_A0 TXD/RXD
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0xd0;                              // 1MHz 115200 (see User's Guide)
  UCA0BR1 = 0x00;                              // 1MHz 115200
  UCA0MCTL |= UCBRS_4 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
  __bis_SR_register(GIE);       // Enter LPM3, interrupts enabled
  //__no_operation();                         // For debugger
  */
  
  //#if EXT_CLK_32768
  #if  0
  P3SEL = 0x30;                             // P3.4,5 = USCI_A0 TXD/RXD
  
  UCA0CTL1 = UCSWRST; // 状态机复位
  //UCA2CTL0 = ;//LSB,8BIT,one stop bit,UART mode,Asynchronous mode
  UCA0CTL1 |= UCSSEL__SMCLK; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  
  UCA0BR0 = 0xa0; 
  UCA0BR1 = 0x0;
  UCA0MCTL = UCBRS_6 + UCBRF_0; // UCBRSx=6, UCBRFx=0
  UCA0IFG = 0;
  UCA0CTL1 &= ~UCSWRST; // 启动状态机
  UCA0IE = UCRXIE; // 允许接收中断
 
#else
  P3SEL = 0x30;                             // P3.4,5 = USCI_A0 TXD/RXD
  UCA0CTL1 = UCSWRST; // 状态机复位
  UCA0CTL0 = UCPEN+UCPAR;//Even parity,LSB,8BIT,One stop bit,UART mode,Asynchronous mode

  UCA0CTL1 |= UCSSEL_0+UCSSEL_1; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  
  UCA0BR0 = 3; 
  UCA0BR1 = 0; 
  UCA0MCTL = UCBRS_3 + UCBRF_0; // UCBRSx=3, UCBRFx=0
  UCA0CTL1 &= ~UCSWRST; // 启动状态机
  UCA0IE |= UCRXIE; // 允许接收中断
#endif
  
  
}

//void Init_RS232_2(void)//UART_A1,BAUDRATE=19200 (16M/UCSRX=833/UCBRSX=2/UCBRFX=0)(UCOS16 = 0)
void Init_RS232_1(void)  //UART_A1,BAUDRATE=115200 (32768/UCSRX=3/UCBRSX=3/UCBRFX=0)
{ 
//#if EXT_CLK_32768
  #if  1
  USB_PORT_SEL   |= TXD_U + RXD_U                                  ; // 选择引脚功能
  USB_PORT_DIR   |= TXD_U                                          ; // 选择引脚功能
  
  UCA1CTL1 = UCSWRST; // 状态机复位
  //UCA2CTL0 = ;//LSB,8BIT,one stop bit,UART mode,Asynchronous mode
  UCA1CTL1 |= UCSSEL__SMCLK; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  
  UCA1BR0 = 0xa0; 
  UCA1BR1 = 0x0;
  UCA1MCTL = UCBRS_6 + UCBRF_0; // UCBRSx=6, UCBRFx=0
  UCA1IFG = 0;
  UCA1CTL1 &= ~UCSWRST; // 启动状态机
  UCA1IE = UCRXIE; // 允许接收中断
 
#else
  P5SEL |= BIT6+BIT7; // 选择引脚功能:P5.6=UCA1TXD,P5.7=UCA1RXD
  UCA1CTL1 = UCSWRST; // 状态机复位
  UCA1CTL0 = UCPEN+UCPAR;//Even parity,LSB,8BIT,One stop bit,UART mode,Asynchronous mode

  UCA1CTL1 |= UCSSEL_0+UCSSEL_1; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  
  UCA1BR0 = 3; 
  UCA1BR1 = 0; 
  UCA1MCTL = UCBRS_3 + UCBRF_0; // UCBRSx=3, UCBRFx=0
  UCA1CTL1 &= ~UCSWRST; // 启动状态机
  UCA1IE |= UCRXIE; // 允许接收中断
#endif
}
//void Init_RS232_2(void)//UART_A1,BAUDRATE=19200 (16M/UCSRX=833/UCBRSX=2/UCBRFX=0)(UCOS16 = 0)
void Init_RS232_2(void)  //UART_A1,BAUDRATE=115200 (32768/UCSRX=3/UCBRSX=3/UCBRFX=0)
{
  P9SEL |= BIT4+BIT5;                             // P9.4,5 = USCI_A0 TXD/RXD
  UCA2CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA2CTL1 |= UCSSEL_2;                     // SMCLK
  UCA2BR0 = 104;                              // 1MHz 9600 (see User's Guide)
  UCA2BR1 = 0;                              // 1MHz 9600
  UCA2MCTL |= 0x02;            // Modulation UCBRSx=1, UCBRFx=0
  UCA2CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA2IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt
  
  //
  //#if EXT_CLK_32768
  #if 0
   P9SEL |= BIT4+BIT5; 
    UCA2CTL1 = UCSWRST; // 状态机复位
  //UCA2CTL0 = ;//LSB,8BIT,one stop bit,UART mode,Asynchronous mode
  UCA2CTL1 |= UCSSEL__SMCLK; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  
  UCA2BR0 = 0xa0; 
  UCA2BR1 = 0x0;
  UCA2MCTL = UCBRS_6 + UCBRF_0; // UCBRSx=6, UCBRFx=0
  UCA2IFG = 0;
  UCA2CTL1 &= ~UCSWRST; // 启动状态机
  UCA2IE = UCRXIE; // 允许接收中断
  
#else
  P9SEL |= BIT4+BIT5;  // 选择引脚功能:P10.4=UCA3TXD,P10.5=UCA3RXD
  UCA2CTL1 = UCSWRST; // 状态机复位
  UCA2CTL0 = UCPEN+UCPAR;//Even parity,LSB,8BIT,One stop bit,UART mode,Asynchronous mode
  
  UCA2CTL1 |= UCSSEL_0+UCSSEL_1; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  
  UCA2BR0 = 3; 
  UCA2BR1 = 0; 
  UCA2MCTL = UCBRS_3 + UCBRF_0; // UCBRSx=3, UCBRFx=0
  UCA2CTL1 &= ~UCSWRST; // 启动状态机
  UCA2IE |= UCRXIE; // 允许接收中断  
#endif
  
}
//void Init_RS232_1(void)//UART_A3,BAUDRATE=9600 (16M/UCSRX=1666/UCBRSX=6/UCBRFX=0)(UCOS16 = 0)
void Init_RS232_3(void)  //UART_A3,BAUDRATE=115200 (32768/UCSRX=3/UCBRSX=3/UCBRFX=0)
{ 

//#if EXT_CLK_32768
  #if 0
  P10SEL |= BIT4+BIT5; 
    UCA3CTL1 = UCSWRST; // 状态机复位
  //UCA2CTL0 = ;//LSB,8BIT,one stop bit,UART mode,Asynchronous mode
  UCA3CTL1 |= UCSSEL__SMCLK; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  
  UCA3BR0 = 0xa0; 
  UCA3BR1 = 0x0;
  UCA3MCTL = UCBRS_6 + UCBRF_0; // UCBRSx=6, UCBRFx=0
  UCA3IFG = 0;
  UCA3CTL1 &= ~UCSWRST; // 启动状态机
  UCA3IE = UCRXIE; // 允许接收中断
  
#else
  P10SEL |= BIT4+BIT5; // 选择引脚功能:P10.4=UCA3TXD,P10.5=UCA3RXD
  UCA3CTL1 = UCSWRST; // 状态机复位
  UCA3CTL0 = UCPEN+UCPAR;//Even parity,LSB,8BIT,One stop bit,UART mode,Asynchronous mode
  
  UCA3CTL1 |= UCSSEL_0+UCSSEL_1; //UCSSEL=10: CLK = SMCLK = 16MHz
  //奇怪，为何改变不了时钟源？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
  
  UCA3BR0 = 3; 
  UCA3BR1 = 0; 
  UCA3MCTL = UCBRS_3 + UCBRF_0; // UCBRSx=3, UCBRFx=0
  UCA3CTL1 &= ~UCSWRST; // 启动状态机
  UCA3IE |= UCRXIE; // 允许接收中断  
#endif
}





void USB_TX(char *tx_buf)
{
  unsigned char i,length;
  length = strlen(tx_buf);
  for(i=0;i<length;i++)
  {
    while (!(UCA2IFG&UCTXIFG));
    UCA2TXBUF = *tx_buf++; 
  }
}

void RS232_0_TX(char *tx_buf)
{
  unsigned char i,length;
  length = strlen(tx_buf);
  for(i=0;i<length;i++)
  {
    while (!(UCA0IFG&UCTXIFG)); 
    UCA0TXBUF = *tx_buf++; 
  }
}

void RS232_1_TX(char *tx_buf)
{
  unsigned char i,length;
  length = strlen(tx_buf);
  for(i=0;i<length;i++)
  {
    while (!(UCA1IFG&UCTXIFG)); 
    UCA1TXBUF = *tx_buf++; 
  }
}

void RS232_2_TX(char *tx_buf)
{
  unsigned char i,length;
  length = strlen(tx_buf);
  for(i=0;i<length;i++)
  {
    while (!(UCA2IFG&UCTXIFG)); 
    UCA2TXBUF = *tx_buf++; 
  }
}

void RS232_3_TX(unsigned char *tx_buf)
{
  unsigned char i,length;
  length = strlen(tx_buf);
  for(i=0;i<length;i++)
  {
    while (!(UCA3IFG&UCTXIFG)); 
    UCA3TXBUF = *tx_buf++; 
  }
}
char test_flag =0;

#pragma vector=USCI_A1_VECTOR    //RS232_1    GSM
__interrupt void USCI_A1_ISR(void)
{
   
   unsigned char ch;
   static unsigned char count = 0, temp[] = {0};
   unsigned char a[1] = {'A'}; 
  
  
  switch(UCA1IV)
  {
    case 0:break;               // Vector 0 - no interrupt
    case 2:                     // Vector 2 - RXIFG    
        /*
         RS2_RX=UCA1RXBUF;
         if(RS2_RX=='2')
           P1OUT&=~BIT7;
         else
           P1OUT|=BIT7;
         break;
        */
	
        ch = UCA1RXBUF;
        temp[count] = ch;
        if(temp[count] == 0x0D)
        {
                temp[count] = ' ';
                LCD_ShowString(142, 160,a);
                LCD_ShowString(150, 160,temp);
                count = 0;	
        }
        if(temp[count] == 0x0A)
                temp[count] = ' ';		
	count ++;           
      break;
    case 4:break;               // Vector 4 - TXIFG
    default: break;  
  }
}

#pragma vector=USCI_A2_VECTOR    //USB RFID
__interrupt void USCI_A2_ISR(void)
{
  switch(UCA2IV)
  {
    case 0:break;               // Vector 0 - no interrupt
    case 2:                     // Vector 2 - RXIFG
      {
        /*
         USB_RX=UCA2RXBUF;
         if(USB_RX=='u')
           P1OUT&=~BIT6;
         else
           P1OUT|=BIT6;
         break;
        */
     /*  if(test_flag){
          P1OUT&=~BIT6;
          test_flag = 0;
        }else{
          test_flag = 1;     
           P1OUT|=BIT6;
        }*/
        uart1_buf[write_index] = UCA2RXBUF;
        write_index++;
        write_index %= BUF_SIZE; //write_index buf clear 0
      }
    case 4:break;               // Vector 4 - TXIFG
    default: break;  
  }
}

#pragma vector=USCI_A3_VECTOR    //RS232_1 
__interrupt void USCI_A3_ISR(void)
{
  switch(UCA3IV)
  {
    case 0:break;               // Vector 0 - no interrupt
    case 2:                     // Vector 2 - RXIFG
      {
        /*
         RS1_RX=UCA3RXBUF;
         if(RS1_RX=='1')
           P1OUT&=~BIT5;
         else
           P1OUT|=BIT5;
         break;
        */
    
         //uart1_buf[write_index] = UCA3RXBUF;
        // write_index++;
        // write_index %= BUF_SIZE;
  
   	//ch = UCA3RXBUF;	
      }
    case 4:break;               // Vector 4 - TXIFG
    default: break;  
  }
}

char Is_RS232_1_data(){
  if(write_index == read_index)
    return 0;
  else 
    return 1;
 
}

uchar get_RS232_1_byte(){
  uchar data = 0;
  data = uart1_buf[read_index];
  read_index++;
  read_index %= BUF_SIZE;
  return data;
}

uchar id[9];
uchar data[35];
/* format
02 39 42 41 35 45 30 32 33 37 03 02 32 31 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 03 
*/
char parse_RFID_info()
{
  uchar i,j;
  
  for(i=0; i<20; i++)
  {
      if(write_index == read_index)
        return 0; //fail
      if(uart1_buf[read_index] == 0x02)
      {
        if((write_index + BUF_SIZE - read_index)%BUF_SIZE > (11))
        {
          if((uart1_buf[(read_index+1)%BUF_SIZE] == 0x39)&&(uart1_buf[(read_index+10)%BUF_SIZE] == 0x03))
          {
            read_index = (read_index+2)%BUF_SIZE;//skip 0x39
            for(j=0;j<8;j++)
            {
              id[j]= uart1_buf[read_index];
              read_index = (read_index+1)%BUF_SIZE;;
            }
            id[8]='\0';     
            read_index =(read_index+1)%BUF_SIZE ;
            return 1;
          }
          else 
          {
            if((uart1_buf[(read_index+1)%BUF_SIZE] == 0x32)&&(uart1_buf[(read_index+36)%BUF_SIZE] == 0x03))
            {
              read_index = (read_index+2)%BUF_SIZE;//skip 0x32
              for(j=0;j<34;j++)
              {
                data[j]=  uart1_buf[read_index];
                read_index = (read_index+1)%BUF_SIZE;;
              }
              data[34]='\0';     
              read_index =(read_index+1)%BUF_SIZE ;
              return 1;
            }
            else
            {
              delay_ms(10);
              continue;
            }
          }
        }  
        else
        {
          delay_ms(100);
          continue;
        }
      }
      read_index++;
      read_index %= BUF_SIZE;
  }
  if(i > 20) return 0; //get id fail
  return 1;
}

uchar* get_RFID_ID()
{
  return &id[0];
}

uchar* get_RFID_DATA()
{
  return &data[0];
}

