#include "menu_lcd.h"
#include "config.h"
#include "main.h"
#include "scheduler.h"
#include "rfid_handler.h"
#include "pcf8574.h"
#include "RC522.h"
#include "log_history.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint32_t last_interaction = 0;
static uint8_t menu_index = 0;
static bool menu_active = false;
static uint32_t last_btn_ok_press_time = 0;

static void reset_menu_timeout(void) {
    last_interaction = HAL_GetTick();
}

static uint32_t get_ms(void) {
    return HAL_GetTick();
}

static void display_main_menu(void) {
    pcf8574_clr();
    switch (menu_index) {
        case 0: pcf8574_send_string("1. Ajout badge"); break;
        case 1: pcf8574_send_string("2. Suppression\n   badge"); break;
        case 2: pcf8574_send_string("3. Reglage\n   heure"); break;
        case 3: pcf8574_send_string("4. Reglage\n   horaires"); break;
        case 4: pcf8574_send_string("5. Voir position   chat"); break;
        case 5: pcf8574_send_string("6. Envoyer\n   historique PC"); break;
        case 6: pcf8574_send_string("7. Quitter"); break;
    }
}

static void display_add_badge_screen(void) {
    pcf8574_clr();
    pcf8574_send_string("Scan nouv. badge");
    pcf8574_cursor(1, 6);
    pcf8574_send_string("....");
}

static void display_remove_badge_screen(void) {
    pcf8574_clr();
    pcf8574_send_string("Scan badge a\nsupprimer  ...");
}

static void update_displayed_data(char *buf, uint8_t cursor, uint8_t row) {
	static char last_buf[LCD_NUM_COLS + 1] = {0};

    if (strcmp(buf, last_buf) != 0) {
    	uint8_t middle = (LCD_NUM_COLS - strlen(buf)) / 2;

        pcf8574_cursor(row, 0);
        char erase[LCD_NUM_COLS + 1];
        memset(erase, ' ', LCD_NUM_COLS);
        erase[LCD_NUM_COLS] = '\0';
        pcf8574_send_string(erase);

        pcf8574_cursor(row, middle);
        pcf8574_send_string(buf);
        strcpy(last_buf, buf);
        pcf8574_cursor(row, cursor);
    }
}

static int select_slot_index(void) {
    uint8_t slot_idx = 0;

    update_displayed_data(" ", 0, 1);
    while (1) {
        char line[20];
        sprintf(line, "Plage hor. [%d]", slot_idx);
        update_displayed_data(line, 0, 0);

        if (HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin) == GPIO_PIN_RESET) {
            slot_idx = (slot_idx + 1) % NB_SLOTS;
            HAL_Delay(200);
        }
        if (HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin) == GPIO_PIN_RESET) {
            slot_idx = (slot_idx == 0) ? NB_SLOTS - 1 : slot_idx - 1;
            HAL_Delay(200);
        }
        if (get_ms() - last_btn_ok_press_time > BTN_DEBOUNCE_MS &&
                HAL_GPIO_ReadPin(BTN_OK_GPIO_Port, BTN_OK_Pin) == GPIO_PIN_RESET) {
            last_btn_ok_press_time = get_ms();
            return slot_idx;
        }
    }
}

static void handle_add_badge(void) {
	display_add_badge_screen();

	char msg[32];
	rfid_handler_add_badge(RFID_ADD_TIMEOUT_MS, msg);

	pcf8574_clr();
	pcf8574_send_string(msg);
	HAL_Delay(1500);
}

static void handle_remove_badge(void) {
	display_remove_badge_screen();

	char msg[32];
	rfid_handler_remove_badge(RFID_ADD_TIMEOUT_MS, msg);

	pcf8574_clr();
	pcf8574_send_string(msg);
	HAL_Delay(1500);
}

static void update_cursor_position(uint8_t cursor, uint8_t row) {
	static uint8_t last_cursor = 16;

    if (cursor != last_cursor) {
        pcf8574_cursor(row, cursor);
        last_cursor = cursor;
    }
}

static void apply_time_digit_change(uint8_t *digits, uint8_t cursor, bool increment) {
    int8_t delta = increment ? 1 : -1;
    switch (cursor) {
        case 0:
        	digits[0] = (digits[0] + delta + 3) % 3;
        	if (digits[0] == 2 && digits[1] >= 4)
        		digits[1] = 3;
        	return;
        case 1:
            if (digits[0] == 2)
                digits[1] = (digits[1] + delta + 4) % 4;
            else
                digits[1] = (digits[1] + delta + 10) % 10;
            return;
        case 2: digits[2] = (digits[2] + delta + 6) % 6; return;
        case 3: digits[3] = (digits[3] + delta + 10) % 10; return;
    }
}

