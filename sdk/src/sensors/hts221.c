/*!******************************************************************
 * \file hts221.h
 * \brief Temperature & Humidity sensor
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * This file provide sample code to use Temperature & Relative Humidity
 * sensor (ref: HTS221).<BR>
 * If you want to use other functionalities of the sensor, please refer
 * to the datasheet:
 * www.st.com/resource/en/datasheet/hts221.pdf
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "hts221.h"


/******** DEFINES **************************************************/
#define HTS221_AUTOINCREMENT               0x80
#define HTS221_ID                          0xBC

#define HTS221_MAX_RETRY                   3 /* Number of measurement retry */


/******* LOCAL VARIABLES *******************************************/
static s16 _calH0;
static s16 _calH1;
static s16 _calT0;
static s16 _calT1;

static s16 _t0Out;
static s16 _t1Out;
static s16 _h0Out;
static s16 _h1Out;


/*******************************************************************/

error_t HTS221_init(void)
{
    error_t err;
    u8 buffer[17];

    /* Reset sensor */
    buffer[0] = HTS221_CTRL_REG2;
    buffer[1] = 0x80;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_HTS221, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return HTS221_ERR_I2C;
    }

    /* Check who am I */
    buffer[0] = HTS221_WHO_AM_I;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_HTS221, buffer, 1, 1);
    if (err != SENSIT_ERR_NONE)
    {
        return HTS221_ERR_I2C;
    }

    if (buffer[1] != HTS221_ID)
    {
        return HTS221_ERR_ID;
    }

    /* Read calibration data */
    buffer[0] = HTS221_CALIBRATION | HTS221_AUTOINCREMENT;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_HTS221, buffer, 1, 16);
    if (err != SENSIT_ERR_NONE)
    {
        return HTS221_ERR_I2C;
    }

    _calH0 = buffer[1];
    _calH1 = buffer[2];

    _calT0 = buffer[6] & 0x3;
    _calT0 <<= 8;
    _calT0 |= buffer[3];

    _calT1 = buffer[6] & 0x0c;
    _calT1 <<= 6;
    _calT1 |= buffer[4];

    _h0Out = buffer[8];
    _h0Out <<= 8;
    _h0Out |= buffer[7];

    _h1Out = buffer[12];
    _h1Out <<= 8;
    _h1Out |= buffer[11];

    _t0Out = buffer[14];
    _t0Out <<= 8;
    _t0Out |= buffer[13];

    _t1Out = buffer[16];
    _t1Out <<= 8;
    _t1Out |= buffer[15];

    /* Configure sensor */
    buffer[0] = HTS221_CTRL_REG1;
    buffer[1] = 0x84; /* active mode, One-shot meamsurement */
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_HTS221, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return HTS221_ERR_I2C;
    }

    return HTS221_ERR_NONE;
}

/*******************************************************************/

error_t HTS221_measure(s16* temperature, u16* humidity)
{
    u8 buffer[5];
    error_t err;
    u8 iter;
    s16 hum;
    s16 temp;
    s32 compute;

    /* Start a new measurement */
    buffer[0] = HTS221_CTRL_REG2;
    buffer[1] = 0x01; /* Start a new conversion */
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_HTS221, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return HTS221_ERR_I2C;
    }

    /* Wait convertion is completed */
    for (iter = 0 ; iter < HTS221_MAX_RETRY ; iter++)
    {
        buffer[0] = HTS221_STATUS_REG;
        err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_HTS221, buffer, 1, 1);
        if (err != SENSIT_ERR_NONE)
        {
            return HTS221_ERR_I2C;
        }

        if ( (buffer[1] & 0x03) == 0x03 )
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

    if (iter == HTS221_MAX_RETRY)
    {
        return HTS221_ERR_MEASURE_TIMEOUT;
    }

    /* Read temperature & relative humidity */
    buffer[0] = HTS221_HUMIDITY_OUT_L | HTS221_AUTOINCREMENT;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_HTS221, buffer, 1, 4);
    if (err != SENSIT_ERR_NONE)
    {
        return HTS221_ERR_I2C;
    }

    /* Compute Relative humidity */
    hum = buffer[2];
    hum <<= 8;
    hum |= buffer[1];

    compute = hum - _h0Out;
    compute *= (_calH1 - _calH0);
    compute /= (_h1Out - _h0Out);

    *humidity = compute + _calH0; //in 1/2 %

    /* Compute Temperature */
    temp = buffer[4];
    temp <<= 8;
    temp |= buffer[3];

    compute = temp - _t0Out;
    compute *= (_calT1 - _calT0);
    compute /= (_t1Out - _t0Out);

    *temperature = compute + _calT0; //in 1/8 °C

    return HTS221_ERR_NONE;
}

/*******************************************************************/
