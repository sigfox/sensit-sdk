/*!******************************************************************
 * \file main_MODEM.c
 * \brief Sens'it Modem with AT commands
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * For more information on this firmware, see modem.md.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "serial.h"
#include "AT_parser.h"


/******** DEFINES **************************************************/
#define SERIAL_BUFFER_SIZE                 32


/******* GLOBAL VARIABLES ******************************************/
u8 firmware_version[] = "AT_v2.0.0";


/*******************************************************************/

int main()
{
    u8 buffer[SERIAL_BUFFER_SIZE];
    u8 index;
    error_t err;

    /* Start of initialization */

    /* Initialization of serial comunication */
    SERIAL_init();

#ifdef EXTERNAL_POWER
    /* Disable battery charger to use an extern alimentation */
    SENSIT_API_switch_battery_charger(FALSE);
#endif

#ifdef TEST_MODE
    /* Switch to Test mode credentials to use test modes */
    SENSIT_API_switch_test_mode_creedentials(TRUE);
#endif

    /* End of initialization */

    while (TRUE)
    {
        /* Execution loop */

        /* Get serial data */
        err = SERIAL_get_data(buffer, SERIAL_BUFFER_SIZE, &index);

        if ( (index != 0) && (err != SERIAL_ERR_OVERLOAD) )
        {
            /* Parse data */
            AT_parse((char*)buffer);
        }
    } /* End of while */
}

/*******************************************************************/
