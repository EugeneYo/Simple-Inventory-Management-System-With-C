#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include "../model/product.h"
#include "../ansi_color/color.h"

#define DATA "data/Inventory.txt"
#define CSV "data/Inventory.csv"

unsigned int totalProduct();
void writeFile(Product *prod, unsigned int *total);
void readFile(Product *prod);

unsigned int totalProductCSV();
void writeCSV(Product *prod, unsigned int *total);
void readCSV(Product *prod);

#endif