/*!
 \if SIGFOX PATTERN
 ----------------------------------------------

   _____   _   _____   _____   _____  __    __      
  /  ___/ | | /  ___| |  ___| /  _  \ \ \  / /      
  | |___  | | | |     | |__   | | | |  \ \/ /       
  \___  \ | | | |  _  |  __|  | | | |   }  {        
   ___| | | | | |_| | | |     | |_| |  / /\ \
  /_____/ |_| \_____/ |_|     \_____/ /_/  \_\

  ----------------------------------------------

    !!!!  DO NOT MODIFY THIS FILE !!!!

  ----------------------------------------------
 \endif
  ----------------------------------------------*/
/*!
    \mainpage Sigfox Verified API documentation

    The picture below describes the architecture of a Sigfox Device organized as software Layers.<br>
    <br>
    The Addon Sigfox Verified is one application firmware - as described below.
    <br> 
    \image html sw_architecture.png 
*/

/*!
 * \file addon_sigfox_verified_api.h
 * \brief Sigfox Verified test application functions
 * \author $(SIGFOX_LIB_AUTHOR)
 * \version $(SIGFOX_LIB_VERSION)
 * \date $(SIGFOX_LIB_DATE)
 * \copyright Copyright (c) 2011-2017 SIGFOX, All Rights Reserved. This is unpublished proprietary source code of SIGFOX.
 *
 * This file includes the Sigfox Verified test modes functions to be used for the Sigfox Verified application 
 */

/* ######################################################################################### */

/* ------------------------------------------------------------------------------------------------------------------------------------- 
                                            IMPORTANT NOTE on ERROR CODES                             
   ------------------------------------------------------------------------------------------------------------------------------------- 

   ALL ADDON_SIGFOX_VERIFIED_API_xxx functions returns an error type sfx_error_t

   The sfx_error_t is composed of the following :
  \verbatim
     MSB_____________________________________________LSB
     15                      8|7                     0
      |                       |                      |
      |   MANUF_ERROR_CODE    |  SIGFOX_ERROR_CODE   |
      |_______________________|______________________|
 
  \endverbatim
    MANUF_ERROR_CODE :
      - Represents the error codes for MCU_API_xx, RF_API_xx, SE_API_xx, REPEATER_API_xx
      - All MCU_API_xx, RF_API_xx, SE_API_xx, REPEATER_API_xx have to return SFX_ERR_NONE when no error
      - Minimum set of error codes are defined into the mcu_api.h, rf_api.h, se_api.h and repeater_api.h : Manufacturer can define more error codes !
 
   SIGFOX_ERROR_CODE :
      - Represents the error codes of the SIGFOX API, internal functions or Sigfox Verified Application functions.
      - All the SIGFOX API and internal functions error codes can be found in the sigfox_api.h. 
      - All the SIGFOX VERIFIED application error codes can be found in this file. 

   ------------------------------------------------------------------------------------------------------------------------------------- */

/* ---------------------------------------------------------------- */
/* Bytes reserved for SIGFOX ERROR CODES : From 0x10 to 0xBF        */
/* ---------------------------------------------------------------- */

/* They are defined in sigfox_api.h */

/* ----------------------------------------------------------------------------- */
/* Bytes reserved for SIGFOX VERIFIED APP ERROR CODES : From 0xC0 to 0xCF        */
/* ----------------------------------------------------------------------------- */
#define SFX_VERIFIED_ERR_API_TIMER_START                      (sfx_u8)(0xC0)
#define SFX_VERIFIED_ERR_API_REPORT_TEST                      (sfx_u8)(0xC1)
#define SFX_VERIFIED_ERR_API_SLEEP_SEND_BIT_1                 (sfx_u8)(0xC2)
#define SFX_VERIFIED_ERR_API_SLEEP_SEND_BIT_2                 (sfx_u8)(0xC3)
#define SFX_VERIFIED_ERR_API_SLEEP_SEND_OUTOFBAND             (sfx_u8)(0xC4)
#define SFX_VERIFIED_ERR_API_SLEEP_SEND_REPEATER_STATUS       (sfx_u8)(0xC5)
#define SFX_VERIFIED_ERR_API_SLEEP_SEND_FRAME                 (sfx_u8)(0xC6)
#define SFX_VERIFIED_ERR_API_TX_DBPSK                         (sfx_u8)(0xC7)
#define SFX_VERIFIED_ERR_API_DELAY_SENSI                      (sfx_u8)(0xC8)
#define SFX_VERIFIED_ERR_API_DELAY_TX_SYNTH                   (sfx_u8)(0xC9)
#define SFX_VERIFIED_ERR_API_WRONG_RC_ENUM                    (sfx_u8)(0xCA)
#define SFX_VERIFIED_ERR_API_GET_PAYLOAD_ENCRYPTION_FLAG      (sfx_u8)(0xCB)
#define SFX_VERIFIED_ERR_API_TEST_MODE_UNKNOWN                (sfx_u8)(0xCC)
#define SFX_VERIFIED_ERR_API_SLEEP_SEND_RC_SYNC               (sfx_u8)(0xCD)
typedef enum
{
     SFX_RC1   = 0, /*!< Radio Configuration 1 */
     SFX_RC2   = 1, /*!< Radio Configuration 2 */
     SFX_RC3A  = 2, /*!< Radio Configuration 3A */
     SFX_RC3C  = 3, /*!< Radio Configuration 3C */
     SFX_RC4   = 4, /*!< Radio Configuration 4 */
     SFX_RC5   = 5, /*!< Radio Configuration 5 */
     SFX_RC101 = 6, /*!< Radio Configuration 101 */
     SFX_RC_LIST_MAX_SIZE,  /*!< Max Radio Configuration size */
} sfx_rc_enum_t;


