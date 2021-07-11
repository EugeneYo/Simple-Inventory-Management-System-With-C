#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/input_validation.h"
#include "src/product_controller.h"

void cleanup(Product **pointer)
{
    free(*pointer);
    *pointer = NULL;
}

void searchMenu(Product *prod, unsigned int *total, unsigned int *viewLimit){
    unsigned short exit = 0;
    unsigned int input;

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
                searchProduct(prod, total, viewLimit, input);
                break;
            case 2:
                printf("Search by Name\n");
                searchProduct(prod, total, viewLimit,input);
                break;
            case 3:
                printf("Search by Genre\n");
                searchProduct(prod, total, viewLimit,input);
                break;
            case 4:
                printf("Search by Quantity\n");
                searchProduct(prod, total, viewLimit,input);
                break;
            case 5:
                printf("Search by Price\n");
                searchProduct(prod, total, viewLimit,input);
                break;
            default:
                printf("Huh?\n");
                break;
            }
            break;
        }
    }
}

int main(void){
    unsigned int *size = (unsigned int *)malloc(sizeof(unsigned int));
    unsigned int *total = (unsigned int *)malloc(sizeof(unsigned int));
    unsigned int *uid = (unsigned int *)malloc(sizeof(unsigned int));
    unsigned int *viewLimit = (unsigned int *)malloc(sizeof(unsigned int));

    Product *prod = initiate(prod, total, uid, size, viewLimit);

    unsigned int input;
    unsigned short exit =  0;

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
        scanf("%d", &input);
        fflush(stdin);
        switch (input)
        {
        case 0:
            printf("Exiting. \n");
            exit = 1;
            break;
        case 1:
            printf("View Products\n");
            listProduct(prod, total, viewLimit);
            break;
        case 2:
            printf("Add New Product\n");
            (*size)++;
            prod = realloc(prod, ((*size) * sizeof(Product)));
            addProduct(prod, total, uid, viewLimit);
            break;
        case 3:
            printf("Update Existing Product\n");
            updateProduct(prod, total, viewLimit);
            break;
        case 4:
            printf("Delete Product\n");
            deleteProduct(prod, total, viewLimit);
            break;
        case 5:
            printf("Search Product\n");
            searchMenu(prod, total, viewLimit);
            break;
        default:
            printf("Huh?\n");
            break;
        }
    }
    free(prod);
    free(total);
    free(uid);
    free(size);
    free(viewLimit);
    return 0;
}