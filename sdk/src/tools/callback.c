/*!******************************************************************
 * \file callback.c
 * \brief Callbacks from Sens'it SDK library
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "serial.h"
#include "AT_parser.h"


/*******************************************************************/

void CALLBACK_report_test_result(bool status, s16 rssi)
{
#ifdef TEST_MODE
    u8 j = 0;
    u8 str[5];

    /* Print status */
    SERIAL_put_data((u8*)"STATUS=", 7);
    AT_itoa((int)status, (char*)str, 10);
    SERIAL_put_data(str, 1);
    SERIAL_put_data((u8*)",", 1);

    /* Print RSSI */
    SERIAL_put_data((u8*)"RSSI=", 5);
    AT_itoa((int)rssi, (char*)str, 10);
    while (str[j] != '\0')
    {
        SERIAL_put_data(str+j,1);
        j++;
    }
    SERIAL_put_data((u8*)"\r", 1);
#endif
}

/*******************************************************************/
