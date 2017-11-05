@echo off
del zeller_x.exe
gcc -c main.c zeller.c  calc_days.c -Wall
if %ERRORLEVEL% equ 0 (
  echo Compile Succeed
) else (
  echo Compile Failed
  goto :EOF
)
gcc main.o zeller.o calc_days.o -o zeller_x -Wall
if %ERRORLEVEL% equ 0 (
  echo Link Succeed
) else (
  echo Link Failed
)
