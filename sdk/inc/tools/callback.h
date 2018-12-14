/*!******************************************************************
 * \file callback.h
 * \brief Callbacks from Sens'it SDK library
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/


/*!******************************************************************
 * \fn void CALLBACK_report_test_result(bool status, s16 rssi)
 * \brief To report the result of Sigfox Verified Addon test mode.<BR>
 * You can use USB, UART or LEDs to report results.
 *
 * \param[out] status                      Is TRUE when result ok else FALSE
 * \param[out] rssi                        RSSI of the received frame
 *******************************************************************/
void CALLBACK_report_test_result(bool status,
                                 s16 rssi);
