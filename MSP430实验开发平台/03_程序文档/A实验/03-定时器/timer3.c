#include "msp430f5438a.h"
#include "timer2.h"

void Init_Timer0_A5(void)
{
  TA0CTL&=~(MC0+MC1);//stop mode
  TA0CTL=TASSEL1+ID1+ID0;//SMCLK=1MHz,IDx=8
  TA0EX0=TAIDEX2;//IDEx=5,则TCLK=SMCK/8/5=25000Hz
  TA0CCR0=50000; // 50000/25000=2S设置计数器溢出时间为100ms！！！！！！！！！！
  TA0CCR3=25000; // 1s
  TA0R=0;//清零计数器
  
  P1DIR|=BIT4;//配置为输出（IMP）！！！！！！！！！！！！！！
  P1SEL|=BIT4;//P1.1选择第二功能：TA0.3（IMP）！！！！！！！！！！！！！！！！！
  
}

void Timer0_A5_Start(void)
{
  TA0CTL|=MC0;//Up mode，50000/25000=2s！！！！！！！！！！！！！！
  TA0CCTL3|=OUTMOD2;//Toggle output mode，该模式下2S的周期！！！！！！！！！！！！！
}

void Timer0_A5_Stop(void)
{
  TA0R=0;//清零计数器
  TA0CTL|=TACLR;//Timer_A clear. Setting this bit resets TAR, the TACLK divider, and the count direction.
  TA0CTL&=~(MC0+MC1);//stop mode
}

