/*!******************************************************************
 * \file my_string.h
 * \brief Redefined functions from the standard C string library
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/


/*!******************************************************************
 * \fn s8 my_memcpy(u8* data_out, u8* data_in, u8 data_size)
 * \brief Copy data_in in dta_out.
 *
 * \param[out] data_out                    Out data pointer
 * \param[in] data_in                      In data pointer
 * \param[in] data_size                    Size of data to copy
 *
 * \retval 0:                              No error
 * \retval -1:                             data_out is a NULL pointer
 *******************************************************************/
s8 my_memcpy(u8* data_out,
             u8* data_in,
             u32 data_size);

/*!******************************************************************
 * \fn bool my_memcmp(u8* data1, u8* data2, u8 data_size)
 * \brief Compare byte to byte data1 and data2.
 *
 * \param[in] data1                        In data pointer
 * \param[in] data2                        In data pointer
 * \param[in] data_size                    Size of data to compare
 *
 * \retval TRUE:                           data1 and data2 are the same
 * \retval FALSE:                          data1 and data2 are different
 *******************************************************************/
bool my_memcmp(u8* data1,
               u8* data2,
               u32 data_size);
