/*!******************************************************************
 * \file etsi.h
 * \brief Management of ETSI duty cycle
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 SIGFOX, All Rights Reserved.
 *
 * The ETSI regulation allows to transmit 1% of the time during 1h,
 * so you can transmit 36s each hour.
 * This regulation is for RC1 only.
 *******************************************************************/


/*!******************************************************************
 * \struct etsi_s
 * \brief Structure to track duty cycle
 *******************************************************************/
typedef struct {
    u32 timestamp;   /*!< Timestamp of the transmission */
    u32 tx_duration; /*!< Duration of the transmission in ms */
} etsi_s;


/*!******************************************************************
 * \fn bool ETSI_handler(u8 frame_size, bool downlink_required)
 * \brief Manage the ETSI duty cyle
 *
 * \param[in] frame_size                   Size of the payload to send
 * \param[in] downlink_required            TRUE if it is a dowlink request
 *
 * \retval FALSE:                          Tx is not permitted
 * \retval TRUE:                           Tx is permitted
 *******************************************************************/
bool ETSI_handler(u8 frame_size,
                  bool downlink_required);
