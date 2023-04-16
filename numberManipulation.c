#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Number manipulation
int digital_root(int number);
int persistence(int number);
int find_outlier(const int* values, int count);
int numberLengh(int number);

int numberLengh(int number)
{
    return floor(log10(abs(number))) + 1;
}

int digital_root(int number)
{
    int nbDigits = floor(log10(abs(number))) + 1;

    while (nbDigits > 1)
    {
        int numberToReturn = 0;

        for (int i = 0; i < nbDigits; i++)
        {
            numberToReturn += number % 10;
            number /= 10;
        }

        number = numberToReturn;
        nbDigits = floor(log10(abs(number))) + 1;
    }
    return number;
}

int persistence(int number)
{
    int nbTimes = 0;
    int nbDigits = floor(log10(abs(number))) + 1;

    while (nbDigits > 1)
    {
        int numberToReturn = number % 10;

        for (int i = 1; i < nbDigits; i++)
        {
            number /= 10;
            numberToReturn *= number % 10;
        }

        number = numberToReturn;
        nbTimes++;
        nbDigits = floor(log10(abs(number))) + 1;
    }
    return nbTimes;
}

int find_outlier(const int* values, int count)
{
    int oddNumber;
    int evenNumber;
    int odd = 0;
    int even = 0;

    for (int i = 0; i < count; i++)
    {
        if (abs(*values) % 2 == 1)
        {
            oddNumber = *values;
            odd++;
        }
        else
        {
            evenNumber = *values;
            even++;
        }
        values++;
    }
    return odd > even ? evenNumber : oddNumber;
}