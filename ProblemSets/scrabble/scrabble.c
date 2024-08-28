// This is scrabble point calculator. It should be able to handle any number of Players if you change the numPlayers at the top.
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int numPlayers = 2;
    int points[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    string words[numPlayers];
    int scores[numPlayers];

    for (int i = 0; i < numPlayers; i++)
    {
        words[i] = get_string("Player %i: ", i + 1);
        scores[i] = 0;
    }
    // Loop through each player's submitted word, then each letter in the word
    for (int i = 0; i < numPlayers; i++)
        for (int j = 0, n = strlen(words[i]); j < n; j++)
        {
            int a = toupper(words[i][j]);
            if (a - 65 >= 0 && a - 65 <= 25)
            {
                scores[i] += points[a - 65];
            }
        }
    // Tie condition true until set to false when one player's score is higher than another's. 
    bool Tie = true;
    int highestScore = 0;
    for (int i = 1; i < numPlayers; i++)
    {
        if (scores[i] > scores[0])
        {
            highestScore = i;
            Tie = false;
        }
        else if (scores[i] < scores[0])
        {
            Tie = false;
        }
    }
    if (Tie == true)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player %i wins!\n", highestScore + 1);
    }
}
