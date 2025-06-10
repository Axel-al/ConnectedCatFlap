#include "scheduler.h"
#include "config.h"
#include "main.h"
#include <stdio.h>

static TimeSlot horaires_autorises[NB_SLOTS];

void scheduler_init(void) {
    for (int i = 0; i < NB_SLOTS; ++i) {
        horaires_autorises[i] = (TimeSlot){0, 0, 0, 0, DIR_BOTH};
    }
    set_rtc_time(0, 0);
}

bool is_time_allowed(Direction dir) {
    return !is_time_forbidden(dir);
}

bool is_time_forbidden(Direction dir) {
    RTC_TimeTypeDef time;
    get_rtc_time(&time);
    uint16_t now = time.Hours * 60 + time.Minutes;

    for (int i = 0; i < NB_SLOTS; ++i) {
        TimeSlot *s = &horaires_autorises[i];

        if (s->direction != dir && s->direction != DIR_BOTH)
            continue;

        uint16_t start = s->start_hour * 60 + s->start_min;
        uint16_t end   = s->end_hour   * 60 + s->end_min;

        if (start < end && now >= start && now <= end)
			return true;
		else if(start > end &&
				((now >= start && now < 24*60) || (now >= 0 && now < end)))
			return true;
    }
    return false;
}

TimeSlot get_time_slot(uint8_t slot_idx) {
	if (slot_idx < NB_SLOTS)
		return horaires_autorises[slot_idx];
	else
		return (TimeSlot) {0, 0, 0, 0, 0};
}

void set_time_slot(uint8_t slot_idx, TimeSlot slot) {
    if (slot_idx < NB_SLOTS)
        horaires_autorises[slot_idx] = slot;
}

void get_rtc_time(RTC_TimeTypeDef *time) {
    RTC_DateTypeDef dummy;
    HAL_RTC_GetTime(&hrtc, time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &dummy, RTC_FORMAT_BIN);
}

bool set_rtc_time(uint8_t hour, uint8_t minute) {
    RTC_TimeTypeDef time = {0};
    time.Hours   = hour;
    time.Minutes = minute;
    time.Seconds = 0;
    if (HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN) != HAL_OK) {
        return false;
    }

    RTC_DateTypeDef dummy;
    HAL_RTC_GetDate(&hrtc, &dummy, RTC_FORMAT_BIN);
    return true;
}

void print_all_slots(void) {
#if DEBUG_UART
    for (int i = 0; i < NB_SLOTS; ++i) {
        printf("Slot %d: %02d:%02d -> %02d:%02d (Dir: %d)\n", i,
            horaires_autorises[i].start_hour, horaires_autorises[i].start_min,
            horaires_autorises[i].end_hour, horaires_autorises[i].end_min,
            horaires_autorises[i].direction);
    }
#endif
}
