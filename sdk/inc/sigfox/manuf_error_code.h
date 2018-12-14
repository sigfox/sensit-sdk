/*!******************************************************************
 * \file manuf_error_code.h
 * \brief MANUF APIs error codes definition
 * \author Sens'it Team
 * \author $(SIGFOX_LIB_AUTHOR)
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/


/*!
 * \defgroup MANUF_ERR_CODES Return Error codes definition for MANUF APIs
 *
 *  @{
 */

/* -------------------------------------------------------------------------------------------------------------------------------------
                                            IMPORTANT NOTE on ERROR CODES
   -------------------------------------------------------------------------------------------------------------------------------------

   ALL SIGFOX_API_xxx or SIGFOX_REPEATER_API_xxx functions returns an error type sfx_error_t

   The sfx_error_t is composed of the following :

     MSB_____________________________________________LSB
     15                      8|7                     0
      |                       |                      |
      |   MANUF_ERROR_CODE    |  SIGFOX_ERROR_CODE   |
      |_______________________|______________________|


   MANUF_ERROR_CODE :
      - Represents the error codes for MCU_API_xx, RF_API_xx, SE_API_xx, REPEATER_API_xx
      - All MCU_API_xx, RF_API_xx, SE_API_xx, REPEATER_API_xx have to return SFX_ERR_NONE when no error
      - Minimum set of error codes are defined into the mcu_api.h, rf_api.h, se_api.h and repeater_api.h : Manufacturer can define more error codes !

   SIGFOX_ERROR_CODE :
       - Represents the error codes of the SIGFOX API or internal functions
       - All the error codes can be found in this file ( sigfox_api.h )

   ------------------------------------------------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/* Bytes reserved for MCU API ERROR CODES : From 0x10 to 0x2F       */
/* ---------------------------------------------------------------- */

#define MCU_ERR_API_MALLOC                          (sfx_u8)(0x11) /*!< Error on MCU_API_malloc */
#define MCU_ERR_API_FREE                            (sfx_u8)(0x12) /*!< Error on MCU_API_free */
#define MCU_ERR_API_VOLT_TEMP                       (sfx_u8)(0x13) /*!< Error on MCU_API_get_voltage_temperature */
#define MCU_ERR_API_DLY                             (sfx_u8)(0x14) /*!< Error on MCU_API_delay */
#define MCU_ERR_API_AES                             (sfx_u8)(0x15) /*!< Error on MCU_API_aes_128_cbc_encrypt */
#define MCU_ERR_API_GETNVMEM                        (sfx_u8)(0x16) /*!< Error on MCU_API_get_nv_mem */
#define MCU_ERR_API_SETNVMEM                        (sfx_u8)(0x17) /*!< Error on MCU_API_set_nv_mem */
#define MCU_ERR_API_TIMER_START                     (sfx_u8)(0x18) /*!< Error on MCU_API_timer_start */
#define MCU_ERR_API_TIMER_START_CS                  (sfx_u8)(0x19) /*!< Error on MCU_API_timer_start_carrier_sense */
#define MCU_ERR_API_TIMER_STOP_CS                   (sfx_u8)(0x1A) /*!< Error on MCU_API_timer_stop_carrier_sense */
#define MCU_ERR_API_TIMER_STOP                      (sfx_u8)(0x1B) /*!< Error on MCU_API_timer_stop */
#define MCU_ERR_API_TIMER_END                       (sfx_u8)(0x1C) /*!< Error on MCU_API_timer_wait_for_end */
#define MCU_ERR_API_TEST_REPORT                     (sfx_u8)(0x1D) /*!< Error on MCU_API_report_test_result */
#define MCU_ERR_API_GET_VERSION                     (sfx_u8)(0x1E) /*!< Error on MCU_API_get_version */
#define MCU_ERR_API_GET_ID                          (sfx_u8)(0x1F) /*!< Error on MCU_API_get_device_id */
#define MCU_ERR_API_GET_PAC                         (sfx_u8)(0x20) /*!< Error on MCU_API_get_initial_pac */

/* ---------------------------------------------------------------- */
/* Bytes reserved for RF API ERROR CODES : From 0x30 to 0x3F        */
/* ---------------------------------------------------------------- */

#define RF_ERR_API_INIT                             (sfx_u8)(0x30) /*!< Error on RF_API_init */
#define RF_ERR_API_SEND                             (sfx_u8)(0x31) /*!< Error on RF_API_send */
#define RF_ERR_API_CHANGE_FREQ                      (sfx_u8)(0x32) /*!< Error on RF_API_change_frequency */
#define RF_ERR_API_STOP                             (sfx_u8)(0x33) /*!< Error on RF_API_stop */
#define RF_ERR_API_WAIT_FRAME                       (sfx_u8)(0x34) /*!< Error on RF_API_wait_frame */
#define RF_ERR_API_WAIT_CLEAR_CHANNEL               (sfx_u8)(0x35) /*!< Error on RF_API_wait_for_clear_channel */
#define RF_ERR_API_START_CONTINUOUS_TRANSMISSION    (sfx_u8)(0x36) /*!< Error on RF_API_start_continuous_transmission */
#define RF_ERR_API_STOP_CONTINUOUS_TRANSMISSION     (sfx_u8)(0x37) /*!< Error on RF_API_stop_continuous_transmission */
#define RF_ERR_API_GET_VERSION                      (sfx_u8)(0x38) /*!< Error on RF_API_get_version */

/* ---------------------------------------------------------------- */
/* Bytes reserved for SE API ERROR CODES : From 0x40 to 0x5F        */
/* ---------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/* Bytes reserved for REPEATER API ERROR CODES : From 0x60 to 0x7F  */
/* ---------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/* Bytes reserved for MONARCH API ERROR CODES : From 0x80 to 0x8F   */
/* ---------------------------------------------------------------- */

/* ---------------------------------------------------------------------- */
/* Bytes reserved for DEVICE CONFIG API ERROR CODES : From 0x90 to 0x9A   */
/* ---------------------------------------------------------------------- */

/** @}*/
