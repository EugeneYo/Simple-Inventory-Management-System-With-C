#ifndef PRODUCT_CONTROLLER_H
#define PRODUCT_CONTROLLER_H

#include "../model/product.h"
#include "../ansi_color/color.h"

void listProduct(Product *prod, unsigned int *total);
void addProduct(Product *prod, unsigned int *total, unsigned int *uid);
void deleteProduct(Product *prod, unsigned int *total);
void updateProduct(Product *prod, unsigned int *total);
void searchProduct(Product *prod, unsigned int *total, unsigned int *action);
void initiate(Product *prod, unsigned int *total, unsigned int *uid, unsigned int *size);

#endif
