/*!******************************************************************
 * \file button.c
 * \brief Sample code for button
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "button.h"


/******* DEFINES ***************************************************/
#define BUTTON_TIMEOUT          2 /* seconds */


/*******************************************************************/

button_e BUTTON_handler(void)
{
    bool new_state;
    bool last_state;

    u32 current_time;
    u32 timeout;

    button_e count = BUTTON_LONG_PRESS;

    SENSIT_API_get_button_state(&new_state);

    if (!new_state)
    {
        /* Button is pressed. Start press count */
        last_state = new_state;

        SENSIT_API_get_current_time(&current_time);
        timeout = current_time + BUTTON_TIMEOUT;

        while (current_time < timeout)
        {
            SENSIT_API_get_button_state(&new_state);

            if (new_state != last_state)
            {
                /* Button state change. Increment presses */
                count += new_state;
                last_state = new_state;

                /* Reload timeout */
                timeout = current_time + BUTTON_TIMEOUT;
            }

            SENSIT_API_sleep(TRUE);
            /* Debounce wait */
            SENSIT_API_wait(5);

            SENSIT_API_get_current_time(&current_time);
        }
    }
    else
    {
        /* Button is not pressed. Exit function. */
        count = BUTTON_LAST;
    }

    return count;
}

/*******************************************************************/
