/* 
 *  employee_manager.c
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "date.h"
#include "employee_manager.h"

static EM_Department_t departments[EM_DEPARTMENT_SIZE] = {
    [EM_DEPARTMENT_UNKNOWN].name    = "Unknown",
    [EM_DEPARTMENT_SALES].name      = "Sales",
    [EM_DEPARTMENT_FINANCE].name    = "Finance",
    [EM_DEPARTMENT_HR].name         = "HR",
    [EM_DEPARTMENT_IT].name         = "IT",
    [EM_DEPARTMENT_MARKETING].name  = "Marketing",
};

EM_Employee_t EM_NewEmployee(char* name, int16_t birth_year, EM_Department_e department, uint32_t salary){
    EM_Employee_t new;
    strncpy(new.name, name, EM_EMPLOYEE_MAX_NAME_LENGTH);
    new.birth_year = birth_year;
    new.department = department;
    new.salary = salary;
    return new;
}

void EM_PrintEmployee(EM_Employee_t* employee){
    printf("%s, %d, %d, %d\n",employee->name, employee->birth_year, employee->department, employee->salary);
}

int8_t EM_AppendEmployee(EM_Employee_t* employee){
    if(employee->department >= EM_DEPARTMENT_SIZE) employee->department = EM_DEPARTMENT_UNKNOWN; /* Department Not Founded */

    EM_Department_t* dpt = &departments[employee->department];

    if(dpt->employees_index >= dpt->employees_capacity){
        /* Allocate more memory */
        if(dpt->employees_capacity == 0){
            dpt->employees_capacity = EM_DEPARTMENT_INIT_CAPACITY;
            dpt->employees = malloc(sizeof(EM_Employee_t) * EM_DEPARTMENT_INIT_CAPACITY);
        }
        else{
            if((dpt->employees_capacity * 2) > EM_DEPARTMENT_MAX_CAPACITY) return 1; /* Max Capacity Exceeded */
            dpt->employees_capacity *= 2; /* Reallocate with 2 times capacity */
            dpt->employees = realloc(dpt->employees, dpt->employees_capacity * sizeof(EM_Employee_t));
        }

        if(dpt->employees == NULL){ 
            dpt->employees_capacity = 0; 
            return 1; /* Memory Allcoation Failed ! */ 
        } 
    }

    memcpy(&dpt->employees[dpt->employees_index], employee, sizeof(EM_Employee_t));

    dpt->employees_index += 1;

    return 0;
}

EM_Department_t EM_GetDepartment(EM_Department_e department){
    if(department >= EM_DEPARTMENT_SIZE) department = EM_DEPARTMENT_UNKNOWN; /* Department Not Founded */
    return departments[department];
}

void EM_PrintDepartment(EM_Department_t* department){
    printf("%s, %d, %d\n",department->name, department->employees_capacity, department->employees_index);
}

EM_Department_e EM_DepartmentByName(const char* department_name) {
    for (uint16_t i = 0; i < EM_DEPARTMENT_SIZE; i++)
    {
        if(strcasecmp(departments[i].name, department_name) == 0) return i;
    }
    return EM_DEPARTMENT_UNKNOWN;
}

void EM_FreeDepartment(EM_Department_e department){
    if(department >= EM_DEPARTMENT_SIZE) return; /* Department Not Founded */

    if(departments[department].employees != NULL) free(departments[department].employees);
    departments[department].employees_capacity = 0;
    departments[department].employees_index = 0;
}

void EM_Free(void){
    for (uint16_t i = 0; i < EM_DEPARTMENT_SIZE; i++)
    {
        EM_FreeDepartment(i);
    }
}

static int is_digit(const char c){
    return (c >= '0' && c <= '9');
}

static int is_numeric(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!is_digit(str[i])) return 0;
    }
    return 1;
}

int8_t EM_FileParser(char* file_name) {
    if (file_name == NULL) return 1;

    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        perror("File Error");
        return 1;
    }

    char line[EM_FILE_PARSER_MAX_LINE_LENGTH];
    uint16_t line_number = 0;

    /* Read first line and skip. */
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("File Empty | Read Error\n");
        fclose(file);
        return 1;
    }

    /* Reading line by line. */
    while (fgets(line, sizeof(line), file)) {
        line_number++;

        line[strcspn(line, "\r\n")] = '\0';

        /* Parse */
        char* ix = strtok(line, ",");
        char* name = strtok(NULL, ",");
        char* age_str = strtok(NULL, ",");
        char* department_str = strtok(NULL, ",");
        char* salary_str = strtok(NULL, ",");
        (void)ix;

        /* Control is there any NULL data */
        if (!name || !age_str || !department_str || !salary_str)continue;

        /* Numeric Control */
        if (!is_numeric(age_str) || !is_numeric(salary_str)) continue;

        /* Construct the employee */
        EM_Employee_t employee = EM_NewEmployee(name, (currentYear() - (uint16_t)atoi(age_str)), EM_DepartmentByName(department_str), (uint32_t)atoi(salary_str));

        if (EM_AppendEmployee(&employee) != 0) {
            printf("EM> Memory Error: Employee not appended! (Line : %d): %s\n", line_number, name);
        }
        
    }

    fclose(file);
    return 0; 
}
