/*!******************************************************************
 * \file sensit_types.h
 * \brief Sens'it SDK type definitions
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/


#define NULL                               (void*)0 /*!< Null pointer */

typedef unsigned char                      u8;  /*!< Unsigned 8 bits type  */
typedef unsigned short                     u16; /*!< Unsigned 16 bits type */
typedef unsigned long                      u32; /*!< Unsigned 32 bits type */

typedef signed char                        s8;  /*!< Signed 8 bits type  */
typedef signed short                       s16; /*!< Signed 16 bits type */
typedef signed long                        s32; /*!< Signed 32 bits type */

typedef unsigned char                      bool;     /*!< Boolean type  */
#define TRUE                               (bool)(1) /*!< Boolean true  */
#define FALSE                              (bool)(0) /*!< Boolean false */

typedef unsigned char                      error_t;  /*!< Sens'it error type*/
