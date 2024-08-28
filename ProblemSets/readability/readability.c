#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int lettercounter(string input);
int wordcounter(string input);
int sentencecounter(string input);

int main(void)
{
    string input = get_string("Input: ");
    int letters = lettercounter(input);
    int words = wordcounter(input);
    int sentences = sentencecounter(input);

    float l = (float) letters / (float) words * 100.0;
    float s = (float) sentences / (float) words * 100.0;

    double readabilityScore = round(0.0588 * l - 0.296 * s - 15.8);

    if (readabilityScore < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else if (readabilityScore >= 1.0 && readabilityScore <= 16.0)
    {
        printf("Grade %i\n", (int) readabilityScore);
    }
    else if (readabilityScore > 16.0)
    {
        printf("Grade 16+\n");
    }
}

int lettercounter(string input)
{
    int letters = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isalnum(input[i]))
        {
            letters++;
        }
    }
    return letters;
}

int wordcounter(string input)
{
    int words = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        // check spaces; if space, then it must be a new word
        if (isspace(input[i]))
        {
            words++;
        }
        else if (input[i] == '.' || input[i] == '!' || input[i] == '?' || input[i] == ',')
        {
            words++;
            i += 1;
        }
    }

    return words;
}

int sentencecounter(string input)
{
    int sentences = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}
