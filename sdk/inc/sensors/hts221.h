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


/*!******************************************************************
 * \defgroup HTS221_REG HTS221 Registers
 * \brief Address of HTS221 registers
 *
 *  @{
 *******************************************************************/
#define HTS221_WHO_AM_I                    0x0F /*!< Device identification */
#define HTS221_AV_CONF                     0x10 /*!< Humidity and temperature resolution mode */
#define HTS221_CTRL_REG1                   0x20 /*!< Control register 1 */
#define HTS221_CTRL_REG2                   0x21 /*!< Control register 2 */
#define HTS221_CTRL_REG3                   0x22 /*!< Control register 3 */
#define HTS221_STATUS_REG                  0x27 /*!< Status register */
#define HTS221_HUMIDITY_OUT_L              0x28 /*!< Relative humidity data (LSB) */
#define HTS221_HUMIDITY_OUT_H              0x29 /*!< Relative humidity data (MSB) */
#define HTS221_TEMP_OUT_L                  0x2A /*!< Temperature data (LSB) */
#define HTS221_TEMP_OUT_H                  0x2B /*!< Temperature data (MSB) */
#define HTS221_CALIBRATION                 0x30 /*!< he Registers in 0x30..0x3F address range contain calibration coefficients. */
/**@}*/


/*!******************************************************************
 * \defgroup HTS221_ERR_CODES HTS221 Error Codes
 * \brief Error code definitions for HTS221
 *
 *  @{
 *******************************************************************/
#define HTS221_ERR_NONE                    0x00 /*!< No error */

#define HTS221_ERR_I2C                     0x30 /*!< Error on I2C communication */
#define HTS221_ERR_ID                      0x31 /*!< Bad ID value */
#define HTS221_ERR_MEASURE_TIMEOUT         0x32 /*!< Error, measurement is too long */
/**@}*/


/*!******************************************************************
 * \defgroup HTS221_API HTS221 APIs
 * \brief Temperature & Relative humidity sensor sample code functions
 *
 *  @{
 *******************************************************************/

/*!******************************************************************
 * \fn error_t HTS221_init(void)
 * \brief Get calibration values & configure sensor in one-shot measurement.
 *
 * \retval HTS221_ERR_NONE:                No error
 * \retval HTS221_ERR_I2C:                 Error on I2C communication
 * \retval HTS221_ERR_ID:                  Bad ID value
 *******************************************************************/
error_t HTS221_init(void);

/*!******************************************************************
 * \fn error_t HTS221_measure(s16* temperature, u16* humidity)
 * \brief Do a measurement of temperature & relative humidity.
 *
 * \retval HTS221_ERR_NONE:                No error
 * \retval HTS221_ERR_I2C:                 Error on I2C communication
 * \retval HTS221_ERR_MEASURE_TIMEOUT:     Error, measurement is too long
 *******************************************************************/
error_t HTS221_measure(s16* temperature,
                       u16* humidity);

/**@}*/
