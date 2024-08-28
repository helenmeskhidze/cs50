#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // get input and check if between 1 and 8 inclusive
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        // spaces
        for (int j = 1; j < (n - i); j++)
        {
            printf(" ");
        }
        // left hashes
        for (int k = 0; k - 1 < i; k++)
        {
            printf("#");
        }
        // middle spaces
        printf("  ");

        // right hashes
        for (int l = -1; l < i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
