/* 
 *  employee_manager.c
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

#include <stdint.h>
#include <stdlib.h>
#include "employee_manager.h"

static EM_Department_t departments[EM_DEPARTMENT_SIZE] = {
    [EM_DEPARTMENT_UNKNOWN].name = "Unknown",
    [EM_DEPARTMENT_SALES].name   = "Sales",
    [EM_DEPARTMENT_FINANCE].name = "Finance",
    [EM_DEPARTMENT_HIRING].name  = "Hiring",
};

EM_Employee_t EM_NewEmployee(char* name, int16_t birth_year, EM_Department_e department){
    EM_Employee_t new;
    new.name = name;
    new.birth_year = birth_year;
    new.department = department;
    return new;
}

int8_t EM_AppendEmployee(EM_Employee_t employee){
    if(employee.department >= EM_DEPARTMENT_SIZE) return 1;
    EM_Department_t dpt = departments[employee.department];

    if(dpt.employees_index == dpt.employees_size){
        /* Allocate more memory */

        return 1;
    }

    dpt.employees[dpt.employees_index] = employee;
    dpt.employees_index += 1;
}

EM_Department_t EM_GetDepartment(EM_Department_e department);

EM_GetSalary