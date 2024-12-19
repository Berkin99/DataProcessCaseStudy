# Data Processor

The Data Processor project is a C-based executable program designed to parse and process employee data from a CSV file. It calculates statistical summaries such as total salary, average age, and identifies employees with the highest salaries within departments.

## Features

- Parse employee data from "data.csv" file.
- Efficient memory management to prevent leaks.
- Error Handling 

## CSV File
#### CSV Format:
- CSV Format Tokens : UniqueID,Name,Age,Department,Salary
- Example csv line  : 12,John Doe,27,IT,120000

#### CSV Invalid Lines:
- Numeric token has non numeric | Alphabetic token has non **Name-Character**.
- ID Recurrence.
- Empty token | Empty line.
- Numeric token has more than 10 digit.
- Negative age.
- Negeative salary.
- Line has more characters than Line character limit.

#### CSV Error Handling:
- If the file is missing, print: Error: File data.csv not found.
- If the file format is incorrect, print: Error: Invalid file format.
- Can print the results with "-f" argument to the program, even if corrupted data.
- Long names clipped with name byte limit.
- Employees with unknown department, stored in **Unknown** department.

## File Structure

- **main.c**: The main program logic for processing employee data.
- **employee_manager.h/.c**: Manages employees and departments, including memory allocation.
- **utils/date.h/.c**: Provides utility functions for date operations, such as retrieving the current year.
- **utils/strtype.h/.c**: Provides utility functions for string operations.

## How to Use

1. Clone the repository and navigate to the project folder.
2. Ensure the CSV file (e.g., `Data_Processor_Case_Study.csv`) is present in the working directory.
3. Compile the program with .bat file:
    ```bash
    ./build.bat
    ```
4. Run the executable:
    ```bash
    ./DataProcessor.exe
    ```
5. For ignoring the corrupted data:
    ```bash
    ./DataProcessor.exe -f
    ```

## Example Output

```text
Total Salary: $2,345,678
Average Age: 35.42
Department with Highest Salary: IT ($120,000)
Employees per Department:
HR: 15
IT: 20
Finance: 10
```

# Employee Manager

Employee Manager is a C-based library for managing employee data, categorized by departments. This project provides functionalities to add, find, and manage employees and their respective departments efficiently.

## Features

- Add new employees with attributes like ID, name, birth year, department, and salary.
- Dynamically allocate memory to handle an increasing number of employees.
- Retrieve, print, and manage employees within departments.
- Parse employee data from a file.
- Free allocated memory to prevent memory leaks.

## File Structure

- **employee_manager.h**: Header file containing function declarations and structure definitions.
- **employee_manager.c**: Implementation file with the core logic of the Employee Manager.
- **date.h**: Provides utility functions related to date operations.

## Dependencies

This project uses standard C libraries:
- `<stdint.h>`
- `<stdlib.h>`
- `<string.h>`
- `<stdio.h>`
- `<ctype.h>`

## Key Structures

### Employee (`EM_Employee_t`)
Defines attributes of an employee:
- `id`: Unique identifier.
- `name`: Name of the employee.
- `birth_year`: Year of birth.
- `department`: Enum representing the department.
- `salary`: Salary in monetary units.

### Department (`EM_Department_t`)
Defines attributes of a department:
- `name`: Department name.
- `employees`: Pointer to a dynamically allocated array of employees.
- `employees_capacity`: Current capacity of the array.
- `employees_index`: Number of employees currently in the department.

## Functions

### Employee Functions

- **`EM_NewEmployee`**
  Creates a new employee with specified attributes.

- **`EM_PrintEmployee`**
  Prints the details of an employee.

- **`EM_AppendEmployee`**
  Appends a new employee to the appropriate department. Dynamically reallocates memory if required.

### Department Functions

- **`EM_GetDepartment`**
  Retrieves a department based on the enum value.

- **`EM_PrintDepartment`**
  Prints the details of a department, including all employees in it.

- **`EM_DepartmentByName`**
  Finds a department based on its name (case-insensitive).

- **`EM_FreeDepartment`**
  Frees all memory allocated for a department.

### General Functions

- **`EM_FindEmployeeByID`**
  Searches for an employee by ID within a specific department or across all departments.

- **`EM_Free`**
  Frees all allocated memory for all departments.

- **`EM_FileParser`**
  Parses employee data from a CSV file and adds employees to departments.

## How to Use

1. Include the required headers (`employee_manager.h`, `date.h`) in your project.
2. Initialize employee and department data using provided functions.
3. Use `EM_FileParser` to load employee data from a CSV file.
4. Call `EM_AppendEmployee` to add new employees dynamically.
5. Manage department data using `EM_GetDepartment` and `EM_PrintDepartment`.
6. Free all allocated memory using `EM_Free` before program termination.

## Example

```c
#include "employee_manager.h"

int main() {
    EM_Employee_t emp1 = EM_NewEmployee(1, "John Doe", 1990, EM_DEPARTMENT_IT, 70000);
    EM_AppendEmployee(&emp1);

    EM_Department_t it_department = EM_GetDepartment(EM_DEPARTMENT_IT);
    EM_PrintDepartment(&it_department);

    EM_Free();
    return 0;
}
```

## Memory Management

- **Dynamic Allocation**: Departments dynamically allocate memory for employees.
- **Reallocation**: Memory is doubled when capacity is reached.
- **Deallocation**: Always call `EM_Free` to release allocated memory.

## Error Handling

- Checks for NULL pointers and invalid data.
- Handles memory allocation failures gracefully.

## Limitations

- Maximum department size is limited by `EM_DEPARTMENT_MAX_CAPACITY`.
- CSV parsing assumes specific formatting.


