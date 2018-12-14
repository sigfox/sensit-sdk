/*!******************************************************************
 * \file discovery.h
 * \brief Ressources of Sens'it Discovery firmware
 * \author Sens'it Team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/


/*!******************************************************************
 * \def DISCOVERY_PAYLOAD_SIZE
 * \brief Size of discovery payload structure.
 *******************************************************************/
#define DISCOVERY_PAYLOAD_SIZE             4 /* Bytes */


/* Fake version increments.
 * Major must be 3 to use sensit.io */
#define DISCOVERY_VERSION_MAJOR            3
#define DISCOVERY_VERSION_MINOR            0
#define DISCOVERY_VERSION_PATCH            2


/*!******************************************************************
 * \struct discovery_payload_s
 * \brief Payload structure of Sens'it Discovery
 *
 * To convert battery level from payload in V:
 *     (battery × 0.05) + 2.7
 *
 * To convert temperature from payload in °C:
 *     (temperature - 200) / 8
 *
 * To convert relative humidity from payload in %:
 *     humidity / 2
 *
 * To convert brightness from payload in lux:
 *     brightness / 96
 *******************************************************************/
typedef struct {

    struct {
        u8 reserved:3;       /* Must be 0b110 */
        u8 battery:5;	     /* Battery level */
    };

    struct {
        u8 special_value:2;  /* Mode TEMPERATURE: temperature MSB */
                             /* Mode DOOR: see door state enum */
                             /* Mode VIBRATION: 01 -> vibration detected */
                             /* Mode MAGNET: 01 -> magnet detected */
        u8 button:1;         /* If TRUE, double presses message */
        u8 mode:5;           /* Payload mode type */
    };

	union {
        struct {
            u8 fw_minorMSB:4;
            u8 fw_major:4;
        };                   /* Mode STANDBY */
		u8 temperatureLSB;   /* Mode TEMPERATURE */
		u8 brightnessMSB;    /* Mode LIGHT */
		u8 event_counterMSB; /* Mode DOOR, VIBRATION & MAGNET */
	};

	union {
        struct {
            u8 fw_patch:6;
            u8 fw_minorLSB:2;
        };                   /* Mode STANDBY */
		u8 humidity;         /* Mode TEMPERATURE */
		u8 brightnessLSB;    /* Mode LIGHT */
		u8 event_counterLSB; /* Mode DOOR, VIBRATION & MAGNET */
	};

} discovery_payload_s;


/*!******************************************************************
 * \enum discovery_mode_e
 * \brief List of Sens'it Discovery mode.
 *******************************************************************/
typedef enum {
    MODE_STANDBY     = 0b00000,
    MODE_TEMPERATURE = 0b00001,
    MODE_LIGHT       = 0b00010,
    MODE_DOOR        = 0b00011,
    MODE_VIBRATION   = 0b00100,
    MODE_MAGNET      = 0b00101,
    MODE_LAST
} discovery_mode_e;


/*!******************************************************************
 * \enum discovery_door_state_e
 * \brief List of mode DOOR state.
 *******************************************************************/
typedef enum {
    DOOR_NONE     = 0b00,
    DOOR_MOVEMENT = 0b01,
    DOOR_CLOSE    = 0b10,
    DOOR_OPEN     = 0b11,
} discovery_door_state_e;


/*!******************************************************************
 * \struct discovery_data_s
 * \brief Input data structure to build discovery payload.
 *******************************************************************/
typedef struct {
    u16 battery;
    s16 temperature;
    u16 humidity;
    u16 brightness;
    discovery_door_state_e door;
    bool vibration;
    bool magnet;
    u16 event_counter;
    bool button;
} discovery_data_s;


/*!************************************************************************
 * \fn void DISCOVERY_build_payload(discovery_payload_s* payload, discovery_mode_e mode, discovery_data_s* data)
 * \brief Function to build the Sens'it Discovery payload.
 *
 * \param[out] payload                     Built payload
 * \param[in] mode                         Mode of the payload structure
 * \param[in] data                         Input data
 **************************************************************************/
void DISCOVERY_build_payload(discovery_payload_s* payload,
                             discovery_mode_e mode,
                             discovery_data_s* data);
