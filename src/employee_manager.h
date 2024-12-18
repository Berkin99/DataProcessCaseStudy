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
    uint32_t id;                             /* Employee Unique ID */
    char name[EM_EMPLOYEE_MAX_NAME_LENGTH];  /* Name should not exceed maximum name length */
    uint16_t birth_year;                     /* Should store birth year instead of age */
    EM_Department_e department;              /* Store only Department enum value */
    uint32_t salary;
}EM_Employee_t;

typedef struct{
    char* name;                     /* Department Name : Should be defined in employee_manager.c/departments */
    EM_Employee_t* employees;       /* Allocated memory pointer for Employee objects */
    uint16_t employees_capacity;    /* Allocated memory capacity */
    uint16_t employees_index;       /* <employees> Size | Array index for Next employee */
}EM_Department_t;

/*
 * @brief : Employee Constructor. If department enum is out of range (> EM_DEPARTMENT_SIZE)
 *          Employee gets EM_DEPARTMENT_UNKNOWN as department value.
 * 
 * @param[in] name       : Employee full name.   
 * @param[in] birth_year : Employee birth year.
 * @param[in] department : Employee working department index. Look: EM_Department_e
 * @param[in] salary     : Employee salary.
 * 
 * @return : EM_Employee_t object.
 */
EM_Employee_t EM_NewEmployee(uint32_t id, char* name, int16_t birth_year, EM_Department_e department, uint32_t salary);

void EM_PrintEmployee(const EM_Employee_t* employee);

/* 
 * @brief : Copies and appends the Employee object to the related department
 *          Error cases :  
 *          - Contains Same ID in the list 
 *          
 * @retval   0 -> Success
 * @retval > 0 -> Error
 */
int8_t EM_AppendEmployee(EM_Employee_t* employee);

EM_Department_t EM_GetDepartment(EM_Department_e department);

void EM_PrintDepartment(EM_Department_t* pDpt);

EM_Department_e EM_DepartmentByName(const char* department_name);

void EM_FreeDepartment(EM_Department_e department);

/* 
 * @brief : Searches the department employees for find the id.
 * 
 * @param[in]  department : EM_Department_e
 * @param[in]  id         : Unique Employee ID 
 * @param[out] pEmployee  : Found employee 
 *
 * @retval   1 -> Found
 * @retval > 0 -> Not Found
 */ 
int8_t EM_FindEmployeeByID(EM_Department_e department, uint32_t id, EM_Employee_t* pEmployee);

void EM_Free(void);

int8_t EM_FileParser(char* file_name, uint8_t debug);
