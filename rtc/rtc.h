#ifndef RTC_H_
#define RTC_H_

#include "../i2c/i2c.h"

#define RTC_SLA_W	0b11010000
#define RTC_SLA_R	0b11010001

typedef struct  
{
	uint8 rtc_regs[7];
	uint8 rtc_time[8]; /*11:23:59*/
	uint8 rtc_date[8]; /*11/10/20*/
}RTC_STRUCT;

void rtc_init();
void rtc_update(RTC_STRUCT*);
void rtc_set_time();

#endif /* RTC_H_ */
