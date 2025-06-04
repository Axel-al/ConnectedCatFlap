#include "lcd_ui.h"
#include "main.h"

static I2C_HandleTypeDef *lcd_i2c;
static uint32_t screen_timeout = 0;
static uint8_t screen_on = 0;

void LCD_UI_Init(I2C_HandleTypeDef *hi2c)
{
    lcd_i2c = hi2c;
}

static void lcd_power(uint8_t on)
{
    (void)lcd_i2c;
    // TODO: control LCD power
    screen_on = on;
    if (on)
        screen_timeout = HAL_GetTick() + 5000;
}

static void process_buttons(void)
{
    if (HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin) == GPIO_PIN_RESET)
        screen_timeout = HAL_GetTick() + 5000;
    if (HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin) == GPIO_PIN_RESET)
        screen_timeout = HAL_GetTick() + 5000;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == BTN_OK_Pin)
    {
        lcd_power(1);
    }
}

void LCD_UI_Poll(void)
{
    if (!screen_on) return;
    process_buttons();
    if (HAL_GetTick() > screen_timeout)
    {
        lcd_power(0);
    }
}
