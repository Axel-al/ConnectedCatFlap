#include "controleur.h"
#include "rfid.h"
#include "pir.h"
#include "gache.h"
#include "rtc_wrapper.h"
#include "lcd_ui.h"
#include "main.h"

static config_t cfg;
static uint8_t uid[5];

void Controleur_Init(void)
{
    Config_Init(&cfg);
    RFID_Init(&hspi1, RC522_CS_GPIO_Port, RC522_CS_Pin, RC522_RST_GPIO_Port, RC522_RST_Pin);
    RTC_Wrapper_Init(&hrtc);
}

static direction_t get_direction(void)
{
    return PIR_Read() ? DIR_OUT : DIR_IN;
}

static int verifier_autorisation(void)
{
    RTC_TimeTypeDef t;
    RTC_DateTypeDef d;
    RTC_Wrapper_GetTime(&t, &d);
    direction_t dir = get_direction();
    if (!Config_IsAllowed(&cfg, t.Hours, dir))
        return 0;
    if (!RFID_CheckCard(uid))
        return 0;
    return 1;
}

void Controleur_Tick(void)
{
    Gache_Update();
    if (verifier_autorisation())
    {
        Gache_Unlock(3000);
    }
}
