/*!******************************************************************
 * \file fxos8700.h
 * \brief Acceleromter & Magnetometer
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * This file provide sample code to use Light sensor (ref: FXOS8700CQ).<BR>
 * If you want to use other functionalities of the sensor, please refer
 * to the datasheet:
 * https://www.nxp.com/docs/en/data-sheet/FXOS8700CQ.pdf
 *******************************************************************/


/*!******************************************************************
 * \defgroup FXOS8700_REG FXOS8700 Registers
 * \brief Address of FXOS8700 registers
 *
 *  @{
 *******************************************************************/
#define FXOS8700_STATUS                    0x00 /*!< Real-time data-ready status or FIFO status */

#define FXOS8700_OUT_X_MSB                 0x01 /*!< [7:0] are 8 MSBs of 14-bit sample */
#define FXOS8700_OUT_X_LSB                 0x02 /*!< [7:2] are 6 LSBs of 14-bit real-time sample */
#define FXOS8700_OUT_Y_MSB                 0x03 /*!< [7:0] are 8 MSBs of 14-bit sample */
#define FXOS8700_OUT_Y_LSB                 0x04 /*!< [7:2] are 6 LSBs of 14-bit real-time sample */
#define FXOS8700_OUT_Z_MSB                 0x05 /*!< [7:0] are 8 MSBs of 14-bit sample */
#define FXOS8700_OUT_Z_LSB                 0x06 /*!< [7:2] are 6 LSBs of 14-bit real-time sample */

#define FXOS8700_F_SETUP                   0x09 /*!< FIFO setup */
#define FXOS8700_TRIG_CFG                  0x0A /*!< FIFO event trigger configuration register */
#define FXOS8700_SYSMOD                    0x0B /*!< Current system mode */
#define FXOS8700_INT_SOURCE                0x0C /*!< Interrupt status */
#define FXOS8700_WHO_AM_I                  0x0D /*!< Device ID */
#define FXOS8700_XYZ_DATA_CFG              0x0E /*!< Acceleration dynamic range and filter enable settings */
#define FXOS8700_HP_FILTER_CUTOFF          0x0F /*!< Pulse detection high-pass and low-pass filter enable bits. High-pass filter cutoff frequency selection */

#define FXOS8700_PL_STATUS                 0x10 /*!< Landscape/portrait orientation status */
#define FXOS8700_PL_CFG                    0x11 /*!< Landscape/portrait configuration */
#define FXOS8700_PL_COUNT                  0x12 /*!< Landscape/portrait debounce counter */
#define FXOS8700_PL_BF_ZCOMP               0x13 /*!< Back/front trip angle threshold */
#define FXOS8700_PL_THS_REG                0x14 /*!< Portrait to landscape trip threshold angle and hysteresis settings */

#define FXOS8700_A_FFMT_CFG                0x15 /*!< Freefall/motion function configuration */
#define FXOS8700_A_FFMT_SRC                0x16 /*!< Freefall/motion event source register */
#define FXOS8700_A_FFMT_THS                0x17 /*!< Freefall/motion threshold register */
#define FXOS8700_A_FFMT_COUNT              0x18 /*!< Freefall/motion debounce counter */

#define FXOS8700_TRANSIENT_CFG             0x1D /*!< FIFO setup */
#define FXOS8700_TRANSIENT_SRC             0x1E /*!< Transient event status register */
#define FXOS8700_TRANSIENT_THS             0x1F /*!< Transient event threshold */
#define FXOS8700_TRANSIENT_COUNT           0x20 /*!< Transient debounce counter */

#define FXOS8700_PULSE_CFG                 0x21 /*!< Pulse function configuration */
#define FXOS8700_PULSE_SRC                 0x22 /*!< Pulse function source register */
#define FXOS8700_PULSE_THSX                0x23 /*!< X-axis pulse threshold */
#define FXOS8700_PULSE_THSY                0x24 /*!< Y-axis pulse threshold */
#define FXOS8700_PULSE_THSZ                0x25 /*!< Z-axis pulse threshold */
#define FXOS8700_PULSE_TMLT                0x26 /*!< Time limit for pulse detection */
#define FXOS8700_PULSE_LTCY                0x27 /*!< Latency time for second pulse detection */
#define FXOS8700_PULSE_WIND                0x28 /*!< Window time for second pulse detection */

#define FXOS8700_ASLP_COUNT                0x29 /*!< In activity counter setting for auto-sleep */

