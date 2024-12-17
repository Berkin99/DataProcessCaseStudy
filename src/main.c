
#include <stdint.h>
#include "employee_manager.h"

int main (){

//     3. Output: Print the results to the terminal in the following format:
//    ```
//    Total Salary: $323,000
//    Average Age: 34.25
//    Department with Highest Salary: IT ($155,000)
//    Employees per Department:
//        IT: 2
//        HR: 1
//        Finance: 1
//    ```

    int32_t sum_salary = 0;
    float   avg_age = 0;

    printf("Total Salary: %d,%d$\n", sum_salary / 100, sum_salary % 100);
    printf("Average Age: %.2f\n", avg_age);
    printf("Department with Highest Salary : %s");
    printf("Employees per Department:\n");


    return 0;
}