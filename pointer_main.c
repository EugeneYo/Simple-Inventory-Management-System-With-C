#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int id;       //2 bytes
    char name[128];        // 1*128 bytes
    char genre[64];        // 1 * 64 bytes
    unsigned int quantity; // 2 bytes
    float price;           // 4 bytes
} Product;                 // total size : 204 bytes
// Product prod[50];          // total size : 10200 bytes

void cleanup(Product **pointer)
{
    free(*pointer);
    *pointer = NULL;
}

// -----------------------------------------------------------------------------------------INPUT VALIDATION
void getDigit(unsigned int *digit)
{
    char *p;
    char input[128];
    unsigned short ask = 1;
    fflush(stdin);
    while (ask)
    {
        fgets(input, 10, stdin);
        *digit = strtol(input, &p, 10);
        ask = (p == input || *p != '\n') ? 1 && printf("Invalid input ! Enter again : ") : 0;
    }
}

void getFloat(float *number)
{
    char *p;
    char input[128];
    unsigned short ask = 1;
    fflush(stdin);
    while (ask)
    {
        fgets(input, 10, stdin);
        *number = strtof(input, &p);
        ask = (p == input || *p != '\n') ? 1 && printf("Invalid input ! Enter again : ") : 0;
    }
}
// ----------------------------------------------------------------------------------------- READ and WRITE
unsigned int totalProduct(){
    int n = 0;
    FILE *f;
    f = fopen("PointerInventory.txt", "r");
    char line[256];
    while (fgets(line, sizeof(line), f))
    {
        fgets(line, sizeof(line), f);
        fgets(line, sizeof(line), f);
        fgets(line, sizeof(line), f);
        fgets(line, sizeof(line), f);
        n++;
    }
    fclose(f);
    return n;
}
void writeFile(Product *prod, unsigned int *total)
{
    int i;
    FILE *f;
    f = fopen("PointerInventory.txt", "w");
    if (f == NULL)
        return;
    for (i = 0; i < *total; i++)
    {
        fprintf(f, "%d\n", (prod + i)->id);
        fputs((prod + i)->name, f);
        fprintf(f, "\n");
        fputs((prod + i)->genre, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", (prod + i)->quantity);
        fprintf(f, "%f\n", (prod + i)->price);
    }
    fclose(f);
}
void readFile(Product *prod)
{
    int n = 0;
    FILE *f;
    f = fopen("PointerInventory.txt", "r");
    char line[256];
    char *temp;
    while (fgets(line, sizeof(line), f))
    {
        prod[n].id = atoi(line);

        fgets(line, sizeof(line), f);
        line[strcspn(line, "\n")] = 0;
        strcpy(prod[n].name, line);

        fgets(line, sizeof(line), f);
        line[strcspn(line, "\n")] = 0;
        strcpy(prod[n].genre, line);

        fgets(line, sizeof(line), f);
        prod[n].quantity = atoi(line);

        fgets(line, sizeof(line), f);
        prod[n].price = atof(line);

        n++;
    }
    fclose(f);
}
// ----------------------------------------------------------------------------------------- CRUD
void listProduct(Product *prod, unsigned int *total)
{
    if (*total == 0)
    {
        printf("No products to view\n");
        return;
    }
    printf(" \t\t\t***** INVENTORY *****\n");
    printf("------------------------------------------------------------------\n");
    printf("S.N.|    %-5s|  %-10s|  %-10s| %-10s|  %-10s|\n", "ID", "Name", "Genre", "Quantity", "Price");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < *total; i++)
    {
        if (prod[i].id == 0)
            continue;
        printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].genre, prod[i].quantity, prod[i].price);
    }
    printf("------------------------------------------------------------------\n\n");
}
void addProduct(Product *prod, unsigned int *total, unsigned int *uid)
{

    prod[*total].id = *uid + 1;

    printf("Product Name: ");
    gets(prod[*total].name);

    printf("Product Genre: ");
    gets(prod[*total].genre);

    printf("Product Quantity: ");
    getDigit(&prod[*total].quantity);

    printf("Product Price: ");
    getFloat(&prod[*total].price);

    (*total)++;
    (*uid)++;
    listProduct(prod, total);
    writeFile(prod, total);
}

