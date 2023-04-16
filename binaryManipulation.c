#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Binary things
int countBits(unsigned value);

int countBits(unsigned value)
{
    int nbBits = 0;
    double binaryValue = 0;
    int remainder = 1;
    int i = 1;

    while (value != 0)
    {
        // Si on veut juste savoir le nombre de bits, on peut faire le nbBits += value % 2, cela n'ajoutera que des 1 ou des 0 au final
        remainder = value % 2;

        if (remainder)
        {
            nbBits++;
        }
        value /= 2;
        binaryValue = remainder * i;
        i *= 10;
    }
    return  nbBits;
}