/* 
 *  date.c
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

#include <time.h>
#include "date.h"

uint16_t currentYear(void) {
    time_t t;
    struct tm *current_time;

    t = time(NULL);
    if (t == -1) return DEFAULT_CURRENT_YEAR;

    current_time = localtime(&t);
    if (current_time == NULL) return DEFAULT_CURRENT_YEAR;

    return current_time->tm_year + 1900;
}
