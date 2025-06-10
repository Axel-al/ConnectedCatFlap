#include "gate_control.h"
#include "main.h"
#include "config.h"
#include "stm32g4xx_hal.h"

void unlock_gate_temporary(void) {
    HAL_GPIO_WritePin(MAGNET_CTRL_GPIO_Port, MAGNET_CTRL_Pin, GPIO_PIN_SET);
    HAL_Delay(GATE_UNLOCK_MS);
    lock_gate();
}

void lock_gate(void) {
    HAL_GPIO_WritePin(MAGNET_CTRL_GPIO_Port, MAGNET_CTRL_Pin, GPIO_PIN_RESET);
}

bool is_pir_triggered(void) {
    return HAL_GPIO_ReadPin(PIR_INPUT_GPIO_Port, PIR_INPUT_Pin) == GPIO_PIN_SET;
}
