#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "file_controller.h"
#include "input_validation.h"
#include "product_controller.h"

Product prod[50];
unsigned int total = 0;
unsigned int uuid = 0;


void listProduct()
{
    if (total == 0)
    {
        printf("No products to view\n");
        return;
    }
    printf(" \t\t\t\t *****  INVENTORY *****\n");
    printf("------------------------------------------------------------------\n");
    printf("S.N.|    %-5s|  %-10s|  %-10s| %-10s|  %-10s|\n", "ID", "Name", "Genre", "Quantity", "Price");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++)
    { 
        printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].genre, prod[i].quantity, prod[i].price);
    }
    printf("------------------------------------------------------------------\n");
}
void addProduct()
{
    prod[total].id = uuid + 1;

    printf("Product Name: ");
    fflush(stdin);
    gets(prod[total].name);

    printf("Product Genre: ");
    fflush(stdin);
    gets(prod[total].genre);

    printf("Product Quantity: ");
    getDigit(&prod[total].quantity);
    fflush(stdin);

    printf("Product Price: ");
    getFloat(&prod[total].price);
    fflush(stdin);
    total++;
    uuid++;
    listProduct();
    writeFile(prod, total);
}

void deleteProduct()
{
    unsigned int id;
    unsigned int exist = 0;
    listProduct();
    printf("Please select the ID of the product to delete : ");
    getDigit(&id);

    for (int i = 0; i < total; i++)
    {
        if(prod[i].id == id)
            exist = 1;

        if(exist)
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
    writeFile(prod,total);
}

void updateProduct()
{
    unsigned int id;
    unsigned int exist = 0;
    unsigned int item;
    listProduct();
    printf("Please select the ID of the product to update : ");
    getDigit(&id);

    for (int i = 0; i < total; i++)
    {
        if (prod[i].id == id)
        {
            prod[i] = prod[i + 1];
            exist = 1;
            item = i;
        }
    }
    if (exist)
    {
        prod[item].id = id;

        printf("Product Name: ");
        fflush(stdin);
        gets(prod[item].name);

        printf("Product Genre: ");
        fflush(stdin);
        gets(prod[item].genre);

        printf("Product Quantity: ");
        getDigit(&prod[item].quantity);
        fflush(stdin);

        printf("Product Price: ");
        getFloat(&prod[item].price);
        fflush(stdin);
        printf("Product with ID %d updated successfully.\n", id);
    }
    else
    {
        printf("Product with ID %d does not exist.\n", id);
    }
    writeFile(prod,total);
}

void initiation(){
    total = readFile(prod);
    printf("Total : %d\n", total);
    uuid = prod[total-1].id;
    printf("UUID : %d\n", uuid);
}