#ifndef GACHE_H
#define GACHE_H

#include "stm32g4xx_hal.h"

void Gache_Lock(void);
void Gache_Unlock(uint32_t duration_ms);
void Gache_Update(void);

#endif /* GACHE_H */