#define FXOS8700_CTRL_REG1                 0x2A /*!< System ODR, accelerometer OSR, operating mode */
#define FXOS8700_CTRL_REG2                 0x2B /*!< Self-test, reset, accelerometer OSR and sleep mode settings */
#define FXOS8700_CTRL_REG3                 0x2C /*!< Sleep mode interrupt wake enable, interrupt polarity, push-pull/open-drain configuration */
#define FXOS8700_CTRL_REG4                 0x2D /*!< Interrupt enable register */
#define FXOS8700_CTRL_REG5                 0x2E /*!< Interrupt pin (INT1/INT2) map */

#define FXOS8700_OFF_X                     0x2F /*!< X-axis accelerometer offset adjust */
#define FXOS8700_OFF_Y                     0x30 /*!< Y-axis accelerometer offset adjust */
#define FXOS8700_OFF_Z                     0x31 /*!< Z-axis accelerometer offset adjust */

#define FXOS8700_M_DR_STATUS               0x32 /*!< Magnetic data ready */
#define FXOS8700_M_OUT_X_MSB               0x33 /*!< MSB of 16-bit magnetic data for X-axis */
#define FXOS8700_M_OUT_X_LSB               0x34 /*!< LSB of 16-bit magnetic data for X-axis */
#define FXOS8700_M_OUT_Y_MSB               0x35 /*!< MSB of 16-bit magnetic data for Y-axis */
#define FXOS8700_M_OUT_Y_LSB               0x36 /*!< LSB of 16-bit magnetic data for Y-axis */
#define FXOS8700_M_OUT_Z_MSB               0x37 /*!< MSB of 16-bit magnetic data for Z-axis */
#define FXOS8700_M_OUT_Z_LSB               0x38 /*!< LSB of 16-bit magnetic data for Z-axis */

#define FXOS8700_CMP_X_MSB                 0x39 /*!< Bits [13:8] of integrated X-axis accerleration data */
#define FXOS8700_CMP_X_LSB                 0x3A /*!< Bits [7:0] of integrated X-axis accerleration data */
#define FXOS8700_CMP_Y_MSB                 0x3B /*!< Bits [13:8] of integrated Y-axis accerleration data */
#define FXOS8700_CMP_Y_LSB                 0x3C /*!< Bits [7:0] of integrated Y-axis accerleration data */
#define FXOS8700_CMP_Z_MSB                 0x3D /*!< Bits [13:8] of integrated Z-axis accerleration data */
#define FXOS8700_CMP_Z_LSB                 0x3E /*!< Bits [7:0] of integrated Z-axis accerleration data */

#define FXOS8700_M_OFF_X_MSB               0x3F /*!< MSB of magnetometer of X-axis offset */
#define FXOS8700_M_OFF_X_LSB               0x40 /*!< LSB of magnetometer of X-axis offset */
#define FXOS8700_M_OFF_Y_MSB               0x41 /*!< MSB of magnetometer of Y-axis offset */
#define FXOS8700_M_OFF_Y_LSB               0x42 /*!< LSB of magnetometer of Y-axis offset */
#define FXOS8700_M_OFF_Z_MSB               0x43 /*!< MSB of magnetometer of Z-axis offset */
#define FXOS8700_M_OFF_Z_LSB               0x44 /*!< LSB of magnetometer of Z-axis offset */

#define FXOS8700_MAX_X_MSB                 0x45 /*!< Magnetometer X-axis maximum value MSB */
#define FXOS8700_MAX_X_LSB                 0x46 /*!< Magnetometer X-axis maximum value LSB */
#define FXOS8700_MAX_Y_MSB                 0x47 /*!< Magnetometer Y-axis maximum value MSB */
#define FXOS8700_MAX_Y_LSB                 0x48 /*!< Magnetometer Y-axis maximum value LSB */
#define FXOS8700_MAX_Z_MSB                 0x49 /*!< Magnetometer Z-axis maximum value MSB */
#define FXOS8700_MAX_Z_LSB                 0x4A /*!< Magnetometer Z-axis maximum value LSB */
#define FXOS8700_MIN_X_MSB                 0x4B /*!< Magnetometer X-axis minimum value MSB */
#define FXOS8700_MIN_X_LSB                 0x4C /*!< Magnetometer X-axis minimum value LSB */
#define FXOS8700_MIN_Y_MSB                 0x4D /*!< Magnetometer Y-axis minimum value MSB */
#define FXOS8700_MIN_Y_LSB                 0x4E /*!< Magnetometer Y-axis minimum value LSB */
#define FXOS8700_MIN_Z_MSB                 0x4F /*!< Magnetometer Z-axis minimum value MSB */
#define FXOS8700_MIN_Z_LSB                 0x50 /*!< Magnetometer Z-axis minimum value LSB */

#define FXOS8700_TEMP                      0x51 /*!< Device temperature, valid range of –128 to 127 °C */

