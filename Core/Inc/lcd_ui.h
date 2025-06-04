#ifndef LCD_UI_H
#define LCD_UI_H

#include "stm32g4xx_hal.h"

void LCD_UI_Init(I2C_HandleTypeDef *hi2c);
void LCD_UI_Poll(void);

#endif /* LCD_UI_H */
