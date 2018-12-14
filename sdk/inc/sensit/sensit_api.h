/*!******************************************************************
 * \file sensit_api.h
 * \brief Sens'it SDK user functions
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *
 * !!! DO NOT MODIFY THIS FILE !!!
 *******************************************************************/


/*!******************************************************************
 * \defgroup SENSIT_ERR_CODES Sens'it Error Codes
 * \brief Error code definitions for Sens'it APIs
 *
 *  @{
 *******************************************************************/
#define SENSIT_ERR_NONE                    0x00 /*!< No error */

#define SENSIT_ERR_MEMORY                  0x01 /*!< Error, device memory is corrupted */

#define SENSIT_ERR_RADIO_CONF              0x08 /*!< Radio configuration has an invalid value */
#define SENSIT_ERR_RADIO_NOT_INIT          0x09 /*!< Error, radio is not configured */

#define SENSIT_ERR_REED_SWITCH_STATE       0x10 /*!< Error, the reed switch is not enabled */

#define SENSIT_ERR_NVMEM_SIZE              0x11 /*!< Block length exceeds \link SENSIT_NV_MEM_SIZE \endlink */
#define SENSIT_ERR_NVMEM_INIT              0x12 /*!< Non-Volatile memory must be init first */
#define SENSIT_ERR_NVMEM_WRITE             0x13 /*!< Failed to write data in non-volatile memory */

#define SENSIT_ERR_I2C_WRITE               0x14 /*!< Failed to write data on I2C bus */
#define SENSIT_ERR_I2C_READ                0x15 /*!< Failed to read data from I2C bus */
#define SENSIT_ERR_I2C_TIMEOUT             0x16 /*!< I2C communication timeout */

#define SENSIT_ERR_UART_STATE              0x17 /*!< UART communication must be init first */
#define SENSIT_ERR_UART_EMPTY              0x18 /*!< UART Rx buffer is empty */
#define SENSIT_ERR_UART_FULL               0x19 /*!< UART Tx buffer is full */

#define SENSIT_ERR_USB_STATE               0x1A /*!< USB communication must be init first */
#define SENSIT_ERR_USB_EMPTY               0x1B /*!< USB Rx buffer is empty */
#define SENSIT_ERR_USB_FULL                0x1C /*!< USB Tx buffer is full */

#define SENSIT_ERR_RESET_SEQ_NB            0x1F /*!< Failed to reset device sequence number */
/**@}*/


/*!******************************************************************
 * \defgroup INTERRUPT_MASK Interrupt Mask
 * \brief Mask definition for Sens'it peripherals interrupt
 *
 * Use this values with \link pending_interrupt \endlink
 * to know wich peripherals have generated an interrupt.
 *
 *  @{
 *******************************************************************/
#define INTERRUPT_MASK_RTC                 0b00000001 /*!< RTC alarm interrupt mask     */
#define INTERRUPT_MASK_BUTTON              0b00000010 /*!< Button interrupt mask        */
#define INTERRUPT_MASK_REED_SWITCH         0b00000100 /*!< Reed switch interrupt mask   */
#define INTERRUPT_MASK_FXOS8700            0b00001000 /*!< Accelerometer interrupt mask */
/**@}*/


/*!******************************************************************
 * \defgroup SENSOR_I2C_ADDR Sensors address
 * \brief I2C address of Sens'it's sensors
 *
 *  @{
 *******************************************************************/
#define SENSOR_I2C_ADDR_HTS221             0xBE /*!< Temperature & Humidity sensor address */
#define SENSOR_I2C_ADDR_LTR329             0x52 /*!< Light sensor address */
#define SENSOR_I2C_ADDR_FXOS8700           0x3C /*!< Accelerometer & Magnetometer address */
/**@}*/


/*!******************************************************************
 * \def SENSIT_NV_MEM_SIZE
 * \brief Sens'it Non-Volatile Memory maximum size.
 *******************************************************************/
#define SENSIT_NV_MEM_SIZE                 0x03F0


/*!******************************************************************
 * \enum radio_conf_e
 * \brief List of implemented Sigfox Radio Configuration.
 *******************************************************************/
