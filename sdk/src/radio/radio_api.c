/*!******************************************************************
 * \file radio_api.c
 * \brief Sigfox APIs implementation for Sens'it
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "sigfox_types.h"
#include "sigfox_api.h"
#include "radio_api.h"
#include "etsi.h"
#include "fcc.h"


/******* LOCAL VARIABLES *******************************************/
static radio_conf_e radio_conf;

static sfx_rc_t rc_data[RADIO_CONF_LAST] = {
    RC1,
    RC2,
    RC3C,
    RC4,
};

static sfx_u32 config_words[RADIO_CONF_LAST][3] = {
    {NA,NA,NA}, // Unused in RC1
    RC2_SM_CONFIG,
    RC3C_CONFIG,
    RC4_SM_CONFIG,
};


/*******************************************************************/

error_t RADIO_API_init(void)
{
    rc_origin_e origin;
    error_t err;

#ifdef USE_RC1
    radio_conf = SIGFOX_RC1;
    origin = RC_FROM_PARAMETER;

#elif USE_RC2
    radio_conf = SIGFOX_RC2;
    origin = RC_FROM_PARAMETER;

#elif USE_RC3
    radio_conf = SIGFOX_RC3C;
    origin = RC_FROM_PARAMETER;

#elif USE_RC4
    radio_conf = SIGFOX_RC4;
    origin = RC_FROM_PARAMETER;

#else
    origin = RC_FROM_MEMORY;
#endif

    /* First, configure Sens'it radio */
    err = SENSIT_API_configure_radio(origin, &radio_conf);
    if (err != SENSIT_ERR_NONE)
    {
        return RADIO_ERR_CONFIGURE_RADIO;
    }

    /* Then, open Sigfox library */
    err = SIGFOX_API_open(&rc_data[radio_conf]);
    if (err != SFX_ERR_NONE)
    {
        return RADIO_ERR_OPEN;
    }

    /* And, set standard config */
    err = SIGFOX_API_set_std_config(&(config_words[radio_conf][0]), SFX_FALSE);
    if (err != SFX_ERR_NONE)
    {
        return RADIO_ERR_SET_STD_CONFIG;
    }

    return RADIO_ERR_NONE;
}

/*******************************************************************/

error_t RADIO_API_send_message(rgb_color_e color, u8* data, u8 size, bool downlink, u8* response_ptr)
{
    sfx_error_t err;
    error_t ret = RADIO_ERR_NONE;

    /* Check if transmission is allowed regarding regulations */
    if (radio_conf == SIGFOX_RC1)
    {
        /* Check ETSI duty cycle */
        if (ETSI_handler(size, downlink) == FALSE)
        {
            return RADIO_ERR_DUTY_CYCLE;
        }
    }
    else if ( (radio_conf == SIGFOX_RC2) || (radio_conf == SIGFOX_RC4) )
    {
        /* Check FCC channel over usage */
        if (FCC_handler(downlink) == FALSE)
        {
            return RADIO_ERR_NO_CHANNEL;
        }
    }

    /* Turn ON Sens'it radio */
    err = SENSIT_API_switch_radio(TRUE, color);
    if (err != SENSIT_ERR_NONE)
    {
        /* Failed to switch on radio */
        return RADIO_ERR_SWITCH_ON;
    }

    /* Send the frame */
    err = SIGFOX_API_send_frame(data, size, response_ptr, 2, downlink);
    if (err != SFX_ERR_NONE)
    {
        if (err == SFX_ERR_INT_PROCESS_UPLINK_CS_TIMEOUT)
        {
            ret = RADIO_ERR_LBT;
        }
        else if (err == SFX_ERR_INT_GET_RECEIVED_FRAMES_TIMEOUT)
        {
            ret = RADIO_ERR_RECEIVE;
        }
        else if (err == SFX_ERR_INT_EXECUTE_COM_SEQUENCE_NVM_STORAGE_MESSAGE)
        {
            ret = RADIO_ERR_NVMEM;
        }
        else
        {
            ret = RADIO_ERR_SEND;
        }
    }

    /* Turn OFF Sens'it radio */
    SENSIT_API_switch_radio(FALSE, color);

    return ret;
}

/*******************************************************************/