typedef enum
{
     SFX_TEST_MODE_TX_BPSK              = 0,   /*!< Only BPSK with Synchro Bit + Synchro frame + PN sequence : no hopping centered on the TX_frequency */
     SFX_TEST_MODE_TX_PROTOCOL          = 1,   /*!< with full protocol with AES key defined at SIGFOX_API_open call: send all SIGFOX protocol frames available with hopping     */
     SFX_TEST_MODE_RX_PROTOCOL          = 2,   /*!< with full protocol with AES key defined at SIGFOX_API_open call: send SIGFOX protocol frames w/ initiate_downlink_flag     = SFX_TRUE */
     SFX_TEST_MODE_RX_GFSK              = 3,   /*!< with known pattern with SB + SF + Pattern on RX_Frequency defined at SIGFOX_API_open function : od internaly compare re    ceived frame <=> known pattern and call sfx_test_report() */
     SFX_TEST_MODE_RX_SENSI             = 4,   /*!< Do uplink +  downlink frame with AES key defined at SIGFOX_API_open call but specific shorter timings */
     SFX_TEST_MODE_TX_SYNTH             = 5,   /*!< Do 9 uplink frames to measure frequency synthesis step */
     SFX_TEST_MODE_TX_FREQ_DISTRIBUTION = 6,   /*!< Call all Sigfox frames of all types and size on all the Sigfox Band  */
} sfx_test_mode_t;

/*!******************************************************************
 * \fn sfx_error_t ADDON_SIGFOX_VERIFIED_API_get_version ( sfx_u8 **version, sfx_u8 *size )
 * \brief This function allows to get the version of the Addon 
 *
 * \param[out] sfx_u8 **version            Pointer to Byte array (ASCII format) containing library version
 * \param[out] sfx_u8 *size                Size of the byte array pointed by *version
 *
 * \retval  The sfx_error_t is composed of the following :
 *
 * \verbatim
 *    MSB_____________________________________________LSB
 *     |                       |                      |
 *     |   MANUF_ERROR_CODE    |  SIGFOX_ERROR_CODE   |
 *     |_______________________|______________________|
 * \endverbatim 
 *
 *******************************************************************/
sfx_error_t ADDON_SIGFOX_VERIFIED_API_get_version ( sfx_u8 **version, sfx_u8 *size );

/*!******************************************************************
 * \fn sfx_error_t ADDON_SIGFOX_VERIFIED_API_test_mode(sfx_rc_enum_t rc_enum, sfx_test_mode_t test_mode)
 * \brief This function executes the test modes needed for the Sigfox Verified Certification 
 * 
 * \param[in]  sfx_rc_t                    Radio Configuration pointer
 * \param[in]  sfx_test_mode_t test_mode   Test mode to be executed
 *
 * \retval  The sfx_error_t is composed of the following :
 *
 * \verbatim
 *    MSB_____________________________________________LSB
 *     |                       |                      |
 *     |   MANUF_ERROR_CODE    |  SIGFOX_ERROR_CODE   |
 *     |_______________________|______________________|
 * \endverbatim 
 *
 *******************************************************************/
sfx_error_t ADDON_SIGFOX_VERIFIED_API_test_mode(sfx_rc_enum_t rc_enum, sfx_test_mode_t test_mode);

