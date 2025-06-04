#ifndef RTC_WRAPPER_H
#define RTC_WRAPPER_H

#include "stm32g4xx_hal.h"

void RTC_Wrapper_Init(RTC_HandleTypeDef *hrtc);
void RTC_Wrapper_GetTime(RTC_TimeTypeDef *time, RTC_DateTypeDef *date);

#endif /* RTC_WRAPPER_H */
