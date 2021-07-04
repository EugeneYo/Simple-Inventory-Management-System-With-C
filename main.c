#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/input_validation.h"
#include "src/product_controller.h"

int main(void)
{
    initiate();
    unsigned short exit = 0;
    unsigned int *input;

    while (!exit)
    {
        printf("===== Inventory management system ===== \n");
        printf("--------------------------------- \n");
        printf("| 1 | %-25s |\n", "View Products");
        printf("| 2 | %-25s |\n", "Add New Product");
        printf("| 3 | %-25s |\n", "Update Existing Product");
        printf("| 4 | %-25s | \n", "Delete Product");
        printf("| 0 | %-25s | \n", "Exit program");
        printf("--------------------------------- \n");
        printf("Actions : ");
        getDigit(input);

        fflush(stdin);
        while (1)
        {
            switch (*input)
            {
            case 0:
                printf("Exiting Program.\n");
                exit = 1;
                break;
            case 1:
                printf("View Products\n");
                listProduct();
                break;
            case 2:
                printf("Add New Product\n");
                addProduct();
                break;
            case 3:
                printf("Update Existing Product\n");
                updateProduct();
                break;
            case 4:
                printf("Delete Product\n");
                deleteProduct();
                break;
            default:
                printf("Options unavailable\n");
                break;
            }
            break;
        }
    }
    return 0;
}
