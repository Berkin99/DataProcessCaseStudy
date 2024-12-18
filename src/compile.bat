@echo off
REM This batch file compiles the date.c, date.h, employee_manager.c, employee_manager.h, and main.c files

REM Compiler settings (Assuming you are using MinGW or GCC)
set CC=gcc
set CFLAGS=-Wall -g

REM Names of the source files
set SOURCES=date.c employee_manager.c main.c
set HEADERS=date.h employee_manager.h

REM Output file name
set OUTPUT=employee_manager_app.exe

REM Start the compilation process

%CC% %CFLAGS% %SOURCES% -o %OUTPUT%

REM 
if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b %ERRORLEVEL%
)

echo Created : %OUTPUT%

REM End of script
pause
