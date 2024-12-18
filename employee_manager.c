/** 
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
#include <ctype.h>

#include "utils/date.h"
#include "utils/strtype.h"
#include "employee_manager.h"

static EM_Department_t departments[EM_DEPARTMENT_SIZE] = {
    [EM_DEPARTMENT_UNKNOWN] = {.name = "Unknown"},
    [EM_DEPARTMENT_HR] = {.name = "HR"},
    [EM_DEPARTMENT_IT] = {.name = "IT"},
    [EM_DEPARTMENT_FINANCE] = {.name = "Finance"},
    [EM_DEPARTMENT_SALES] = {.name = "Sales"},
    [EM_DEPARTMENT_MARKETING] = {.name = "Marketing"},
};

EM_Employee_t EM_NewEmployee(uint32_t id, char* name, uint16_t birth_year, EM_Department_e department, uint32_t salary){
    if(department >= EM_DEPARTMENT_SIZE) department = EM_DEPARTMENT_UNKNOWN;

    EM_Employee_t new;
    new.id = id;
    strncpy(new.name, name, EM_EMPLOYEE_MAX_NAME_LENGTH);
    new.name[EM_EMPLOYEE_MAX_NAME_LENGTH - 1] = '\0';
    new.birth_year = birth_year;
    new.department = department;
    new.salary = salary;
    return new;
}

void EM_PrintEmployee(const EM_Employee_t* employee){
    printf("EM> %d : %s, %d, %d, %d\n",employee->id, employee->name, employee->birth_year, employee->department, employee->salary);
}

int8_t EM_AppendEmployee(EM_Employee_t* employee){
    if(employee->department >= EM_DEPARTMENT_SIZE) employee->department = EM_DEPARTMENT_UNKNOWN; /* Department Not Founded */
    EM_Employee_t buffer;
    if(EM_FindEmployeeByID(EM_DEPARTMENT_UNKNOWN, employee->id, &buffer)) return 1; /* ID Already Existed */

    EM_Department_t* pDpt = &departments[employee->department];

    if(pDpt->employees_index >= pDpt->employees_capacity){
        /* Allocate more memory */
        if(pDpt->employees_capacity == 0){
            pDpt->employees_capacity = EM_DEPARTMENT_INIT_CAPACITY;
            pDpt->employees = malloc(sizeof(EM_Employee_t) * EM_DEPARTMENT_INIT_CAPACITY);
        }
        else{
            if((pDpt->employees_capacity * 2) > EM_DEPARTMENT_MAX_CAPACITY) return 2; /* Max Capacity Exceeded */
            pDpt->employees_capacity *= 2; /* Reallocate with 2 times capacity */
            EM_Employee_t* temp = realloc(pDpt->employees, pDpt->employees_capacity * sizeof(EM_Employee_t));
            if(temp != NULL) pDpt->employees = temp; 
        }

        if(pDpt->employees == NULL){ 
            pDpt->employees_capacity = 0; 
            return 2; /* Memory Allcoation Fail! */ 
        } 
    }

    memcpy(&pDpt->employees[pDpt->employees_index], employee, sizeof(EM_Employee_t));
    pDpt->employees_index += 1;

    return 0;
}

EM_Department_t EM_GetDepartment(EM_Department_e department){
    if(department >= EM_DEPARTMENT_SIZE) department = EM_DEPARTMENT_UNKNOWN; /* Department Not Found */
    return departments[department];
}

void EM_PrintDepartment(EM_Department_t* pDpt){
    printf("EM> Department : %s, Capacity : %d, Index : %d\n",pDpt->name, pDpt->employees_capacity, pDpt->employees_index);
    for (uint16_t i = 0; i < pDpt->employees_index; i++)
    {
        EM_PrintEmployee(&pDpt->employees[i]);
    }
}

EM_Department_e EM_DepartmentByName(const char* department_name) {
    /* Search all department names. */
    for (uint16_t i = 0; i < EM_DEPARTMENT_SIZE; i++)
    {
        if(strcasecmp(departments[i].name, department_name) == 0) return i;
    }
    return EM_DEPARTMENT_UNKNOWN;
}

