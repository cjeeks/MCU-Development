#include "msp430f5438a.h"
#include "RTC.h"
#include "intrinsics.h"

void Init_RTC_Calendar(void)
{
  
  RTCCTL01=RTCBCD+RTCMODE;//+RTCTEVIE+RTCAIE+RTCRDYIE;
  //BCD ,RTC Time Event Interrupt Enable,RTC Mode:Calendar
  //ACLK must be set to 32768 Hz, nominal for proper Real-Time Clock calendar operation
}

CALENDAR_n GetTime(void)
{
    CALENDAR_n time;
    unsigned int data=0;
    while(!(RTCCTL01&RTCRDY)); //等待keepout window出现
    data=RTCYEARH;
    time.Year = (data<<8)+RTCYEARL;
    time.Month = RTCMON;
    time.DayofMonth=RTCDAY;
    time.DayofWeek=RTCDOW;
    time.Hours=RTCHOUR;
    time.Minutes=RTCMIN;
    time.Seconds=RTCSEC;
    return time;
}

void SET_Time(CALENDAR_n time)
{
  while(!(RTCCTL01&RTCRDY));//等待keepout window出现
  RTCYEARH=(unsigned char)(time.Year>>8);
  RTCYEARL=(unsigned char)time.Year;
  RTCMON=time.Month;
  RTCDAY=time.DayofMonth;
  RTCDOW=time.DayofWeek;
  RTCHOUR=time.Hours;
  RTCMIN=time.Minutes;
  RTCSEC=time.Seconds;
}

void SET_Alarmtime(unsigned char day,unsigned char dow,unsigned char hour,unsigned char min)
{
  while(!(RTCCTL01&RTCRDY));//等待keepout window出现
  RTCADAY = (day ? 0x80+day : day);
  RTCADOW = (dow ? 0x80+dow : dow);
  RTCAHOUR = (hour ? 0x80+hour : hour);
  RTCAMIN = (min ? 0x80+min : min);
}
