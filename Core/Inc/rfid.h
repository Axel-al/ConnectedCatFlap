#ifndef RFID_H
#define RFID_H

#include "stm32g4xx_hal.h"

void RFID_Init(SPI_HandleTypeDef *hspi,
               GPIO_TypeDef *cs_port, uint16_t cs_pin,
               GPIO_TypeDef *rst_port, uint16_t rst_pin);
int RFID_CheckCard(uint8_t *uid);

#endif /* RFID_H */
