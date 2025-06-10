#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

// === RFID ===
#define MAX_BADGES             10     // Nombre maximum de badges autorisés
#define UID_LENGTH             5      // Taille d'un UID RFID

// === Ajout de badge ===
#define RFID_ADD_TIMEOUT_MS    10000   // Délai max pour scanner un nouveau badge (ms)

// === Plages horaires ===
#define NB_SLOTS               5      // Nombre de plages horaires programmables

// === Gâche électromagnétique ===
#define GATE_UNLOCK_MS         5000   // Temps d'ouverture de la trappe (ms)

// === Interface LCD ===
#define LCD_TIMEOUT_S          10     // Délai d'extinction de l'écran LCD (secondes)
#define MENU_ITEM_COUNT        7      // Nombre d'items dans le menu principale

// === Boutons ===
#define BTN_DEBOUNCE_MS        150    // Anti-rebond (en ms) pour le bouton OK

// === Logs ===
#define MAX_LOG_ENTRIES        32     // Nombre de logs gardé en mémoire

// === Debug UART ===
#define DEBUG_UART             0      // Active printf si 1, sinon désactive

#endif /* INC_CONFIG_H_ */