typedef enum {
    SIGFOX_RC1  = 0, /*!< Sigfox Radio Configuration 1  */
    SIGFOX_RC2  = 1, /*!< Sigfox Radio Configuration 2  */
    SIGFOX_RC3C = 2, /*!< Sigfox Radio Configuration 3c */
    SIGFOX_RC4  = 3, /*!< Sigfox Radio Configuration 4  */
    RADIO_CONF_LAST
} radio_conf_e;


/*!******************************************************************
 * \enum rc_origin_e
 * \brief Enum to be used in \link SENSIT_API_configure_radio \endlink
 *******************************************************************/
typedef enum {
    RC_FROM_PARAMETER = 0, /*!< Use Radio Configuration passed as parameter  */
    RC_FROM_MEMORY    = 1, /*!< Use Radio Configuration set in device memory */
} rc_origin_e;


/*!******************************************************************
 * \enum rgb_color_e
 * \brief List of possible colors for the RGB led.
 *******************************************************************/
typedef enum {
    RGB_OFF     = 0b000, /*!< RGB led is off     */
    RGB_BLUE    = 0b001, /*!< RGB led is blue    */
    RGB_GREEN   = 0b010, /*!< RGB led is green   */
    RGB_CYAN    = 0b011, /*!< RGB led is cyan    */
    RGB_RED     = 0b100, /*!< RGB led is red     */
    RGB_MAGENTA = 0b101, /*!< RGB led is magenta */
    RGB_YELLOW  = 0b110, /*!< RGB led is yellow  */
    RGB_WHITE   = 0b111, /*!< RGB led is white   */
} rgb_color_e;


/*!******************************************************************
 * \enum interrupt_e
 * \brief Interupt configuration
 *******************************************************************/
typedef enum {
    INTERRUPT_NONE         = 0b00, /*!< Interrupt disable               */
    INTERRUPT_FALLING_EGDE = 0b01, /*!< Falling edge interrupt          */
    INTERRUPT_RISING_EGDE  = 0b10, /*!< Rising edge interrupt           */
    INTERRUPT_BOTH_EGDE    = 0b11, /*!< Falling & Rising edge interrupt */
} interrupt_e;


/*!******************************************************************
 * \var extern u8 firmware_version[16]
 * \brief Varible use at the device initialization to set your firmware
 * version in the non-volatile memory.
 *
 * Its value is written at the address 0x08007400.
 *
 * \warning If the value of firmware_version change, the non-volatile
 * memory will be erased.
 *******************************************************************/
extern u8 firmware_version[16];


/*!******************************************************************
 * \var volatile u8 pending_interrupt
 * \brief Bit array of peripherals interrupt.
 *
 * Use \link INTERRUPT_MASK \endlink to know wich peripheral
 * have a pending interrupt.
 *******************************************************************/
volatile u8 pending_interrupt;


/*!******************************************************************
 * \defgroup SENSIT_API Sens'it APIs
 * \brief Sens'it SDK user functions
 *
 *  @{
 *******************************************************************/

/*!******************************************************************
 * \fn error_t SENSIT_API_get_sdk_version(u8** version, u8* size)
 * \brief Return Sens'it SDK library version, in ASCII format.
 *
 * \param[out] version                     Pointer to Byte array containing version
 * \param[out] size                        Size of version buffer
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_get_sdk_version(u8** version,
                                   u8* size);

/*!******************************************************************
 * \fn error_t SENSIT_API_configure_radio(rc_origin_e origin, radio_conf_e* rc)
 * \brief Configure the device with the selected Sigfox Radio Configuration (RC).
 *
 * \param[in] origin                       Radio Configuration value origin
 * \param[out] rc                          If RC_FROM_MEMORY, Radio Configuration set in the device memory
 * \param[in] rc                           If RC_FROM_PARAMETER, Radio Configuration to use
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_MEMORY:              Error, device memory is corrupted
 * \retval SENSIT_ERR_RADIO_CONF:          Radio Configuration has an invalid value
 *******************************************************************/
error_t SENSIT_API_configure_radio(rc_origin_e origin,
                                   radio_conf_e* rc);

