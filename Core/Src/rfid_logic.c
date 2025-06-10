#include "rfid_logic.h"
#include "config.h"
#include <string.h>
#include <stdio.h>

static uint8_t badge_list[MAX_BADGES][UID_LENGTH];
static uint8_t badge_count = 0;

void rfid_logic_init(void) {
    badge_count = 0;
}

bool is_authorized(const uint8_t *uid) {
    for (uint8_t i = 0; i < badge_count; ++i) {
        if (memcmp(uid, badge_list[i], UID_LENGTH) == 0) {
            return true;
        }
    }
    return false;
}

bool add_badge(const uint8_t *uid) {
    if (badge_count >= MAX_BADGES)
        return false;

    memcpy(badge_list[badge_count], uid, UID_LENGTH);
    badge_count++;
    return true;
}

bool remove_badge(const uint8_t *uid) {
    for (uint8_t i = 0; i < badge_count; ++i) {
        if (memcmp(uid, badge_list[i], UID_LENGTH) == 0) {
            for (uint8_t j = i; j < badge_count - 1; ++j) {
                memcpy(badge_list[j], badge_list[j + 1], UID_LENGTH);
            }
            badge_count--;
            memset(badge_list[badge_count], 0, UID_LENGTH);
            return true;
        }
    }
    return false;
}

void clear_badge_list(void) {
    badge_count = 0;
}

void print_all_badges(void) {
#if DEBUG_UART
    for (uint8_t i = 0; i < badge_count; ++i) {
        printf("Badge %d: ", i);
        for (uint8_t j = 0; j < UID_LENGTH; ++j) {
            printf("%02X ", badge_list[i][j]);
        }
        printf("\n");
    }
#endif
}
