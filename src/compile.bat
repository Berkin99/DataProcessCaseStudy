@echo off
REM Compiler settings
set CC=gcc
set CFLAGS=-Wall -g
set SOURCES=date.c employee_manager.c main.c
set HEADERS=date.h employee_manager.h
set OUTPUT=program.exe
%CC% %CFLAGS% %SOURCES% -o %OUTPUT%

if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    exit /b %ERRORLEVEL%
)

echo Created : %OUTPUT%
REM
pause
