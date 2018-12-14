/*!******************************************************************
 * \file AT_parser.h
 * \brief Parsing functions
 * \author Sens'it Team
 * \author SigFox Test and Validation team
 * \copyright Copyright (c) 2018 Sigfox, All Rights Reserved.
 *******************************************************************/


#define size_t unsigned int


char* AT_strcat(char* dest, const char* src);
char* AT_strcpy(char* dest, const char* src);
int AT_strcmp(const char* s1, const char* s2);
int AT_strncmp(const char* s1, const char* s2, size_t n);
size_t AT_strlen(const char* s);
void AT_reverse(char* str);
char* AT_itoa(int num, char* str, int base);
int AT_atoh(const char* nptr);
int AT_atoi(const char* nptr);

/*!******************************************************************
 * \fn void AT_parse(char* command)
 * \brief Command parser.
 *
 * \param[in] command                      Input string to parse
 *******************************************************************/
void AT_parse(char* command);
