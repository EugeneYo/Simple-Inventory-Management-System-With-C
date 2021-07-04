#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int id;
    char name[128];
    char genre[64];
    unsigned int quantity;
    float price;
} Product;
Product prod[50];
unsigned int total;
unsigned int uuid;

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
        if (p == input || *p != '\n')
        {
            printf("Invalid input ! Enter again: ");
        }
        else
        {
            ask = 0;
        }
    }
}

void getFloat(float *number)
{
    char *p ;
    char input[128];
    unsigned short ask = 1;
    fflush(stdin);
    while (ask)
    {
        fgets(input, 10, stdin);
        *number = strtof(input, &p);
        if (p == input || *p != '\n')
        {
            printf("Invalid input ! Enter again: ");
        }
        else
        {
            ask = 0;
        }
    }

}
// ----------------------------------------------------------------------------------------- READ and WRITE
void writeFile()
{
    int i;
    FILE *f;
    f = fopen("GameInventory.txt", "w");
    if (f == NULL)
        return;
    for (i = 0; i < total; i++)
    {
        fprintf(f, "%d\n", prod[i].id);
        fputs(prod[i].name, f);
        fprintf(f, "\n");
        fputs(prod[i].genre, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", prod[i].quantity);
        fprintf(f, "%f\n", prod[i].price);
    }
    fclose(f);
}

int readFile()
{
    int n = 0;
    int i;
    FILE *f;

    if ((f = fopen("GameInventory.txt", "r")) == NULL)
    {
        printf("GameInventory.txt File doesn't exist. Creating it now...");
        writeFile();
    }
    else
    {
        char line[256];
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
    }
    fclose(f);
    return n;
}

// ----------------------------------------------------------------------------------------- CRUD
void listProduct(Product *prod, unsigned int total)
{
    if (total == 0)
    {
        printf("No products to view\n");
        return;
    }
    printf(" \t\t\t***** INVENTORY *****\n");
    printf("------------------------------------------------------------------\n");
    printf("S.N.|    %-5s|  %-10s|  %-10s| %-10s|  %-10s|\n", "ID", "Name", "Genre", "Quantity", "Price");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++)
    {
        if (prod[i].id == 0)
            continue;
        printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].genre, prod[i].quantity, prod[i].price);
    }
    printf("------------------------------------------------------------------\n\n");
}
void addProduct()
{
    prod[total].id = uuid + 1;

    printf("Product Name: ");
    // fflush(stdin);
    gets(prod[total].name);

    printf("Product Genre: ");
    // fflush(stdin);
    gets(prod[total].genre);

    printf("Product Quantity: ");
    getDigit(&prod[total].quantity);
    // fflush(stdin);

    printf("Product Price: ");
    getFloat(&prod[total].price);
    // fflush(stdin);
    total++;
    uuid++;
    listProduct(prod, total);
    printf("Writing File\n");
    writeFile();
    printf("Done writing\n");
}

void deleteProduct()
{
    unsigned int id;
    unsigned int exist = 0;
    listProduct(prod, total);
    printf("Please select the ID of the product to delete : ");
    getDigit(&id);

    for (int i = 0; i < total; i++)
    {
        if (prod[i].id == id)
            exist = 1;

        if (exist)
            prod[i] = prod[i + 1];
    }

    if (exist)
    {
        printf("Product with ID %d deleted successfully\n", id);
        total--;
    }
    else
    {
        printf("Product with ID %d does not exist.\n", id);
    }
    printf("Writing File\n");
    writeFile();
    printf("Done writing\n");

}

void updateProduct()
{
    unsigned int id;
    unsigned int exist = 0;
    unsigned int item;
    char *input = (char *)malloc(128 * sizeof(char));

    listProduct(prod, total);
    printf("Please select the ID of the product to update : ");
    getDigit(&id);

    for (int i = 0; i < total; i++)
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
                printf("Invalid input ! Enter again: ");
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
                printf("Invalid input ! Enter again: ");
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
    printf("Writing File\n");
    writeFile();
    printf("Done writing\n");
}
void searchProduct(unsigned int action)
{
    Product result[10];
    unsigned int digit;
    char *string = (char *)malloc(128 * sizeof(char));
    float number = 0;
    unsigned int k = 0;

    if (action == 1)
    {
        printf("ID : ");
        getDigit(&digit);
        // for (int i = 0; i < 10; i++)
        // {
        //     result[i].id = 0;
        // }
        for (int i = 0; i < total; i++)
        {
            if (prod[i].id == digit)
            {
                result[k] = prod[i];
                k++;
            }
        }
        listProduct(result, k);
        k = 0;
    }
    else if (action == 2)
    {
        printf("Name : ");
        fflush(stdin);
        gets(string);
        // for (int i = 0; i < 10; i++)
        // {
        //     result[i].id = 0;
        // }
        for (int i = 0; i < total; i++)
        {
            if (strcmp(prod[i].name, string) == 0)
            {
                result[k] = prod[i];
                k++;
            }
        }
        listProduct(result, k);
        k = 0;
    }
    else if (action == 3)
    {
        printf("Genre : ");
        fflush(stdin);
        gets(string);
        // for (int i = 0; i < 10; i++)
        // {
        //     result[i].id = 0;
        // }
        for (int i = 0; i < total; i++)
        {
            if (strcmp(prod[i].genre, string) == 0)
            {
                result[k] = prod[i];
                k++;
            }
        }
        listProduct(result, k);
        k = 0;
    }
    else if (action == 4)
    {
        printf("Quantity : ");
        getDigit(&digit);
        // for (int i = 0; i < 10; i++)
        // {
        //     result[i].id = 0;
        // }
        for (int i = 0; i < total; i++)
        {
            if (prod[i].quantity == digit)
            {
                result[k] = prod[i];
                k++;
            }
        }
        listProduct(result, k);
        k = 0;
    }
    else if (action == 5)
    {
        printf("Price : ");
        getFloat(&number);
        // for (int i = 0; i < 10; i++)
        // {
        //     result[i].id = 0;
        // }
        for (int i = 0; i < total; i++)
        {
            if (prod[i].price == number)
            {
                result[k] = prod[i];
                k++;
            }
        }
        listProduct(result, k);
        k = 0;
    }

    free(string);
}
// ----------------------------------------------------------------------------------------- Loop
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
// ----------------------------------------------------------------------------------------- Initialize
void initiate()
{
    total = readFile(prod);
    printf("Total : %d\n", total);
    if (total == 0)
    {
        uuid = 0;
    }
    else
    {
        uuid = prod[total - 1].id;
        printf("UUID : %d\n", uuid);
    }
}
// ----------------------------------------------------------------------------------------- MAIN
int main(void)
{
    unsigned short exit = 0;
    unsigned short input;
    initiate();
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
        while (1)
        {
            switch (input)
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
                printf("Huh?\n");
                break;
            }
            break;
        }
    }
    return 0;
}
