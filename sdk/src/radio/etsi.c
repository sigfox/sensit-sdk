/*!******************************************************************
 * \file etsi.c
 * \brief Management of ETSI duty cycle
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 SIGFOX, All Rights Reserved.
 *
 * The ETSI regulation allows to transmit 1% of the time during 1h,
 * so you can transmit 36s each hour.
 * This regulation is for RC1 only.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "etsi.h"


/******* DEFINES ***************************************************/
#define ETSI_MAX_ALLOWED_TX_DURATION       36000 /* 36s in ms to reach 1% of time/hour */
#define ETSI_WINDOW                        3600 /* 1 hour window */

/* Frame duration for each payload size. Three frames are sent in one Sigfox message. */
#define FRAME_0_BYTES                      1120 /* 1.12 s */
#define FRAME_1_BYTES                      1200 /* 1.2 s */
#define FRAME_2_4_BYTES                    1440 /* 1.44 s */
#define FRAME_5_8_BYTES                    1760 /* 1.76 s */
#define FRAME_9_12_BYTES                   2080 /* 2.08 s */
#define FRAME_OOB                          1760 /* 1.76 s */


/******* LOCAL VARIABLES *******************************************/
static etsi_s frame_sent[10] = { {0, 0} };


/*******************************************************************/

bool ETSI_handler(u8 frame_size, bool downlink_required)
{
    u8 i;
    u32 current_time;
    u32 needed_duration;
    u32 used_duration = 0;

    /* Compute needed Tx duration */
    if (frame_size == 0)
    {
        needed_duration = 3 * FRAME_0_BYTES;
    }
    else if ( frame_size == 1)
    {
        needed_duration = 3 * FRAME_1_BYTES;
    }
    else if ( frame_size < 5)
    {
        needed_duration = 3 * FRAME_2_4_BYTES;
    }
    else if ( frame_size < 9)
    {
        needed_duration = 3 * FRAME_5_8_BYTES;
    }
    else
    {
        needed_duration = 3 * FRAME_9_12_BYTES;
    }
    if (downlink_required == TRUE)
    {
        /* Add time for downlink acknoledge */
        needed_duration += FRAME_OOB;
    }

    /* Compute available Tx duration */
    SENSIT_API_get_current_time(&current_time);

    /* Check last 10 messages sent */
    for (i = 0 ; i < 10 ; i++)
    {
        if (frame_sent[i].timestamp > current_time )
        {
            /* Message is in the duty cycle window */
            used_duration += frame_sent[i].tx_duration;
        }
    }

    /* Check if the transmission is allowed */
    if ( (needed_duration + used_duration) <= ETSI_MAX_ALLOWED_TX_DURATION )
    {
        /* Transmission allowed. Save timestamp & Tx duration */
        for (i = 0 ; i < 10 ; i++)
        {
            if (frame_sent[i].timestamp <= current_time)
            {
                /* Case is free. Write values here. */
                frame_sent[i].timestamp = current_time + ETSI_WINDOW;
                frame_sent[i].tx_duration = needed_duration;
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
