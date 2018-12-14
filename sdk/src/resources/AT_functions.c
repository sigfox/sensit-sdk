/*!******************************************************************
 * \file AT_functions.c
 * \brief Functions call by the AT parser
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "sigfox_types.h"
#include "sigfox_api.h"
#include "addon_sigfox_verified_api.h"
#include "AT_parser.h"
#include "serial.h"


/******* LOCAL VARIABLES *******************************************/
static radio_conf_e radio_conf = RADIO_CONF_LAST;
static bool use_public_key = FALSE;

static sfx_rc_t Sigfox_Radio_Configuration[RADIO_CONF_LAST] = {
    RC1,
    RC2,
    RC3C,
    RC4,
};

static sfx_u32 Config_Words[RADIO_CONF_LAST][3] = {
    {NA,NA,NA},//Unused in RC1
    RC2_SM_CONFIG,
    RC3C_CONFIG,
    RC4_SM_CONFIG,
};

static sfx_rc_enum_t addon_rc[RADIO_CONF_LAST] =  {
    SFX_RC1,
    SFX_RC2,
    SFX_RC3C,
    SFX_RC4,
};


/******* LOCAL FUNCTIONS *******************************************/
static void AT_report_error_code(sfx_error_t err);
static void AT_ok(void);
static void AT_error(void);


/*******************************************************************/

void AT_get_id(void)
{
    u8 id[ID_LENGTH];
    u8 i;
    u8 id_str[2];

    /* Get device ID */
    SIGFOX_API_get_device_id(id);
    /* Print ID */
    for ( i = 1 ; i <= ID_LENGTH ; i++)
    {
        AT_itoa((int)id[ID_LENGTH-i], (char*)id_str, 16);
        SERIAL_put_data(id_str, 2);
    }
}

/*******************************************************************/

void AT_get_sdk_version(void)
{
    u8* version;
    u8 size;

    /* Get SDK version */
    SENSIT_API_get_sdk_version(&version, &size);
    /* Print version */
    SERIAL_put_data(version, size-1);
}

/*******************************************************************/

void AT_get_sfx_lib_version(sfx_version_type_t type)
{
    u8* version;
    u8 size;

    if (type <= VERSION_RF)
    {
        /* Get lib version */
        SIGFOX_API_get_version(&version, &size, type);
        /* Print version */
        SERIAL_put_data(version, size-1);
    }
}

/*******************************************************************/

void AT_get_rc(void)
{
    u8 rc_number;

    if (radio_conf >= RADIO_CONF_LAST)
    {
        AT_error();
    }
    else
    {
        /* Print Radio Configuration */
        SERIAL_put_data((u8*)"RC", 2);
        AT_itoa((int)(radio_conf+1), (char*)&rc_number, 10);
        SERIAL_put_data(&rc_number, 1);
    }
}

/*******************************************************************/

void AT_set_rc(radio_conf_e rc)
{
    if (rc >= RADIO_CONF_LAST)
    {
        AT_error();
    }
    else
    {
        radio_conf = rc;
        SENSIT_API_configure_radio(RC_FROM_PARAMETER, &radio_conf);
        AT_ok();
    }
}

/*******************************************************************/

void AT_get_key_type(void)
{
    if (use_public_key != FALSE)
    {
        SERIAL_put_data((u8*)"PUBLIC", 6);
    }
    else
    {
        SERIAL_put_data((u8*)"PRIVATE", 7);
    }
}

/*******************************************************************/

void AT_set_key_type(bool type)
{
    use_public_key = type;
    AT_ok();
}

/*******************************************************************/

void AT_send_frame(u8* payload, u8 length)
{
    sfx_error_t err;

    err = SIGFOX_API_open(&Sigfox_Radio_Configuration[radio_conf]);
    if (err != SFX_ERR_NONE)
    {
        AT_report_error_code(err);
        return;
    }

    err = SIGFOX_API_set_std_config(&(Config_Words[radio_conf][0]), SFX_FALSE);
    if (err != SFX_ERR_NONE)
    {
        AT_report_error_code(err);
        return;
    }

    if (use_public_key != FALSE)
    {
        SIGFOX_API_switch_public_key(SFX_TRUE);
    }

    SENSIT_API_switch_radio(TRUE, 0xFF);

    err = SIGFOX_API_send_frame(payload, length, NULL, 2, SFX_FALSE);
    if (err != SFX_ERR_NONE)
    {
        AT_report_error_code(err);
        return;
    }

    SENSIT_API_switch_radio(FALSE, RGB_OFF);

    err = SIGFOX_API_close();
    if (err != SFX_ERR_NONE)
    {
        AT_report_error_code(err);
        return;
    }

    AT_ok();
}

/*******************************************************************/

void AT_continuous_wave(u32 frequency, sfx_modulation_type_t type)
{
    bool btn = TRUE;
    sfx_error_t err;

    SENSIT_API_switch_radio(TRUE, RGB_WHITE);

    err = SIGFOX_API_start_continuous_transmission(frequency, type);
    if (err != SFX_ERR_NONE)
    {
        AT_report_error_code(err);
        return;
    }

    SENSIT_API_set_rgb_led(RGB_WHITE);

    while (btn == TRUE)
    {
        /* Wait button is pressed */
        SENSIT_API_get_button_state(&btn);
    }

    SENSIT_API_set_rgb_led(RGB_OFF);

    err = SIGFOX_API_stop_continuous_transmission();
    if (err != SFX_ERR_NONE)
    {
        AT_report_error_code(err);
        return;
    }

    SENSIT_API_switch_radio(FALSE, RGB_WHITE);

    AT_ok();
}

/*******************************************************************/

void AT_get_test_mode_version(void)
{
    u8* version;
    u8 size;

    /* Get addon version */
    ADDON_SIGFOX_VERIFIED_API_get_version(&version, &size);
    /* Print version */
    SERIAL_put_data(version, size-1);
}

/*******************************************************************/

void AT_test_mode(sfx_test_mode_t mode)
{
    error_t err;

    /* Switch radio on */
    SENSIT_API_switch_radio(TRUE, 0xFF);

    err = ADDON_SIGFOX_VERIFIED_API_test_mode(addon_rc[radio_conf], mode);
    if (err != SFX_ERR_NONE)
    {
        AT_report_error_code(err);
    }
    else
    {
        AT_ok();
    }

    /* Switch radio off */
    SENSIT_API_switch_radio(FALSE, RGB_OFF);
}

/*******************************************************************/

static void AT_report_error_code(sfx_error_t err)
{
    u8 code[4];
    u8 i = 0;

    SERIAL_put_data((u8*)"ERR=0x", 6);
    AT_itoa((int)err, (char*)code, 16);
    while (code[i] != '\0')
    {
        SERIAL_put_data(code+i, 1);
        i++;
    }
}

/*******************************************************************/

static void AT_ok(void)
{
    SERIAL_put_data((u8*)"OK", 2);
}

/*******************************************************************/

static void AT_error(void)
{
    SERIAL_put_data((u8*)"ERR", 3);
}

/*******************************************************************/
