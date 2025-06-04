#include "rfid.h"

static SPI_HandleTypeDef *rfid_hspi;
static GPIO_TypeDef *rfid_cs_port;
static uint16_t rfid_cs_pin;
static GPIO_TypeDef *rfid_rst_port;
static uint16_t rfid_rst_pin;

void RFID_Init(SPI_HandleTypeDef *hspi,
               GPIO_TypeDef *cs_port, uint16_t cs_pin,
               GPIO_TypeDef *rst_port, uint16_t rst_pin)
{
    rfid_hspi = hspi;
    rfid_cs_port = cs_port;
    rfid_cs_pin = cs_pin;
    rfid_rst_port = rst_port;
    rfid_rst_pin = rst_pin;
    // Reset the module
    HAL_GPIO_WritePin(rfid_rst_port, rfid_rst_pin, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(rfid_rst_port, rfid_rst_pin, GPIO_PIN_SET);
}

int RFID_CheckCard(uint8_t *uid)
{
    (void)uid;
    // TODO: implement communication with RC522 to read UID
    return 0;
}
