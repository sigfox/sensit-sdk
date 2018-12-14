/*!******************************************************************
 * \file error.c
 * \brief Critical errors management
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "button.h"
#include "radio_api.h"
#include "hts221.h"
#include "ltr329.h"
#include "fxos8700.h"


/******* LOCAL FUNCTIONS ******************************************/
static void ERROR_loop(u8 blink);


/*******************************************************************/

void ERROR_parser(error_t err)
{
    if ((err == RADIO_ERR_CONFIGURE_RADIO) || (err == RADIO_ERR_OPEN) || (err == RADIO_ERR_SET_STD_CONFIG))
    {
        /* Failed to init radio */
        ERROR_loop(2);
    }
    else if ((err == HTS221_ERR_I2C) || (err == HTS221_ERR_ID) || (err == LTR329_ERR_I2C) || (err == LTR329_ERR_ID) || (err == FXOS8700_ERR_I2C) || (err == FXOS8700_ERR_ID))
    {
        /* Sensor critical error */
        ERROR_loop(3);
    }
    else if ((err == RADIO_ERR_SEND) || (err == RADIO_ERR_SWITCH_ON))
    {
        /* A fatal error has occurred during transmission */
        ERROR_loop(4);
    }
    else if ((err == RADIO_ERR_DUTY_CYCLE) || (err == RADIO_ERR_NO_CHANNEL) || (err == RADIO_ERR_LBT))
    {
        /* Transmission not allowed. You must wait. */
        SENSIT_API_set_rgb_led(RGB_RED);
        SENSIT_API_wait(500);
        SENSIT_API_set_rgb_led(RGB_OFF);
    }
    else if (err == HTS221_ERR_MEASURE_TIMEOUT)
    {
        /* Temperature & relative humidity measurement timeout */
        SENSIT_API_set_rgb_led(RGB_RED);
        SENSIT_API_wait(250);
        SENSIT_API_set_rgb_led(RGB_GREEN);
        SENSIT_API_wait(250);
        SENSIT_API_set_rgb_led(RGB_RED);
        SENSIT_API_wait(250);
        SENSIT_API_set_rgb_led(RGB_OFF);

        /* Reset sensor */
        if (HTS221_init() != HTS221_ERR_NONE)
        {
            /* Sensor critical error */
            ERROR_loop(3);
        }
    }
    else if (err == LTR329_ERR_MEASURE_TIMEOUT)
    {
        /* Light measurement timeout */
        SENSIT_API_set_rgb_led(RGB_RED);
        SENSIT_API_wait(250);
        SENSIT_API_set_rgb_led(RGB_YELLOW);
        SENSIT_API_wait(250);
        SENSIT_API_set_rgb_led(RGB_RED);
        SENSIT_API_wait(250);
        SENSIT_API_set_rgb_led(RGB_OFF);

        /* Reset sensor */
        if (LTR329_init() != LTR329_ERR_NONE)
        {
            /* Sensor critical error */
            ERROR_loop(3);
        }
    }
    else if (err == RADIO_ERR_NVMEM)
    {
        /* Reset the device sequence number */
        SENSIT_API_reset_device_sequence_number();
        /* A fatal error has occurred */
        ERROR_loop(5);
    }
}

/*******************************************************************/

static void ERROR_loop(u8 blink)
{
    button_e btn;
    u8 i;

    /* Device is put in a blocked mode to display error */
    while (TRUE)
    {
        btn = BUTTON_handler();

        if (btn == BUTTON_ONE_PRESS)
        {
            for (i = 0 ; i < blink ; i++)
            {
                /* Red led blinks to display error type */
                SENSIT_API_set_rgb_led(RGB_RED);
                SENSIT_API_wait(500);
                SENSIT_API_set_rgb_led(RGB_OFF);
                SENSIT_API_wait(500);
            }
        }
        else if (btn == BUTTON_FOUR_PRESSES)
        {
            /* Reset device */
            SENSIT_API_reset();
        }

        SENSIT_API_sleep(FALSE);
    }
}

/*******************************************************************/
