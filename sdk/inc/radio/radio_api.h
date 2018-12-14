/*!******************************************************************
 * \file radio_api.h
 * \brief Sigfox APIs implementation for the Sens'it
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/


/*!******************************************************************
 * \defgroup RADIO_ERR_CODES Radio Error Codes
 * \brief Error code definitions for RADIO APIs
 *
 *  @{
 *******************************************************************/
#define RADIO_ERR_NONE                     0x00 /*!< No error */

#define RADIO_ERR_CONFIGURE_RADIO          0x20 /*!< Failed to configure Sens'it radio */
#define RADIO_ERR_OPEN                     0x21 /*!< Failed to open Sigfox library */
#define RADIO_ERR_SET_STD_CONFIG           0x22 /*!< Failed to configure Sigfox library */
#define RADIO_ERR_SWITCH_ON                0x23 /*!< Failed to switch radio ON */
#define RADIO_ERR_DUTY_CYCLE               0x24 /*!< Transmission not allowed, duty cycle limit reach (RC1 only) */
#define RADIO_ERR_NO_CHANNEL               0x25 /*!< Transmission not allowed, no available channel (RC2 & RC4 only) */
#define RADIO_ERR_LBT                      0x26 /*!< Transmission not allowed, channel occupied (RC3 only) */
#define RADIO_ERR_SEND                     0x27 /*!< SIGFOX_API_send_frame internal error */
#define RADIO_ERR_RECEIVE                  0x28 /*!< No downlink message received */
#define RADIO_ERR_NVMEM                    0x29 /*!< Error during NVMEM storage */
/**@}*/


/*!******************************************************************
 * \defgroup RADIO_API Radio APIs
 * \brief Sigfox APIs implementation for the Sens'it
 *
 *  @{
 *******************************************************************/

/*!******************************************************************
 * \fn error_t RADIO_API_init(void)
 * \brief Initialize Sens'it radio & Sigfox library.
 *
 * \retval RADIO_ERR_NONE:                 No error
 * \retval RADIO_ERR_CONFIGURE_RADIO:      Failed to configure Sens'it radio
 * \retval RADIO_ERR_OPEN:                 Failed to open Sigfox library
 * \retval RADIO_ERR_SET_STD_CONFIG:       Failed to configure Sigfox library
 *******************************************************************/
error_t RADIO_API_init(void);

/*!******************************************************************
 * \fn error_t RADIO_API_send_message(rgb_color_e color, u8* data, u8 size, bool downlink, u8* response_ptr)
 * \brief Send a Sigfox message.
 *
 * \param[in] color                        Color of led toggle during transmission
 * \param[in] data                         Data to transmit
 * \param[in] size                         Size of data to transmit
 * \param[in] downlink                     True to required a downlink
 * \param[out] response_ptr                Pointer to get downlink data (max: 8 bytes)
 *
 * \retval RADIO_ERR_NONE:                 No error
 * \retval RADIO_ERR_SWITCH_ON:            Failed to switch radio ON
 * \retval RADIO_ERR_DUTY_CYCLE:           Transmission not allowed, duty cycle limit reach (RC1 only)
 * \retval RADIO_ERR_NO_CHANNEL:           Transmission not allowed, no available channel (RC2 & RC4 only)
 * \retval RADIO_ERR_LBT:                  Transmission not allowed, channel occupied (RC3 only)
 * \retval RADIO_ERR_SEND:                 SIGFOX_API_send_frame internal error
 * \retval RADIO_ERR_RECEIVE:              No downlink message received
 * \retval RADIO_ERR_NVMEM:                Error during NVMEM storage
 *******************************************************************/
error_t RADIO_API_send_message(rgb_color_e color,
                               u8* data,
                               u8 size,
                               bool downlink,
                               u8* response_ptr);

/**@}*/
