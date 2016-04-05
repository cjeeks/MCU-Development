#include "msp430f5438a.h"
#include "watchdog.h"

void WatchDog_init(void)
{
  WDTCTL=WDTPW+WDTCNTCL+WDTTMSEL+WDTIS0;//每次写WDTCTL必须带上WDTPW
                                        //WDTCNTCL：Watchdog timer counter clear.
                                        //WDTTMSEL：Interval timer mode
                                        //WDTIS0~2：Watchdog timer interval select.
  //001=Watchdog clock source /128M,SCLK/128M=16M/128M,对应128/16=8s
  WDT_INTENABLE;//使能WDT中断
}

