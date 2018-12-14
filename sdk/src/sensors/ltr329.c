/*!******************************************************************
 * \file ltr329.c
 * \brief Light sensor
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * This file provide sample code to use Light sensor (ref: LTR329ALS).<BR>
 * If you want to use other functionalities of the sensor, please refer
 * to the datasheet:
 * http://optoelectronics.liteon.com/upload/download/DS86-2014-0006/LTR-329ALS-01_DS_V1.pdf
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "ltr329.h"


/******** DEFINES **************************************************/
#define LTR329_ID                          0xA0
#define LTR329_MANUF_ID                    0x05

#define LTR329_MAX_RETRY                   3 /* Number of measurement retry */


/*******************************************************************/

error_t LTR329_init(void)
{
    error_t err;
    u8 buffer[2];

    /* Reset sensor */
    buffer[0] = LTR329_ALS_CONTR;
    buffer[1] = 0x02; /* SW reset */
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_LTR329, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return LTR329_ERR_I2C;
    }

    /* Check PART ID */
    buffer[0] = LTR329_PART_ID;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_LTR329, buffer, 1, 1);
    if (err != SENSIT_ERR_NONE)
    {
        return LTR329_ERR_I2C;
    }

    if (buffer[1] != LTR329_ID)
    {
        return LTR329_ERR_ID;
    }

    /* Configure sensor measurement rate & integration time */
    buffer[0] = LTR329_ALS_MEAS_RATE;
    buffer[1] = 0b00001101; /* Measurement rate = 2s ; Integration time = 50ms */
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_LTR329, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return LTR329_ERR_I2C;
    }

    return LTR329_ERR_NONE;
}

/*******************************************************************/

error_t LTR329_set_standby_mode(void)
{
    error_t err;
    u8 buffer[2];

    /* Set sensor in stand-by mode */
    buffer[0] = LTR329_ALS_CONTR;
    buffer[1] = 0x00;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_LTR329, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return LTR329_ERR_I2C;
    }

    return LTR329_ERR_NONE;
}

/*******************************************************************/

error_t LTR329_set_active_mode(ltr329_gain_e gain)
{
    error_t err;
    u8 buffer[2];

    if ( (gain > LTR329_GAIN_LAST) || (gain == LTR329_GAIN_INVALID0) || (gain == LTR329_GAIN_INVALID1) )
    {
        return LTR329_ERR_GAIN;
    }

    /* Set sensor in active mode */
    buffer[0] = LTR329_ALS_CONTR;
    buffer[1] = 0x01 | (gain << 3);
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_LTR329, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return LTR329_ERR_I2C;
    }

    return LTR329_ERR_NONE;
}

/*******************************************************************/

error_t LTR329_measure(u16* light_ch0, u16* light_ch1)
{
    error_t err;
    u8 buffer[2];
    u8 iter;
    u8 data[4];

    /* Wait measurement is completed */
    for ( iter = 0 ; iter < LTR329_MAX_RETRY ; iter++)
    {
        buffer[0] = LTR329_ALS_STATUS;
        err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_LTR329, buffer, 1, 1);
        if (err != SENSIT_ERR_NONE)
        {
            return LTR329_ERR_I2C;
        }

        if ( (buffer[1] & 0x04) == 0x04 )
        {
            /* Data is ready. Loop end. */
            break;
        }
        else
        {
            /* Wait */
            SENSIT_API_sleep(TRUE);
        }
    }

    if (iter == LTR329_MAX_RETRY)
    {
        return LTR329_ERR_MEASURE_TIMEOUT;
    }

    /* Get measurement data */
    for ( iter = 0 ; iter < 4 ; iter++)
    {
        buffer[0] = LTR329_ALS_DATA_CH1_0 + iter;
        err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_LTR329, buffer, 1, 1);
        if (err != SENSIT_ERR_NONE)
        {
            return LTR329_ERR_I2C;
        }
        data[iter] = buffer[1];
    }

    *light_ch1 = data[1];
    *light_ch1 <<= 8;
    *light_ch1 |= data[0];

    *light_ch0 = data[3];
    *light_ch0 <<= 8;
    *light_ch0 |= data[2];

    return LTR329_ERR_NONE;
}

/*******************************************************************/
