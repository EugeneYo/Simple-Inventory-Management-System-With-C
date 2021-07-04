#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/input_validation.h"
#include "src/product_controller.h"

void searchMenu()
{
    unsigned short exit = 0;
    unsigned short input;
    while (!exit)
    {
        printf("--------------------------------- \n");
        printf("| 1 | %-25s |\n", "Search by ID");
        printf("| 2 | %-25s |\n", "Search by Name");
        printf("| 3 | %-25s |\n", "Search by Genre");
        printf("| 4 | %-25s | \n", "Search by Quantity");
        printf("| 5 | %-25s | \n", "Search by Price");
        printf("| 0 | %-25s | \n", "Back to Main Menu");
        printf("--------------------------------- \n");
        printf("Actions : ");
        scanf("%d", &input);

        fflush(stdin);
        while (1)
        {
            switch (input)
            {
            case 0:
                exit = 1;
                break;
            case 1:
                printf("Search by ID\n");
                searchProduct(input);
                break;
            case 2:
                printf("Search by Name\n");
                searchProduct(input);
                break;
            case 3:
                printf("Search by Genre\n");
                searchProduct(input);
                break;
            case 4:
                printf("Search by Quantity\n");
                searchProduct(input);
                break;
            case 5:
                printf("Search by Price\n");
                searchProduct(input);
                break;
            default:
                printf("Huh?\n");
                break;
            }
            break;
        }
    }
}

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
        printf("| 5 | %-25s | \n", "Search Product/s");
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
                viewProducts();
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
            case 5:
                printf("Search Product\n");
                searchMenu();
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
