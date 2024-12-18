/* 
 *  employee_manager.h
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

#include <stdint.h>

#define EM_EMPLOYEE_MAX_NAME_LENGTH         32
#define EM_DEPARTMENT_INIT_CAPACITY         8
#define EM_DEPARTMENT_MAX_CAPACITY          1024
#define EM_FILE_PARSER_MAX_LINE_LENGTH      256

typedef enum{
    EM_DEPARTMENT_UNKNOWN,
    EM_DEPARTMENT_SALES,
    EM_DEPARTMENT_FINANCE,
    EM_DEPARTMENT_HR,
    EM_DEPARTMENT_IT,
    EM_DEPARTMENT_MARKETING,
    /* ... */
    EM_DEPARTMENT_SIZE
}EM_Department_e;

typedef struct {
    char name[EM_EMPLOYEE_MAX_NAME_LENGTH];  /* Name should not exceed maximum name length */
    uint16_t birth_year;                     /* Should store birth year instead of age */
    EM_Department_e department;              /* Store only Department enum value */
    uint32_t salary;
}EM_Employee_t;

typedef struct{
    char* name;
    EM_Employee_t* employees;
    uint16_t employees_capacity;
    uint16_t employees_index;
}EM_Department_t;

/*
 * @brief : Employee Constructor. If department enum is out of range (> EM_DEPARTMENT_SIZE)
 * Employee gets EM_DEPARTMENT_UNKNOWN as department value.
 * 
 * @param[in] name       : Employee full name.   
 * @param[in] birth_year : Employee birth year.
 * @param[in] department : Employee working department index. Look: EM_Department_e
 * @param[in] salary     : Employee salary.
 * 
 * @return : EM_Employee_t object.
 */
EM_Employee_t EM_NewEmployee(char* name, int16_t birth_year, EM_Department_e department, uint32_t salary);

void EM_PrintEmployee(const EM_Employee_t* employee);

int8_t EM_AppendEmployee(EM_Employee_t* employee);

EM_Department_t EM_GetDepartment(EM_Department_e department);

void EM_PrintDepartment(EM_Department_t* pDpt);

EM_Department_e EM_DepartmentByName(const char* department_name);

void EM_FreeDepartment(EM_Department_e department);

void EM_Free(void);

int8_t EM_FileParser(char* file_name);
