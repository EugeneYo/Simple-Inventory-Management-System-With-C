
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "product_controller.h"


int readFile(Product *prod)
{
    int n = 0;
    int i;
    FILE *f;
    f = fopen("GameInventory.txt", "r");
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
    fclose(f);
    return n;
}

void writeFile(Product *prod, unsigned int total)
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
