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