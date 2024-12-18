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
    if (EM_FileParser("Data_Processor_Case_Study.csv") != 0) return 1;

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
    printf("Total Salary: $");
    printWithCommas(sum_salary);
    printf("\n");
    
    printf("Average Age: %.2f\n", avg_age);
    
    printf("Department with Highest Salary : %s ($", EM_GetDepartment(max_salary_employee.department).name);
    printWithCommas(max_salary_employee.salary);
    printf(")\n");
    
    printf("Employees per Department:\n");
    for (uint16_t i = 0; i < EM_DEPARTMENT_SIZE; i++)
    {
        EM_Department_t dpt = EM_GetDepartment(i);
        printf("%s: %d\n", dpt.name, dpt.employees_index);
    }
    
    EM_Free();

    return 0;
}

/* Prints with commas for each 3 digits */
void printWithCommas(uint32_t number) {
    char num[30];
    sprintf(num, "%u", number);
    int len = strlen(num);
    for (int i = 0; i < len; i++) {
        putchar(num[i]);
        if ((len - i - 1) % 3 == 0 && i != len - 1) {
            putchar(',');
        }
    }
}
