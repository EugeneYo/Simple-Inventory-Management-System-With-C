#include <file_controller.h>

void readINI(unsigned int *viewLimit){
    FILE *f = fopen(INI, "r");
    char line[256];
    while (fgets(line, sizeof(line), f)){
        char *value = strtok(line, " = ");
        // printf("First Value : %s", value); // ViewLimit
        value = strtok(NULL, " = ");// 10
        *viewLimit = atoi(value);
        // printf("Second Value : %s", value);
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
