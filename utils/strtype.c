/** 
 *  strtype.c
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Positive Numeric Control */
int isNumeric(const char* str) {
    if (str == NULL) return 0; 
    if (*str == 0) return 0; 

    for (size_t i = 0; str[i] != '\0'; i++) {
        if(i == 10) return 0;
        if (!isdigit(str[i]) && str[i] != ' ') return 0;
    }
    return 1;
}

/* Alphabetic Control */
int isName(const char* str) {
    if (str == NULL) return 0; 
    if (*str == 0) return 0; 

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!isalpha((unsigned char)str[i]) && str[i] != ' ' && str[i] != '.') return 0;
    }
    return 1; 
}

char* strctok(char* str, char token){
    if(str == NULL) return NULL;
    while(*str){
        if(*str == token){
            *str = '\0';
            return (++str);
        }
        str += 1;
    }
    return NULL;
}
