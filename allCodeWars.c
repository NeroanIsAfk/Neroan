#include <stddef.h>
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
char* rot13(const char* source);

// Number manipulation
int digital_root(int number);
int persistence(int number);
int find_outlier(const int* values, int count);

// Binary things
int countBits(unsigned value);

// Morse
char* decode_morse(const char* morse_code);

#define NB_MORSE_CODE 55

const char* morse[NB_MORSE_CODE] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-....-", "..--.-", ".-..-.", "...-..-", ".--.-.", "...---..." };
const char* ascii[NB_MORSE_CODE] = { "A",  "B",    "C",    "D",   "E", "F",    "G",   "H",    "I",  "J",    "K",   "L",    "M",  "N",  "O",   "P",    "Q",    "R",   "S",   "T", "U",   "V",    "W",   "X",    "Y",    "Z",    "0",     "1",     "2",     "3",     "4",     "5",     "6",     "7",     "8",     "9",     ".",      ",",      "?",      "'",      "!",      "/",     "(",     ")",      "&",     ":",      ";",      "=",     "+",     "-",      "_",      "\"",     "$",       "@",      "SOS" };

void main(void)
{
    /*char* text;
    char* camel;

    text = (char*)malloc(32 * sizeof(char));
    camel = (char*)malloc(32 * sizeof(char));
    */
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

char* rot13(const char* source)
{
    char* result = malloc(strlen(source) * sizeof(char) + 1); // add 1 to include the null terminator

    if (result == NULL)
    {
        return NULL;
    }

    char* output = result; // create a separate pointer that points to the beginning of the allocated memory block

    while (*source != '\0')
    {
        if ((*source >= 'a' && *source <= 'z') || (*source >= 'A' && *source <= 'Z'))
        {
            if ((*source >= 'N' && *source <= 'Z') || *source >= 'n')
            {
                *output = *source - 13;
            }
            else
            {
                *output = *source + 13;
            }
        }
        else
        {
            *output = *source; // copy non-alphabetic characters directly
        }
        output++;
        source++;
    }
    *output = '\0'; // add the null terminator to the end of the modified string
    return result;
}

char* decode_morse(const char* morse_code)
{
    char* result = malloc(64 * sizeof(char) + 1); // add 1 to include the null terminator

    if (result == NULL)
    {
        return NULL;
    }

    char* output = result;
    int whiteSpace = 0;

    while (*morse_code)
    {
        char morseChar[8] = "";
        int iMorseChar = 0;

        if (isblank(*morse_code))
        {
            whiteSpace++;
            morse_code++;
        }
        else
        {
            whiteSpace = 0;
        }

        if (whiteSpace == 3)
        {
            *output = ' ';
            output++;
        }

        while (!isblank(*morse_code) && *morse_code)
        {
            morseChar[iMorseChar] = *morse_code;
            iMorseChar++;
            morse_code++;
        }

        // Change the morse code to ascii and writing it 
        for (int i = 0; i < NB_MORSE_CODE; i++)
        {
            if (strcmp(morseChar, morse[i]) == 0)
            {
                *output = *ascii[i];
                output++;
            }
        }
    }
    *output = '\0';
    return result;
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