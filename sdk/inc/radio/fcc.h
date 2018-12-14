/*!******************************************************************
 * \file fcc.h
 * \brief Management of FCC duty cycle
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 SIGFOX, All Rights Reserved.
 *
 * The FCC regulation prohibits re-transmission in the same channel
 * before 20s.
 * This regulation is for RC2 & RC4 only.
 *******************************************************************/


/*!******************************************************************
 * \struct fcc_s
 * \brief Structure to track duty cycle
 *******************************************************************/
typedef struct {
    u32 timestamp;   /*!< Timestamp of the transmission */
    u8 channel_used; /*!< Number of channel used */
} fcc_s;


/*!******************************************************************
 * \fn bool bool FCC_handler(bool downlink_required)
 * \brief Manage FCC channel occupation.
 *
 * \param[in] downlink_required            TRUE if it is a dowlink request
 *
 * \retval FALSE:                          Tx is not permitted
 * \retval TRUE:                           Tx is permitted
 *******************************************************************/
bool FCC_handler(bool downlink_required);