static bool edit_time(uint8_t *h, uint8_t *m, char *title) {
    uint8_t digits[4] = {
        *h / 10,
        *h % 10,
        *m / 10,
        *m % 10
    };

    uint8_t cursor = 0;

    pcf8574_send_cmd(0x0D); // disp=on , cur=off, blink=on
    pcf8574_clr();
    pcf8574_send_string(title);

    update_displayed_data(" ", 0, 1);
    HAL_Delay(100);
    while (1) {
        char buf[6] = {
            '0' + digits[0],
            '0' + digits[1],
            ':',
            '0' + digits[2],
            '0' + digits[3],
            '\0'
        };
        update_displayed_data(buf, 5 + cursor + (cursor >= 2), 1);
        update_cursor_position(5 + cursor + (cursor >= 2), 1);

        if (HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin) == GPIO_PIN_RESET) {
            apply_time_digit_change(digits, cursor, true);
            HAL_Delay(200);
        }

        if (HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin) == GPIO_PIN_RESET) {
            apply_time_digit_change(digits, cursor, false);
            HAL_Delay(200);
        }

        if (get_ms() - last_btn_ok_press_time > BTN_DEBOUNCE_MS &&
            HAL_GPIO_ReadPin(BTN_OK_GPIO_Port, BTN_OK_Pin) == GPIO_PIN_RESET) {
            last_btn_ok_press_time = get_ms();
            if (cursor == 3) {
                *h = digits[0] * 10 + digits[1];
                *m = digits[2] * 10 + digits[3];

                pcf8574_send_cmd(0x0C); // disp=on , cur=off, blink=off
                return true;
            } else {
                cursor++;
                HAL_Delay(200);
            }
        }
    }
    return false;
}

void handle_slot_edit(void) {
    uint8_t slot = select_slot_index();
    TimeSlot cur_slot = get_time_slot(slot);

    if (!edit_time(&cur_slot.start_hour, &cur_slot.start_min, "Heure de debut :")) return;
    if (!edit_time(&cur_slot.end_hour, &cur_slot.end_min, "Heure de fin :")) return;

    char *dirs[] = {"IN ", "OUT", "BOTH"};
    uint8_t *dir_val = &cur_slot.direction;

    pcf8574_clr();
    pcf8574_send_string("Dir. interdite :");

    update_displayed_data(" ", 0, 1);
    while (1) {
        char line[17];
        sprintf(line, "< %s >", dirs[*dir_val]);
        update_displayed_data(line, 0, 1);

        if (HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin) == GPIO_PIN_RESET) {
            *dir_val = (*dir_val + 1) % 3;
            HAL_Delay(200);
        }

        if (HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin) == GPIO_PIN_RESET) {
            *dir_val = (*dir_val + 2) % 3;
            HAL_Delay(200);
        }

        if (get_ms() - last_btn_ok_press_time > BTN_DEBOUNCE_MS &&
            HAL_GPIO_ReadPin(BTN_OK_GPIO_Port, BTN_OK_Pin) == GPIO_PIN_RESET) {
            last_btn_ok_press_time = get_ms();

            set_time_slot(slot, cur_slot);
            pcf8574_clr();
            pcf8574_send_string("Plage\nenregistree");
            HAL_Delay(1500);
            return;
        }
    }
}

void menu_edit_rtc_time(void) {
    RTC_TimeTypeDef now;
    get_rtc_time(&now);
    uint8_t h = now.Hours, m = now.Minutes;

    if (edit_time(&h, &m, "Regl. heure RTC")) {
        if (set_rtc_time(h, m)) {
            pcf8574_clr();
            pcf8574_send_string("Heure mise\na jour");
        } else {
            pcf8574_clr();
            pcf8574_send_string("Erreur reglage heure");
        }
        HAL_Delay(1500);
    }
}

static void display_position(void) {
    pcf8574_clr();
    Direction dir = last_log_dir();
	if (dir == DIR_IN) {
        pcf8574_send_string("Le chat est a\nl'interieur");
	} else if (dir == DIR_OUT) {
        pcf8574_send_string("Le chat est a\nl'exterieur");
	} else {
		pcf8574_send_string("Le chat n'est\npas encore passe");
	}
	HAL_Delay(1500);
}

static void navigate_menu(void) {
    if (!menu_active) return;

    if (HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin) == GPIO_PIN_RESET) {
        menu_index = (menu_index == 0) ? (MENU_ITEM_COUNT - 1) : (menu_index - 1);
        display_main_menu();
        reset_menu_timeout();
        HAL_Delay(200);
    }

    if (HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin) == GPIO_PIN_RESET) {
        menu_index = (menu_index == (MENU_ITEM_COUNT - 1)) ? 0 : (menu_index + 1);
        display_main_menu();
        reset_menu_timeout();
        HAL_Delay(200);
    }

    if (get_ms() - last_btn_ok_press_time > BTN_DEBOUNCE_MS &&
    		HAL_GPIO_ReadPin(BTN_OK_GPIO_Port, BTN_OK_Pin) == GPIO_PIN_RESET) {
        switch (menu_index) {
            case 0: handle_add_badge(); break;
            case 1: handle_remove_badge(); break;
            case 2: menu_edit_rtc_time(); break;
            case 3: handle_slot_edit(); break;
            case 4: display_position(); break;
            case 5: print_log_history(); HAL_Delay(1000); break;
            case 6:
            	last_btn_ok_press_time = HAL_GetTick();
            	menu_active = false;
            	pcf8574_clr();
                HAL_Delay(300);
            	return;
        }
        display_main_menu();
        reset_menu_timeout();
        HAL_Delay(300);
    }
}

void lcd_menu_init(void) {
    pcf8574_init();
    pcf8574_clr();
    menu_active = false;
}

void handle_menu_navigation(void) {
    if (menu_active) navigate_menu();
}

void lcd_menu_timeout_check(void) {
    if (menu_active && (get_ms() - last_interaction > LCD_TIMEOUT_S * 1000)) {
        pcf8574_clr();
        menu_active = false;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == BTN_OK_Pin) {
		uint32_t now = HAL_GetTick();

	    if (!menu_active) {
	    	if (now - last_btn_ok_press_time < BTN_DEBOUNCE_MS) return;
	    	last_btn_ok_press_time = now;

	    	menu_active = true;
	        menu_index = 0;
	        display_main_menu();
	        reset_menu_timeout();
	    }
	}
}
