#include "msp430f5438a.h"
#include "timer.h"

void Init_Timer0_A5(void)
{
  TA0CTL=TASSEL1+ID1+ID0;//SMCLK,IDx=8
  TA0EX0=TAIDEX0+TAIDEX1+TAIDEX2;//IDEx=8,则TCLK=SMCK/8/8=250000Hz
  TA0CCR0=50000; // 50000/250000=0.2S=200ms设置计数器溢出时间为200ms
}

void Timer0_A5_Start(void)
{
  TA0R=0;//清零计数器
  TA0CTL&=~(MC0+MC1);//stop mode
  TA0CTL|=MC0+TAIE;//up mode,使能中断
}

void Timer0_A5_Stop(void)
{
  TA0R=0;//清零计数器
  TA0CTL|=TACLR;//Timer_A clear. Setting this bit resets TAR, the TACLK divider, and the count direction.
  TA0CTL&=~(MC0+MC1);//stop mode
}

unsigned char Timercounter=0,sign=0;

#pragma vector=TIMER0_A1_VECTOR                             
__interrupt void Timer0_A1(void)
{
   TA0CTL&=~TAIFG;//清中断标志位，防止不断进入中断函数
   Timercounter++;//200ms后进入中断，Timercounter加1
   if(Timercounter==5)//5x200ms=1s
   {
     Timercounter=0;//清零Timercounter
     sign=1;//置位全局变量sign
   }
}