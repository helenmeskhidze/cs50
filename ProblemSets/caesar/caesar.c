#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string a);
string encoder(string text, int k);

int main(int argc, string argv[])
{
    // check that submit50 cs50/problems/2024/x/caesarthe user has provided at least one and only one command line argument
    if (argv[1] == NULL || argv[2] != NULL)
    {
        printf("Usage: ./caesar key\n");
        exit(1);
    }

    // check that the user has provided only a number as that commant line argument
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        exit(1);
    }

    int k = atoi(argv[1]);
    string textToConvert = get_string("plaintext:  ");
    string convertedText = encoder(textToConvert, k);
    printf("ciphertext: %s\n", convertedText);
    return 0;
}

bool only_digits(string a)
{
    for (int i = 0, n = strlen(a); i < n; i++)
    {
        if (isdigit(a[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

string encoder(string text, int k)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // get the int of the current char
        int num = (int) text[i];

        // cipher on uppercase letters
        if (num >= 65 && num <= 90)
        {
            num -= 65;
            text[i] = (char)((num + k) % 26) + 65;
        }
        // cipher on lowercase letters
        else if (num >= 97 && num <= 122)
        {
            num -= 97;
            int test = ((num + k) % 26) + 97;
            text[i] = (char)((num + k) % 26) + 97;
        }
    }
    return text;
}
