#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "stm32g4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum { DIR_IN, DIR_OUT, DIR_BOTH } Direction;

typedef struct {
    uint8_t start_hour, start_min;
    uint8_t end_hour, end_min;
    Direction direction;
} TimeSlot;

void scheduler_init(void);
bool is_time_allowed(Direction dir);
bool is_time_forbidden(Direction dir);
TimeSlot get_time_slot(uint8_t slot_idx);
void set_time_slot(uint8_t slot_idx, TimeSlot slot);
void get_rtc_time(RTC_TimeTypeDef *time);
bool set_rtc_time(uint8_t hour, uint8_t minute);
void print_all_slots(void);

#endif /* INC_SCHEDULER_H_ */
