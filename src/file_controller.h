#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <product.h>
#include <color.h>

#define DATA "data/Inventory.txt"
#define CSV "data/Inventory.csv"
#define INI "config.ini"

void readINI(unsigned int *viewLimit);
unsigned int totalProductCSV();
void writeCSV(Product *prod, unsigned int *total);
void readCSV(Product *prod);

#endif