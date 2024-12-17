/* 
 *  employee_manager.h
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

#include <stdint.h>

#define EM_MAX_MEMORY_LIMIT 32000
#define EM_MAX_NAME_LENGTH  36

typedef enum{
    EM_DEPARTMENT_UNKNOWN,
    EM_DEPARTMENT_SALES,
    EM_DEPARTMENT_FINANCE,
    EM_DEPARTMENT_HIRING,
    EM_DEPARTMENT_SIZE
}EM_Department_e;

typedef struct {
    char name[EM_MAX_NAME_LENGTH]; /* Name should not exceed maximum name length */
    uint16_t birth_year;           /* Should store birth year instead of age */
    EM_Department_e department;    /* Department enum */
}EM_Employee_t;

typedef struct{
    char* name;
    EM_Department_e department;
    EM_Employee_t* employees;
    uint16_t employees_size;
    uint16_t employees_index;
}EM_Department_t;

EM_Employee_t EM_NewEmployee(char* name, int16_t birth_year, EM_Department_e department);

int8_t EM_AppendEmployee(EM_Employee_t employee);

EM_Department_t EM_GetDepartment(EM_Department_e department);