void deleteProduct(Product *prod, unsigned int *total)
{
    unsigned int id;
    unsigned int exist = 0;
    listProduct(prod, total);
    printf("Please select the ID of the product to delete : ");
    getDigit(&id);

    for (int i = 0; i < *total; i++)
    {
        if (prod[i].id == id)
            exist = 1;

        if (exist)
            prod[i] = prod[i + 1];
    }

    if (exist)
    {
        printf("Product with ID %d deleted successfully\n", id);
        (*total)--;
    }
    else
    {
        printf("Product with ID %d does not exist.\n", id);
    }
    writeFile(prod, total);
}

void updateProduct(Product *prod, unsigned int *total)
{
    unsigned int id;
    unsigned int exist = 0;
    unsigned int item;
    char *input = (char *)malloc(128 * sizeof(char));

    listProduct(prod, total);
    printf("Please select the ID of the product to update : ");
    getDigit(&id);

    for (int i = 0; i < *total; i++)
    {
        if (prod[i].id == id)
        {
            exist = 1;
            item = i;
        }
    }
    if (exist)
    {
        prod[item].id = id;
        printf("- Type 'Enter' to skip and the data will remain the same.\n");
        printf("%22s%10s -> %-10s\n", "", "[Old]", "[New]");
        printf("%-20s: %10s -> ", "Product Name", prod[item].name);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            strcpy(prod[item].name, input);
        }

        printf("%-20s: %10s -> ", "Product Genre", prod[item].genre);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            strcpy(prod[item].genre, input);
        }

        printf("%-20s: %10d -> ", "Product Quantity", prod[item].quantity);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            if (atoi(input) == 0)
            {
                printf("Invalid input ! Enter again : ");
                getDigit(&prod[item].quantity);
            }
            else
            {
                prod[item].price = atoi(input);
            }
        }

        printf("%-20s: %10.2f -> ", "Product Price", prod[item].price);
        // fflush(stdin);
        fgets(input, 100, stdin);
        if (*input != '\n')
        {
            input[strcspn(input, "\n")] = 0;
            if (atof(input) == 0)
            {
                printf("Invalid input ! Enter again : ");
                getFloat(&prod[item].price);
            }
            else
            {
                prod[item].price = atof(input);
            }
        }

        printf("Product with ID %d updated successfully.\n", id);
    }
    else
    {
        printf("Product with ID %d does not exist.\n", id);
    }
    writeFile(prod, total);
    free(input);
}
void searchProduct(Product *prod, unsigned int *total, unsigned int *action)
{
    Product result[10];
    unsigned int digit;
    char *string = (char *)malloc(128 * sizeof(char));
    float number = 0;
    unsigned int *k = (unsigned int *)malloc(sizeof(unsigned int));
    *k = 0;

    if (*action == 1)
    {
        printf("ID : ");
        getDigit(&digit);

        for (int i = 0; i < *total; i++)
        {
            if (prod[i].id == digit)
            {
                result[*k] = prod[i];
                (*k)++;
            }
        }
        printf("k is %d\n", *k);
        listProduct(result, k);
        *k = 0;
    }
    else if (*action == 2)
    {
        printf("Name : ");
        fflush(stdin);
        gets(string);

        for (int i = 0; i < *total; i++)
        {
            if (strcmp(prod[i].name, string) == 0)
            {
                result[*k] = prod[i];
                (*k)++;
            }
        }
        listProduct(result, k);
        *k = 0;
    }
    else if (*action == 3)
    {
        printf("Genre : ");
        fflush(stdin);
        gets(string);

        for (int i = 0; i < *total; i++)
        {
            if (strcmp(prod[i].genre, string) == 0)
            {
                result[*k] = prod[i];
                (*k)++;
            }
        }
        listProduct(result, k);
        *k = 0;
    }
    else if (*action == 4)
    {
        printf("Quantity : ");
        getDigit(&digit);

        for (int i = 0; i < *total; i++)
        {
            if (prod[i].quantity == digit)
            {
                result[*k] = prod[i];
                (*k)++;
            }
        }
        listProduct(result, k);
        *k = 0;
    }
    else if (*action == 5)
    {
        printf("Price : ");
        getFloat(&number);

        for (int i = 0; i < *total; i++)
        {
            if (prod[i].price == number)
            {
                result[*k] = prod[i];
                (*k)++;
            }
        }
        listProduct(result, k);
        *k = 0;
    }

    free(string);
    free(k);
}
// // ----------------------------------------------------------------------------------------- Loop
void searchMenu(Product *prod, unsigned int *total)
{
    unsigned short exit = 0;
    unsigned int *input = (unsigned int *)malloc(sizeof(unsigned int));

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
        scanf("%d", input);

        fflush(stdin);
        while (1)
        {
            switch (*input)
            {
            case 0:
                exit = 1;
                break;
            case 1:
                printf("Search by ID\n");
                searchProduct(prod, total, input);
                break;
            case 2:
                printf("Search by Name\n");
                searchProduct(prod, total, input);
                break;
            case 3:
                printf("Search by Genre\n");
                searchProduct(prod, total, input);
                break;
            case 4:
                printf("Search by Quantity\n");
                searchProduct(prod, total, input);
                break;
            case 5:
                printf("Search by Price\n");
                searchProduct(prod, total, input);
                break;
            default:
                printf("Huh?\n");
                break;
            }
            break;
        }
    }
    free(input);
}
// ----------------------------------------------------------------------------------------- Initialize
void initiate(Product *prod, unsigned int *total, unsigned int *uid, unsigned int *size)
{
    *total = totalProduct();
    if(*total > *size){
        *size = *total + 10;
        prod = realloc(prod, ((*size) * sizeof(Product)));
    }
    readFile(prod);
    *uid = (*total == 0) ? 0 : prod[*total - 1].id;
}

