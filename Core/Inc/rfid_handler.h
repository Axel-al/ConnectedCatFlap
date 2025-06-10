#ifndef INC_RFID_HANDLER_H_
#define INC_RFID_HANDLER_H_

#include <stdint.h>
#include <stdbool.h>

void rfid_handler_poll(void);
bool rfid_handler_add_badge(uint32_t timeout, char *message_out);
bool rfid_handler_remove_badge(uint32_t timeout, char *message_out);

#endif /* INC_RFID_HANDLER_H_ */
