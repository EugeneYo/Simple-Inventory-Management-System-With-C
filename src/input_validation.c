#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_validation.h"

void getDigit(unsigned int *digit)
{
    char *p = (char *)malloc(sizeof(char));
    char *input = (char *)malloc(128 * sizeof(char));
    unsigned short ask = 1;
    fflush(stdin);
    while (ask)
    {
        fgets(input, 10, stdin);
        *digit = strtol(input, &p, 10);
        ask = (p == input || *p != '\n') ? printf("Invalid input ! Enter again: ") : 0;
    }
    free(p);
    free(input);
}

void getFloat(float *number)
{
    char *p = (char *)malloc(sizeof(char));
    char *input = (char *)malloc(128 * sizeof(char));
    unsigned short ask = 1;
    fflush(stdin);
    while (ask)
    {
        fgets(input, 10, stdin);
        *number = strtof(input, &p);
        ask = (p == input || *p != '\n') ? printf("Invalid input ! Enter again: ") : 0;
    }
    free(p);
    free(input);
}