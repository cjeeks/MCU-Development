#include "msp430f5438a.h"
#include "timer1.h"

unsigned char sign=0;

void Init_Timer0_A5(void)
{
  TA0CTL=TASSEL1+ID1+ID0;//SMCLK=16MHz,IDx=8
  TA0EX0=TAIDEX2;//IDEx=5,则TCLK=SMCK/8/5=400000Hz
  TA0R=0;//清零计数器
  TA0CTL&=~(MC0+MC1);//stop mode
  
}

unsigned char timercount=0;
void Timer0_A5_Start(void)
{
  TA0CTL|=MC1;//Continuous mode，65535/400000=164ms
  while(!(TA0CTL&TAIFG));//等待164ms延时结束，置位中断标志位
  TA0CTL&=~TAIFG;//清中断标志位
  timercount++;
  if(timercount==30)//4.92S的延时
  {
    timercount=0;sign=1;//置位sign
  }
}

void Timer0_A5_Stop(void)
{
  TA0R=0;//清零计数器
  TA0CTL|=TACLR;//Timer_A clear. Setting this bit resets TAR, the TACLK divider, and the count direction.
  TA0CTL&=~(MC0+MC1);//stop mode
}
