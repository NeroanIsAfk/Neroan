#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Strings manipulation
void to_camel_case(char* text, char* camel);
void spin_words(const char* sentence, char* result);
char* to_jaden_case(char* jaden_case, const char* string);

// Number manipulation
int digital_root(int number);
int persistence(int number);
int find_outlier(const int* values, int count);

// Binary things
int countBits(unsigned value);

void main(void)
{
    /*char* text;
    char* camel;

    text = (char*)malloc(32 * sizeof(char));
    camel = (char*)malloc(32 * sizeof(char));
    */
    int numbers[20] = { 1,1,-1,1,1,-44,7,7,7,7,7,7,7,7 };
    printf("%d", find_outlier(numbers, 14));
}

/* 
   Explication du calcul du nombre de chiffres dans un nombre :
   1. Tout d'abord, on met la valeur en absolue grâce à l'instruction abs, ce qui évitera les valeurs négatives
   2. Ensuite, on aura le log10, ici il faut comprendre que log10(100) -> 2, log10(1000) -> 3, log10(10000) -> 4, log10(9999) 3,99...
   3. Et le floor qui nous permettra d'arrondir le chiffre pour le faire +1 ensuite pour avoir le nombre de chiffres
*/

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

// Hormis le if, tout le module est utile pour la transformation d'un nombre décimal en binaire

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

char* to_jaden_case(char* jaden_case, const char* string)
{
    bool blank = false;

    while (!iscntrl(*jaden_case))
    {
        if (blank)
        {
            jaden_case = toupper(jaden_case);
            blank = false;
        }

        if (isspace(*jaden_case))
        {
            blank = true;
        }
        jaden_case++;
    }
    return jaden_case;
}

void spin_words(const char* sentence, char* result) 
{
    int iSentence = strlen(sentence);
    result[iSentence] = '\0';
    iSentence--;

    while (!iscntrl(*sentence))
    {
        result[iSentence] = *sentence;
        sentence++;
        iSentence--;
    }
}

// Cette fonction à pour objectif de transformer n'importe quelle chaine de caractère écrite avec le format texte_texte en camelCase

void to_camel_case(char* text, char* camel)
{
    int iCount = 0;
    bool underscore = false;

    while (!iscntrl(*text))
    {
        if (!isalpha(*text))
        {
           underscore = true;
        }
        else
        {
            if (underscore)
            {
                underscore = false;
                camel[iCount] = toupper(*text);
            }
            else
            {
                camel[iCount] = *text;
            }
            iCount++;
        }
        text++;
    }
    camel[iCount] = '\0';
}