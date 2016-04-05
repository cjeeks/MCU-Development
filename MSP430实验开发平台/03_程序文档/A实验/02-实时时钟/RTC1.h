#ifndef _RTC_H
#define _RTC_H

#define RTC_HOLD do{RTCCTL01|=RTCHOLD;}while(0)
#define RTC_CALENDARMODE do{RTCCTL01|=RTCMODE;}while(0)

typedef struct {
  unsigned int Year;
  unsigned char Month;
  unsigned char DayofMonth;
  unsigned char DayofWeek;
  unsigned char Hours;
  unsigned char Minutes;
  unsigned char Seconds;
}CALENDAR_n;

extern void Init_RTC_Calendar(void);
extern CALENDAR_n GetTime(void);
extern void SET_Time(CALENDAR_n);
extern void SET_Alarmtime(unsigned char,unsigned char,unsigned char,unsigned char);

#endif