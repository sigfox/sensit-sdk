/*!******************************************************************
 * \file fcc.c
 * \brief Management of FCC duty cycle
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 SIGFOX, All Rights Reserved.
 *
 * The FCC regulation prohibits re-transmission in the same channel
 * before 20s.
 * This regulation is for RC2 & RC4 only.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "fcc.h"


/******* DEFINES ***************************************************/
#define FCC_MAX_ALLOWED_CHANNELS           6  /* There are 6 available frequency hopping channel */
#define FCC_WINDOW                         20 /* Reload each 20s */


/******* LOCAL VARIABLES *******************************************/
static fcc_s channel_used[2] = { {0,0} };


/*******************************************************************/

bool FCC_handler(bool downlink_required)
{
    u8 i;
    u32 current_time;
    u8 needed_channels;
    u8 used_channels = 0;

    /* Compute needed channels */
    needed_channels = 3; /* A Sigfox message use 3 channels */
    if (downlink_required == TRUE)
    {
        /* Need a channel for downlink acknoledge */
        needed_channels += 1;
    }

    /* Compute available channels */
    SENSIT_API_get_current_time(&current_time);

    /* Count available number of channels */
    for (i = 0 ; i < 2 ; i++)
    {
        if (channel_used[i].timestamp > current_time)
        {
            used_channels += channel_used[i].channel_used;
        }
    }

    /* Check if the transmission is allowed */
    if ( (needed_channels + used_channels) <= FCC_MAX_ALLOWED_CHANNELS )
    {
        /* Transmission allowed. Save timestamp & Nb of used channels */
        for (i = 0 ; i < 2 ; i++)
        {
            if (channel_used[i].timestamp <= current_time)
            {
                /* Case is free. Write values here. */
                channel_used[i].timestamp = current_time + FCC_WINDOW;
                channel_used[i].channel_used = needed_channels;
                break;
            }
        }

        return TRUE;
    }
    else
    {
        /* Transmission forbidden */
        return FALSE;
    }
}

/*******************************************************************/
