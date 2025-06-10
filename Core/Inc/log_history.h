#ifndef INC_LOG_HISTORY_H_
#define INC_LOG_HISTORY_H_

#include "scheduler.h"
#include <stdint.h>

typedef struct {
    uint8_t hour;
    uint8_t minute;
    Direction direction;
} PassageLog;

void log_passage(uint8_t hour, uint8_t minute, Direction dir);
Direction last_log_dir(void);
void print_log_history(void);

#endif /* INC_LOG_HISTORY_H_ */
