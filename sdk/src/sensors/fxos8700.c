/*!******************************************************************
 * \file fxos8700.c
 * \brief Acceleromter & Magnetometer
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * This file provide sample code to use Light sensor (ref: FXOS8700CQ).<BR>
 * If you want to use other functionalities of the sensor, please refer
 * to the datasheet:
 * https://www.nxp.com/docs/en/data-sheet/FXOS8700CQ.pdf
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "fxos8700.h"


/******** DEFINES **************************************************/
#define FXOS8700_ID                        0xC7


/*******************************************************************/

error_t FXOS8700_init(void)
{
    error_t err;
    u8 buffer[2];

    /* Reset sensor */
    err = FXOS8700_reset();
    if (err != FXOS8700_ERR_NONE)
    {
        return err;
    }

    /* Check who am I */
    buffer[0] = FXOS8700_WHO_AM_I;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 1, 1);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    if (buffer[1] != FXOS8700_ID)
    {
        return FXOS8700_ERR_ID;
    }

    return FXOS8700_ERR_NONE;
}

/*******************************************************************/

error_t FXOS8700_reset(void)
{
    error_t err;
    u8 buffer[2];

    /* Reset sensor */
    buffer[0] = FXOS8700_CTRL_REG2;
    buffer[1] = 0b01000000;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    /* The reset of the accelerometer will cause a I2C write error code */
    if (err == SENSIT_ERR_I2C_WRITE)
    {
        /* Wait at least 1ms */
        SENSIT_API_wait(2);
        return FXOS8700_ERR_NONE;
    }
    else
    {
        return FXOS8700_ERR_I2C;
    }
}

/*******************************************************************/

error_t FXOS8700_set_standby_mode(void)
{
    error_t err;
    u8 buffer[2];

    /* Put sensor in stand-by mode */
    buffer[0] = FXOS8700_CTRL_REG1;
    buffer[1] = 0x00;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    /* Disable FXOS8700 interrupt */
    SENSIT_API_configure_fxos8700_interrupt(FALSE);

    return FXOS8700_ERR_NONE;
}

/*******************************************************************/

error_t FXOS8700_set_transient_mode(fxos8700_range_e range, u8 threshold, u8 count)
{
    error_t err;
    u8 buffer[2];

    /* Reset sensor */
    err = FXOS8700_reset();
    if (err != FXOS8700_ERR_NONE)
    {
        return err;
    }

    if (range >= FXOS8700_RANGE_LAST)
    {
        /* Range is invalid */
        return FXOS8700_ERR_RANGE;
    }

    /* Set data range */
    buffer[0] = FXOS8700_XYZ_DATA_CFG;
    buffer[1] = 0x10 | range; /* Enable high-pass filter on acceleration output data
                               * Configure range */
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    /* Configure Transient mode */
    buffer[0] = FXOS8700_TRANSIENT_CFG;
    buffer[1] = 0b00011110; /* Event flag latch enabled
                             * Z-axis event detection enabled
                             * Y-axis event detection enabled
                             * X-axis event detection enabled */
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    /* Set transient mode threshold */
    buffer[0] = FXOS8700_TRANSIENT_THS;
    buffer[1] = 0x80 | ( 0x7F & threshold); /* Clears debounce counter when the transient event condition is not true during the current ODR period. */
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    /* Set transient mode debounce counter */
    buffer[0] = FXOS8700_TRANSIENT_COUNT;
    buffer[1] = count;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    /* Enable transient interrupt */
    buffer[0] = FXOS8700_CTRL_REG4;
    buffer[1] = 0b00100000;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    /* Route Interrupt to INT1 pin */
    buffer[0] = FXOS8700_CTRL_REG5;
    buffer[1] = 0b00100000;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    /* Set accelerometer in low power mode */
    buffer[0] = FXOS8700_CTRL_REG2;
    buffer[1] = 0b00000011; /* Low power mode */
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    /* Set Output Data Rate & Put accelerometer in active mode */
    buffer[0] = FXOS8700_CTRL_REG1;
    buffer[1] = 0b00111001; /* Output Data Rate = 1.5625 Hz
                             * Active mode */
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 2, 0);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    /* Enable FXOS8700 interrupt */
    SENSIT_API_configure_fxos8700_interrupt(TRUE);

    return FXOS8700_ERR_NONE;
}

/******************************************************************************/

error_t FXOS8700_clear_transient_interrupt(bool* flag)
{
    error_t err;
    u8 buffer[2];

    /* Read transient interrupt register */
    buffer[0] = FXOS8700_TRANSIENT_SRC;
    err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 1, 1);
    if (err != SENSIT_ERR_NONE)
    {
        return FXOS8700_ERR_I2C;
    }

    *flag = buffer[1]?TRUE:FALSE;

    return FXOS8700_ERR_NONE;
}

/*******************************************************************/

error_t FXOS8700_read_acceleration(fxos8700_data_s* acc)
{
    error_t err;
    u8 buffer[2];
    u8 iter;
    u8 data[6];

    /* Get measurement data */
    for ( iter = 0 ; iter < 6 ; iter++)
    {
        buffer[0] = FXOS8700_OUT_X_MSB + iter;
        err = SENSIT_API_write_read_i2c_bus(SENSOR_I2C_ADDR_FXOS8700, buffer, 1, 1);
        if (err != SENSIT_ERR_NONE)
        {
            return FXOS8700_ERR_I2C;
        }
        data[iter] = buffer[1];
    }

    (*acc).x = data[0];
    (*acc).x <<= 8;
    (*acc).x |= (0x00FF & data[1]);

    (*acc).y = data[2];
    (*acc).y <<= 8;
    (*acc).y |= (0x00FF & data[3]);

    (*acc).z = data[4];
    (*acc).z <<= 8;
    (*acc).z |= (0x00FF & data[5]);

    return FXOS8700_ERR_NONE;
}

/*******************************************************************/
