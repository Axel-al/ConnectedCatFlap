#include "gache.h"
#include "main.h"

static uint32_t unlock_end = 0;

void Gache_Lock(void)
{
    HAL_GPIO_WritePin(MAGNET_CTRL_GPIO_Port, MAGNET_CTRL_Pin, GPIO_PIN_RESET);
    unlock_end = 0;
}

void Gache_Unlock(uint32_t duration_ms)
{
    HAL_GPIO_WritePin(MAGNET_CTRL_GPIO_Port, MAGNET_CTRL_Pin, GPIO_PIN_SET);
    unlock_end = HAL_GetTick() + duration_ms;
}

void Gache_Update(void)
{
    if (unlock_end && HAL_GetTick() > unlock_end)
    {
        Gache_Lock();
    }
}
