#include "rfid_handler.h"
#include "RC522.h"
#include "rfid_logic.h"
#include "scheduler.h"
#include "gate_control.h"
#include "config.h"
#include "log_history.h"
#include <string.h>
#include <stdio.h>

static bool rfid_read_uid(uint8_t *uid) {
    uint8_t status, cardType[2];
    status = MFRC522_Request(PICC_REQIDL, cardType);
    if (status != MI_OK) return false;
    status = MFRC522_Anticoll(uid);
    if (status == MI_OK) {
		#if DEBUG_UART
    	printf("Lecture du RFID, UID : %02X:%02X:%02X:%02X\n", uid[0], uid[1], uid[2], uid[3]);
		#endif
    	return true;
    }
    return false;
}

static Direction detect_direction(void) {
	Direction dir = is_pir_triggered() ? DIR_OUT : DIR_IN;
	#if DEBUG_UART
	if (dir == DIR_IN)
		printf("Le chat est à l'exterieur et va vers l'interieur\n");
	else
		printf("Le chat est à l'interieur et va vers l'exterieur\n");
	#endif
    return dir;
}

static void process_uid(uint8_t *uid) {
    if (!is_authorized(uid)) return;
    Direction dir = detect_direction();
    if (is_time_allowed(dir)) {
        unlock_gate_temporary();
        RTC_TimeTypeDef now;
        get_rtc_time(&now);
        log_passage(now.Hours, now.Minutes, dir);
    }
}

void rfid_handler_poll(void) {
    uint8_t uid[UID_LENGTH];
    if (rfid_read_uid(uid)) {
        process_uid(uid);
    }
}

bool rfid_handler_add_badge(uint32_t timeout, char *message_out) {
    uint8_t uid[UID_LENGTH];
    uint32_t start = HAL_GetTick();

    while (HAL_GetTick() - start < timeout) {
        if (rfid_read_uid(uid)) {

            if (is_authorized(uid)) {
                sprintf(message_out, "Deja autorise");
                return false;
            } else if (add_badge(uid)) {
                sprintf(message_out, "Badge ajoute !");
                return true;
            } else {
                sprintf(message_out, "Liste pleine !");
                return false;
            }
        }
    }

    sprintf(message_out, "Ajout annule");
    return false;
}

bool rfid_handler_remove_badge(uint32_t timeout, char *message_out) {
    uint8_t uid[UID_LENGTH];
    uint32_t start = HAL_GetTick();

    while (HAL_GetTick() - start < timeout) {
        if (rfid_read_uid(uid)) {

            if (remove_badge(uid)) {
                sprintf(message_out, "Badge supprime !");
                return true;
            } else {
                sprintf(message_out, "Badge non trouve");
                return false;
            }
        }
    }

    sprintf(message_out, "Suppression\nannule");
    return false;
}