/*!******************************************************************
 * \fn error_t SENSIT_API_switch_radio(bool on, rgb_color_e color)
 * \brief Switch on/off radio power.
 *
 * \param[in] on                           TRUE to switch on radio
 *                                         FALSE to switch off radio
 * \param[in] color                        Color of LEDs blink during transmission.
 *                                         Use 0xFF to have the white LED blinks.
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_RADIO_NOT_INIT       Error, radio is not configured
 *******************************************************************/
error_t SENSIT_API_switch_radio(bool on,
                                rgb_color_e color);

/*!******************************************************************
 * \fn void SENSIT_API_reset(void)
 * \brief Reset the device.
 *
 * The device reset is signaled by 5 white led blinks.<BR>
 * If the button is pressed during the reset,
 * the device will restart in bootloader.
 *******************************************************************/
void SENSIT_API_reset(void);

/*!******************************************************************
 * \fn error_t SENSIT_API_sleep(bool auto_wake_up)
 * \brief Put the device in stop mode and wait for an interrupt.
 *
 * Use \link pending_interrupt \endlink to know wake up source.
 *
 * \param[in] auto_wake_up                 If TRUE, auto wake up each second
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_sleep(bool auto_wake_up);

/*!******************************************************************
 * \fn error_t SENSIT_API_set_rtc_alarm(u32 interrupt_period)
 * \brief Set RTC alarm timer.<BR>
 * Set interrupt period to 0 to disable it.
 *
 * Use \link pending_interrupt \endlink to know when timer interrupt
 * occurs.
 *
 * \param[in] interrupt_period             Alarm interrupt period in s
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_set_rtc_alarm(u32 interrupt_period);

/*!******************************************************************
 * \fn error_t SENSIT_API_configure_button(interrupt_e config)
 * \brief Configure button interrupt.
 *
 * \param[in] config                       Interrupt configuration
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_configure_button(interrupt_e config);

/*!******************************************************************
 * \fn error_t SENSIT_API_get_button_state(bool* state)
 * \brief Get the state of the button.
 *
 * \param[out] state                       If FALSE, button is pressed.
 *                                         If TRUE, button is released.
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_get_button_state(bool* state);

/*!******************************************************************
 * \fn error_t SENSIT_API_set_rgb_led(rgb_color_e color)
 * \brief Set RGB led state.
 *
 * \param[in] color                        Color of the RGB led
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_set_rgb_led(rgb_color_e color);

/*!******************************************************************
 * \fn error_t SENSIT_API_set_white_led(bool on)
 * \brief Set white led state.
 *
 * \param[in] on                           TRUE: led is turned on
 *                                         FALSE: led is turned off
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_set_white_led(bool on);

/*!******************************************************************
 * \fn error_t SENSIT_API_get_battery_level(u16* battery_voltage)
 * \brief Do a measurement of battery voltage.
 *
 * \param[out] battery_voltage             Battery voltage in mV
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_get_battery_level(u16* battery_voltage);

/*!******************************************************************
 * \fn error_t SENSIT_API_get_current_time(u32* current_time)
 * \brief Return time passed since last device reset.
 *
 * \param[out] current_time                Current time in s
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_get_current_time(u32* current_time);

/*!******************************************************************
 * \fn error_t SENSIT_API_wait(u32 time_ms)
 * \brief Wait during 'time_ms'.
 *
 * \param[in] time_ms                      Time to wait in milliseconds
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_wait(u32 time_ms);

/*!******************************************************************
 * \fn error_t SENSIT_API_configure_reed_switch(bool enable, interrupt_e config)
 * \brief Enable/disable the reed switch and configure interrupt.
 *
 * \param[in] enable                       TRUE to enable reed switch
 * \param[in] config                       Interrupt configuration
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_configure_reed_switch(bool enable,
                                         interrupt_e config);

/*!******************************************************************
 * \fn error_t SENSIT_API_get_reed_switch_state(bool* state)
 * \brief Get the state of the reed switch.
 *
 * \param[out] state                       If FALSE, magnet not detected.
 *                                         If TRUE, magnet detected
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_REED_SWITCH_STATE:   Reed switch is not enabled
 *******************************************************************/
error_t SENSIT_API_get_reed_switch_state(bool* state);

