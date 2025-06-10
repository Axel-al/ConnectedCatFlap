#ifndef INC_RFID_LOGIC_H_
#define INC_RFID_LOGIC_H_

#include <stdint.h>
#include <stdbool.h>

void rfid_logic_init(void);
bool is_authorized(const uint8_t *uid);
bool add_badge(const uint8_t *uid);
bool remove_badge(const uint8_t *uid);
void clear_badge_list(void);
void print_all_badges(void);

#endif /* INC_RFID_LOGIC_H_ */
