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
    printf(" \t\t\t***** INVENTORY *****\n");
    printf("------------------------------------------------------------------\n");
    printf("S.N.|    %-5s|  %-10s|  %-10s| %-10s|  %-10s|\n", "ID", "Name", "Genre", "Quantity", "Price");
    printf("------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++)
    { 
        printf("%-4d|    %-5d|  %-10s|  %-10s| %-10d|  %-10.2f|\n", i + 1, prod[i].id, prod[i].name, prod[i].genre, prod[i].quantity, prod[i].price);
    }
    printf("------------------------------------------------------------------\n\n");
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
    char *input = (char *)malloc(128 * sizeof(char));
    
    listProduct();
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
        printf("%22s%10s -> %-10s\n", "","[Old]", "[New]");
        printf("%-20s: %10s -> ", "Product Name",prod[item].name);
        fflush(stdin);
        fgets(input, 100, stdin);
        if(*input != '\n'){
            input[strcspn(input, "\n")] = 0;
            strcpy(prod[item].name, input);
        }


        printf("%-20s: %10s -> ","Product Genre",prod[item].genre);
        fflush(stdin);
        fgets(input, 100, stdin);
        if(*input != '\n'){
            input[strcspn(input, "\n")] = 0;
            strcpy(prod[item].genre, input);
        }

        printf("%-20s: %10d -> ","Product Quantity",prod[item].quantity);
        fflush(stdin);
        fgets(input, 100, stdin);
        if(*input != '\n'){
            input[strcspn(input, "\n")] = 0;
            if(atoi(input)==0){
                printf("Invalid input ! Enter again: ");
                getDigit(&prod[item].quantity);
            }else{
                prod[item].price = atoi(input);
            }
        }
    
        printf("%-20s: %10.2f -> ","Product Price",prod[item].price );
        fflush(stdin);
        fgets(input, 100, stdin);
        if(*input != '\n'){
            input[strcspn(input, "\n")] = 0;
            if(atof(input)==0){
                printf("Invalid input ! Enter again: ");
                getFloat(&prod[item].price);
            }else{
                prod[item].price = atof(input);
            }
        }
        
        printf("Product with ID %d updated successfully.\n", id);
    }
    else
    {
        printf("Product with ID %d does not exist.\n", id);
    }
    writeFile(prod,total);
}

void initiate(){
    total = readFile(prod);
    printf("Total : %d\n", total);
    uuid = prod[total-1].id;
    printf("UUID : %d\n", uuid);
}