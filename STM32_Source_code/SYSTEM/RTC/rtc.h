#ifndef __RTC_H__
#define __RTC_H__

#include "stm32f4xx.h"

void RTC_Config(void);
void RTC_TimeShow(u8 *aShowTime);
void RTC_DateShow(u8 *aShowTime);
 void RTC_AlarmShow(u8 *aShowTime);
void Set_Alarm(void);

#endif
