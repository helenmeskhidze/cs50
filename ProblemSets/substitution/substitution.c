#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool keyChecker(string a);
string encoder(string text, string key);

int main(int argc, string argv[])
{
    string key = argv[1];
    string textToConvert;

    // check that the user has provided at least one and only one command line argument
    if (argv[1] == NULL || argv[2] != NULL)
    {
        printf("Usage: ./caesar key\n");
        exit(1);
    }

    if (keyChecker(key) == false)
    {
        printf("Key not right format!\n");
        return 1;
    }
    else
    {
        textToConvert = get_string("plaintext:  ");
    }

    string convertedText = encoder(textToConvert, key);
    printf("ciphertext: %s\n", convertedText);
    return 0;
}

bool keyChecker(string a)
{
    int n = strlen(a);
    if (n != 26)
    {
        return false;
    }

    // force uppercase with toupper, store the numerical codes in toNum
    int toNum[26];
    for (int i = 0, j = strlen(a); i < j; i++)
    {
        if (isalpha(a[i]) != 0)
        {
            toNum[i] = (int) toupper(a[i]);
        }
        else
        {
            return false;
        }
    }

    // check for repeats by checking everything after i
    // (will also ensure all letters are present)
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (toNum[j] == toNum[i])
            {
                return false;
            }
        }
    }
    return true;
}

string encoder(string text, string key)
{
    // convert the keys to upper again for ease of use later
    for (int i = 0, j = strlen(key); i < j; i++)
    {
        key[i] = (int) toupper(key[i]) - 65;
    }

    for (int i = 0, j = strlen(text); i < j; i++)
    {
        int a = (int) text[i];

        // if uppercase
        if (65 <= a && a <= 90)
        {
            text[i] = (char)(key[a - 65] + 65);
        }
        // if lowercase
        if (97 <= a && a <= 122)
        {
            text[i] = (char)(key[a - 97] + 97);
        }
    }
    return text;
}
