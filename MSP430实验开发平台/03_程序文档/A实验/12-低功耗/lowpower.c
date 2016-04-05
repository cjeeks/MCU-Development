#include "msp430f5438a.h"
#include "lowpower.h"

/*************使用实时时钟的中断来使系统对出低功耗******************/

void Init_RTC(void)
{
  RTCCTL01=RTCTEV0+RTCTEVIE;
  //RTC Mode:32-bit counter mode / ACLK=32768Hz
  //RTCTEV=01:16-bit overflow, 65535/32768=2s
  //RTC Time Event Interrupt Enable
}

