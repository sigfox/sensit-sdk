/*!******************************************************************
 * \file serial.c
 * \brief Generic function to use USB or UART
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * To use the USB communication, use -DUSB in the compilation flags.
 * To use the UART communication, use -DUART in the compilation flags.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "serial.h"


/*******************************************************************/

void SERIAL_init(void)
{
#ifdef USB
    /* Initialize USB communication */
    SENSIT_API_init_usb();
#elif UART
    /* Initialize UART communication */
    SENSIT_API_init_uart();
#else
#error "Serial communication not defined!"
#endif
}

/*******************************************************************/

error_t SERIAL_get_data(u8* buffer, u8 size, u8* index)
{
    error_t err;

    /* Set buffer index to 0 */
    *index = 0;

    for ( (*index) = 0 ; (*index) < size ; (*index)++)
    {
#ifdef USB
        err = SENSIT_API_get_data_from_usb(buffer + (*index));
        if (err == SENSIT_ERR_USB_EMPTY)
        {
            /* No more data to read */
            return SERIAL_ERR_NONE;
        }
#elif UART
        err = SENSIT_API_get_data_from_uart(buffer + (*index));
        if (err == SENSIT_ERR_UART_EMPTY)
        {
            /* No more data to read */
            return SERIAL_ERR_NONE;
        }
#else
#error "Serial communication not defined!"
#endif
        /* Wait 1ms to not read buffer too fast */
        SENSIT_API_wait(1);
    }

    return SERIAL_ERR_OVERLOAD;
}

/*******************************************************************/

void SERIAL_put_data(u8* data, u8 size)
{
#ifdef USB
    SENSIT_API_send_data_to_usb(data, size);
#elif UART
    SENSIT_API_send_data_to_uart(data, size);
#else
#error "Communication bus not defined!"
#endif
}

/*******************************************************************/
