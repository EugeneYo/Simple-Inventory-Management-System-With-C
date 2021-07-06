gcc main.c ^
src\input_validation.c src\product_controller.c src\file_controller.c   ^
-o main

cls

IF EXIST "main.exe" (
  main.exe
)