int8_t EM_FindEmployeeByID(EM_Department_e department, uint32_t id, EM_Employee_t* employee){
    if(department >= EM_DEPARTMENT_SIZE) return 0;

    for (uint16_t i = 0; i < departments[department].employees_index; i++)
    {
        if(departments[department].employees[i].id == id){
            *employee = departments[department].employees[i];
            return 1;
        }
    }

    /* Should be <EM_DEPARTMENT_UNKNOWN = 0> for this loop */
    if(department == EM_DEPARTMENT_UNKNOWN){
        /* If department is not known, search all departments */
        for (uint16_t i = 1; i < EM_DEPARTMENT_SIZE; i++)
            if(EM_FindEmployeeByID(i, id, employee)) return 1;
    }

    return 0;
}

void EM_FreeDepartment(EM_Department_e department){
    if(department >= EM_DEPARTMENT_SIZE) return; /* Department Not Founded */

    if(departments[department].employees != NULL){
        free(departments[department].employees);
        departments[department].employees = NULL;
    }
    departments[department].employees_capacity = 0;
    departments[department].employees_index = 0;
}

void EM_Free(void){
    for (uint16_t i = 0; i < EM_DEPARTMENT_SIZE; i++){
        EM_FreeDepartment(i);
    }
}

int8_t EM_FileParser(FILE* file, uint8_t debug) {
    if (file == NULL) return 3; /* File Not Found */
    uint8_t file_corrupted = 0;

    char line[EM_FILE_PARSER_MAX_LINE_LENGTH];
    line[EM_FILE_PARSER_MAX_LINE_LENGTH - 1] = '\0';
    uint16_t line_number = 1;

    /* Read first line and skip*/
    if (fgets(line, EM_FILE_PARSER_MAX_LINE_LENGTH - 1, file) == NULL) return 1;

    /* Reading line by line. Clamped with maximum read value */
    while (fgets(line, EM_FILE_PARSER_MAX_LINE_LENGTH - 1, file)) {
        line_number++;

        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) continue;

        /* Parse with custom tokenizer */
        char* id = line;
        char* name = strctok(id, ',');
        char* age_str = strctok(name, ',');
        char* department_str = strctok(age_str, ',');
        char* salary_str = strctok(department_str, ',');

        /* Control is there any NULL data */
        if (!id || !name || !age_str || !department_str || !salary_str){
            if(debug) printf("EM> Line <%d> : Missing Data.\n", line_number);
            file_corrupted = 1; continue;
        }

        /* Alphabetic and Numeric Control */
        if (!isNumeric(id) || !isName(name) || !isNumeric(age_str) || !isName(department_str) || !isNumeric(salary_str)){
            if(debug) printf("EM> Line <%d> : Token type error.\n", line_number);
            file_corrupted = 1; continue;
        }

        /* Age Control */
        int age = atoi(age_str);
        if(age > 120 || age < 0){
            if(debug) printf("EM> Line <%d> : Age not valid.\n", line_number);
            file_corrupted = 1; continue;
        }
        uint16_t birth_year = currentYear() - age;

        /* Unknown department is not error for the employee_manager. But should flag it for this study. */
        EM_Department_e department = EM_DepartmentByName(department_str);
        if(department == EM_DEPARTMENT_UNKNOWN){
            if(debug) printf("EM> Line <%d> : Department not found.\n", line_number);
            file_corrupted = 1; continue;
        }

        /* Construct the employee */
        EM_Employee_t employee = EM_NewEmployee((uint32_t)atoi(id), name, birth_year, department, (uint32_t)atoi(salary_str));
        
        /* Append */
        int8_t rslt = EM_AppendEmployee(&employee);
        if(rslt == 1){ /* ID Recurrance */
            if(debug) printf("EM> Line <%d> : ID Recurrance.\n", line_number);
            file_corrupted = 1; continue;
        } 
        
        if(rslt == 2){ /* Memory Error! */
            if(debug) printf("EM> Line <%d> : Memory error. Checkout employee_manager.h limits.\n", line_number);
            return 2;          
        }
    }

    return file_corrupted; 
}
