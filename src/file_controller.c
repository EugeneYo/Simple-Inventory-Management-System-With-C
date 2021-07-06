
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product_controller.h"
#include "file_controller.h"

unsigned int totalProduct()
{
    int n = 0;
    FILE *f = fopen(DATA, "r");
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
    FILE *f = fopen(DATA, "w");
    for (int i = 0; i < *total; i++)
    {
        fprintf(f, "%d\n", (prod + i)->id);
        fputs((prod + i)->name, f);
        fprintf(f, "\n");
        fputs((prod + i)->genre, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", (prod + i)->quantity);
        fprintf(f, "%.2f\n", (prod + i)->price);
    }
    fclose(f);
}
void readFile(Product *prod)
{
    int n = 0;
    FILE *f = fopen(DATA, "r");
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

unsigned int totalProductCSV()
{
    int n = -1;
    FILE *f = fopen(CSV, "r");
    char line[256];
    while (fgets(line, sizeof(line), f)) n++;
    fclose(f);
    n = (n == -1) ? 0 : n;
    return n;
}
void writeCSV(Product *prod, unsigned int *total)
{
    FILE *f = fopen(CSV, "w");
    fprintf(f, "%s, %s, %s, %s, %s\n", "ID", "Name", "Genre", "Quantity", "Price");
    for (int i = 0; i < *total; i++)
    {
        fprintf(f, "%d, %s, %s, %d, %.2f\n", prod[i].id, prod[i].name, prod[i].genre, prod[i].quantity, prod[i].price);
    }
    fclose(f);
}
void readCSV(Product *prod)
{
    FILE *f = fopen(CSV, "r");
    char string[2048];
    int row = 0;
    int column = 0;
    while (fgets(string, 2048, f))
    {
        column = 0;
        row++;
        // Skip the header row
        if (row == 1)
            continue;

        // Splitting the data
        char *value = strtok(string, ", ");
        while (value)
        {
            if (column == 0) prod[row - 2].id = atoi(value); // ID
            
            if (column == 1) strcpy(prod[row - 2].name, value); // Name
            
            if (column == 2) strcpy(prod[row - 2].genre, value); // Genre
            
            if (column == 3) prod[row - 2].quantity = atoi(value); // Quantity

            if (column == 4) prod[row - 2].price = atof(value); // Price
            
            value = strtok(NULL, ", ");
            column++;
        }
    }
    fclose(f);
}
