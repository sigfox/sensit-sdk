/*!******************************************************************
 * \file discovery.c
 * \brief Ressources of Sens'it Discovery firmware
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "discovery.h"


/******* DEFINES ***************************************************/
#define BATTERY_LVL_MIN         2700 /* 2.7 V  */
#define BATTERY_LVL_MAX         4250 /* 4.25 V */
#define BATTERY_LVL_OFFSET      2700 /* 2.7 V  */
#define BATTERY_LVL_STEP        50   /* 50 mV  */


#define TEMPERATURE_MIN         -200 /* -25°C     */
#define TEMPERATURE_MAX         823  /* 102.875°C */
#define TEMPERATURE_OFFSET      200  /* 25 °C */

#define HUMIDITY_MAX            200  /* 100% */


/*******************************************************************/

void DISCOVERY_build_payload(discovery_payload_s* payload, discovery_mode_e mode, discovery_data_s* data)
{
    payload->reserved = 0b110;
    payload->mode = mode;
    payload->button = data->button;

    if ( data->battery <= BATTERY_LVL_MIN )
    {
         payload->battery = (BATTERY_LVL_MIN - BATTERY_LVL_OFFSET)/BATTERY_LVL_STEP;
    }
    else if ( data->battery >= BATTERY_LVL_MAX )
    {
         payload->battery = (BATTERY_LVL_MAX - BATTERY_LVL_OFFSET)/BATTERY_LVL_STEP;
    }
    else
    {
        payload->battery = (data->battery - BATTERY_LVL_OFFSET)/BATTERY_LVL_STEP;
    }

    if ( mode == MODE_STANDBY )
    {
        payload->fw_major = DISCOVERY_VERSION_MAJOR & 0xF;
        payload->fw_minorMSB = (DISCOVERY_VERSION_MINOR >> 2) & 0xF;
        payload->fw_minorLSB = DISCOVERY_VERSION_MINOR & 0x03;
        payload->fw_patch = DISCOVERY_VERSION_PATCH & 0x3F;
    }
    else if ( mode == MODE_TEMPERATURE )
    {
        if ( data->temperature < TEMPERATURE_MIN )
        {
            payload->special_value = (TEMPERATURE_MIN + TEMPERATURE_OFFSET) >> 8;
            payload->temperatureLSB = (u8)(TEMPERATURE_MIN + TEMPERATURE_OFFSET);
        }
        else if ( data->temperature > TEMPERATURE_MAX )
        {
            payload->special_value = (TEMPERATURE_MAX + TEMPERATURE_OFFSET) >> 8;
            payload->temperatureLSB = (u8)(TEMPERATURE_MAX + TEMPERATURE_OFFSET);
        }
        else
        {
            payload->special_value = (data->temperature + TEMPERATURE_OFFSET) >> 8;
            payload->temperatureLSB = (u8)(data->temperature + TEMPERATURE_OFFSET);
        }

        if ( data->humidity > HUMIDITY_MAX )
        {
            payload->humidity = HUMIDITY_MAX;
        }
        else
        {
            payload->humidity = data->humidity;
        }
    }
    else if ( mode == MODE_LIGHT )
    {
        payload->brightnessMSB = (u8)(data->brightness >> 8);
        payload->brightnessLSB = (u8)data->brightness;
    }
    else if ( mode == MODE_DOOR )
    {
        payload->special_value = data->door;
        payload->event_counterMSB = (u8)(data->event_counter >> 8);
        payload->event_counterLSB = (u8)data->event_counter;
    }
    else if ( mode == MODE_VIBRATION )
    {
        payload->special_value = data->vibration;
        payload->event_counterMSB = (u8)(data->event_counter >> 8);
        payload->event_counterLSB = (u8)data->event_counter;
    }
    else if ( mode == MODE_MAGNET )
    {
        payload->special_value = data->magnet;
        payload->event_counterMSB = (u8)(data->event_counter >> 8);
        payload->event_counterLSB = (u8)data->event_counter;
    }
}

/*******************************************************************/