#define FXOS8700_M_THS_CFG                 0x52 /*!< Magnetic threshold detection function configuration */
#define FXOS8700_M_THS_SRC                 0x53 /*!< Magnetic threshold event source register */
#define FXOS8700_M_THS_X_MSB               0x54 /*!< X-axis magnetic threshold MSB */
#define FXOS8700_M_THS_X_LSB               0x55 /*!< X-axis magnetic threshold LSB */
#define FXOS8700_M_THS_Y_MSB               0x56 /*!< Y-axis magnetic threshold MSB */
#define FXOS8700_M_THS_Y_LSB               0x57 /*!< Y-axis magnetic threshold LSB */
#define FXOS8700_M_THS_Z_MSB               0x58 /*!< Z-axis magnetic threshold MSB */
#define FXOS8700_M_THS_Z_LSB               0x59 /*!< Z-axis magnetic threshold LSB */
#define FXOS8700_M_THS_COUNT               0x5A /*!< Magnetic threshold debounce counter */

#define FXOS8700_M_CTRL_REG1               0x5B /*!< Control for magnetic sensor functions */
#define FXOS8700_M_CTRL_REG2               0x5C /*!< Control for magnetic sensor functions */
#define FXOS8700_M_CTRL_REG3               0x5D /*!< Control for magnetic sensor functions */
#define FXOS8700_M_INT_SRC                 0x5E /*!< Magnetic interrupt source */

#define FXOS8700_A_VECM_CFG                0x5F /*!< Acceleration vector-magnitude configuration register */
#define FXOS8700_A_VECM_THS_MSB            0x60 /*!< Acceleration vector-magnitude threshold MSB */
#define FXOS8700_A_VECM_THS_LSB            0x61 /*!< Acceleration vector-magnitude threshold LSB */
#define FXOS8700_A_VECM_CNT                0x62 /*!< Acceleration vector-magnitude debounce count */
#define FXOS8700_A_VECM_INITX_MSB          0x63 /*!< Acceleration vector-magnitude X-axis reference value MSB */
#define FXOS8700_A_VECM_INITX_LSB          0x64 /*!< Acceleration vector-magnitude X-axis reference value LSB */
#define FXOS8700_A_VECM_INITY_MSB          0x65 /*!< Acceleration vector-magnitude Y-axis reference value MSB */
#define FXOS8700_A_VECM_INITY_LSB          0x66 /*!< Acceleration vector-magnitude Y-axis reference value LSB */
#define FXOS8700_A_VECM_INITZ_MSB          0x67 /*!< Acceleration vector-magnitude Z-axis reference value MSB */
#define FXOS8700_A_VECM_INITZ_LSB          0x68 /*!< Acceleration vector-magnitude Z-axis reference value LSB */

#define FXOS8700_M_VECM_CFG                0x69 /*!< Magnetic vector-magnitude configuration register */
#define FXOS8700_M_VECM_THS_MSB            0x6A /*!< Magnetic vector-magnitude threshold MSB */
#define FXOS8700_M_VECM_THS_LSB            0x6B /*!< Magnetic vector-magnitude threshold LSB */
#define FXOS8700_M_VECM_CNT                0x6C /*!< Magnetic vector-magnitude debounce count */
#define FXOS8700_M_VECM_INITX_MSB          0x6D /*!< Magnetic vector-magnitude reference value X-axis MSB */
#define FXOS8700_M_VECM_INITX_LSB          0x6E /*!< Magnetic vector-magnitude reference value X-axis LSB */
#define FXOS8700_M_VECM_INITY_MSB          0x6F /*!< Magnetic vector-magnitude reference value Y-axis MSB */
#define FXOS8700_M_VECM_INITY_LSB          0x70 /*!< Magnetic vector-magnitude reference value Y-axis LSB */
#define FXOS8700_M_VECM_INITZ_MSB          0x71 /*!< Magnetic vector-magnitude reference value Z-axis MSB */
#define FXOS8700_M_VECM_INITZ_LSB          0x72 /*!< Magnetic vector-magnitude reference value Z-axis LSB */

#define FXOS8700_A_FFMT_THS_X_MSB          0x73 /*!< X-axis FMT threshold MSB */
#define FXOS8700_A_FFMT_THS_X_LSB          0x74 /*!< X-axis FMT threshold LSB */
#define FXOS8700_A_FFMT_THS_Y_MSB          0x75 /*!< Y-axis FMT threshold MSB */
#define FXOS8700_A_FFMT_THS_Y_LSB          0x76 /*!< Y-axis FMT threshold LSB */
#define FXOS8700_A_FFMT_THS_Z_MSB          0x77 /*!< Z-axis FMT threshold MSB */
#define FXOS8700_A_FFMT_THS_Z_LSB          0x78 /*!< Z-axis FMT threshold LSB */
/**@}*/


