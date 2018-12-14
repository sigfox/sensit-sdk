/*!******************************************************************
 * \file button.h
 * \brief Sample code for button
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/


/*!******************************************************************
 * \enum button_e
 * \brief Enumaration of button actions.
 *******************************************************************/
typedef enum {
    BUTTON_LONG_PRESS    = 0,
    BUTTON_ONE_PRESS     = 1,
    BUTTON_TWO_PRESSES   = 2,
    BUTTON_THREE_PRESSES = 3,
    BUTTON_FOUR_PRESSES  = 4,
    BUTTON_LAST
} button_e;


/*!************************************************************************
 * \fn void BUTTON_handler(void)
 * \brief Count button presses.
 *
 * Both falling edge interrupt & rising edge interrupt must be enabled.
 *
 * \retval BUTTON_LONG_PRESS:              A long press has been recorded.
 * \retval BUTTON_ONE_PRESS:               One press has been recorded.
 * \retval BUTTON_TWO_PRESSES:             Two presses have been recorded.
 * \retval BUTTON_THREE_PRESSES:           Three presses have been recorded.
 * \retval BUTTON_FOUR_PRESSES:            Four presses have been recorded.
 * \retval BUTTON_LAST:                    Invalid number of presses.
 **************************************************************************/
button_e BUTTON_handler(void);
