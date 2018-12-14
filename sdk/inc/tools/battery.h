/*!******************************************************************
 * \file battery.h
 * \brief Example of battery manager
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 SIGFOX, All Rights Reserved.
 *******************************************************************/


#define BATTERY_LOW_LEVEL               3000  /* 3V */
#define BATTERY_INIT_LEVEL              3300  /* 3.3V */
#define BATTERY_MEASURE_PERIOD          600   /* 10 minutes */


/*!******************************************************************
 * \fn void BATTERY_handler(u16* battery_level)
 * \brief Check if the battery voltage is not too low.
 *
 * \param[out] battery_level               Battery volatage in mV
 *******************************************************************/
void BATTERY_handler(u16* battery_level);