/*!******************************************************************
 * \defgroup FXOS8700_ERR_CODES FXOS8700 Error Codes
 * \brief Error code definitions for FXOS8700
 *
 *  @{
 *******************************************************************/
#define FXOS8700_ERR_NONE                  0x00 /*!< No error */

#define FXOS8700_ERR_I2C                   0x50 /*!< Error on I2C communication */
#define FXOS8700_ERR_ID                    0x51 /*!< Bad ID value */
#define FXOS8700_ERR_RANGE                 0x51 /*!< Invalid range value */
/**@}*/


/*!******************************************************************
 * \enum fxos8700_range_e
 * \brief Setting for accelerometer range.
 *******************************************************************/
typedef enum {
    FXOS8700_RANGE_2G = 0b00, /*!< Range +/- 2g , Sensitivity ±0.244 mg/LSB */
    FXOS8700_RANGE_4G = 0b01, /*!< Range +/- 4g , Sensitivity ±0.488 mg/LSB */
    FXOS8700_RANGE_8G = 0b10, /*!< Range +/- 8g , Sensitivity ±0.976 mg/LSB */
    FXOS8700_RANGE_LAST
} fxos8700_range_e;


/*!******************************************************************
 * \struct fxos8700_data_s
 * \brief Data structure for acceleration & magnetic data.
 *
 * For acceleration convert values in g with the LSB resolution of
 * the configured acceleration range.
 *******************************************************************/
typedef struct {
    s16 x; /*!< Data on X-axis */
    s16 y; /*!< Data on Y-axis */
    s16 z; /*!< Data on Z-axis */
} fxos8700_data_s;


/*!******************************************************************
 * \defgroup FXOS8700_API FXOS8700 APIs
 * \brief Accelerometer sample code functions
 *
 *  @{
 *******************************************************************/

/*!******************************************************************
 * \fn error_t FXOS8700_init(void)
 * \brief Reset accelerometer & Check part ID.
 *
 * \retval FXOS8700_ERR_NONE:              No error
 * \retval FXOS8700_ERR_I2C:               Error on I2C communication
 * \retval FXOS8700_ERR_ID:                Bad ID value
 *******************************************************************/
error_t FXOS8700_init(void);

/*!******************************************************************
 * \fn error_t FXOS8700_reset(void)
 * \brief Reset accelerometer registers seting.
 *
 * \warning When reseting accelerometer, you may have the error:
 * \link SENSIT_ERR_I2C_TIMEOUT \endlink. You can ignore it.
 *
 * \retval FXOS8700_ERR_NONE:              No error
 * \retval FXOS8700_ERR_I2C:               Error on I2C communication
 *******************************************************************/
error_t FXOS8700_reset(void);

/*!******************************************************************
 * \fn error_t FXOS8700_set_standby_mode(void)
 * \brief Put accelerometer in stand-by mode & Disable interrupt.
 *
 * \retval FXOS8700_ERR_NONE:              No error
 * \retval FXOS8700_ERR_I2C:               Error on I2C communication
 *******************************************************************/
error_t FXOS8700_set_standby_mode(void);

/*!******************************************************************
 * \fn error_t FXOS8700_set_transient_mode(fxos8700_range_e range, u8 threshold, u8 count)
 * \brief Put accelerometer in transient mode.
 *
 * \param[in] range                        Acceleration measurement range
 * \param[in] threshold                    Acceleration threshold, resolution depend of range
 * \param[in] count                        Number of event to trigger an interrupt
 *
 * \retval FXOS8700_ERR_NONE:              No error
 * \retval FXOS8700_ERR_I2C:               Error on I2C communication
 * \retval FXOS8700_ERR_RANGE:             Invalid range value
 *******************************************************************/
error_t FXOS8700_set_transient_mode(fxos8700_range_e range,
                                    u8 threshold,
                                    u8 count);

/*!******************************************************************
 * \fn error_t FXOS8700_clear_transient_interrupt(bool* flag)
 * \brief Read transient mode interrupt register.
 *
 * \param[out] flag                        TRUE if a transient event has been triggered, otherwise FALSE
 *
 * \retval FXOS8700_ERR_NONE:              No error
 * \retval FXOS8700_ERR_I2C:               Error on I2C communication
 *******************************************************************/
error_t FXOS8700_clear_transient_interrupt(bool* flag);

/*!******************************************************************
 * \fn error_t FXOS8700_read_acceleration(fxos8700_data_s* acc)
 * \brief Read acceleration data.
 *
 * \param[out] acc                         Acceleration of the 3-axis
 *
 * \retval FXOS8700_ERR_NONE:              No error
 * \retval FXOS8700_ERR_I2C:               Error on I2C communication
 *******************************************************************/
error_t FXOS8700_read_acceleration(fxos8700_data_s* acc);

/**@}*/
