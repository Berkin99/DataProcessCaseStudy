/* 
 *  date.h
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

#include <stdint.h>

#define DEFAULT_CURRENT_YEAR 2024

/* 
 * @brief  : Returns current year. If time not found, returns 
 *           default year.
 *  
 * @return : Current year | DEFAULT_CURRENT_YEAR 
 */
uint16_t currentYear(void);