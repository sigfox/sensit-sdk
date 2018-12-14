/*!******************************************************************
 * \file ltr329.h
 * \brief Light sensor
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * This file provide sample code to use Light sensor (ref: LTR329ALS).<BR>
 * If you want to use other functionalities of the sensor, please refer
 * to the datasheet:
 * http://optoelectronics.liteon.com/upload/download/DS86-2014-0006/LTR-329ALS-01_DS_V1.pdf
 *******************************************************************/


/*!******************************************************************
 * \defgroup LTR329_REG LTR329 Registers
 * \brief Address of LTR329 registers
 *
 *  @{
 *******************************************************************/
#define LTR329_ALS_CONTR                   0x80 /*!< ALS operation mode control SW reset */
#define LTR329_ALS_MEAS_RATE               0x85 /*!< ALS measurement rate in active mode */
#define LTR329_PART_ID                     0x86 /*!< Part Number ID and Revision ID */
#define LTR329_MANUFAC_ID                  0x87 /*!< Manufacturer ID */
#define LTR329_ALS_DATA_CH1_0              0x88 /*!< ALS measurement CH1 data, lower byte */
#define LTR329_ALS_DATA_CH1_1              0x89 /*!< ALS measurement CH1 data, upper byte */
#define LTR329_ALS_DATA_CH0_0              0x8A /*!< ALS measurement CH0 data, lower byte */
#define LTR329_ALS_DATA_CH0_1              0x8B /*!< ALS measurement CH0 data, upper byte */
#define LTR329_ALS_STATUS                  0x8C /*!< ALS new data status */
/**@}*/


/*!******************************************************************
 * \defgroup LTR329_ERR_CODES LTR329 Error Codes
 * \brief Error code definitions for LTR329
 *
 *  @{
 *******************************************************************/
#define LTR329_ERR_NONE                    0x00 /*!< No error */

#define LTR329_ERR_I2C                     0x40 /*!< Error on I2C communication */
#define LTR329_ERR_ID                      0x41 /*!< Bad ID value */
#define LTR329_ERR_GAIN                    0x42 /*!< Gain has an invalid value */
#define LTR329_ERR_MEASURE_TIMEOUT         0x43 /*!< Error, measurement is too long */
/**@}*/


/*!******************************************************************
 * \enum ltr329_gain_e
 * \brief Setting for light sensor gain.
 *******************************************************************/
typedef enum {
    LTR329_GAIN_1X       = 0b000, /*!< Gain x1 -> range: 1 lux to 64k lux */
    LTR329_GAIN_2X       = 0b001, /*!< Gain x2 -> range: 0.5 lux to 32k lux */
    LTR329_GAIN_4X       = 0b010, /*!< Gain x4 -> range: 0.25 lux to 16k lux */
    LTR329_GAIN_8X       = 0b011, /*!< Gain x8 -> range: 0.125 lux to 8k lux */
    LTR329_GAIN_INVALID0 = 0b100, /*!< Invalid gain value */
    LTR329_GAIN_INVALID1 = 0b101, /*!< Invalid gain value */
    LTR329_GAIN_48X      = 0b110, /*!< Gain x48 -> range: 0.02 lux to 1.3k lux */
    LTR329_GAIN_96X      = 0b111, /*!< Gain x96 -> range: 0.01 lux to 600 lux */
    LTR329_GAIN_LAST
} ltr329_gain_e;


/*!******************************************************************
 * \defgroup LTR329_API LTR329 APIs
 * \brief Light sensor sample code functions
 *
 *  @{
 *******************************************************************/

/*!******************************************************************
 * \fn error_t LTR329_init(void)
 * \brief Configure sensor with measurement rate of 2s &
 * integration time of 50ms.<BR>
 * Sensor is in stand-by mode.
 *
 * \retval LTR329_ERR_NONE:                No error
 * \retval LTR329_ERR_I2C:                 Error on I2C communication
 * \retval LTR329_ERR_ID:                  Bad ID value
 *******************************************************************/
error_t LTR329_init(void);

/*!******************************************************************
 * \fn error_t LTR329_set_standby_mode(void)
 * \brief Put sensor in stand-by mode.
 *
 * \retval LTR329_ERR_NONE:                No error
 * \retval LTR329_ERR_I2C:                 Error on I2C communication
 *******************************************************************/
error_t LTR329_set_standby_mode(void);

/*!******************************************************************
 * \fn error_t LTR329_set_active_mode(ltr329_gain_e gain)
 * \brief Put sensor in active mode & configure sensor gain.
 *
 * \param[in] gain                         Light measurement gain
 *
 * \retval LTR329_ERR_NONE:                No error
 * \retval LTR329_ERR_I2C:                 Error on I2C communication
 * \retval LTR329_ERR_GAIN:                Gain has an invalid value
 *******************************************************************/
error_t LTR329_set_active_mode(ltr329_gain_e gain);

/*!******************************************************************
 * \fn error_t LTR329_measure(u16* light_ch0, u16* light_ch1)
 * \brief Get a light measurement.<BR>
 * Values must be divided by the configured gain to convert it in lux.
 *
 * \param[out] light_ch0                   Light level on channel 0 (visible)
 * \param[out] light_ch1                   Light level on channel 1 (infrared)
 *
 * \retval LTR329_ERR_NONE:                No error
 * \retval LTR329_ERR_I2C:                 Error on I2C communication
 * \retval LTR329_ERR_MEASURE_TIMEOUT:     Error, measurement is too long
 *******************************************************************/
error_t LTR329_measure(u16* light_ch0,
                       u16* light_ch1);

/**@}*/
