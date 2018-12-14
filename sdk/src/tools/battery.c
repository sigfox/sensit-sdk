/*!******************************************************************
 * \file battery.c
 * \brief Example of battery manager
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 SIGFOX, All Rights Reserved.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "button.h"
#include "battery.h"


/******* LOCAL VARIABLES *******************************************/
static u16 min_voltage = BATTERY_INIT_LEVEL;


/******* LOCAL FUNCTIONS *******************************************/
static void BATTERY_low(void);


/*******************************************************************/

void BATTERY_handler(u16* battery_level)
{
    /* Do a battery measurement */
    SENSIT_API_get_battery_level(battery_level);

    /* Check battery is not too low */
    if (*battery_level <= min_voltage)
    {
        /* Battery volatge is too low */
        BATTERY_low();
    }

    /* Compare to init level only for the first measurement */
    min_voltage = BATTERY_LOW_LEVEL;
}

/*******************************************************************/

static void BATTERY_low(void)
{
    button_e btn;
    u16 battLvl;
    u8 i;

    SENSIT_API_set_rtc_alarm(BATTERY_MEASURE_PERIOD);

    while (TRUE)
    {
        btn = BUTTON_handler();

        if (btn == BUTTON_ONE_PRESS)
        {
            for (i = 0 ; i < 3 ; i++)
            {
                /* When short click, blink white led */
                SENSIT_API_set_rgb_led(RGB_WHITE);
                SENSIT_API_wait(200);
                SENSIT_API_set_rgb_led(RGB_OFF);
                SENSIT_API_set_white_led(TRUE);
                SENSIT_API_wait(200);
                SENSIT_API_set_white_led(FALSE);
            }
        }
        else if (btn == BUTTON_FOUR_PRESSES)
        {
            /* Reset the device */
            SENSIT_API_reset();
        }

        SENSIT_API_get_battery_level(&battLvl);

        if (battLvl > BATTERY_INIT_LEVEL)
        {
            /* Battery level is ok. Restart device. */
            SENSIT_API_reset();
        }

        SENSIT_API_sleep(FALSE);
    }
}

/*******************************************************************/
