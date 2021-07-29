#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <input_validation.h>
#include <product_controller.h>

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
        printf( CYN "===== Search Existing Product ===== \n" reset);
        printf("--------------------------------- \n");
        printf("| 1 | %-25s |\n", "Search by ID");
        printf("| 2 | %-25s |\n", "Search by Name");
        printf("| 3 | %-25s |\n", "Search by Category");
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
                ClearScreen();
                printf( CYN "===== Search by ID ===== \n" reset);
                searchProduct(prod, total, viewLimit, input);
                break;
            case 2:
                ClearScreen();
                printf( CYN "===== Search by Name ===== \n" reset);
                searchProduct(prod, total, viewLimit,input);
                break;
            case 3:
                ClearScreen();
                printf( CYN "===== Search by Category ===== \n" reset);
                searchProduct(prod, total, viewLimit,input);
                break;
            case 4:
                ClearScreen();
                printf( CYN "===== Search by Quantity ===== \n" reset);
                searchProduct(prod, total, viewLimit,input);
                break;
            case 5:
                ClearScreen();
                printf( CYN "===== Search by Price ===== \n" reset);
                searchProduct(prod, total, viewLimit,input);
                break;
            default:
                ClearScreen();
                printf(RED"Please select the options available\n"reset);
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
printf( CYN ""
"  _____ _                 _        __  __                                                   _      _____           _                 "
"\n / ____(_)               | |      |  \\/  |                                                 | |    / ____|         | |                "
"\n| (___  _ _ __ ___  _ __ | | ___  | \\  / | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_  | (___  _   _ ___| |_ ___ _ __ ___  "
"\n \\___ \\| | '_ ` _ \\| '_ \\| |/ _ \\ | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|  \\___ \\| | | / __| __/ _" "\\ '_ ` _ \\ "
"\n ____) | | | | | | | |_) | |  __/ | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_   ____) | |_| \\__ \\ ||  __/ | | | | |"
"\n|_____/|_|_| |_| |_| .__/|_|\\___| |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__| |_____/ \\__, |___/\\__\\___|_| "
"|_| |_|"
"\n                   | |                                       __/ |                                        __/ |                      "
"\n                   |_|                                      |___/                                        |___/                       "
"\n" reset);
    while (!exit)
    {
        printf( CYN "\n===== Inventory management system ===== \n" reset);
        printf("--------------------------------- \n");
        printf("| 1 | %-25s |\n", "View Existing Products");
        printf("| 2 | %-25s |\n", "Add New Product");
        printf("| 3 | %-25s |\n", "Update Existing Product");
        printf("| 4 | %-25s | \n", "Delete Existing Product");
        printf("| 5 | %-25s | \n", "Search Existing Product/s");
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
            ClearScreen();
            printf( CYN "===== View Existing Products ===== \n" reset);
            listProduct(prod, total, viewLimit);
            break;
        case 2:
            ClearScreen();
            printf( CYN "===== Add New Product ===== \n" reset);
            (*size)++;
            prod = realloc(prod, ((*size) * sizeof(Product)));
            addProduct(prod, total, uid, viewLimit);
            break;
        case 3:
            ClearScreen();
            printf( CYN "===== Update Existing Product ===== \n\n" reset);
            updateProduct(prod, total, viewLimit);
            break;
        case 4:
            ClearScreen();
            printf( CYN "===== Delete Existing Product ===== \n\n" reset);
            deleteProduct(prod, total, viewLimit);
            break;
        case 5:
            ClearScreen();
            searchMenu(prod, total, viewLimit);
            break;
        default:
            ClearScreen();
            printf(RED"Please select the options available\n"reset);
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