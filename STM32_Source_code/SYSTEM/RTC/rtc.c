#include "rtc.h"
#include "string.h"

void RTC_Config(void)
{
	RTC_InitTypeDef RTC_InitStructure;
	RTC_TimeTypeDef RTC_TimeStructure;
  RTC_DateTypeDef RTC_DateStructure;
  
  /* 使能PWR电源时钟，Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* 允许访问rtc ,Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);
    
  /* 选择低速外部时钟：Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);

  /* 等待时钟稳定，Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }

  /* 设置时钟源Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
  
  /* 使能时钟，Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* 等待时钟同步，Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
  
  /* ck_spre(1Hz) = RTCCLK(LSE) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
  /* Configure the RTC data register and RTC prescaler */
  RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
  RTC_InitStructure.RTC_SynchPrediv = 0xFF;
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
  
	
	
  /* 设置日期，Set the date: Monday May 6th 2019 */
  RTC_DateStructure.RTC_Year = 0x19; // 年
  RTC_DateStructure.RTC_Month = RTC_Month_May; // 月
  RTC_DateStructure.RTC_Date = 0x06; // 日
  RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Monday; // 星期几
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
  
  /* 设置时间，Set the time to 05h 20mn 00s AM */
  RTC_TimeStructure.RTC_H12     = RTC_H12_PM; // 下午
  RTC_TimeStructure.RTC_Hours   = 0x23; // 时
  RTC_TimeStructure.RTC_Minutes = 0x59; // 分
  RTC_TimeStructure.RTC_Seconds = 0x55; // 秒
  
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);   
  
  /* 启动保护，Indicator for the RTC configuration */
  RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
}

void Set_Alarm(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;

	RTC_AlarmTypeDef RTC_AlarmStructure;
	
	/* Set the alarm 05h:20min:30s */
	RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_PM;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x15;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x14;
	RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x00;
	
	RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31;
	RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_WeekDay;
	RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;

	 /* Configure the RTC Alarm A register */
	RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
	
			/* Enable RTC Alarm A Interrupt */
	RTC_ITConfig(RTC_IT_ALRA, ENABLE);
	
	/* Enable the alarm */
	RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
	
	RTC_ClearFlag(RTC_FLAG_ALRAF);

	
	/* RTC Alarm A Interrupt Configuration */
	/* EXTI configuration *******************************************************/
	EXTI_ClearITPendingBit(EXTI_Line17);
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable the RTC Alarm Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	


}

void RTC_TimeShow(u8 *aShowTime)
{
	RTC_TimeTypeDef RTC_TimeStructure;
	
  /* Get the current Time */
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  /* Display time Format : hh:mm:ss */
  sprintf((char *)aShowTime,"%0.2d:%0.2d:%0.2d",RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
}

void RTC_DateShow(u8 *aShowTime)
{
	RTC_DateTypeDef RTC_DateStructure;
	
  /* Get the current Time */
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
  /* Display time Format : hh:mm:ss */
  sprintf((char *)aShowTime,"%0.2d年 %0.2d月 %0.2d日 星期%d",RTC_DateStructure.RTC_Year, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date, RTC_DateStructure.RTC_WeekDay);
}

 void RTC_AlarmShow(u8 *aShowTime)
{
	RTC_AlarmTypeDef RTC_AlarmStructure;
	
  /* Get the current Alarm */
  RTC_GetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);
  sprintf((char*)aShowTime,"%0.2d:%0.2d:%0.2d", RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours, RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes, RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds);
}

