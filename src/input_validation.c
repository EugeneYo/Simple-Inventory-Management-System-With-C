#include <input_validation.h>

void getDigit(unsigned int *digit)
{
    char *p;
    char input[128];
    unsigned short ask = 1;
    fflush(stdin);
    while (ask)
    {
        fgets(input, 10, stdin);
        *digit = strtol(input, &p, 10);
        ask = (p == input || *p != '\n') ? printf("Invalid input ! Enter again: ") : 0;
    }
}

void getFloat(float *number)
{
    char *p;
    char input[128];
    unsigned short ask = 1;
    fflush(stdin);
    while (ask)
    {
        fgets(input, 10, stdin);
        *number = strtof(input, &p);
        ask = (p == input || *p != '\n') ? printf("Invalid input ! Enter again: ") : 0;
    }
}