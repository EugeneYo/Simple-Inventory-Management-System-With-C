#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_controller.h"
#include "input_validation.h"
#include "product_controller.h"


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
    writeCSV(prod, total);
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
    writeCSV(prod, total);
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
    writeCSV(prod, total);
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

void initiate(Product *prod, unsigned int *total, unsigned int *uid, unsigned int *size)
{
    *total = totalProductCSV();
    if(*total > *size){
        *size = *total + 10;
        prod = realloc(prod, ((*size) * sizeof(Product)));
    }
    readCSV(prod);
    *uid = (*total == 0) ? 0 : prod[*total - 1].id;
}