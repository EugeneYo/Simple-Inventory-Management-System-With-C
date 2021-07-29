gcc main.c \
src/input_validation.c src/product_controller.c src/file_controller.c  -I./src/ \
-I./model/ \
./ansi_color/clear.c -I./ansi_color/ \
-o output 
