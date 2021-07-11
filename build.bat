gcc main.c ^
src\input_validation.c src\product_controller.c src\file_controller.c  -I.\src\ ^
-I.\model\ ^
-I.\ansi_color\ ^
-o main 

@REM cls

IF EXIST "main.exe" (
  main.exe
)


@REM first
@REM gcc sqlite3.c -c  => this is to compile the c file into an object file (other files can use the sqlite3.h as lib)
@REM  example of running the sqlite3.h lib
@REM gcc test.c .\sqlite3\sqlite3.o -o test -I.\sqlite3\ 