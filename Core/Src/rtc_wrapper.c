#include "rtc_wrapper.h"

static RTC_HandleTypeDef *rtc;

void RTC_Wrapper_Init(RTC_HandleTypeDef *hrtc)
{
    rtc = hrtc;
}

void RTC_Wrapper_GetTime(RTC_TimeTypeDef *time, RTC_DateTypeDef *date)
{
    if (!rtc) return;
    HAL_RTC_GetTime(rtc, time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(rtc, date, RTC_FORMAT_BIN);
}
