/*!******************************************************************
 * \file serial.h
 * \brief Generic function to use USB or UART
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * To use the USB communication, use -DUSB in the compilation flags.
 * To use the UART communication, use -DUART in the compilation flags.
 *******************************************************************/


 /*!******************************************************************
  * \defgroup SERIAL_ERR_CODES Error Codes
  * \brief Error code definitions for Serial drivers
  *
  *  @{
  *******************************************************************/
 #define SERIAL_ERR_NONE                    0x00 /*!< No error */

 #define SERIAL_ERR_OVERLOAD                0x60 /*!< No more space in out buffer */
 /**@}*/


/*!******************************************************************
 * \fn void SERIAL_init(void)
 * \brief Initialize serial communication.
 *
 * The USB interfaces will not work if your device is in sleep mode.
 * - Serial Link settings:
 *      * Data Rate: 115,200 bps
 *      * Parity: None
 *      * Bit: 8
 *      * Stop bit: 1
 *      .
 * .
 *******************************************************************/
void SERIAL_init(void);

/*!******************************************************************
 * \fn error_t SERIAL_get_data(u8* buffer, u8 size, u8* index)
 * \brief Get serial data.
 *
 * \param[out] buffer                      Buffer of read data
 * \param[in] size                         Buffer size
 * \param[out] index                       Final buffer index position
 *
 * \retval SERIAL_ERR_NONE:                No error
 * \retval SERIAL_ERR_OVERLOAD:            No more space in out buffer
 *******************************************************************/
error_t SERIAL_get_data(u8* buffer,
                        u8 size,
                        u8* index);

/*!******************************************************************
 * \fn void SERIAL_put_data(u8* data, u8 size)
 * \brief Send serial data.
 *
 * \param[in] data                         Data to send
 * \param[in] size                         Data size
 *******************************************************************/
void SERIAL_put_data(u8* data,
                     u8 size);
