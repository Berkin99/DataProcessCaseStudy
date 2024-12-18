/** 
 *  strtype.h
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

int isNumeric(const char* str);

int isName(const char* str);

/**
 * @brief Find the token and replace it with '\0'
 * 
 * If given string is NULL or token not founded : Returns NULL
 * 
 * @param str    : Null terminated string.
 * @param token  : Terminator token.
 * 
 * @return char* : Next string | NULL
 */
char* strctok(char* str, char token);
