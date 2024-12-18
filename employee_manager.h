/** 
 *  employee_manager.h
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

#include <stdint.h>
#include <stdio.h>

#define EM_EMPLOYEE_MAX_NAME_LENGTH         32
#define EM_DEPARTMENT_INIT_CAPACITY         8
#define EM_DEPARTMENT_MAX_CAPACITY          2048
#define EM_FILE_PARSER_MAX_LINE_LENGTH      128

typedef enum{
    EM_DEPARTMENT_UNKNOWN = 0,  /* Always Zero */
    EM_DEPARTMENT_HR,
    EM_DEPARTMENT_IT,
    EM_DEPARTMENT_FINANCE,
    EM_DEPARTMENT_SALES,    
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

/**
 * @brief  Creates a new employee structure with the given details.
 *
 * Constructs an EM_Employee_t structure with the provided attributes.
 * If the specified department is invalid, it defaults to EM_DEPARTMENT_UNKNOWN.
 *
 * @param[in]  id          Employee ID (unique identifier).
 * @param[in]  name        Pointer to the employee's name (NULL-terminated string).
 * @param[in]  birth_year  Year of birth of the employee.
 * @param[in]  department  Department to which the employee belongs.
 *                         - Valid range: 0 to EM_DEPARTMENT_SIZE - 1.
 * @param[in]  salary      Employee's salary.
 *
 * @return EM_Employee_t   Newly created employee structure.
 *
 * @note Name is truncated if it exceeds EM_EMPLOYEE_MAX_NAME_LENGTH.
 */
EM_Employee_t EM_NewEmployee(uint32_t id, char* name, uint16_t birth_year, EM_Department_e department, uint32_t salary);

/**
 * @brief  Prints the details of an employee to the console.
 *
 * Outputs the employee's information in the following format:
 * `<ID> : <Name>, <Birth Year>, <Department>, <Salary>`
 *
 * @param[in] employee  Pointer to the employee structure to print.
 *                      - Must not be NULL.
 *
 * @return void
 */
void EM_PrintEmployee(const EM_Employee_t* employee);

/**
 * @brief  Appends an employee to their designated department.
 *
 * Adds the given employee to the appropriate department. If the
 * department's capacity is exceeded, memory is dynamically allocated
 * or reallocated. If the ID already exists, the function returns an error.
 *
 * @param[in] employee  Pointer to the employee to append.
 *                      - Must not be NULL.
 *
 * @retval 0 : Success
 * @retval 1 : ID already exists.
 * @retval 2 : Memory allocation failed. | Capacity was exceeded.
 * 
 */
int8_t EM_AppendEmployee(EM_Employee_t* employee);

/**
 * @brief  Retrieves the department structure for the specified department ID.
 *
 * If the department ID is invalid, returns the EM_DEPARTMENT_UNKNOWN structure.
 *
 * @param[in] department  Department ID to retrieve.
 *                        - Valid range: 0 to EM_DEPARTMENT_SIZE - 1.
 *
 * @return EM_Department_t Department structure corresponding to the given ID.
 */
EM_Department_t EM_GetDepartment(EM_Department_e department);

/**
 * @brief  Prints the details of a department and its employees.
 *
 * Outputs the department name, capacity, and current size, followed by
 * a list of its employees.
 *
 * @param[in] pDpt  Pointer to the department structure to print.
 *                  - Must not be NULL.
 *
 * @return void
 */
void EM_PrintDepartment(EM_Department_t* pDpt);

/**
 * @brief  Finds the department ID by its name.
 *
 * Searches for a department with a name matching the provided string,
 * ignoring case. If no match is found, returns EM_DEPARTMENT_UNKNOWN.
 *
 * @param[in] department_name  Name of the department to search for.
 *                             - Must be a NULL-terminated string.
 *
 * @return EM_Department_e Department ID corresponding to the name, or
 *                         EM_DEPARTMENT_UNKNOWN if not found.
 */
EM_Department_e EM_DepartmentByName(const char* department_name);

/**
 * @brief  Searches for an employee by ID in a specified department or all departments.
 *
 * Locates the employee with the given ID within the specified department. If the
 * department is EM_DEPARTMENT_UNKNOWN, searches across all departments.
 *
 * @param[in]  department  Department to search within.
 *                         - Valid range: 0 to EM_DEPARTMENT_SIZE - 1.
 * @param[in]  id          Employee ID to search for.
 * @param[out] employee    Pointer to store the found employee's data.
 *                         - Must not be NULL.
 *
 * @retval 0 : NotFound
 * @retval 1 : Found
 */
int8_t EM_FindEmployeeByID(EM_Department_e department, uint32_t id, EM_Employee_t* employee);

/**
 * @brief  Frees all resources associated with a department.
 *
 * Deallocates memory used by the employee list of the specified department
 * and resets its capacity and size to zero.
 *
 * @param[in] department  Department ID to free.
 *                        - Valid range: 0 to EM_DEPARTMENT_SIZE - 1.
 *
 * @return void
 */
void EM_FreeDepartment(EM_Department_e department);

/**
 * @brief  Frees resources for all departments.
 *
 * Iterates through all departments and releases their allocated memory.
 */
void EM_Free(void);

/**
 * @brief  Parses a CSV file and populates departments with employees.
 *
 * Reads employee records from the specified file, validates the data, and
 * appends employees to their respective departments. Each line in the file
 * must follow the format:
 * `<ID>,<Name>,<Age>,<Department>,<Salary>`.
 *
 * @param[in]  file  Pointer to the open file to parse.
 * @param[in]  debug If non-zero, prints each successfully parsed employee.
 *
 * @retval 0 : Success
 * @retval 1 : File corrupted.
 * @retval 2 : Memory allocation failed. | Capacity was exceeded.
 * @retval 3 : File not found.
 * 
 * @note Process don't stop at empty lines or invalid employee data.
 */
int8_t EM_FileParser(FILE* file, uint8_t debug);
