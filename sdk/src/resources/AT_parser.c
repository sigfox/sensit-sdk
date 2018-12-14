/*!******************************************************************
 * \file AT_parser.c
 * \brief Parsing functions
 * \author Sens'it Team
 * \author SigFox Test and Validation team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/
/******* INCLUDES **************************************************/
#include "sensit_types.h"
#include "sensit_api.h"
#include "sigfox_types.h"
#include "sigfox_api.h"
#include "addon_sigfox_verified_api.h"
#include "AT_parser.h"
#include "AT_functions.h"
#include "serial.h"


/*******************************************************************/

static inline int AT_isxdigit(char c)
{
    return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

/*******************************************************************/

static inline int AT_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

/*******************************************************************/

char* AT_strcat(char* dest, const char* src)
{
    int index_dest = 0;
    int index_src = 0;

    while(dest[index_dest] != '\0')
    {
        index_dest++;
    }

    while(src[index_src] != '\0')
    {
        dest[index_dest + index_src] = src[index_src];
        index_src++;
    }

    dest[index_dest + index_src] = '\0';

    return dest;
}

/*******************************************************************/

char* AT_strcpy(char* dest, const char* src)
{
    int index = 0;

    while(src[index] != '\0')
    {
        dest[index] = src[index];
        index++;
    }

    dest[index] = '\0';

    return dest;
}

/*******************************************************************/

int AT_strcmp(const char* s1, const char* s2)
{
    int index = 0;

    while(s1[index] != '\0' && s2[index] != '\0' && s1[index] == s2[index])
    {
        index++;
    }

    if(s1[index] > s2[index])
    {
        return 1;
    }
    else if(s1[index] < s2[index])
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************/

int AT_strncmp(const char* s1, const char* s2, size_t n)
{
    int index = 0;

    while (s1[index] != '\0' && s2[index] != '\0' && s1[index] == s2[index] && index < n - 1)
    {
        index++;
    }

    if (s1[index] > s2[index])
    {
        return 1;
    }
    else if (s1[index] < s2[index])
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************/

size_t AT_strlen(const char* s)
{
    size_t len = 0;

    while (s[len] != '\0')
    {
        len++;
    }

    return len;
}

/*******************************************************************/

void AT_reverse(char* str)
{
    /* Function reversing a string  */
    int start = 0;
    int end = 0;
    char buf;

    end = AT_strlen(str) - 1;

    /* Swapping the characters */
    while (start < end)
    {
        buf = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = buf;
        start++;
        end--;
    }
}

/*******************************************************************/


char* AT_itoa(int num, char* str, int base)
{
    /* Converting an integer into a string, in a specific base */
    int rem;
    int index = 0;
    char isNegative = 0;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[index++] = '0';
        str[index] = '\0';
        return str;
    }

    /* In standard itoa(), negative numbers are handled only with
     * base 10. Otherwise numbers are considered unsigned. */
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }

    /* Process individual digits */
    while (num != 0)
    {
        rem = num % base;
        str[index++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    /* If number is negative, append '-' */
    if (isNegative == 1)
    {
        str[index++] = '-';
    }

    /* Append string terminator */
    str[index] = '\0';

    /* Reverse the string */
    AT_reverse(str);

    return str;
}

/*******************************************************************/

int AT_atoh(const char* nptr)
{
    /* Converting a string containing an hexadecimal value in ascii to an integer */
    int res = 0;
    int index;

    /* Iterate through all characters of input string and update result */
    for (index=0; AT_isxdigit(nptr[index]) ; ++index)
    {
        if (nptr[index] >= 'A' && nptr[index] <= 'Z')
        {
            res = res*16 + nptr[index] + 10 - 'A';
        }
        else if (nptr[index] >= 'a' && nptr[index] <= 'z')
        {
            res = res*16 + nptr[index] + 10 - 'a';
        }
        else
        {
            res = res*16 + nptr[index] - '0';
        }
    }

    return res;
}

/*******************************************************************/

int AT_atoi(const char* nptr)
{
    /* Converting a string containing a decimal value in ASCII to an integer */
    int res = 0;
    int index;

    /* Iterate through all characters of input string and update result */
    for (index=0; AT_isdigit(nptr[index]) ; ++index)
    {
        res = res*10 + nptr[index] - '0';
    }

    return res;
}

/*******************************************************************/

void AT_parse(char* command)
{
    int param1;
    int param2;
    int cnt;
    char payload[12];
    char data[3];

    if (AT_strncmp(command, "ATZ", 3) == 0)
    {
        /* Command: ATZ
         * Purpose: Reset the device */
        SENSIT_API_reset();
    }

    else if (AT_strncmp(command, "AT$ID?", 6) == 0)
    {
        /* Command: AT$ID?
         * Purpose: Get device sfx id */
        AT_get_id();
    }

    else if (AT_strncmp(command, "AT$V", 4) == 0)
    {
        if (command[4] == '?')
        {
            /* Command: AT$V?
             * Purpose: Get SDK version */
            AT_get_sdk_version();
        }
        else if (command[4] == '=')
        {
            /* Command: AT$V=<type>
             * Purpose: Get Sigfox library version
             * <type>: Version  type (0: sigfox_api; 1: mcu_api; 2: rf_api) */
            param1 = AT_atoi(command + 5);
            AT_get_sfx_lib_version(param1);
        }
    }

    else if (AT_strncmp(command, "AT$RC", 5) == 0)
    {
        if (command[5] == '?')
        {
            /* Command: AT$RC?
             * Purpose: Return current Radio Configuration */
            AT_get_rc();
        }
        else if (command[5] == '=')
        {
            /* Command: AT$RC=<rc>
             * Purpose: Set the radio configuration
             * <rc>: Radio Configuration */
            param1 = AT_atoi(command + 6);
            AT_set_rc(param1);
        }
    }

    else if (AT_strncmp(command, "ATS410", 6) == 0)
    {
        if (command[6] == '?')
        {
            /* Command: ATS410?
             * Purpose: Return used key type */
            AT_get_key_type();
        }
        else if (command[6] == '=')
        {
            /* Command: ATS410=<type>
             * Purpose: Set the key type to use
             * <type>: AES key type (0: PRIVATE; 1: PUBLIC) */
            param1 = AT_atoi(command + 7);
            AT_set_key_type(param1);
        }
    }

    else if (AT_strncmp(command, "AT$SF=", 6) == 0)
    {
        /* Command: AT$SF=<payload>
         * Purpose: Send payload in bytes
         * <payload>: payload (given in hexadecimal value) */

        /* Getting the payload */
        cnt = 0;
        data[2] = '\0';
        while (AT_isxdigit(command[2*cnt+6]))
        {
            if (!AT_isxdigit(command[2*cnt+7]))
            {
                break;
            }
            else
            {
                /* Data is extracted byte per byte from the command */
                data[0] = command[2*cnt+6];
                data[1] = command[2*cnt+7];
                payload[cnt] = (char) (AT_atoh(data) & 0xFF);
                cnt++;
            }
        }
        param1 = cnt;
        AT_send_frame((u8*)payload, param1);
    }

    else if (AT_strncmp(command, "AT$CW=", 6) == 0)
    {
        /* Command: AT$CW=<frequency>,<type>
         * Purpose: Generate a continuous wave
         * <frequency>: Carrier center frequency
         * <type>: 0-> No modulation; 1-> DBPSK 100bps; 2-> DBPSK 600bps */
        param1 = AT_atoi(command + 6);
        for (cnt = 6 ; AT_isdigit(command[cnt]) ; cnt++);
        if (command[cnt] == ',')
        {
            cnt++;
            param2 = AT_atoi(command + cnt);
            while (AT_isdigit(command[cnt]))
            {
                cnt++;
            }
             AT_continuous_wave(param1, param2);
        }
    }

#ifdef TEST_MODE
    else if (AT_strncmp(command, "AT$TM", 5) == 0)
    {
        if (command[5] == '?')
        {
            /* Command: AT$TM?
             * Purpose: Get Test mode lib version */
            AT_get_test_mode_version();
        }
        else if (command[5] == '=')
        {
            /* Command: AT$TM=<mode>
             * Purpose: Activate Sigfox test mode
             * <mode>: test mode to activate */
            param1 = AT_atoi(command + 6);
            AT_test_mode(param1);
        }
    }
#endif

    else if (command[0] == 13)
    {
        /* Just a Carriage Return */
    }

    else
    {
    	SERIAL_put_data((u8*)"UNKNOWN", 7);
    }

    /* Carriage return */
    SERIAL_put_data((u8*)"\n", 1);
}

/*******************************************************************/
