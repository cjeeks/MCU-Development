#include "msp430f5438a.h"
#include "watchdog1.h"

void WatchDog_init1(void)
{
  WDTCTL=WDTPW+WDTCNTCL+WDTIS1;//每次写WDTCTL必须带上WDTPW
                               //WDTCNTCL：Watchdog timer counter clear.
                               //WDTIS0~2：Watchdog timer interval select.
  //010=Watchdog clock source /8192k,SCLK/8192k=16M/8192k,对应8192k/16M=512ms
}

