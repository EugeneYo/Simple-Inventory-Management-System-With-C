
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product_controller.h"
#include "file_controller.h"

unsigned int totalProduct()
{
    int n = 0;
    FILE *f;
    f = fopen(DATA, "r");
    if (!f)
        printf("Can't open file\n");

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
    FILE *f;
    f = fopen(DATA, "w");
    if (!f)
        printf("Can't open file\n");

    for (int i = 0; i < *total; i++)
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
    f = fopen(DATA, "r");
    if (!f)
        printf("Can't open file\n");

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
    int n = 0;
    FILE *f = fopen(CSV, "r");
    char line[256];
    while (fgets(line, sizeof(line), f))
        n++;
    fclose(f);
    return n;
}
void writeCSV(Product *prod, unsigned int *total)
{
    FILE *f = fopen(CSV, "w");
    fprintf(f, "%s, %s, %s, %s, %s\n", "ID", "Name", "Genre", "Quantity", "Price");
    for (int i = 0; i < *total; i++)
    {
        fprintf(f, "%d, %s, %s, %d, %f\n", prod[i].id, prod[i].name, prod[i].genre, prod[i].quantity, prod[i].price);
    }
    fclose(f);
}
void readCSV(Product *prod)
{
    FILE *f = fopen(CSV, "r");
    char string[1024];
    int row = 0;
    int column = 0;
    while (fgets(string, 1024, f))
    {
        column = 0;
        row++;
        
        if (row == 1)
            continue;

        // Splitting the data
        char *value = strtok(string, ", ");
        while (value)
        {
            if (column == 0)
                prod[row - 1].id = atoi(value);

            if (column == 1)
                strcpy(prod[row - 1].name, value);

            if (column == 2)
                strcpy(prod[row - 1].genre, value);

            if (column == 3)
                prod[row - 1].quantity = atoi(value);

            if (column == 4)
                prod[row - 1].price = atof(value);

            value = strtok(NULL, ", ");
            column++;
        }
    }
    fclose(f);
}