/*!******************************************************************
 * \fn error_t SENSIT_API_write_read_i2c_bus(u8 addr, u8* buffer, u8 nbWrite, u8 nbRead)
 * \brief I2C bus driver.
 *
 * \param[in] addr                         Sensor address. Use \link SENSOR_I2C_ADDR \endlink values.
 * \param[in] buffer                       From buffer[0] to buffer[nbWrite-1]: Data to write
 * \param[out] buffer                      From buffer[nbWrite] to buffer[nbWrite+nbRead-1]: Read data
 * \param[in] nbWrite                      Number of bytes to write
 * \param[in] nbRead                       Number of bytes to read
 *
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_I2C_WRITE:           Failed to write data on I2C bus
 * \retval SENSIT_ERR_I2C_READ:            Failed to read data from I2C bus
 * \retval SENSIT_ERR_I2C_TIMEOUT:         I2C communication timeout
 *******************************************************************/
error_t SENSIT_API_write_read_i2c_bus(u8 addr,
                                      u8* buffer,
                                      u8 nbWrite,
                                      u8 nbRead);

/*!******************************************************************
 * \fn error_t SENSIT_API_configure_fxos8700_interrupt(bool enable)
 * \brief Enable/Disable interrupt from Accelerometer.
 *
 * \warning Interrupt must be routed to INT1 pin and active low
 * in FXOS8700 registers.
 *
 * \param[in] enable                       TRUE to enable interrupt
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_configure_fxos8700_interrupt(bool enable);

/*!******************************************************************
 * \fn error_t SENSIT_API_init_nv_mem(u16 block_length)
 * \brief Initialize Non-Volatile Memory.
 *
 * \warning If you change the block length, it will be impossible to get
 * data already stored in Non-Volatile Memory.
 *
 * \param[in] block_length                 Non-Volatile Memory data block length
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_NVMEM_SIZE:          Block length exceeds \link SENSIT_NV_MEM_SIZE \endlink
 *******************************************************************/
error_t SENSIT_API_init_nv_mem(u16 block_length);

/*!******************************************************************
 * \fn error_t SENSIT_API_get_nv_mem(u8* data)
 * \brief Read user data from non-volatile memory.
 *
 * Data length must be defined by initializing the NVMEM with
 * \link SENSIT_API_init_nv_mem \endlink
 *
 * \param[out] data                        Data read from non-volatile memory
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_NVMEM_INIT:          Non-Volatile memory must be init first
 *******************************************************************/
error_t SENSIT_API_get_nv_mem(u8* data);

/*!******************************************************************
 * \fn error_t SENSIT_API_set_nv_mem(u8* data)
 * \brief Write user data in a non-volatile memory.
 *
 * Data length must be defined by initializing the NVMEM with
 * \link SENSIT_API_init_nv_mem \endlink
 *
 * \param[in] data                         Data to write in non-volatile memory
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_NVMEM_INIT:          Non-Volatile memory must be init first
 * \retval SENSIT_ERR_NVMEM_WRITE:         Failed to write data
 *******************************************************************/
error_t SENSIT_API_set_nv_mem(u8* data);

/*!******************************************************************
 * \fn error_t SENSIT_API_init_watchdog(void)
 * \brief Activate the watchdog.
 *
 * \link SENSIT_API_watchdog_clear \endlink must be called at least
 * every 26 seconds, otherwise the device will be reset.
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_init_watchdog(void);

/*!******************************************************************
 * \fn error_t SENSIT_API_clear_watchdog(void)
 * \brief Clear watchdog timer.
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_clear_watchdog(void);

/*!******************************************************************
 * \fn error_t SENSIT_API_init_uart(void)
 * \brief Initialize the UART communication.
 *
 * - Serial Link settings:
 *      * Data Rate: 115,200 bps
 *      * Parity: None
 *      * Bit: 8
 *      * Stop bit: 1
 *      .
 * .
 *
 * \warning Sleep mode will be disable.
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_init_uart(void);

/*!******************************************************************
 * \fn error_t SENSIT_API_close_uart(void)
 * \brief Close the UART communication.
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_close_uart(void);

/*!******************************************************************
 * \fn error_t SENSIT_API_send_data_to_uart(u8* data, u8 size)
 * \brief Send a string on the UART communication.
 *
 * \param[in] data                         Data to send
 * \param[in] size                         Data size
 *
 * \retval SENSIT_ERR_NONE                 No error
 * \retval SENSIT_ERR_UART_STATE:          First init the UART
 * \retval SENSIT_ERR_UART_FULL:           No more space in UART Tx buffer
 *******************************************************************/
