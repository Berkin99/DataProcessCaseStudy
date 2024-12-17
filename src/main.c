/* 
 *  main.c
 *
 *  Author : Berkin Baris YILMAZ 
 *  Date   : 17 Dec 2024
 *  github : github.com/Berkin99/DataProcessorCaseStudy
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "date.h"
#include "employee_manager.h"

void printWithCommas(uint32_t number);

int main(void){

    /* Read the csv file */
    EM_FileParser("Data_Processor_Case_Study.csv");

    /* Program */
    EM_Employee_t max_salary_employee = {0};
    uint32_t      sum_salary = 0;
    float         avg_age = 0.0;
    float         avg_index = 0.0;

    for (uint16_t i = 0; i < EM_DEPARTMENT_SIZE; i++)
    {
        EM_Department_t dpt = EM_GetDepartment(i);
 
        for (uint16_t j = 0; j < dpt.employees_index; j++)
        {
            
            sum_salary += dpt.employees[j].salary;
            if(dpt.employees[j].salary > max_salary_employee.salary) max_salary_employee = dpt.employees[j];
            float age_n = (float)(currentYear() - dpt.employees[j].birth_year);
            avg_age = avg_age * (avg_index / (avg_index + 1.0)) + age_n * (1.0 / (avg_index + 1.0)); /* Zn = Zn * i/(i+1) + Xn * 1/(i+1) */
            avg_index += 1;
        }
        
    }

    /* Print Results */
    printf("Total Salary: $%d\n", sum_salary);
    
    printf("Average Age: %.2f\n", avg_age);
    
    printf("Department with Highest Salary : %s ($%d)\n", EM_GetDepartment(max_salary_employee.department).name, max_salary_employee.salary);
    
    printf("Employees per Department:\n");
    for (uint16_t i = 0; i < EM_DEPARTMENT_SIZE; i++)
    {
        EM_Department_t dpt = EM_GetDepartment(i);
        printf("%s: %d\n", dpt.name, dpt.employees_index);
    }
    
    EM_Free();

    return 0;
}

void printWithCommas(uint32_t number) {
    char buffer[20]; 
    char result[25]; 
    uint32_t i, j, len, count = 0;

    sprintf(buffer, "%d", number);
    len = strlen(buffer);

    j = 0;

    for (i = len - 1; i >= 0; i--) {
        result[j++] = buffer[i];
        count++;

        /* Add a comma after every 3 digits (except at the end)*/
        if (count % 3 == 0 && i != 0) {
            result[j++] = ',';
        }
    }

    result[j] = '\0';

    for (i = 0; i < j / 2; i++) {
        char temp = result[i];
        result[i] = result[j - i - 1];
        result[j - i - 1] = temp;
    }

    printf("%s", result);
}
