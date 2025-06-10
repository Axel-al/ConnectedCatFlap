#include "log_history.h"
#include "config.h"
#include <stdio.h>

static PassageLog log_buffer[MAX_LOG_ENTRIES];
static uint16_t log_count = 0;
static uint16_t log_index = 0;

void log_passage(uint8_t hour, uint8_t minute, Direction dir) {
    log_buffer[log_index].hour = hour;
    log_buffer[log_index].minute = minute;
    log_buffer[log_index].direction = dir;

    log_index = (log_index + 1) % MAX_LOG_ENTRIES;
    if (log_count < MAX_LOG_ENTRIES)
        log_count++;
}

Direction last_log_dir(void) {
	if (log_count == 0) {
		return DIR_BOTH;
	}
	uint16_t last_idx = (log_index + log_count - 1) % MAX_LOG_ENTRIES;
	return log_buffer[last_idx].direction;
}

void print_log_history(void) {
    printf("Historique passages (%d):\n", log_count);
    for (uint16_t i = 0; i < log_count; i++) {
        uint16_t idx = (log_index + i) % MAX_LOG_ENTRIES;
        printf("[%02d:%02d] %s\n",
               log_buffer[idx].hour,
               log_buffer[idx].minute,
               log_buffer[idx].direction == DIR_IN ? "ENTREE" : "SORTIE");
    }
}