error_t SENSIT_API_send_data_to_uart(u8* data,
                                     u8 size);

/*!******************************************************************
 * \fn error_t SENSIT_API_get_data_from_uart(u8* c)
 * \brief Get a char from the UART Rx buffer.
 *
 * \param[out] c                           Pointer on the read char
 *
 * \retval SENSIT_ERR_NONE                 No error
 * \retval SENSIT_ERR_UART_STATE:          First init the UART
 * \retval SENSIT_ERR_UART_EMPTY:          UART Rx buffer is empty
 *******************************************************************/
error_t SENSIT_API_get_data_from_uart(u8* c);

/*!******************************************************************
 * \fn error_t SENSIT_API_init_usb(void)
 * \brief Initialize USB communication of the device.
 *
 * The USB interfaces will not work if your device is in sleep mode.
 * - Serial Link settings:
 *      * Data Rate: 115,200 bps
 *      * Parity: None
 *      * Bit: 8
 *      * Stop bit: 1
 *      .
 * .
 *
 * \warning Sleep mode will be disable.
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_init_usb(void);

/*!******************************************************************
 * \fn error_t SENSIT_API_send_data_to_usb(u8* data, u8 size)
 * \brief Send a string on the USB communication.
 *
 * \param[in] data                         Data to send
 * \param[in] size                         Data size
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_USB_STATE:           First init the USB
 *******************************************************************/
error_t SENSIT_API_send_data_to_usb(u8* data,
                                    u8 size);

/*!******************************************************************
 * \fn error_t SENSIT_API_get_data_from_usb(u8* c)
 * \brief Get a char from the USB Rx buffer.
 *
 * \param[out] c                           Pointer on the read character
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_USB_STATE:           First init the USB
 * \retval SENSIT_ERR_USB_EMPTY:           USB Rx buffer empty
 *******************************************************************/
error_t SENSIT_API_get_data_from_usb(u8* c);

/*!******************************************************************
 * \fn error_t SENSIT_API_switch_battery_charger(bool enable)
 * \brief Function to disable battery charger in case of use of an
 * external power supply.
 *
 * \param[in] enable                       TRUE to enable battery charger
 *                                         FALSE to disable battery charger
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_switch_battery_charger(bool enable);

/*!******************************************************************
 * \fn error_t SENSIT_API_switch_test_mode_creedentials(bool enable)
 * \brief Switch to private/test mode credentials.
 *
 * Test mode credentials are used for Sigfox API test functions &
 * Sigfox Verified Addon.<BR>
 * Test mode ID = 0xFEDCBA98 <BR>
 * TEST mode key = 0x0123456789ABCDEF0123456789ABCDEF
 *
 * \warning You will no longer be received by the network when using
 * the test mode credentials.
 *
 * \param[in] enable                       TRUE to enable test mode credentials
 *
 * \retval SENSIT_ERR_NONE:                No error
 *******************************************************************/
error_t SENSIT_API_switch_test_mode_creedentials(bool enable);

/*!******************************************************************
 * \fn error_t SENSIT_API_reset_device_sequence_number(void)
 * \brief Reset device sequence number.
 *
 * This fucntion can be use when you have an error during the save of
 * sequence number (SFX_ERR_INT_EXECUTE_COM_SEQUENCE_NVM_STORAGE_MESSAGE).
 *
 * \warning If you reset the sequence number, you will need to
 * "Disengage sequence number" on the Sigfox Cloud to continue to
 * receive your messages.
 *
 * \retval SENSIT_ERR_NONE:                No error
 * \retval SENSIT_ERR_RESET_SEQ_NB:        Failed to reset device sequence number.
 *******************************************************************/
error_t SENSIT_API_reset_device_sequence_number(void);

/**@}*/