// ----------------------------------------------------------------------------------------- MAIN
int main(void)
{
    unsigned int *size = (unsigned int *)malloc(sizeof(unsigned int));
    *size = 5;
    Product *prod = (Product *)malloc((*size) * sizeof(Product));
    unsigned int *total = (unsigned int *)malloc(sizeof(unsigned int));
    unsigned int *uid = (unsigned int *)malloc(sizeof(unsigned int));


    unsigned int *input = (unsigned int *)malloc(sizeof(unsigned int));
    unsigned short exit = 0;

    initiate(prod, total, uid, size);

    printf("Total After initiate: %d\n", *total);
    printf("uid After initiate : %d\n", *uid);
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
        scanf("%d", input);
        fflush(stdin);
        switch (*input)
        {
        case 0:
            printf("Exiting. \n");
            exit = 1;
            break;
        case 1:
            printf("View Products\n");
            listProduct(prod, total);
            break;
        case 2:
            printf("Add New Product\n");
            if ((*size - *total ) <= 1)
            {
                *size = *size + 10;
                prod = realloc(prod, ((*size) * sizeof(Product)));
            }
            addProduct(prod, total, uid);
            break;
        case 3:
            printf("Update Existing Product\n");
            updateProduct(prod, total);
            break;
        case 4:
            printf("Delete Product\n");
            deleteProduct(prod, total);
            break;
        case 5:
            printf("Search Product\n");
            searchMenu(prod, total);
            break;
        default:
            printf("Huh?\n");
            break;
        }
    }
    free(prod);
    free(total);
    free(uid);
    free(input);
    free(size);
    return 0;
}
