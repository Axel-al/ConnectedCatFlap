#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

typedef enum {
    DIR_ANY,
    DIR_IN,
    DIR_OUT
} direction_t;

typedef struct {
    uint8_t start_hour;  /* 0-23 */
    uint8_t end_hour;    /* 0-23 */
    direction_t dir;     /* restriction */
} horaire_t;

#define MAX_HORAIRES 4

typedef struct {
    horaire_t horaires[MAX_HORAIRES];
    uint8_t count;
} config_t;

void Config_Init(config_t *cfg);
int Config_IsAllowed(const config_t *cfg, uint8_t hour, direction_t dir);

#endif /* CONFIG_H */
