#include "pir.h"
#include "main.h"

void PIR_Init(void)
{
    // nothing to init since pin configured in MX_GPIO_Init
}

uint8_t PIR_Read(void)
{
    return HAL_GPIO_ReadPin(PIR_INPUT_GPIO_Port, PIR_INPUT_Pin);
}
