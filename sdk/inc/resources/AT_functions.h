/*!******************************************************************
 * \file AT_functions.h
 * \brief Functions call by the AT parser
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/


/*!******************************************************************
 * \fn void AT_get_id(void)
 * \brief Print device ID.
 *******************************************************************/
void AT_get_id(void);

/*!******************************************************************
 * \fn void AT_get_sdk_version(void)
 * \brief Print Sens'it SDK version.
 *******************************************************************/
void AT_get_sdk_version(void);

/*!******************************************************************
 * \fn void AT_get_sfx_lib_version(sfx_version_type_t type)
 * \brief Command parser.
 *
 * \param[in] type                         Sigfox lib version type
 *******************************************************************/
void AT_get_sfx_lib_version(sfx_version_type_t type);

/*!******************************************************************
 * \fn void AT_get_rc(void)
 * \brief Print used Radio configuration.
 *******************************************************************/
void AT_get_rc(void);

/*!******************************************************************
 * \fn void AT_set_rc(radio_conf_e rc)
 * \brief Set the radio configuration.
 *
 * \param[in] rc                           Radio Configuration to set
 *******************************************************************/
void AT_set_rc(radio_conf_e rc);

/*!******************************************************************
 * \fn void AT_get_key_type(void)
 * \brief Print the used AES key type.
 *******************************************************************/
void AT_get_key_type(void);

/*!******************************************************************
 * \fn void AT_set_key_type(bool type)
 * \brief Set the AES key type
 *
 * \param[in] type                         0: Private key ; 1: Public key
 *******************************************************************/
void AT_set_key_type(bool type);

/*!******************************************************************
 * \fn void AT_send_frame(u8* payload, u8 length)
 * \brief Send a Sigfox message.
 *
 * \param[in] payload                      Data to send
 * \param[in] length                       Number of byte to send
 *******************************************************************/
void AT_send_frame(u8* payload,
                   u8 length);

/*!******************************************************************
 * \fn void AT_continuous_wave(u32 frequency, sfx_modulation_type_t type)
 * \brief Start a continuous wave transmission with/without modulation.
 *
 * To stop the CW, press the button.
 *
 * \param[in] frequency                    Carrier center frequency
 * \param[in] type                         Modulation type
 *******************************************************************/
void AT_continuous_wave(u32 frequency,
                        sfx_modulation_type_t type);

/*!******************************************************************
 * \fn void AT_get_test_mode_version(void)
 * \brief Print Sigfox Verified addon version.
 *******************************************************************/
void AT_get_test_mode_version(void);

/*!******************************************************************
 * \fn void AT_test_mode(sfx_test_mode_t mode)
 * \brief Sigfox Verified test modes.
 *
 * To stop the CW, press the button.
 *
 * \param[in] mode                         Test mode to launch
 *******************************************************************/
void AT_test_mode(sfx_test_mode_t mode);
