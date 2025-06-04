#include "config.h"

void Config_Init(config_t *cfg)
{
    cfg->count = 0;
}

static int match_dir(direction_t cond, direction_t current)
{
    if (cond == DIR_ANY) return 1;
    if (cond == current) return 1;
    return 0;
}

int Config_IsAllowed(const config_t *cfg, uint8_t hour, direction_t dir)
{
    if (cfg->count == 0) return 1;

    for (uint8_t i = 0; i < cfg->count; i++)
    {
        horaire_t *h = &cfg->horaires[i];
        if (hour >= h->start_hour && hour < h->end_hour)
        {
            if (match_dir(h->dir, dir))
                return 1;
        }
    }
    return 0;
}
