#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct
{
    unsigned int id;
    char name[128];
    char genre[64];
    unsigned int quantity;
    float price;
} Product;

#endif