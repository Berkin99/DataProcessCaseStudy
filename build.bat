@echo off
REM Compiler settings
set CC=gcc
set CFLAGS=-Wall -Werror -Wextra -g
set SOURCES= utils/date.c utils/strtype.c employee_manager.c main.c
set HEADERS= utils/date.h utils/strtype.h employee_manager.h 
set OUTPUT=DataProcessor.exe
%CC% %CFLAGS% %SOURCES% -o %OUTPUT%

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b %ERRORLEVEL%
)

echo Created : %OUTPUT%
REM
pause
